#ifndef CONFIG_H
#define CONFIG_H

#define ABS(x) ((x) < 0 ? -(x) : (x))

#define BAUDRATE 115200

#define MAX_PWM_VALUE 255
#define MIN_PWM_VALUE 0

#define MAX_MOTOR_SPEED 100
#define STOP_MOTOR_SPEED 0
#define MIN_MOTOR_SPEED -100

#define SPEED_CHANGE_STEP 10

#define RESISTOR_PIN A0
#define R0 10000
#define VREF 5.0
#define ADC_RESOLUTION 1023

// median filter settings
#define WINDOW_SIZE 15


enum HBRRIDGE_PINS 
{
    H_BRIDGE_PWM_PIN = 10,
    H_BRIDGE_IN1_PIN,
    H_BRIDGE_IN2_PIN,
};

#endif // !CONFIG_H