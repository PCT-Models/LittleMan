#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#include "stdlib.h"
#include "stdio.h"
#include "conio.h"
#include "string.h"
#include "math.h"
#include "dos.h"
#include "graphics.h"
#include "memory.h"
//#include "alloc.h"
#include "speccode.h"   /* included in distribution file */

/*program arm2.c*/
 /* Version 1.0 with diagram, May 26, 1989 */
 /* revised with new graphics routines, Feb. 28, 1990 */
 /* Version 1.1; full dynamics unit added, Oct.1, 1990 */
 /* Version 1.2; arm dynamics parameter adjustment, Nov 4,1990 */
 /* Version 1.3; converted to C, Oct.24-Nov 15, 1991 */
 /*  note: will not correspond exactly to writeup on distribution disk */
 /* Version 2.0 dynamical model with visual-kinesthetic map, Apr. 11, 1990 */
 /* V 2.1 Adaptive Map control added, July 1992 */
 /* System and level designations made rational Sept. 9, 1992 */
 /* Map feature removed, simplified for distribution May 9, 1997 */
 /* added adaptive timing for fast computers April 12, 1999 WTP */

 /* ANGLES ARE MEASURED AS 0-4095 INTEGER ANGLE UNITS */

#define NEW 1
#define NOTNEW 0
#define pi 3.141592654
#define FALSE 0
#define TRUE -1
#define anglerange 4096
#define one80 2048
#define three4pi ((one80 + one80 + one80) / 2)
#define rightangle  (one80 / 2)
#define maxmin1 (one80 - 1)
#define crlf cputs("\x0a\x0d")

#ifndef numkparams
#define numkparams 15
#endif
#ifndef numvparams
#define numvparams 8
#endif
#ifndef numsparams
#define numsparams 6
#endif

extern int graphmode;
extern int muldiv(int m1, int m2, int d);
extern int vcenter,hcenter,vsize,hsize;
extern void selectgraph(int driver, int mode);


extern float kparams[];   /* arm parameters */
extern float dt,torque0,torque1,torque2;
extern int gravity;
extern int mark;

void maketarget(void);
void correct(int xadr,int yadr,int radr,int xin,int yin,int rin);


extern void setgravity(void);
extern int muldiv(int m1, int m2, int m3);
extern void getparams(void *paramlist,int num,char kind);
extern void makeconstants(void);
extern void initdynam(void);
extern void showangles(int a1,int a2,int a3);
extern void showcontrol(int level,int which);
extern void showfloat(char *s, int x, int y, float n);
void showint(char *title, int x, int y, int num);
extern void saveparams(void *params,
		       int nparams,
		       char kind);

extern void setlegends(char *klegends[],
		       int numlegends,
		       int xloc,
		       int yloc);

extern void setparams(void *kparams,
		      int nparams,
		      int xloc,
		      int yloc,
		      int width,
		      int decimals,
		      char kind);

char *klegends[] = {
		       "Shoulder X, Kg, stretch",
		       "            Kt, tension",
		       "            Kd, damping",
		       "            Ko, output ",
		       "            Ks, spring ",
		       "Shoulder Y, Kg, stretch",
		       "            Kt, tension",
		       "            Kd, damping",
		       "            Ko, output ",
		       "            Ks, spring ",
		       "Elbow,      Kg, stretch",
		       "            Kt, tension",
		       "            Kd, damping",
		       "            Ko, output ",
		       "            Ks, spring ",
		       };
char *vlegends[] = {
		       "head gain,  x",
		       "head gain,  y",
		       "visual gain,y",
		       "visual gain,x",
		       "visual gain,z",
		       "visual lead,y",
		       "visual lead,x",
		       "visual lead,z",
		       };

char *slegends[] = {
		       "kin 2, prop,x",
		       "   integral,x",
		       "kin 2, prop,y",
		       "   integral,y",
		       "kin 2  prop,z",
		       "   integral,z",
		       };
void switchtarg(void);
void showstatus(void);
void arminit(void);
void makesincos(void);
unsigned char getnumstr(int n, int l);
void armcont(int *az,int *t1,int * t2,int o3a,int o3e,int o3d);
void getfunctions(void);
void makecube(void);
void makebody(void);
void makehead(void);
void makelefteye(void);
void makerighteye(void);
void seteyes(void);
void environment(void);
void filldiagram(void);
void  distance3(void);
void  vertical3(void);
void  azimuth3(void);
void  link3to2(void);
void  gaze1xr(void);
void  gaze1xl(void);
void  gaze1y(void);
void  link2to1(void);
unsigned char getcod(void);
void redraw(int new1);
void showhelp(void);

typedef struct {int x2d,y2d;} xytype[50];
typedef struct {int x3d,y3d,z3d;} polytype3d[75];

typedef union {
		 xytype xy;
		 int a[100];
		} polytype2d;

typedef int sincostype[anglerange];
typedef int invtantype[4096];

static int halfside,       /* half of one side of box */
    rf,             /* radius, shoulder to finger */
    FIx,            /* x position of finger */
    FIy,            /* y position of finger */
    FIz,            /* z position of finger */
    TAx,            /* x position of target */
    TAy,            /* y position of target */
    TAz,            /* z position of target */
    REx,            /* right eye x coordinate */
    REy,            /* right eye y coordinate */
    REz,            /* right eye z coordinate */
    LEx,            /* left eye x coordinate */
    LEy,            /* left eye y coordinate */
    LEz,            /* left eye z coordinate */
    RExr,            /* right eye rotated x coordinate */
    REyr,            /* right eye rotated y coordinate */
    REzr,            /* right eye rotated z coordinate */
    LExr,            /* left eye rotated x coordinate */
    LEyr,            /* left eye rotated y coordinate */
    LEzr,            /* left eye rotated z coordinate */
    ELx,            /* x coordinate of elbow */
    ELy,            /* y coordinate of elbow */
    ELz,            /* z coordinate of elbow */
    SHx,            /* x coordinate of shoulder */
    SHy,            /* y coordinate of shoulder */
    SHz,            /* z coordinate of shoulder */
    ra1,             /* length of upper arm */
    rb1,             /* length of lower arm */
    t1,             /* angle from nadir to upper arm */
    t2,             /* angle from projection of upper arm to lower arm */
    t3,             /* angle from shoulder to finger */
    az,             /* azimuth angle of arm */
    TLRd,           /* tan depth angle to target */
    FLRd,           /* tan depth angle to finger */

    TRx,            /* azimuth angle, right eye to target */
    TLx,            /* azimuth angle, left  eye to target */
    FRx,            /* azimuth angle, right eye to finger */
    FLx,            /* azimuth angle, left  eye to finger */

    TRy,            /* vertical angle, right eye to target */
    TLy,            /* vertical angle, left  eye to target */
    FRy,            /* vertical angle, right eye to finger */
    FLy,            /* vertical angle, left  eye to finger */

