; MSUMACS.INC
; MSU-1 driver macros.
; Copyright (c) 2025 Sunlit
; Released under the MIT License
;
; Please credit me if you use this code in your software or make any derivatives of this code.
; It was a pain to write, and it would be greatly appreciated if you did!
; It's not like you have to pay me or anything. Crediting me is free.

; Macros, written for Argonaut Software's assembler.
; Note: savemode saves the last called processor mode macro, returnmode inserts the last called processor mode macro.
; Macros are intended to be run in a8 mode unless otherwise specified.
;-------------------------------------------------------------
	; define an MSU-1 track in MSUTRKS.INC
msutrack	macro	[track,num]
bgm{track}	equ	{num}
	endm
;-------------------------------------------------------------
	; play an MSU-1 track
msuplay	macro	[track,audiostate]
	php
	pha	;save a&x
	phx

	a8i16
	lda	#audiostate_{audiostate}
	ldx	#bgm{track}
	jsl	msuplay_l

	plx	;return a&x
	pla
	plp
	endm
;-------------------------------------------------------------
	; use this macro if the former breaks stuff
	; you have to know what A/X should and will be,
	; and if any macros using savemode/returnmode are run before using this
msuplay_alt	macro	[track,audiostate]
	savemode
	pha	;save a&x
	phx

	a8i16
	lda	#audiostate_{audiostate}
	ldx	#bgm{track}
	jsl	msuplay_l

	plx	;return a&x
	pla
	returnmode
	endm
;-------------------------------------------------------------
	;Shut the MSU-1 off
msustop	macro
	stz	msu_volume
	stz	msu_control
	endm
;-------------------------------------------------------------
	;Pause MSU-1 audio
msupause	macro
	lda	#audiostate_none
	sta	msu_control
	endm
;-------------------------------------------------------------
	;Set resume point for current track, when this track plays again, it'll continue where it left off
msusetresume	macro
	LDA #audiostate_resume
	STA msu_control
	endm
;-------------------------------------------------------------
	;Resume MSU-1 audio
msuresume	macro	[audiostate]
	LDA #audiostate_{audiostate}
	STA msu_control
	endm
;-------------------------------------------------------------
	;Trigger fade out
msufade	macro
	php
	a8
	lda	#1
	sta	msufadeflag
	plp
	endm
;-------------------------------------------------------------
	;Trigger fade out
	;see msuplay_alt for notes on usage
msufade_alt	macro
	savemode
	a8
	lda	#1
	sta	msufadeflag
	returnmode
	endm
;-------------------------------------------------------------
; set MSU-1 data seek port
msu1_setseekport	macro [addr]
	lda #{addr}_byte1
	sta msu_seek
	lda #{addr}_byte2
	sta msu_seek2
	lda #{addr}_byte3
	sta msu_seek3
	lda #{addr}_byte4
	sta msu_seek4
	ENDM
;--------------------------------------------------------------
; Stream data from .MSU file
; dest = dest addr
; addr = addr of data in .msu file
; example:
;	msustream	$00D0,msu1data_teststring
msustream	macro	[dest,addr]
	pha
	phy
	savemode
	a8
	msu1_setseekport	{addr}
	a16
	lda	#{dest}
	sta	msu_dest_ptr
	lda	#{addr}len
	sta msu_read_len
	jsl	msuread_l
	returnmode
	ply
	pla
	ENDM
;--------------------------------------------------------------