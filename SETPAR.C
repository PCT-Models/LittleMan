/* assume in graphics mode for setting parameters */

#include "conio.h"
#include "stdio.h"
#include "stdlib.h"
#include "speccode.h"
#include "graphics.h"
#include "math.h"
#include "string.h"

#define leading 10

static char terminator;
static int chhigh,chwide;
static char instr[21];
static char outstr[21];
static float ftempvar;
static int   itempvar;
static int   stempvar;
static FILE *paramfile;

extern int
	ghx,ghy,  /* head gains */
    g3e,g3a,g3d,  /* visual gains */
    d3e,d3a,d3d,  /* visual derivatives (phase advance) */
    test1,test2,test3,testnum; /* test in progress */

extern float
	I1,I2,loopgain0,loopgain1,loopgain2,
	kg0,kt0,kd0,ko0,ks0,
	kg1,kt1,kd1,ko1,ks1,
	kg2,kt2,kd2,ko2,ks2;

extern int gs0,is0,gs1,is1,gs2,is2,c1a,c1b,testnum;

extern int hcenter,vcenter,hsize,vsize;
extern void showfloat(char *s,int x,int y,float n);

unsigned char getcod(void);

void saveparams(void *params,
		       int nparams,
		       char kind);


void showparams(void *paramlist,
		int numparams,
		int xloc,
		int yloc,
		int width,
		int decimals,
		char kind);

char setparams(void *paramlist,
	       int numparams,
	       int xloc,
	       int yloc,
	       int width,
	       int decimals,
	       char kind);

void getparams(void *paramlist,
	       int num,
	       char kind)
{
float *flist;   /* floating, kinesthetic list */
int   *ilist;   /* integer, visual list */
int   *slist;   /* integer, brainstem list */

 if(kind == 'i')
 {
  ilist = paramlist;
  paramfile = fopen("vparams","rb");
  if( !paramfile)
  {
   ilist[0] = 20;
   ilist[1] = 20;
   ilist[2] = 60;
   ilist[3] = 60;
   ilist[4] = 60;
   ilist[5] = 100;
   ilist[6] = 100;
   ilist[7] = 100;
   paramfile = fopen("vparams","wb");
   fwrite(ilist,num*sizeof(int),1,paramfile);
  }
  else fread(ilist,num*sizeof(int),1,paramfile);
  fclose(paramfile);
  ghx = ilist[0];
  ghy = ilist[1];
  g3e = ilist[2];
  g3a = ilist[3];
  g3d = ilist[4];
  d3e = ilist[5];
  d3a = ilist[6];
  d3d = ilist[7];
 }
 else if(kind == 's')
 {
  slist = paramlist;
  paramfile = fopen("sparams","rb");
  if( !paramfile)
  {
   slist[0] = 10;    /* gain */
   slist[1] = 50;    /* integral */
   slist[2] = 10;
   slist[3] = 50;
   slist[4] = 10;
   slist[5] = 50;
   paramfile = fopen("sparams","wb");
   fwrite(slist,num*sizeof(int),1,paramfile);
  }
  else fread(slist,num*sizeof(int),1,paramfile);
  fclose(paramfile);
  gs0 = slist[0];
  is0 = slist[1];
  gs1 = slist[2];
  is1 = slist[3];
  gs2 = slist[4];
  is2 = slist[5];
  if(c1a < 100) c1a = 100;
  if(c1b < 100) c1b = 100;
 }
 else
 {
   flist = paramlist;
   paramfile = fopen("kparams","rb");
   if( !paramfile)
  {
   flist[0] = 3.0;
   flist[1] = 1.0;
   flist[2] = 0.01;
   flist[3] = 1.0;
   flist[4] = 300.0;
   flist[5] = 3.0;
   flist[6] = 1.0;
   flist[7] = 0.01;
   flist[8] = 1.0;
   flist[9] = 200;
   flist[10] = 3.0;
   flist[11] = 1.0;
   flist[12] = 0.005;
   flist[13] = 1.0;
   flist[14] = 50.0;
   paramfile = fopen("kparams","wb");
   fwrite(flist,num*sizeof(float),1,paramfile);
  }
  else fread(flist,num*sizeof(float),1,paramfile);
  fclose(paramfile);
  kg0 = flist[0];
  kt0 = flist[1];
  kd0 = flist[2];
  ko0 = flist[3];
  ks0 = flist[4];
  kg1 = flist[5];
  kt1 = flist[6];
  kd1 = flist[7];
  ko1 = flist[8];
  ks1 = flist[9];
  kg2 = flist[10];
  kt2 = flist[11];
  kd2 = flist[12];
  ko2 = flist[13];
  ks2 = flist[14];
 }
};