/*    la,   */          /* lateral angle, right eye gaze to target */

    TXL,TYL,TZL,FXL,FYL,FZL,   /* positions relative to eyes */
    TXR,TYR,TZR,FXR,FYR,FZR;


int pf,                       /* angle from horizontal eyes to finger */
    temp,at1,at3,az1;

int    p2e,p2a,p2d,p2dl,p2dr,p1e,e2e,e2a,
    e2d,e2dl,e2dr,e1e,o2e,o2a,o2d,o2dl,o2dr,
    o1e,r2e,r2a,r2d,r2dl,r2dr,r1e,            /* lower order control */
    p3e,p3a,p3d,e3e,e3a,e3d,
    o3e,o3a,o3d,r3e,r3a,r3d;            /* higher order control */

int ghx,ghy,  /* head gains */
    g3e,g3a,g3d,  /* visual gains */
    d3e,d3a,d3d;  /* visual derivatives (phase advance) */

int gs0,is0,gs1,is1,gs2,is2,c1a,c1b;

int eyetot,eyetof;
int distort;

int i1a = 0,i1b = 0,i1c = 0,
    i2dl = 2000,i2dr = -1634,
    i1e = -4667,i3e = 0,i3a = 0,i3d = 0;

int vparams[numvparams];
int sparams[numsparams];
int errlim;
int scale = 4096;
int trace = 0;
int count = 0;
char cstr[10];

FILE *paramfile;
FILE *helpfile;

static int x,y,z,xp,yp,zp,yasp,xasp;
static char ch;
unsigned char byte;

polytype3d cube3,body3,head3,head3r,lefteye3,lefteye3r,righteye3,righteye3r,arm3,target3;
polytype2d cube2,body2,head2,lefteye2,righteye2,arm2,target2;

int    theta,phi,gazex,gazexle,gazexre,gazey,phi2,theta2,phi2le,phi2re,d,headwidth,headheight,neck,eyesize;

int        v1[3],v2[3];

unsigned char cmd;

sincostype sine,cosine;
invtantype invtan;
FILE *invtanfile;
FILE *sincosfile;

int       top,middle,bottom;
int       xa,ya;
unsigned  time;
int       interval;
FILE     *Driver;
void     *DriverP;
int       handle,
	  delta;
int       tempt,
	  pr,pt,pp,
	  purpose,
	  track,
	  framemoved,
          statuschange,
	  test1 = 0,
	  test2 = 0,
	  test3 = 0,
	  test4 = 0,
	  testnum,
	  testt0 = 100,
	  testt1 = 100,
	  testt2 = 100,
	  moving = 0,
	  timer = 100,
	  movex = 0,
	  movey = 0,
	  movez = 0,
          dist = 100,
          visual = -1;

struct {
	int x,y,z;
       } targ1,targ2;
int seektarg1 = 0;

long tt,tcount = 10000L, clocktime;
int timercount,dcount;
struct time newtime,oldtime;


void showhelp(){
 int inch;
 restorecrtmode(); //clrscr();
 rewind(helpfile);
 inch = getc(helpfile);
 while (inch != EOF)
 {
  printf("%c",inch);
  inch = getc(helpfile);
 }
 (void) getch();
 setgraphmode(graphmode);
 clearviewport();
 setwritemode(1);
 framemoved = TRUE;
 redraw(NEW);
}

void switchtarg(){
 seektarg1 = !seektarg1;
  if(seektarg1)
   {
    TAx = targ1.x;
    TAy = targ1.y;
    TAz = targ1.z;
   }
  else
   {
    TAx = targ2.x;
    TAy = targ2.y;
    TAz = targ2.z;
   }
}

void showstatus(){
 setfillstyle(0,0);
 moveto(hsize-130,24);
 bar(hsize - 130,24,hsize-1,34);
 outtext("GRAVITY ");
 if(gravity) outtext("ON"); else outtext("OFF");
 moveto(hsize-130,36);
 bar(hsize - 130,36,hsize-1,46);
  if(test1) outtext("KIN TEST 1");
  else if(test2) outtext("KIN TEST 2");
  else if(test3) outtext("ALT POSITIONS");
  else if(test4) outtext("RAND POSITIONS");
  else outtext("MANUAL OPERATION");
 outtextxy(hcenter,vsize - 50,"q to quit program");
 outtextxy(hcenter,vsize - 35,"? for help");
}

void filldiagram(){

 textattr(0x70);
 gotoxy(4,1); cprintf("%5d",TAx);
 gotoxy(4,2); cprintf("%5d",TAy);
 gotoxy(4,3); cprintf("%5d",TAz);
 gotoxy(16,1); cprintf("%5d",FIx);
 gotoxy(16,2); cprintf("%5d",FIy);
 gotoxy(16,3); cprintf("%5d",FIz);

 gotoxy(32,5); cprintf("%4d",r3a);
 gotoxy(22,8); cprintf("%5d",p3a);
 gotoxy(28,8); cprintf("%5d",e3a);
 gotoxy(34,8); cprintf("%5d",o3a);

 gotoxy(42,4); cprintf("%5d",p3d);
 gotoxy(48,4); cprintf("%5d",e3d);
 gotoxy(54,4); cprintf("%5d",o3d);

 gotoxy(72,5); cprintf("%4d",r3e);
 gotoxy(62,8); cprintf("%5d",p3e);
 gotoxy(68,8); cprintf("%5d",e3e);
 gotoxy(74,8); cprintf("%5d",o3e);

 gotoxy(22,21); cprintf("%5d",az);
 gotoxy(28,21); cprintf("%5d",e2a);
 gotoxy(34,21); cprintf("%5.1f",torque0);
 gotoxy(42,21); cprintf("%5d",t2);
 gotoxy(48,21); cprintf("%5d",e2d);
 gotoxy(54,21); cprintf("%5.1f",torque2);
 gotoxy(62,21); cprintf("%5d",t1);
 gotoxy(68,21); cprintf("%5d",e2e);
 gotoxy(74,21); cprintf("%5.1f",torque1);
 gotoxy( 2,18); cprintf("%5d",p1e);
 gotoxy( 8,18); cprintf("%5d",e1e);
 gotoxy(14,18); cprintf("%5d",o1e);
 gotoxy( 2,12); cprintf("%5d",(p2dl+p2dr)/2);
 gotoxy( 8,12); cprintf("%5d",(e2dl+e2dr)/2);
 gotoxy(14,12); cprintf("%5d",(o2dl+o2dr)/2);
 gotoxy(30,17); cprintf("%5d",r2a);
 gotoxy(50,17); cprintf("%5d",r2d);
 gotoxy(70,17); cprintf("%5d",r2e);
 textattr(0x0f);
 delay(100);
};

