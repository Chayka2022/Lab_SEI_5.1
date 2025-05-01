#include "hysteresis.h"

void hysteresis_cycle_call(Hysteresis_t *hysteresis, int16_t value)
{
    hysteresis_set_current_value(hysteresis, value);
    if (hysteresis->current_value > hysteresis->previous_value + hysteresis->hysteresis_value)
    {
        hysteresis->direction = DC_MOTOR_BACKWARD;
        hysteresis->previous_value = hysteresis->current_value;
    }
    else if (hysteresis->current_value < hysteresis->previous_value - hysteresis->hysteresis_value)
    {
        hysteresis->direction = DC_MOTOR_FORWARD;
        hysteresis->previous_value = hysteresis->current_value;
    }
    else
    {
        hysteresis->direction = DC_MOTOR_STOP;
    }
}

void hysteresis_init(Hysteresis_t *hysteresis, int16_t setpoint, int16_t hysteresis_value)
{
    hysteresis->setpoint = setpoint;
    hysteresis->hysteresis_value = hysteresis_value;
    hysteresis->current_value = 0;
    hysteresis->direction = DC_MOTOR_STOP;
}

void hysteresis_set_setpoint(Hysteresis_t *hysteresis, int16_t setpoint)
{
    hysteresis->setpoint = setpoint;
    hysteresis->previous_value = hysteresis->current_value;
}

void hysteresis_set_current_value(Hysteresis_t *hysteresis, int16_t current_value)
{
    hysteresis->current_value = current_value;
}

int16_t hysteresis_get_current_value(Hysteresis_t *hysteresis)
{
    return(hysteresis->current_value);
}

DCMotorDirection_t hysteresis_get_direction(Hysteresis_t *hysteresis)
{
	return hysteresis->direction;
}