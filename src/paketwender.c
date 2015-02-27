/**
 *
 *  @package   paketwender
 *  @file      paketwender.c
 *  @brief     Embedded Software zur Steuerung des fischertechnik-Modell 
 *             "Paketwendeanlage"
 *  @author    Rolf Hemmerling <hemmerling@gmx.net>
 *  @version   1.00, 
 *             programming language "C",
 *             framework "RTX51-Tiny",
 *             development tool chain "Keil C51"
 *  @date      2015-01-01
 *  @copyright Apache License, Version 2.0
 *
 *  paketwender.c - Paketwendeanlage
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
 * Hardware:
 *  - (1a) 80537 Microcontroller-Systeme der FH Hannover
 *    - Ein/Ausgaben ueber Port 4 und 5 und AN0 .. AN3.
 *    - Timer0 wird von RTX-Tiny verwendet
 *    - PC ist mit Schnittstelle S0OUT,S0IN verbunden
 *  - (1b) MSDOS PC mit Fischertechnik-Parallelinterface
 *  - (2) Fischertechnik-Modell "Paketwendeanlage"
 * Simulation:
 *  - Keil DSCOPE-51+ V5.01 fuer MSDOS und neuer
 *  - DSCOPE fuer Windows 1.51e und neuer
 * Emulation:
 *  - EMULATOR E3200 Dr.Krohn&Stiller, fuer 80537
 *     Software fuer 8051 Targets:
 *  - Keil Software C51 C-Compiler V3.40, V5.50 und neuer
 *  - RTX-51 Tiny Betriebssystem (keine Unterstuetzung von
 *    Mehrfach-Datenpointern, non-reentrant Unterstuetzung der
 *    Arithmetik-Einheit, keine Unterstuetzung von als reentrant
 *    definierten/deklarierten Funktionen)
 * Software fuer MSDOS / WINDOWS Targets:
 *  - Diverse MSDOS C-Compiler
 * Aufgabe:
 *  Steuerung des fischertechnik-Modells "Paketwendeanlage":
 *  a) Erkennung der Anschriftsseite
 *  b) Wenden des Pakets zur Anschriftsseite hin
 * Kommunikation:
 *  - EMULATOR E3200 Dr.Krohn&Stiller ->Kommmando JDB initialisiert
 *    u.a. serielle Schnittstelle des Emulators
 *  - COM1 (PC) = S0OUT,S0IN (80537) -> Terminal-Ein/Ausgabe
 * Letzter Test mit Hardware:
 *  1999-11-22
 */
 
#include "misra_doxygen.h"
#include "paketwender.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Modulglobale Variablen                                          */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/** 
 * @var      MV_anin_value
 * @brief    Ablage der eingelesenen A/D Werte der Lichtschranke 
 */
static int MV_anin_value[4][NUMBER_OF_ANINS];

/* Ruhezustand der Taster bei Prozessbeginn wird hier gespeichert */
/* Daher sind Taster sowohl als Schalter als auch als Unterbrecher*/
/* wahlfrei einbaubar !                                           */
#if defined (USE_BITACCESS)
bdata
#endif
      /** 
       *  @var MV_digin_state_of_rest
       *  MV_digin_state_of_rest
       */
      int MV_digin_state_of_rest;

#if defined (USE_BITACCESS)
/**
 *  @var      STATE_OF_REST1
 *	@brief    STATE_OF_REST1 
 */
sbit STATE_OF_REST1 = MV_digin_state_of_rest^0;
/**
 *  @var      STATE_OF_REST2
 *	@brief    STATE_OF_REST2 
 */
sbit STATE_OF_REST2 = MV_digin_state_of_rest^1;
/**
 *  @var      STATE_OF_REST3
 *	@brief    STATE_OF_REST3 
 */
sbit STATE_OF_REST3 = MV_digin_state_of_rest^2;
/**
 *  @var      STATE_OF_REST4
 *	@brief    STATE_OF_REST4 
 */
sbit STATE_OF_REST4 = MV_digin_state_of_rest^3;
/**
 *  @var      STATE_OF_REST5
 *	@brief    STATE_OF_REST5 
 */
sbit STATE_OF_REST5 = MV_digin_state_of_rest^4;
/**
 *  @var      STATE_OF_REST6
 *	@brief    STATE_OF_REST6 
 */
sbit STATE_OF_REST6 = MV_digin_state_of_rest^5;
/**
 *  @var      STATE_OF_REST7
 *	@brief    STATE_OF_REST7 
 */
sbit STATE_OF_REST7 = MV_digin_state_of_rest^6;
/**
 *  @var      STATE_OF_REST8
 *	@brief    STATE_OF_REST8 
 */
sbit STATE_OF_REST8 = MV_digin_state_of_rest^7;
#endif

#if !defined(USE_RTX51_TINY)
/* Semaphoren */
/**
 *  @var      MV_sema0
 *	@brief    Semaphore MV_sema0 
 */
static int MV_sema0 = 0;
/**
 *  @var      MV_sema1
 *	@brief    Semaphore MV_sema1 
 */
static int MV_sema1 = 0;
/**
 *  @var      MV_sema2
 *	@brief    Semaphore MV_sema2 
 */
static int MV_sema2 = 0;
#endif

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Modulglobale Prozeduren und Funktionen                          */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#if defined(DEBUG2)

void GP_break00(void){}

void GP_break01(void){}

void GP_break02(void){}

void GP_break03(void){}

void GP_break10(void){}

void GP_break20(void){}

void GP_break30(void){}

void GP_break31(void){}

void GP_break32(void){}

void GP_break33(void){}

void GP_break40(void){}

