	INCPUBLICS	ext\msudrv.ext

; Standard playback volume
; $FE is divisible by 2, so if you want to do a faster fade (dec 2x instead of 1x) it'll work
msuplaybackvolume	equ	$FE

; see MSUMACS.inc for usage
;-------------------------------------------------------------
; plays an MSU-1 track
; A - audiostate
; X - track to play
msuplay_l
	a8i16
	stz	msu_volume	;Shut chip off
	stz	msu_control
	stz	msufadeflag

	stx	msu_track	; Load track

; Note: some emulators do not need this loop, however the SD2SNES/FXPak Pro does
.msuaudiobusyloop
	bit	msu_status ; Is the audio busy flag set?
	bvs	.msuaudiobusyloop ; Loop until it isn't

	pha	; Save audiostate to stack
	lda	#msuplaybackvolume	; Set volume
	sta	curmsuvolume
	sta	msu_volume
	pla	; Pull audiostate and start playing music
	sta	msu_control
	rtl
;-------------------------------------------------------------
; Detects presence of the MSU-1
; Ideally you would run this at boot
CheckForMSU_l
	lda	MSU_ID	; Get MSU-1 ID register
	cmp	#$53	; MSU_ID == 'S' ?
	bne	NoMSU	; Stop checking if it's wrong
MSUFound	; Yes!
	lda	#1
	sta	msupresent ; Set chip present flag
NoMSU
	rtl
;-------------------------------------------------------------