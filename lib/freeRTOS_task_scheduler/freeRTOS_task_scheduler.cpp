#include "freeRTOS_task_scheduler.h"

DD_VARIABLE_RESISTOR_H_t variableResistor;
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
    own_stdio_setup();

    dd_variable_resistor_setup(&variableResistor);

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
        variableResistorValue = dd_variable_resistor_cycle_call(&variableResistor);
        dcMotorSetSpeed(&motor, SERVO_MOTOR_SPEED);
        //printf("Resistor Value: %d. Users set value: %d\n\r", variableResistorValue, usersCurrentSetValue);
        if(dd_variable_resistor_get_value() != usersCurrentSetValue)
        {
            dd_variable_resister_set_wasModified(&variableResistor, true);
        }
        else 
        {
            dd_variable_resister_set_wasModified(&variableResistor, true);
        }
        if(dd_variable_resister_get_wasModified(&variableResistor) == true)
        {
            while(variableResistorValue != usersCurrentSetValue)
            {
                variableResistorValue = dd_variable_resistor_cycle_call(&variableResistor); 
                dcMotorSetDirection(&motor, dcMotorCalculateDirection(&motor, usersCurrentSetValue, variableResistorValue, HYSTERESIS_VALUE));
                if(dcMotorGetDirection(&motor) == DC_MOTOR_STOP)
                {
                    usersCurrentSetValue = variableResistorValue;
                }
                dcMotorCycleCall(&motor, &hbridge);
            }
        }
        hysteresis_cycle_call(&hysteresis, variableResistorValue);
        dcMotorSetDirection(&motor, hysteresis_get_direction(&hysteresis));
        dcMotorSetSpeed(&motor, STOP_MOTOR_SPEED);
        vTaskDelay(16 / portTICK_PERIOD_MS);
    }
}

void printValuesTask(void *pvParameters) 
{
    printf("Resistor Value: %d. Users set value: %d\n\r", variableResistorValue, usersCurrentSetValue);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
}

void vApplicationIdleHook()
{
    static uint8_t needInit = true;
    if(needInit)
    {
        initUserInterface();
        needInit = false;
    }
    uint8_t result = processUserCommand();
    dd_variable_resister_set_wasModified(&variableResistor, result);
}