void GP_break50(void){}
#endif

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
                              VV_wait) reentrant
  {
#if defined(HAVE_CLOCK)
    /* Pauses for a specified number of microseconds. */
    /* Entnommen aus MSVC Beispiel fuer  '_inp'       */
    clock_t PV_goal;
    PV_goal = VV_wait + clock();
    while (PV_goal > clock() );
#else
#if defined(HAVE_WAIT)
    unsigned int LV_ii = 0;
    for (LV_ii=0; LV_ii<VV_wait; LV_ii++)
      {
        os_wait(K_IVL, 255,0);
      };
#else
    unsigned long LV_ii = 0L, LV_jj = 0L;
    volatile int PV_dummy1;
    volatile int PV_dummy2;
    for (LV_jj=0L; LV_jj<VV_wait; LV_jj++)
     {
       for (LV_ii=0L; LV_ii<SPEED_COMPENSATION; LV_ii++)
        {
          PV_dummy2 = PV_dummy1;
        };
     };
#endif
#endif
  }

static void MP_wait(void) reentrant
 {
#if defined(HAVE_CLOCK)
    /* Zeitdauer 250.000 usec = 0.25 sec */
    clock_t PV_time = 2500000L;
#else
#if defined(HAVE_WAIT)
    /* Zeitdauer */
    int PV_time = 1;
#else
    /* Zeitdauer */
    long PV_time = 1L;
#endif
#endif
      MP_sleep(PV_time);
 }

static void MP_motors_off(void)
 {
#if defined (USE_BITACCESS)
    MOTOR_CONTROL(MOTOR1_1,MOTOR1_0,OFF);
#else
    MOTOR_CONTROL(DEVICE_MOTOR1,OFF);
#endif

#if defined (USE_BITACCESS)
    MOTOR_CONTROL(MOTOR2_1,MOTOR2_0,OFF);
#else
    MOTOR_CONTROL(DEVICE_MOTOR2,OFF);
#endif

#if defined (USE_BITACCESS)
    MOTOR_CONTROL(MOTOR3_1,MOTOR3_0,OFF);
#else
    MOTOR_CONTROL(DEVICE_MOTOR3,OFF);
#endif

#if defined (USE_BITACCESS)
    MOTOR_CONTROL(MOTOR4_1,MOTOR4_0,OFF);
#else
    MOTOR_CONTROL(DEVICE_MOTOR4,OFF);
#endif

 }

static void MP_init(void)
 {
#if defined(_80537)

   /* Schnittstelleninitialisierung                        */
   /* fuer DSCOPE-51+ geeignet, 9600 bps, 8 bit, No Parity)*/
   /* Baudraten-Generator ein                              */
   BD    = 1;
   /* SCON: UART Mode 1 (oder 3); Empfaenger bereit,       */
   /* TI-Flag gesetzt, TB8 Bit nicht gesetzt               */
   SCON  = 0x052;
   /* PCON: SMOD=1 ->  9600 bd                             */
   PCON  = PCON | 0x80;


   /* Nach einem Reset des 80537 sind alle Ports = 1, */
   /* d.h. sie koennen zur Eingabe genutzt werden     */

   /* Port4 fuer Eingabe vorbereiten */
   P4 = 0xFF;

   /* Ruhezustand der Digitaleingaenge lesen */
   MV_digin_state_of_rest = P4;

   /* Port5 fuer Ausgabe vorbereiten                              */
   /* Es ist fuer Motoren als auch fuer Lampen egal, ob an ihren  */
   /* Eingaengen paarweise "1" oder "0" anliegt                   */
   /* = in jedem Fall Motor-Stillstand bzw. Lampen-Aus            */
   P5 = 0xFF;
#endif

#if defined(USE_SERIAL_INT)
   /* Interrupt-Freigabe fuer serielle Schnittstelle */
   GP_serial_init ();
#endif

#if defined(USE_RTX51_TINY)
   /* Signale loeschen */
   os_clear_signal(SCHIEBER);
   os_clear_signal(WENDEBAND);
   os_clear_signal(FOERDERBAND);
   os_clear_signal(LICHT);
#else
   /* Semaphoren-Initialisierung */
   MV_sema0 = 0;
   MV_sema1 = 0;
   MV_sema2 = 0;
#endif

   MV_digin_state_of_rest = 0;

   /* Motoren abschalten */
   MP_motors_off();

 }


#if !defined(_80537)
#if !defined(USE_RTX51_TINY)
static void MP_motor(int VV_device,int VV_command) reentrant
 {
#if defined(_80537)
#if defined(_80537)
   /* Opt1: Diese Methode nutzen fuer 80537 */
   /* Loeschen der zu VV_device gehoerenden Bits */
   P5 &= ~(0x03 << (VV_device*2));
   /* Addition der VV_command Bits */
   P5 |= (VV_command << (VV_device*2));
#else
   /* Opt2: Diese Methode nutzen fuer 80537 */
   switch (VV_device)
    { 
      case 0:
        MOTOR1_0 = VV_command & 0x01;
        MOTOR1_1 = (VV_command>>1) & 0x01;break;
      case 1:
        MOTOR2_0 = VV_command & 0x01;
        MOTOR2_1 = (VV_command>>1) & 0x01;break;
      case 2:
        MOTOR3_0 = VV_command & 0x01;
        MOTOR3_1 = (VV_command>>1) & 0x01;break;
      case 3:
        MOTOR4_0 = VV_command & 0x01;
        MOTOR4_1 = (VV_command>>1) & 0x01;break;
      default: break;
    };
#endif
#endif
 }
#endif
#endif

#if !defined(_80537)
#if !defined(USE_RTX51_TINY)
static int MP_digin(int VV_device) reentrant
 {
   int PV_value = 0;
#if defined(_80537)
   /* Achtung, P4 ist vom Typ "unsigned char" */
   /* => explizite (int) Umwandlung notwendig */
   PV_value = (((int)P4) >> VV_device) & 0x01;
#endif
   return (PV_value);
 }
#endif
#endif

