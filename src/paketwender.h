#ifndef PAKETWENDER_H
#define PAKETWENDER_H
/**
 *
 *  @package   paketwender
 *  @file	   paketwender.h
 *  @brief     Header file for the application
 *             "Paketwendeanlage" 
 *  @author    Rolf Hemmerling <hemmerling@gmx.net>
 *  @version   1.00, 
 *             programming language "C",
 *             framework "RTX51-Tiny",
 *             development tool chain "Keil C51"
 *  @date      2015-01-01
 *  @copyright Apache License, Version 2.0
 *
 *  paketwender.h - Header file for the application "Paketwendeanlage"
 *
 *  Copyright 1999-2015 Rolf Hemmerling
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing,
 *  software distributed under the License is distributed on an
 *  "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 *  either express or implied.
 *  See the License for the specific language governing permissions
 *  and limitations under the License.
 *
 */

#if defined(__C51__)

/** 
 *  @def      _80537
 *  @brief    CPU ist 80515 mit einigen speziellen Funktionsregistern 
 */
#define _80537

/** 
 *  @def      USE_RTX51_TINY
 *  @brief    RTX-51 TINY nutzen 
 */
#define USE_RTX51_TINY

/** 
 *   def      DEBUG OBJECTEXTEND
 *  @brief    Pragma DEBUG OBJECTEXTEND
 *  Betrieb mit E3200 bzw. DSCOPE vorbereiten
 */
#pragma DEBUG OBJECTEXTEND CODE

/** 
 *   def      COMPACT
 *  @brief    Pragma COMPACT
 *  Reentrant definierten/deklarierten Funktionen
 *  RTX-Vollversion -> COMPACT Modell
 *  RTX-Tiny -> wird nicht unterstuetzt
 */
#pragma COMPACT

/** 
 *   def      REGISTERBANK
 *  @brief    Pragma REGISTERBANK
 *  RTX-Tiny:
 *  Verwendung der 80537 Arithmetik, non-reentrant
 *  Keine Verwendung von Mehrfach-Datenpointern
 *  Registerbank 0 fuer alle Tasks
 */
#pragma REGISTERBANK (0)
/* #pragma MOD517(NODP8) */

#else
/** 
 *  @def      bit
 *  @brief    bit
 */
#define bit int
	
/** 
 *  @def      idata
 *  @brief    idata
 */
#define idata

/** 
 *  @fn       _getkey
 *  @return   char
  *	@brief    Zeichen auf Standard-Ausgabe ausgeben 
 */
extern char _getkey(void);

#endif

/**
 *   def      TEST
 *  @brief    Wenn TEST dann "nur" Tasks zur Programmentwicklung starten
 *            (Motor-Schalten, Digital + Analog Ein/Ausgabe) 
 */
#undef TEST

/** 
 *  @def      DEBUG
 *  @brief    Zusaetzliche Text-Ausgaben 
 */
#define DEBUG

/**
 *  @def      DEBUG2
 *  @brief    Vereinbarung von Labels zum Gebrauch als Breakpoints 
 */
#define DEBUG2

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Gemeinsame "#define" fuer alle Betriebssysteme&Compiler erzeugen*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if defined(__GNUC__) && defined(MSDOS)
/* DJ GNU-C */

/** 
 *  @def      _MSDOS
 *  @brief    _MSDOS
 */
#define _MSDOS
#endif

#if defined(__BORLANDC__) && defined(__MSDOS__)
/* BORLAND-C 16-Bit */

/** 
 *  @def      _MSDOS
 *  @brief    _MSDOS
 */
#define _MSDOS
#endif

#if defined(__BORLANDC__) && defined(__TLS__)
/* BORLAND-C 32-Bit MSDOS Dos-Extender; NT */

/** 
 *  @def      _MSDOS
 *  @brief    _MSDOS
 */
#define _MSDOS

/** 
 *  @def      _NT
 *  @brief    _NT
 */
#define _NT
#endif

#if defined(__WATCOMC__) && defined(MSDOS)
/* WATCOM-C */

/** 
 *  @def _MSDOS
 */
 */
#define _MSDOS
#endif

#if defined(_MSDOS)
/** 
 *  @def      PC_PARALLEL
 *  @brief    Parallel-Drucker Interface
 */
#define PC_PARALLEL
/** 
 *  @def      HAVE_CLOCK
 *  @brief    HAVE_CLOCK
 */
#define HAVE_CLOCK
#endif

#if defined(__C51__)
/** 
 *  @def      SPEED_COMPENSATION
 *  @brief    SPEED_COMPENSATION
 */
#define SPEED_COMPENSATION 2000UL

/** 
 *   def      USE_BITACCESS
 *  @brief    *define USE_BITACCESS = Verwende BIT-Zugriffe auf Ports
 *            *undef USE_BITACCESS = Nutze Macros zum Zugriff auf Ports
 */
#undef USE_BITACCESS
//#define USE_BITACCESS
#else

/** 
 *  @def      SPEED_COMPENSATION
 *  @brief    Geschwindigkeits-Kompensation
 */
#define SPEED_COMPENSATION 0UL
#endif

#if defined(USE_RTX51_TINY)

/** 
 *   def      HAVE_WAIT
 *  @brief    wait()-Funktion des BS nutzen
 */
#undef HAVE_WAIT

/** 
 *  @def      USE_SERIAL_INT
 *  @brief    Benutze Interrupt-Routinen fuer serielle Kommunikation
 */
#define USE_SERIAL_INT

/** 
 *  @def      SELF
 *  @brief    Die Task-ID der eigenen Task
 */
#define SELF os_running_task_id()

/** 
 *  @def      reentrant
 *  @brief    Reentrant
 */
#define reentrant

/** 
 *  @def      WAIT
 *  @brief    Direkter Aufruf des BS, 
 *            da eigene Routinen ja nicht reentrant sind
 */
#define WAIT os_wait(K_IVL, 255,0);

#else

/** 
 *  @def      WAIT
 *  @brief    Bitte immer Voraussetzung pruefen, 
 *            dass das BS reentrant Routinen unterstuetzt
 */
#define WAIT MP_wait();
#endif


/** 
 *  @def      LIGHTCHECK_ANALOG
 *  @brief    *define LIGHTCHECK_ANALOG =
 *            A/D Konvertierung des Signals der Fototransistoren
 *            *undefine LIGHTCHECK_ANALOG =
 *            Digitale Konvertierung des Signals der Fototransistoren
 */
