#ifndef DD_VARIABLE_RESISTOR_H
#define DD_VARIABLE_RESISTOR_H

#include <Arduino.h>
#include "config.h"
#include "own_stdio.h"
#include "MedianFilter.h"
#include "MeanFilter.h"

void dd_variable_resistor_setup(void);
uint16_t dd_variable_resistor_cycle_call(void);
uint16_t dd_variable_resistor_get_value(void);
uint16_t dd_variable_resistor_setMaxAngle();
uint16_t dd_variable_resistor_setMinAngle();
uint16_t dd_variable_resistor_setSetPoint();
uint16_t dd_variable_resistor_convertAngleToResistance(uint16_t angleValue);

#endif // !DD_VARIABLE_RESISTOR_H