static int MP_anin(int VV_device)
 {
   int PV_value = 0;
#if defined(_80537)

   /* Kanal einstellen, einmalige Wandlung vorbereiten */
   ADCON0 = ADCON0 & 0xC0;
   ADCON0 = ADCON0 | (unsigned char)VV_device;
   /* ADU starten */
   DAPR  = 0x00;

   /* Polling bis A/D Wandlung beendet */
   while (BSY);

   /* Wert lesen */
   PV_value = ADDAT;

#endif
   return (PV_value);
 }

 static int MP_lichtschranke(int VV_device)
 {
   int PV_value = 0;
#if defined(_80537)
   switch (VV_device)
    { 
      case 0:
        /* Fototransistor waagerecht am Transportband: */
#if defined(LIGHTCHECK_ANALOG)
        PV_value = (MP_anin(DEVICE_ANIN1) <
                   MV_anin_value[THRESHOLD][DEVICE_ANIN1]);
#else
        PV_value = (
#if defined (USE_BITACCESS)
                     LOG_DIGITAL_INPUT(CMD_DIGIN6,CMD_STATE_OF_REST6)
#else
                     LOG_DIGITAL_INPUT(CMD_DIGIN6)
#endif
                                                                ) == 1);
#endif
        break;
      case 1:
        /* Fototransistor der Reflexlichtschranke: */
#if defined(LIGHTCHECK_ANALOG)
        PV_value = (MP_anin(DEVICE_ANIN2) <
                   MV_anin_value[THRESHOLD][DEVICE_ANIN2]);
#else
        PV_value = (
#if defined (USE_BITACCESS)
                     LOG_DIGITAL_INPUT(CMD_DIGIN7,CMD_STATE_OF_REST7)
#else
                     LOG_DIGITAL_INPUT(CMD_DIGIN7)
#endif
                                                                ) == 1);
#endif
        break;
      default:
        break;
    };
#endif
   return (PV_value);
 }


#if !defined(USE_RTX51_TINY)
static int MP_sema(int VV_sema)
 {
  /**
   *  @var      PV_value
   *	@brief    PV_value  
   */
   int PV_value = 0;
#if defined(_80537)
   switch (VV_sema)
    { 
      case 0:
        PV_value = MV_sema0; break;
      case 1:
        PV_value = MV_sema1; break;
      case 2:
        PV_value = MV_sema2; break;
      default: break;
    };
#endif
   return(PV_value);
 }
#endif

#if !defined(USE_RTX51_TINY)
static void MP_semaset(int VV_sema, int VV_value)
 {
#if defined(_80537)
   switch (VV_sema)
    { 
      case 0:
        MV_sema0 = VV_value; break;
      case 1:
        MV_sema1 = VV_value; break;
      case 2:
        MV_sema2 = VV_value; break;
      default: break;
    };
#endif
 }
#endif

static void MP_p1wait1()
 {
#if defined (USE_BITACCESS)
    CONTINOUS_DATA_FLOW(MOTOR_CONTROL(MOTOR1_1,MOTOR1_0,RECHTS))
#else
    CONTINOUS_DATA_FLOW(MOTOR_CONTROL(DEVICE_MOTOR1,RECHTS))
#endif
        while (
#if defined (USE_BITACCESS)
                LOG_DIGITAL_INPUT(CMD_DIGIN2,CMD_STATE_OF_REST2)
#else
//                LOG_DIGITAL_INPUT(CMD_DIGIN2)

				(((int)P4) >> 2 )
		 // ^ ((MV_digin_state_of_rest >> CMD_DIGIN2) & 0x01)
//                LOG_DIGITAL_INPUT(CMD_DIGIN2)
#endif
                                                           == 0);
 }


static void MP_p1wait2()
 {
#if defined(USE_RTX51_TINY)
      /* Ein eventuelles Signal der "eigenen" Task loeschen */
      os_clear_signal(SELF);

      /* Auftrag erledigt markieren */
      os_send_signal(FOERDERBAND);

      /* Warten, bis Auftrag von Prozess3 erteilt wird */
      os_wait(K_SIG, 0,0);

#else
      /* Auftrag erledigt markieren */
      MP_semaset(SEMA_V1,0);
      /* Warten, bis Auftrag von Prozess3 erteilt wird */
      while (MP_sema(SEMA_V1) == 0);
#endif
 }

static void MP_p1wait3()
 {
#if defined (USE_BITACCESS)
    CONTINOUS_DATA_FLOW(MOTOR_CONTROL(MOTOR1_1,MOTOR1_0,LINKS))
#else
    CONTINOUS_DATA_FLOW(MOTOR_CONTROL(DEVICE_MOTOR1,LINKS))
#endif
    while (
#if defined (USE_BITACCESS)
            LOG_DIGITAL_INPUT(CMD_DIGIN1,CMD_STATE_OF_REST1)
#else
            LOG_DIGITAL_INPUT(CMD_DIGIN1)
#endif
                                                       == 0);
 }

void MP_prozess1(void)
#if defined(USE_RTX51_TINY)
                          _task_ SCHIEBER
#endif
 {
    /* Start */
    while(1)
    {

#if defined(DEBUG2)
      GP_break10();
#endif

      /* Grundstellung des Schiebers anfahren */
      /* Schieber ganz zurueck bis zur Endstellung fahren */
      MP_p1wait1();

      /* Motor1 ausschalten */
#if defined (USE_BITACCESS)
      MOTOR_CONTROL(MOTOR1_1,MOTOR1_0,OFF);
#else
      MOTOR_CONTROL(DEVICE_MOTOR1,OFF);
#endif

      /* Auftrag erledigt markieren */
      /* Warten, bis Auftrag von Prozess3 erteilt wird */
      MP_p1wait2();

      /* Schieber nach vorne fahren bis in die Endstellung */
      MP_p1wait3();
    };

 }

