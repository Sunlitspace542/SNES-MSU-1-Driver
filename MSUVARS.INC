; MSUVARS.INC
; RAM allocations for variables used by the code.
; Copyright (c) 2025 Sunlit
; Released under the MIT License
;
; Please credit me if you use this code in your software or make any derivatives of this code.
; It was a pain to write, and it would be greatly appreciated if you did!
; It's not like you have to pay me or anything. Crediting me is free.

; Formatted for Argonaut's tools. alc means a WRAM variable, zalc means a Zeropage variable

	; is the MSU-1 present? 0 == no, 1 == yes
	alc	msupresent,1

	; Length of data to read out from .msu file
	alc	msu_read_len,2

	; Pointer to MSU-1 data stream destination address.
	; copied to msu_dest_zptr when msuread_l is executed.
	alc	msu_dest_ptr,2

	; set to 1 to trigger fadeout
	zalc	msufadeflag,1	; MUST BE IN ZEROPAGE!!

	; current chip volume for fade routine
	zalc	curmsuvolume,1	; MUST BE IN ZEROPAGE!!

	; Pointer to MSU-1 data stream destination address. (zeropage copy used by msuread_l)
	zalc	msu_dest_zptr,2	; MUST BE IN ZEROPAGE!!