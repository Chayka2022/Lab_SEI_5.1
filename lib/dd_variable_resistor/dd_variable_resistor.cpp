#include "dd_variable_resistor.h"

static volatile uint16_t rawReadValue = 0;
static volatile uint16_t rawValueConvertedToResistance = 0;

static volatile uint16_t sensorValueMedian = 0;
static volatile uint16_t sensorValueMean = 0;

static sMedianFilter_t medianFilter;
static sMedianNode_t medianBuffer[WINDOW_SIZE];

static MeanFilter_t meanFilter;
static uint16_t meanBuffer[WINDOW_SIZE];

static uint16_t resistanceValue;

void dd_variable_resistor_setup(void)
{
    medianFilter.numNodes = WINDOW_SIZE;
    medianFilter.medianBuffer = medianBuffer;
    
    MEDIANFILTER_Init(&medianFilter);

    MeanFilter_Init(&meanFilter, meanBuffer, WINDOW_SIZE);

    pinMode(RESISTOR_PIN, INPUT);
}

uint16_t dd_variable_resistor_cycle_call(void)
{
    rawReadValue = dd_variable_resistor_get_value();
    sensorValueMedian = MEDIANFILTER_Insert(&medianFilter, rawReadValue);
    sensorValueMean = MeanFilter_Insert(&meanFilter, sensorValueMedian);
    return rawReadValue;
}

uint16_t dd_variable_resistor_get_value(void)
{
    return analogRead(RESISTOR_PIN);
}

uint16_t dd_variable_resistor_setMaxAngle()
{
    return MAX_RESISTANCE;
}

uint16_t dd_variable_resistor_setMinAngle()
{
    return MIN_RESISTANCE;
}

uint16_t dd_variable_resistor_setSetPoint()
{
    return SETPOINT_RESISTANCE;
}

uint16_t dd_variable_resistor_convertAngleToResistance(uint16_t angleValue)
{
    resistanceValue = (uint16_t)(MIN_RESISTANCE + (uint32_t)(MAX_RESISTANCE - MIN_RESISTANCE) * angleValue / 180); 
    return resistanceValue;
}