void showint(char *title, int x, int y, int num){
char numstr[25];
char titlestr[50];
 strcpy(titlestr,title);
 (void) itoa(num,numstr,10);
 strcat(titlestr,numstr);
 bar(x,y,x+textwidth(titlestr)+30,y+10);
 outtextxy(x,y,titlestr);
}

void makesincos(){
int i;
double u,v;
clrscr(); crlf; crlf; cputs(
"   Trigonometric tables not found: creating SINCOS && INVTAN\x0a\x0d");
 for(i = 0; i < anglerange; ++i)
 {
  u = scale * cos((i - 2048) * pi/one80);
  v = scale * sin((i - 2048) * pi/one80);
  cosine[i] = u;
  sine[i] = v;
 };
 for(i = 0; i < scale; ++i)
  invtan[i] = one80/pi*atan(1.0*i/scale);
};

void getfunctions(){
 sincosfile = fopen("sincos","rb");
 if(!sincosfile)
  {
   makesincos();
   sincosfile = fopen("sincos","wb");
   fwrite(sine,sizeof(sincostype),1,sincosfile);
   fwrite(cosine,sizeof(sincostype),1,sincosfile);
   fclose(sincosfile);
  }
 else
  {
   fread(sine,sizeof(sincostype),1,sincosfile);
   fread(cosine,sizeof(sincostype),1,sincosfile);
   fclose(sincosfile);
  };
invtanfile = fopen("invtan","rb");
 if( !invtanfile)
  {
   invtanfile = fopen("invtan","wb");
   fwrite(invtan,sizeof(invtantype),1,invtanfile);
   fclose(invtanfile);
  }
 else
  {
   fread(invtan,sizeof(invtantype),1,invtanfile);
   fclose(invtanfile);
  };
};

int findangle(int x,int y)   /* integer arc-tangent */{
int u,v,theta;
 u = abs(x); v = abs(y);
 if( v <= u) theta = invtan[muldiv(scale,v,u)];
    else theta = rightangle - invtan[muldiv(scale,u,v)];
 if( x < 0) theta = one80 - theta;
 if( y < 0) theta = - theta;
 return theta;
};

void rotateview(polytype3d *poly1,         /* rotate from head3 or eyes3 */
		polytype3d *poly2,         /* to head3r or eyes3r */
		int n,
		int theta2,
		int phi2,
		int x0,                 /* center of rotation */
		int y0,
		int z0){
int i,ca,sa;
 for(i = 0; i < n; ++i)
  {
   x = (*poly1)[i].x3d - x0;
   y = (*poly1)[i].y3d - y0;
   z = (*poly1)[i].z3d - z0;
   ca = cosine[2048+theta2]; sa = sine[2048+theta2];
   yp = muldiv(ca,y,scale) + muldiv(sa,z,scale);
   zp = -muldiv(sa,y,scale) + muldiv(ca,z,scale);
   y = yp; z = zp;
   ca = cosine[2048+phi2]; sa = sine[2048+phi2];
   xp = muldiv(ca,x,scale) + muldiv(sa,z,scale);
   zp = -muldiv(sa,x,scale) + muldiv(ca,z,scale);
   (*poly2)[i].x3d = xp + x0;
   (*poly2)[i].y3d = yp + y0;
   (*poly2)[i].z3d = zp + z0;
  };
};

void projectxy(polytype3d *poly1,
	       polytype2d *poly2d,
	       int  n, int theta, int phi,int d){
int        i,ca,sa;
int        x0,y0;
polytype3d p1;

 if( theta < -one80) theta = theta + one80 + one80;
 if( theta >= one80) theta = theta - one80 - one80;
 x0 = (hcenter + hcenter + hcenter) / 2;
 y0 = vcenter - (vsize >> 5);
 for(i = 0; i < n; ++i)
  {
   x = (*poly1)[i].x3d;
   y = (*poly1)[i].y3d;
   z = (*poly1)[i].z3d;

   ca = cosine[2048+phi]; sa = sine[2048+phi];
   xp = muldiv(ca,x,scale) + muldiv(sa,z,scale);
   zp = -muldiv(sa,x,scale) + muldiv(ca,z,scale);

   x = xp; z = zp;

   ca = cosine[2048+theta]; sa = sine[2048+theta];
   yp = muldiv(ca,y,scale) + muldiv(sa,z,scale);
   zp = -muldiv(sa,y,scale) + muldiv(ca,z,scale);

   p1[i].x3d = xp;
   p1[i].y3d = yp;
   p1[i].z3d = zp + d;
   if((p1[i].z3d != -500))
    {
     poly2d->xy[i].x2d = x0 + muldiv(muldiv(p1[i].x3d,yasp,xasp),
		      500,(500 + p1[i].z3d));
     poly2d->xy[i].y2d = y0 - muldiv(p1[i].y3d,500,(500 + p1[i].z3d));
    };
  };
};

void rotateimage(int *Ax,
		 int *Ay,   /* visual angles, pointer to results*/
		 int Vx,
		 int Vy,
		 int Vz,   /* coordinates, finger or target*/
		 int th2,
		 int ph2)  /* theta: x axis, phi: y axis*/
{
int sa,ca,y,z,xp,yp,zp;
 x = Vx;
 y = Vy;
 z = Vz;

 ca = cosine[2048-th2]; sa = sine[2048-th2];

 yp =  muldiv(y,ca,scale) + muldiv(z,sa,scale);
 zp = -muldiv(y,sa,scale) + muldiv(z,ca,scale);

 y = yp; z = zp;

 ca = cosine[2048-ph2]; sa = sine[2048-ph2];

 xp=  muldiv(x,ca,scale) + muldiv(z,sa,scale);
 zp = -muldiv(x,sa,scale) + muldiv(z,ca,scale);
 x = xp; z = zp;

 *Ax = findangle(z,x);
 *Ay = findangle(z,y);
};



void makecube(){
polytype3d *polyg;
int i;
 i = 0;
 polyg = &cube3;

(*polyg)[i].x3d = -halfside;
(*polyg)[i].y3d = -halfside;
(*polyg)[i++].z3d = -halfside;
(*polyg)[i].x3d = -halfside;
(*polyg)[i].y3d =  halfside;
(*polyg)[i++].z3d = -halfside;
(*polyg)[i].x3d =  halfside;
(*polyg)[i].y3d =  halfside;
(*polyg)[i++].z3d = -halfside;
(*polyg)[i].x3d =  halfside;
(*polyg)[i].y3d = -halfside;
(*polyg)[i++].z3d = -halfside;
(*polyg)[i].x3d = -halfside;
(*polyg)[i].y3d = -halfside;
(*polyg)[i++].z3d = -halfside;
(*polyg)[i].x3d = -halfside;
(*polyg)[i].y3d = -halfside;
(*polyg)[i++].z3d = -halfside;
(*polyg)[i].x3d = -halfside;
(*polyg)[i].y3d = -halfside;
(*polyg)[i++].z3d =  halfside;
(*polyg)[i].x3d = -halfside;
(*polyg)[i].y3d =  halfside;
(*polyg)[i++].z3d =  halfside;
(*polyg)[i].x3d =  halfside;
(*polyg)[i].y3d =  halfside;
(*polyg)[i++].z3d =  halfside;
(*polyg)[i].x3d =  halfside;
(*polyg)[i].y3d = -halfside;
(*polyg)[i++].z3d =  halfside;
(*polyg)[i].x3d =  halfside;
(*polyg)[i].y3d = -halfside;
(*polyg)[i].z3d = -halfside;
};

