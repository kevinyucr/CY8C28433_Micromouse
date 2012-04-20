//*****************************************************************************
//*****************************************************************************
//  FILENAME: PWM8_Right_Rev.h
//   Version: 2.60, Updated on 2012/3/2 at 9:15:10
//  Generated by PSoC Designer 5.2.2551
//
//  DESCRIPTION: PWM8 User Module C Language interface file
//-----------------------------------------------------------------------------
//  Copyright (c) Cypress Semiconductor 2012. All Rights Reserved.
//*****************************************************************************
//*****************************************************************************
#ifndef PWM8_Right_Rev_INCLUDE
#define PWM8_Right_Rev_INCLUDE

#include <m8c.h>

#pragma fastcall16 PWM8_Right_Rev_EnableInt
#pragma fastcall16 PWM8_Right_Rev_DisableInt
#pragma fastcall16 PWM8_Right_Rev_Start
#pragma fastcall16 PWM8_Right_Rev_Stop
#pragma fastcall16 PWM8_Right_Rev_bReadCounter              // Read  DR0
#pragma fastcall16 PWM8_Right_Rev_WritePeriod               // Write DR1
#pragma fastcall16 PWM8_Right_Rev_bReadPulseWidth           // Read  DR2
#pragma fastcall16 PWM8_Right_Rev_WritePulseWidth           // Write DR2

// The following symbols are deprecated.
// They may be omitted in future releases
//
#pragma fastcall16 bPWM8_Right_Rev_ReadCounter              // Read  DR0 (Deprecated)
#pragma fastcall16 bPWM8_Right_Rev_ReadPulseWidth           // Read  DR2 (Deprecated)


//-------------------------------------------------
// Prototypes of the PWM8_Right_Rev API.
//-------------------------------------------------

extern void PWM8_Right_Rev_EnableInt(void);                        // Proxy Class 1
extern void PWM8_Right_Rev_DisableInt(void);                       // Proxy Class 1
extern void PWM8_Right_Rev_Start(void);                            // Proxy Class 1
extern void PWM8_Right_Rev_Stop(void);                             // Proxy Class 1
extern BYTE PWM8_Right_Rev_bReadCounter(void);                     // Proxy Class 2
extern void PWM8_Right_Rev_WritePeriod(BYTE bPeriod);              // Proxy Class 1
extern BYTE PWM8_Right_Rev_bReadPulseWidth(void);                  // Proxy Class 1
extern void PWM8_Right_Rev_WritePulseWidth(BYTE bPulseWidth);      // Proxy Class 1

// The following functions are deprecated.
// They may be omitted in future releases
//
extern BYTE bPWM8_Right_Rev_ReadCounter(void);            // Deprecated
extern BYTE bPWM8_Right_Rev_ReadPulseWidth(void);         // Deprecated


//--------------------------------------------------
// Constants for PWM8_Right_Rev API's.
//--------------------------------------------------

#define PWM8_Right_Rev_CONTROL_REG_START_BIT   ( 0x01 )
#define PWM8_Right_Rev_INT_REG_ADDR            ( 0x0df )
#define PWM8_Right_Rev_INT_MASK                ( 0x01 )


//--------------------------------------------------
// Constants for PWM8_Right_Rev user defined values
//--------------------------------------------------

#define PWM8_Right_Rev_PERIOD                  ( 0xc8 )
#define PWM8_Right_Rev_PULSE_WIDTH             ( 0xff )


//-------------------------------------------------
// Register Addresses for PWM8_Right_Rev
//-------------------------------------------------

#pragma ioport  PWM8_Right_Rev_COUNTER_REG: 0x040          //DR0 Count register
BYTE            PWM8_Right_Rev_COUNTER_REG;
#pragma ioport  PWM8_Right_Rev_PERIOD_REG:  0x041          //DR1 Period register
BYTE            PWM8_Right_Rev_PERIOD_REG;
#pragma ioport  PWM8_Right_Rev_COMPARE_REG: 0x042          //DR2 Compare register
BYTE            PWM8_Right_Rev_COMPARE_REG;
#pragma ioport  PWM8_Right_Rev_CONTROL_REG: 0x043          //Control register
BYTE            PWM8_Right_Rev_CONTROL_REG;
#pragma ioport  PWM8_Right_Rev_FUNC_REG:    0x140          //Function register
BYTE            PWM8_Right_Rev_FUNC_REG;
#pragma ioport  PWM8_Right_Rev_INPUT_REG:   0x141          //Input register
BYTE            PWM8_Right_Rev_INPUT_REG;
#pragma ioport  PWM8_Right_Rev_OUTPUT_REG:  0x142          //Output register
BYTE            PWM8_Right_Rev_OUTPUT_REG;
#pragma ioport  PWM8_Right_Rev_INT_REG:       0x0df        //Interrupt Mask Register
BYTE            PWM8_Right_Rev_INT_REG;


//-------------------------------------------------
// PWM8_Right_Rev Macro 'Functions'
//-------------------------------------------------

#define PWM8_Right_Rev_Start_M \
   PWM8_Right_Rev_CONTROL_REG |=  PWM8_Right_Rev_CONTROL_REG_START_BIT

#define PWM8_Right_Rev_Stop_M  \
   PWM8_Right_Rev_CONTROL_REG &= ~PWM8_Right_Rev_CONTROL_REG_START_BIT

#define PWM8_Right_Rev_EnableInt_M   \
   M8C_EnableIntMask(PWM8_Right_Rev_INT_REG, PWM8_Right_Rev_INT_MASK)

#define PWM8_Right_Rev_DisableInt_M  \
   M8C_DisableIntMask(PWM8_Right_Rev_INT_REG, PWM8_Right_Rev_INT_MASK)

#endif
// end of file PWM8_Right_Rev.h
