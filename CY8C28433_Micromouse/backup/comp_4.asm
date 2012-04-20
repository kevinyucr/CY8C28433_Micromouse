;;*****************************************************************************
;;*****************************************************************************
;;  FILENAME: COMP_4.asm
;;   Version: 2.10, Updated on 2012/3/2 at 9:13:8
;;  Generated by PSoC Designer 5.2.2551
;;
;;  DESCRIPTION: COMP User Module software implementation file
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
;; Copyright (c) Cypress Semiconductor 2012. All Rights Reserved.
;;*****************************************************************************
;;*****************************************************************************

include "m8c.inc"
include "memory.inc"
include "COMP_4.inc"

;-----------------------------------------------
;  Global Symbols
;-----------------------------------------------

export  COMP_4_Start
export _COMP_4_Start
export  COMP_4_Stop
export _COMP_4_Stop
export  COMP_4_SetPower
export _COMP_4_SetPower
export  COMP_4_SetPolarity
export _COMP_4_SetPolarity
export  COMP_4_SetRef
export _COMP_4_SetRef

export  COMP_4_EnableInt
export _COMP_4_EnableInt
export  COMP_4_DisableInt
export _COMP_4_DisableInt
export  COMP_4_ClearInt
export _COMP_4_ClearInt

;-----------------------------------------------
;  Constant Definitions
;-----------------------------------------------

COMP_4_POLMASK:      equ 0x01
COMP_4_POWERMASK:    equ 0x03
COMP_4_REFMASK:      equ 0xF0
COMP_4_EXGAIN:       equ 0x01
COMP_4_GAINMASK:     equ 0xF4
COMP_4_HIGHGAINMASK: equ 0x10
COMP_4_HIGHGAIN:     equ 0x04

;-----------------------------------------------
; Variable Allocation
;-----------------------------------------------

AREA UserModules (ROM, REL)

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: COMP_4_Start
;  FUNCTION NAME: COMP_4_SetPower
;
;  DESCRIPTION:
;  Applies power setting to the module's analog blocks
;-----------------------------------------------------------------------------
;  ARGUMENTS:    
;   A  Contains the power settings 0=Off, 1=Low, 2=Med, and 3=High.
;  RETURNS:      Nothing.
;  SIDE EFFECTS: 
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.

 COMP_4_Start:
_COMP_4_Start:
 COMP_4_SetPower:
_COMP_4_SetPower:

   RAM_PROLOGUE RAM_USE_CLASS_2
   and A, COMP_4_POWERMASK                       ; mask A to protect unchanged bits
   mov X, SP                                     ; define temp store location

   push A                                        ; put power value in temp store
   mov A, reg[COMP_4_CR2]                        ; read power value
   and A, ~COMP_4_POWERMASK                      ; clear power bits in A
   or  A, [X]                                    ; combine power value with balance of reg.
   mov reg[COMP_4_CR2], A
   pop A
   RAM_EPILOGUE RAM_USE_CLASS_2
   ret
.ENDSECTION

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: COMP_4_Stop
;
;  DESCRIPTION:
;  Removes power setting to the module's analog blocks.
;-----------------------------------------------------------------------------
;  ARGUMENTS:    None.
;  RETURNS:      Nothing.
;  SIDE EFFECTS: 
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.

 COMP_4_Stop:
_COMP_4_Stop:

   RAM_PROLOGUE RAM_USE_CLASS_1
   and   reg[COMP_4_CR2], ~COMP_4_POWERMASK   ; Turn off Power to analog block
   RAM_EPILOGUE RAM_USE_CLASS_1
   ret
.ENDSECTION

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: COMP_4_SetRef
;
;  DESCRIPTION:
;    Sets comparator threshold at specified ratio between Low Limit and Vcc
;-----------------------------------------------------------------------------
;  ARGUMENTS:
;   A contains reference value.
;     Ref values shown are for example
;     1.000     f0h
;     0.937     e0h
;     ....
;     0.500     70h
;     ....
;     0.062     00h
;     0.042     14h
;     0.021     04h
;
;  RETURNS: none
;
;  SIDE EFFECTS:
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.
;
 COMP_4_SetRef:
_COMP_4_SetRef:

   RAM_PROLOGUE RAM_USE_CLASS_2
   and  A, COMP_4_GAINMASK                       ; mask A to protect unchanged bits
   mov  X, SP                                    ; define temp store location
   push A                                        ; put reference value in temp store
   mov  A, reg[COMP_4_CR0]                       ; read old CR0 value
   and  A, ~COMP_4_REFMASK                       ; clear reference bits in A
   tst  [X], COMP_4_HIGHGAIN                     ; See if High Gain bit is set
   jnz  .sethigain
   
   and  reg[COMP_4_CR3], ~COMP_4_EXGAIN          ; Clear High Gain bit.
   jmp  .setlogain
   
.sethigain:
   or   reg[COMP_4_CR3], COMP_4_EXGAIN           ; Set High Gain bit.
   and  [X], COMP_4_HIGHGAINMASK                 ; Make sure we have a valid high gain
   
.setlogain:   
   or   A, [X]                                   ; combine gain value with balance of reg.
   mov  reg[COMP_4_CR0], A                       ; move complete value back to register
   pop  A
   RAM_EPILOGUE RAM_USE_CLASS_2
   ret
.ENDSECTION

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: COMP_4_SetPolarity
;
;  DESCRIPTION:
;    Sets comparator output polarity;
;-----------------------------------------------------------------------------
;  ARGUMENTS:
;  A  Contains the polarity settings 0=Neg., 1=Pos.
;  RETURNS: none
;  SIDE EFFECTS:
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.
;
 COMP_4_SetPolarity:
_COMP_4_SetPolarity:
   
   RAM_PROLOGUE RAM_USE_CLASS_2
   and  A, COMP_4_POLMASK
   jz   .lut_nA
   mov  A, COMP_4_LUT_A
   jmp  .lut_A
.lut_nA:   
   mov  A, COMP_4_LUT_NA
.lut_A:
   mov  X, SP
   push A
   M8C_SetBank1
   mov  A, reg[COMP_4_LUT_REG]
   and  A, ~COMP_4_LUT_MASK
   or   A, [X]
   mov  reg[COMP_4_LUT_REG], A
   M8C_SetBank0
   pop  A
   RAM_EPILOGUE RAM_USE_CLASS_2
   ret
.ENDSECTION

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: COMP_4_EnableInt
;
;  DESCRIPTION:
;  Enables the Analog Column Interrupt
;-----------------------------------------------------------------------------
;  ARGUMENTS:    None.
;  RETURNS:      Nothing.
;  SIDE EFFECTS: 
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.

 COMP_4_EnableInt:
_COMP_4_EnableInt:
   RAM_PROLOGUE RAM_USE_CLASS_1
//Enable the AColumn Interrupt
   or    reg[COMP_4_INT_REG],COMP_4_INT_MASK  ;enable ACol interrupt
   RAM_EPILOGUE RAM_USE_CLASS_1
   ret
.ENDSECTION

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: COMP_4_DisableInt
;
;  DESCRIPTION:
;  Disables the Analog Column Interrupt
;-----------------------------------------------------------------------------
;  ARGUMENTS:    None.
;  RETURNS:      Nothing.
;  SIDE EFFECTS: 
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.

 COMP_4_DisableInt:
_COMP_4_DisableInt:
   RAM_PROLOGUE RAM_USE_CLASS_1
//Disable the AColumn Interrupt
   and   reg[COMP_4_INT_REG],~COMP_4_INT_MASK  ;disable ACol interrupt
   RAM_EPILOGUE RAM_USE_CLASS_1
   ret
.ENDSECTION

.SECTION
;-----------------------------------------------------------------------------
;  FUNCTION NAME: COMP_4_ClearInt
;
;  DESCRIPTION:
;  Cleares the pending Analog Column Interrupt
;-----------------------------------------------------------------------------
;  ARGUMENTS:    None.
;  RETURNS:      Nothing.
;  SIDE EFFECTS: 
;    The A and X registers may be modified by this or future implementations
;    of this function.  The same is true for all RAM page pointer registers in
;    the Large Memory Model.  When necessary, it is the calling function's
;    responsibility to perserve their values across calls to fastcall16 
;    functions.

 COMP_4_ClearInt:
_COMP_4_ClearInt:
   RAM_PROLOGUE RAM_USE_CLASS_1
//Cleare the pending AColumn Interrupt
   and   reg[COMP_4_INT_CLR_REG],~COMP_4_INT_MASK  ;clearing ACol interrupt
   RAM_EPILOGUE RAM_USE_CLASS_1
   ret
.ENDSECTION

; End of File COMP_4.asm