void makebody(){
polytype3d *polyg;
int        du,i;

 polyg = &body3;
 i = 0;

 du = headwidth / 2;
(*polyg)[i].x3d =    0;
(*polyg)[i].y3d =    0;
(*polyg)[i++].z3d = -halfside;

(*polyg)[i].x3d =  -SHx;
(*polyg)[i].y3d =    0;
(*polyg)[i++].z3d = -halfside;

(*polyg)[i].x3d =    0;
(*polyg)[i].y3d = -halfside;
(*polyg)[i++].z3d = -halfside;

(*polyg)[i].x3d =   SHx;
(*polyg)[i].y3d =    0;
(*polyg)[i++].z3d = -halfside;

(*polyg)[i].x3d =    0;
(*polyg)[i].y3d =    0;
(*polyg)[i++].z3d = -halfside;

(*polyg)[i].x3d =    0;
(*polyg)[i].y3d =   0;
(*polyg)[i++].z3d = -halfside;

(*polyg)[i].x3d =    0;
(*polyg)[i].y3d =  du;
(*polyg)[i++].z3d = -halfside;

};

void makehead(){
polytype3d *polyg;
int        du,dv,i;

 du = headwidth / 2;
 dv = headheight;
 polyg = &head3;

 i = 0;

(*polyg)[i].x3d =    0;
(*polyg)[i].y3d =  neck;
(*polyg)[i++].z3d = -halfside ;
(*polyg)[i].x3d =   du;
(*polyg)[i].y3d =  neck;
(*polyg)[i++].z3d = -halfside ;
(*polyg)[i].x3d =   du;
(*polyg)[i].y3d =  neck + dv;
(*polyg)[i++].z3d = -halfside ;
(*polyg)[i].x3d =  -du;
(*polyg)[i].y3d =  neck + dv;
(*polyg)[i++].z3d = -halfside ;
(*polyg)[i].x3d =  -du;
(*polyg)[i].y3d =  neck;
(*polyg)[i++].z3d = -halfside ;
(*polyg)[i].x3d =    0;
(*polyg)[i].y3d =  neck;
(*polyg)[i].z3d = -halfside ;
};

void makelefteye(){
polytype3d *polyg;
int        e,i;

 e = eyesize / 2;
 i = 0;
 polyg = &lefteye3;

 (*polyg)[i].x3d =  LEx - e;
 (*polyg)[i].y3d =  LEy - e;
 (*polyg)[i++].z3d = LEz;

 (*polyg)[i].x3d =  LEx - e;
 (*polyg)[i].y3d =  LEy + e;
 (*polyg)[i++].z3d = LEz;

 (*polyg)[i].x3d =  LEx + e;
 (*polyg)[i].y3d =  LEy + e;
 (*polyg)[i++].z3d = LEz;

 (*polyg)[i].x3d =  LEx + e;
 (*polyg)[i].y3d =  LEy - e;
 (*polyg)[i++].z3d = LEz;

 (*polyg)[i].x3d =  LEx - e;
 (*polyg)[i].y3d =  LEy - e;
 (*polyg)[i++].z3d = LEz;
}

void makerighteye(){
polytype3d *polyg;
int        e,i;
 e = eyesize / 2;
 i = 0;
 polyg = &righteye3;

 (*polyg)[i].x3d =  REx - e;
 (*polyg)[i].y3d =  REy - e;
 (*polyg)[i++].z3d = LEz;

 (*polyg)[i].x3d =  REx - e;
 (*polyg)[i].y3d =  REy + e;
 (*polyg)[i++].z3d = REz;

 (*polyg)[i].x3d =  REx + e;
 (*polyg)[i].y3d =  REy + e;
 (*polyg)[i++].z3d = REz;

 (*polyg)[i].x3d =  REx + e;
 (*polyg)[i].y3d =  REy - e;
 (*polyg)[i++].z3d = REz;

 (*polyg)[i].x3d =  REx - e;
 (*polyg)[i].y3d =  REy - e;
 (*polyg)[i++].z3d = REz;
};

void seteyes(){
   LExr = lefteye3r[00].x3d + 8;
   LEyr = lefteye3r[00].y3d + 8;
   LEzr = lefteye3r[00].z3d;
   RExr = righteye3r[00].x3d + 8;
   REyr = righteye3r[00].y3d + 8;
   REzr = righteye3r[00].z3d;
};

void drawenvironment(int theta,
		     int phi,
		     int d,
		     int new1){
  if(framemoved)
  {
   setcolor(WHITE);
   if(!new)
   {
    drawpoly(11, cube2.a);
    drawpoly(7,  body2.a);
   }
   projectxy(&cube3,&cube2,11,theta,phi,d);
   projectxy(&body3,&body2,7,theta,phi,d);
   drawpoly(11,cube2.a);
   drawpoly(7,body2.a);
  }
  framemoved = FALSE;
 };

void maketarget(){
int ts;

  ts = muldiv(24,vsize,348);
  target3[00].x3d = TAx;
  target3[00].y3d = TAy - ts;
  target3[00].z3d = TAz;
  target3[01].x3d = TAx - ts;
  target3[01].y3d = TAy + ts;
  target3[01].z3d = TAz;
  target3[02].x3d =  TAx + ts;
  target3[02].y3d =  TAy + ts;
  target3[02].z3d =  TAz;
  target3[03].x3d =  TAx;
  target3[03].y3d =  TAy - ts;
  target3[03].z3d =  TAz;
};

void arminit(){
 halfside = vsize / 2;
 headheight = halfside / 2;
 headwidth = halfside / 2;
 eyesize = halfside / 10;
 neck = halfside / 4;
 d = 1000;
 ra1 =  muldiv(5,halfside,5);
 rb1 =  muldiv(5,halfside,4);
 REx = headwidth / 4;
 REy = muldiv(5,halfside,8);
 REz = -halfside + halfside / 8;
 LEx = -REx; LEy = REy; LEz = REz;
 SHx =  halfside / 2; SHy =   0; SHz = -halfside;
 FIx =  TAx; FIy = TAy; FIz = TAz;
 i3a = 0; i3e = 0; i3d = 0;
 initdynam();
};

