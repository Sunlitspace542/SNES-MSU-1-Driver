; MSUDRV.ASM
; Main MSU-1 Driver Routines.
; Copyright (c) 2025 Sunlit
; Released under the MIT License
;
; Please credit me if you use this code in your software or make any derivatives of this code.
; It was a pain to write, and it would be greatly appreciated if you did!
; It's not like you have to pay me or anything. Crediting me is free.


	INCPUBLICS	ext\msudrv.ext

; Standard playback volume
; $FE is divisible by 2, so if you want to do a faster fade (dec 2x instead of 1x) it'll work

msu_mastervol		equ	254	; Master volume, set to 255 if using alternate fade decrement code


; set to 1 to handle missing tracks
msudebug	equ	0

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
	lda	#msu_mastervol	; Set volume
	sta	curmsuvolume
	sta	msu_volume
	pla	; Pull audiostate and start playing music
	sta	msu_control

	IFNE	msudebug
	; ERROR CHECK
	lda msu_status
	bit #status_trackmissing
	beq .donemsuplayback ; error bit set?
.msufailed
	stz	msu_volume	; Mute MSU-1 to avoid loud buzzing on hardware
.donemsuplayback
	ENDC
	rtl
;-------------------------------------------------------------
; Streams from .msu file to a RAM address.
; Can stream up to 1 memory bank's worth of data and then some (65k bytes)
; Inputs:
; MSU seek port should be set before calling
; msu_dest_zptr = 16-bit zeropage pointer to where data should be written, set before calling
; msu_read_len = len data to read out, set before calling
;
; Uses:
; Y = data destination address offset
; A = general operations
;
; Clobbers: A,Y
;
; Change DBR if needed to target destination bank

msuread_l
	ai16
	ldy #0	; initialize Y

.msureadloop
.waitbusyclear	; wait for data busy flag clear
	a8
	lda msu_status
	bmi	.waitbusyclear

	lda msu_read	; read out a byte, chip will return the current byte and automatically increment the seek port address by 1
	sta [msu_dest_zptr],y	; write to dest
	iny	; inc dest offset

	; dec len counter
	a16
	dec	msu_read_len
	lda	msu_read_len
	bne .msureadloop
	rtl
;-------------------------------------------------------------
; Detects presence of the MSU-1
; Ideally, you would run this at boot
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