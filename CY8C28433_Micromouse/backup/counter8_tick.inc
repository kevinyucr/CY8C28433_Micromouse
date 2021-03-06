;;*****************************************************************************
;;*****************************************************************************
;;  FILENAME: Counter8_Tick.inc
;;   Version: 2.60, Updated on 2012/3/2 at 9:13:11
;;  Generated by PSoC Designer 5.2.2551
;;
;;  DESCRIPTION: Assembler declarations for the Counter8 user module interface
;;-----------------------------------------------------------------------------
;;  Copyright (c) Cypress Semiconductor 2012. All Rights Reserved.
;;*****************************************************************************
;;*****************************************************************************

include "m8c.inc"


;--------------------------------------------------
; Constants for Counter8_Tick API's.
;--------------------------------------------------

Counter8_Tick_CONTROL_REG_START_BIT:       equ 0x01    ; Control register start bit
Counter8_Tick_INT_REG:                     equ 0x0e1
Counter8_Tick_INT_MASK:                    equ 0x01


;--------------------------------------------------
; Constants for Counter8_Tick user defined values
;--------------------------------------------------

Counter8_Tick_PERIOD:                      equ 0x00
Counter8_Tick_COMPARE_VALUE:               equ 0x00


;--------------------------------------------------
; Register Address Constants for Counter8_Tick
;--------------------------------------------------

Counter8_Tick_COUNTER_REG:             equ 0x20   ; DR0 Counter register
Counter8_Tick_PERIOD_REG:              equ 0x21   ; DR1 Period register
Counter8_Tick_COMPARE_REG:             equ 0x22   ; DR2 CompareValue register
Counter8_Tick_CONTROL_REG:             equ 0x23   ; Control register
Counter8_Tick_FUNC_REG:                equ 0x20   ; Function register
Counter8_Tick_INPUT_REG:               equ 0x21   ; Input register
Counter8_Tick_OUTPUT_REG:              equ 0x22   ; Output register


;--------------------------------------------------
; Counter8_Tick Macro 'Functions'
;--------------------------------------------------

   macro Counter8_Tick_Start_M
   or    reg[Counter8_Tick_CONTROL_REG],  Counter8_Tick_CONTROL_REG_START_BIT
   endm

   macro Counter8_Tick_Stop_M
   and   reg[Counter8_Tick_CONTROL_REG], ~Counter8_Tick_CONTROL_REG_START_BIT
   endm

   macro Counter8_Tick_EnableInt_M
   M8C_EnableIntMask Counter8_Tick_INT_REG, Counter8_Tick_INT_MASK
   endm

   macro Counter8_Tick_DisableInt_M
   M8C_DisableIntMask Counter8_Tick_INT_REG, Counter8_Tick_INT_MASK
   endm


; end of file Counter8_Tick.inc