#define LIGHTCHECK_ANALOG

/** 
 *  @def      USE_CONSOLE_IO
 *  @brief    Ein / Ausgaben uber die serielle Schnittstelle
 */
#define USE_CONSOLE_IO

#if defined(USE_CONSOLE_IO)

/* Auf welches Eingabegeraet wird bei der    */
/* Kalibrierung der Lichtschranken gewartet? */
#if defined(LIGHTCHECK_ANALOG)

/** 
 *  @def WAIT_FOR_KEY
 *  DEVICE_DIGIN6, DEVICE_DIGIN6 und die Consolen-Tastatur
 *  stehen als Eingabegeraete zur Verfuegung
 */
#define WAIT_FOR_KEY

#else

/** 
 *  @def      WAIT_FOR_KEY
 *  @brief    Nur die Consolen-Tastatur steht
 *            als Eingabegeraet zur Verfuegung
 */
#define WAIT_FOR_KEY

#endif
#endif

/** 
 *  @def      DEFAULT_LIGHTED1
 *  @brief    Helligkeiten bei aktiver Lichtschranke :
 *            255 = beleuchteter FT, 0 = unbeleuchteter FT
 */
#define DEFAULT_LIGHTED1 0x0DC

/** 
 *  @def      DEFAULT_LIGHTED2
 *  @brief    Helligkeiten bei aktiver Lichtschranke :
 *            255 = beleuchteter FT, 0 = unbeleuchteter FT
 */
#define DEFAULT_LIGHTED2 0x0FF

/** 
 *  @def      DEFAULT_DISRUPTED1
 *  @brief    Helligkeiten bei unterbrochener Lichtschranke :
 *            255 = beleuchteter FT, 0 = unbeleuchteter FT
 */
#define DEFAULT_DISRUPTED1 0x0FF

/** 
 *  @def      DEFAULT_DISRUPTED2
 *  @brief    Helligkeiten bei unterbrochener Lichtschranke :
 *            255 = beleuchteter FT, 0 = unbeleuchteter FT
 */
#define DEFAULT_DISRUPTED2 0x0CD

/** 
 *  @def      KORREKTUR_FAKTOR
 *  @brief    Korrekturfaktor, um den die Helligkeitsschwelle hoeher liegt
 *            als der Helligkeitswert des unbeleuchteten Analogeingangs
 */
#define KORREKTUR_FAKTOR 1.1

/** 
 *  @def      NOTAUS
 *  @brief    Ein unbeschalteter Digital-Eingangs wird zu "0" eingelesen
 *            *define NOTAUS 1 = Notaus-Schalter ist Schalter
 *            *define NOTAUS 0 = Notaus-Schalter ist Unterbrecher
 */
#define NOTAUS 1

/** 
 *  @def      SIMULATION_HERE
 *  @brief    Simulation der Helligkeitsschwellwert-Ermittelung
 *            fuer die Lichtschranke nicht per DSCOPE, sondern
 *            "hier" im Programm
 */
#define SIMULATION_HERE
#undef SIMULATION_HERE

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Include, #define                                                */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/* Abstrakte Kennzeichnung der E/A Ports */

/** 
 *  @def      DEVICE_MOTOR1
 *  @brief    Abstrakte Kennzeichnung von "Motor 1"
 */
#define DEVICE_MOTOR1 0

/** 
 *  @def      DEVICE_MOTOR2
 *  @brief    Abstrakte Kennzeichnung von "Motor 2"
 */
#define DEVICE_MOTOR2 1

/** 
 *  @def      DEVICE_MOTOR3
 *  @brief    Abstrakte Kennzeichnung von "Motor 3"
 */
#define DEVICE_MOTOR3 2

/** 
 *  @def      DEVICE_MOTOR4
 *  @brief    Abstrakte Kennzeichnung von "Motor 4"
 */
#define DEVICE_MOTOR4 3

/** 
 *  @def      NUMBER_OF_MOTORS
 *  @brief    Anzahl der Motoren
 */
#define NUMBER_OF_MOTORS 4

/** 
 *  @def      DEVICE_DIGIN1
 *  @brief    Abstrakte Kennzeichnung des digitalen Eingabe-Ports "DIGIN1"
 */
#define DEVICE_DIGIN1 0

/** 
 *  @def      DEVICE_DIGIN2
 *  @brief    Abstrakte Kennzeichnung des digitalen Eingabe-Ports "DIGIN2"
 */
#define DEVICE_DIGIN2 1

/** 
 *  @def      DEVICE_DIGIN3
 *  @brief    Abstrakte Kennzeichnung des digitalen Eingabe-Ports "DIGIN3"
 */
#define DEVICE_DIGIN3 2

/** 
 *  @def      DEVICE_DIGIN4
 *  @brief    Abstrakte Kennzeichnung des digitalen Eingabe-Ports "DIGIN4"
 */
#define DEVICE_DIGIN4 3

/** 
 *  @def      DEVICE_DIGIN5
 *  @brief    Abstrakte Kennzeichnung des digitalen Eingabe-Ports "DIGIN5"
 */
#define DEVICE_DIGIN5 4

/** 
 *  @def      DEVICE_DIGIN6
 *  @brief    Abstrakte Kennzeichnung des digitalen Eingabe-Ports "DIGIN6"
 */
#define DEVICE_DIGIN6 5

/** 
 *  @def      DEVICE_DIGIN7
 *  @brief    Abstrakte Kennzeichnung des digitalen Eingabe-Ports "DIGIN7"
 */
#define DEVICE_DIGIN7 6

/** 
 *  @def      DEVICE_DIGIN8
 *  @brief    Abstrakte Kennzeichnung des digitalen Eingabe-Ports "DIGIN8"
 */
#define DEVICE_DIGIN8 7

/** 
 *  @def      NUMBER_OF_DIGINS
 *  @brief    Anzahl der digitalen Eingabe-Ports
 */
#define NUMBER_OF_DIGINS 8

/** 
 *  @def      DEVICE_ANIN1
 *  @brief    Abstrakte Kennzeichnung des analogen Eingabe-Ports "DEVICE_ANIN1"
 */
#define DEVICE_ANIN1 0