static void MP_p2wait1(void)
 {
    if (
#if defined (USE_BITACCESS)
         LOG_DIGITAL_INPUT(CMD_DIGIN5,CMD_STATE_OF_REST5)
#else
         LOG_DIGITAL_INPUT(CMD_DIGIN5)
#endif
                                                    == 0)
     {
#if defined (USE_BITACCESS)
    CONTINOUS_DATA_FLOW(MOTOR_CONTROL(MOTOR2_1,MOTOR2_0,LINKS))
#else
    CONTINOUS_DATA_FLOW(MOTOR_CONTROL(DEVICE_MOTOR2,LINKS))
#endif
       while (
#if defined (USE_BITACCESS)
               LOG_DIGITAL_INPUT(CMD_DIGIN5,CMD_STATE_OF_REST5)
#else
               LOG_DIGITAL_INPUT(CMD_DIGIN5)
#endif
                                                          == 0);
     }
 }

static void MP_p2wait2(void)
 {
#if defined(USE_RTX51_TINY)
    /* Ein eventuelles Signal der "eigenen" Task loeschen */
    os_clear_signal(SELF);

    /* Auftrag erledigt markieren */
    os_send_signal(FOERDERBAND);

    /* Warten, bis Auftrag von Prozess3 erteilt wird */
    os_wait(K_SIG, 0,0);
#else
    /* Auftrag erledigt melden */
    MP_semaset(SEMA_V2,0);
    /* Warten, bis Auftrag von Prozess3 erteilt wird */
    while (MP_sema(SEMA_V2) == 0);
#endif
 }

static void MP_p2wait3(void)
 {
#if defined (USE_BITACCESS)
    CONTINOUS_DATA_FLOW(MOTOR_CONTROL(MOTOR2_1,MOTOR2_0,LINKS))
#else
    CONTINOUS_DATA_FLOW(MOTOR_CONTROL(DEVICE_MOTOR2,LINKS))
#endif
    while (
#if defined (USE_BITACCESS)
            LOG_DIGITAL_INPUT(CMD_DIGIN5,CMD_STATE_OF_REST5)
#else
            LOG_DIGITAL_INPUT(CMD_DIGIN5)
#endif
                                                       == 1);
 }

void MP_prozess2(void)
#if defined(USE_RTX51_TINY)
                              _task_ WENDEBAND
#endif
 {
    /* Start */
    while (1)
    {

#if defined(DEBUG2)
      GP_break20();
#endif

      /* Grundstellung: Wendeband laufen lassen, */
      /* bis Taster geschlossen ist */
      MP_p2wait1();

      /* Motor2 ausschalten */
#if defined (USE_BITACCESS)
      MOTOR_CONTROL(MOTOR2_1,MOTOR2_0,OFF);
#else
      MOTOR_CONTROL(DEVICE_MOTOR2,OFF);
#endif

      /* Auftrag erledigt melden */
      /* Warten, bis Auftrag von Prozess3 erteilt wird */
      MP_p2wait2();

      /* Schieber nach vorne fahren bis in die Endstellung */
      MP_p2wait3();
    };

 }

static void MP_p3wait1(void)
 {
   while (
#if defined (USE_BITACCESS)
           LOG_DIGITAL_INPUT(CMD_DIGIN4,CMD_STATE_OF_REST4)
#else
           LOG_DIGITAL_INPUT(CMD_DIGIN4)
#endif
                                                      == 0);
 }

static void MP_p3wait2(void)
 {
   int LV_ii;
   volatile int PV_dummy1;
   volatile int PV_dummy2;
#if defined (USE_BITACCESS)
   MOTOR_CONTROL(MOTOR3_1,MOTOR3_0,RECHTS);
#else
   MOTOR_CONTROL(DEVICE_MOTOR3,RECHTS);
#endif
   while (MP_lichtschranke(LICHTSCHRANKE1) == 1);
#if defined(_80537)
   for (LV_ii=0L; LV_ii<100; LV_ii++)
    {
      PV_dummy2 = PV_dummy1;
    };
#endif
   while (MP_lichtschranke(LICHTSCHRANKE1) == 0);
 }

static void MP_p3wait3(void)
 {
#if defined (USE_BITACCESS)
   MOTOR_CONTROL(MOTOR3_1,MOTOR3_0,LINKS);
#else
   MOTOR_CONTROL(DEVICE_MOTOR3,LINKS);
#endif
   while (MP_lichtschranke(LICHTSCHRANKE1) == 1);
#if defined (USE_BITACCESS)
   MOTOR_CONTROL(MOTOR3_1,MOTOR3_0,OFF);
#else
   MOTOR_CONTROL(DEVICE_MOTOR3,OFF);
#endif
 }

static void MP_impulsscheibe(int VV_impulse)
 {
    int PV_var3 = 0;

    do
     {
       while (
#if defined (USE_BITACCESS)
               LOG_DIGITAL_INPUT(CMD_DIGIN3,CMD_STATE_OF_REST3)
#else
               LOG_DIGITAL_INPUT(CMD_DIGIN3)
#endif
                                                          == 0);
       while (
#if defined (USE_BITACCESS)
               LOG_DIGITAL_INPUT(CMD_DIGIN3,CMD_STATE_OF_REST3)
#else
               LOG_DIGITAL_INPUT(CMD_DIGIN3)
#endif
                                                          == 1);
       PV_var3++;
     } while (PV_var3 < VV_impulse);

 }

static void MP_p3wait4(void)
 {
#if defined(USE_RTX51_TINY)
    /* Ein eventuelles Signal der "eigenen" Task loeschen */
    os_clear_signal(SELF);

    /* Wendeauftrag erteilen und warten, bis er ausgefuehrt wurde */
    os_send_signal(WENDEBAND);
    os_wait(K_SIG, 0,0);
#else
   MP_semaset(SEMA_V2,MP_sema(SEMA_V2)+1);
   while (MP_sema(SEMA_V2) != 0);
#endif
 }

