//*****************************************************************************
//*****************************************************************************
//  FILENAME: SleepTimer.h
//   Version: 1.0, Updated on 2012/3/2 at 9:15:13
//  Generated by PSoC Designer 5.2.2551
//
//  DESCRIPTION: SleepTimer User Module C Language interface file
//-----------------------------------------------------------------------------
//  Copyright (c) Cypress Semiconductor 2012. All Rights Reserved.
//*****************************************************************************
//*****************************************************************************
#ifndef SleepTimer_INCLUDE
#define SleepTimer_INCLUDE

#include <m8c.h>
#define SleepTimer_TICK_CNTR_SIZE             1

#pragma fastcall16 SleepTimer_EnableInt                 //                 Proxy 1
#pragma fastcall16 SleepTimer_DisableInt                //                 Proxy 1
#pragma fastcall16 SleepTimer_Start                     //                 Proxy 1
#pragma fastcall16 SleepTimer_Stop                      //                 Proxy 1
#pragma fastcall16 SleepTimer_SetInterval               //                 Proxy 1
#pragma fastcall16 SleepTimer_SetTimer
#pragma fastcall16 SleepTimer_bGetTimer

#pragma fastcall16 SleepTimer_SyncWait                  //                 Proxy 1
#pragma fastcall16 SleepTimer_TickWait                  //                 Proxy 1

#pragma fastcall16 SleepTimer_bGetTickCntr              //                 Proxy 2


#if ( SleepTimer_TICK_CNTR_SIZE & (4|2) )
#pragma fastcall16 SleepTimer_iGetTickCntr              //                 Proxy 4
#endif

#if ( SleepTimer_TICK_CNTR_SIZE & 4 )
#pragma fastcall16 SleepTimer_lGetTickCntr              //                 Proxy 4
#endif

//-------------------------------------------------
// Prototypes of the SleepTimer API.
//-------------------------------------------------

extern void SleepTimer_EnableInt(void);
extern void SleepTimer_DisableInt(void);
extern void SleepTimer_Start(void);
extern void SleepTimer_Stop(void);
extern void SleepTimer_SetInterval(BYTE bInterval);
extern void SleepTimer_SyncWait(BYTE bTicks, BYTE bMode);
extern void SleepTimer_TickWait(BYTE bTicks);
extern void SleepTimer_SetTimer(BYTE bNewTimerValue);
extern BYTE SleepTimer_bGetTimer( void );

extern BYTE SleepTimer_bGetTickCntr(void);

#if ( SleepTimer_TICK_CNTR_SIZE & (4|2) )
extern unsigned int  SleepTimer_iGetTickCntr(void);
#define ST_INT_VALID
#endif

#if ( SleepTimer_TICK_CNTR_SIZE & 4 )
extern unsigned long * SleepTimer_lGetTickCntr(unsigned long * lptr);
#define ST_LONG_VALID
#endif

// Frequency of sleep timer interrupts
#define SleepTimer_1_HZ                      0x18
#define SleepTimer_8_HZ                      0x10
#define SleepTimer_64_HZ                     0x08
#define SleepTimer_512_HZ                    0x00

#define SleepTimer_FORCE_RELOAD              0x01
#define SleepTimer_WAIT_RELOAD               0x00
extern BYTE SleepTimer_fTick;


#endif
// end of file SleepTimer.h
