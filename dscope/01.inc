/* 01.INC Start */

func void DP_tasks (int VV_alltasks)
/**********************************/
/* CREATE A STATUS FUNCTION       */
/**********************************/
 {
  uchar i;
  uint  adr;
  uint number_of_tasks;

  if (VV_alltasks)
   {
     number_of_tasks = uchar(C:?RTX_TASKIDX);
   }
  else
   {
     /* es werden nur die Tasks bis zur hoechsten gueltigen ID angezeigt */
     number_of_tasks = ?RTX_TASKIDX;
   };

  printf ("+----------+-------+---------+------------------+--------+-------+-------+\n");
  printf ("| Task ID  | Start | State   | Wait for Event   | Signal | Timer | Stack |\n");
  printf ("+----------+-------+---------+------------------+--------+-------+-------+");

  for (i = 0; i <= number_of_tasks; i++)  {
    printf ("\n|    %2d    | ", i);
    adr = &?RTX_TASKENTRY + i*2;
    printf ("%04XH | ", uint (c:adr));
    adr = &?RTX_TASKSTATUS + i*2;
    if (RTX_CURRENTTASK == i  &&
        (uchar (i:adr+1) & 0x10))     printf ("RUNNING | ");
    else if (uchar (i:adr+1) & 0x40)  printf ("TIMEOUT | ");
    else if (uchar (i:adr+1) & 0x10)  printf ("READY   | ");
    else if (uchar (i:adr+1) & 0x03)  printf ("WAITING | ");
    else if (uchar (i:adr+1) == 0)    printf ("DELETED | ");
    else                              printf ("ILLEGAL | ");

    switch (uchar (i:adr+1) & 0x03)  {
      case 0:  printf ("                "); break;
      case 1:  printf ("SIGNAL          "); break;
      case 2:  printf ("TIMEOUT         "); break;
      case 3:  printf ("SIGNAL & TIMEOUT"); break;
    }

    if (uchar (i:adr+1) & 0x04)  printf (" |    1");
    else                         printf (" |    0");
  
    printf ("   |   %3d |", uchar (i:adr));
    adr = &?RTX_TASKSP + i;
    printf ("   %02XH |", uchar (i:adr));
  }
  printf ("\n+----------+-------+---------+------------------+--------+-------+-------+\n");
}

/* 01.INC Ende */

