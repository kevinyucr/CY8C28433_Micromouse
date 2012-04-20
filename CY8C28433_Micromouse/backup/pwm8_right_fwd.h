//*****************************************************************************
//*****************************************************************************
//  FILENAME: PWM8_Right_Fwd.h
//   Version: 2.60, Updated on 2012/3/2 at 9:15:10
//  Generated by PSoC Designer 5.2.2551
//
//  DESCRIPTION: PWM8 User Module C Language interface file
//-----------------------------------------------------------------------------
//  Copyright (c) Cypress Semiconductor 2012. All Rights Reserved.
//*****************************************************************************
//*****************************************************************************
#ifndef PWM8_Right_Fwd_INCLUDE
#define PWM8_Right_Fwd_INCLUDE

#include <m8c.h>

#pragma fastcall16 PWM8_Right_Fwd_EnableInt
#pragma fastcall16 PWM8_Right_Fwd_DisableInt
#pragma fastcall16 PWM8_Right_Fwd_Start
#pragma fastcall16 PWM8_Right_Fwd_Stop
#pragma fastcall16 PWM8_Right_Fwd_bReadCounter              // Read  DR0
#pragma fastcall16 PWM8_Right_Fwd_WritePeriod               // Write DR1
#pragma fastcall16 PWM8_Right_Fwd_bReadPulseWidth           // Read  DR2
#pragma fastcall16 PWM8_Right_Fwd_WritePulseWidth           // Write DR2

// The following symbols are deprecated.
// They may be omitted in future releases
//
#pragma fastcall16 bPWM8_Right_Fwd_ReadCounter              // Read  DR0 (Deprecated)
#pragma fastcall16 bPWM8_Right_Fwd_ReadPulseWidth           // Read  DR2 (Deprecated)


//-------------------------------------------------
// Prototypes of the PWM8_Right_Fwd API.
//-------------------------------------------------

extern void PWM8_Right_Fwd_EnableInt(void);                        // Proxy Class 1
extern void PWM8_Right_Fwd_DisableInt(void);                       // Proxy Class 1
extern void PWM8_Right_Fwd_Start(void);                            // Proxy Class 1
extern void PWM8_Right_Fwd_Stop(void);                             // Proxy Class 1
extern BYTE PWM8_Right_Fwd_bReadCounter(void);                     // Proxy Class 2
extern void PWM8_Right_Fwd_WritePeriod(BYTE bPeriod);              // Proxy Class 1
extern BYTE PWM8_Right_Fwd_bReadPulseWidth(void);                  // Proxy Class 1
extern void PWM8_Right_Fwd_WritePulseWidth(BYTE bPulseWidth);      // Proxy Class 1

// The following functions are deprecated.
// They may be omitted in future releases
//
extern BYTE bPWM8_Right_Fwd_ReadCounter(void);            // Deprecated
extern BYTE bPWM8_Right_Fwd_ReadPulseWidth(void);         // Deprecated


//--------------------------------------------------
// Constants for PWM8_Right_Fwd API's.
//--------------------------------------------------

#define PWM8_Right_Fwd_CONTROL_REG_START_BIT   ( 0x01 )
#define PWM8_Right_Fwd_INT_REG_ADDR            ( 0x0df )
#define PWM8_Right_Fwd_INT_MASK                ( 0x04 )


//--------------------------------------------------
// Constants for PWM8_Right_Fwd user defined values
//--------------------------------------------------

#define PWM8_Right_Fwd_PERIOD                  ( 0xff )
#define PWM8_Right_Fwd_PULSE_WIDTH             ( 0x00 )


//-------------------------------------------------
// Register Addresses for PWM8_Right_Fwd
//-------------------------------------------------

#pragma ioport  PWM8_Right_Fwd_COUNTER_REG: 0x048          //DR0 Count register
BYTE            PWM8_Right_Fwd_COUNTER_REG;
#pragma ioport  PWM8_Right_Fwd_PERIOD_REG:  0x049          //DR1 Period register
BYTE            PWM8_Right_Fwd_PERIOD_REG;
#pragma ioport  PWM8_Right_Fwd_COMPARE_REG: 0x04a          //DR2 Compare register
BYTE            PWM8_Right_Fwd_COMPARE_REG;
#pragma ioport  PWM8_Right_Fwd_CONTROL_REG: 0x04b          //Control register
BYTE            PWM8_Right_Fwd_CONTROL_REG;
#pragma ioport  PWM8_Right_Fwd_FUNC_REG:    0x148          //Function register
BYTE            PWM8_Right_Fwd_FUNC_REG;
#pragma ioport  PWM8_Right_Fwd_INPUT_REG:   0x149          //Input register
BYTE            PWM8_Right_Fwd_INPUT_REG;
#pragma ioport  PWM8_Right_Fwd_OUTPUT_REG:  0x14a          //Output register
BYTE            PWM8_Right_Fwd_OUTPUT_REG;
#pragma ioport  PWM8_Right_Fwd_INT_REG:       0x0df        //Interrupt Mask Register
BYTE            PWM8_Right_Fwd_INT_REG;


//-------------------------------------------------
// PWM8_Right_Fwd Macro 'Functions'
//-------------------------------------------------

#define PWM8_Right_Fwd_Start_M \
   PWM8_Right_Fwd_CONTROL_REG |=  PWM8_Right_Fwd_CONTROL_REG_START_BIT

#define PWM8_Right_Fwd_Stop_M  \
   PWM8_Right_Fwd_CONTROL_REG &= ~PWM8_Right_Fwd_CONTROL_REG_START_BIT

#define PWM8_Right_Fwd_EnableInt_M   \
   M8C_EnableIntMask(PWM8_Right_Fwd_INT_REG, PWM8_Right_Fwd_INT_MASK)

#define PWM8_Right_Fwd_DisableInt_M  \
   M8C_DisableIntMask(PWM8_Right_Fwd_INT_REG, PWM8_Right_Fwd_INT_MASK)

#endif
// end of file PWM8_Right_Fwd.h