static void MP_p3wait5(void)
 {
#if defined(USE_RTX51_TINY)
    /* Ein eventuelles Signal der "eigenen" Task loeschen */
    os_clear_signal(SELF);

    /* Schiebeauftrag erteilen und warten, bis er ausgefuehrt wurde */
    os_send_signal(SCHIEBER);
    os_wait(K_SIG, 0,0);
#else
   MP_semaset(SEMA_V1,MP_sema(SEMA_V1)+1);
   while (MP_sema(SEMA_V1) != 0);
#endif
 }

void MP_prozess3(void)
#if defined(USE_RTX51_TINY)
                              _task_ FOERDERBAND
#endif
 {
    int PV_weiss_oben = 0;
#if defined(DEBUG)
    char PV_char;
#endif

    /* Start */
    while (1)
    {

#if defined(DEBUG2)
      GP_break30();
#endif

      /* Auf Start-Taster warten (Paket eingelegt) */
      MP_p3wait1();

      /* Paket bis zur Lichtschranke fahren */
      MP_p3wait2();
#if defined(DEBUG)
         printf("DEBUG: Paket ist bis zur Lichtschranke gefahren\n");
         /* PV_char = getchar(); printf("\n"); */
#endif

      do
       {

#if defined(DEBUG2)
         GP_break31();
#endif

#if defined(DEBUG)
         printf("DEBUG: Paket zurueck fahren\n");
         /* PV_char = getchar(); printf("\n"); */
#endif

         /* Paket bis zur Lichtschranke zurueck fahren */
         /* und dann Foerderband stoppen */
         MP_p3wait3();

#if defined(DEBUG)
         printf("DEBUG: Paket ist zurueckgefahren, nun Paketoberflaeche vermessen\n");
         /* PV_char = getchar(); printf("\n"); */
#endif

         /* Paketoberflaeche vermessen (gelb/weiá  - oder schwarz) */
         PV_weiss_oben = (MP_lichtschranke(LICHTSCHRANKE2) == 1);

#if defined(DEBUG)
         printf("DEBUG: Lichtschranke= %d\n",PV_weiss_oben);
         /* PV_char = getchar(); printf("\n"); */
#endif

         if (PV_weiss_oben)
          {

#if defined(DEBUG2)
            GP_break32();
#endif

            /* Zum Wendeband fahren */
            /* Oberseite des Pakets gelb/weiá */

#if defined(DEBUG)
         printf("DEBUG: Zum Wendeband fahren\n");
         /* PV_char = getchar(); printf("\n"); */
#endif

#if defined (USE_BITACCESS)
            MOTOR_CONTROL(MOTOR3_1,MOTOR3_0,RECHTS);
#else
            MOTOR_CONTROL(DEVICE_MOTOR3,RECHTS);
#endif

            /* Paket zum Wendeband transportieren */
            /* 5 Schritte der Impulsscheibe */
            MP_impulsscheibe(5);

            /* Wendeauftrag erteilen und warten, bis er ausgefuehrt wurde */
            MP_p3wait4();

            /* Schleife nochmal durchlaufen ! */
          }
         else
          {

#if defined(DEBUG2)
            GP_break33();
#endif

            /* Zum Schieber fahren */
            /* Oberseite des Pakets schwarz */

#if defined (USE_BITACCESS)
            MOTOR_CONTROL(MOTOR3_1,MOTOR3_0,LINKS);
#else
            MOTOR_CONTROL(DEVICE_MOTOR3,LINKS);
#endif

            /* Paket zum Schieber transportieren */
            /* 5 Schritte der Impulsscheibe */
            MP_impulsscheibe(6);

            /* Druckfehler im Buch, hier korregiert: */
#if defined (USE_BITACCESS)
            MOTOR_CONTROL(MOTOR3_1,MOTOR3_0,OFF);
#else
            MOTOR_CONTROL(DEVICE_MOTOR3,OFF);
#endif

            /* Schiebeauftrag erteilen und warten, bis er ausgefuehrt wurde */
            MP_p3wait5();

            /* Schleife nicht mehr durchlaufen ! */
          }
       } while (PV_weiss_oben);
    };

 }

void MP_prozess4(void)
#if defined(USE_RTX51_TINY)
                              _task_ LICHT
#endif
 {
    /* Start */
    while (1)
    {
#if defined(DEBUG2)
      GP_break40();
#endif

#if defined (USE_BITACCESS)
      MOTOR_CONTROL(MOTOR4_1,MOTOR4_0,ON);
#else
      MOTOR_CONTROL(DEVICE_MOTOR4,ON);
#endif
#if defined(USE_RTX51_TINY)
#if defined(PC_PARALLEL)
      /* Bei kontinuierlichem Datenfluss: */
      /* Zeitweise Suspendierung          */
      os_wait(K_IVL, 255,0);
#else
      /* Kein kontinuierlicher Datenfluss */
      /* Prozess kann terminiert werden   */
      os_delete_task(SELF);
#endif
#endif
    };

 }

void MP_prozess5(void)
#if defined(USE_RTX51_TINY)
                              _task_ BLINKLICHT
#endif
 {
#if defined(HAVE_CLOCK)
    /* Zeitdauer 250.000 usec = 0.25 sec */
    clock_t PV_time = 2500000L;
#else
#if defined(HAVE_WAIT)
    /* Zeitdauer fuer Blinklicht-Takt */
    int PV_time = 1;
#else
    /* Zeitdauer fuer Blinklicht-Takt */
    long PV_time = 1L;
#endif
#endif
    /* Start */
    while (1)
    {

#if defined(DEBUG2)
      GP_break50();
#endif

      /* Licht an */
#if defined (USE_BITACCESS)
      MOTOR_CONTROL(MOTOR4_1,MOTOR4_0,ON);
#else
      MOTOR_CONTROL(DEVICE_MOTOR4,ON);
#endif
      MP_sleep(PV_time);

      /* Licht aus */
#if defined (USE_BITACCESS)
      MOTOR_CONTROL(MOTOR4_1,MOTOR4_0,OFF);
#else
      MOTOR_CONTROL(DEVICE_MOTOR4,OFF);
#endif
      MP_sleep(PV_time);
    };

 }


