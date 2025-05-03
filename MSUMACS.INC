; Macros, written for Argonaut Software's assembler.
; Note: savemode saves the last called processor mode macro, return mode inserts the last called processor mode macro.
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
	;Resume MSU-1 audio
	;Audiostate can be repeat,norepeat
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