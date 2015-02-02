/**
 *
 *  @package   paketwender
 *  @file	   sioirq.c
 *  @brief     Interrupt Controlled Serial Interface for
 *             RTX-51 tiny 80535/80537 Version for the application
 *             "Paketwendeanlage" 
 *  @author    Rolf Hemmerling <hemmerling@gmx.net>
 *  @version   1.00, 
 *             programming language "C",
 *             framework "RTX51-Tiny",
 *             development tool chain "Keil C51"
 *  @date      2015-01-01
 *  @copyright Apache License, Version 2.0
 *
 *  sioirq.c - Interrupt Controlled Serial Interface for
 *             RTX-51 tiny 80535/80537 Version for the application
 *             "Paketwendeanlage"  
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

#include "misra_doxygen.h"

#ifdef _80537
#include <reg515.h>
#endif

#include "io.h"
#include "rtos.h"

/** 
 *  @def      USE_RTX51_TINY
 *  @brief    RTX-51 TINY nutzen 
 */
#define USE_RTX51_TINY

#ifdef USE_RTX51_TINY
/* RTX-51 Tiny ´Funktionen & Defines */
#include <rtx51tny.h>                 
#endif

/** 
 *  @def      OLEN
 *  @brief    Groesse des seriellen Sendepuffers
 *  ES0
 */
#define  OLEN  8

/** 
 *  @var      ostart
 *  @brief    Start-Index des Sendepuffers
 */
unsigned char  ostart;

/** 
 *  @var      oend
 *  @brief    Ende-Index des Sendepuffers
 */
unsigned char  oend;

/** 
 *  @var      outbuf
 *  @brief    Speicherplatz fuer Sendepuffer
 */
idata    char  outbuf[OLEN];

/** 
 *  @var      otask
 *  @brief    Task-Nummer des Sende-Tasks
 */
unsigned char  otask = 0xff;

/** 
 *  @def      ILEN
 *  @brief    Laenge des seriellen Empfangspuffer
 */
#define  ILEN  8
 
/** 
 *  @var      istart
 *  @brief    Start-Index des Empfangspuffers
 */
unsigned char  istart;

/** 
 *  @var      iend
 *  @brief    Ende-Index des Empfangspuffers
 */
unsigned char  iend;

/** 
 *  @var      inbuf
 *  @brief    Speicherplatz fuer Empfangspuffer
 */
idata    char  inbuf[ILEN];

/** 
 *  @var      itask
 *  @brief    Task-Nummer des Emfangs-Tasks
 */
unsigned char  itask = 0xff;

/** 
 *  @def      CTRL_Q
 *  @brief    Control+Q Zeichen
 */
#define   CTRL_Q  0x11

/** 
 *  @def      CTRL_S
 *  @brief    Control+S Zeichen
 */
#define   CTRL_S  0x13

/** 
 *  @var      sendfull
 *  @brief    Flag: Markiert, dass Sendepuffer voll ist
 */
bit   sendfull;

/** 
 *  @var      sendactive
 *  @brief    Flag: Markiert, dass Sender aktiv ist
 */
bit   sendactive;

/** 
 *  @var      sendstop
 *  @brief    Flag: Markiert XOFF Zeichen
 */
bit   sendstop;

/**
 *
 *  @fn       putbuf (char c)
 *  @param    c
 *	@brief    Zeichen zu S0BUF oder Sendepuffer schreiben 
 *
 */
void putbuf (char c)  {
  if (!sendfull)  {                   
		/* Senden nur wenn der Puffer nicht voll ist */
    if (!sendactive && !sendstop)  {  
			/* Wenn Sender nicht aktiv ist: */
			/* Sende das erste Zeichen direkt */
      sendactive = 1;                 
			/* Nach S0BUF um Senden anzufangen */
      S0BUF = c;                       
    }
    else  {                           
			/* Sonst: */
			/* Uebertrage das Zeichen in den Sendepuffer */
      outbuf[oend++ & (OLEN-1)] = c;  
			/* Setze Flag, dass Puffer voll ist */
      if (((oend ^ ostart) & (OLEN-1)) == 0)  sendfull = 1;
    }                                 
  }
}


