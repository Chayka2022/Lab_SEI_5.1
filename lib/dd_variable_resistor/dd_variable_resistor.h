#ifndef DD_VARIABLE_RESISTOR_H
#define DD_VARIABLE_RESISTOR_H

#include <Arduino.h>
#include "config.h"
#include "own_stdio.h"
#include "MedianFilter.h"
#include "MeanFilter.h"

typedef struct {
    uint16_t    value;
    uint8_t     wasModified;
} DD_VARIABLE_RESISTOR_H_t;

void        dd_variable_resistor_setup(DD_VARIABLE_RESISTOR_H_t *variableResistor);
uint16_t    dd_variable_resistor_cycle_call(DD_VARIABLE_RESISTOR_H_t *variableResistor);
void        dd_variable_resister_set_wasModified(DD_VARIABLE_RESISTOR_H_t *variableResistor, uint8_t wasModfied);
uint8_t     dd_variable_resister_get_wasModified(DD_VARIABLE_RESISTOR_H_t *variableResistor);
uint16_t    dd_variable_resistor_get_value(void);
uint16_t    dd_variable_resistor_setMaxAngle(void);
uint16_t    dd_variable_resistor_setMinAngle(void);
uint16_t    dd_variable_resistor_setSetPoint(void);
uint16_t    dd_variable_resistor_convertAngleToResistance(uint16_t angleValue);

#endif // !DD_VARIABLE_RESISTOR_H