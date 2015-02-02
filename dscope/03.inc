/* 03.INC Start */

func void DP_portstatus()
/********************************************/
/* Status aller Ports der Paket-Wendeanlage */
/********************************************/
 {
  printf("-Paket-Wendeanlage-\n");
  printf("Hardware-Status:\n");
  exec("SIGNAL STATE");
  printf("I/O-Status:\n");
  printf(" %d, %d : M1 - Schieber-Antrieb\n",(PORT5>>1) & 0x01,PORT5 & 0x01);
  printf(" %d, %d : M2 - Antrieb der Wendestation\n",(PORT5 >>3)& 0x01,(PORT5 >>2)& 0x01);
  printf(" %d, %d : M3 - Antrieb des Transportbandes\n",(PORT5 >>5)& 0x01,(PORT5 >>4)& 0x01);
  printf(" %d, %d : M4 - Linsenlampen von beiden Lichtschranken\n",(PORT5 >>7)& 0x01,(PORT5 >>6)& 0x01);

  printf(" %d : E1 - Schieber-Eindstellung (Paket auswerfen)\n",PORT4 & 0x01);
  printf(" %d : E2 - Schieber-Endstellung (Transportband frei)\n",(PORT4 >>1)& 0x01);
  printf(" %d : E3 - Impulsscheibe am Transportband-Antrieb\n",(PORT4 >>2)& 0x01);
  printf(" %d : E4 - Ausloesekontakt fuer Rutsche\n",(PORT4 >>3)& 0x01);
  printf(" %d : E5 - Taster an der Wendestation\n",(PORT4 >>4)& 0x01);
  /*
  printf(" %d : E6 - Opt1:Fototransistor waagerecht am Transportband\n",(PORT4 >>5)& 0x01);
  printf(" %d : E7 - Opt1:Fototransistor der Reflexlichtschranke\n",(PORT4 >>6)& 0x01);
  printf(" %d : E8\n",(PORT4 >>6)& 0x01);
  */

  printf(" %f : EX - Fototransistor waagerecht am Transportband\n", AIN0);
  printf(" %f : EY - Fototransistor der Reflexlichtschranke\n", AIN1);
}

func void DP_sim0()
/*************************************************/
/* Start der Simulation der Paketwendeanlage     */
/* ***funktioniert so nicht ***                  */
/*************************************************/
 {
  float volts;
  int PV_char;
  printf("Simulation der Paketwendeanlage\n");
  exec("G 0");
 }

/* 03.INC Ende */

