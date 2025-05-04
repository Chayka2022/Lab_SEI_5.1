#include "dd_h_bridge.h"

void hbridgeInit(   
                    HBridge_t *hbridge,
                    uint8_t pwm_pin,
                    uint8_t in_1,
                    uint8_t in_2,
                    HBridgeDirection_t direction,
                    uint16_t pwmValue
                )
{
    //printf("HBridge Init\n\r");
    hbridge->pwm_pin = pwm_pin;
    hbridge->in_1 = in_1;
    hbridge->in_2 = in_2;

    hbridgeEnable(hbridge);
    hbridgeSetDirection(hbridge, direction);
    controlPwm(hbridge, pwmValue);
}

void controlPwm(HBridge_t *hbridge, uint16_t value)
{   
    hbridge->pwmValue = value;
    hbridgeSetPwmWrapper(hbridge->pwm_pin, value);
}

uint8_t hbridgeGetPwm(HBridge_t *hbridge)
{
    return hbridge->pwmValue;
}

void hbridgeSetDirection(HBridge_t *hbridge, HBridgeDirection_t direction)
{
    hbridge->direction = direction;
    if (direction == HBRIDGE_FORWARD)
    {
        hbridgeSetDirectionWrapper(hbridge->in_1, hbridge->in_2, HIGH, LOW);
        //printf("HBridge Direction: FORWARD\n\r");
    }
    else if (direction == HBRIDGE_BACKWARD)
    {
        hbridgeSetDirectionWrapper(hbridge->in_1, hbridge->in_2, LOW, HIGH);
        //printf("HBridge Direction: BACKWARD\n\r");
    }
    else
    {
        hbridgeSetDirectionWrapper(hbridge->in_1, hbridge->in_2, LOW, LOW);
        //printf("HBridge Direction: STOP\n\r");
    }
}

uint8_t hbridgeGetDirection(HBridge_t *hbridge)
{
    return hbridge->direction;
}

void hbridgeEnable(HBridge_t *hbridge)
{
    hbridgeSetPinAsOutputStateWrapper(hbridge->pwm_pin);
    hbridgeSetPinAsOutputStateWrapper(hbridge->in_1);
    hbridgeSetPinAsOutputStateWrapper(hbridge->in_2);
}

void hbridgeDisable(HBridge_t *hbridge)
{
    hbridgeSetPinAsInputStateWrapper(hbridge->pwm_pin);
    hbridgeSetPinAsInputStateWrapper(hbridge->in_1);
    hbridgeSetPinAsInputStateWrapper(hbridge->in_2);
}

void hbridgeStop(HBridge_t *hbridge)
{
    controlPwm(hbridge, 0);
}