void drawrighteye(int FRx,int FRy,int TRx,int TRy){
static int oldfrx = 0,oldfry = 0,oldtrx = 0,oldtry = 0;

 putpixel(hcenter - 50 - oldfrx/5, vcenter - 50 + oldfry/5, BLACK);
 putpixel(hcenter - 50 - oldtrx/5 + 2, vcenter - 50 + oldtry/5 + 2,BLACK);
 putpixel(hcenter - 50 - oldtrx/5 + 0, vcenter - 50 + oldtry/5 + 2,BLACK);
 putpixel(hcenter - 50 - oldtrx/5 - 2, vcenter - 50 + oldtry/5 + 2,BLACK);
 putpixel(hcenter - 50 - oldtrx/5 + 1, vcenter - 50 + oldtry/5,    BLACK);
 putpixel(hcenter - 50 - oldtrx/5 - 1, vcenter - 50 + oldtry/5,    BLACK);
 putpixel(hcenter - 50 - oldtrx/5 - 0, vcenter - 50 + oldtry/5 - 2,BLACK);


 oldfrx = FRx; oldfry = FRy; oldtry = TRy; oldtrx = TRx;

 putpixel(hcenter - 50 - oldfrx/5, vcenter - 50 + oldfry/5, WHITE);
 putpixel(hcenter - 50 - oldtrx/5 + 2, vcenter - 50 + oldtry/5 + 2,WHITE);
 putpixel(hcenter - 50 - oldtrx/5 + 0, vcenter - 50 + oldtry/5 + 2,WHITE);
 putpixel(hcenter - 50 - oldtrx/5 - 2, vcenter - 50 + oldtry/5 + 2,WHITE);
 putpixel(hcenter - 50 - oldtrx/5 + 1, vcenter - 50 + oldtry/5,    WHITE);
 putpixel(hcenter - 50 - oldtrx/5 - 1, vcenter - 50 + oldtry/5,    WHITE);
 putpixel(hcenter - 50 - oldtrx/5 - 0, vcenter - 50 + oldtry/5 - 2,WHITE);

 }

void drawlefteye(int FLx,int FLy,int TLx,int TLy){
static int oldflx = 0,oldfly = 0,oldtlx = 0,oldtly = 0;

 putpixel(hcenter - 50 - oldflx/5, vcenter - 50 + oldfly/5, BLACK);
 putpixel(hcenter - 50 - oldtlx/5 + 2, vcenter - 50 + oldtly/5 + 2,BLACK);
 putpixel(hcenter - 50 - oldtlx/5 + 0, vcenter - 50 + oldtly/5 + 2,BLACK);
 putpixel(hcenter - 50 - oldtlx/5 - 2, vcenter - 50 + oldtly/5 + 2,BLACK);
 putpixel(hcenter - 50 - oldtlx/5 + 1, vcenter - 50 + oldtly/5,    BLACK);
 putpixel(hcenter - 50 - oldtlx/5 - 1, vcenter - 50 + oldtly/5,    BLACK);
 putpixel(hcenter - 50 - oldtlx/5 - 0, vcenter - 50 + oldtly/5 - 2,BLACK);


 oldflx = FLx; oldfly = FLy; oldtly = TLy; oldtlx = TLx;

 putpixel(hcenter - 50 - oldflx/5, vcenter - 50 + oldfly/5, WHITE);
 putpixel(hcenter - 50 - oldtlx/5 + 2, vcenter - 50 + oldtly/5 + 2,WHITE);
 putpixel(hcenter - 50 - oldtlx/5 + 0, vcenter - 50 + oldtly/5 + 2,WHITE);
 putpixel(hcenter - 50 - oldtlx/5 - 2, vcenter - 50 + oldtly/5 + 2,WHITE);
 putpixel(hcenter - 50 - oldtlx/5 + 1, vcenter - 50 + oldtly/5,    WHITE);
 putpixel(hcenter - 50 - oldtlx/5 - 1, vcenter - 50 + oldtly/5,    WHITE);
 putpixel(hcenter - 50 - oldtlx/5 - 0, vcenter - 50 + oldtly/5 - 2,WHITE);

 }

void environment(){

/* t1 is angle of upper arm above horizontal. t2 is angle from extension
   of upper arm to forearm */

 t3 = t1 + t2 / 2; /* horiz to shoulder-finger line */

/*FIND X,Y,Z COORDINATES OF FINGERTIP */

    /* radius, shoulder-finger */
 rf =  (muldiv(ra1 + rb1,cosine[2048+ (t2 / 2)],scale));

 FIy = SHy + muldiv(rf,sine[2048+t3],scale);      /* y coordinate of finger */
 temp = muldiv(rf,cosine[2048+t3],scale);
 FIx = SHx + muldiv(temp,sine[2048+az],scale);      /* x coordinate of finger */
 FIz = SHz + muldiv(temp,cosine[2048+az],scale);    /* z coordinate of finger */

/*FIND X,Y,Z COORDINATES OF ELBOW */

 ELy = SHy + muldiv(ra1,sine[2048+t1],scale);
 temp = muldiv(ra1,cosine[2048+t1],scale);
 ELx = SHx + muldiv(temp,sine[2048+az],scale);
 ELz = SHz + muldiv(temp,cosine[2048+az],scale);

  /* FILL IN POLYGON FOR ARM */

 arm3[0].x3d = SHx; arm3[0].y3d = SHy; arm3[0].z3d = SHz;
 arm3[1].x3d = ELx; arm3[1].y3d = ELy; arm3[1].z3d = ELz;
 arm3[2].x3d = FIx; arm3[2].y3d = FIy; arm3[2].z3d = FIz;

 /* CALCULATE TEMPORARY VARIABLES FOR COMPUTING EYE ANGLES */

 TXL = TAx - LExr; TXR = TAx - RExr;
 TYL = TAy - LEyr; TYR = TAy - REyr;
 TZL = TAz - LEzr; TZR = TAz - REzr;

 FXL = FIx - LExr; FXR = FIx - RExr;
 FYL = FIy - LEyr; FYR = FIy - REyr;
 FZL = FIz - LEzr; FZR = FIz - REzr;

 /* target distance to eye */

 eyetot = 10.0*sqrt(
		(0.1*TXR*TXR+0.1*TYR*TYR+0.1*TZR*TZR)
	      );
 eyetof = 10.0*sqrt(
		(0.1*FXR*FXR+0.1*FYR*FYR+0.1*FZR*FZR)
	      );

  /* FIND ANGLES, FINGER && TARGET, RIGHT EYE */

 rotateimage(&TRx,&TRy,TXR,TYR,TZR,theta2,phi2re);
 rotateimage(&FRx,&FRy,FXR,FYR,FZR,theta2,phi2re);

 /* FIND ANGLES, FINGER && TARGET, LEFT EYE */

 rotateimage(&TLx,&TLy,TXL,TYL,TZL,theta2,phi2le);
 rotateimage(&FLx,&FLy,FXL,FYL,FZL,theta2,phi2le);

 /* FIND DEPTH ANGLES, EYES TO TARGET AND FINGER, radians */

 FLRd = FLx - FRx;
 TLRd = TLx - TRx;

 drawrighteye(FRx,FRy,TRx,TRy);
 drawlefteye(FLx,FLy,TLx,TLy);
 };

