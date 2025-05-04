#include "dd_dc_motor.h"

void dcMotorInit(
                    DD_DC_MOTOTR_H_t *motor,
                    uint8_t direction,
                    int8_t speed,
                    uint8_t wasModified
                )
{
    motor->direction = direction;
    motor->speed = STOP_MOTOR_SPEED;
    motor->wasModified = wasModified;
}

void dcMotorCycleCall(DD_DC_MOTOTR_H_t *motor, HBridge_t *hbridge)
{
    if (motor->wasModified == true)
    {
        hbridgeSetDirection(hbridge, HBridgeDirection_t(motor->direction));
        controlPwm(hbridge, dcMotorConvertSpeedToPwm(motor->speed));
        
        motor->wasModified = false; 
    }

    // if (motor->wasModified == true)
    // {
    //     motor->wasModified = false;
    //     uint8_t direction = dcMotorComputeDirection(motor->speed);
    //     int16_t pwmValue = dcMotorConvertSpeedToPwm(motor->speed);

    //     hbridgeSetDirection(hbridge, HBridgeDirection_t(direction));
    //     controlPwm(hbridge, pwmValue);

    //     printf("Motor direction: %d\n\r", direction);
    // }
}

void dcMotorSetSpeed(DD_DC_MOTOTR_H_t *motor, int8_t value)
{
    motor->speed = value;
    motor->wasModified = true;
}

int8_t dcMotorGetSpeed(DD_DC_MOTOTR_H_t *motor)
{
    return motor->speed;
}

void dcMotorSetDirection(DD_DC_MOTOTR_H_t *motor, uint8_t direction)
{
    motor->direction = direction;
    motor->wasModified = true;
}

uint8_t dcMotorCalculateDirection(DD_DC_MOTOTR_H_t *motor, uint16_t usersSetValue, uint16_t currentValue, uint8_t hysteresis_value)
{
    if (usersSetValue > currentValue)
    {
        motor->direction = DC_MOTOR_BACKWARD;
    }
    else if (usersSetValue < currentValue)
    {
        motor->direction = DC_MOTOR_FORWARD;
    }
    else
    {
        motor->direction = DC_MOTOR_STOP;
    }    
    return motor->direction;
}

uint8_t dcMotorGetDirection(DD_DC_MOTOTR_H_t *motor)
{
    return motor->direction;
}

void dcMotorStop(DD_DC_MOTOTR_H_t *motor)
{
    motor->speed = STOP_MOTOR_SPEED;
    motor->wasModified = true;
}

void dcMotorEmergencyStop(DD_DC_MOTOTR_H_t *motor)
{
    motor->direction = DC_MOTOR_STOP;
    motor->wasModified = true;
}

void dcMotorSetMaxSpeed(DD_DC_MOTOTR_H_t *motor)
{
    motor->speed = MAX_MOTOR_SPEED;
    motor->wasModified = true;
}

void dcMotorSpeedUp(DD_DC_MOTOTR_H_t *motor)
{
    if((motor->speed + SPEED_CHANGE_STEP) < MAX_MOTOR_SPEED)
    {
        motor->speed += SPEED_CHANGE_STEP;
    }
    else 
    {
        motor->speed = MAX_MOTOR_SPEED;   
    }
    motor->wasModified = true;
}

void dcMotorSpeedDown(DD_DC_MOTOTR_H_t *motor)
{
    if ((motor->speed - SPEED_CHANGE_STEP) > MIN_MOTOR_SPEED)
    {
        motor->speed -= SPEED_CHANGE_STEP;
    }
    else 
    {
        motor->speed = MIN_MOTOR_SPEED;   
    }
    motor->wasModified = true;
}

uint8_t dcMotorComputeDirection(int8_t speed)
{
    if (speed > 0)
    {
        return DC_MOTOR_FORWARD;
    }
    else if (speed < 0)
    {
        return DC_MOTOR_BACKWARD;
    }
    else
    {
        return DC_MOTOR_STOP;
    }
}

int16_t dcMotorConvertSpeedToPwm(int16_t speed)
{
    int16_t pwmValue = 0;

    pwmValue = (ABS(speed) * MAX_PWM_VALUE) / MAX_MOTOR_SPEED;
    return pwmValue;
}

