/* Start 1.inc */

func void tasks ()  {
  uchar i;
  uint  adr;

  printf ("ีออออออออออัอออออออัอออออออออัออออออออออออออออออัออออออออัอออออออัอออออออธ\n");
  printf ("ณ Task ID  ณ Start ณ State   ณ Wait for Event   ณ Signal ณ Timer ณ Stack ณ\n");
  printf ("ฦออออออออออุอออออออุอออออออออุออออออออออออออออออุออออออออุอออออออุอออออออต\n");

  for (i = 0; i <= ?RTX_TASKIDX; i++)  {
    printf ("ณ    %2d    ณ ", i);
    adr = &?RTX_TASKENTRY + i*2;
    printf ("%04XH ณ ", uint (c:adr));
    adr = &?RTX_TASKSTATUS + i*2;
    if (RTX_CURRENTTASK == i  &&
        (uchar (i:adr+1) & 0x10))     printf ("RUNNING ณ ");
    else if (uchar (i:adr+1) & 0x40)  printf ("TIMEOUT ณ ");
    else if (uchar (i:adr+1) & 0x10)  printf ("READY   ณ ");
    else if (uchar (i:adr+1) & 0x03)  printf ("WAITING ณ ");
    else if (uchar (i:adr+1) == 0)    printf ("DELETED ณ ");
    else                              printf ("ILLEGAL ณ ");

    switch (uchar (i:adr+1) & 0x03)  {
      case 0:  printf ("                "); break;
      case 1:  printf ("SIGNAL          "); break;
      case 2:  printf ("TIMEOUT         "); break;
      case 3:  printf ("SIGNAL & TIMEOUT"); break;
    }

    if (uchar (i:adr+1) & 0x04)  printf (" ณ    1");
    else                         printf (" ณ    0");
  
    printf ("   ณ   %3d ณ", uchar (i:adr));
    adr = &?RTX_TASKSP + i;
    printf ("   %02XH ณ", uchar (i:adr));
    printf ("\n");
  }
  printf ("ิออออออออออฯอออออออฯอออออออออฯออออออออออออออออออฯออออออออฯอออออออฯอออออออพ\n");
}

set f3 = "tasks ()"
bs ?RTX_NEXTTASK, 1, "printf (\"Switch to Task %d\\n\", R7)"

/* Ende 1.inc */