/**
 *
 *  @fn       putchar (char c)
 *  @param    c
 *  @return   char
 *	@brief    Interrupt-gesteuerte Ausgabe eines Zeichens 
 *
 */
char putchar (char c)  {
  if (c == '\n')  {                   
		/* Expandiere das Newline Zeichen: */
    /* Warte bis der Sendepuffer leer ist */
    while (sendfull)  {               
			/* Setze Nummer des Ausgabe-Tasks */
      otask = os_running_task_id ();  
			/* RTX-51 Aufruf: Warte auf Signal */
      os_wait (K_SIG, 0, 0);          
			/* Loesche die Nummer des Ausgabe-Tasks */
      otask = 0xff;                   
    }
		/* Sende CR vor LF fuer <Neue Zeile> */
    putbuf (0x0D);                    
  }
	
	/* Warte bis Sendepuffer leer ist */
  while (sendfull)  {                 
		/* Setze Nummer des Ausgabe-Tasks */
    otask = os_running_task_id ();    
		/* RTX-51 Aufruf: Warte auf Signal */
    os_wait (K_SIG, 0, 0);            
		/* Loesche die Nummer des Ausgabe-Tasks */
    otask = 0xff;                     
  }
	
	/* Sende Zeichen */
  putbuf (c);                         
	/* Gib das Zeichen zurueck, weil so bei ANSI genormt */
  return (c);                         
}


/**
 *
 *  @fn       _getkey
 *	@brief    Interrupt-gesteuertes Lesen eines Zeichens 
 *
 */
char _getkey (void)  {
  while  (iend == istart)  {
		/* Setze Nummer des Eingabe-Tasks */
    itask = os_running_task_id ();    
		/* RTX-51 Aufruf: Warte auf Signal */
    os_wait (K_SIG, 0, 0);            
		/* Loesche die Nummer des Eingabe-Tasks */
    itask = 0xff;                     
  }
  return (inbuf[istart++ & (ILEN-1)]);
}

/**
 *
 *  @fn serial
 *	@brief    Interrupt-Routine für seriellen Empfaenger / Sender 
 *  Verwende Registerbank 2 für Interrupts
 */
void serial (void)
#ifdef __C51__
				           interrupt 4 using 2 
#endif
{
  unsigned char c;
  bit   start_trans = 0;

	/* Wenn Empfangs-Interrupt */
  if (RI0)  {                        
		/* Lese Zeichen */
    c = S0BUF;                       
		/* Loesche Interrupt-Anforderungs Flag */
    RI0 = 0;                         
		
		/* Verarbeite Zeichen */
    switch (c)  {                    
      case CTRL_S:
				/* Wenn Control+S, dann stoppe das Senden */
        sendstop = 1;                
        break;

      case CTRL_Q:
				/* Wenn Control+Q, dann starte das Senden */
        start_trans = sendstop;      
        sendstop = 0;
        break;

      default:                       
				/* Lese alle anderen Zeichen in inbuf */
        if (istart + ILEN != iend)  {
          inbuf[iend++ & (ILEN-1)] = c;
        }
        /* Wenn Task wartet: Signalisiere "fertig" */
        if (itask != 0xFF) isr_send_signal (itask);
        break;
    }
  }

	/* Wenn Sender-Interrupt */
  if (TI0 || start_trans)  {         
		/* Loesche Interrupt-Request Flag */
    TI0 = 0;                         
		/* Wenn Zeichen in Puffer und */
    if (ostart != oend)  {           
			/* Wenn nicht Control+S empfangen wurde */
      if (!sendstop)  {              
				/* Sende Zeichen */
        S0BUF = outbuf[ostart++ & (OLEN-1)];
        /* Loesche 'sendfull' Flag */				
        sendfull = 0;                
        /* Wenn Task wartet: Signalisiere "fertig" */
        if (otask != 0xFF)  isr_send_signal (otask);
      }
    }
    else 
		  /* Wenn alles gesendet ist, loesche 'sendactive' */
			sendactive = 0;             
  }

}

/**
 *
 *  @fn       GP_serial_init
 *	@brief    Serielle Schnittstelle initalisieren 
 *
 */
void GP_serial_init (void)  {
  /* Aktiviere den Interrupt fuer die seriellen Schnittstelle */
	ES = 1; 
}
