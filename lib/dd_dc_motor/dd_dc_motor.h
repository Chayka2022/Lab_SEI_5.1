#ifndef DD_DC_MOTOR_H
#define DD_DC_MOTOR_H

#include <Arduino.h>
#include "config.h"
#include "own_stdio.h"
#include "dd_h_bridge.h"


enum DCMotorDirection_t
{
    DC_MOTOR_STOP = 0,
    DC_MOTOR_BACKWARD,
    DC_MOTOR_FORWARD,

};

typedef struct DD_DC_MOTOTR_H_t
{
    int8_t speed;
    uint8_t direction;
    uint8_t wasModified;
} DD_DC_MOTOTR_H_t;

void dcMotorInit(   
                    DD_DC_MOTOTR_H_t *motor,
                    uint8_t direction,
                    int8_t speed,
                    uint8_t wasModified
                );

void dcMotorCycleCall(DD_DC_MOTOTR_H_t *motor, HBridge_t *hbridge);

void dcMotorSetSpeed(DD_DC_MOTOTR_H_t *motor, int8_t value);
int8_t dcMotorGetSpeed(DD_DC_MOTOTR_H_t *motor);

void dcMotorSetDirection(DD_DC_MOTOTR_H_t *motor, uint8_t direction);
uint8_t dcMotorCalculateDirection(DD_DC_MOTOTR_H_t *motor, uint16_t usersSetValue, uint16_t currentValue, uint8_t hysteresis_value);
uint8_t dcMotorGetDirection(DD_DC_MOTOTR_H_t *motor);

void dcMotorStop(DD_DC_MOTOTR_H_t *motor);
void dcMotorEmergencyStop(DD_DC_MOTOTR_H_t *motor);

void dcMotorSetMaxSpeed(DD_DC_MOTOTR_H_t *motor);

void dcMotorSpeedUp(DD_DC_MOTOTR_H_t *motor);
void dcMotorSpeedDown(DD_DC_MOTOTR_H_t *motor);

uint8_t dcMotorComputeDirection(int8_t speed);

int16_t dcMotorConvertSpeedToPwm(int16_t speed);

#endif // !DD_DC_MOTOR_H