#if defined(USE_RTX51_TINY)
static void MP_notaus_abschaltung(char * IV_meldung)
 {
   /* Notaus-Meldung */
   os_create_task (BLINKLICHT);

#if defined(USE_CONSOLE_IO)
   printf("%s\n",IV_meldung);
#endif

   /* Prozess kann suspendiert werden  */
   /* os_wait(K_SIG, 0,0); */
   /* Prozess kann terminiert werden   */
   os_delete_task(SELF);
 }
#endif


#if defined(USE_RTX51_TINY)
static void MP_wait_for_operator()
 {

#if defined(WAIT_FOR_KEY)
   int PV_char;
   /* Tastatur-Tastendruck */
   PV_char = _getkey ();
#else
   int PV_taster;
   /* Auf Tastenschalter warten */
   PV_taster =
#if defined (USE_BITACCESS)
               LOG_DIGITAL_INPUT(CMD_DIGIN7,CMD_STATE_OF_REST7)
#else
               LOG_DIGITAL_INPUT(CMD_DIGIN7)
#endif
                                                          ;
   while (PV_taster ==
#if defined (USE_BITACCESS)
                       LOG_DIGITAL_INPUT(CMD_DIGIN7,CMD_STATE_OF_REST7)
#else
                       LOG_DIGITAL_INPUT(CMD_DIGIN7)
#endif
                                                                  );
#endif
 }
#endif

static void MP_calibrate(int VV_action)
 {
   int LV_ii, PV_diff;

   switch(VV_action)
    {
      case THRESHOLD:
#if defined(USE_CONSOLE_IO)
        printf("Helligkeitsschwellen:\n");
#endif
        for (LV_ii=0;LV_ii<NUMBER_OF_ANINS;LV_ii++)
         {
           /* Kalibrierung der eingelesenen Werte */
           PV_diff = MV_anin_value[LIGHTED][LV_ii] -
                     MV_anin_value[DISRUPTED][LV_ii];
           if (PV_diff > 0)
            {
              /* Fall: LICHTSCHRANKE2 */
              MV_anin_value[VV_action][LV_ii] = (int)
                            MV_anin_value[DISRUPTED][LV_ii] + (PV_diff / 2);
            }
           else
            {
              /* Fall: LICHTSCHRANKE1 */
              MV_anin_value[VV_action][LV_ii] = (int)
                            MV_anin_value[LIGHTED][LV_ii] - (PV_diff / 2);
            };
#if defined(USE_CONSOLE_IO)
           printf("%6x ",MV_anin_value[VV_action][LV_ii] );
#endif
         };

#if defined(USE_CONSOLE_IO)
        printf("\n");
#endif
        break;
      case UNLIGHTED:
#if defined(USE_CONSOLE_IO)
        printf("Umgebungshelligkeit:\n");
#endif
        goto ML_calibrate;
      case LIGHTED:
#if defined(USE_CONSOLE_IO)
        printf("Helligkeit bei aktiver Lichtschranke:\n");
#endif
        goto ML_calibrate;
      case DEFAULT1:
#if defined(USE_CONSOLE_IO)
        printf("Default-Helligkeit bei aktiver Lichtschranke:\n");
#endif
        MV_anin_value[LIGHTED][DEVICE_ANIN1] = DEFAULT_LIGHTED1,
        MV_anin_value[LIGHTED][DEVICE_ANIN2] = DEFAULT_LIGHTED2;
#if defined(USE_CONSOLE_IO)
        printf("%6x, %6x\n",MV_anin_value[LIGHTED][DEVICE_ANIN1],
                            MV_anin_value[LIGHTED][DEVICE_ANIN2]
          );
        break;
#endif
      case DEFAULT2:
#if defined(USE_CONSOLE_IO)
        printf("Default-Helligkeit bei unterbrochener Lichtschranke:\n");
#endif
        MV_anin_value[DISRUPTED][DEVICE_ANIN1] = DEFAULT_DISRUPTED1,
        MV_anin_value[DISRUPTED][DEVICE_ANIN2] = DEFAULT_DISRUPTED2;
#if defined(USE_CONSOLE_IO)
        printf("%6x, %6x\n",MV_anin_value[DISRUPTED][DEVICE_ANIN1],
                            MV_anin_value[DISRUPTED][DEVICE_ANIN2]
          );
#endif
        break;
      case DISRUPTED:
#if defined(USE_CONSOLE_IO)
        printf("Helligkeit bei unterbrochener Lichtschranke:\n");
#endif
      default:
        ML_calibrate:;
        for (LV_ii=0;LV_ii<NUMBER_OF_ANINS;LV_ii++)
         {
           /* Lesen der Analog-Eingaenge */
           MV_anin_value[VV_action][LV_ii] = MP_anin(LV_ii);
#if defined(USE_CONSOLE_IO)
           printf("%6x ",MV_anin_value[VV_action][LV_ii] );
#endif
         };
#if defined(USE_CONSOLE_IO)
        printf("\n");
#endif
        break;
   };
 }


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Testroutinen                                                    */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#if defined(USE_CONSOLE_IO)
static void MP_display_light_intensity(void)
  { int PV_value = 0;
    printf("Helligkeitsanzeige der Fototransistoren 8..1:\n");
#if defined (USE_BITACCESS)
    MOTOR_CONTROL(MOTOR4_1,MOTOR4_0,ON);
#else
    MOTOR_CONTROL(DEVICE_MOTOR4,ON);
#endif
    while (1)
     {
       printf("%x, %x, %x, %x, %x, %x, %x, %x\n",
            MP_anin(DEVICE_ANIN8),MP_anin(DEVICE_ANIN7),
            MP_anin(DEVICE_ANIN6),MP_anin(DEVICE_ANIN5),
            MP_anin(DEVICE_ANIN4),MP_anin(DEVICE_ANIN3),
            MP_anin(DEVICE_ANIN2),MP_anin(DEVICE_ANIN1));
     };
  }
