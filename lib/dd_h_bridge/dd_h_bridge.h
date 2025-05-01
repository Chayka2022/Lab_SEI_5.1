#ifndef DD_H_BRIDGE_H
#define DD_H_BRIDGE_H

#include <Arduino.h>
#include "config.h"
#include "own_stdio.h"
#include "dd_h_bridge_wrapper.h"

enum HBridgeDirection_t
{
    HBRIDGE_STOP = 0,
    HBRIDGE_BACKWARD,
    HBRIDGE_FORWARD
};

typedef struct HBridge_t
{
    uint8_t pwm_pin;
    uint8_t in_1;
    uint8_t in_2;
    HBridgeDirection_t direction;
    uint16_t pwmValue;
} HBridge_t;

void hbridgeInit(HBridge_t *hbridge,
                 uint8_t pwm_pin,
                 uint8_t in_1,
                 uint8_t in_2,
                 HBridgeDirection_t direction,
                 uint16_t pwmValue
                );

void controlPwm(HBridge_t *hbridge, uint16_t value);
uint8_t hbridgeGetPwm(HBridge_t *hbridge);

void hbridgeSetDirection(HBridge_t *hbridge, HBridgeDirection_t direction);
uint8_t hbridgeGetDirection(HBridge_t *hbridge);

void hbridgeEnable(HBridge_t *hbridge);
void hbridgeDisable(HBridge_t *hbridge);

void hbridgeStop(HBridge_t *hbridge);

#endif // !DD_H_BRIDGE_H