/* THE FOLLOWING THREE ROUTINES ARE THE X AND Y CONTROL SYSTEMS FOR
   HEAD-EYE ORIENTATION */

void gaze1xr() /* right eye, x */{
 r2dr = 0;
 p2dr = TRx;         /* perceived x target deviation from gaze angle */
 e2dr = r2dr - p2dr;
 i2dr -= e2dr;
 o2dr = muldiv(i2dr,ghx,100);  /* head angle, x */

};

void gaze1xl() /* left eye, x */{
 r2dl = 0;
 p2dl = TLx;         /* perceived x target deviation from gaze angle */
 e2dl = r2dl - p2dl;
 i2dl -= e2dl;       /* integral of error signal */
 o2dl = muldiv(i2dl,ghx,100);  /* head angle, x */

};

void gaze1y()   /* both eyes, y */ {
 r1e = 0;
 p1e = TRy;         /* perceived y target deviation from gaze angle */
 e1e = r1e - p1e;
 i1e -= e1e;       /* integral of error signal */
 o1e = muldiv(i1e,ghy,100); /* head angle, y */
};


/* THE FOLLOWING THREE ROUTINES ARE THE VISUAL CONTROL SYSTEMS FOR
   ELEVATION, AZIMUTH, AND DISTANCE AT LEVEL 3 */

void vertical3(){
 if( purpose) r3e = muldiv(pr,sine[2048+pt],4096);  /* PT IS TIME */
 else r3e = 0;
 p3e = FRy - TRy;
 e3e = r3e - p3e;
 if(visual)
  {
   i3e += muldiv(g3e,e3e,100);
   if(i3e > 1800) i3e = 1800; else if(i3e < -1800) i3e = -1800;
   o3e = i3e/3 + muldiv(d3e,e3e,100);
  }
  else
  i3e = o3e = 0;
};

void azimuth3(){
 if( purpose) r3a = muldiv(pr,cosine[2048+pt],4096);
 else r3a = 0;
 p3a = FRx - TRx;
 e3a = r3a - p3a;
 if(visual)
  {
   i3a += muldiv(g3a,e3a,100);
   if(i3a > 1800) i3a = 1800; else if(i3a < -1800) i3a = -1800;
   o3a = i3a/3 + muldiv(d3a,e3a,100);
  }
  else i3a = o3a = 0;
};

void distance3()   /* this is the hardest one to get right */
{
r3d = 0;    /* target-finger distance */
p3d = TLRd - FLRd;
e3d = r3d - p3d;
e3d = muldiv(200,e3d,dist); /* compensate for distance */
if(e3d > 1500) e3d = 1500; else if(e3d < -1500) e3d = -1500;
 if(visual)
  {
   i3d += muldiv(g3d,e3d,100);
   if(i3d > 1800) i3d = 1800; else if(i3d < -1800) i3d = -1800;
   o3d = i3d + muldiv(d3d,e3d,100);
  }
  else i3d = o3d = 0;

};

void link3to2()    /* Second level kinesthetic control system */
{
static int tempe = 0;
static int tempa = 0;
static int tempd = 0;
static int itempe = -2769; /* initialize integral terms */
static int itempa = -1112;
static int itempd = 5515;
int oe,oa,od;

   if(test3)
      if((time % 200) == 0) switchtarg();
   if(test2)
    {
     if(((time-1) % (interval*10)) == 0)
      switch(testnum)
      {
       case 1: testt1 = -testt1; tempa = -100; tempd = 1000; break;
       case 0: testt0 = -testt0; tempe = 0; tempd = 1000; break;
       case 2: testt2 = -testt2; tempe = 0;    tempa = -100; break;
      }
     switch(testnum)
      {
       case 1: tempe += (2*testt1 - tempe)/2; break;
       case 0: tempa += (2*testt0 - tempa)/2; break;
       case 2: tempd += (4*testt2 + 1000 - tempd)/2; break;
      }
      r2e = tempe;
      r2a = tempa;
      r2d = tempd;
     }
     else
      {
       if(visual)
         {
          r2e = o3e;     /* LINK WHEN NOT TESTING */
          r2a = o3a;
          r2d = o3d;
         }
      }

 r2d = 2048 - r2d;   /* convert output for external-angle control */

 p2e = t1 + 0.5*t2;      /* ELEVATION PERCEPTION */
 p2a = az;               /* AZIMUTH PERCEPTION */
 p2d = t2;               /* DISTANCE PERCEPTION */

 e2e = r2e - p2e;
 e2a = r2a - p2a;
 e2d = r2d - p2d;    /* error is eternal elbow angle error */

 itempa += muldiv(e2a,is0,100); /* integrals of error signals */
 itempe += muldiv(e2e,is1,100);
 itempd += muldiv(e2d,is2,100);

 /* Limit integrals */
 if(itempa > 20000) itempa = 20000; if(itempa < -20000) itempa = -20000;
 if(itempd > 20000) itempd = 20000; if(itempd < -20000) itempd = -20000;
 if(itempe > 20000) itempe = 20000; if(itempe < -20000) itempe = -20000;

 /* integrals plus proportionals */
 oa = muldiv(e2a,gs0,100) + itempa/5;          /* azimuth */
 oe = muldiv(e2e,gs1,100) + itempe/5;          /* elevation */
 od = muldiv(e2d,gs2,100) + itempd/5;          /* distance */

 /* limit reach distance */
 if(od > 2048) od = 2048; if(od < 128) od = 128;

 o2a = oa;
 o2d = od;
 o2e = oe - 0.5*o2d; /* prevent reach from disturbing elevation */

 /* limit azimuth and elevation angles */
 if(o2a > 1024) o2a = 1024; if(o2a < -1024) o2a = -1024;
 if(o2e > 1024) o2e = 1024; if(o2e < -1560) o2e = -1560;

}

/* THE FOLLOWING ROUTINE LINKS THE SECOND-LEVEL SYSTEMS TO THE
   SPINAL SYSTEMS CONTROLLING JOINT ANGLES AZ, T1, AND T2 */