#endif

#if defined(USE_CONSOLE_IO)
static void MP_display_digin(void)
  { int PV_value = 0;
    printf("Schaltzustaende der Digitaleingaenge 8..1 (State:Raw:Log):\n");
#if defined (USE_BITACCESS)
    MOTOR_CONTROL(MOTOR4_1,MOTOR4_0,ON);
#else
    MOTOR_CONTROL(DEVICE_MOTOR4,ON);
#endif
    while (1)
     {
       printf("S%x:R%x:L%x,S%x:R%x:L%x,S%x:R%x:L%x,S%x:R%x:L%x,S%x:R%x:L%x,S%x:R%x:L%x,S%x:R%x:L%x,S%x:R%x:L%x\n",
                STATE_OF_REST_DIGITAL_INPUT(CMD_STATE_OF_REST8),
                RAW_DIGITAL_INPUT(CMD_DIGIN8),
#if defined (USE_BITACCESS)
                LOG_DIGITAL_INPUT(CMD_DIGIN8,CMD_STATE_OF_REST8),
#else
                LOG_DIGITAL_INPUT(CMD_DIGIN8),
#endif
                STATE_OF_REST_DIGITAL_INPUT(CMD_STATE_OF_REST7),
                RAW_DIGITAL_INPUT(CMD_DIGIN7),
#if defined (USE_BITACCESS)
                LOG_DIGITAL_INPUT(CMD_DIGIN7,CMD_STATE_OF_REST7),
#else
                LOG_DIGITAL_INPUT(CMD_DIGIN7),
#endif
                STATE_OF_REST_DIGITAL_INPUT(CMD_STATE_OF_REST6),
                RAW_DIGITAL_INPUT(CMD_DIGIN6),
#if defined (USE_BITACCESS)
                LOG_DIGITAL_INPUT(CMD_DIGIN6,CMD_STATE_OF_REST6),
#else
                LOG_DIGITAL_INPUT(CMD_DIGIN6),
#endif
                STATE_OF_REST_DIGITAL_INPUT(CMD_STATE_OF_REST5),
                RAW_DIGITAL_INPUT(CMD_DIGIN5),
#if defined (USE_BITACCESS)
                LOG_DIGITAL_INPUT(CMD_DIGIN5,CMD_STATE_OF_REST5),
#else
                LOG_DIGITAL_INPUT(CMD_DIGIN5),
#endif
                STATE_OF_REST_DIGITAL_INPUT(CMD_STATE_OF_REST4),
                RAW_DIGITAL_INPUT(CMD_DIGIN4),
#if defined (USE_BITACCESS)
                LOG_DIGITAL_INPUT(CMD_DIGIN4,CMD_STATE_OF_REST4),
#else
                LOG_DIGITAL_INPUT(CMD_DIGIN4),
#endif
                STATE_OF_REST_DIGITAL_INPUT(CMD_STATE_OF_REST3),
                RAW_DIGITAL_INPUT(CMD_DIGIN3),
#if defined (USE_BITACCESS)
                LOG_DIGITAL_INPUT(CMD_DIGIN3,CMD_STATE_OF_REST3),
#else
                LOG_DIGITAL_INPUT(CMD_DIGIN3),
#endif
                STATE_OF_REST_DIGITAL_INPUT(CMD_STATE_OF_REST2),
                RAW_DIGITAL_INPUT(CMD_DIGIN2),
#if defined (USE_BITACCESS)
                LOG_DIGITAL_INPUT(CMD_DIGIN2,CMD_STATE_OF_REST2),
#else
                LOG_DIGITAL_INPUT(CMD_DIGIN2),
#endif
                STATE_OF_REST_DIGITAL_INPUT(CMD_STATE_OF_REST1),
                RAW_DIGITAL_INPUT(CMD_DIGIN1),
#if defined (USE_BITACCESS)
                LOG_DIGITAL_INPUT(CMD_DIGIN1,CMD_STATE_OF_REST1)
#else
                LOG_DIGITAL_INPUT(CMD_DIGIN1)
#endif
                                                              );
     };
  }
#endif

#if defined(USE_CONSOLE_IO)
static void MP_switch_motor(void)
  { int PV_motor = 0, PV_command = 0;
    char PV_char;
    printf("Ausgaenge (Motoren) schalten 0..3:\n");
    PV_char = getchar();
    PV_motor = (int)PV_char - (int)'0';
    printf("\nSchaltwert fuer die beiden Ausgaenge (Eingaenge des Motors) 0..3:\n");
    PV_char = getchar();
    printf("\n");
    PV_command = (int)PV_char - (int)'0';
    printf("Motor %d, Kommando %d\n",PV_motor,PV_command);
    switch (PV_motor)
     {
       case DEVICE_MOTOR1:
#if defined (USE_BITACCESS)
         MOTOR_CONTROL(MOTOR1_1,MOTOR1_0,PV_command);
#else
         MOTOR_CONTROL(DEVICE_MOTOR1,PV_command);
#endif
         break;
       case DEVICE_MOTOR2:
#if defined (USE_BITACCESS)
         MOTOR_CONTROL(MOTOR2_1,MOTOR2_0,PV_command);
#else
         MOTOR_CONTROL(DEVICE_MOTOR2,PV_command);
#endif
         break;
       case DEVICE_MOTOR3:
#if defined (USE_BITACCESS)
         MOTOR_CONTROL(MOTOR3_1,MOTOR3_0,PV_command);
#else
         MOTOR_CONTROL(DEVICE_MOTOR3,PV_command);
#endif
         break;
       case DEVICE_MOTOR4:
#if defined (USE_BITACCESS)
         MOTOR_CONTROL(MOTOR4_1,MOTOR4_0,PV_command);
#else
         MOTOR_CONTROL(DEVICE_MOTOR4,PV_command);
#endif
         break;
       default:
         printf("Falsche Eingabe - Motor %d gibt es nicht\n",PV_motor);
     };
  }
