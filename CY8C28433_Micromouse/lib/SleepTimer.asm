;;*****************************************************************************
;;*****************************************************************************
;;  Filename:   SleepTimer.asm
;;  Version: 1.0, Updated on 2012/3/2 at 9:15:13
;;  Generated by PSoC Designer 5.2.2551
;;
;;  DESCRIPTION:  SleepTimer User Module software implementation file for the
;;                22/24/27/29xxx families.
;;
;;
;;  NOTE: User Module APIs conform to the fastcall16 convention for marshalling
;;        arguments and observe the associated "Registers are volatile" policy.
;;        This means it is the caller's responsibility to preserve any values
;;        in the X and A registers that are still needed after the API functions
;;        returns. For Large Memory Model devices it is also the caller's 
;;        responsibility to perserve any value in the CUR_PP, IDX_PP, MVR_PP and 
;;        MVW_PP registers. Even though some of these registers may not be modified
;;        now, there is no guarantee that will remain the case in future releases.
;;-----------------------------------------------------------------------------
;;  Copyright (c) Cypress Semiconductor 2012. All Rights Reserved.
;;*****************************************************************************
;;*****************************************************************************


include "m8c.inc"
include "memory.inc"
include "SleepTimer.inc"

;-----------------------------------------------
;  Global Symbols
;-----------------------------------------------
;-------------------------------------------------------------------
;  Declare the functions global for both assembler and C compiler.
;
;  Note that there are two names for each API. First name is
;  assembler reference. Name with underscore is name reference for
;  C compiler.  Calling function in C source code does not require
;  the underscore.
;-------------------------------------------------------------------
export  SleepTimer_EnableInt
export _SleepTimer_EnableInt
export  SleepTimer_DisableInt
export _SleepTimer_DisableInt

export  SleepTimer_Start
export _SleepTimer_Start
export  SleepTimer_Stop
export _SleepTimer_Stop

export  SleepTimer_TickWait
export _SleepTimer_TickWait

export  SleepTimer_SyncWait
export _SleepTimer_SyncWait

export  SleepTimer_SetInterval
export _SleepTimer_SetInterval
	
export  SleepTimer_bGetTickCntr
export _SleepTimer_bGetTickCntr

export  SleepTimer_SetTimer
export _SleepTimer_SetTimer

export  SleepTimer_bGetTimer
export _SleepTimer_bGetTimer

IF(SleepTimer_TICK_CNTR_SIZE & (4|2))
export  SleepTimer_iGetTickCntr
export _SleepTimer_iGetTickCntr
ENDIF

IF(SleepTimer_TICK_CNTR_SIZE & 4)
export  SleepTimer_lGetTickCntr
export _SleepTimer_lGetTickCntr
ENDIF


area text (ROM,REL)

;-----------------------------------------------
;  EQUATES
;-----------------------------------------------

; Counter LSB Offset if 4 byte tick counter
IF(SleepTimer_TICK_CNTR_SIZE & 4)
ST_LSB_OFFSET:   equ  3
ENDIF

; Counter LSB Offset if 2 byte tick counter
IF(SleepTimer_TICK_CNTR_SIZE & 2)
ST_LSB_OFFSET:   equ  1
ENDIF

; Counter LSB Offset if 1 byte tick counter
IF(SleepTimer_TICK_CNTR_SIZE & 1)
ST_LSB_OFFSET:   equ  0
ENDIF


area UserModules (ROM, REL, CON)

;=============================================================================
;=============================================================================
;
;     Low-Level Commands
;
;=============================================================================
;=============================================================================

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: SleepTimer_EnableInt
;
;  DESCRIPTION:
;     Enables SleepTimer interrupts.
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:
;     none.
;
;  RETURNS:
;     none.
;
;  SIDE EFFECTS:
;     REGISTERS ARE VOLATILE: THE A AND X REGISTERS MAY BE MODIFIED!
;
;  THEORY of OPERATION OR PROCEDURE:
;
 SleepTimer_EnableInt:
