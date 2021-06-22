#include "stdlib.h"
#include "string.h"
#include "dos.h"
#include "conio.h"
#include "graphics.h"

void selectgraph(int gdriver,int gmode);

int grapherror;
int graphdriver,graphmode;
int vsize,hsize,vcenter,hcenter;
char drivertype[10];

void abortit(char *msg)
{
 cputs("\x0a\x0d");
 cprintf("%s: \n",msg, grapherrormsg(graphresult()));
 exit(1);
};

void selectgraph(int gdriver,int gmode)
{
int errcode,tstmax;
 graphmode = gmode;
 graphdriver = gdriver;
 if (gmode == DETECT)
   detectgraph(&graphdriver,&graphmode);
  switch (graphdriver) {
     case HERCMONO: graphmode = HERCMONOHI; break;
     case CGA     : graphmode = CGAHI; break;
     case MCGA    : graphmode = MCGAMED; break;
     case EGA64   : graphmode = EGA64HI; break;
     case EGAMONO : graphmode = EGAMONOHI; break;
     case EGA     : graphmode = EGAHI; break;
     case VGA     : graphmode = VGAHI; break;
     case ATT400  : graphmode = ATT400MED; break;
  };

 if (graphdriver == VGA || graphdriver == EGA ||
    graphdriver == EGA64 || graphdriver == EGAMONO)
    if (registerbgidriver(EGAVGA_driver) < 0)
     abortit("EGA/VGA");


 if (graphdriver == CGA || graphdriver == MCGA)
    if (registerbgidriver(CGA_driver) < 0)
     abortit("CGA");

 if (graphdriver == HERCMONO)
    if (registerbgidriver(Herc_driver) < 0)
    abortit("HERC");

 if (graphdriver == ATT400)
    if (registerbgidriver(ATT_driver) < 0)
    abortit("AT&T");


 initgraph(&graphdriver,&graphmode,"");
 errcode = graphresult();
 if (errcode != grOk)
  {
   cprintf("Initialization Graphics Error: %s",grapherrormsg(errcode));
   delay(3000);
   exit(1);
  };
 tstmax = getmaxmode();
 if (graphmode > tstmax) graphmode = tstmax;
 setgraphmode(graphmode);
 errcode = graphresult();
 if (errcode != grOk)
  {
   cprintf("Set-Graph Mode Error: %s",grapherrormsg(errcode));
   delay(3000);
   exit(1);
  };
 strcpy(drivertype,getdrivername());
 vsize = getmaxy() + 1;
 hsize = getmaxx() + 1;
 vcenter = vsize / 2;
 hcenter = hsize / 2;
};
