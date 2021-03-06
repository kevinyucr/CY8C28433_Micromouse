;;*****************************************************************************
;;*****************************************************************************
;;  FILENAME: TX8_BT.inc
;;   Version: 3.50, Updated on 2013/5/19 at 10:44:45
;;  Generated by PSoC Designer 5.4.2946
;;
;;  DESCRIPTION:  Assembler declarations for the TX8 user module.
;;-----------------------------------------------------------------------------
;;  Copyright (c) Cypress Semiconductor 2013. All Rights Reserved.
;;*****************************************************************************
;;*****************************************************************************

include "m8c.inc"

;---------------------------------------------------
; Constants for TX8_BT API's
;---------------------------------------------------

;mask value for global int reg bit for TX instance
TX8_BT_bINT_MASK:        equ 08h
;TX8 interrupt address
TX8_BT_INT_REG:          equ 0e1h

; Old equate, will be removed in future release, Do not use.
bTX8_BT_INT_MASK:        equ 08h


;------------------------------------
;  Transmitter Parity masks
;------------------------------------
TX8_BT_PARITY_NONE:       equ   00h
TX8_BT_PARITY_EVEN:       equ   02h
TX8_BT_PARITY_ODD:        equ   06h

;------------------------------------
;  Transmitter Status Register masks
;------------------------------------
TX8_BT_TX_COMPLETE:        equ   20h
TX8_BT_TX_BUFFER_EMPTY:    equ   10h


TX8_BT_INT_MODE_TX_REG_EMPTY:                equ 0x00
TX8_BT_INT_MODE_TX_COMPLETE:                 equ 0x01

; Do not use! old style equates.  Will be moved
; in future versions.
TX8_PARITY_NONE:           equ   00h
TX8_PARITY_EVEN:           equ   02h
TX8_PARITY_ODD:            equ   06h
TX8_TX_COMPLETE:           equ   20h
TX8_TX_BUFFER_EMPTY:       equ   10h

;----------------------------------------------------
;  Register Address Constants for TX8_BT
;----------------------------------------------------
TX8_BT_CONTROL_REG: equ 2fh                      ; Control register
TX8_BT_TX_SHIFT_REG:    equ 2ch                  ; TX Shift Register register
TX8_BT_TX_BUFFER_REG:   equ 2dh                  ; TX Buffer Register
TX8_BT_FUNC_REG:    equ 2ch                      ; Function register
TX8_BT_INPUT_REG:   equ 2dh                      ; Input register
TX8_BT_OUTPUT_REG:  equ 2eh                      ; Output register

; end of file TX8_BT.inc