void saveparams(void *paramlist,
		int num,
		char kind)
{
float *flist;
int   *ilist;
int   *slist;

 if(kind == 'i')
  {
   ilist = paramlist;
   paramfile = fopen("vparams","wb");
   fwrite(ilist,num*sizeof(int),1,paramfile);
  }
  else if(kind == 's')
  {
   slist = paramlist;
   paramfile = fopen("sparams","wb");
   fwrite(slist,num*sizeof(int),1,paramfile);
  }
  else
  {
   flist = paramlist;
   paramfile = fopen("kparams","wb");
   fwrite(flist,num*sizeof(float),1,paramfile);
  }
 fclose(paramfile);
};

unsigned char getcod()
{
unsigned char ch;
 ch = getch();
 if(ch == 0) ch = getch() | 0x80;
 return ch;
}

char readnumstr(char *instr,
		int xloc,
		int yloc,
		int width,
		int decimals,
		char kind)
{
int i;
int done;
char ch;
char format[20];
char strform[10];
 strform[0] = '%';
 sprintf(&strform[1],"%d",width);
 strcat(strform,"s");
 format[0] = '%';
 if(kind == 'f')
 {
  sprintf(&format[1],"%d.%d",width,decimals);
  strcat(format,"f");
 }
 else
  {
   sprintf(&format[1],"%d",width);
   strcat(format,"i");
  }
 i = 0;
 do
 {
  ch = getcod();
  done = (ch == 0x0d || ch == Up || ch == Down || ch == EndKey);
  if(!done )
   {
    if(ch == 8 && i > 0) instr[--i] = '\0';
    else
    if( (ch >= '0' && ch <= '9') || ch == '.' || ch == '+' || ch == '-')
    {
     instr[i++] = ch;
     if(i > width) --i;
     instr[i] = '\0';
    }
    bar(xloc,yloc,xloc + width*chwide,yloc + chhigh);
    sprintf(outstr,strform,instr);
    outtextxy(xloc,yloc,outstr);
   }

 }
 while (!done);
 if(strlen(instr))
 {
   bar(xloc,yloc,xloc + width*chwide,yloc + chhigh);
   if(kind == 'f')
   sprintf(outstr,format,(ftempvar = atof(instr)));
   else if(kind == 's')
   sprintf(outstr,format,(stempvar = atoi(instr)));
   else
   sprintf(outstr,format,(itempvar = atoi(instr)));
   outtextxy(xloc,yloc,outstr);
 }
 return ch;                /* return terminating keystroke */
};

void setlegends(char *legendlist[], int numleg, int xloc, int yloc)
{
int i;
 settextjustify(LEFT_TEXT,TOP_TEXT);
 settextstyle(0,HORIZ_DIR,1);
 for(i=0;i<numleg;++i)
   outtextxy(xloc,yloc+leading*i,legendlist[i]);
}

void showparams( void *paramlist,
		int numparams,
		int xloc,
		int yloc,
		int width,
		int decimals,
		char kind)
{
int i;
char format[20];
float *flist;
int   *ilist;
int   *slist;
 format[0] = '%';
 if (kind == 'f')
 {
  flist = paramlist;
  sprintf(&format[1],"%d.%d",width,decimals);
  strcat(format,"f");
 }
 else if(kind == 's')
 {
  slist = paramlist;
  sprintf(&format[1],"%d",width);
  strcat(format,"i");
 }
 else
 {
  ilist = paramlist;
  sprintf(&format[1],"%d",width);
  strcat(format,"i");
 }
 for(i=0;i<numparams;++i)
 {
  bar(xloc,yloc + leading*i,xloc + width*chwide,yloc + chhigh + leading*i);
  if (kind == 'f')
  sprintf(outstr,format,flist[i]);
  else if(kind == 's')
  sprintf(outstr,format,slist[i]);
  else
  sprintf(outstr,format,ilist[i]);
  outtextxy(xloc,yloc + leading*i,outstr);
 }
}