_SleepTimer_EnableInt:
   RAM_PROLOGUE RAM_USE_CLASS_1
   M8C_EnableIntMask SleepTimer_INT_REG, SleepTimer_INT_MASK
   RAM_EPILOGUE RAM_USE_CLASS_1
   ret
.ENDSECTION

    
.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: SleepTimer_DisableInt
;
;  DESCRIPTION:
;     Disables the sleep timer. 
;
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:
;     none.
;
;  RETURNS:
;     none.
;
;  SIDE EFFECTS:
;     REGISTERS ARE VOLATILE: THE A AND X REGISTERS MAY BE MODIFIED!
;
;  THEORY of OPERATION OR PROCEDURE:
;
 SleepTimer_DisableInt:
_SleepTimer_DisableInt:
   RAM_PROLOGUE RAM_USE_CLASS_1
   M8C_DisableIntMask SleepTimer_INT_REG, SleepTimer_INT_MASK
   RAM_EPILOGUE RAM_USE_CLASS_1
   ret
.ENDSECTION


.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: SleepTimer_Start()
;
;  DESCRIPTION:
;     Clears all the variables.  
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:
;      none
;
;  RETURNS:
;     none.
;
;  SIDE EFFECTS;    
;    REGISTERS ARE VOLATILE: THE A AND X REGISTERS MAY BE MODIFIED!
;    IN THE LARGE MEMORY MODEL CURRENTLY ONLY THE PAGE POINTER 
;    REGISTERS LISTED BELOW ARE MODIFIED.  THIS DOES NOT GUARANTEE 
;    THAT IN FUTURE IMPLEMENTATIONS OF THIS FUNCTION OTHER PAGE POINTER 
;    REGISTERS WILL NOT BE MODIFIED.
;          
;    Page Pointer Registers Modified: 
;          CUR_PP
;
;  THEORY of OPERATION OR PROCEDURE:
;
 SleepTimer_Start:
_SleepTimer_Start:
   RAM_PROLOGUE RAM_USE_CLASS_4
   RAM_SETPAGE_CUR >SleepTimer_fTick      
   mov  A,0
   mov  [SleepTimer_fTick],A
   mov  [SleepTimer_bTimerValue],A
   mov  [SleepTimer_bCountDown],A
   mov  [SleepTimer_TickCount + ST_LSB_OFFSET],A        ; Clear TickCount[0:7]
IF(SleepTimer_TICK_CNTR_SIZE & (4|2))
   mov  [SleepTimer_TickCount + ST_LSB_OFFSET - 1],A    ; Clear TickCount[8:15]
ENDIF


IF(SleepTimer_TICK_CNTR_SIZE & 4)
   mov   [SleepTimer_TickCount + ST_LSB_OFFSET - 2],A    ; Clear TickCount[16:31]
   mov   [SleepTimer_TickCount + ST_LSB_OFFSET - 3],A    
ENDIF


   RAM_EPILOGUE RAM_USE_CLASS_4
   ret
.ENDSECTION


.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: SleepTimer_Stop
;
;  DESCRIPTION:
;   This function does nothing at this time.  It is only here as a place 
;   holder.
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:
;     none.
;
;  RETURNS:
;     none.
;
;  SIDE EFFECTS:
;     REGISTERS ARE VOLATILE: THE A AND X REGISTERS MAY BE MODIFIED!
;
;  THEORY of OPERATION OR PROCEDURE:
;
 SleepTimer_Stop:
_SleepTimer_Stop:
   RAM_PROLOGUE RAM_USE_CLASS_1
   RAM_EPILOGUE RAM_USE_CLASS_1
   ret
.ENDSECTION

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: SleepTimer_SetInterval
;
;  DESCRIPTION:
;     Sets sleep timer interval
;
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:
;     A <= Timer setting
;
;  RETURNS:
;     none.
;
;  SIDE EFFECTS:
;     REGISTERS ARE VOLATILE: THE A AND X REGISTERS MAY BE MODIFIED!
;
;  THEORY of OPERATION OR PROCEDURE:
;
 SleepTimer_SetInterval:
_SleepTimer_SetInterval:
   RAM_PROLOGUE RAM_USE_CLASS_2
   and  A,SleepTimer_CLOCK_MASK               ; Mask off invalid data
   mov  X, SP
   push A
   M8C_SetBank1
   mov  A, reg[OSC_CR0]                  ; Get current timer value
   and  A,~SleepTimer_CLOCK_MASK   ; Zero out old timer value
   or   A, [X]                           ; Set new timer values
   mov  reg[OSC_CR0],A                   ; Write it
   M8C_SetBank0
   pop  A
   RAM_EPILOGUE RAM_USE_CLASS_2
   ret
.ENDSECTION


.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: SleepTimer_TickWait(BYTE bTicks)
;
;  DESCRIPTION:
;     Wait X Ticks and return
;
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:
;     A <= Count down time
;
;  RETURNS:
;     none.
;
;  SIDE EFFECTS;    
;    REGISTERS ARE VOLATILE: THE A AND X REGISTERS MAY BE MODIFIED!
;    IN THE LARGE MEMORY MODEL CURRENTLY ONLY THE PAGE POINTER 
;    REGISTERS LISTED BELOW ARE MODIFIED.  THIS DOES NOT GUARANTEE 
;    THAT IN FUTURE IMPLEMENTATIONS OF THIS FUNCTION OTHER PAGE POINTER 
;    REGISTERS WILL NOT BE MODIFIED.
;          
;    Page Pointer Registers Modified: 
;          CUR_PP
;
;  THEORY of OPERATION OR PROCEDURE:
;
 SleepTimer_TickWait:
_SleepTimer_TickWait:
   RAM_PROLOGUE RAM_USE_CLASS_4
   RAM_SETPAGE_CUR >SleepTimer_fTick      
   mov   [SleepTimer_fTick],0x00          ; Clear tick flag

.WaitTick:
   tst   [SleepTimer_fTick],0xFF          ; Check for tick 
   jz    .WaitTick
   mov   [SleepTimer_fTick],0x00          ; Clear tick flag
   dec   A                                      ; Dec the timer variable
   jnz   .WaitTick                              ; Loop until we count down to zero

   RAM_EPILOGUE RAM_USE_CLASS_4
   ret
.ENDSECTION


.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: SleepTimer_SyncWait(BYTE bCounts, BYTE fMode)
;
;  DESCRIPTION:
;     This function resets the SyncWait timer.  If fMode = 0, the timer
;     is set to the new value then exits the function immediatly.  If fMode
;     is set to 1, the firmware waits for the timer to expire before the
;     timer is reset and and exits.
;
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:
;     A <= tCounts to wait
;     X <= fMode    fMode = 0  Just reload the value, do not wait
;                   fMode = 1  Wait for last value to count down to zero
;                              then reload.
;
;  RETURNS:
;     none.
;
;  SIDE EFFECTS;    
;    REGISTERS ARE VOLATILE: THE A AND X REGISTERS MAY BE MODIFIED!
;    IN THE LARGE MEMORY MODEL CURRENTLY ONLY THE PAGE POINTER 
;    REGISTERS LISTED BELOW ARE MODIFIED.  THIS DOES NOT GUARANTEE 
;    THAT IN FUTURE IMPLEMENTATIONS OF THIS FUNCTION OTHER PAGE POINTER 
;    REGISTERS WILL NOT BE MODIFIED.
;          
;    Page Pointer Registers Modified: 
;          CUR_PP
;
;  THEORY of OPERATION OR PROCEDURE:
;
 SleepTimer_SyncWait:
_SleepTimer_SyncWait:
   RAM_PROLOGUE RAM_USE_CLASS_4
   RAM_SETPAGE_CUR >SleepTimer_bCountDown
   swap  A,X
   AND   A,SleepTimer_FORCE_RELOAD
   jnz   .ReloadIt

.WaitLoop:
   tst   [SleepTimer_bCountDown],0xFF
   jnz   .WaitLoop


