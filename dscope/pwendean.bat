rem set C51LIB=C:\C51\LIB
rem set C51INC=C:\C51\INC
c51 pwendea1.c
pause
goto XX01
C51 SIOIRQ.C
C51 SIOPOLL.C
C51 GETLINE.C
:XX01
rem BL51 pwendea1.OBJ, SIOIRQ.OBJ RTX51TINY RAMSIZE (256)
BL51 pwendea1.OBJ, SIOPOLL.OBJ RTX51TINY RAMSIZE (256)
rem BL51 pwendea1.OBJ, SIOPOLL.OBJ RAMSIZE (256)
rem * fuer E3200:
rem ohs51 pwendea1
REM
REM DEBUG WITH DSCOPE-51
rem PAUSE
rem DS51 INIT (pwendea1.INI)
:XX00