char setparams(void *paramlist,
	       int numparams,
	       int xloc,
	       int yloc,
	       int width,
	       int decimals,
	       char kind)
{
static int lineptr = 0;
float *flist;
int   *ilist;
int   *slist;
int toplim,botlim;
 if(test1)
 {
  if(testnum == 0) {botlim = 0; toplim = 5;}
  if(testnum == 1) {botlim = 5; toplim = 10;}
  if(testnum == 2) {botlim = 10; toplim = 15;}
 }
 else {botlim = 0; toplim = numparams;}

 if(lineptr >= toplim) lineptr = botlim;
 if(lineptr < botlim) lineptr = toplim - 1;
 if(kind == 'f')
  flist = paramlist;
 else if(kind == 's')
  slist = paramlist;
 else
  ilist = paramlist;
 settextjustify(LEFT_TEXT,TOP_TEXT);
 settextstyle(0,HORIZ_DIR,1);
 chhigh = textheight("8"); chwide = textwidth("8");
 setfillstyle(0,0);
 showparams(paramlist,numparams,xloc,yloc,width,decimals,kind);
 do
 {
  moveto(xloc - 10,yloc + leading*lineptr);
  outtext(">");
  if(kind == 'f')
   ftempvar = flist[lineptr];
  else if(kind == 's')
   stempvar = slist[lineptr];
  else
   itempvar = ilist[lineptr];
  instr[0] = '\0';
  terminator = readnumstr(instr,xloc,yloc + leading*lineptr,width,decimals,kind);
  moveto(xloc - 10,yloc + leading*lineptr);
  bar(xloc-10,yloc + leading*lineptr,xloc,yloc+chhigh + leading*lineptr);
  if(strlen(instr))
   if(kind == 'f')
    flist[lineptr] = ftempvar;
   else if(kind == 's')
    slist[lineptr] = stempvar;
   else
    ilist[lineptr] = itempvar;
  switch(terminator)
   {
    case Down: ++lineptr; if(lineptr >= toplim) lineptr = botlim; break;
    case   Up: --lineptr; if(lineptr < botlim) lineptr = toplim - 1; break;
   }
  if(kind == 'f')
  { kg0 = flist[0];
    kt0 = flist[1];
    kd0 = flist[2];
    ko0 = flist[3];
    ks0 = flist[4];
    kg1 = flist[5];
    kt1 = flist[6];
    kd1 = flist[7];
    ko1 = flist[8];
    ks1 = flist[9];
    kg2 = flist[10];
    kt2 = flist[11];
    kd2 = flist[12];
    ko2 = flist[13];
    ks2 = flist[14];
    loopgain0 = kt0*ko0*ks0;
    loopgain1 = kt1*ko1*ks1;
    loopgain2 = kt2*ko2*ks2;

    switch(testnum)
    {
     case 0: showfloat("Loopgain 0    =",hcenter/3,vsize - 20,loopgain0);
	     showfloat("Static gain 0 = ",hcenter/3,vsize - 10,
			(kg0/(1+1e-10)+kt0+1.0/(ko0*kt0 +1e-10)));
	     break;
     case 1: showfloat("Loopgain 1 =",hcenter/3,vsize - 20,loopgain1);
	     showfloat("Static gain 1 = ",hcenter/3,vsize - 10,
			(kg1/kt1+1.0/(ko1*kt1 +1e-10)));
	     break;
     case 2: showfloat("Loopgain 2 =",hcenter/3,vsize - 20,loopgain2);
	     showfloat("Static gain 2= ",hcenter/3,vsize - 10,
			(kg2/kt2+1.0/(ko2*kt2 +1e-10)));
	     break;
     }
  }
 }
 while(terminator != 0x0d && terminator != EndKey);
 if (kind == 'f')
  saveparams(flist,numparams,'f');
 else if(kind == 's')
  saveparams(slist,numparams,'s');
 else
  saveparams(ilist,numparams,'i');

 if (kind == 'f')
  getparams(flist,numparams,'f');
 else if(kind == 's')
  getparams(slist,numparams,'s');
 else
  getparams(ilist,numparams,'i');

 return terminator;
};