.ReloadIt:
   swap  A,X
   mov   [SleepTimer_bCountDown],A 

   RAM_EPILOGUE RAM_USE_CLASS_4
   ret
.ENDSECTION



.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: SleepTimer_bGetTickCntr
;
;  DESCRIPTION:
;     Returns the LSB of the tick Counter
;
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:
;     none
;
;  RETURNS:
;     LSB of lTickCount
;
;  SIDE EFFECTS;    
;    REGISTERS ARE VOLATILE: THE A AND X REGISTERS MAY BE MODIFIED!
;    IN THE LARGE MEMORY MODEL CURRENTLY ONLY THE PAGE POINTER 
;    REGISTERS LISTED BELOW ARE MODIFIED.  THIS DOES NOT GUARANTEE 
;    THAT IN FUTURE IMPLEMENTATIONS OF THIS FUNCTION OTHER PAGE POINTER 
;    REGISTERS WILL NOT BE MODIFIED.
;          
;    Page Pointer Registers Modified: 
;          CUR_PP
;
;  THEORY of OPERATION OR PROCEDURE:
;
 SleepTimer_bGetTickCntr:
_SleepTimer_bGetTickCntr:
   RAM_PROLOGUE RAM_USE_CLASS_4
   RAM_SETPAGE_CUR >SleepTimer_TickCount
   mov   A,[SleepTimer_TickCount + ST_LSB_OFFSET]
   RAM_EPILOGUE RAM_USE_CLASS_4
   ret
.ENDSECTION

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: SleepTimer_SetTimer
;
;  DESCRIPTION:
;     Set timer with parameter in A
;
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:
;     A => Value used to set Timer value
;
;  RETURNS:
;     None
;
;  SIDE EFFECTS;    
;    REGISTERS ARE VOLATILE: THE A AND X REGISTERS MAY BE MODIFIED!
;    IN THE LARGE MEMORY MODEL CURRENTLY ONLY THE PAGE POINTER 
;    REGISTERS LISTED BELOW ARE MODIFIED.  THIS DOES NOT GUARANTEE 
;    THAT IN FUTURE IMPLEMENTATIONS OF THIS FUNCTION OTHER PAGE POINTER 
;    REGISTERS WILL NOT BE MODIFIED.
;          
;    Page Pointer Registers Modified: 
;          CUR_PP
;
;  THEORY of OPERATION OR PROCEDURE:
;
 SleepTimer_SetTimer:
_SleepTimer_SetTimer:
   RAM_PROLOGUE RAM_USE_CLASS_4
   RAM_SETPAGE_CUR >SleepTimer_TickCount
   mov   [SleepTimer_bTimerValue],A
   RAM_EPILOGUE RAM_USE_CLASS_4
   ret
.ENDSECTION

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: SleepTimer_bGetTimer
;
;  DESCRIPTION:
;     Returns timer value in A
;
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:
;     None
;
;  RETURNS:
;     Return timer value in A
;
;  SIDE EFFECTS;    
;    REGISTERS ARE VOLATILE: THE A AND X REGISTERS MAY BE MODIFIED!
;    IN THE LARGE MEMORY MODEL CURRENTLY ONLY THE PAGE POINTER 
;    REGISTERS LISTED BELOW ARE MODIFIED.  THIS DOES NOT GUARANTEE 
;    THAT IN FUTURE IMPLEMENTATIONS OF THIS FUNCTION OTHER PAGE POINTER 
;    REGISTERS WILL NOT BE MODIFIED.
;          
;    Page Pointer Registers Modified: 
;          CUR_PP
;
;  THEORY of OPERATION OR PROCEDURE:
;
 SleepTimer_bGetTimer:
_SleepTimer_bGetTimer:
   RAM_PROLOGUE RAM_USE_CLASS_4
   RAM_SETPAGE_CUR >SleepTimer_TickCount
   mov   A,[SleepTimer_bTimerValue]
   RAM_EPILOGUE RAM_USE_CLASS_4
   ret
.ENDSECTION

