@ECHO OFF
set C51LIB=C:\C51\LIB
set C51INC=C:\C51\INC
  if not exist %1.C goto Fehler_1
C:\C51\BIN\C51 %1.C
  IF ERRORLEVEL 4 GOTO FATALERROR 
  IF ERRORLEVEL 2 GOTO ERROR
 PAUSE 
c:\C51\BIN\L51 %1.obj
 PAUSE
c:\C51\BIN\OHS51 %1
pause
rem xt %1.hex
GOTO ENDE
:Fehler_1
    ECHO Der C-Compiler kann die Datei  %1.C  nicht finden.
    ECHO Evtl. den Dateinamen OHNE Endung ( .C ) eingeben !
    GOTO ENDE
:FATALERROR
    ECHO GROBER FEHLER : Assemblierung abgebrochen
    GOTO ENDE
:ERROR
    ECHO Fehler w„hrend der Assemblierung aufgetreten
:ENDE
    ECHO  ON
