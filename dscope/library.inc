/* library.INC Start */

SIGNAL void SP_analog0 (float limit)
/*************************************************/
/* Analog0() simulates analog input values given */
/*  to channel-0 (AIN0) of the 80C517            */
/*************************************************/
 {
   float volts;

   printf ("ANALOG0 (%f) ENTERED\n", limit);
   while (1)  {          /* forever */
    volts = 0;
    while (volts <= limit)
     {
      ain0 = volts;     /* analog input-0 */
      twatch (30000); /* 30000 Cycles Time-Break */
      volts += 0.5;     /* increase voltage */
     }
    volts = limit - 0.5;
    while (volts >= 0.5)
     {
       ain0 = volts;
       twatch (30000);   /* 30000 Cycles Time-Break */
       volts -= 0.5;     /* decrease voltage */
     }
   }
 }

func void DP_set4(int VV_port)
 {
  PORT4 |= 0x01 << VV_port;       /* set Port4.port */
  printf("SET(P4.%d)\n",VV_port);
 }

func void DP_clear4(int VV_port)
 {
  PORT4 &= ~(0x01 << VV_port);    /* reset Port4.port */
  printf("CLEAR(P4.%d)\n",VV_port);
 }

func void DP_set5(int VV_port)
 {
  PORT5 |= 0x01 << VV_port;       /* set Port5.port */
  printf("SET(P5.%d)\n",VV_port);
 }

func void DP_clear5(int VV_port)
 {
  PORT5 &= ~(0x01 << VV_port);    /* reset Port5.port */
  printf("CLEAR(P5.%d)\n",VV_port);
 }

/* Analog-Werte setzen fuer Fototransistor */
func void DP_setanalog()
 {
  int PV_device;
  float PV_value;
  PV_device = getint("Device AIN?: ");
  PV_value = getfloat("Voltage (Volt): ");
  switch (PV_device)
   {
     case 0: AIN0 = PV_value; break;
     case 1: AIN1 = PV_value; break;
     case 2: AIN2 = PV_value; break;
     case 3: AIN3 = PV_value; break;
     case 4: AIN4 = PV_value; break;
     case 5: AIN5 = PV_value; break;
     case 6: AIN6 = PV_value; break;
     case 7: AIN7 = PV_value; break;
     default:break;
   }
 }

func void DP_lichtschranken()
/*************************************************/
/* lichtschranken() simuliert die Lichtschranken */
/*************************************************/
 {
  int PV_status;
  PV_status = getint("Lichtschranken nicht unterbrochen = 0, unterbrochen=1 ?: ");
  /* Analog-Werte setzen fuer Fototransistoren */
  switch (PV_status)
   {
     case 0:
       /* Lichtschranken nicht unterbrochen */
       AIN0 = 0x0DC * 5 / 255;
       AIN1 = 0x0FF * 5 / 255;
       printf("Lichtschranken nicht unterbrochen\n");
       break;
     case 1:
       /* Lichtschranken unterbrochen */
       AIN0 = 0x0FF * 5 / 255;
       AIN1 = 0x0CD * 5 / 255;
       printf("Lichtschranken unterbrochen\n");
       break;
     default:
       printf("Falsche Parametereingabe fuer Lichtschranken-Simulation\n");
       break;
   }
 }

func void DP_portstatus2()  {
/******************************************************/
/* Status aller Ports + Signale der Paket-Wendeanlage */
/******************************************************/
  printf("-Paket-Wendeanlage-\n");
  printf("Hardware-Status:\n");
  exec("SIGNAL STATE");
  printf("I/O-Status:\n");
  printf("Port4:  %x\n", PORT4);
  printf("Port5:  %x\n", PORT5);
  printf("Lichtschranke 1 %f\n", AIN0);
  printf("Lichtschranke 2 %f\n", AIN1);
}

/* Start-Taster (Paket eingelegt) */
set F3="DP_set4 (3)"
/* Start-Taster (kein Paket eingelegt) */
set F4="DP_clear4 (3)"

/* Lichtschranken-Simulation */
set F7="DP_lichtschranken()"

/* Status aller Ports der Paket-Wendeanlage */
set F8="DP_portstatus2 ()"

/* library.INC Ende */

