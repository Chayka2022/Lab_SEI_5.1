#include "dd_variable_resistor.h"

static volatile uint16_t rawReadValue = 0;
static volatile uint16_t rawValueConvertedToResistance = 0;

void dd_variable_resistor_setup(void)
{
    pinMode(RESISTOR_PIN, INPUT);
}

uint16_t dd_variable_resistor_cycle_call(void)
{
    return dd_variable_resistor_get_value();
}

uint16_t dd_variable_resistor_get_value(void)
{
    rawReadValue = analogRead(RESISTOR_PIN);
    return rawReadValue;
    // printf("Resistance: %d\n\r", rawReadValue);
    // #include <stdlib.h>
    // char buffer[10];
    // dtostrf(dd_Sensors_convert_to_resistance_value(), 7, 2, buffer);
    // printf("Resistance: %s\n\r", buffer);
}

// double dd_Sensors_convert_to_resistance_value(void)
// {
//     uint16_t sensorVoltage = rawReadValue * VREF / ADC_RESOLUTION;
//     return rawValueConvertedToResistance = (VREF / sensorVoltage - 1) * R0;
// }