/** 
 *  @def      DEVICE_ANIN2
 *  @brief    Abstrakte Kennzeichnung des analogen Eingabe-Ports "DEVICE_ANIN2"
 */
#define DEVICE_ANIN2 1

/** 
 *  @def      DEVICE_ANIN3
 *  @brief    Abstrakte Kennzeichnung des analogen Eingabe-Ports "DEVICE_ANIN3"
 *            Beim FT-Interface: nicht vorhanden
 */
#define DEVICE_ANIN3 2 

/** 
 *  @def      DEVICE_ANIN4
 *  @brief    Abstrakte Kennzeichnung des analogen Eingabe-Ports "DEVICE_ANIN4"
 *            Beim FT-Interface: nicht vorhanden
 */
#define DEVICE_ANIN4 3 

/** 
 *  @def      DEVICE_ANIN5
 *  @brief    Abstrakte Kennzeichnung des analogen Eingabe-Ports "DEVICE_ANIN5"
 *            Beim _80537, Verpackungsanlage: unbeschaltet
 */
#define DEVICE_ANIN5 4 

/** 
 *  @def      DEVICE_ANIN6
 *  @brief    Abstrakte Kennzeichnung des analogen Eingabe-Ports "DEVICE_ANIN6"
 *            Beim _80537, Verpackungsanlage: unbeschaltet
 */
#define DEVICE_ANIN6 5 

/** 
 *  @def      DEVICE_ANIN7
 *  @brief    Abstrakte Kennzeichnung des analogen Eingabe-Ports "DEVICE_ANIN7"
 *            Beim _80537, Verpackungsanlage: unbeschaltet
 */
#define DEVICE_ANIN7 6 

/** 
 *  @def      DEVICE_ANIN8
 *  @brief    Abstrakte Kennzeichnung des analogen Eingabe-Ports "DEVICE_ANIN8"
 *            Beim _80537, Verpackungsanlage: unbeschaltet
 */
#define DEVICE_ANIN8 7 

/** 
 *  @def      NUMBER_OF_ANINS
 *  @brief    Anzahl der analogen Eingabe-Ports
 */
#define NUMBER_OF_ANINS 2

/* Abstrakte Kennzeichnung der Semaphoren */

/** 
 *  @def      SEMA_ADCONV
 *  @brief    Abstrakte Kennzeichnung der Semaphore
 */
#define SEMA_ADCONV 0

/** 
 *  @def      SEMA_V1
 *  @brief    Abstrakte Kennzeichnung der Semaphore
 */
#define SEMA_V1 1

/** 
 *  @def      SEMA_V2
 *  @brief    Abstrakte Kennzeichnung der Semaphore
 */
#define SEMA_V2 2

/* Abstrakte Kennzeichnung der Motorbefehle */

/** 
 *  @def      OFF
 *  @brief    OFF
 */
#define OFF 0

/** 
 *  @def      ON
 *  @brief    ON
 */
#define ON 1

/** 
 *  @def      RECHTS
 *  @brief    RECHTS
 */
#define RECHTS 1

/** 
 *  @def      LINKS
 *  @brief    LINKS
 */
#define LINKS 2

/* Abstrakte Kennzeichnung der Lichtschranken (Fototransistoren) */

/** 
 *  @def      LICHTSCHRANKE1
 *  @brief    Fototransistor waagerecht am Transportband
 */
#define LICHTSCHRANKE1 0

/** 
 *  @def      LICHTSCHRANKE2
 *  @brief    Fototransistor der Reflexlichtschranke
 */ 
#define LICHTSCHRANKE2 1

/* 1. Feldindex von MV_anin_value: */

/** 
 *  @def      UNLIGHTED
 *  @brief    Wert "unbeleuchtet" von MV_anin_value
 */
#define UNLIGHTED 0

/** 
 *  @def      LIGHTED
 *  @brief    Wert "beleuchtet" von MV_anin_value
 */ 
#define LIGHTED   1

/** 
 *  @def      DISRUPTED
 *  @brief    Wert "unterbrochen" von MV_anin_value
 */
#define DISRUPTED 2

/** 
 *  @def      THRESHOLD
 *  @brief    Wert "Schwellwert" von MV_anin_value
 */ 
#define THRESHOLD 3

/** 
 *  @def      DEFAULT1
 *  @brief    Wert "Default1" von MV_anin_value
 */
#define DEFAULT1  4

/** 
 *  @def      DEFAULT2
 *  @brief    Wert "Default2" von MV_anin_value
 */
#define DEFAULT2  5


#if defined(_80537)

#include <reg515.h>

/** 
 *  @def      S0CON
 *  @brief    S0CON
 */
#define S0CON SCON

/** 
 *  @def      ADCON0
 *  @brief    ADCON0
 */
#define ADCON0 ADCON

#include <INTRINS.H>

#if defined(USE_RTX51_TINY)
/* RTX-51 tiny functions & defines   */
#include <rtx51tny.h> 

/** 
 *  @def      INIT
 *  @brief    Task-Nummer des Tasks: init
 */
#define INIT        0 

/** 
 *  @def      SCHIEBER
 *  @brief    Task-Nummer des Tasks: Schieber
 */
#define SCHIEBER    1


/** 
 *  @def      WENDEBAND
 *  @brief    Task-Nummer des Tasks: Wendeband
 */
#define WENDEBAND   2

/** 
 *  @def      FOERDERBAND
 *  @brief    Task-Nummer des Tasks: Foerderband
 */
#define FOERDERBAND 3 

/** 
 *  @def      LICHT
 *  @brief    Task-Nummer des Tasks: Licht
 */
#define LICHT       4

/** 
 *  @def      BLINKLICHT
 *  @brief    Task-Nummer des Tasks: Blinklicht
 */
#define BLINKLICHT  5
#endif

/* Hardwareanschluss */

/**
 *  @var      MOTOR1_0
 *  @brief    Motor 
 *            M1 - Schieber-Antrieb
 */
sbit MOTOR1_0 = P5^0; 
/**
 *  @var      MOTOR1_1
 *  @brief    Motor 
 *            M1 - Schieber-Antrieb
 */
sbit MOTOR1_1 = P5^1;

/**
 *  @var      MOTOR2_0
 *  @brief    Motor 
 *            M2 - Antrieb der Wendestation
 */
