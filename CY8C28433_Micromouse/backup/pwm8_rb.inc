;;*****************************************************************************
;;*****************************************************************************
;;  FILENAME: PWM8_RB.inc
;;   Version: 2.60, Updated on 2012/3/2 at 9:15:10
;;  Generated by PSoC Designer 5.2.2551
;;
;;  DESCRIPTION: Assembler declarations for the PWM8 user module interface
;;-----------------------------------------------------------------------------
;;  Copyright (c) Cypress Semiconductor 2012. All Rights Reserved.
;;*****************************************************************************
;;*****************************************************************************

include "m8c.inc"


;--------------------------------------------------
; Constants for PWM8_RB API's.
;--------------------------------------------------

PWM8_RB_CONTROL_REG_START_BIT:             equ 0x01    ; Control register start bit
PWM8_RB_INT_REG:                           equ 0x0df
PWM8_RB_INT_MASK:                          equ 0x01


;--------------------------------------------------
; Constants for PWM8_RB user defined values
;--------------------------------------------------

PWM8_RB_PERIOD:                            equ 0xff
PWM8_RB_PULSE_WIDTH:                       equ 0xff


;--------------------------------------------------
; Register Address Constants for PWM8_RB
;--------------------------------------------------

PWM8_RB_COUNTER_REG:                   equ 0x40   ; DR0 Count register
PWM8_RB_PERIOD_REG:                    equ 0x41   ; DR1 Period register
PWM8_RB_COMPARE_REG:                   equ 0x42   ; DR2 Compare register
PWM8_RB_CONTROL_REG:                   equ 0x43   ; Control register
PWM8_RB_FUNC_REG:                      equ 0x40   ; Function register
PWM8_RB_INPUT_REG:                     equ 0x41   ; Input register
PWM8_RB_OUTPUT_REG:                    equ 0x42   ; Output register


;--------------------------------------------------
; PWM8_RB Macro 'Functions'
;--------------------------------------------------

   macro PWM8_RB_Start_M
   or    reg[PWM8_RB_CONTROL_REG],  PWM8_RB_CONTROL_REG_START_BIT
   endm

   macro PWM8_RB_Stop_M
   and   reg[PWM8_RB_CONTROL_REG], ~PWM8_RB_CONTROL_REG_START_BIT
   endm

   macro PWM8_RB_EnableInt_M
   M8C_EnableIntMask PWM8_RB_INT_REG, PWM8_RB_INT_MASK
   endm

   macro PWM8_RB_DisableInt_M
   M8C_DisableIntMask PWM8_RB_INT_REG, PWM8_RB_INT_MASK
   endm


; end of file PWM8_RB.inc
