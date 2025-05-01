#ifndef HYSTERESIS_H
#define HYSTERESIS_H

#include <stdint.h>
#include "config.h"
#include "dd_dc_motor.h"

typedef struct Hysteresis_t
{
    int16_t setpoint;
    int16_t current_value;
    int16_t previous_value;
    int16_t hysteresis_value;
    DCMotorDirection_t direction;
} Hysteresis_t;

void hysteresis_cycle_call(Hysteresis_t *hysteresis, int16_t value);
void hysteresis_init(Hysteresis_t *hysteresis, int16_t setpoint, int16_t hysteresis_value);
void hysteresis_set_setpoint(Hysteresis_t *hysteresis, int16_t setpoint);
void hysteresis_set_current_value(Hysteresis_t *hysteresis, int16_t current_value);
int16_t hysteresis_get_current_value(Hysteresis_t *hysteresis);
DCMotorDirection_t hysteresis_get_direction(Hysteresis_t *hysteresis);

#endif // !HYSTERESIS_H