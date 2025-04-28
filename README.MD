SNES MSU-1 Music Driver
=======================

This is the MSU-1 music driver I wrote for Star Fox CD, cleaned up to be presentable for an open source release now that it is stable.  
Please note that this was written for Argonaut Software's assembler. Modify as needed for your situation.  

Intended usage:  
``CheckForMSU_l`` checks for the presence of the chip, ideal for preventing your software from booting without it present or to activate SHVC-SOUND/SPC700-driven BGM instead of using MSU-1 music.  
``msuplay_l`` is called by the various macros I've written, you shouldn't need to call it manually.  
The fade handler should run during NMI (ideally, being uploaded and run from RAM first).  

## Files included and what they do
``MSUDRV.ASM`` - MSU-1 track playback routine, MSU-1 chip presence check routine.
``MSUDRV.EXT`` - Global label definition for the previous file.
``MSUNMI.ASM`` - Driver routines that have to do with NMI (fade routine and fade routine RAM upload code).
``MSUREGS.INC`` - Equates and documentation for MSU-1 registers.
``MSUVARS.INC`` - MSU-1 driver variables.
``MSUMACS.INC`` - MSU-1 driver macros.
``MSUTRKS.INC`` - File for defining tracks formatted for the msuplay macro.