void link2to1(){
static int temp0 = 0,temp1 = 0,temp2 = 0;
 if(test1)
  {           /* SQUARE-WAVE REFERENCE SIGNAL FOR TEST */
     if(((time-1) % (interval*5)) == 0)
      switch(testnum)
      {
       case 0: testt0 = - testt0; temp1 = -100; temp2 = 300; break;
       case 1: testt1 = - testt1; temp0 = 0; temp2 = 300; break;
       case 2: testt2 = - testt2; temp0 = 0; temp1 = -100; break;
      }
     switch(testnum)
      {
       case 0: temp0 += (2*testt0 - temp0)/3; break;
       case 1: temp1 += (2*testt1 - temp1)/3; break;
       case 2: temp2 += (2*testt2 + 550 - temp2)/3; break;
      }

       armcont(&az,&t1,&t2,temp0,temp1,temp2);
   }
  else
   armcont(&az,&t1,&t2,o2a,o2e,o2d);   /*azimuth, elevation, dist */

 /* HEAD-EYE CONTROL SYSTEMS, NO KINESTHETIC LEVEL */
 gazexle = o2dl;   /* gaze x, left eye */
 gazexre = o2dr;   /* gaze x, right eye */
 gazex = (gazexle + gazexre)/2;
 gazey = o1e;   /* gaze y, head direction */
};