sbit MOTOR2_0 = P5^2;
/**
 *  @var      MOTOR2_1
 *  @brief    Motor 
 *            M2 - Antrieb der Wendestation
 */
sbit MOTOR2_1 = P5^3;

/**
 *  @var      MOTOR3_0
 *  @brief    Motor 
 *            M3 - Antrieb des Transportbandes
 */
sbit MOTOR3_0 = P5^4; 
/**
 *  @var      MOTOR3_1
 *  @brief    Motor 
 *            M3 - Antrieb des Transportbandes
 */
sbit MOTOR3_1 = P5^5;

/**
 *  @var      MOTOR4_0
 *  @brief    Motor 
 *            M4 - Linsenlampen von beiden Lichtschranken
 */
sbit MOTOR4_0 = P5^6;
/**
 *  @var      MOTOR4_1
 *  @brief    Motor 
 *            M4 - Linsenlampen von beiden Lichtschranken
 */
sbit MOTOR4_1 = P5^7;

/* Digital-Eingaenge */
/**
 *  @var      DIGINPUT1
 *  @brief    E1 - Schieber-Endstellung (Paket auswerfen)
 */
sbit DIGINPUT1 = P4^DEVICE_DIGIN1;

/**
 *  @var      DIGINPUT2
 *  @brief    E2 - Schieber-Endstellung (Transportband frei) 
 */
sbit DIGINPUT2 = P4^DEVICE_DIGIN2;

/**
 *  @var      DIGINPUT3
 *  @brief    E3 - Impulsscheibe am Transportband-Antrieb 
 */
sbit DIGINPUT3 = P4^DEVICE_DIGIN3; 

/**
 *  @var      DIGINPUT4
 *  @brief    E4 - Ausloesekontakt fuer Rutsche 
 */
sbit DIGINPUT4 = P4^DEVICE_DIGIN4; 

/**
 *  @var      DIGINPUT5
 *  @brief    E5 - Taster an der Wendestation 
 */
sbit DIGINPUT5 = P4^DEVICE_DIGIN5; 

/**
 *  @var      DIGINPUT6
 *  @brief    E6 - Opt1:Fototransistor waagerecht am Transportband 
 */
sbit DIGINPUT6 = P4^DEVICE_DIGIN6; 

/**
 *  @var      DIGINPUT7
 *  @brief    E7 - Opt1:Fototransistor der Reflexlichtschranke
 *            Opt3:Operator-Taste (Lichtschranken-Einrichtung 
 */
sbit DIGINPUT7 = P4^DEVICE_DIGIN7; 

/**
 *  @var      DIGINPUT8
 *  @brief    E8 - Notaus 
 */
sbit DIGINPUT8 = P4^DEVICE_DIGIN8;

/* Analog-Eingaenge */
/* Opt2: An0 Fototransistor waagerecht am Transportband */
/* Opt2: An1 Fototransistor der Reflexlichtschranke */

#endif

#if defined(_MSDOS)

/** 
 *  @def      BITCOUNT
 *  @brief    *define BITCOUNT 8  fuer normales Interface
 *            *define BITCOUNT 16 fuer 2 gekoppelte Interfaces 
 */
#define BITCOUNT 8

/* FT-Interface Kommandos */

/** 
 *  @def      FT_XDATA
 *  @brief    FT-Interface Kommandos
 */
#define FT_XDATA      0x30                           

/** 
 *  @def      FT_LOAD_IN
 *  @brief    FT-Interface Kommandos
 */
#define FT_LOAD_IN    0x02

/** 
 *  @def      FT_DATA_OUT
 *  @brief    FT-Interface Kommandos
 */
#define FT_DATA_OUT   0x04

/** 
 *  @def      FT_SET_CLOCK
 *  @brief    FT-Interface Kommandos
 */
#define FT_SET_CLOCK  0x08

/** 
 *  @def      FT_LOAD_OUT
 *  @brief    FT-Interface Kommandos
 */
#define FT_LOAD_OUT   0x09   
                                      
/** 
 *  @def      ANINPUT_X
 *  @brief    Analog-Eingabe X
 */
#define ANINPUT_X   1

/** 
 *  @def      ANINPUT_Y
 *  @brief    Analog-Eingabe Y
 */
#define ANINPUT_Y   2

/** 
 *  @def      PDATA
 *  @brief    PDATA
 */
#define PDATA    0x090

/** 
 *  @def      PMASKE
 *  @brief    PMASKE
 */
#define PMASKE   0x010 
     
/** 
 *  @def      MOTOR1
 *  @brief    MOTOR1: Schieber-Antrieb
 */		 
#define MOTOR1 0x00003ul

/** 
 *  @def      MOTOR2
 *  @brief    MOTOR2: Antrieb der Wendestation
 */		 
#define MOTOR2 0x0000Cul

/** 
 *  @def      MOTOR3
 *  @brief    MOTOR3: Antrieb des Transportbandes
 */		 
#define MOTOR3 0x00030ul

/** 
 *  @def      MOTOR4
 *  @brief    MOTOR4: Linsenlampen von beiden Lichtschranken
 */		 
#define MOTOR4 0x000C0ul

#if BITCOUNT==16
/** 
 *  @def      MOTOR5
 *  @brief    MOTOR5: Ungenutzt
 */		 
# define MOTOR5 0x00300ul

/** 
 *  @def      MOTOR6
 *  @brief    MOTOR6: Ungenutzt
 */		 
# define MOTOR6 0x00C00ul

/** 
 *  @def      MOTOR7
 *  @brief    MOTOR7: Ungenutzt
 */		 
# define MOTOR7 0x03000ul

/** 
 *  @def      MOTOR8
 *  @brief    MOTOR8: Ungenutzt
 */		 
# define MOTOR8 0x0C000ul
#endif                      
     
/** 
 *  @def      DIGINPUT1
 *  @brief    Schieber-Eindstellung (Paket auswerfen)
 */		 
#define DIGINPUT1       1ul 

/** 
 *  @def      DIGINPUT2
 *  @brief    Schieber-Endstellung (Transportband frei)
 */		 
#define DIGINPUT2       2ul 

/** 
 *  @def      DIGINPUT3
 *  @brief    Impulsscheibe am Transportband-Antrieb
 */		 
#define DIGINPUT3       4ul

