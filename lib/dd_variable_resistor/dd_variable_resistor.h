#ifndef DD_VARIABLE_RESISTOR_H
#define DD_VARIABLE_RESISTOR_H

#include <Arduino.h>
#include "config.h"
#include "own_stdio.h"

void dd_variable_resistor_setup(void);
uint16_t dd_variable_resistor_cycle_call(void);
uint16_t dd_variable_resistor_get_value(void);
//double dd_Sensors_convert_to_resistance_value(void);

#endif // !DD_VARIABLE_RESISTOR_H