void redraw(int new1){
        delay(32);                         /* DISPLAY TIMING */
	drawenvironment(theta,phi,d,new);

	if(!new)
	 {
	  drawpoly(5,lefteye2.a);
	  drawpoly(5,righteye2.a);
	 }
	projectxy(&lefteye3r,&lefteye2,5,theta,phi,d);
	drawpoly(5,lefteye2.a);
	projectxy(&righteye3r,&righteye2,5,theta,phi,d);
	drawpoly(5,righteye2.a);

	if(!new) drawpoly(6,head2.a);
	projectxy(&head3r,&head2,6,theta,phi,d);
	drawpoly(6,head2.a);

	if(!new) drawpoly(4,target2.a);
	projectxy(&target3,&target2,4,theta,phi,d);
	drawpoly(4,target2.a);

	if(!new) drawpoly(3,arm2.a);
	projectxy(&arm3,&arm2,3,theta,phi,d);
	drawpoly(3,arm2.a);

    if(track)
     {
      setwritemode(0);
      putpixel(arm2.xy[2].x2d+1,arm2.xy[2].y2d-1,WHITE);
      setwritemode(1);
     }
 if(new)
 {
  circle(hcenter - 50,vcenter - 50,50);
  outtextxy(hcenter - 100,vcenter + 10,"RETINAL IMAGES");
  outtextxy(hcenter - 100, vcenter + 20,"  COMBINED");
  showstatus();
 }
}
/* ====================================================================== */
void main(){
 //helpfile = fopen("help.man","rt");
 //if (!helpfile)
  /*{
   clrscr(); printf("File 'help.man ' not in current directory");
   exit(1);
  }*/
 e3e=e3a=e3d=0;
 r3e=r3a=r3d=0;
 test1 = 0;
 test2 = 0;
 test3 = 0;
 test4 = 0;
 pr = 150; pt = 0; delta = 20;
 selectgraph(0,0);
 graphmode = getmaxmode();
 setgraphmode(graphmode);
 clearviewport();
 restorecrtmode();
 cputs("Loading functions"); crlf;
 getfunctions();
 cputs("Loading parameters"); crlf;
 getparams(vparams,numvparams,'i');
 getparams(kparams,numkparams,'f');
 getparams(sparams,numkparams,'s');
 initdynam();
 o3e = 0; o3a = 0; o3d = 0;
 i3e = 0; i3a = 0; i3d = 0;
 cputs("Initializing"); crlf;
 TAx = 0; TAy = 0; TAz = 100;
 phi = 1200; theta = 0;
 gazexle = gazexre = 0; gazey = 0;
 phi2le = phi2re = phi2 = 0;
 theta2 = 0;
 track = FALSE;
 top = vsize / 4;
 middle = vsize / 2;
 bottom = 3 * vsize;
 bottom = bottom / 4;
 arminit();
 makecube();
 makebody();
 makehead();
 makelefteye();
 makerighteye();
 TAx = 0; TAy = 0; TAz = 100;
 setgraphmode(graphmode);
 clearviewport();
 settextstyle(0,0,1);
 settextjustify(LEFT_TEXT,TOP_TEXT);
 getaspectratio(&xa,&ya);
 setcolor(WHITE);
 xasp = xa; yasp = muldiv(ya,106,100);
 setwritemode(1);
 framemoved = TRUE;
 rotateview(&head3,&head3r,6,theta2/4,phi2/4,0,neck,-halfside);
 rotateview(&lefteye3,&lefteye3r,5,theta2/4,phi2/4,0,neck,-halfside);
 rotateview(&righteye3,&righteye3r,5,theta2/4,phi2/4,0,neck,-halfside);
 rotateview(&lefteye3r,&lefteye3r,5,3*theta2/4,3*phi2le/4,LEx,LEy,LEz);
 rotateview(&righteye3r,&righteye3r,5,3*theta2/4,3*phi2le/4,REx,REy,REz);
 seteyes();
 maketarget();
 projectxy(&target3,&target2,4,theta,phi,d);
 projectxy(&arm3,&arm2,3,theta,phi,d);
 projectxy(&head3r,&head2,6,theta,phi,d);
 projectxy(&lefteye3r,&lefteye2,5,theta,phi,d);
 projectxy(&righteye3r,&righteye2,5,theta,phi,d);
 setwritemode(1);
 redraw(NEW);

 time = 0; tempt = 0;
 ch = ' '; purpose = FALSE; pt = 0;
 interval = 0.1/dt;

 /* main loop */

 while(ch != 'q')
 {
  time = (time + 1) % 10000;
     if ((time % interval) == 0)
      {
       if (count > 1000) count = 0;
       setfillstyle(0,0);
       bar(hsize - 130,0,hsize-1,10);
       sprintf(cstr,"%5.1f sec",count/10.0);
       setcolor(WHITE);
       outtextxy(hsize - 130,0,cstr);
       ++count;
      }
  redraw(NOTNEW);
  if( purpose)
   {
    pt = (pt + 30);
    if( pt > 2047) pt = -2048;
   };
  if( ch == 'p')
   {
     ch = getch();
     ch = ' ';
   };

  /*FIRST, CHECK FOR COMMANDS FROM KEYBOARD*/

  ch = '\0';
  while( kbhit())
   {
    cmd = getcod(); ch = cmd;
    if (cmd >= 'A' && cmd <= 'Z') ch = cmd | 0x20;
    switch(cmd)
     {
      case Esc: test1 = test2 = test3 = test4 = 0;
                statuschange = TRUE;
                visual = -1;
                arminit();
                break;
      case F3:
      case F2:
      case F1: test2 = test3 = test4 = visual = 0;
	       test1 = TRUE;
	       statuschange = TRUE;
	       if(test1)
		{
		 if(cmd == F1) testnum = 0;
		 else if(cmd == F2) testnum = 1;
		 else if(cmd == F3) testnum = 2;
		 else if(cmd == F4) testnum = -1;
		 testt0=testt1=testt2=100;
		}
		else {
		       testt1=testt2=testt0 = 0;
		       testnum = -1;
		     }
		arminit();
		break;
      case F4:
      case F5:
      case F6: test1 = test3 = test4 = visual = 0;
	       test2 = TRUE;
	       statuschange = TRUE;
	       if(test2)
		{
		 if(cmd == F4) testnum = 0;
		 else if(cmd == F5) testnum = 1;
		 else if(cmd == F6) testnum = 2;
		 testt0=testt1=testt2=100;
		}
		else {
		       testt1=testt2=testt0 = 0;
		       testnum = -1;
		     }
		arminit();
		break;
       case F7: targ1.x = TAx;
		targ1.y = TAy;
		targ1.z = TAz;
		seektarg1 = TRUE;
		break;
       case F8: targ2.x = TAx;
		targ2.y = TAy;
		targ2.z = TAz;
		seektarg1 = FALSE;
		break;
       case F9: switchtarg(); break;
       case F10:  test1 = test2 = test4 = 0;
		  test3 = TRUE;
		  statuschange = TRUE;
		  break;
       case AltF10: test1 = test2 = test3 = 0;
		  test4 = TRUE;
		  statuschange = TRUE;
		  break;

       case Up: if( TAy < (halfside + halfside / 2) - delta)
	      TAy = TAy + delta; else TAy = halfside + halfside / 2; break;
       case Down: if( TAy > -halfside + delta)
	      TAy = TAy - delta; else TAy = -halfside; break;
       case PgUp: if( TAz < halfside - delta)
	      TAz = TAz + delta; else TAz = halfside; break;
       case PgDn: if( TAz > -halfside + 180 + delta)
	      TAz = TAz - delta; else TAz = -halfside + 180; break;
       case Right:if( TAx < halfside - delta)
	      TAx = TAx + delta; else TAx = halfside; break;
       case Left: if( TAx > -halfside + delta)
	      TAx = TAx - delta; else TAx = -halfside; break;
       case '+': if( delta <= 190) delta += 10; else delta = 200;
		      break;
       case '-': if( delta >= 30) delta -= 10; else delta = 20;
		      break;
     };

       if(ch == '!') purpose = ! purpose;


     /*EXECUTE COMMANDS*/
     switch(ch)
     {
      case 'c': clearviewport();
	        setwritemode(1);
                framemoved = TRUE;
	        redraw(NEW);
                break;
      case 'r': phi = (phi + 25);     break;
      case 'l': phi = phi - 25;       break;
      case 'u': theta = (theta + 25); break;
      case 'd': theta = theta - 25;   break;
      case 'g': setgravity();
		statuschange = TRUE;
		break;
      case 't': track = !track; break;
      case 'z': arminit(); break;
      case 'k':    /* kinesthetic spinal */
      case 's':    /* brainStem */
      case 'v':    /* visual */
	    setviewport(0,0,hsize/2,vsize-25,0);
	    clearviewport();
	    setwritemode(1);
	    if(ch == 'v')
	     {
	      setlegends(vlegends,numvparams,0,0);
	      setparams(vparams,numvparams,120,0,6,0,'i');
	     }
	    else if(ch == 's')
	     {
	      setlegends(slegends,numsparams,0,vcenter);
	      setparams(sparams,numsparams,120,vcenter,6,0,'s');
	     }
	    else
	     {
	      setlegends(klegends,numkparams,0,vcenter/2);
	      setparams(kparams,numkparams,220,vcenter/2,9,3,'f');
	      initdynam();
	     }
	    framemoved = TRUE;
	    setviewport(0,0,hsize - 1,vsize-1,0);
	    clearviewport();
	    setwritemode(1);
	    redraw(NEW);
	    ch = '\0';
	    break;
       case '?': showhelp(); break;
     };
     if( phi > maxmin1) phi = phi - 2 * one80;
     if( phi < -one80) phi = phi + 2 * one80;
     if( theta > maxmin1) theta = theta - 2 * one80;
     if( theta < -one80) theta = theta + 2 * one80;
     framemoved = strchr("udrlsz",ch) != NULL;
    };  /* of if(kbhit())*/


   /* ADJUST CLOCK FOR 1/30-SECOND ITERATIONS */
  for (tt=1; tt < tcount; ++tt);   /* TIMING DELAY */
  ++timercount;

  (void) gettime(&newtime);
  if (newtime.ti_sec != oldtime.ti_sec)
  {
   dcount = (100 - timercount);
   if (dcount > 100) dcount = 100;
   if (dcount < -100) dcount = -100;
   tcount -= dcount*200;
   if (tcount < 10000L) tcount = 10000L;
   oldtime.ti_sec = newtime.ti_sec;
   timercount = 1;
  }


  if( ch != 'q'){

  /* DRAW LITTLE MAN IN CURRENT CONFIGURATION */

  phi2le = gazexle;
  phi2re = gazexre;
  phi2 = (phi2le + phi2re)/2;
  theta2 = gazey;
	/* move head and eyes */
    rotateview(&head3,&head3r,6,theta2/4,phi2/4,0,neck,-halfside);
    rotateview(&lefteye3,&lefteye3r,5,theta2/4,phi2/4,0,neck,-halfside);
    rotateview(&righteye3,&righteye3r,5,theta2/4,phi2/4,0,neck,-halfside);
    rotateview(&lefteye3r,&lefteye3r,5,3*theta2/4,3*phi2le/4,LEx,LEy,LEz);
    rotateview(&righteye3r,&righteye3r,5,3*theta2/4,3*phi2re/4,REx,REy,REz);
    seteyes();
    maketarget();

    if(test1) showcontrol(1,testnum);
    else if (test2) showcontrol(2,testnum);
    else showangles(az/6,t1/6,t2/6);

   if(statuschange) showstatus();
  };

  /*CALCULATE THE STATE OF ENVIRONMENT AND ALL CONTROL SYSTEMS*/


  environment();
  gaze1xl();
  gaze1xr();
  dist = 10000/(1 + abs(gazexle - gazexre));
  gaze1y();
  if(!test1){
  if(test4)
   {
    if( --timer <= 0 )
     {
      timer = 200;
      movex = random(2*halfside) - halfside;
      movey = random(2*halfside) - halfside;
      movez = random(halfside - 50) - 20;
     }
     TAx = movex;
     TAy = movey;
     TAz = movez;
   }
   vertical3();
   azimuth3();
   distance3();
  }
  if(!test1) link3to2();    /* second kinesthetic level */
  link2to1();               /* first kinesthetic level */




 };

  saveparams(kparams,numkparams,'f');  /* save kinesthetic parameters */
  saveparams(vparams,numvparams,'i');  /* save visual parameters */
  saveparams(sparams,numsparams,'s');  /* save brainstem parameters */
  restorecrtmode();
  closegraph();
  fclose(helpfile);
 };
 
