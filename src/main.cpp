#include <Arduino.h>
#include "config.h"
#include "own_stdio.h"
#include "dd_h_bridge.h"
#include "dd_dc_motor.h"
#include "dd_h_bridge_wrapper.h"
#include "dd_variable_resistor.h"
#include "hysteresis.h"
#include "freeRTOS_task_scheduler.h"



void setup() 
{
    FreeRTOS_scheduler_setup(NULL);
}

void loop() 
{

}