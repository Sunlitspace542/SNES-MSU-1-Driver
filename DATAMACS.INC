; DATAMACS.INC
; Macros to assist in generating the MSU-1 data file.
; Copyright (c) 2025 Sunlit
; Released under the MIT License
;
; Please credit me if you use this code in your software or make any derivatives of this code.
; It was a pain to write, and it would be greatly appreciated if you did!
; It's not like you have to pay me or anything. Crediting me is free.

; get data length
getmsu1datalen	macro [label]
{label}len	equ	{label}len-{label} ;-1
	ENDM

; get data address and separate address bytes (also writes out length of data to the generated .inc)
getmsu1dataaddr	macro	[label]
{label}_byte1	equ	({label})&$FF
{label}_byte2	equ	(({label})>>8)&$FF
{label}_byte3	equ	(({label})>>16)&$FF
{label}_byte4	equ	(({label})>>24)&$FF

	fopen	+msudata.inc
	printf	"{label}%tequ%t%x{label} %n"
	printf	"{label}_byte1%tequ%t%x{label}_byte1 %n"
	printf	"{label}_byte2%tequ%t%x{label}_byte2 %n"
	printf	"{label}_byte3%tequ%t%x{label}_byte3 %n"
	printf	"{label}_byte4%tequ%t%x{label}_byte4 %n"
	printf	"{label}len%tequ%t%x{label}len %n"
	fclose	msudata.inc
	ENDM