/** 
 *  @def      DIGINPUT4
 *  @brief    Ausloesekontakt fuer Rutsche
 */		 
#define DIGINPUT4       8ul

/** 
 *  @def      DIGINPUT5
 *  @brief    Taster an der Wendestation
 */		 
#define DIGINPUT5      16ul

/** 
 *  @def      DIGINPUT6
 *  @brief    Opt1:Fototransistor waagerecht am Transportband
 */		 
#define DIGINPUT6      32ul 

/** 
 *  @def      DIGINPUT7
 *  @brief    Opt1:Fototransistor der Reflexlichtschranke
 */		 
#define DIGINPUT7      64ul

/** 
 *  @def      DIGINPUT8
 *  @brief    Ungenutzt
 */		 
#define DIGINPUT8     128ul

#if BITCOUNT==16
/** 
 *  @def      DIGINPUT9
 *  @brief    Ungenutzt
 */		 
#define DIGINPUT9     256ul

/** 
 *  @def      DIGINPUT10
 *  @brief    Ungenutzt
 */		 
#define DIGINPUT10    512ul

/** 
 *  @def      DIGINPUT11
 *  @brief    Ungenutzt
 */		 
#define DIGINPUT11   1024ul

/** 
 *  @def      DIGINPUT12
 *  @brief    Ungenutzt
 */		 
#define DIGINPUT12   2048ul

/** 
 *  @def      DIGINPUT13
 *  @brief    Ungenutzt
 */		 
#define DIGINPUT13   4096ul

/** 
 *  @def      DIGINPUT14
 *  @brief    Ungenutzt
 */		 
#define DIGINPUT14   8192ul

/** 
 *  @def      DIGINPUT15
 *  @brief    Ungenutzt
 */		 
#define DIGINPUT15  16384ul

/** 
 *  @def      DIGINPUT16
 *  @brief    Ungenutzt
 */		 
#define DIGINPUT16  32768ul
#endif

/** 
 *  @def      ANINPUTX
 *  @brief    Opt2: An0 Fototransistor waagerecht am Transportband
 */		 
#define ANINPUTX 0ul

/** 
 *  @def      ANINPUTY
 *  @brief    Opt2: An1 Fototransistor der Reflexlichtschranke
 */		 
#define ANINPUTY 1ul

/** 
 *  @def      EIN
 *  @brief    EIN
 */		 
#define EIN    0x05555ul

/** 
 *  @def      AUS
 *  @brief    AUS
 */		 
#define AUS    0x0FFFFul

/** 
 *  @def      RECHTS
 *  @brief    RECHTS
 */		 
#define RECHTS 0x05555ul

/** 
 *  @def      LINKS
 *  @brief    LINKS
 */		 
#define LINKS  0x0AAAAul  

#endif

#if defined (USE_BITACCESS)
/** 
 *  @def      CMD_DIGIN1
 *  @brief    Kommando CMD_DIGIN1
 */		 
#define CMD_DIGIN1 DIGINPUT1

/** 
 *  @def      CMD_DIGIN2
 *  @brief    Kommando CMD_DIGIN2
 */		 
#define CMD_DIGIN2 DIGINPUT2

/** 
 *  @def      CMD_DIGIN3
 *  @brief    Kommando CMD_DIGIN3
 */		 
#define CMD_DIGIN3 DIGINPUT3

/** 
 *  @def      CMD_DIGIN4
 *  @brief    Kommando CMD_DIGIN4
 */		 
#define CMD_DIGIN4 DIGINPUT4

/** 
 *  @def      CMD_DIGIN5
 *  @brief    Kommando CMD_DIGIN5
 */		 
#define CMD_DIGIN5 DIGINPUT5

/** 
 *  @def      CMD_DIGIN6
 *  @brief    Kommando CMD_DIGIN6
 */		 
#define CMD_DIGIN6 DIGINPUT6

/** 
 *  @def      CMD_DIGIN7
 *  @brief    Kommando CMD_DIGIN7
 */		 
#define CMD_DIGIN7 DIGINPUT7

/** 
 *  @def      CMD_DIGIN8
 *  @brief    Kommando CMD_DIGIN8
 */		 
#define CMD_DIGIN8 DIGINPUT8

/** 
 *  @def      CMD_STATE_OF_REST1
 *  @brief    Kommando CMD_STATE_OF_REST1
 */
#define CMD_STATE_OF_REST1 STATE_OF_REST1

/** 
 *  @def      CMD_STATE_OF_REST2
 *  @brief    Kommando CMD_STATE_OF_REST2
 */
#define CMD_STATE_OF_REST2 STATE_OF_REST2

/** 
 *  @def      CMD_STATE_OF_REST3
 *  @brief    Kommando CMD_STATE_OF_REST3
 */
#define CMD_STATE_OF_REST3 STATE_OF_REST3

/** 
 *  @def      CMD_STATE_OF_REST4
 *  @brief    Kommando CMD_STATE_OF_REST4
 */
#define CMD_STATE_OF_REST4 STATE_OF_REST4

/** 
 *  @def      CMD_STATE_OF_REST5
 *  @brief    Kommando CMD_STATE_OF_REST5
 */
#define CMD_STATE_OF_REST5 STATE_OF_REST5

/** 
 *  @def      CMD_STATE_OF_REST6
 *  @brief    Kommando CMD_STATE_OF_REST6
 */
#define CMD_STATE_OF_REST6 STATE_OF_REST6

/** 
 *  @def      CMD_STATE_OF_REST7
 *  @brief    Kommando CMD_STATE_OF_REST7
 */
#define CMD_STATE_OF_REST7 STATE_OF_REST7

/** 
 *  @def      CMD_STATE_OF_REST8
 *  @brief    Kommando CMD_STATE_OF_REST8
 */
#define CMD_STATE_OF_REST8 STATE_OF_REST8
#else

/** 
 *  @def      CMD_DIGIN1
 *  @brief    Kommando CMD_DIGIN1
 */		 
#define CMD_DIGIN1 DEVICE_DIGIN1

/** 
 *  @def      CMD_DIGIN2
 *  @brief    Kommando CMD_DIGIN2
 */		 
#define CMD_DIGIN2 DEVICE_DIGIN2

/** 
 *  @def      CMD_DIGIN3
 *  @brief    Kommando CMD_DIGIN3
 */		 
