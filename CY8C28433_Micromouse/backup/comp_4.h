//*****************************************************************************
//*****************************************************************************
//  FILENAME: COMP_4.h
//   Version: 2.10, Updated on 2012/3/2 at 9:13:8
//  Generated by PSoC Designer 5.2.2551
//
//  DESCRIPTION: COMP User Module C Language interface file
//-----------------------------------------------------------------------------
// Copyright (c) Cypress Semiconductor 2012. All Rights Reserved.
//*****************************************************************************
//*****************************************************************************
#ifndef COMP_4_INCLUDE
#define COMP_4_INCLUDE

#include <m8c.h>

//-------------------------------------------------
// Defines for COMP_4 API's.
//-------------------------------------------------

#define COMP_4_LOWPOWER   1
#define COMP_4_MEDPOWER   2
#define COMP_4_HIGHPOWER  3

#define COMP_4_POL_POS    1
#define COMP_4_POL_NEG    0

#define COMP_4_REF1_000   0xf0
#define COMP_4_REF0_937   0xe0
#define COMP_4_REF0_875   0xd0
#define COMP_4_REF0_812   0xc0
#define COMP_4_REF0_750   0xb0
#define COMP_4_REF0_688   0xa0
#define COMP_4_REF0_625   0x90
#define COMP_4_REF0_562   0x80
#define COMP_4_REF0_500   0x70
#define COMP_4_REF0_437   0x60
#define COMP_4_REF0_375   0x50
#define COMP_4_REF0_312   0x40
#define COMP_4_REF0_250   0x30
#define COMP_4_REF0_188   0x20
#define COMP_4_REF0_125   0x10
#define COMP_4_REF0_062   0x00
#define COMP_4_REF0_042   0x14
#define COMP_4_REF0_021   0x04


#pragma fastcall16 COMP_4_Start			// Write CR2
#pragma fastcall16 COMP_4_Stop			// Write CR2
#pragma fastcall16 COMP_4_SetPower		// Write CR2
#pragma fastcall16 COMP_4_SetPolarity		// Write LUT control register
#pragma fastcall16 COMP_4_SetRef			// Write CR0, CR3

#pragma fastcall16 COMP_4_EnableInt
#pragma fastcall16 COMP_4_DisableInt
#pragma fastcall16 COMP_4_ClearInt

//-------------------------------------------------
// Prototypes of the COMP_4 API.
//-------------------------------------------------

extern void COMP_4_Start(BYTE bPower);
extern void COMP_4_Stop(void);
extern void COMP_4_SetPower(BYTE bPower);
extern void COMP_4_SetPolarity(BYTE bPolarity);
extern void COMP_4_SetRef(BYTE bReference);

extern void COMP_4_EnableInt(void);
extern void COMP_4_DisableInt(void);
extern void COMP_4_ClearInt(void);

//-------------------------------------------------
// Register Addresses for COMP_4
//-------------------------------------------------

#pragma ioport  COMP_4_CR0: 0x071
BYTE            COMP_4_CR0;
#pragma ioport  COMP_4_CR1: 0x072
BYTE            COMP_4_CR1;
#pragma ioport  COMP_4_CR2: 0x073
BYTE            COMP_4_CR2;
#pragma ioport  COMP_4_CR3: 0x070
BYTE            COMP_4_CR3;

#pragma ioport  COMP_4_INT_REG:     0x0e0    //Interrupt Mask Register
BYTE            COMP_4_INT_REG;
#pragma ioport  COMP_4_INT_CLR_REG: 0xda     //Interrupt Clear Register
BYTE            COMP_4_INT_CLR_REG;
#pragma ioport  COMP_4_LUT_REG:     0x67     //LUT control Register
BYTE            COMP_4_LUT_REG;

#endif
// end of file COMP_4.h
