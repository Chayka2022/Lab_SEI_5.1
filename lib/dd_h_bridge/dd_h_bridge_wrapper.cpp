#include "dd_h_bridge_wrapper.h"

void hbridgeSetPwmWrapper(uint8_t pin, uint8_t value)
{
    analogWrite(pin, value);
}

void hbridgeSetDirectionWrapper(uint8_t in_1_pin, uint8_t in_2_pin, uint8_t in_1_vaue, uint8_t in_2_value)
{
    digitalWrite(in_1_pin, in_1_vaue);
    digitalWrite(in_2_pin, in_2_value);
}

void hbridgeSetPinAsOutputStateWrapper(uint8_t pin)
{
    pinMode(pin, OUTPUT);
}

void hbridgeSetPinAsInputStateWrapper(uint8_t pin)
{
    pinMode(pin, INPUT);
}

uint8_t hbridgeGetStateWrapper(uint8_t pin)
{
    return digitalRead(pin);
}