#define CMD_DIGIN3 DEVICE_DIGIN3

/** 
 *  @def      CMD_DIGIN4
 *  @brief    Kommando CMD_DIGIN4
 */		 
#define CMD_DIGIN4 DEVICE_DIGIN4

/** 
 *  @def      CMD_DIGIN5
 *  @brief    Kommando CMD_DIGIN5
 */		 
#define CMD_DIGIN5 DEVICE_DIGIN5

/** 
 *  @def      CMD_DIGIN6
 *  @brief    Kommando CMD_DIGIN6
 */		 
#define CMD_DIGIN6 DEVICE_DIGIN6

/** 
 *  @def      CMD_DIGIN7
 *  @brief    Kommando CMD_DIGIN7
 */		 
#define CMD_DIGIN7 DEVICE_DIGIN7

/** 
 *  @def      CMD_DIGIN8
 *  @brief    Kommando CMD_DIGIN8
 */		 
#define CMD_DIGIN8 DEVICE_DIGIN8

/** 
 *  @def      CMD_STATE_OF_REST1
 *  @brief    Kommando CMD_STATE_OF_REST1
 */
#define CMD_STATE_OF_REST1 DEVICE_DIGIN1

/** 
 *  @def      CMD_STATE_OF_REST2
 *  @brief    Kommando CMD_STATE_OF_REST2
 */
#define CMD_STATE_OF_REST2 DEVICE_DIGIN2

/** 
 *  @def      CMD_STATE_OF_REST3
 *  @brief    Kommando CMD_STATE_OF_REST3
 */
#define CMD_STATE_OF_REST3 DEVICE_DIGIN3

/** 
 *  @def      CMD_STATE_OF_REST4
 *  @brief    Kommando CMD_STATE_OF_REST4
 */
#define CMD_STATE_OF_REST4 DEVICE_DIGIN4

/** 
 *  @def      CMD_STATE_OF_REST5
 *  @brief    Kommando CMD_STATE_OF_REST5
 */
#define CMD_STATE_OF_REST5 DEVICE_DIGIN5

/** 
 *  @def      CMD_STATE_OF_REST6
 *  @brief    Kommando CMD_STATE_OF_REST6
 */
#define CMD_STATE_OF_REST6 DEVICE_DIGIN6

/** 
 *  @def      CMD_STATE_OF_REST7
 *  @brief    Kommando CMD_STATE_OF_REST7
 */
#define CMD_STATE_OF_REST7 DEVICE_DIGIN7

/** 
 *  @def      CMD_STATE_OF_REST8
 *  @brief    Kommando CMD_STATE_OF_REST8
 */
#define CMD_STATE_OF_REST8 DEVICE_DIGIN8
#endif

#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Macros                                                          */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/* Wartezeit nach action notwendig z.B. in MP_p2wait3(), damit     */
/* sich Signal aendern kann und auf die Wiederherstellung des      */
/* Signals gewartet werden kann (vorher = nachher = 1)             */
#if defined(PC_PARALLEL)
/** 
 *  @def      CONTINOUS_DATA_FLOW
 *  @brief    Ueberwachung des Datenstroms vom Computer. Sperren der
 *  	        Ausgaenge 0.5 sec nach Ausbleiben der Datensignale.
 *            Die Signale bleiben jedoch gespeichert.
 */
#define CONTINOUS_DATA_FLOW(action) do { action; WAIT;}
#else
/** 
 *  @def      CONTINOUS_DATA_FLOW
 *  @brief    Keine Ueberwachung des Datenstroms
 */
#define CONTINOUS_DATA_FLOW(action) action; WAIT;
#endif

#if defined(_80537)
#if defined (USE_BITACCESS)

/** 
 *  @def      LOG_DIGITAL_INPUT
 *  @brief    LOG_DIGITAL_INPUT
 */
#define LOG_DIGITAL_INPUT(device1,device2) !(device1 ^ device2)
    
/** 
 *  @def      RAW_DIGITAL_INPUT
 *  @brief    RAW_DIGITAL_INPUT
 */
#define RAW_DIGITAL_INPUT(device) !device

/** 
 *  @def      STATE_OF_REST_DIGITAL_INPUT
 *  @brief    STATE_OF_REST_DIGITAL_INPUT
 */
#define STATE_OF_REST_DIGITAL_INPUT(device) device

/** 
 *  @def      MOTOR_CONTROL
 *  @brief    MOTOR_CONTROL
 */
#define MOTOR_CONTROL(device1, device2, command) device1 = (command >> 1);device2 = (command & 0x01)
#else
/** 
 *  @def      LOG_DIGITAL_INPUT
 *  @brief    Nur aufgrund Struktur der erzeugten Assembler-Befehle
 *            kann hier auf eine zeitweilige Interrupt-Abschaltung
 *            verzichtet werden (ANL,ORL) !
 *            Achtung, P4 ist vom Typ "unsigned char"
 *            => explizite (int) Umwandlung notwendig
 */
#define LOG_DIGITAL_INPUT(device) !((((int)P4) >> device) & 0x01) ^ ((MV_digin_state_of_rest >> device) & 0x01)

/** 
 *  @def      RAW_DIGITAL_INPUT
 *  @brief    Nur aufgrund Struktur der erzeugten Assembler-Befehle
 *            kann hier auf eine zeitweilige Interrupt-Abschaltung
 *            verzichtet werden (ANL,ORL) !
 *            Achtung, P4 ist vom Typ "unsigned char"
 *            => explizite (int) Umwandlung notwendig
 */
#define RAW_DIGITAL_INPUT(device) !((((int)P4) >> device) & 0x01)

/** 
 *  @def      STATE_OF_REST_DIGITAL_INPUT
 *  @brief    STATE_OF_REST_DIGITAL_INPUT
 */
#define STATE_OF_REST_DIGITAL_INPUT(device) (MV_digin_state_of_rest >> device) & 0x01

/** 
 *  @def      MOTOR_CONTROL
 *  @brief    MOTOR_CONTROL
 */
#define MOTOR_CONTROL(device, command) P5 &= ~(0x03 << (device*2));P5 |= (command << (device*2))

/* Reentrant definierte/deklarierte Funktionen  */
/* RTX-Vollversion -> COMPACT Modell            */
/* RTX-Tiny -> wird nicht unterstuetzt          */

