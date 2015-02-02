#ifndef MISRA_DOXYGEN_H
#define MISRA_DOXYGEN_H
/**
 *
 *  @package   paketwender
 *  @file	   misra_doxygen.h
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
 *  misra_doxygen.h - Header file for the application "Paketwendeanlage"
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

/* MISRA-C Überprüfungen mit TI CCS aktivieren */
#ifdef __TI_COMPILER_VERSION__
/** 
 *  @def      CHECK_MISRA
 *  @brief    CHECK_MISRA
 */
#pragma CHECK_MISRA("all")
#endif

#ifdef __STDC__
/** 
 *  @def      DOXYGEN
 *  @brief    DOXYGEN is not running
 */
#undef DOXYGEN
#else
/** 
 *  @def      DOXYGEN
 *  @brief    DOXYGEN is running
 */
#define DOXYGEN
/* Defines to check conditional code */
#define __C51__
#endif

#endif
