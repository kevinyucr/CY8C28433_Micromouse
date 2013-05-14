#ifndef ADC_H
#define ADC_H

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules
#include "PSoCGPIOINT.h"
#include "ui.h"

#define IR_Emitter_On()    (IR_Emitter_Data_ADDR  |=  IR_Emitter_MASK)
#define IR_Emitter_Off()   (IR_Emitter_Data_ADDR  &= ~IR_Emitter_MASK)
#define IR_Emitter_Powered (IR_Emitter_Data_ADDR  &   IR_Emitter_MASK)

// Name to ADC pin mappings (not bitmasks)
#define ADC_CHAN_IR_FRONT SAR10_CHS_P00
#define ADC_CHAN_IR_LEFT  SAR10_CHS_P01
#define ADC_CHAN_IR_RIGHT SAR10_CHS_P02
#define ADC_CHAN_USER     SAR10_CHS_P06

// General purpose sensor directional bitmasks
#define ADC_MASK_FRONT 0x01
#define ADC_MASK_LEFT  0x02
#define ADC_MASK_RIGHT 0x04

// Ambient light offsets
//#define ADC_OFFSET_IR_FRONT 48
//#define ADC_OFFSET_IR_LEFT  65
//#define ADC_OFFSET_IR_RIGHT 195
#define ADC_OFFSET_IR_RIGHT 230
#define ADC_OFFSET_IR_FRONT 18
#define ADC_OFFSET_IR_LEFT  50

extern unsigned int adcIRFrontDark;
extern unsigned int adcIRLeftDark;
extern unsigned int adcIRRightDark;

extern unsigned int adcIRFront;
extern unsigned int adcIRLeft;
extern unsigned int adcIRRight;

extern unsigned int adcLastUser;
extern unsigned int adcUser;

extern unsigned char adcFilteredWallState;

extern unsigned char adcGood;
extern unsigned char adcButtonPressed;

//extern unsigned int adcSideCenterDistance;
//extern unsigned int adcFrontCenterDistance;

void ADC_Init(void);
void ADC_Update(void);

#define ADC_WALL_THRESHOLD   200

#define ADC_FrontWallExists  (adcIRFront > ADC_WALL_THRESHOLD)
#define ADC_LeftWallExists   (adcIRLeft  > ADC_WALL_THRESHOLD)
#define ADC_RightWallExists  (adcIRRight > ADC_WALL_THRESHOLD)

#define ADC_FilteredFrontWallExists (adcFilteredWallState & ADC_MASK_FRONT)
#define ADC_FilteredLeftWallExists  (adcFilteredWallState & ADC_MASK_LEFT)
#define ADC_FilteredRightWallExists (adcFilteredWallState & ADC_MASK_RIGHT)

#endif