#endif
#else
/** 
 *  @def      LOG_DIGITAL_INPUT
 *  @brief    LOG_DIGITAL_INPUT
 */
#define LOG_DIGITAL_INPUT(device) (MP_digin(device)) ^ ((MV_digin_state_of_rest >> device) & 0x01)

/** 
 *  @def      RAW_DIGITAL_INPUT
 *  @brief    RAW_DIGITAL_INPUT
 */
#define RAW_DIGITAL_INPUT(device) MP_digin(device)

/** 
 *  @def      STATE_OF_REST_DIGITAL_INPUT
 *  @brief    STATE_OF_REST_DIGITAL_INPUT
 */
#define STATE_OF_REST_DIGITAL_INPUT(device) (MV_digin_state_of_rest >> device) & 0x01

/** 
 *  @def      MOTOR_CONTROL
 *  @brief    MOTOR_CONTROL
 */
#define MOTOR_CONTROL(device, command) MP_motor(device,command) 

/** 
 *  @def      reentrant
 *  @brief    reentrant
 *  Schluesselwort fuer MSDOS ungueltig
 */
#define reentrant

/** 
 *  @def      bdata
 *  @brief    bdata
 *  Schluesselwort fuer MSDOS ungueltig
 */
#define bdata
#endif

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Funktions-Definitionen                                          */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** 
 *  @fn       MP_sleep
 *	@brief    Zeitverzoegerung 
 */
static void MP_sleep(
#if defined(HAVE_CLOCK)
                      clock_t
#else
#if defined(HAVE_WAIT)
                      unsigned int
#else
                      unsigned long
#endif
#endif
                              VV_wait) reentrant;
											
/** 
 *  @fn       MP_wait
 *	@brief    Feste Wartezeit  
 */
static void MP_wait(void) 

#ifndef DOXYGEN
                          reentrant
#endif
;

/** 
 *  @fn       MP_init
 *  @brief    Programm-Initialisierung 
 */
static void MP_init(void);
#if defined(USE_RTX51_TINY)

/** 
 *  @fn       MP_notaus_abschaltung
 *  @param    IV_meldung
 *	@brief    NOTAUS-Abschaltung der Anlage 
 */
static void MP_notaus_abschaltung(char * IV_meldung);
#else

/** 
 *  @fn       MP_motor(int VV_device,int VV_command)
 *  @param    VV_device
 *  @param    VV_command
 *	@brief    Digitale Ausgabe: Motorsteuerung 
 *
 *  VV_device = [ DEVICE_MOTOR1, DEVICE_MOTOR2,.. ]
 *  VV_command = ON, OFF, RECHTS, LINKS
 */
static void MP_motor(int VV_device,int VV_command);

/** 
 *  @fn       MP_digin(int VV_device)
 *  @param    VV_device
 *  @brief    MP_digin
 *
 *  VV_device = [ CMD_DIGIN1, CMD_DIGIN2,.. ]
 */
static int MP_digin(int VV_device) reentrant;

/** 
 *  @fn       MP_sema(int VV_sema)
 *  @param    VV_sema
 *  @return   int Wert der Semaphore
 *	@brief    Semaphore lesen  
 */
static int MP_sema(int VV_sema);

/** 
 *  @fn       MP_semaset(int VV_sema, int VV_value)
 *  @param    VV_sema
 *  @param    VV_value
 *	@brief    Semaphore setzen  
 */
static void MP_semaset(int VV_sema, int VV_value);
#endif

/** 
 *  @fn       MP_anin(int VV_device)
 *  @param    VV_device
 *  @return   int Helligkeit des Fototransistors
 *	@brief    Analoge Eingabe: Fototransistoren lesen 
  *
 *  Der 8051 kann immer nur eine A/D Konvertierung zu einem
 *  Zeitpunkt vornehmen.
 *  VV_device = [ DEVICE_ANIN1, DEVICE_ANIN2,.. ]
 *  Rueckgabewert:
 *  255 = beleuchteter FT, 0 = unbeleuchteter FT
 */
static int MP_anin(int VV_device);

/** 
 *  @fn       MP_lichtschranke(int VV_device)
 *  @param    VV_device
 *  @return   int TRUE = Fotozelle wird beleuchtet
 *	@brief    Lichtschranke abfragen  
 *
 *  VV_device = [ LICHTSCHRANKE1, LICHTSCHRANKE2 ]
 *  Rueckgabewert:
 *  TRUE = Fotozelle wird beleuchtet
 *  255 = beleuchteter FT, 0 = unbeleuchteter FT 
 */
static int MP_lichtschranke(int VV_device);

/** 
 *  @fn       MP_p1wait1
 *	@brief    Prozess1, Schleife1  
 *
 *  Prozess1, Schleife1
 *  Grundstellung des Schiebers anfahren
 *  Schieber ganz zurueck bis zur Endstellung fahren
 */
static void MP_p1wait1(void);

/** 
 *  @fn       MP_p1wait2
 *	@brief    Prozess1, Schleife2  
 *
 *  Prozess1, Schleife2
 *  Auftrag erledigt markieren
 *  Warten, bis Auftrag von Prozess3 erteilt wird
 */
static void MP_p1wait2(void);

/** 
 *  @fn       MP_p1wait3
 *	@brief    Prozess1, Schleife3  
 *
 *  Prozess1, Schleife3
 *  Schieber nach vorne fahren bis in die Endstellung
 */
static void MP_p1wait3(void);

/** 
 *  @fn       MP_p2wait1
 *	@brief    Prozess2, Schleife1  
 *
 *  Prozess2, Schleife1
 *  Grundstellung: Wendeband laufen lassen,
 *  bis Taster geschlossen ist
 */
static void MP_p2wait1(void);

/** 
 *  @fn       MP_p2wait2
 *	@brief    Prozess2, Schleife2  
 *
 *  Prozess2, Schleife2
 *  Auftrag erledigt melden
 *  Warten, bis Auftrag von Prozess3 erteilt wird
 */
static void MP_p2wait2(void);

/** 
 *  @fn       MP_p2wait3
 *	@brief    Prozess2, Schleife3  
 *
 *  Prozess2, Schleife3
 *  Wendeband betaetigen, bis Taster wieder betaetigt wird
 *  (Paket kippen)
 */
static void MP_p2wait3(void);

