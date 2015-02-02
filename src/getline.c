/**
 *
 *  @package   paketwender
 *  @file	   getline.c
 *  @brief     Line Edited Character Input for the application
 *             "Paketwendeanlage" 
 *  @author    Rolf Hemmerling <hemmerling@gmx.net>
 *  @version   1.00, 
 *             programming language "C",
 *             framework "RTX51-Tiny",
 *             development tool chain "Keil C51" 
 *  @date      2015-01-01
 *  @copyright Apache License, Version 2.0
 *
 *  getline.c - Line Edited Character Input for the application
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

#include <stdio.h>

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
 *  @def      DEL
 *  @brief    DEL Zeichen
 */
#define DEL        0x7F

/** 
 *  @def      BACKSPACE
 *  @brief    BACKSPACE Zeichen
 */
#define BACKSPACE  0x08

/** 
 *  @def      CR
 *  @brief    CR Zeichen
 */
#define CR         0x0D

/** 
 *  @def      LF
 *  @brief    LF Zeichen
 */
#define LF         0x0A

/**
 *
 *  @fn       getline (char idata *line, unsigned char n)
 *  @param    line
 *  @param    n
 *	@brief    Zeichen auf Standard-Ausgabe ausgeben 
 *
 */
void getline (char idata *line, unsigned char n)  {
  unsigned char cnt = 0;
  char c;

  do  {
		/* Lese Zeichen */
    if ((c = _getkey ()) == CR) {
    	c = LF; }
		/* Verarbeite BACKSPACE */
    if (c == BACKSPACE  ||  c == DEL)  {    
      if (cnt != 0)  {            
				/* Verringere Zaehler cnt */
        cnt--;                              
				/* und den Zeilen-Zeigers */
        line--;                             
				/* Echo BACKSPACE */
        putchar (0x08);                     
        putchar (' ');
        putchar (0x08);
      }
    }
    else if (c != CTRL_Q && c != CTRL_S)  {   
			/* Ignoriere Control S und Control Q */
			/* Echo und speichern des Zeichens */
      putchar (*line = c);                  
			/* Erhoehung des Zeilen-Zeigers */
      line++;                               
			/* und Zaehlers */
      cnt++;                                
    }
  }  while (cnt < n - 1  &&  c != LF); 
     /* Pruefe auf Begrenzung und auf LINEFEED */	
	/* Markiere das Ende der Zeichenkette */
  *line = 0;                                
}
