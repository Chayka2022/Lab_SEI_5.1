#ifndef DD_H_BRIDGE_WRAPPER_H
#define DD_H_BRIDGE_WRAPPER_H

#include <Arduino.h>

void hbridgeSetPwmWrapper(uint8_t pin, uint8_t value);
void hbridgeSetDirectionWrapper(uint8_t in_1_pin, uint8_t in_2_pin, uint8_t in_1_value, uint8_t in_2_value);

void hbridgeSetPinAsOutputStateWrapper(uint8_t pin);
void hbridgeSetPinAsInputStateWrapper(uint8_t pin);

uint8_t hbridgeGetStateWrapper(uint8_t pin);

#endif // !DD_H_BRIDGE_WRAPPER_H