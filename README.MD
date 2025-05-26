SNES MSU-1 Driver
=======================

This is the MSU-1 driver I wrote for Star Fox CD, cleaned up to be presentable for an open source release now that it is stable.  
  
I couldn't find much MSU-1 documentation when I started, so I hope this library helps you.  
  
Please credit me if you use this code in your software or make any derivatives of this code.  
It was a pain to write, and it would be greatly appreciated if you did!  
It's not like you have to pay me or anything. Crediting me is free.  

This code can:  
- Play MSU-1 music tracks
- Fade out MSU-1 music tracks
- Generate an MSU-1 data file, generating an include file containing address and length equates
- Stream up to 65k of data (realistically speaking, only 64k) from the .msu file given a 32 bit seek port address.
  
Please note that this was written for Argonaut Software's assembler. Modify as needed for your situation.  

Intended Usage:  
``CheckForMSU_l`` checks for the presence of the chip, ideal for preventing your software from booting without it present or to activate SHVC-SOUND/SPC700-driven BGM instead of using MSU-1 music.  

``msuplay_l`` is called by the various macros I've written, you shouldn't need to call it manually.  

``msuread_l`` is also called by macros I've prepared, you shouldn't need to manually call it.  

The fade handler should run during NMI (ideally, being uploaded and run from RAM first).  

Usage Examples:

```
	msuplay	intro,norepeat ; play and loop track 'intro'
```

```
	msufade	; trigger MSU-1 audio fade out
```

```
	msustream	$00D0,msu1data_teststring ; stream msu1data_teststring into WRAM starting at address $00D0
```

```
	jsl	CheckForMSU_l ; check for MSU-1
	lda	msupresent ; is it present
	beq	.nomsu1 ; no!
	bne	.msu1present ; yes!
.nomsu1
	jsl	nomsu1screen_l ; jump to no MSU-1 screen and loop there
.msu1present
	; continue game execution
```

## Files included and what they do
``MSUDATA.ASM`` - Source file to create an .msu MSU-1 data file and generate a data address list  
``MSUDRV.ASM`` - MSU-1 track playback routine, MSU-1 chip presence check routine.  
``MSUDRV.EXT`` - Global label definition for the previous file.  
``MSUNMI.ASM`` - Driver routines that have to do with NMI (fade routine and fade routine RAM upload code).  
``DATAMACS.INC`` - Macros used in ``MSUDATA.ASM``  
``MSUREGS.INC`` - Equates and documentation for MSU-1 registers.  
``MSUVARS.INC`` - MSU-1 driver variables.  
``MSUMACS.INC`` - MSU-1 driver macros.  
``MSUTRKS.INC`` - File for defining tracks formatted for the msuplay macro.  