; Variables the driver code uses
; Formatted for Argonaut's tools. alc means a WRAM variable, zalc means a Zeropage variable

	; is the MSU-1 present? 0 == no, 1 == yes
	alc	msupresent,1

	; set to 1 to trigger fadeout
	zalc	msufadeflag,1	; MUST BE IN ZEROPAGE!!

	; current chip volume for fade routine
	zalc	curmsuvolume,1	; MUST BE IN ZEROPAGE!!