/* 04.INC Start */

SIGNAL void SP_motor1 (long VV_delay1, long VV_delay2)
/*************************************************/
/* SP_motor1() simuliert den Schieber            */
/* VV_delay1 = Pause bei Inaktivitaet            */
/* VV_delay2 = Zeit, die der Motor braucht, den  */
/*             Schieber bis zum Taster E1 bzw.   */
/*             E2 zu bewegen                     */
/*************************************************/
 {
   int PV_motor;
   printf ("SP:Simulation des Schiebers aktiv\n");
   while (1)
     {
      twatch (VV_delay1); /* Simulations-Unterbrechung */
      PV_motor = (PORT5 >> 0) & 0x03;
      switch(PV_motor)
       {
         case 3: /* Motor aus */
         case 0: /* Motor aus */ 
           printf ("SP:Schieber-Stillstand\n");
           break;
         case 1: /* Motor rechts */
           /* Motor faehrt zurueck bis Taster E2 gedrueckt */

           printf ("SP:Taster E1 wird von Schieber nicht mehr gedrueckt\n");

           PORT4 |= !0x01; /* E1 wird nicht mehr gedrueckt */
           twatch (VV_delay2);
           PORT4 &= !0x02; /* E2 wird gedrueckt */
           printf ("SP:Taster E2 von Schieber gedrueckt\n");
           break;
         case 2: /* Motor links */
           /* Motor faehrt vor bis Taster E1 gedrueckt */

           printf ("SP:Taster E2 wird von Schieber nicht mehr gedrueckt\n");

           PORT4 |= !0x02; /* E2 wird nicht mehr gedrueckt */
           twatch (VV_delay2);
           PORT4 &= !0x01; /* E2 wird gedrueckt */
           printf ("SP:Taster E1 von Schieber gedrueckt\n");
           break;
         default:
           printf("SP:Schieber Simulationsfehler!\n");
       };
     };
 }

SIGNAL void SP_motor2 (long VV_delay1, long VV_delay2)
/********************************************************/
/* SP_motor2() simuliert das Wendeband                  */
/* VV_delay1 = Pause bei Inaktivitaet                   */
/* VV_delay2 = Zeit, die der Motor braucht, das         */
/*             Wendeband von einem Unterbrechungsmarker */
/*             bis zum naechsten zu transportieren      */
/********************************************************/
 {
   int PV_motor;
   printf ("SP:Simulation des Wendebands aktiv\n");
   while (1)
     {
      twatch (VV_delay1); /* Simulations-Unterbrechung */
      PV_motor = (PORT5 >> 2) & 0x03;
      switch(PV_motor)
       {
         case 3: /* Motor aus */
         case 0: /* Motor aus */ 
           printf ("SP:Wendeband-Stillstand\n");
           break;
         case 2: /* Motor links */
           /* Motor faehrt Wendeband von einem Unterbrechungsmarker */
           /* bis zum naechsten, wodurch E5 (wieder) gedrueckt wird */
           printf ("SP:Wendeband-Motor faehrt an\n");

           printf ("SP:Taster E5 des Wendebandes wird nicht gedrueckt\n");
           PORT4 &= !0x10;
           twatch (VV_delay2);

           printf ("SP:Taster E5 des Wendebandes gedrueckt\n");
           PORT4 |= 0x10;

           break;
         case 1: /* Motor rechts */
           printf("SP:Wendeband-Motor faehrt an, aber in falsche Richtung!\n");
         default:
         printf("SP:Wendeband Simulationsfehler!\n");
       };
     };
 }

