; Code that uploads the MSU-1 fade handler to RAM
msufadehanaddr equ	$0162	; where the fade handler will go in RAM
msufadehanbank	equ	$1f	; source bank of fade handler code

	ai16
	ldx	#msufadehan&WM ; src data addr
	ldy	#msufadehanaddr ; dest data addr
	lda	#msufadehanend-msufadehan-1 ; len of data to copy
	IFNE	FASTROM	; if your game is in FastROM, do this
	mvn	msufadehanbank+$80,$80 ; src bank -> dest bank
	ELSEIF ; if SlowROM, do this
	mvn	msufadehanbank,$00
	ENDC

; Code that fades the MSU-1 audio when the fade flag is set
msufadehan
	a8
	lda msufadeflag	; check fade flag
	beq .nofade	; if zero, don't fade
	lda curmsuvolume	; load current volume
	beq .nofade	; if zero, don't fade
	dec a	; dec volume (do twice for faster fade)
	sta curmsuvolume	; store new volume
	sta msu_volume	; set msu-1 volume
.nofade
	; if you're hooking into existing code to get to this routine
	; put the code you need to return from the hook here
	rtl	; return to NMI handler
msufadehanend

