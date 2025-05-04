#ifndef FREERTOS_TASK_SCHEDULER_H
#define FREERTOS_TASK_SCHEDULER_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "config.h"
#include "own_stdio.h"
#include "dd_h_bridge.h"
#include "dd_dc_motor.h"
#include "dd_h_bridge_wrapper.h"
#include "dd_variable_resistor.h"
#include "hysteresis.h"
#include "MedianFilter.h"
#include "MeanFilter.h"
#include "user_interface.h"



void FreeRTOS_scheduler_setup(void *pvParameters);
void controlMotorTask(void *pvParameters);

#endif // !FREERTOS_TASK_SCHEDULER_H