IF(SleepTimer_TICK_CNTR_SIZE & (4|2))
.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: SleepTimer_iGetTickCntr
;
;  DESCRIPTION:
;     Returns the least significant 16 bits.
;
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:
;     none
;
;  RETURNS:
;     (int)TickCount in A and X  
;     X  <= MSB
;     A  <= LSB
;
;  SIDE EFFECTS;    
;    REGISTERS ARE VOLATILE: THE A AND X REGISTERS MAY BE MODIFIED!
;    IN THE LARGE MEMORY MODEL CURRENTLY ONLY THE PAGE POINTER 
;    REGISTERS LISTED BELOW ARE MODIFIED.  THIS DOES NOT GUARANTEE 
;    THAT IN FUTURE IMPLEMENTATIONS OF THIS FUNCTION OTHER PAGE POINTER 
;    REGISTERS WILL NOT BE MODIFIED.
;          
;    Page Pointer Registers Modified: 
;          CUR_PP
;
;  THEORY of OPERATION OR PROCEDURE:
;
 SleepTimer_iGetTickCntr:
_SleepTimer_iGetTickCntr:
   RAM_PROLOGUE RAM_USE_CLASS_4
   RAM_SETPAGE_CUR >SleepTimer_TickCount
   ; Disable interrupt here
   M8C_DisableIntMask SleepTimer_INT_REG, SleepTimer_INT_MASK
   mov   A,[SleepTimer_TickCount + ST_LSB_OFFSET]    ; Place LSB in A
   mov   X,[SleepTimer_TickCount + ST_LSB_OFFSET - 1]    ; Place MSB in X
   M8C_EnableIntMask SleepTimer_INT_REG, SleepTimer_INT_MASK
   RAM_EPILOGUE RAM_USE_CLASS_4
   ret
.ENDSECTION
ENDIF

IF(SleepTimer_TICK_CNTR_SIZE & 4)
.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: SleepTimer_lGetTickCntr
;
;  DESCRIPTION:
;     Returns a pointer to TickCount
;
;-----------------------------------------------------------------------------
;
;  ARGUMENTS:
;     [A:X] => Pointer to 32 bit tick counter (X=LSB, A=MSB)
;
;  RETURNS:
;     Pointer to lTickCount
;
;  SIDE EFFECTS;    
;    REGISTERS ARE VOLATILE: THE A AND X REGISTERS MAY BE MODIFIED!
;    IN THE LARGE MEMORY MODEL CURRENTLY ONLY THE PAGE POINTER 
;    REGISTERS LISTED BELOW ARE MODIFIED.  THIS DOES NOT GUARANTEE 
;    THAT IN FUTURE IMPLEMENTATIONS OF THIS FUNCTION OTHER PAGE POINTER 
;    REGISTERS WILL NOT BE MODIFIED.
;          
;    Page Pointer Registers Modified: 
;          CUR_PP
;
;  THEORY of OPERATION OR PROCEDURE:
;
 SleepTimer_lGetTickCntr:
_SleepTimer_lGetTickCntr:
   RAM_PROLOGUE RAM_USE_CLASS_4
   RAM_PROLOGUE RAM_USE_CLASS_3
   ; Disable interrupt here
   M8C_DisableIntMask SleepTimer_INT_REG, SleepTimer_INT_MASK
   RAM_SETPAGE_CUR >SleepTimer_TickCount
   RAM_SETPAGE_IDX A
   push  A
   mov   A,[SleepTimer_TickCount + 0]
   mov   [X + 0],A
   mov   A,[SleepTimer_TickCount + 1]
   mov   [X + 1],A
   mov   A,[SleepTimer_TickCount + 2]
   mov   [X + 2],A
   mov   A,[SleepTimer_TickCount + 3]
   mov   [X + 3],A
   pop   A
   
   M8C_EnableIntMask SleepTimer_INT_REG, SleepTimer_INT_MASK
   RAM_EPILOGUE RAM_USE_CLASS_4
   RAM_EPILOGUE RAM_USE_CLASS_3
   ret
.ENDSECTION
ENDIF




; End of File SleepTimer.asm
