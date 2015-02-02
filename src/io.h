#ifndef IO_H
#define IO_H
/**
 *
 *  @package   paketwender
 *  @file      io.h
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
 *  io.h - Header file for the application "Paketwendeanlage"
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

/* Serial i/o communication */

/** 
 *  @var      SBUF
 *  @brief    SBUF
 */
extern char SBUF;
/** 
 *  @var      RI
 *  @brief    RI
 */
extern char RI;
/** 
 *  @var      TI
 *  @brief    TI
 */
extern char TI;
/** 
 *  @var      SCON
 *  @brief    SCON
 */
extern char SCON;
/** 
 *  @var      ES
 *  @brief    ES
 */
extern char ES;
/** 
 *  @var      SCON
 *  @brief    SCON
 */
extern char SCON;
/** 
 *  @var      ADCON
 *  @brief    ADCON
 */
extern char ADCON;

/** 
 *  @var      ADCON
 *  @brief    ADCON
 */
extern char ADCON;

/** 
 *  @var      K_SIG
 *  @brief    K_SIG
 */
extern int K_SIG;

/**
 *  @var      P4
 *  @brief    P4
 */
extern unsigned char P4;
	
/** 
 *  @def      S0BUF
 *  @brief    S0BUF
 */
#define S0BUF SBUF

/** 
 *  @def      RI0
 *  @brief    RI0
 */
#define RI0 RI

/** 
 *  @def      S0BUF
 *  @brief    S0BUF
 */
#define S0BUF SBUF

/** 
 *  @def      TI0
 *  @brief    TI0
 */
#define TI0 TI

/** 
 *  @def      S0CON
 *  @brief    S0CON
 */
#define S0CON SCON

/** 
 *  @def      ES0
 *  @brief    ES0
 */
#define ES0 ES

#endif