#endif

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* main()                                                          */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#if defined(USE_RTX51_TINY)
void MP_prozess0(void) _task_ INIT
  {
#if defined(HAVE_CLOCK)
   /* Zeitdauer 250.000 usec = 0.25 sec */
   clock_t PV_time = 2500000L;
#else
#if defined(HAVE_WAIT)
   /* Zeitdauer fuer Blinklicht-Takt */
   int PV_time = 1;
#else
   /* Zeitdauer fuer Blinklicht-Takt */
   long PV_time = 1L;
#endif
#endif

   /* Initialisierung */
   MP_init();

#if defined(USE_CONSOLE_IO)
   printf("Steuerung des Fischertechnik-Modells ->Paketwendeanlage<-\n");
   printf("Analyse einer Paketsendung (Erkennung der Anschriftsseite)\n\n");
#endif
   /* Maschine springt nur an, wenn Notaus nicht betaetigt ist */
   /* Notaus-Schalter *muss* richtig gepolt sein, d.h. kein    */
   /* Vergleich mit dem "Einschaltzustand"                     */
   if (RAW_DIGITAL_INPUT(CMD_DIGIN8) == !NOTAUS)
    {


      /* Notaus Unterbrecher ist nicht betaetigt */

#if defined(DEBUG2)
      GP_break00();
#endif

      /* A/D Wert unbeleuchteter Fotozellen sichern */
      MP_calibrate(UNLIGHTED);


      /* Licht anschalten */
#if defined (USE_BITACCESS)
      MOTOR_CONTROL(MOTOR4_1,MOTOR4_0,ON);
#else
      MOTOR_CONTROL(DEVICE_MOTOR4,ON);
#endif

      /* Kleine Wartezeit ist notwendig. Ohne sie */
      /* wird hier der falsche Wert gemessen !    */
      MP_sleep(PV_time);

#if defined(DEBUG2)
      GP_break01();
#endif

      /* A/D Wert bei nicht unterbrochener Lichtschranke sichern */
      MP_calibrate(LIGHTED);


#if defined(USE_CONSOLE_IO)
      printf("Das Probepaket ist in Laengsrichtung so in Anlage plazieren,\n");
      printf("dass BEIDE Lichtschranken unterbrochen sind !\n");
      printf("Nach Unterbrechung der Lichtschranken bitte ");
#if defined(WAIT_FOR_KEY)
      printf("<RETURN> druecken !!\n");
#else
      printf("Taster %d !!\n", (int)DEVICE_DIGIN8);
#endif
#endif

#if defined(DEBUG2)
      GP_break02();
#endif

#if defined(USE_CONSOLE_IO)
      MP_wait_for_operator();
#endif

      /* A/D Wert bei unterbrochener Lichtschranke sichern */
      MP_calibrate(DISRUPTED);

#if defined(USE_CONSOLE_IO)
      printf("Nach Freigabe der Lichtschranken bitte ");
#if defined(WAIT_FOR_KEY)
      printf("<RETURN> druecken !!\n");
#else
      printf("Taster %d !!\n", (int)DEVICE_DIGIN8);
#endif
#endif

#if defined(DEBUG2)
      GP_break03();
#endif

#if defined(USE_CONSOLE_IO)
      MP_wait_for_operator();
#endif


#ifdef SIMULATION_HERE
      /* A/D Wert Default-Werte fuer Helligkeitsschwellen verwenden */
      MP_calibrate(DEFAULT1);
      MP_calibrate(DEFAULT2);
#endif

      /* Helligkeitsschwellen festlegen */
      MP_calibrate(THRESHOLD);

      /* Ueberwachungstask zum Lichteinschalten aktivieren */

      os_create_task (LICHT);

#if !defined(TEST)
      /* Tasks starten */
      os_create_task (SCHIEBER);
      os_create_task (WENDEBAND);
      os_create_task (FOERDERBAND);
#endif

    }
   else
    {


      /* Notaus Unterbrecher ist nach Betaetigung immer noch eingerastet */
      MP_notaus_abschaltung("Bitte NOTAUS Schalter loesen und Anlage neu starten !");
    };

   do
    {

#if defined(TEST)
#if defined(USE_CONSOLE_IO)
     /* MP_display_digin(); */
     MP_display_light_intensity();
     /* MP_switch_motor(); */
#endif
#endif

     /* Abfrage des NOTAUS-Schalters */
     if (RAW_DIGITAL_INPUT(CMD_DIGIN8) == NOTAUS)
      {
        /* Notaus wurde gedrueckt*/
        os_delete_task (SCHIEBER);
        os_delete_task (WENDEBAND);
        os_delete_task (FOERDERBAND);
        os_delete_task (LICHT);

        /* Motoren abschalten */
        MP_motors_off();

        MP_notaus_abschaltung("NOTAUS wurde betaetigt");
      };
    }
   while (1);
  
  }
#else
#if defined(_80537)
/**
 *
 *  @fn       main
 *	@brief    main 
 *
 */	
void main(void)
#else
/**
 *
 *  @fn       main
 *  @param    argc
 *  @param    argv     
 *	@brief    main 
 *
 */	
int main(int argc, char *argv[])
#endif
  {
    MP_init();
    printf("PWENDEANLAGE V1.00\n");
    printf("Steuerung des Fischertechnik-Modells ->Paketwendeanlage<-\n");
    printf("Analyse einer Paketsendung (Erkennung der Anschriftsseite)\n\n");
    printf("Copyright 1999-2015 Rolf Hemmerling\n");
    printf("Licensed under the Apache License, Version 2.0\n");
  }
#endif
