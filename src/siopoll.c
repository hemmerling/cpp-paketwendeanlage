/**
 *
 *  @package   paketwender
 *  @file	   siopoll.c
 *  @brief     General character output of C51 for the application
 *             "Paketwendeanlage" 
 *  @author    Rolf Hemmerling <hemmerling@gmx.net>
 *  @version   1.00, 
 *             programming language "C",
 *             framework "RTX51-Tiny",
 *             development tool chain "Keil C51" 
 *  @date      2015-01-01
 *  @copyright Apache License, Version 2.0
 *
 *  siopoll.c - General character output of C51 for the application
 *              "Paketwendeanlage"  
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

/** 
 *  @def      S0BUF
 *  @brief    S0BUF
 */
#define S0BUF  SBUF

/**
 *
 *  @fn       _getkey
 *  @return   char
 *	@brief    Zeichen von Tastatur lesen 
 *
 */
char _getkey (void)  {
  /** 
   *  @var      c
   *  @brief    c
   */
  char c;

  while (!(S0CON & 0x01));
  c = S0BUF;
	/* RI = 0 */
  S0CON &= 0xFE;   
  return (c);
}

/** 
 *  @def XON
 *  XON
 */
#define XON  0x11

/** 
 *  @def XOFF
 *  XOFF
 */
#define XOFF 0x13

/**
 *
 *   fn       putchar (char c)
 *  @param    c
 *  @return   char
 *	@brief    Zeichen auf Standard-Ausgabe ausgeben 
 *
 */
char putchar (char c)  {

  if (c == '\n')  {
	  /* RI*/
    if (S0CON & 0x01)  {         
      if (S0BUF == XOFF)  {
        do  {
					/* RI = 0 */
          S0CON &= 0xFE;         
		      /* RI */
          while (!(S0CON & 0x01)); 
        }
        while (S0BUF != XON);
				/* RI = 0 */
        S0CON &= 0xFE;           
      }
    }
		/* while (!TI); */
    while (!(S0CON & 0x02));     
		/* TI = 0 */
    S0CON &= 0xFD;               
		/* Gib CR aus */
    S0BUF = 0x0d;                
  }
  if (S0CON & 0x01)  {
    if (S0BUF == XOFF)  {
      do  {
				/* RI = 0 */
        S0CON &= 0xFE;           
				/* while (!RI) */
        while (!(S0CON & 0x01)); 
      }
      while (S0BUF != XON);
			/* RI = 0 */
      S0CON &= 0xFE;             
    }
  }
	/* while (!TI); */
  while (!(S0CON & 0x02));       
	/* TI = 0 */
  S0CON &= 0xFD;                 
  return (S0BUF = c);
}

/**
 *
 *   fn       GP_serial_init
 *	@brief    Serielle Schnittstelle initalisieren 
 *
 */
void GP_serial_init (void)  {
	 /* Interrupt fuer serielle Schnittstelle deaktivieren */
   ES = 0; 
}