SIGNAL void SP_motor3 (long VV_delay1, long VV_delay2)
/*************************************************/
/* SP_motor3() simuliert das Foerderband         */
/*************************************************/
 {
   /* Unvollstaendige Simulation: */
   /* Motor3 links/rechts/aus wird nur 1x geprueft, richtig waere,
      daá davon auch die Simulation abhaengt */

   int PV_motor;
   int PV_paketoberflaeche;
   int PV_impuls;
   float volts;
   printf ("SP:Simulation des Foerderbands aktiv\n");
   while (1)
     {
      /* Einlegen eines neuen Pakets bestaetigen */
      keywait("Warten auf Einfuehren des naechsten Pakets");

      printf ("SP:Start-Taster wird vom Paket gedrueckt\n");
      PORT4 &= !0x08;

      twatch (VV_delay1);

      printf ("SP:Start-Taster ist nicht mehr gedrueckt\n");
      PORT4 |= 0x08;

      printf ("SP:Warten auf Anlaufen des Foerderbandes nach RECHTS\n");
      PV_motor = (PORT5 >> 4) & 0x03;
      while (PV_motor != 2)
       {twatch (VV_delay1); PV_motor = (PORT5 >> 4) & 0x03; };

      printf ("SP:Paket faehrt auf Foerderband zur Lichtschranke\n");
      twatch (VV_delay2);

      printf ("SP:Lichtschranke wird ausgeloest (Einfahren von RECHTS)\n");
      /* PORT4 &= !0x20; */
      volts = 0x0FF * 5; AIN0 = volts / 255;

      twatch (VV_delay2);
      printf ("SP:Lichtschranke wird nicht mehr ausgeloest (Ausfahren nach LINKS)\n");
      /* PORT4 |= 0x20; */
      volts = 0x0DC * 5; AIN0 = volts / 255;

      do

       {
         twatch (VV_delay1);

         printf ("SP:Warten auf Anlaufen des Foerderbandes nach LINKS\n");
         PV_motor = (PORT5 >> 4) & 0x03;
         while (PV_motor != 1)
         { twatch (VV_delay1); PV_motor = (PORT5 >> 4) & 0x03; };

         /* Vor Einfahren von Links muessen wir festlegen, wie die
            Paketoberflaeche aussieht */
         PV_paketoberflaeche = getint("Paketoberflaeche 0=schwarz, 1=weiss :");

         twatch (VV_delay1);
         printf ("SP:Lichtschranke wird ausgeloest (Einfahren von LINKS)\n");
         /* PORT4 |= 0x20; */
         volts = 0x0FF * 5; AIN0 = volts / 255;

         if (PV_paketoberflaeche==0)
          { volts = 0x0FC * 5; AIN0 = volts / 255; }
         else
          { volts = 0x0DC * 5; AIN0 = volts / 255; };

         printf ("SP:Warten auf Stop des Foerderbandes \n");
         PV_motor = (PORT5 >> 4) & 0x03;
         while (PV_motor != 0)
          { twatch (VV_delay1); PV_motor = (PORT5 >> 4) & 0x03; };

         if (PV_paketoberflaeche==0)
          {
            printf ("SP:Paketoberflaeche schwarz\n");

            printf ("SP:Warten auf Anlaufen des Foerderbandes nach RECHTS\n");
            PV_motor = (PORT5 >> 4) & 0x03;
            PV_impuls = 0;
            while (PV_motor != 2)
             {
               twatch (VV_delay1);
               PORT4 &= !0x40;
               twatch (VV_delay1);
               PORT4 |= 0x40;
               PV_impuls++;
               printf ("SP:Impulsscheiben-Impuls%d\n",PV_impuls);
               PV_motor = (PORT5 >> 4) & 0x03;
             };

            printf ("SP:Warten auf Stop des Foerderbandes \n");
            PV_motor = (PORT5 >> 4) & 0x03;
            while (PV_motor != 0)
             { twatch (VV_delay1); PV_motor = (PORT5 >> 4) & 0x03; };

            twatch (VV_delay1);
          }
         else
          {
            printf ("SP:Paketoberflaeche weiss\n");
            printf ("SP:Warten auf Anlaufen des Foerderbandes nach LINKS\n");
            PV_motor = (PORT5 >> 4) & 0x03;
            PV_impuls = 0;
            while (PV_motor != 2)
             {
               twatch (VV_delay1);
               PORT4 &= !0x40;
               twatch (VV_delay1);
               PORT4 |= 0x40;
               PV_impuls++;
               printf ("SP:Impulsscheiben-Impuls%d\n",PV_impuls);
               PV_motor = (PORT5 >> 4) & 0x03;
             };

            twatch (VV_delay1);

            };
       } while (PV_paketoberflaeche!=0);
     };
 }

SP_motor1 (900000L,1000000L);
SP_motor2 (900000L,1000000L);
/* Foerderbandsimulation wird einstweilen per Hand gestartet */
/* SP_motor3 (900000L,1000000L); */

/* 04.INC Ende */
