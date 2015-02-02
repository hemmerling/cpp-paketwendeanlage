/* 05.INC Start */

func void DP_taskswitch_msg(void) {printf ("Switch to Task %d\n", R7);}

func void DP_break00(void)
/******************************************/
/* Lichtschranken sind unbeleuchtet       */
/******************************************/
 {
   float volts;
   volts = 0x0FC * 5; AIN0 = volts / 255;
   volts = 0x0FF * 5; AIN1 = volts /255;
   printf("Lichtschranken sind unbeleuchtet\n");
   printf ("GP_break00\n");
 }

func void DP_break01(void)
/******************************************/
/* Lichtschranken sind nicht unterbrochen */
/******************************************/
 {
   float volts;
   volts = 0x0DC * 5; AIN0 = volts / 255;
   volts = 0x0FF * 5; AIN1 = volts /255;
   printf("Lichtschranken sind nicht unterbrochen\n");
   printf ("GP_break01\n");
 }

func void DP_break02(void)
/************************************/
/* Lichtschranken sind unterbrochen */
/************************************/
 {
   float volts;
   volts = 0x0FF * 5; AIN0 = volts / 255;
   volts = 0x0CD * 5; AIN1 = volts / 255;
   printf("Lichtschranken sind unterbrochen\n");
   printf ("GP_break02\n");
 }

func void DP_break03(void)
/******************************************/
/* Lichtschranken sind nicht unterbrochen */
/******************************************/
 {
   float volts;
   volts = 0x0DC * 5; AIN0 = volts / 255;
   volts = 0x0FF * 5; AIN1 = volts /255;
   printf("Lichtschranken sind nicht unterbrochen\n");
   printf ("GP_break03\n");
 }

func void DP_break10(void) { printf ("GP_break10\n");}
func void DP_break20(void) { printf ("GP_break20\n");}
func void DP_break30(void) { printf ("GP_break30\n");}
func void DP_break31(void) { printf ("GP_break31\n");}
func void DP_break32(void) { printf ("GP_break32\n");}
func void DP_break33(void) { printf ("GP_break33\n");}
func void DP_break40(void) { printf ("GP_break40\n");}
func void DP_break50(void) { printf ("GP_break50\n");}

func void DP_set_breaks(void)
/*************************************************/
/* Breakpoints setzen                            */
/*************************************************/
 {
   /* exec("BS ?RTX_NEXTTASK, 1, \"DP_taskswitch_msg()\""); */

   exec("BS GP_break00, 1, \"DP_break00()\"");
   exec("BS GP_break01, 1, \"DP_break01()\"");
   exec("BS GP_break02, 1, \"DP_break02()\"");
   exec("BS GP_break03, 1, \"DP_break03()\"");

   exec("BS GP_break10, 1, \"DP_break10()\"");
   exec("BS GP_break20, 1, \"DP_break20()\"");
   exec("BS GP_break30, 1, \"DP_break30()\"");
   exec("BS GP_break31, 1, \"DP_break31()\"");
   exec("BS GP_break32, 1, \"DP_break32()\"");
   exec("BS GP_break33, 1, \"DP_break33()\"");
   exec("BS GP_break40, 1, \"DP_break40()\"");
   exec("BS GP_break50, 1, \"DP_break50()\"");

 }

/* Breakpoints setzen */
DP_set_breaks()

/* 05.INC Ende */