/** 
 *  @fn       MP_p3wait1
 *	@brief    Auf Start-Taster warten ( Paket eingelegt ) 
 */
static void MP_p3wait1(void);

/** 
 *  @fn       MP_p3wait2
 *	@brief    Paket bis zur Lichtschranke fahren 
 *
 *  M3 positionieren
 *  Paket bis zur Lichtschranke fahren
 */
static void MP_p3wait2(void);

/** 
 *  @fn       MP_p3wait3
 *	@brief    Paket bis zur Lichtschranke zurueck fahren
 *            und dann Foerderband stoppen 
 *
 *  M3 positionieren
 *  Paket bis zur Lichtschranke zurueck fahren
 *  und dann Foerderband stoppen
 */
static void MP_p3wait3(void);

/**
 *  @fn       MP_p3wait4
 *	@brief    Wendeauftrag erteilen und warten, 
 *            bis er ausgefuehrt wurde 
 */
static void MP_p3wait4(void);

/**
 *  @fn       MP_p3wait5
 *	@brief    Schiebeauftrag erteilen und warten, 
 *            bis er ausgefuehrt wurde 
 */
static void MP_p3wait5(void);

/**
 *  @fn       MP_impulsscheibe
 *  @param    VV_impulse
 *	@brief    5 Schritte der Impulsscheibe abwarten 
 */
static void MP_impulsscheibe(int VV_impulse);


/** 
 *  @fn       MP_calibrate
 *  @param    VV_action
 *	@brief    Kalibrierung der Analog-Eingaenge 
 */
static void MP_calibrate(int VV_action);

/** 
 *  @fn       MP_wait_for_operator
 *	@brief    Warten auf Aktion des Bedienpersonals 
 */
static void MP_wait_for_operator(void);

/** 
 *  @fn       MP_motors_off
 *  @brief    Motor-Abschaltung 
 */
static void MP_motors_off(void);
/*.. */

#if defined(DEBUG2)
/** 
 *  @fn       GP_break00
 *  @brief    GP_break00
 */
void GP_break00(void);

/** 
 *  @fn       GP_break01
 *  @brief    GP_break01
 */
void GP_break01(void);

/** 
 *  @fn       GP_break02
 *  @brief    GP_break02
 */
void GP_break02(void);

/** 
 *  @fn       GP_break03
 *  @brief    GP_break03
 */
void GP_break03(void);

/** 
 *  @fn       GP_break10
 *  @brief    GP_break10
 */
void GP_break10(void);

/** 
 *  @fn       GP_break20
 *  @brief    GP_break20
 */
void GP_break20(void);

/** 
 *  @fn       GP_break30
 *  @brief    GP_break30
 */
void GP_break30(void);

/** 
 *  @fn       GP_break31
 *  @brief    GP_break31
 */
void GP_break31(void);

/** 
 *  @fn       GP_break32
 *  @brief    GP_break32
 */
void GP_break32(void);

/** 
 *  @fn       GP_break33
 *  @brief    GP_break33
 */
void GP_break33(void);

/** 
 *  @fn       GP_break40
 *  @brief    GP_break40
 */
void GP_break40(void);

/** 
 *  @fn       GP_break50
 *  @brief    GP_break50
 */
void GP_break50(void);
#endif

/**
 *  @fn       MP_prozess0
 *	@brief    Zuerst ausgefuehrter Prozess 
 */	
void MP_prozess0(void);

/** 
 *  @fn       MP_prozess1
 *	@brief    Prozess 1, Schieber  
 *
 *  Prozess 1
 *  Schieber
 */
void MP_prozess1(void);

/** 
 *  @fn       MP_prozess2
 *	@brief    Prozess2, Wendeband
 *
 *  Prozess 2
 *  Wendeband
 */
void MP_prozess2(void);

/** 
 *  @fn       MP_prozess3
 *	@brief    Prozess 3, Foerderband 
 */
void MP_prozess3(void);

/** 
 *  @fn       MP_prozess4
 *	@brief    Prozess 4, Licht 
 */
void MP_prozess4(void);

/** 
 *  @fn       MP_prozess5
 *	@brief    Prozess 5, Blinklicht 
 */
void MP_prozess5(void);

#if defined(_80537)
#if !defined(USE_RTX51_TINY)

/** 
 *  @fn       main
 *  @brief    main
 */
void main(void);
#endif
#else
/** 
 *  @fn      main(int VV_argc, char *IV_argv[])
 *  @param   VV_argc
 *  @param   IV_argv
 *  @return  status
 *  main
 */
int main(int VV_argc, char *IV_argv[]);
#endif

#if defined(USE_CONSOLE_IO)
/** 
 *  @fn       MP_lichtintensitaets_test
 *  @brief    MP_lichtintensitaets_test
 */
static void MP_lichtintensitaets_test(void);
#endif

#if defined(USE_RTX51_TINY)
#if defined(USE_CONSOLE_IO)
/** 
 *  @fn       getline (char *line, char n)
 *  @param    line
 *  @param    n
 *  @brief    Eingabezeile vom Terminal holen
 */
extern getline (char *, char);

/**
 *  @fn       GP_serial_init
 *	@brief    Serielle Schnittstelle initalisieren 
 */
extern void GP_serial_init (void);

/**
 *  @fn       _getkey
 *	@brief    _getkey
 */
extern char _getkey (void);
#endif
#endif

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Testroutinen-Definition                                         */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#if defined(USE_CONSOLE_IO)
/**
 *  @fn       MP_display_light_intensity
 *	@brief    Anzeige der Helligkeitsschwelle des Fototransistors
 *
 *  Anzeige der Helligkeitsschwelle des Fototransistors zum
 *  Betrieb der Lichtschranke zur Festlegung des Wertes der
 *  Preprozessor-Konstante HELLIGKEITS_SCHWELLE
 *  255 = beleuchteter FT, LS nicht unterbrochen
 *  0 = LS unterbrochen, 0 = unbeleuchteter FT
 */
static void MP_display_light_intensity(void);

/**
 *  @fn       MP_display_digin
 *	@brief    Anzeige der Schaltzustaende der Digitaleingaenge
 */
static void MP_display_digin(void);

/**
 *  @fn       MP_switch_motor
 *	@brief    Ausgaenge (Motoren) schalten 
 */
static void MP_switch_motor(void);
#endif
#endif
