/* special key definitions */

#define Home 0xc7
#define Up 0xc8
#define PgUp 0xc9
#define Left 0xcb
#define Right 0xcd
#define EndKey 0xcf
#define Down 0xd0
#define PgDn 0xd1
#define Ins 0xd2
#define Del 0xd3
#define F1 0xbb
#define F2 0xbc
#define F3 0xbd
#define F4 0xbe
#define F5 0xbf
#define F6 0xc0
#define F7 0xc1
#define F8 0xc2
#define F9 0xc3
#define F10 0xc4
#define CtlF1 222
#define CtlF2 223
#define CtlF3 224
#define CtlF4 225
#define CtlF5 226
#define CtlF6 227
#define CtlF7 228
#define CtlF8 229
#define CtlF9 230
#define CtlF10 231
#define AltF1 232
#define AltF2 233
#define AltF3 234
#define AltF4 235
#define AltF5 236
#define AltF6 237
#define AltF7 238
#define AltF8 239
#define AltF9 240
#define AltF10 241
#define AltA 158
#define AltB 176
#define AltC 174
#define AltD 160
#define AltE 146
#define AltF 161
#define AltG 162
#define AltH 163
#define AltI 151
#define AltJ 164
#define AltK 165
#define AltL 166
#define AltM 178
#define AltN 177
#define AltO 152
#define AltP 153
#define AltQ 144
#define AltR 147
#define AltS 159
#define AltT 148
#define AltU 150
#define AltV 175
#define AltW 145
#define AltX 173
#define AltY 149
#define AltZ 172
#define Alt1 248
#define Alt2 249
#define Alt3 250
#define Alt4 251
#define Alt5 252
#define Alt6 253
#define Alt7 254
#define Alt8 255
#define Alt9 128
#define Alt0 129

#define Esc 0x1b
#define Us   0x1f
#define Etb  0x17
#define Etx  3
#define Soh  1
#define Stx  2

/* box elements */

#define TLC1 218
#define TRC1 191
#define BLC1 192
#define BRC1 217
#define H1 196
#define V1 179
#define LT1 195
#define TT1 194
#define RT1 180
#define BT1 193
#define TLC2 201
#define TRC2 187
#define BLC2 200
#define BRC2 188
#define H2 205
#define V2 186
#define LT2 204
#define TT2 203
#define RT2 185
#define BT2 202
#define TLCH1V2 214
#define TLCH2V1 213
#define TRCH1V2 183
#define TRCH2V1 184
#define BLCH1V2 211
#define BLCH2V1 212
#define BRCH1V2 189
#define BRCH2V1 190
#define LTH1V2 199
#define LTH2V1 198
#define TTH1V2 210
#define TTH2V1 209
#define RTH1V2 182
#define RTH2V1 181
#define BTH1V2 208
#define BTH2V1 207

      /* AP ASCII CODES */

 #define spb 0x10
 #define  one8 0x5b
 #define  two8 0x5c
 #define  three8 0x5d
 #define  four8 0x7b
 #define  five8 0x7c
 #define  six8 0x7d
 #define  seven8 0x7e
 #define quadleft 0x3c
 #define waitingfirst 0
 #define ondisk 1
 #define sentaps 2
 #define sendaps 4
 #define retransmit 8

/* typesetting parameters */

 #define esc 0x1b
 #define thinspace 11
 #define enspace 22

   /* APS command codes */

 #define ml  0x8f  /* mark location */
 #define rl  0x90  /* return to location */
 #define rv  0x93  /* return to V-location */
 #define lm  0xa4  /* set left margin */
 #define cf  0xb0  /* change font */
 #define hz  0xb1  /* set horiz size */
 #define vz  0xb2  /* set vertical size */
 #define rs  0xb5  /* reserve string */
 #define es  0xb6  /* execute string */
 #define va  0xc0  /* vertical space absolute */
 #define vr  0xc1  /* vertical space relative */
 #define ha  0xc2  /* horizontal space absolute */
 #define hr  0xc3  /* horizontal space relative */
 #define ph  0xcd  /* horizontal position absolute */
 #define vl  0xd0  /* store vertical space */
 #define av  0xd5  /* set vertical rule a */
 #define ah  0xd6  /* set horizontal rule a */
 #define bv  0xd7  /* set vertical rule b */
 #define bh  0xd8  /* set horizontal rule b */
 #define al  0xda  /* store horizontal space a */
 #define bl  0xdb  /* store horizontal space b */
 #define mh  0xde  /* mark horizontal position */
 #define hm  0xdf  /* return to horizontal mark */
 #define xs  0xe0  /* execute stored vertical space */
 #define rb  0xe1  /* return beam to left margin */
 #define acr 0xe2  /* carriage return (vert space, return beam */
/* #define xa  0xe5 */  /* execute rule a */
 #define xb  0xe7  /* execute rule b */
 #define hsa 0xea  /* execute horizontal space a */
 #define hsb 0xeb  /* execute horizontal space b */
 #define ri  0xee  /* reset */
 #define cs  0xf0  /* close string */
 #define mv  0xf2  /* mark vertical position */
 #define rm  0xf3  /* return to vertical mark */
 #define ht  0xfd  /* halt */

/* start and end command */

//#define SC '\xc6'    /* autologic mru zoom factor, not used as command */
