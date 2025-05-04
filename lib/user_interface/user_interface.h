#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "config.h"
#include "own_stdio.h"
#include "dd_variable_resistor.h"

uint8_t processUserCommand(void);
void initUserInterface(void);

#endif // !USER_INTERFACE_H