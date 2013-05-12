#ifndef MOTION_H
#define MOTION_H

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "PSoCGPIOINT.h"
#include "MicromouseModules.h"

#define MOTION_BASE_VELOCITY  8    // Encoder ticks per cycle

#define MOTION_COUNT_BACKLASH 15   // encoder ticks of drivetrain backlash
//#define MOTION_COUNT_CELL     547  // encoder ticks per wall length
#define MOTION_COUNT_CELL     537  // encoder ticks per wall length
//#define MOTION_COUNT_ROT90    261  // encoder ticks per wheel to rotate in place 90 degrees
#define MOTION_COUNT_ROT90    255

#define MOTION_COMMAND_NONE    0    // Do nothing
#define MOTION_COMMAND_FWD     1    // Go forward 1 cell
#define MOTION_COMMAND_LEFT90  2    // Rotate in place 90 degrees left
#define MOTION_COMMAND_RIGHT90 4    // Rotate in place 90 degrees right

#define MOTION_COMMAND_FWDWAIT 5    // Go forward 1 cell when front is free
#define MOTION_COMMAND_FWDFOLLOW 6  // Go forward 1 cell while following wall.

// for pairing up commands
#define MOTION_APPEND(first, second) (first + (second << 4))
#define MOTION_FIRST(command)      (command & 0x0F)
#define MOTION_SECOND(command)     ((command >> 4) & 0x0F)
#define MOTION_HAS_SECOND(command) (command & 0xF0)
#define MOTION_APPEND_FWD(first)   MOTION_APPEND(first, MOTION_COMMAND_FWDFOLLOW)

#define Motion_Ready()  (motionCommandNext == MOTION_COMMAND_NONE)  // Motion module is ready to accept another command
#define Motion_Done()   (motionCommandCurrent == MOTION_COMMAND_NONE && Motion_Ready())

#define Motion_SetNextCommand(__c)  (motionCommandNext = __c)  // Set the motion module's next command

extern char motionCommandNext;
extern char motionCommandCurrent;

void Motion_Init(void);
void Motion_Update(void);

void _Motion_CommandForward(void);
void _Motion_CommandLeft90(void);
void _Motion_CommandRight90(void);
void _Motion_CommandForwardWait(void);
void _Motion_CommandForwardFollow(void);

#endif