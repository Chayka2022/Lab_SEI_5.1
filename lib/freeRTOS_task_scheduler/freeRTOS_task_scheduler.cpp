#include "freeRTOS_task_scheduler.h"

HBridge_t hbridge;
DD_DC_MOTOTR_H_t motor;
Hysteresis_t hysteresis;

uint16_t variableResistorValue;
uint16_t usersCurrentSetValue = SETPOINT_RESISTANCE;

void FreeRTOS_scheduler_setup(void *pvParameters)
{
    xTaskCreate(
        controlMotorTask,           /* Task function */
        "Control Motor Task",       /* Name of task */
        1000,                      /* Stack size in words */
        NULL,                      /* Parameter passed as input to the task */
        1,                         /* Priority of the task */
        NULL                       /* Task handle to keep track of created task */
    );

    vTaskStartScheduler();       /* Start the scheduler */
}

void initializeModules(void *pvParameters)
{
    printf("Setup started\n\r");
    
    own_stdio_setup();

    dd_variable_resistor_setup();

    hbridgeInit(
                    &hbridge, 
                    H_BRIDGE_PWM_PIN, 
                    H_BRIDGE_IN1_PIN, 
                    H_BRIDGE_IN2_PIN, 
                    HBRIDGE_STOP, 
                    MIN_PWM_VALUE
                );
    
    dcMotorInit(&motor, DC_MOTOR_STOP, MIN_MOTOR_SPEED,  false);

    hysteresis_init(&hysteresis, SETPOINT_RESISTANCE, HYSTERESIS_VALUE);
}

void controlMotorTask(void *pvParameters)
{
    static uint8_t needInit = true;

    if(needInit == true)
    {
        initializeModules(NULL);
        needInit = false;
    }

    for(;;)
    {
        variableResistorValue = dd_variable_resistor_cycle_call();
        dcMotorSetSpeed(&motor, SERVO_MOTOR_SPEED);
        while(variableResistorValue != usersCurrentSetValue)
        {
            variableResistorValue = dd_variable_resistor_cycle_call(); 
            //printf("Resistor Value: %d. Users set value: %d\n\r", variableResistorValue, usersCurrentSetValue);
            dcMotorSetDirection(&motor, dcMotorCalculateDirection(&motor, usersCurrentSetValue, variableResistorValue, HYSTERESIS_VALUE));
            if(dcMotorGetDirection(&motor) == DC_MOTOR_STOP)
            {
                usersCurrentSetValue = variableResistorValue;
            }
            dcMotorCycleCall(&motor, &hbridge);
        }
        hysteresis_cycle_call(&hysteresis, variableResistorValue);
        dcMotorSetDirection(&motor, hysteresis_get_direction(&hysteresis));
        dcMotorSetSpeed(&motor, STOP_MOTOR_SPEED);
        vTaskDelay(16 / portTICK_PERIOD_MS);
    }
}

void vApplicationIdleHook(void)
{
    static uint8_t needInit = true;
    if(needInit)
    {
        initUserInterface();
        needInit = false;
    }
    processUserCommand();
}