#include "user_interface.h"

extern uint16_t usersCurrentSetValue;

static int16_t commandValue = 0;

static const char *servoMotorControlCommands[CONTROL_NUMBER_OF_COMMANDS] = 
{
    "set",
    "setpoint",
    "min",
    "max",
    "help"
};

static const char *servoMotorControlDescriptions[CONTROL_NUMBER_OF_COMMANDS] = 
{
    "Set angle (0-180) - Usage: set <value>",
    "Set setpoint to current position",
    "Set min to current position",
    "Set max to current position",
    "Print help menu"
};

// Add help function prototype
static void printHelp(void);

void setServoAngle(void);
void setTheSetPointAngle(void);
void setMinAngle(void);
void setMaxAngle(void);

void (*commandHandler[])(void) = 
{
    setServoAngle,
    setTheSetPointAngle,
    setMinAngle,
    setMaxAngle,
    printHelp
};

// Initialization function
void initUserInterface(void)
{
    printHelp();
    printf("User interface initialized!\n");
}

// Help function implementation
static void printHelp(void)
{
    printf("\nAvailable commands:\n");
    for(int i = 0; i < CONTROL_NUMBER_OF_COMMANDS; i++) {
        printf("  %-10s - %s\n", 
               servoMotorControlCommands[i], 
               servoMotorControlDescriptions[i]);
    }
    printf("Type commands in format: <command> [value]\n\n");
}

uint8_t processUserCommand(void)
{
    char inputBuffer[64];
    printf("\nCommand> ");
    
    if (fgets(inputBuffer, sizeof(inputBuffer), stdin) != NULL)
    {
        char *cmd = strtok(inputBuffer, " \n");
        char *valStr = strtok(NULL, " \n");
        
        if(!cmd) return false;

        for(int i = 0; i < CONTROL_NUMBER_OF_COMMANDS; i++)
        {
            if(strcmp(cmd, servoMotorControlCommands[i]) == 0)
            {
                if(i == 0) // "set" command
                {
                    if(!valStr)
                    {
                        printf("Missing value. Usage: %s\n", 
                               servoMotorControlDescriptions[i]);
                        return false;
                    }
                    
                    commandValue = atoi(valStr);
                    
                    if(commandValue < 0 || commandValue > 180) {
                        printf("Error: Value %d is out of range (0-180)\n", commandValue);
                        return false;
                    }
                }
                else
                {
                    if(valStr)
                    {
                        printf("Invalid usage. %s\n", 
                               servoMotorControlDescriptions[i]);
                        return false;
                    }
                }
                
                commandHandler[i]();
                printf("Executed: %s\n", servoMotorControlDescriptions[i]);
                return true;
            }
        }
        
        printf("Unknown command. Valid commands: ");
        for(int i = 0; i < CONTROL_NUMBER_OF_COMMANDS; i++) {
            printf("%s ", servoMotorControlCommands[i]);
        }
        printf("\n");
        return false;
    }
    
    // Return false if no input received
    return false;
}

// Command implementations
void setServoAngle(void)
{
    usersCurrentSetValue = dd_variable_resistor_convertAngleToResistance(commandValue);
}

void setTheSetPointAngle(void)
{
    usersCurrentSetValue = dd_variable_resistor_setSetPoint();
}

void setMinAngle(void)
{
    usersCurrentSetValue = dd_variable_resistor_setMinAngle();
}

void setMaxAngle(void)
{
    usersCurrentSetValue = dd_variable_resistor_setMaxAngle();
}