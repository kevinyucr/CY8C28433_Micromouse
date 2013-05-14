#ifndef NAV_H
#define NAV_H

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "PSoCGPIOINT.h"
#include "MicromouseModules.h"

void Nav_Init(void);
void Nav_Update(void);

// Nav behaiviors
void Nav_CommandListFollower(char list[], char count);
void Nav_BasicWander1(void);
void Nav_RandomWander1(void);
void Nav_RandomWander2(void);

unsigned char Nav_GetRandomBit(void);

#endif
