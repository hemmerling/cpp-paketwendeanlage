/* 07.INC Start */

/* define watch variables */
/* ws variable */
WS PORT5
WS PORT4

/* 8051-Logik: Taster auf "0" setzen, d.h. nicht gedrueckt */
PORT4 = 0xFF;
/* Motoren auf "0" setzen, also Stilltstand und kein Licht" */
PORT5 = 0xFF;
/* Fototransistor = "0" = keine Lichteinstrahlung setzen  */
AIN0 &= 0x00;
AIN1 &= 0x00;

/* Fuer Simulationstest: */

/* ASSIGN WIN < S0IN > S0OUT */
/* ASSIGN COM2 <S0IN >S0OUT */
/* ASSIGN WIN <NUL >NUL */
/* ASSIGN COM2 <SIN >SOUT */

/* 07.INC Ende */

