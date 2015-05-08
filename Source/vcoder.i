
#pragma used+
sfrb PINF=0;
sfrb PINE=1;
sfrb DDRE=2;
sfrb PORTE=3;
sfrb ADCL=4;
sfrb ADCH=5;
sfrw ADCW=4;      
sfrb ADCSRA=6;
sfrb ADMUX=7;
sfrb ACSR=8;
sfrb UBRR0L=9;
sfrb UCSR0B=0xa;
sfrb UCSR0A=0xb;
sfrb UDR0=0xc;
sfrb SPCR=0xd;
sfrb SPSR=0xe;
sfrb SPDR=0xf;
sfrb PIND=0x10;
sfrb DDRD=0x11;
sfrb PORTD=0x12;
sfrb PINC=0x13;
sfrb DDRC=0x14;
sfrb PORTC=0x15;
sfrb PINB=0x16;
sfrb DDRB=0x17;
sfrb PORTB=0x18;
sfrb PINA=0x19;
sfrb DDRA=0x1a;
sfrb PORTA=0x1b;
sfrb EECR=0x1c;
sfrb EEDR=0x1d;
sfrb EEARL=0x1e;
sfrb EEARH=0x1f;
sfrw EEAR=0x1e;   
sfrb SFIOR=0x20;
sfrb WDTCR=0x21;
sfrb OCDR=0x22;
sfrb OCR2=0x23;
sfrb TCNT2=0x24;
sfrb TCCR2=0x25;
sfrb ICR1L=0x26;
sfrb ICR1H=0x27;
sfrw ICR1=0x26;   
sfrb OCR1BL=0x28;
sfrb OCR1BH=0x29;
sfrw OCR1B=0x28;  
sfrb OCR1AL=0x2a;
sfrb OCR1AH=0x2b;
sfrw OCR1A=0x2a;  
sfrb TCNT1L=0x2c;
sfrb TCNT1H=0x2d;
sfrw TCNT1=0x2c;  
sfrb TCCR1B=0x2e;
sfrb TCCR1A=0x2f;
sfrb ASSR=0x30;
sfrb OCR0=0x31;
sfrb TCNT0=0x32;
sfrb TCCR0=0x33;
sfrb MCUCSR=0x34;
sfrb MCUCR=0x35;
sfrb TIFR=0x36;
sfrb TIMSK=0x37;
sfrb EIFR=0x38;
sfrb EIMSK=0x39;
sfrb EICRB=0x3a;
sfrb XDIV=0x3c;
sfrb SPL=0x3d;
sfrb SPH=0x3e;
sfrb SREG=0x3f;
#pragma used-

#asm
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x20
	.EQU __sm_mask=0x1C
	.EQU __sm_powerdown=0x10
	.EQU __sm_powersave=0x18
	.EQU __sm_standby=0x14
	.EQU __sm_ext_standby=0x1C
	.EQU __sm_adc_noise_red=0x08
	.SET power_ctrl_reg=mcucr
	#endif
#endasm

#pragma used+

void delay_us(unsigned int n);
void delay_ms(unsigned int n);

#pragma used-

typedef char *va_list;

#pragma used+

char getchar(void);
void putchar(char c);
void puts(char *str);
void putsf(char flash *str);
int printf(char flash *fmtstr,...);
int sprintf(char *str, char flash *fmtstr,...);
int vprintf(char flash * fmtstr, va_list argptr);
int vsprintf(char *str, char flash * fmtstr, va_list argptr);

char *gets(char *str,unsigned int len);
int snprintf(char *str, unsigned int size, char flash *fmtstr,...);
int vsnprintf(char *str, unsigned int size, char flash * fmtstr, va_list argptr);

int scanf(char flash *fmtstr,...);
int sscanf(char *str, char flash *fmtstr,...);

#pragma used-

#pragma library stdio.lib

#pragma used+

signed char cmax(signed char a,signed char b);
int max(int a,int b);
long lmax(long a,long b);
float fmax(float a,float b);
signed char cmin(signed char a,signed char b);
int min(int a,int b);
long lmin(long a,long b);
float fmin(float a,float b);
signed char csign(signed char x);
signed char sign(int x);
signed char lsign(long x);
signed char fsign(float x);
unsigned char isqrt(unsigned int x);
unsigned int lsqrt(unsigned long x);
float sqrt(float x);
float ftrunc(float x);
float floor(float x);
float ceil(float x);
float fmod(float x,float y);
float modf(float x,float *ipart);
float ldexp(float x,int expon);
float frexp(float x,int *expon);
float exp(float x);
float log(float x);
float log10(float x);
float pow(float x,float y);
float sin(float x);
float cos(float x);
float tan(float x);
float sinh(float x);
float cosh(float x);
float tanh(float x);
float asin(float x);
float acos(float x);
float atan(float x);
float atan2(float y,float x);

#pragma used-
#pragma library math.lib

typedef struct {
unsigned char active; 
signed char point[9];   

signed char expon; 
} CURVE_STRUCT;

typedef struct {
unsigned       ACTIVE:1, 

SOURSE_TYPE:1, 

PROC_SOURSE:1, 

MIX_SW:1, 

SW_INV:1, 

UCH_SW:3; 
} TMIX_TYPE;

typedef struct {
unsigned    CH_SOURSE:4, 
CH_DEST:4;   
} TCH_NUM;

typedef struct {
TMIX_TYPE    MIX_TYPE;  
TCH_NUM        CH_NUM;  
unsigned char MIX_VAL;  

} MIXER_STRUCT;

typedef struct {
unsigned char  FMODE_NAME;       
unsigned char  TRIMSTEP;         
signed char    UCH_TRIMMER[7];   
unsigned int   LCH_MIDLE[16];    
CURVE_STRUCT   LCH_CURVE[16];    
MIXER_STRUCT   MIXER[40 ]; 
} FMODE_STRUCT;

typedef struct {
signed char UCH_LEFT;  
signed char UCH_RIGHT; 
} UCH_STRUCT;

typedef struct {
unsigned char FILTER_TYPE; 

unsigned int        VAL1; 

} TCHFILTERS;

typedef struct {   
unsigned char    LCH_COUNT; 
unsigned int    CH_EPL[16]; 
unsigned int    CH_EPR[16]; 

unsigned char   LCHDELDN[16]; 
unsigned char   LCHDELUP[16]; 

unsigned char    LCH_REV[16]; 

unsigned char PPM_CH_COUNT; 
TCHFILTERS       FILTER[8]; 
} TCHANNELS;

typedef struct {
unsigned char       MODEL_TYPE;       
unsigned char       MODEL_NAME[8];    

unsigned int        MODEL_FLYTIMER;   
unsigned int        MODEL_LIVETIMER;  

TCHANNELS           CHANNELS;         
UCH_STRUCT          UCH[14 ];   
unsigned char       PPM_TO_LCH_CAP[8]; 
unsigned char       FMODE_COUNT;      
FMODE_STRUCT        FMODE[3];         

} MODEL_INFO_STRUCT;

MODEL_INFO_STRUCT rmodel;

unsigned char get_mnu_keys(void); 
void CalcCurveORD(void); 
unsigned char getMixCount(unsigned char fmode); 
extern unsigned char mixercount;  
extern unsigned char mixtochan;   
extern unsigned char mixtochanlast;   
extern unsigned char mch[8]; 
extern unsigned int OLD_LCH_LEN[16]; 

extern unsigned char ppmStop; 

extern unsigned int keyhold;      

unsigned int read_adc(unsigned char adc_input);

extern unsigned int UCHmid[7]; 
extern unsigned int UCHmin[7]; 
extern unsigned int UCHmax[7]; 

extern eeprom unsigned int E_UCHmid[7]; 
extern eeprom unsigned int E_UCHmin[7]; 
extern eeprom unsigned int E_UCHmax[7]; 

extern eeprom unsigned char E_CurModelNum; 

extern unsigned char ClusterSize; 

extern eeprom unsigned char E_SOUND_ON; 
extern unsigned char SOUND_ON; 

extern eeprom unsigned char E_key_press_time; 
extern eeprom unsigned char E_key_repress_time; 
extern eeprom unsigned char E_trim_press_time; 

extern unsigned char key_press_time; 
extern unsigned char key_repress_time; 
extern unsigned char trim_press_time; 
extern eeprom unsigned char E_nulTrimBeep; 

void resetKeyReader(); 

extern unsigned int UCH_VALUES[14]; 
extern signed  char UCH_VAL_PROC[14]; 

extern unsigned char BLINK; 

extern unsigned int CH_PPM[8]; 

extern unsigned int batt; 
extern eeprom unsigned int E_battMin; 
extern unsigned int battMin; 

extern flash unsigned char *messStr1; 
extern flash unsigned char *messStr2; 
extern flash unsigned char *messStr3; 
extern flash unsigned char *messStr4; 
extern flash unsigned char *messStr5; 
extern unsigned char messRetCode; 

extern unsigned char printMess; 

extern unsigned int FMODE_NUM; 

extern eeprom unsigned char E_eventStart; 
extern eeprom unsigned char E_eventStop;   

extern unsigned char flyTimerOn; 
extern unsigned int flyCurrTimer; 
extern unsigned char  TimerEndBeepCounter;
extern unsigned char  TimerEnd;

extern eeprom unsigned char E_beep1min; 
extern eeprom unsigned char E_beep2sec; 

extern eeprom unsigned char PPM_capture; 
extern eeprom unsigned char E_var3;
extern eeprom unsigned char E_var4;

extern eeprom unsigned char E_var11;
extern eeprom unsigned char E_var12;

extern eeprom unsigned int  E_vari2;
extern eeprom unsigned int  E_vari3;
extern eeprom unsigned int  E_vari4;

extern eeprom unsigned int  E_vari5;
extern eeprom unsigned int  E_vari6;
extern eeprom unsigned int  E_vari7;
extern eeprom unsigned int  E_vari8;
extern eeprom unsigned int  E_vari9;
extern eeprom unsigned int  E_vari10;

extern unsigned char PPM_CUR_CH_NUM;
extern unsigned int  PPM_PAUSE; 
extern unsigned int LCH_LEN[16]; 
extern unsigned int CURVE_POINT[16][9][2]; 

extern unsigned char ModelChange; 

extern unsigned int     outx1, outx2, outx3, outy1, outy2, outy3, outkk; 

unsigned char buff[8][128]; 

void LCD_command(unsigned char command) 
{

PORTC &= 0xE5;
DDRA = 0xFF;
PORTA = command;
PORTC |= 0x20;
PORTC &= 0xDF;
PORTC |= 0x02;
}

void LCD_data(unsigned char data) 
{

PORTC &= ~18;
PORTC |= 8;
DDRA = 0xFF;
PORTA = data;
PORTC |= 32;
PORTC &= ~32;
PORTC |= 2;
}

void LCD_refresh (void)  
{
unsigned char i,j;
for(i=0; i<8; i++)
{ LCD_command(0xB0  |  i);
LCD_command(0x10);	
LCD_command(0x04);
for (j=0; j<128; j++) LCD_data(buff[i][j]);
}
}

void LCD_clear (void) 
{
unsigned char x, y;
for (y=0; y<8; y++)    
for (x=0; x<128; x++) buff[y][x]=0;   
}           

void LCD_init(void) 
{
PORTC &= 0x04;            
delay_us(1);
delay_us(1);              
PORTC |= 0x04;            
delay_us(1500);
LCD_command(0xe2); 
LCD_command(0xae); 
LCD_command(0xa1); 
LCD_command(0xA6); 
LCD_command(0xA4); 
LCD_command(0xA2); 
LCD_command(0xC0); 
LCD_command(0x2F); 
LCD_command(0x25); 
LCD_command(0x81); 
LCD_command(0x22); 
LCD_command(0xAF); 
LCD_clear();  
LCD_refresh();  
}

void LCD_setContrast(unsigned char contr) {
LCD_command(0x81); 
LCD_command(contr); 

}

__flash const unsigned char font[] = { 

0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x5e,0x00,0x00, 
0x00,0x08,0x06,0x08,0x06, 
0x28,0x7e,0x28,0x7e,0x28, 
0x04,0x2a,0x7e,0x2a,0x10, 
0x4c,0x2c,0x10,0x68,0x64, 
0x34,0x4a,0x56,0x20,0x50, 
0x00,0x00,0x00,0x08,0x06, 
0x00,0x00,0x18,0x24,0x42, 
0x00,0x00,0x42,0x24,0x18, 
0x14,0x08,0x3e,0x08,0x14, 
0x08,0x08,0x3e,0x08,0x08, 
0x00,0x00,0xb0,0x70,0x00, 
0x00,0x08,0x08,0x08,0x08, 
0x00,0x00,0x60,0x60,0x00, 
0x00,0x60,0x18,0x06,0x00, 
0x00,0x3c,0x42,0x42,0x3c, 
0x00,0x00,0x44,0x7e,0x40, 
0x00,0x44,0x62,0x52,0x4c, 
0x00,0x42,0x4a,0x4a,0x34, 
0x00,0x18,0x14,0x7a,0x10, 
0x00,0x2e,0x4a,0x4a,0x32, 
0x00,0x3c,0x4a,0x4a,0x30, 
0x00,0x02,0x72,0x0a,0x06, 
0x00,0x34,0x4a,0x4a,0x34, 
0x00,0x0c,0x52,0x52,0x3c, 
0x00,0x00,0x6c,0x6c,0x00, 
0x00,0x00,0xa8,0x68,0x00, 
0x00,0x00,0x08,0x14,0x22, 
0x00,0x14,0x14,0x14,0x14, 
0x00,0x00,0x22,0x14,0x08, 
0x00,0x04,0x52,0x0a,0x04, 
0x3c,0x42,0x5a,0x5a,0x1c, 
0x00,0x7c,0x12,0x12,0x7c, 
0x00,0x7e,0x4a,0x4a,0x34, 
0x00,0x3c,0x42,0x42,0x24, 
0x00,0x7e,0x42,0x42,0x3c, 
0x00,0x7e,0x4a,0x4a,0x42, 
0x00,0x7e,0x0a,0x0a,0x02, 
0x00,0x3c,0x42,0x52,0x34, 
0x00,0x7e,0x10,0x10,0x7e, 
0x00,0x42,0x7e,0x42,0x00, 
0x00,0x20,0x40,0x40,0x3e, 
0x00,0x7e,0x18,0x24,0x42, 
0x00,0x7e,0x40,0x40,0x40, 
0x7e,0x04,0x08,0x04,0x7e, 
0x00,0x7e,0x08,0x10,0x7e, 
0x00,0x3c,0x42,0x42,0x3c, 
0x00,0x7e,0x12,0x12,0x0c, 
0x00,0x3c,0x42,0x22,0x5c, 
0x00,0x7e,0x12,0x32,0x4c, 
0x00,0x24,0x4a,0x52,0x24, 
0x02,0x02,0x7e,0x02,0x02, 
0x00,0x3e,0x40,0x40,0x3e, 
0x1e,0x20,0x40,0x20,0x1e, 
0x7e,0x20,0x18,0x20,0x7e, 
0x42,0x24,0x18,0x24,0x42, 
0x02,0x04,0x78,0x04,0x02, 
0x00,0x62,0x52,0x4a,0x46, 
0x00,0x7e,0x42,0x42,0x00, 
0x00,0x06,0x18,0x60,0x00, 
0x00,0x42,0x42,0x7e,0x00, 
0x08,0x04,0x02,0x04,0x08, 
0x40,0x40,0x40,0x40,0x40, 
0x00,0x00,0x06,0x08,0x00, 
0x00,0x30,0x48,0x48,0x78, 
0x00,0x7e,0x48,0x48,0x30, 
0x00,0x30,0x48,0x48,0x48, 
0x00,0x30,0x48,0x48,0x7e, 
0x00,0x78,0x48,0x58,0x58, 
0x00,0x08,0xfe,0x0a,0x08, 
0x00,0x10,0xa8,0xa8,0x78, 
0x00,0x7e,0x08,0x08,0x70, 
0x00,0x48,0x7a,0x40,0x00, 
0x00,0x80,0x88,0xfa,0x00, 
0x00,0x7e,0x10,0x28,0x40, 
0x00,0x42,0x7e,0x40,0x00, 
0x78,0x08,0x70,0x08,0x70, 
0x00,0x78,0x08,0x08,0x70, 
0x00,0x30,0x48,0x48,0x30, 
0x00,0xf8,0x28,0x28,0x10, 
0x00,0x10,0x28,0x28,0xf8, 
0x00,0x78,0x10,0x08,0x08, 
0x00,0x50,0x58,0x68,0x28, 
0x00,0x08,0x7e,0x48,0x48, 
0x00,0x38,0x40,0x40,0x78, 
0x18,0x20,0x40,0x20,0x18, 
0x38,0x40,0x30,0x40,0x38, 
0x00,0x48,0x30,0x30,0x48, 
0x00,0x98,0xa0,0xa0,0x78, 
0x00,0x48,0x68,0x58,0x48, 
0x00,0x10,0x7c,0x44,0x00, 
0x00,0x00,0x7e,0x00,0x00, 
0x00,0x00,0x44,0x7c,0x10, 
0x10,0x10,0x44,0x38,0x10, 
0x10,0x38,0x44,0x10,0x10  

};

unsigned char LCD_Y;
unsigned char LCD_X;

void LCD_setxy(char x,unsigned char y) 
{
LCD_X=x+2;
LCD_Y=y;
}

void LCD_char(unsigned char ch, unsigned char mode) {   
unsigned char x;
if ((ch<127) || (ch>32)) { 
for (x=0; x<5; x++) {
if (mode==2) mode=BLINK; 
switch (mode) {
case 0: { buff[LCD_Y][LCD_X]=font[ (unsigned int)(ch-32)*5+x ];  break; }
case 1: { buff[LCD_Y][LCD_X]=255-font[ (unsigned int)(ch-32)*5+x ]; break; }
}
LCD_X++; 
}
}
}

void LCD_out(unsigned char ch) { 
buff[LCD_Y][LCD_X]=ch;
LCD_X++;
}

void LCD_wrsf (flash unsigned char*str,unsigned char color) 
{
while(*str!='\0') { LCD_char(*str, color);
str++; } 
}

void LCD_dec(unsigned int val, unsigned char len, unsigned char mode) {
unsigned char i;
unsigned char cx=0;
unsigned char savePOS_X;

savePOS_X=LCD_X; 
cx+=(len-1)*5;
for (i=0; i<len; i++) {
LCD_X=cx+savePOS_X; LCD_char(val%10+'0',mode);
cx-=5;
val/=10;
}
LCD_X=savePOS_X+len*5;  
}

void LCD_V_dec(unsigned int val, unsigned char len, unsigned char mode) {
unsigned char i;
unsigned char savePOS_X, savePOS_Y;

savePOS_X=LCD_X; 
savePOS_Y=LCD_Y;
LCD_Y=LCD_Y+len-1;

for (i=0; i<len; i++) {
LCD_X=savePOS_X; LCD_char(val%10+'0',mode);
LCD_Y--;
val/=10;
}
LCD_X=savePOS_X;
LCD_Y=savePOS_Y;  
}

void LCD_pixel (unsigned char x, unsigned char y, unsigned char color)
{  
unsigned char i, bt;
if ((x<128)&&(y<64)) {
i=y>>3;
bt=1<<(y & 0x7);
if(color) buff[i][x]|=bt;
else buff[i][x]&=(~bt);
} 
} 

void LCD_big_char(unsigned char x, unsigned char y, unsigned char ch) {
unsigned char px,py,i;

for (px=0;px<5;px++) { 

i=font[ (unsigned int)(ch-32)*5+px ]; 

for (py=0; py<8;py++) { 
if ((i%2)==1) { 
LCD_pixel(x+px*2,y+py*2,1);   LCD_pixel(x+px*2+1,y+py*2,1);
LCD_pixel(x+px*2,y+py*2+1,1); LCD_pixel(x+px*2+1,y+py*2+1,1);
}
i=i/2;
}
}
}

void LCD_big_dec(unsigned char x, unsigned char y, unsigned int val, unsigned char len) {
unsigned char i,px;
unsigned char cx=0;

cx+=(len-1)*10;
for (i=0; i<len; i++) {
px=cx+x; LCD_big_char(px, y, val%10+'0');
cx-=10;
val/=10;
}
}

void LCD_big3_char(unsigned char x, unsigned char y, unsigned char ch) {
unsigned char px,py,i;
unsigned char ppx, ppy;

for (px=0;px<5;px++) { 

i=font[ (unsigned int)(ch-32)*5+px ]; 

ppx=px*3; 
for (py=0; py<8;py++) { 
if ((i%2)==1) {
ppy=py*3; 
LCD_pixel(x+ppx, y+ppy,1);   LCD_pixel(x+ppx+1,y+ppy,1);    LCD_pixel(x+ppx+2,y+ppy,1);
LCD_pixel(x+ppx, y+ppy+1,1); LCD_pixel(x+ppx+1,y+ppy+1,1);  LCD_pixel(x+ppx+2,y+ppy+1,1);
LCD_pixel(x+ppx, y+ppy+2,1); LCD_pixel(x+ppx+1,y+ppy+2,1);  LCD_pixel(x+ppx+2,y+ppy+2,1);
}
i=i/2;
}
}
}

void LCD_big3_dec(unsigned char x, unsigned char y, unsigned int val, unsigned char len) {
unsigned char i,px;
unsigned char cx=0;

cx+=(len-1)*15;
for (i=0; i<len; i++) {
px=cx+x; LCD_big3_char(px, y, val%10+'0');
cx-=15;
val/=10;
}
}

void LCD_dashline ( char x1, char y1, char x2, char y2)
{
char mode;
int dx, dy, stepx, stepy, fraction;

dy = y2 - y1;
dx = x2 - x1;
mode=1;

if ( dy < 0 ) { dy= -dy; stepy = -1; }
else stepy = 1;
if ( dx < 0 ) { dx= -dx; stepx = -1; }
else stepx = 1;
dx <<= 1;
dy <<= 1;
LCD_pixel( x1, y1, mode );
if ( dx > dy )
{
fraction = dy - (dx >> 1);
while ( x1 != x2 )
{
if(fraction >= 0 ) { y1 += stepy; fraction -= dx; }
x1 += stepx;
fraction += dy;
if (mode) mode=0;
else mode=1;
LCD_pixel( x1, y1, mode );
}
}
else
{
fraction = dx - (dy >> 1);
while ( y1 != y2 )
{
if ( fraction >= 0 ) { x1 += stepx; fraction -= dy; }
y1 += stepy;
fraction += dx;
if (mode) mode=0;
else mode=1;
LCD_pixel( x1, y1, mode );
}
}
}

void LCD_line(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, char mode) {
signed char   dx, dy, sx, sy;
unsigned char  x,  y, mdx, mdy, l;

dx=x2-x1; dy=y2-y1;

if (dx>=0) { mdx=dx; sx=1; } else { mdx=x1-x2; sx=-1; } 
if (dy>=0) { mdy=dy; sy=1; } else { mdy=y1-y2; sy=-1; }

x=x1; y=y1;

if (mdx>=mdy) {
l=mdx;
while (l>0) {
if (dy>0) { y=y1+mdy*(x-x1)/mdx; } 
else { y=y1-mdy*(x-x1)/mdx; }
LCD_pixel(x,y,mode);
x=x+sx;
l--;
}
} else {
l=mdy;
while (l>0) {
if (dy>0) { x=x1+((mdx*(y-y1))/mdy); } 
else { x=x1+((mdx*(y1-y))/mdy); }
LCD_pixel(x,y,mode);
y=y+sy;
l--;
}    
}
}

void LCD_rectangle(char x1,char y1,char x2,char y2,char mode) { 
LCD_line(x1,y1, x2,y1, mode);
LCD_line(x1,y2, x2,y2, mode);
LCD_line(x1,y1, x1,y2, mode);
LCD_line(x2,y1, x2,y2, mode);
}

eeprom unsigned char notUsed; 

eeprom unsigned char E_ClusterSize; 
eeprom unsigned char VDISK[1952  ]; 

eeprom unsigned char files[16]; 
eeprom unsigned char freesp; 

unsigned int  cluster; 
unsigned int   cl_pos; 
unsigned char fileNum; 

unsigned char F_STATUS; 

void formatVDisk() {
unsigned int i; 
if ( (E_ClusterSize==16) || (E_ClusterSize==32) || (E_ClusterSize==48) || (E_ClusterSize==64) ) {

for(i=0;i<(1952  /E_ClusterSize);i++) {
if (i!=((1952  /E_ClusterSize)-1)) VDISK[i*E_ClusterSize]=i+1; else VDISK[i*E_ClusterSize]=255;
}

for  (i=0; i<16; i++) files[i]=255; 

freesp=0; 
} 
else {

messStr1="  INCORRECT CLUTER SIZE  "; 
messStr2="CLUSTER SIZE SET TO 32   ";
messStr3=" CHECK NEW VALUE IN MENU:";
messStr4=" SYSTEM - V-DISK";
messStr5=" AND TRY AGAIN.. ";
printMess=1;
E_ClusterSize=32;
} 
}

unsigned char fileToRead(unsigned char filenum) {
unsigned char retcode;

F_STATUS=1; 

if (filenum>15) retcode=1; 
else {

if (files[filenum]==255) { 
retcode=2; } 
else {
fileNum=filenum;
cluster=files[filenum]; 
cl_pos=1; 
retcode=0;
F_STATUS=0; 
}  
}

return retcode;   
}

unsigned char fileRead() {
unsigned char readc; 

readc=0; 

if (F_STATUS==0) {

readc=VDISK[cluster*E_ClusterSize+cl_pos]; 

cl_pos++; 
if (cl_pos==E_ClusterSize) { 
cl_pos=1;
cluster=VDISK[cluster*E_ClusterSize]; 
if (cluster==255) { 
F_STATUS=1; 
}
} 
}
return readc; 
}

unsigned char fileToWrite(unsigned char filenum) {
unsigned char retcode;

F_STATUS=1; 

if (filenum>15) 
retcode=1; 
else {
if (freesp!=255) { 

files[filenum]=freesp; 

cluster=freesp; 

freesp=VDISK[((unsigned int)freesp)*((unsigned int)E_ClusterSize)]; 

VDISK[((unsigned int)cluster)*((unsigned int)E_ClusterSize)]=255; 

fileNum=filenum;
cl_pos=1; 
retcode=0;
F_STATUS=0; 
}
else retcode=2;         
}    
return retcode;   
}

void fileDelete(unsigned char filenum) {
unsigned char i; 
if (files[filenum]!=255) { 

i=freesp; 
if (i!=255) {
while (VDISK[((unsigned int)i)*((unsigned int)E_ClusterSize)]!=255) { 
i=VDISK[((unsigned int)i)*((unsigned int)E_ClusterSize)];  
}

VDISK[((unsigned int)i)*((unsigned int)E_ClusterSize)]=files[filenum]; 
} else freesp=files[filenum];
files[filenum]=255; 

if (printMess==0) {

messStr2=""; 
messStr1="      FILE ERASED !      ";
messStr3=" ";
messStr4=" ";
messStr5=" ";
printMess=1;
}                   
} 
}

void fileWrite(unsigned char wrChar) {

if (F_STATUS==0) { 

if (VDISK[cluster*E_ClusterSize+cl_pos]!=wrChar) 

VDISK[cluster*E_ClusterSize+cl_pos]=wrChar;  

cl_pos++; 

if (cl_pos==E_ClusterSize) { 

cl_pos=1; 

if (freesp!=255) { 

VDISK[((unsigned int)cluster)*((unsigned int)E_ClusterSize)]=freesp; 

cluster=freesp; 

freesp=VDISK[((unsigned int)cluster)*((unsigned int)E_ClusterSize)]; 

VDISK[((unsigned int)cluster)*((unsigned int)E_ClusterSize)]=255;  
} 
else { 
F_STATUS=1; 

messStr1="    FILE WRITE ERROR !   ";

messStr2=" No free space for task  ";
messStr3="    File NOT SAVED";
messStr4=" ";
messStr5=" ";
printMess=1;
fileDelete(fileNum);                   
}
} 
}
}

unsigned char fileSize(unsigned char filenum) {
unsigned char i,s;
s=files[filenum];
if (s!=255) {
i=1; 
while (VDISK[((unsigned int)s)*((unsigned int)E_ClusterSize)]!=255) { 
s=VDISK[((unsigned int)s)*((unsigned int)E_ClusterSize)];            
i++;
}

} else i=0; 
return i;
}
unsigned char get_mnu_keys(void); 
void CalcCurveORD(void); 
unsigned char getMixCount(unsigned char fmode); 
extern unsigned char mixercount;  
extern unsigned char mixtochan;   
extern unsigned char mixtochanlast;   
extern unsigned char mch[8]; 
extern unsigned int OLD_LCH_LEN[16]; 

extern unsigned char ppmStop; 

extern unsigned int keyhold;      

unsigned int read_adc(unsigned char adc_input);

extern unsigned int UCHmid[7]; 
extern unsigned int UCHmin[7]; 
extern unsigned int UCHmax[7]; 

extern eeprom unsigned int E_UCHmid[7]; 
extern eeprom unsigned int E_UCHmin[7]; 
extern eeprom unsigned int E_UCHmax[7]; 

extern eeprom unsigned char E_CurModelNum; 

extern unsigned char ClusterSize; 

extern eeprom unsigned char E_SOUND_ON; 
extern unsigned char SOUND_ON; 

extern eeprom unsigned char E_key_press_time; 
extern eeprom unsigned char E_key_repress_time; 
extern eeprom unsigned char E_trim_press_time; 

extern unsigned char key_press_time; 
extern unsigned char key_repress_time; 
extern unsigned char trim_press_time; 
extern eeprom unsigned char E_nulTrimBeep; 

void resetKeyReader(); 

extern unsigned int UCH_VALUES[14]; 
extern signed  char UCH_VAL_PROC[14]; 

extern unsigned char BLINK; 

extern unsigned int CH_PPM[8]; 

extern unsigned int batt; 
extern eeprom unsigned int E_battMin; 
extern unsigned int battMin; 

extern flash unsigned char *messStr1; 
extern flash unsigned char *messStr2; 
extern flash unsigned char *messStr3; 
extern flash unsigned char *messStr4; 
extern flash unsigned char *messStr5; 
extern unsigned char messRetCode; 

extern unsigned char printMess; 

extern unsigned int FMODE_NUM; 

extern eeprom unsigned char E_eventStart; 
extern eeprom unsigned char E_eventStop;   

extern unsigned char flyTimerOn; 
extern unsigned int flyCurrTimer; 
extern unsigned char  TimerEndBeepCounter;
extern unsigned char  TimerEnd;

extern eeprom unsigned char E_beep1min; 
extern eeprom unsigned char E_beep2sec; 

extern eeprom unsigned char PPM_capture; 
extern eeprom unsigned char E_var3;
extern eeprom unsigned char E_var4;

extern eeprom unsigned char E_var11;
extern eeprom unsigned char E_var12;

extern eeprom unsigned int  E_vari2;
extern eeprom unsigned int  E_vari3;
extern eeprom unsigned int  E_vari4;

extern eeprom unsigned int  E_vari5;
extern eeprom unsigned int  E_vari6;
extern eeprom unsigned int  E_vari7;
extern eeprom unsigned int  E_vari8;
extern eeprom unsigned int  E_vari9;
extern eeprom unsigned int  E_vari10;

extern unsigned char PPM_CUR_CH_NUM;
extern unsigned int  PPM_PAUSE; 
extern unsigned int LCH_LEN[16]; 
extern unsigned int CURVE_POINT[16][9][2]; 

extern unsigned char ModelChange; 

extern unsigned int     outx1, outx2, outx3, outy1, outy2, outy3, outkk; 

#pragma used+

char *strcat(char *str1,char *str2);
char *strcatf(char *str1,char flash *str2);
char *strchr(char *str,char c);
signed char strcmp(char *str1,char *str2);
signed char strcmpf(char *str1,char flash *str2);
char *strcpy(char *dest,char *src);
char *strcpyf(char *dest,char flash *src);
unsigned int strlenf(char flash *str);
char *strncat(char *str1,char *str2,unsigned char n);
char *strncatf(char *str1,char flash *str2,unsigned char n);
signed char strncmp(char *str1,char *str2,unsigned char n);
signed char strncmpf(char *str1,char flash *str2,unsigned char n);
char *strncpy(char *dest,char *src,unsigned char n);
char *strncpyf(char *dest,char flash *src,unsigned char n);
char *strpbrk(char *str,char *set);
char *strpbrkf(char *str,char flash *set);
char *strrchr(char *str,char c);
char *strrpbrk(char *str,char *set);
char *strrpbrkf(char *str,char flash *set);
char *strstr(char *str1,char *str2);
char *strstrf(char *str1,char flash *str2);
char *strtok(char *str1,char flash *str2);

unsigned int strlen(char *str);
void *memccpy(void *dest,void *src,char c,unsigned n);
void *memchr(void *buf,unsigned char c,unsigned n);
signed char memcmp(void *buf1,void *buf2,unsigned n);
signed char memcmpf(void *buf1,void flash *buf2,unsigned n);
void *memcpy(void *dest,void *src,unsigned n);
void *memcpyf(void *dest,void flash *src,unsigned n);
void *memmove(void *dest,void *src,unsigned n);
void *memset(void *buf,unsigned char c,unsigned n);
unsigned int strcspn(char *str,char *set);
unsigned int strcspnf(char *str,char flash *set);
int strpos(char *str,char c);
int strrpos(char *str,char c);
unsigned int strspn(char *str,char *set);
unsigned int strspnf(char *str,char flash *set);

#pragma used-
#pragma library string.lib

__flash const unsigned char UCH_Names[14][10]= { 
"AILERON", 
"ELEVAT.",   
"THROTT.", 
"RUDDER ", 
"HOV PIT",  
"HOV THR",  
"PIT TRM",
"F MODE ",  
"GEAR   ",    
"TRAINER",
"THR.CUT", 
"AILE DR",  
"ELEV DR", 
"RUDD DR" };

__flash const unsigned char MODEL_TYPE[3][8]= { "ACRO  ", "PLANER", "HELI  " };

__flash const unsigned char CHANNEL_FILTER_TYPE[3 ][8]= { 
"LINE",    
"SW",      
"MULTI" };

__flash const unsigned char SL_FMODE_NAME[12 ][9]= {
"NORMAL",  "LANDING",  "TRAINER",  "PILOTAGE",  "3D",  "4D",
"IDLE1",   "IDLE2",    
"START",   "SPEED",    "CRUISE",   "THERMAL"};

typedef void (*tmenu_proc)(void);

unsigned char   disp_mode; 

unsigned char numitem_cur; 
unsigned char    posxmenu; 

unsigned char    menu_exe; 
tmenu_proc      menu_proc; 

unsigned char fmode_source, fmode_to; 
unsigned char get_mnu_keys(void); 
void CalcCurveORD(void); 
unsigned char getMixCount(unsigned char fmode); 
extern unsigned char mixercount;  
extern unsigned char mixtochan;   
extern unsigned char mixtochanlast;   
extern unsigned char mch[8]; 
extern unsigned int OLD_LCH_LEN[16]; 

extern unsigned char ppmStop; 

extern unsigned int keyhold;      

unsigned int read_adc(unsigned char adc_input);

extern unsigned int UCHmid[7]; 
extern unsigned int UCHmin[7]; 
extern unsigned int UCHmax[7]; 

extern eeprom unsigned int E_UCHmid[7]; 
extern eeprom unsigned int E_UCHmin[7]; 
extern eeprom unsigned int E_UCHmax[7]; 

extern eeprom unsigned char E_CurModelNum; 

extern unsigned char ClusterSize; 

extern eeprom unsigned char E_SOUND_ON; 
extern unsigned char SOUND_ON; 

extern eeprom unsigned char E_key_press_time; 
extern eeprom unsigned char E_key_repress_time; 
extern eeprom unsigned char E_trim_press_time; 

extern unsigned char key_press_time; 
extern unsigned char key_repress_time; 
extern unsigned char trim_press_time; 
extern eeprom unsigned char E_nulTrimBeep; 

void resetKeyReader(); 

extern unsigned int UCH_VALUES[14]; 
extern signed  char UCH_VAL_PROC[14]; 

extern unsigned char BLINK; 

extern unsigned int CH_PPM[8]; 

extern unsigned int batt; 
extern eeprom unsigned int E_battMin; 
extern unsigned int battMin; 

extern flash unsigned char *messStr1; 
extern flash unsigned char *messStr2; 
extern flash unsigned char *messStr3; 
extern flash unsigned char *messStr4; 
extern flash unsigned char *messStr5; 
extern unsigned char messRetCode; 

extern unsigned char printMess; 

extern unsigned int FMODE_NUM; 

extern eeprom unsigned char E_eventStart; 
extern eeprom unsigned char E_eventStop;   

extern unsigned char flyTimerOn; 
extern unsigned int flyCurrTimer; 
extern unsigned char  TimerEndBeepCounter;
extern unsigned char  TimerEnd;

extern eeprom unsigned char E_beep1min; 
extern eeprom unsigned char E_beep2sec; 

extern eeprom unsigned char PPM_capture; 
extern eeprom unsigned char E_var3;
extern eeprom unsigned char E_var4;

extern eeprom unsigned char E_var11;
extern eeprom unsigned char E_var12;

extern eeprom unsigned int  E_vari2;
extern eeprom unsigned int  E_vari3;
extern eeprom unsigned int  E_vari4;

extern eeprom unsigned int  E_vari5;
extern eeprom unsigned int  E_vari6;
extern eeprom unsigned int  E_vari7;
extern eeprom unsigned int  E_vari8;
extern eeprom unsigned int  E_vari9;
extern eeprom unsigned int  E_vari10;

extern unsigned char PPM_CUR_CH_NUM;
extern unsigned int  PPM_PAUSE; 
extern unsigned int LCH_LEN[16]; 
extern unsigned int CURVE_POINT[16][9][2]; 

extern unsigned char ModelChange; 

extern unsigned int     outx1, outx2, outx3, outy1, outy2, outy3, outkk; 

unsigned char temp1, temp2, temp3; 
unsigned int temp4;

__flash const char CHNUM_table[] = { 
'1','2','3','4','5','6','7','8',
'9','A','B','C','D','E','F','G'       
};

void menu_EDIT_CHANNEL_FILTERS() {
unsigned char filt_num;        
unsigned char ftype;
unsigned char mode;
unsigned int fval;
unsigned int x,y;
unsigned char chcount;
unsigned char chnum; 
signed char   valsc; 

if (temp1==0) { 
temp2=0; 
temp3=0; 
temp1=1;
temp4=1; 
}

LCD_setxy(0,0); LCD_wrsf("       FILTER EDIT       ",1);

filt_num=numitem_cur-36; 

ftype=rmodel.CHANNELS.FILTER[filt_num].FILTER_TYPE; 
fval=rmodel.CHANNELS.FILTER[filt_num].VAL1; 

LCD_setxy(0,2); LCD_wrsf("CHANNEL: ",0); LCD_char(CHNUM_table[filt_num],0);

if (temp2==0) mode=2; else mode=0;

LCD_setxy(0,3); LCD_wrsf("FILTER TYPE: ",0); LCD_wrsf(CHANNEL_FILTER_TYPE[ftype], mode); 

switch (ftype) { 
case 1: { 

if (temp2==1) mode=2; else mode=0;
chnum=fval%256;
valsc=fval/256; 
LCD_setxy(0,4); LCD_wrsf("SWITCH: ",0); LCD_wrsf(UCH_Names[chnum], mode);

if (temp2==2) mode=2; else mode=0;
LCD_setxy(0,5); LCD_wrsf("VALUE: ",0); 
if (valsc<0) { LCD_char('-',mode); valsc=-valsc; } else LCD_char('+',mode); 
LCD_dec(valsc, 3, mode); LCD_char('%',mode);
valsc=fval/256;
break;
}

case 2: { 

LCD_setxy(0,4); LCD_wrsf("CHANNELS: [ . . . . ]",0);
LCD_setxy(60,4);
chcount=0;
for (x=0;x<16;x++) {
if ((fval%2)==1) { LCD_char(CHNUM_table[x], 1); LCD_char(' ',0); chcount++; }
fval=fval/2;
}

for (y=0; y<2; y++) {
LCD_setxy(40,6+y);
for (x=0;x<8;x++) {
if (((y*8+x)==temp3)&&(temp2==1)) mode=2; 
else mode=0;  
LCD_char(CHNUM_table[y*8+x], mode); 
LCD_X++; LCD_X++;
}
}
break;
}   
}

mode=get_mnu_keys(); 
switch (mode) { 

case 238: { 
if (temp2>0) { temp2--; }
break; } 

case 246: {  
switch (ftype) { 
case 1: { 
if (temp2<2) { temp2++;  }
break;
}

case 2: { 
if (temp2<1) temp2++;
break;
}          
}
break; 
}

case 250: {  

if ((ftype==2) && (chcount<4)) { 
rmodel.CHANNELS.FILTER[filt_num].VAL1=0;
rmodel.CHANNELS.FILTER[filt_num].FILTER_TYPE=0;
} 
temp2=0; 
temp3=0; 
temp1=0;
temp4=0;
resetKeyReader(); 
menu_exe=0;
break; }

case 252: {  
ModelChange=1;
resetKeyReader(); 
if (temp2>0)                                             
switch (ftype) {
case 1: { 

break;
}        

case 2: { 
x=rmodel.CHANNELS.FILTER[filt_num].VAL1 & temp4;
if (x>0) rmodel.CHANNELS.FILTER[filt_num].VAL1=rmodel.CHANNELS.FILTER[filt_num].VAL1-temp4;
else if (chcount<4) rmodel.CHANNELS.FILTER[filt_num].VAL1=rmodel.CHANNELS.FILTER[filt_num].VAL1+temp4; 
break;
}        

}
break; 
} 

case 222: {  
ModelChange=1;
if (temp2==0) { 
if (ftype>0) {                                  

rmodel.CHANNELS.FILTER[filt_num].FILTER_TYPE--;
if (rmodel.CHANNELS.FILTER[filt_num].FILTER_TYPE==1) {
rmodel.CHANNELS.FILTER[filt_num].VAL1=8;
}  else { rmodel.CHANNELS.FILTER[filt_num].VAL1=0; }
} 
}

else {
switch (ftype) {
case 1: { 
if (temp2==1) { 
if (chnum<13) { chnum++;
rmodel.CHANNELS.FILTER[filt_num].VAL1=valsc*256+chnum;
} 
}
if (temp2==2) { 
if (valsc<125) { valsc++;
rmodel.CHANNELS.FILTER[filt_num].VAL1=valsc*256+chnum;
} 
}

break;
}

case 2: { 
if (temp3<15) {
temp3++;
temp4=temp4*2;    
}    

break;
}

}
} 
break; 
}

case 190: { 
ModelChange=1;
if (temp2==0) {
if (ftype<2) { 
rmodel.CHANNELS.FILTER[filt_num].FILTER_TYPE++;  
if (rmodel.CHANNELS.FILTER[filt_num].FILTER_TYPE==1) {
rmodel.CHANNELS.FILTER[filt_num].VAL1=8;
} else { rmodel.CHANNELS.FILTER[filt_num].VAL1=0; }
} 
}

else {
switch (ftype) {
case 1: { 
if (temp2==1) { 
if (chnum>7) { chnum--;
rmodel.CHANNELS.FILTER[filt_num].VAL1=valsc*256+chnum;
} 
}

if (temp2==2) { 
if (valsc>-125) { valsc--; 
rmodel.CHANNELS.FILTER[filt_num].VAL1=valsc*256+chnum;
} 
}

break;
}

case 2: { 
if (temp3>0) {
temp3--;
temp4=temp4/2;    
}    
break;
}
}  
}
break; 
}
} 
}

__flash const char Name_table[] = { 
' ','_','-','+','A','B','C','D','E','F',
'G','H','I','J','K','L','M','N','O','P',
'Q','R','S','T','U','V','W','X','Y','Z',
'0','1','2','3','4','5','6','7','8','9'       
};

void menu_EDIT_MODEL_NAME() {
unsigned int i,j; 
unsigned char mode;

if (temp1==0) { 
temp2=0; 
temp3=0; 
temp1=1;
}

LCD_setxy(0,0); LCD_wrsf("     EDIT MODEL NAME     ",1);

LCD_setxy(10,2); LCD_wrsf("NAME: [", 0);

for (i=0;i<8;i++) { 
if (i==temp2) { mode=2; } else { mode=0; }
LCD_char(rmodel.MODEL_NAME[i], mode);
}
LCD_char(']', 0); 

for (i=0;i<4;i++) { 
LCD_setxy(29,i+4);
for (j=0;j<10;j++) { 
if (temp3==i*10+j) mode=1; else mode=0;
LCD_char(Name_table[i*10+j], mode);
LCD_X++; 
LCD_X++;
}
} 

mode=get_mnu_keys(); 
switch (mode) { 

case 238: { 
if (temp2>0) temp2--; else temp2=7;
break; } 

case 246: {  
if (temp2<7) temp2++; else temp2=0;
break; } 

case 250: {  
temp2=0; 
temp3=0; 
temp1=0;
resetKeyReader(); 
menu_exe=0;
break; }

case 252: {  
rmodel.MODEL_NAME[temp2]=Name_table[temp3]; 
if (temp2<7) temp2++; else temp2=0; 
ModelChange=1;
resetKeyReader(); 
break; } 

case 222: {  
if (temp3<39) temp3++; else temp3=0;
break; }

case 190: { 
if (temp3>0) temp3--; else temp3=39;
break; }
}
}

void menu_SYSTEM_CALIBRATION_INFO() {
unsigned int y; 
LCD_setxy(0,0);
LCD_wrsf("     CALIBRATION INFO    ", 1);

for (y=0;y<7;y++) {

LCD_setxy(0,y+1);
LCD_wrsf(UCH_Names[y],0);   
LCD_char(' ',0); 
LCD_dec(UCHmin[y],4,0);     
LCD_char(' ',0); 
LCD_dec(UCHmid[y],4,0);     
LCD_char(' ',0); 
LCD_dec(UCHmax[y],4,0);     

}

y=get_mnu_keys();
switch (y) {
case 250 : { resetKeyReader(); 
menu_exe=0; }
}

}

unsigned char system_calibration_part;
void menu_SYSTEM_NEW_CALIBRATION() { 
unsigned char i, j, k; 
unsigned char ok; 
unsigned int v, v1, v2;

LCD_setxy(0,0); LCD_wrsf("       CALIBRATION       ",1);   LCD_line(0, 10, 127, 10, 1);

if (system_calibration_part==0) { 

for (i=0; i<7; i++) { UCHmin[i]=UCH_VALUES[i]; UCHmax[i]=UCH_VALUES[i]; } 
system_calibration_part=1; } 

if (system_calibration_part==1) { 
ok=0;
for (i=0; i<7; i++) { 
if (UCHmin[i]>UCH_VALUES[i]) UCHmin[i]=UCH_VALUES[i]; 
if (UCHmax[i]<UCH_VALUES[i]) UCHmax[i]=UCH_VALUES[i]; 
LCD_rectangle(1+i*17, 12, 10+i*17, 42,  1);  
LCD_setxy(3+i*17,6);     LCD_char(i+'0', 1); 
v=UCH_VALUES[i]-UCHmin[i];       v*=28;      v/=(UCHmax[i]-UCHmin[i]);   k=13+v;
if (k<43)  { LCD_line(1+i*17, k, 10+i*17, k, 1); } 

v1=(UCHmax[i]-UCHmin[i])/2;    v2=UCH_VALUES[i]-UCHmin[i];
if ((v2<(v1*107/100)) && (v2>(v1*100/107))) {
for (j=k; j<42; j++) LCD_line(1+i*17, j, 10+i*17, j, 1);
ok++;
}     
LCD_setxy(i*17+1, 7); LCD_dec(UCH_VALUES[i],3,0);  
}

j=get_mnu_keys(); 
switch (j) {
case 252 : { 
resetKeyReader(); 

for (i=0; i<7; i++) { 
UCHmid[i]=UCH_VALUES[i]; 

E_UCHmin[i]=UCHmin[i];
E_UCHmid[i]=UCHmid[i];
E_UCHmax[i]=UCHmax[i];
}

messStr1=" CALIBRATION COMPLETE !  ";

messStr2="All analog controls ready";
messStr3="";
messStr4="";
printMess=1;

system_calibration_part=0;
menu_exe=0;

break; 
}

case 250 : { 
for (i=0; i<7; i++) { 

UCHmin[i]=E_UCHmin[i];
UCHmid[i]=E_UCHmid[i];
UCHmax[i]=E_UCHmax[i];
}
system_calibration_part=0; 
menu_exe=0;
resetKeyReader(); 
break; } 
}
}
}

void menu_FMODE_CURVES_EXPO(unsigned char fmode, unsigned char LCH) {
unsigned char i;
signed int y;
const signed char line_y[9] ={ -100,-75,-50,-25,0,25,50,75,100};
const signed char expo_y[9] ={ -100,-45,-15, -3,0, 3,15,45,100};

for (i=0; i<9; i++) {
y = line_y[i]-expo_y[i];
y*= rmodel.FMODE[fmode].LCH_CURVE[LCH].expon;
y/= 100;    
y = line_y[i]-y;
rmodel.FMODE[fmode].LCH_CURVE[LCH].point[i]=y;
}
}

unsigned char temp5;

void menu_FMODE_CURVES() {

unsigned char fmode=0; 
unsigned char mode;    
signed char cval; 
unsigned char ch; 
unsigned char lpx, lpy, px, py; 
signed char curx; 

if (temp1==0) { 
temp2=0; 
temp3=0; 
temp4=0; 
temp5=0; 
temp1=1; 
ModelChange=1;
}

switch (numitem_cur) {         
case 112: { fmode=0; break; }
case 117: { fmode=1; break; }
case 122: { fmode=2; break; }
}

LCD_setxy(0,0); LCD_wrsf("       CURVE  EDIT       ",1);

LCD_setxy(0,1); LCD_wrsf("F MODE: ", 0);
LCD_char(fmode+0x31,0);

if (temp2==0) mode=1; else mode=0;  

LCD_setxy(0,2); LCD_wrsf("LCH NUM: ", mode);
if (mode==1) mode=2; else mode=0;
if (temp4<9) ch=temp4+49; else ch=temp4+56; 
LCD_char(ch,mode);

if (temp2==1) mode=1; else mode=0; 

LCD_setxy(0,3); LCD_wrsf("CURVE: ", mode);
if (mode==1) mode=2; else mode=0; 
switch (rmodel.FMODE[fmode].LCH_CURVE[temp4].active) {
case 0: { LCD_wrsf(" OFF", mode); break; }
case 1: { LCD_wrsf(" ON", mode); break; }
}

if (rmodel.FMODE[fmode].LCH_CURVE[temp4].active==1) {

if (temp2==2) mode=1; else mode=0; 
LCD_setxy(0,4); LCD_wrsf("EXPO:   ", mode);
cval=rmodel.FMODE[fmode].LCH_CURVE[temp4].expon;
if (mode==1) mode=2; else mode=0; 
if (cval<0) { LCD_char('-',mode); cval=-cval; } else LCD_char('+',mode); 
LCD_dec(cval,3,mode); LCD_char('%',mode);

if (temp2==3) mode=1; else mode=0; 
LCD_setxy(0,5); LCD_wrsf("LCH IN: ", mode);
if (mode==1) mode=2; else mode=0; 
switch (temp5) {
case 0: { LCD_wrsf("-100%", mode); break; }
case 1: { LCD_wrsf(" -75%", mode); break; }
case 2: { LCD_wrsf(" -50%", mode); break; }
case 3: { LCD_wrsf(" -25%", mode); break; }
case 4: { LCD_wrsf("   0%", mode); break; }
case 5: { LCD_wrsf(" +25%", mode); break; }
case 6: { LCD_wrsf(" +50%", mode); break; }
case 7: { LCD_wrsf(" +75%", mode); break; }
case 8: { LCD_wrsf("+100%", mode); break; }    
}

if (temp2==4) mode=1; else mode=0; 
LCD_setxy(0,6); LCD_wrsf("VALUE:  ", mode);

cval=rmodel.FMODE[fmode].LCH_CURVE[temp4].point[temp5];
if (mode==1) mode=2; else mode=0; 
if (cval<0) { LCD_char('-',mode); cval=-cval; } else LCD_char('+',mode); 
LCD_dec(cval,3,mode); LCD_char('%',mode);

for (mode=0; mode<9; mode++) {
LCD_dashline(     72,    12+mode*5,     112,      12+mode*5  );
if (temp5==mode) LCD_line( 72+mode*5,    12,      72+mode*5,      52      ,1);
else LCD_dashline( 72+mode*5,    12,      72+mode*5,      52      );  
}

LCD_line(72,  32, 112, 32, 1); 

curx=-100; 
lpx=72;
cval=rmodel.FMODE[fmode].LCH_CURVE[temp4].point[0];

lpy=32-cval/5;

curx=curx+25;
for (mode=1;mode<9;mode++) {

switch (curx) {
case -100: { px=72; break; }
case  -75: { px=77; break; }
case  -50: { px=82; break; }
case  -25: { px=87; break; }
case    0: { px=92; break; }
case   25: { px=97; break; }
case   50: { px=102; break; }
case   75: { px=107; break; }
case  100: { px=112; break; }
}

cval=rmodel.FMODE[fmode].LCH_CURVE[temp4].point[mode];

py=32-cval/5;

LCD_line(lpx,lpy,px,py,1);

lpx=px;
lpy=py;
curx=curx+25;
}
}

mode=get_mnu_keys();
switch (mode) {
case 238: { 
if (temp2>0) temp2--; 
break; 
} 

case 246: {  
if (rmodel.FMODE[fmode].LCH_CURVE[temp4].active==1) {

if (temp2<4) temp2++; else temp2=0; } else {
if (temp2<1) temp2++; else temp2=0; } 
break; 
} 

case 250: {  
temp2=0; 
temp3=0;
temp4=0;
temp5=0; 
temp1=0;
resetKeyReader(); 
menu_exe=0;
CalcCurveORD();
break; 
}

case 252: {  
resetKeyReader(); 
break; 
} 

case 222: {  
switch (temp2) {
case 0: { 
if (temp4<(rmodel.CHANNELS.LCH_COUNT-1)) temp4++;
break;
}
case 1: { 
if (rmodel.FMODE[fmode].LCH_CURVE[temp4].active==1)
rmodel.FMODE[fmode].LCH_CURVE[temp4].active=0; else
rmodel.FMODE[fmode].LCH_CURVE[temp4].active=1; 
break;  
}
case 2: { 
if (rmodel.FMODE[fmode].LCH_CURVE[temp4].expon<100) {
rmodel.FMODE[fmode].LCH_CURVE[temp4].expon++;
menu_FMODE_CURVES_EXPO(fmode,temp4); 
}
break;  
}                    
case 3: { 
if (temp5<8) temp5++; 
break;
}
case 4: { 
if (rmodel.FMODE[fmode].LCH_CURVE[temp4].point[temp5]<100) 
rmodel.FMODE[fmode].LCH_CURVE[temp4].point[temp5]++;
break;

} 
}
break; 
}

case 190: { 
switch (temp2) {
case 0: { 
if (temp4>0) temp4--;
break;
}
case 1: { 
if (rmodel.FMODE[fmode].LCH_CURVE[temp4].active==1)
rmodel.FMODE[fmode].LCH_CURVE[temp4].active=0; else
rmodel.FMODE[fmode].LCH_CURVE[temp4].active=1; 
break;  
}
case 2: { 
if (rmodel.FMODE[fmode].LCH_CURVE[temp4].expon > -100) {
rmodel.FMODE[fmode].LCH_CURVE[temp4].expon--;
menu_FMODE_CURVES_EXPO(fmode,temp4); 
}
break;  
}       
case 3: { 
if (temp5>0) temp5--; 
break;
}
case 4: { 
if (rmodel.FMODE[fmode].LCH_CURVE[temp4].point[temp5]>-100) 
rmodel.FMODE[fmode].LCH_CURVE[temp4].point[temp5]--;
break;
}              
}
break; 
}     
}
}

__flash const unsigned char UCH_SNAMES[14][5]= { 
"AIL.", 
"ELE.",   
"THR.", 
"RUD.", 
"HOVP",  
"HOVT",  
"PITT",
"100%",  
"GEAR",    
"TRAI",
"THRC", 
"AILD",  
"ELED", 
"RUDD" };
void FMODE_MIXERS_editmix(unsigned char fmode, unsigned char mixnum){ 
unsigned char ACTIVE; 

unsigned char MIX_SW; 
unsigned char UCH_SW; 
unsigned char SW_INV; 

unsigned char DEST_CH; 

unsigned char SOURSE_CH; 
unsigned char SOURSE_TYPE; 

unsigned char PROC_SOURSE; 
signed char MIX_VAL; 
signed char MX_VAL;
unsigned char MIX_UCH; 
unsigned char MIX_INV; 

unsigned char mode, modex; 

unsigned char tmp; 

ACTIVE=rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.ACTIVE;  

MIX_SW=rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.MIX_SW; 
UCH_SW=7+rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.UCH_SW; 
SW_INV=rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.SW_INV;

DEST_CH=rmodel.FMODE[fmode].MIXER[mixnum].CH_NUM.CH_DEST; 

SOURSE_TYPE=rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.SOURSE_TYPE; 
SOURSE_CH=rmodel.FMODE[fmode].MIXER[mixnum].CH_NUM.CH_SOURSE; 

PROC_SOURSE=rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.PROC_SOURSE; 
MIX_VAL=rmodel.FMODE[fmode].MIXER[mixnum].MIX_VAL; 

MIX_UCH=0x0F & rmodel.FMODE[fmode].MIXER[mixnum].MIX_VAL; 
if ((0x10&rmodel.FMODE[fmode].MIXER[mixnum].MIX_VAL)!=0) MIX_INV=1;  
else MIX_INV=0;

if (temp4==0) mode=1; else mode=0; 

LCD_setxy(0,2);
LCD_wrsf("ACTIVE: ",mode);

if (mode==1) { 
if (temp5==1) modex=2; else modex=1;  
} else modex=0;
if (ACTIVE==1) LCD_wrsf("ON", modex); else LCD_wrsf("OFF", modex);

if (temp4==1) mode=1; else mode=0;        

LCD_setxy(0,3);              
LCD_wrsf("SWITCH: ",mode);

if (mode==1) {                                   
if (temp5==1) modex=2; else modex=1;  
} else modex=0;
if (MIX_SW==0) LCD_wrsf("OFF", modex); 
else {   
LCD_wrsf("ON ", modex);

if (mode==1) {                                
if (temp5==2) modex=2; else modex=1;  
} else modex=0;

if (SW_INV==1) LCD_wrsf("-", modex); else LCD_wrsf("+", modex); 

LCD_char(' ',mode);

if (mode==1) {                                
if (temp5==3) modex=2; else modex=1;  
} else modex=0;
LCD_wrsf(UCH_SNAMES[UCH_SW],modex);     
}

if (temp4==2) mode=1; else mode=0;        
LCD_setxy(0,4);              
LCD_wrsf("DEST:   ",mode);

if (mode==1) { 
if (temp5==1) modex=2; else modex=1;  
} else modex=0;
if (DEST_CH<9) tmp=DEST_CH+49; else tmp=DEST_CH+56; 
LCD_char(tmp,modex);

if (temp4==3) mode=1; else mode=0;        
LCD_setxy(0,5);
LCD_wrsf("SOURCE: ",mode);

if (SOURSE_TYPE==0) { 
if (mode==1) { 
if (temp5==1) modex=2; else modex=1;  
} else modex=0;
LCD_wrsf("UCH ",modex);

if (mode==1) { 
if (temp5==2) modex=2; else modex=1;  
} else modex=0;
LCD_wrsf(UCH_SNAMES[SOURSE_CH],modex);

} 

else { 
if (mode==1) { 
if (temp5==1) modex=2; else modex=1;  
} else modex=0;
LCD_wrsf("LCH ",modex);

if (mode==1) { 
if (temp5==2) modex=2; else modex=1;  
} else modex=0;
if (SOURSE_CH<9) tmp=SOURSE_CH+49; else tmp=SOURSE_CH+56; 
LCD_char(tmp,modex);  
} 

if (temp4==4) mode=1; else mode=0;        
LCD_setxy(0,6);
LCD_wrsf("MIX %: ",mode);

if (mode==1) { 
if (temp5==1) modex=2; else modex=1;  
} else modex=0;

if (PROC_SOURSE==0) { 
LCD_wrsf("FIX ",modex);

if (mode==1) { 
if (temp5==2) modex=2; else modex=1;  
} else modex=0;

if (MIX_VAL<0) { LCD_char('-',modex); MX_VAL=-MIX_VAL; } else { LCD_char('+',modex); MX_VAL=MIX_VAL;}
LCD_dec(MX_VAL,3,modex);
} 

else { 
LCD_wrsf("UCH ",modex);

if (mode==1) { 
if (temp5==2) modex=2; else modex=1;  
} else modex=0;

if (MIX_INV!=0) { LCD_char('-',modex); } else LCD_char('+',modex);  

LCD_char(' ',mode);

if (mode==1) { 
if (temp5==3) modex=2; else modex=1;  
} else modex=0;
LCD_wrsf(UCH_SNAMES[MIX_UCH],modex);
}

mode=get_mnu_keys(); 
switch (mode) { 

case 238: { 
switch (temp5) { 

case 0: { 

if (temp4>0) temp4--;
break;
}

case 1: { 
switch (temp4) {
case 0: { 
if (ACTIVE==0) ACTIVE=1; else ACTIVE=0;
break;
}

case 1: { 
if (MIX_SW==0) MIX_SW=1; else MIX_SW=0;
break;
}

case 2: { 
if (DEST_CH<(rmodel.CHANNELS.LCH_COUNT-1)) DEST_CH++;
break;
}
case 3: { 
if (SOURSE_TYPE==0) SOURSE_TYPE=1; else { 
SOURSE_TYPE=0; }
SOURSE_CH=0;
break;
}
case 4: { 
if (PROC_SOURSE==0) PROC_SOURSE=1; else PROC_SOURSE=0;
break;
}
}
break;
}

case 2: {
switch (temp4) {
case 1: { 
if (SW_INV==0) SW_INV=1; else SW_INV=0;
break;
}

case 3: { 
if (SOURSE_TYPE==1) {                                          
if (SOURSE_CH<(rmodel.CHANNELS.LCH_COUNT-1)) SOURSE_CH++;
else SOURSE_CH=0;
}  else

if (SOURSE_CH<13) SOURSE_CH++; else SOURSE_CH=0;
break;
}
case 4: { 
if (PROC_SOURSE==0) { 
if (MIX_VAL<125) MIX_VAL++; 
} 
else { 
if (MIX_INV==0) MIX_INV=1; else MIX_INV=0;
}
break;
}
}
break;
}

case 3: { 
switch (temp4) {
case 1: { 
if (UCH_SW<13) UCH_SW++; 
break;
}

case 4: { 
if (MIX_UCH<13) MIX_UCH++; 
break;
}
}

break;
}

}
break; 
}

case 246: {  
switch (temp5) {
case 0: { 

if (temp4<4) temp4++;
break;
}

case 1: { 
switch (temp4) {
case 0: { 
if (ACTIVE==0) ACTIVE=1; else ACTIVE=0;
break;
}

case 1: { 
if (MIX_SW==0) MIX_SW=1; else MIX_SW=0;
break;
}

case 2: { 
if (DEST_CH>0) DEST_CH--;
break;
}
case 3: { 
if (SOURSE_TYPE==0) SOURSE_TYPE=1; else { 
SOURSE_TYPE=0; SOURSE_CH=0; }
break;
}
case 4: { 
if (PROC_SOURSE==0) {
PROC_SOURSE=1;
MIX_VAL=0; 
}
else { 
PROC_SOURSE=0;
MIX_VAL=100;
}
break;
}
}
break;
}

case 2: {
switch (temp4) {
case 1: { 
if (SW_INV==0) SW_INV=1; else SW_INV=0;
break;
}

case 3: { 
if (SOURSE_CH>0) SOURSE_CH--;

if ((SOURSE_TYPE==0) && (SOURSE_CH>13)) SOURSE_CH=0;
break;
}
case 4: { 
if (PROC_SOURSE==0) { 
if (MIX_VAL>-125) MIX_VAL--; 
} 
else { 
if (MIX_INV==0) MIX_INV=1; else MIX_INV=0;
}
break;
}
}
break;
}

case 3: { 
switch (temp4) {
case 1: { 
if (UCH_SW>7) UCH_SW--; 
break;
}

case 4: { 
if (MIX_UCH>0) MIX_UCH--; 
break;
}
}

break;
}
}
break; 
} 

case 250: {  
temp3=0; 
resetKeyReader(); 
getMixCount(FMODE_NUM);
mixtochan=mixercount/rmodel.CHANNELS.PPM_CH_COUNT;
mixtochanlast=mixercount%rmodel.CHANNELS.PPM_CH_COUNT;                  
break; }

case 252: {  
switch (temp4) { 
case 0: {  
if (temp5<1) temp5++; else temp5=0;
break;
}

case 1: {  
if (MIX_SW==0) { 
if (temp5<1) temp5++; else temp5=0; } 
else {  
if (temp5<3) temp5++; else temp5=0; }
break;
}

case 2: {  
if (temp5<1) temp5++; else temp5=0;
break;
}

case 3: {  
if (temp5<2) temp5++; else temp5=0;
break;
}

case 4: {  
if (PROC_SOURSE==0) { 
if (temp5<2) temp5++; else temp5=0; }
else { if (temp5<3) temp5++; else temp5=0; }
break;
}
}
break; } 

case 222: {  
switch (temp4) { 
case 0: {  
if (temp5<1) temp5++;
break;
}

case 1: {  
if (MIX_SW==0) { 
if (temp5<1) temp5++; } 
else {  
if (temp5<3) temp5++; }
break;
}

case 2: {  
if (temp5<1) temp5++;
break;
}

case 3: {  
if (temp5<2) temp5++;
break;
}

case 4: {  
if (PROC_SOURSE==0) { 
if (temp5<2) temp5++; }
else if (temp5<3) temp5++; 
break;
}

}
break; 
}

case 190: { 
if (temp5>0) temp5--;
break; 
}
} 

if ((ACTIVE==0) && (temp3==0)) {
for (tmp=mixnum;tmp<40;tmp++) 
rmodel.FMODE[fmode].MIXER[tmp]=rmodel.FMODE[fmode].MIXER[(unsigned char) (tmp+1)];
}  

else {
rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.ACTIVE=ACTIVE;  

rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.MIX_SW=MIX_SW; 

rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.UCH_SW=UCH_SW-7; 
rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.SW_INV=SW_INV;

rmodel.FMODE[fmode].MIXER[mixnum].CH_NUM.CH_DEST=DEST_CH; 

rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.SOURSE_TYPE=SOURSE_TYPE; 

rmodel.FMODE[fmode].MIXER[mixnum].CH_NUM.CH_SOURSE=SOURSE_CH; 

rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.PROC_SOURSE=PROC_SOURSE; 
if (PROC_SOURSE==0) 
rmodel.FMODE[fmode].MIXER[mixnum].MIX_VAL=MIX_VAL; 
else rmodel.FMODE[fmode].MIXER[mixnum].MIX_VAL=MIX_UCH+MIX_INV*16; 

}
}

void menu_FMODE_MIXERS() {
unsigned char fmode;

unsigned char offs; 
unsigned char i;

unsigned char x; 
unsigned char y; 
unsigned int ii; 

unsigned char mode; 
unsigned char MIX_SW, SOURSE_TYPE, PROC_SOURSE; 
unsigned char mixnum; 
unsigned char UCH_SW; 

unsigned char CH_DEST; 
unsigned char CH_SOURSE; 
unsigned char tmp; 
signed char S_MIX_VAL; 
unsigned char MIX_VAL; 
unsigned char MIX_UCH; 
unsigned char MIX_INV; 
unsigned char mixmax; 

if (temp1==0) { 
temp2=0; 
temp3=0; 
temp4=0; 
temp5=0; 
temp1=1; 
ModelChange=1; 
}

switch (numitem_cur) {         
case 113: { fmode=0; break; }
case 118: { fmode=1; break; }
case 123: { fmode=2; break; }
}

LCD_setxy(0,0); LCD_wrsf("       MIXER  EDIT       ",1);

if (temp3==3) { 

for (x=0;x<2;x++) { 
for (y=0;y<4;y++) { 
if ((x*4+y)<rmodel.CHANNELS.PPM_CH_COUNT) { 

LCD_setxy(10+x*60,y+2); 
LCD_wrsf("CH",0); LCD_dec((unsigned char)(x*4+y+1),1,0);
LCD_char(' ',0);

if ((CH_PPM[(unsigned char)(x*4+y)]>=rmodel.CHANNELS.CH_EPL[(unsigned char)(x*4+y)]) && 
(CH_PPM[(unsigned char)(x*4+y)]<=rmodel.CHANNELS.CH_EPR[(unsigned char)(x*4+y)]))  {

ii=(CH_PPM[(unsigned char)(x*4+y)] - rmodel.CHANNELS.CH_EPL[(unsigned char)(x*4+y)]);

ii=ii /
(( rmodel.CHANNELS.CH_EPR[(unsigned char)(x*4+y)] - 
rmodel.CHANNELS.CH_EPL[(unsigned char)(x*4+y)]) / 25) ;

for (i=0;i<(unsigned char)ii; i++) {
LCD_out(0x7E);     
}

while (i<25) {
LCD_out(0x10);
i++;
} 
}  

else {
if (CH_PPM[(unsigned char)(x*4+y)]<=rmodel.CHANNELS.CH_EPL[(unsigned char)(x*4+y)])
LCD_wrsf("<MIN ",2); else LCD_wrsf(">MAX ",2);

}

}
}
}      

mode=get_mnu_keys(); 
switch (mode) { 
case 250: {  
temp3=0; 
resetKeyReader(); 
break; }             

case 222: {  
temp3=3; 
break; }

case 190: { 
temp3=2; 
break; }
} 

} 

else

if (temp3==2) { 

for (x=0;x<2;x++) { 
for (y=0;y<4;y++) { 
if ((x*4+y)<rmodel.CHANNELS.PPM_CH_COUNT) {
LCD_setxy(10+x*65,y+2); 
LCD_wrsf("CH",0); LCD_dec((unsigned char)(x*4+y+1),1,0);
LCD_char(' ',0);
LCD_dec(CH_PPM[(unsigned char)(x*4+y)],4,0);
}
}
}

mode=get_mnu_keys(); 
switch (mode) { 
case 250: {  
temp3=0; 
resetKeyReader(); 
break; }             

case 222: {  
temp3=3; 
break; }

case 190: { 
temp3=2; 
break; }
} 

} 

else

if (temp3==1) {  
FMODE_MIXERS_editmix(fmode, temp2);   
}
else 
{  

LCD_setxy(0,1); LCD_wrsf("NO TYP SWIT. D SOUR PROC.", 0);
mode=0;
if (temp2>5) offs=temp2-5; else offs=0;

for (i=0;i<6;i++) {

mixmax=39;
mixnum=i+offs;

LCD_setxy(0,2+i); 

if (mixnum==temp2) mode=1; else mode=0; 

if (rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.ACTIVE==1) { 

LCD_dec((unsigned char)(mixnum+1),2,mode);  
LCD_char(' ',mode);

MIX_SW=rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.MIX_SW;
if (MIX_SW==1) { 
LCD_char('S',mode); } else { LCD_char('-',mode); }

SOURSE_TYPE=rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.SOURSE_TYPE;
if (SOURSE_TYPE==1) { 
LCD_char('L',mode); } else { LCD_char('U',mode); }

PROC_SOURSE=rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.PROC_SOURSE;
if (PROC_SOURSE==1) { 
LCD_char('U',mode); } else { LCD_char('F',mode); }

LCD_char(' ',mode); 

if (MIX_SW==1) { 

UCH_SW=rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.UCH_SW;

if (rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.SW_INV==1) LCD_char('-',mode); 
else LCD_char(' ',mode);

LCD_wrsf(UCH_SNAMES[(unsigned char)(UCH_SW+7)],mode); 
} 
else { 
LCD_wrsf("-----",mode);
}
LCD_char(' ',mode);

CH_DEST=rmodel.FMODE[fmode].MIXER[mixnum].CH_NUM.CH_DEST; 
if (CH_DEST<9) tmp=CH_DEST+49; else tmp=CH_DEST+56; 
LCD_char(tmp,mode);
LCD_char(' ', mode);

CH_SOURSE=rmodel.FMODE[fmode].MIXER[mixnum].CH_NUM.CH_SOURSE; 

if (SOURSE_TYPE==1) { 
LCD_char(' ', mode);
if (CH_SOURSE<9) tmp=CH_SOURSE+49; else tmp=CH_SOURSE+56; 
LCD_char(tmp,mode);
LCD_char(' ', mode);
LCD_char(' ', mode);
}
else { 
LCD_wrsf(UCH_SNAMES[CH_SOURSE],mode);
}
LCD_char(' ',mode);

if (PROC_SOURSE==1) { 
MIX_VAL=rmodel.FMODE[fmode].MIXER[mixnum].MIX_VAL; 
MIX_UCH=MIX_VAL & 0x0F; 
if ((MIX_VAL-MIX_UCH)!=0) { LCD_char('-',mode); MIX_INV=1; 
} 
else { MIX_INV=0; 
LCD_char(' ',mode); }

LCD_wrsf(UCH_SNAMES[MIX_UCH],mode);            

} else { 
S_MIX_VAL=rmodel.FMODE[fmode].MIXER[mixnum].MIX_VAL;
if (S_MIX_VAL<0) { LCD_char('-',mode); S_MIX_VAL=-S_MIX_VAL; } else LCD_char('+',mode);
LCD_dec(S_MIX_VAL,3,mode); 
}
} 
else { 
LCD_wrsf("-- --- ----- - ---- -----", mode);
mixmax=mixnum;
break; 
}
} 

mode=get_mnu_keys(); 
switch (mode) { 

case 238: { 
if (temp2>0) temp2--;
break; } 

case 246: {  
if (temp2<mixmax) temp2++;
break; } 

case 250: {  
temp2=0; 
temp3=0; 
temp4=0;
temp5=0;
temp1=0; 
resetKeyReader(); 
menu_exe=0;
break; }

case 252: {  
temp3=1; 
temp4=0; 
temp5=0; 
resetKeyReader(); 
break; } 

case 222: {  
temp3=3; 
break; }

case 190: { 
temp3=2; 
break; }
} 

} 

} 

void FILE_RESET() {
unsigned char rkey,i,j;

rmodel.MODEL_TYPE=0;      

rmodel.MODEL_NAME[0]='N'; 
rmodel.MODEL_NAME[1]='E';
rmodel.MODEL_NAME[2]='W';
rmodel.MODEL_NAME[3]='M';
rmodel.MODEL_NAME[4]='O';
rmodel.MODEL_NAME[5]='D';
rmodel.MODEL_NAME[6]='E';
rmodel.MODEL_NAME[7]='L';

rmodel.MODEL_FLYTIMER=600;

rmodel.MODEL_LIVETIMER=0;

rmodel.FMODE_COUNT=1;

for (rkey=0; rkey<16; rkey++) { 

rmodel.CHANNELS.CH_EPL[rkey]=1000;
rmodel.CHANNELS.CH_EPR[rkey]=2000;

rmodel.CHANNELS.LCHDELDN[rkey]=0;
rmodel.CHANNELS.LCHDELUP[rkey]=0; 

rmodel.CHANNELS.LCH_REV[rkey]=0;

rmodel.FMODE[0].LCH_MIDLE[rkey]=1500; 
rmodel.FMODE[1].LCH_MIDLE[rkey]=1500; 
rmodel.FMODE[2].LCH_MIDLE[rkey]=1500; 

rmodel.FMODE[0].LCH_CURVE[rkey].active=0; 
rmodel.FMODE[0].LCH_CURVE[rkey].expon=0; 

rmodel.FMODE[0].LCH_CURVE[rkey].point[0]=-100;
rmodel.FMODE[1].LCH_CURVE[rkey].point[0]=-100;
rmodel.FMODE[2].LCH_CURVE[rkey].point[0]=-100;      

rmodel.FMODE[0].LCH_CURVE[rkey].point[1]=-75;
rmodel.FMODE[1].LCH_CURVE[rkey].point[1]=-75;
rmodel.FMODE[2].LCH_CURVE[rkey].point[1]=-75;

rmodel.FMODE[0].LCH_CURVE[rkey].point[2]=-50;
rmodel.FMODE[1].LCH_CURVE[rkey].point[2]=-50;
rmodel.FMODE[2].LCH_CURVE[rkey].point[2]=-50;      

rmodel.FMODE[0].LCH_CURVE[rkey].point[3]=-25;
rmodel.FMODE[1].LCH_CURVE[rkey].point[3]=-25;
rmodel.FMODE[2].LCH_CURVE[rkey].point[3]=-25;

rmodel.FMODE[0].LCH_CURVE[rkey].point[4]=0;
rmodel.FMODE[1].LCH_CURVE[rkey].point[4]=0;
rmodel.FMODE[2].LCH_CURVE[rkey].point[4]=0;      

rmodel.FMODE[0].LCH_CURVE[rkey].point[5]=25;
rmodel.FMODE[1].LCH_CURVE[rkey].point[5]=25;
rmodel.FMODE[2].LCH_CURVE[rkey].point[5]=25;      

rmodel.FMODE[0].LCH_CURVE[rkey].point[6]=50;
rmodel.FMODE[1].LCH_CURVE[rkey].point[6]=50;
rmodel.FMODE[2].LCH_CURVE[rkey].point[6]=50;      

rmodel.FMODE[0].LCH_CURVE[rkey].point[7]=75;
rmodel.FMODE[1].LCH_CURVE[rkey].point[7]=75;
rmodel.FMODE[2].LCH_CURVE[rkey].point[7]=75;      

rmodel.FMODE[0].LCH_CURVE[rkey].point[8]=100;
rmodel.FMODE[1].LCH_CURVE[rkey].point[8]=100;
rmodel.FMODE[2].LCH_CURVE[rkey].point[8]=100;       
}

rmodel.CHANNELS.LCH_COUNT=8;   

for (rkey=0; rkey<8; rkey++) { 
rmodel.CHANNELS.FILTER[rkey].FILTER_TYPE=0;
rmodel.CHANNELS.FILTER[rkey].VAL1=0; 
}

for (i=0;i<3;i++) { 

rmodel.FMODE[i].TRIMSTEP=1; 

for (j=0;j<40;j++) { 
rmodel.FMODE[i].MIXER[j].MIX_TYPE.ACTIVE=0;       
rmodel.FMODE[i].MIXER[j].MIX_TYPE.SOURSE_TYPE=0;  
rmodel.FMODE[i].MIXER[j].MIX_TYPE.PROC_SOURSE=0;  
rmodel.FMODE[i].MIXER[j].MIX_TYPE.MIX_SW=0;       
rmodel.FMODE[i].MIXER[j].MIX_TYPE.SW_INV=0;       
rmodel.FMODE[i].MIXER[j].MIX_TYPE.UCH_SW=0;       
rmodel.FMODE[i].MIXER[j].CH_NUM.CH_SOURSE=0;      
rmodel.FMODE[i].MIXER[j].CH_NUM.CH_DEST=0;        
rmodel.FMODE[i].MIXER[j].MIX_VAL=100;             
}
}

for (rkey=0; rkey<14; rkey++) { 
rmodel.UCH[rkey].UCH_LEFT=-100;
rmodel.UCH[rkey].UCH_RIGHT=100;
}

rmodel.CHANNELS.PPM_CH_COUNT=8; 
PPM_PAUSE=0;     
PPM_CUR_CH_NUM=0; 

for (i=0;i<rmodel.CHANNELS.LCH_COUNT;i++) {
LCH_LEN[i]=rmodel.FMODE[FMODE_NUM].LCH_MIDLE[i];
}

for (i=0; i<8; i++) rmodel.PPM_TO_LCH_CAP[i]=0; 

resetKeyReader(); 
}

void menu_FILE_RESET() { 
unsigned char mode;

LCD_setxy(0,0);  LCD_wrsf(" RESET CURRENT MODEL     ",1);

LCD_setxy(0,2);  LCD_wrsf(" to cancel press MENU   >",0);

LCD_setxy(0,6);  LCD_wrsf("to process press - EXIT >",0);

mode=get_mnu_keys(); 
switch (mode) { 

case 238: { 
break; } 

case 246: {  
break; } 

case 252: {  
temp2=0; 
temp3=0; 
temp4=0;
temp5=0;
temp1=0; 
resetKeyReader(); 
menu_exe=0;
break; }

case 250: {  
FILE_RESET();
E_CurModelNum=255;
ModelChange=0;
temp2=0; 
temp3=0; 
temp4=0;
temp5=0;
temp1=0; 
resetKeyReader(); 
menu_exe=0;                  
break; } 

case 222: {  
break; }

case 190: { 
break; }
} 

}

void OpenModel(unsigned char filenum) {
unsigned char i,j,k,tmp; 
unsigned int  ti,i1,i2;

FILE_RESET(); 
FMODE_NUM=0;

if (fileToRead(filenum)==0) { 

rmodel.MODEL_TYPE=fileRead();

for(i=0;i<8;i++) {
rmodel.MODEL_NAME[i]=fileRead();
}

i1=fileRead();
i2=fileRead();
ti=i1+i2*256;
rmodel.MODEL_FLYTIMER=ti;
flyCurrTimer=rmodel.MODEL_FLYTIMER;

i1=fileRead();
i2=fileRead();
ti=i1+i2*256;
rmodel.MODEL_LIVETIMER=ti;

rmodel.CHANNELS.LCH_COUNT=fileRead(); 

for (i=0; i<rmodel.CHANNELS.LCH_COUNT; i++) {

i1=fileRead();
i2=fileRead();
ti=i1+i2*256;
rmodel.CHANNELS.CH_EPL[i]=ti;
} 

for (i=0; i<rmodel.CHANNELS.LCH_COUNT; i++) {

i1=fileRead();
i2=fileRead();
ti=i1+i2*256;
rmodel.CHANNELS.CH_EPR[i]=ti;
} 

for (i=0; i<rmodel.CHANNELS.LCH_COUNT; i++) {

rmodel.CHANNELS.LCHDELDN[i]=fileRead();
} 

for (i=0; i<rmodel.CHANNELS.LCH_COUNT; i++) {

rmodel.CHANNELS.LCHDELUP[i]=fileRead();
} 

for (i=0; i<rmodel.CHANNELS.LCH_COUNT; i++) {

rmodel.CHANNELS.LCH_REV[i]=fileRead();
} 

rmodel.CHANNELS.PPM_CH_COUNT=fileRead();

for (i=0; i<rmodel.CHANNELS.PPM_CH_COUNT; i++) {

rmodel.CHANNELS.FILTER[i].FILTER_TYPE=fileRead(); 

i1=fileRead();
i2=fileRead();
ti=i1+i2*256;
rmodel.CHANNELS.FILTER[i].VAL1=ti;
}

i=fileRead();
while (i!=0) {
rmodel.UCH[i-1].UCH_LEFT=fileRead();
rmodel.UCH[i-1].UCH_RIGHT=fileRead();
i=fileRead();
}

rmodel.FMODE_COUNT=fileRead();
for (i=0;i<rmodel.FMODE_COUNT;i++) {  

rmodel.FMODE[i].FMODE_NAME=fileRead();

rmodel.FMODE[i].TRIMSTEP=fileRead();

for (j=0;j<7;j++) {
rmodel.FMODE[i].UCH_TRIMMER[j]=fileRead();
}

for (j=0;j<rmodel.CHANNELS.LCH_COUNT;j++) {
i1=fileRead();
i2=fileRead();
ti=i1+i2*256;
rmodel.FMODE[i].LCH_MIDLE[j]=ti;
}

for (j=0;j<rmodel.CHANNELS.LCH_COUNT;j++) {
switch (fileRead()) {
case 0 : { 
rmodel.FMODE[i].LCH_CURVE[j].active=0; 
break;
}
case 1 : { 
rmodel.FMODE[i].LCH_CURVE[j].active=1; 
for (k=0;k<9;k++) { 
rmodel.FMODE[i].LCH_CURVE[j].point[k]=fileRead();
}
break;
}
case 100:{ 
rmodel.FMODE[i].LCH_CURVE[j].active=1; 
rmodel.FMODE[i].LCH_CURVE[j].expon=fileRead(); 
for (k=0;k<9;k++) { 
rmodel.FMODE[i].LCH_CURVE[j].point[k]=fileRead();
}           
break;
}   
}
}

k=fileRead(); 

for (j=0;j<k;j++) {
tmp=fileRead(); 
rmodel.FMODE[i].MIXER[j].MIX_TYPE.ACTIVE=1;          
if ((tmp&0b01000000)!=0) rmodel.FMODE[i].MIXER[j].MIX_TYPE.SOURSE_TYPE=1; 
else rmodel.FMODE[i].MIXER[j].MIX_TYPE.SOURSE_TYPE=0;

if ((tmp&0b00100000)!=0) rmodel.FMODE[i].MIXER[j].MIX_TYPE.PROC_SOURSE=1; 
else rmodel.FMODE[i].MIXER[j].MIX_TYPE.PROC_SOURSE=0; 

if ((tmp&0b00010000)!=0) rmodel.FMODE[i].MIXER[j].MIX_TYPE.MIX_SW=1;
else rmodel.FMODE[i].MIXER[j].MIX_TYPE.MIX_SW=0;

if ((tmp&0b00001000)!=0) rmodel.FMODE[i].MIXER[j].MIX_TYPE.SW_INV=1;
else rmodel.FMODE[i].MIXER[j].MIX_TYPE.SW_INV=0;

rmodel.FMODE[i].MIXER[j].MIX_TYPE.UCH_SW=tmp & 0x07;

tmp=fileRead(); 
rmodel.FMODE[i].MIXER[j].CH_NUM.CH_SOURSE=tmp>>4;
rmodel.FMODE[i].MIXER[j].CH_NUM.CH_DEST=tmp & 0x0F;   

rmodel.FMODE[i].MIXER[j].MIX_VAL=fileRead(); 
}
}    

}

for (i=0; i<8; i++) mch[i]=0; 

for (i=0;i<16;i++) { 
LCH_LEN[i]=rmodel.FMODE[FMODE_NUM].LCH_MIDLE[i];
OLD_LCH_LEN[i]=rmodel.FMODE[FMODE_NUM].LCH_MIDLE[i];
}

CalcCurveORD(); 
getMixCount(FMODE_NUM);
mixtochan=mixercount/rmodel.CHANNELS.PPM_CH_COUNT;
mixtochanlast=mixercount%rmodel.CHANNELS.PPM_CH_COUNT;

}

void menu_MODEL_OPEN() {
unsigned char i, offs, mode, tmp; 

if (temp1==0) { 
temp1=1; 
temp2=0; 
}

LCD_setxy(0,0); LCD_wrsf("     OPEN MODEL FILE     ",1);

LCD_setxy(0,2); LCD_wrsf("NN TYPE   MODELNAME SIZE ",0);

if (temp2>4) offs=temp2-4; else offs=0;

for (i=0; i<5; i++) {      LCD_setxy(0,3+i);
if (temp2==(i+offs)) mode=1; else mode=0; 
LCD_dec((unsigned char)(i+offs),2,mode); 
LCD_char(' ', mode); 

if (fileToRead(i+offs)==0) { 

tmp=fileRead(); 
LCD_wrsf(MODEL_TYPE[tmp],mode); 

LCD_char(' ',mode); 

for (tmp=0;tmp<8; tmp++) { 
LCD_char(fileRead(),mode);
}

LCD_char(' ',mode);
LCD_char(' ', mode);
LCD_char(' ', mode);
LCD_char(' ', mode);

tmp=fileSize(i+offs);
LCD_dec(tmp,2,mode);    
}
}
mode=get_mnu_keys(); 
switch (mode) { 

case 238: { 
if (temp2>0) temp2--;
break; } 

case 246: {  
if (temp2<15) temp2++;
break; } 

case 250: {  
temp2=0; 
temp3=0; 
temp4=0;
temp5=0;
temp1=0; 
resetKeyReader(); 
menu_exe=0;
break; }

case 252: {  
OpenModel(temp2);
E_CurModelNum=temp2;
temp2=0; 
temp3=0; 
temp4=0;
temp5=0;
temp1=0; 
resetKeyReader(); 
menu_exe=0;                  
break; } 

case 222: {  
break; }

case 190: { 
break; }
} 

}

void SaveModel(unsigned filenum) {
unsigned char i,j,k,tmp; 

ppmStop=1; 

while (ppmStop!=2);

printMess=1;
fileDelete(filenum); 
printMess=0;

if (fileToWrite(filenum)==0) { 

fileWrite(rmodel.MODEL_TYPE);

for(i=0;i<8;i++) {
fileWrite(rmodel.MODEL_NAME[i]);
}

fileWrite((unsigned char)(rmodel.MODEL_FLYTIMER%256));
fileWrite((unsigned char)(rmodel.MODEL_FLYTIMER/256));

fileWrite((unsigned char)(rmodel.MODEL_LIVETIMER%256));
fileWrite((unsigned char)(rmodel.MODEL_LIVETIMER/256));

fileWrite(rmodel.CHANNELS.LCH_COUNT); 

for (i=0; i<rmodel.CHANNELS.LCH_COUNT; i++) {

fileWrite((unsigned char)(rmodel.CHANNELS.CH_EPL[i]%256));
fileWrite((unsigned char)(rmodel.CHANNELS.CH_EPL[i]/256));
} 

for (i=0; i<rmodel.CHANNELS.LCH_COUNT; i++) {

fileWrite((unsigned char)(rmodel.CHANNELS.CH_EPR[i]%256));
fileWrite((unsigned char)(rmodel.CHANNELS.CH_EPR[i]/256));
} 

for (i=0; i<rmodel.CHANNELS.LCH_COUNT; i++) {

fileWrite(rmodel.CHANNELS.LCHDELDN[i]);
} 

for (i=0; i<rmodel.CHANNELS.LCH_COUNT; i++) {

fileWrite(rmodel.CHANNELS.LCHDELUP[i]);
} 

for (i=0; i<rmodel.CHANNELS.LCH_COUNT; i++) {

fileWrite(rmodel.CHANNELS.LCH_REV[i]);
} 

fileWrite(rmodel.CHANNELS.PPM_CH_COUNT);

for (i=0; i<rmodel.CHANNELS.PPM_CH_COUNT; i++) {

fileWrite(rmodel.CHANNELS.FILTER[i].FILTER_TYPE); 

fileWrite(rmodel.CHANNELS.FILTER[i].VAL1%256);
fileWrite(rmodel.CHANNELS.FILTER[i].VAL1/256);
}

for (i=0;i<14; i++) { 

tmp=0;
for (j=0; j<40; j++) { 
for (k=0; k<3; k++) { 
if ((rmodel.FMODE[k].MIXER[j].MIX_TYPE.ACTIVE==1) &&
(rmodel.FMODE[k].MIXER[j].MIX_TYPE.PROC_SOURSE==1) ) {
if (i==(rmodel.FMODE[k].MIXER[j].MIX_VAL&0x0F)) {
tmp=1;  
break;
} 
}   
} 
if (tmp==1) break;
}

if (tmp==1) {
fileWrite(i+1);
fileWrite(rmodel.UCH[i].UCH_LEFT);
fileWrite(rmodel.UCH[i].UCH_RIGHT);
}
}
fileWrite(0); 

fileWrite(rmodel.FMODE_COUNT);
for (i=0;i<rmodel.FMODE_COUNT;i++) {  

fileWrite(rmodel.FMODE[i].FMODE_NAME);

fileWrite(rmodel.FMODE[i].TRIMSTEP);

for (j=0;j<7;j++) {
fileWrite(rmodel.FMODE[i].UCH_TRIMMER[j]);
}

for (j=0;j<rmodel.CHANNELS.LCH_COUNT;j++) {
fileWrite(rmodel.FMODE[i].LCH_MIDLE[j]%256);
fileWrite(rmodel.FMODE[i].LCH_MIDLE[j]/256);
}

for (j=0;j<rmodel.CHANNELS.LCH_COUNT;j++) {
if (rmodel.FMODE[i].LCH_CURVE[j].active!=0) { 

if (rmodel.FMODE[i].LCH_CURVE[j].expon==0) 
fileWrite(1); 
else { 
fileWrite(100); 
fileWrite(rmodel.FMODE[i].LCH_CURVE[j].expon); 
}

if (rmodel.FMODE[i].LCH_CURVE[j].active!=0) { 
for (k=0;k<9;k++) { 
fileWrite(rmodel.FMODE[i].LCH_CURVE[j].point[k]);
}      
}
} else fileWrite(0); 
}

k=0; 
while (rmodel.FMODE[i].MIXER[k].MIX_TYPE.ACTIVE==1) k++;
fileWrite(k); 

for (j=0;j<k;j++) {
tmp=0x80;

if (rmodel.FMODE[i].MIXER[j].MIX_TYPE.SOURSE_TYPE==1) tmp=tmp|0b01000000;
if (rmodel.FMODE[i].MIXER[j].MIX_TYPE.PROC_SOURSE==1) tmp=tmp|0b00100000;
if (rmodel.FMODE[i].MIXER[j].MIX_TYPE.MIX_SW==1)      tmp=tmp|0b00010000;
if (rmodel.FMODE[i].MIXER[j].MIX_TYPE.SW_INV==1)      tmp=tmp|0b00001000;
tmp=tmp|rmodel.FMODE[i].MIXER[j].MIX_TYPE.UCH_SW;           
fileWrite(tmp); 
tmp=0;
tmp=tmp|rmodel.FMODE[i].MIXER[j].CH_NUM.CH_SOURSE;
tmp=tmp<<4;
tmp=tmp|rmodel.FMODE[i].MIXER[j].CH_NUM.CH_DEST;   
fileWrite(tmp); 
fileWrite(rmodel.FMODE[i].MIXER[j].MIX_VAL); 
}
}    

} else { 

messStr1="     V-DISK  ERROR !     ";

messStr2="    NO FREE  SPACE !     ";
messStr3="   delete old models     ";
messStr4="   or format V-Disk      ";
printMess=1;
}

ppmStop=0;
}

void menu_FILE_ERASE() {
unsigned char i, offs, mode, tmp; 

if (temp1==0) { 
temp1=1; 
temp2=0; 
}

LCD_setxy(0,0); LCD_wrsf("   ERASE  MODEL AS..     ",1);

LCD_setxy(0,2); LCD_wrsf("NN TYPE   MODELNAME SIZE ",0);

if (temp2>4) offs=temp2-4; else offs=0;

for (i=0; i<5; i++) {      LCD_setxy(0,3+i);
if (temp2==(i+offs)) mode=1; else mode=0; 
LCD_dec((unsigned char)(i+offs),2,mode); 
LCD_char(' ', mode); 

if (fileToRead(i+offs)==0) { 

tmp=fileRead(); 
LCD_wrsf(MODEL_TYPE[tmp],mode); 

LCD_char(' ',mode); 

for (tmp=0;tmp<8; tmp++) { 
LCD_char(fileRead(),mode);
}

LCD_char(' ',mode);
LCD_char(' ', mode);
LCD_char(' ', mode);
LCD_char(' ', mode);

tmp=fileSize(i+offs);
LCD_dec(tmp,2,mode);    
}
}
mode=get_mnu_keys(); 
switch (mode) { 

case 238: { 
if (temp2>0) temp2--;
break; } 

case 246: {  
if (temp2<15) temp2++;
break; } 

case 250: {  
temp2=0; 
temp3=0; 
temp4=0;
temp5=0;
temp1=0; 
resetKeyReader(); 
menu_exe=0;
break; }

case 252: {  
fileDelete(temp2);
temp2=0; 
temp3=0; 
temp4=0;
temp5=0;
temp1=0; 
resetKeyReader(); 
menu_exe=0;                  
break; } 

case 222: {  
break; }

case 190: { 
break; }
} 

}

void menu_MODEL_SAVE_AS() {
unsigned char i, offs, mode, tmp; 

if (temp1==0) { 
temp1=1; 
temp2=0; 
}

LCD_setxy(0,0); LCD_wrsf("     SAVE MODEL AS..     ",1);

LCD_setxy(0,2); LCD_wrsf("NN TYPE   MODELNAME SIZE ",0);

if (temp2>4) offs=temp2-4; else offs=0;

for (i=0; i<5; i++) {      LCD_setxy(0,3+i);
if (temp2==(i+offs)) mode=1; else mode=0; 
LCD_dec((unsigned char)(i+offs),2,mode); 
LCD_char(' ', mode); 

if (fileToRead(i+offs)==0) { 

tmp=fileRead(); 
LCD_wrsf(MODEL_TYPE[tmp],mode); 

LCD_char(' ',mode); 

for (tmp=0;tmp<8; tmp++) { 
LCD_char(fileRead(),mode);
}

LCD_char(' ',mode);
LCD_char(' ', mode);
LCD_char(' ', mode);
LCD_char(' ', mode);

tmp=fileSize(i+offs);
LCD_dec(tmp,2,mode);    
}
}
mode=get_mnu_keys(); 
switch (mode) { 

case 238: { 
if (temp2>0) temp2--;
break; } 

case 246: {  
if (temp2<15) temp2++;
break; } 

case 250: {  
temp2=0; 
temp3=0; 
temp4=0;
temp5=0;
temp1=0; 
resetKeyReader(); 
menu_exe=0;
break; }

case 252: {  
E_CurModelNum=temp2;
SaveModel(E_CurModelNum);
if (printMess==0) {

messStr1="       FILE SAVED !      "; 
messStr2="";
messStr3="";
messStr4="";
messStr5="";
printMess=1;
}
temp2=0; 
temp3=0; 
temp4=0;
temp5=0;
temp1=0; 
resetKeyReader(); 
menu_exe=0;                  
break; } 

case 222: {  
break; }

case 190: { 
break; }
} 

}  

void menu_MODEL_SAVE() {
unsigned char mode;

LCD_setxy(0,0);  LCD_wrsf("   SAVE CURRENT MODEL    ",1);

LCD_setxy(0,2);  LCD_wrsf("to process press - MENU >",0);

LCD_setxy(0,6);  LCD_wrsf(" to cancel press EXIT   >",0);

mode=get_mnu_keys(); 
switch (mode) { 

case 238: { 
break; } 

case 246: {  
break; } 

case 250: {  
temp2=0; 
temp3=0; 
temp4=0;
temp5=0;
temp1=0; 
resetKeyReader(); 
menu_exe=0;
break; }

case 252: {  
if (E_CurModelNum<16) SaveModel(E_CurModelNum); 
temp2=0; 
temp3=0; 
temp4=0;
temp5=0;
temp1=0; 
if (printMess==0) {

messStr1="       FILE SAVED !      "; 
messStr2="";
messStr3="";
messStr4="";
messStr5="";
printMess=1;
}                  
resetKeyReader(); 
menu_exe=0;                  
break; } 

case 222: {  
break; }

case 190: { 
break; }
} 
}

void menu_formatVDisk() {
unsigned char mode;

LCD_setxy(0,0);  LCD_wrsf("    FORMAT V-DISK ?      ",1);

LCD_setxy(0,2);  LCD_wrsf("to process press - MENU >",0);

LCD_setxy(0,4);  LCD_wrsf("All data must be deleted!",2);

LCD_setxy(0,6);  LCD_wrsf(" to cancel press EXIT   >",0);

mode=get_mnu_keys(); 
switch (mode) { 

case 238: { 
break; } 

case 246: {  
break; } 

case 250: {  
temp2=0; 
temp3=0; 
temp4=0;
temp5=0;
temp1=0; 
resetKeyReader(); 
menu_exe=0;
break; }

case 252: {  
formatVDisk();
temp2=0; 
temp3=0; 
temp4=0;
temp5=0;
temp1=0; 
if (printMess==0) {

messStr1="   V-DISK  FORMATTED !   ";

messStr2=" File operations enabled";
messStr3=" ";
messStr4=" ";
messStr5=" ";
printMess=1;                   
}
resetKeyReader(); 
menu_exe=0;                  
break; } 

case 222: {  
break; }

case 190: { 
break; }
} 
}

void menu_req_save_model() {
unsigned char mode;

LCD_setxy(0,0);  LCD_wrsf("     MODEL  MODIFIED     ", 1);
LCD_setxy(0,1);  LCD_wrsf("                         ", 0);
LCD_setxy(0,2);  LCD_wrsf("                  SAVE ->", 0);
LCD_setxy(0,3);  LCD_wrsf("                         ", 0);
LCD_setxy(0,4);  LCD_wrsf(" SAVE CHANGES TO V-DISK? ", 2);
LCD_setxy(0,5);  LCD_wrsf("                         ", 0);
LCD_setxy(0,6);  LCD_wrsf("                CANCEL ->", 0);
LCD_setxy(0,7);  LCD_wrsf("                         ", 0);

mode=get_mnu_keys(); 
switch (mode) { 

case 238: { 
break; } 

case 246: {  
break; } 

case 250: {  
resetKeyReader(); 
menu_exe=0;
disp_mode=2;
break; }

case 252: {  
if (E_CurModelNum<16) { 
SaveModel(E_CurModelNum);
menu_exe=0;
disp_mode=2;
}  
else {
menu_proc=menu_MODEL_SAVE_AS;
}
break; } 

case 222: {  
break; }

case 190: { 
break; }
} 
}

void menu_VDISK_INFO(void) {
unsigned char mode, i;

LCD_setxy(0,0);  LCD_wrsf("       V-DISK  INFO      ", 1);

LCD_setxy(0,3);  LCD_wrsf("V-Disk sector col: ", 0); LCD_dec(1952  /E_ClusterSize,3,1);

mode=freesp; 
i=0;
while (mode!=255) {
i++;
mode=VDISK[(unsigned int)mode*E_ClusterSize];
} 

LCD_setxy(0,5);  LCD_wrsf(" free space: ", 0); LCD_dec(i,3,1);

mode=get_mnu_keys(); 
switch (mode) { 

case 238: { 
break; } 

case 246: {  
break; } 

case 250: {  
resetKeyReader(); 
menu_exe=0;
break; }

case 252: {  
break; } 

case 222: {  
break; }

case 190: { 
break; }
} 

}

void menu_CODER_INFO(void) {
unsigned char mode;

LCD_setxy(0,0);  LCD_wrsf("   V-CODER  ver 0.99b    ", 1);
LCD_setxy(0,1);  LCD_wrsf("author: Vitaly V Gorbukov", 0);

LCD_setxy(0,3);  LCD_wrsf(" build: 2324  17.08.2012 ", 0);
LCD_setxy(0,4);  LCD_wrsf(" first use at 21.07.2010 ", 0);

LCD_setxy(0,6);  LCD_wrsf("   for support mail to   ", 0);
LCD_setxy(0,7);  LCD_wrsf("   gorbukov@yandex.ru    ", 1);

mode=get_mnu_keys(); 
switch (mode) { 

case 238: { 
break; } 

case 246: {  
break; } 

case 250: {  
resetKeyReader(); 
menu_exe=0;
break; }

case 252: {  
break; } 

case 222: {  
break; }

case 190: { 
break; }
} 
}

typedef struct {
unsigned char   numitem;  
unsigned char itemstr[12];  
unsigned char  nextitem;  
unsigned char  previtem;  
unsigned char    upitem;  
unsigned char  downitem;  

void            * pvar1; 
void            * pvar2; 
unsigned char   partype; 
tmenu_proc  menu_proc;  

unsigned char *colitemcount; 
unsigned char   colitem; 

} MENU_STRUCT;

flash const MENU_STRUCT menu[]={

{    0   ,"MAIN MENU"      ,       0 ,       0 ,     0 ,       1 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0       },

{    1   ,"FILE"           ,       2 ,       0 ,     0 ,       7 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0       },
{    2   ,"EDIT"           ,       3 ,       1 ,     0 ,      12 ,  &rmodel.MODEL_NAME   ,  0                       , 2          ,  0                 ,           0      ,       0       },
{    3   ,"TIMERS"         ,       4 ,       2 ,     0 ,     132 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0       },
{    4   ,"SYSTEM"         ,       5 ,       3 ,     0 ,      63 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0       },
{    5   ,"INFO"           ,       0 ,       4 ,     0 ,       0 ,  0                    ,  0                       , 0          ,  menu_CODER_INFO   ,           0      ,       0       },

{   63   ,"ALARM"          ,      64 ,       0 ,     4 ,     174 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0       },
{   64   ,"CONTROLS"       ,      65 ,      63 ,     4 ,     157 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0       },
{   65   ,"CONTRAST"       ,     136 ,      64 ,     4 ,       0 ,  0                    ,  0                       , 31         ,  0                 ,           0      ,       0       },
{  136   ,"PPM FORMAT"     ,      66 ,      65 ,     4 ,       0 ,  0                    ,  0                       , 30         ,  0                 ,           0      ,       0             },
{   66   ,"SOUND"          ,     227 ,     136 ,     4 ,     226 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0       },
{  227   ,"KEYS & TRIM"    ,     223 ,      66 ,     4 ,     228 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0       },
{  223   ,"V-DISK"         ,       0 ,     227 ,     4 ,     224 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0       },

{  157   ,"STICK MODE"     ,      67 ,       0 ,    64 ,       0 ,  0                    ,  0                       , 33         ,  0                 ,           0      ,       0       },
{   67   ,"VIEW CALIBR"    ,      68 ,     157 ,    64 ,       0 ,  0                    ,  0                       , 0          ,  menu_SYSTEM_CALIBRATION_INFO, 0      ,       0       },
{   68   ,"CALIBRATION"    ,       0 ,      67 ,    64 ,       0 ,  0                    ,  0                       , 0          ,  menu_SYSTEM_NEW_CALIBRATION,  0      ,       0       },

{    7   ,"RESET MODEL"    ,       8 ,       0 ,     1 ,       0 ,  0                    ,  0                       , 0          , menu_FILE_RESET    ,           0      ,       0       },
{    8   ,"OPEN MODEL"     ,       9 ,       7 ,     1 ,       0 ,  0                    ,  0                       , 0          , menu_MODEL_OPEN    ,           0      ,       0       },
{    9   ,"SAVE MODEL"     ,      10 ,       8 ,     1 ,       0 ,  0                    ,  0                       , 0          , menu_MODEL_SAVE    ,           0      ,       0              },
{   10   ,"SAVE AS.."      ,      11 ,       9 ,     1 ,       0 ,  0                    ,  0                       , 0          , menu_MODEL_SAVE_AS ,           0      ,       0              },
{   11   ,"ERASE MODEL"    ,       0 ,      10 ,     1 ,       0 ,  0                    ,  0                       , 0          , menu_FILE_ERASE    ,           0      ,       0              },

{   12   ,"TYPE"           ,      13 ,       0 ,     2 ,       0 ,  &rmodel.MODEL_TYPE   ,  0                       , 1          ,  0                 ,           0      ,       0              },
{   13   ,"NAME"           ,      14 ,      12 ,     2 ,       0 ,  &rmodel.MODEL_NAME   ,  0                       , 2          ,  menu_EDIT_MODEL_NAME,         0      ,       0           },
{   14   ,"CHANNELS"       ,      15 ,      13 ,     2 ,      69 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0             },
{   15   ,"CONTROLS"       ,      16 ,      14 ,     2 ,      45 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0             },
{   16   ,"FLY MODES"      ,       0 ,      15 ,     2 ,     105 ,  0                    ,  0                       , 0          ,  0                 ,           &rmodel.FMODE_COUNT      ,       0             },

{   69   ,"LCH SET"        ,      70 ,       0 ,    14 ,      17 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0           },
{   70   ,"CH SET"         ,       0 ,      69 ,    14 ,      44 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0           },

{   17   ,"LCH COUNT"      ,      18 ,       0 ,    69 ,       0 ,  &rmodel.CHANNELS.LCH_COUNT  ,  0                , 3          ,  0                 ,           0      ,       0           },
{   18   ,"LCH EPA"        ,      71 ,      17 ,    69 ,      20 ,  0                    ,  0                       , 0          ,  0                 ,           &rmodel.CHANNELS.LCH_COUNT      ,       0             },
{   71   ,"LCH DELAY"      ,      88 ,      18 ,    69 ,      72 ,  0                    ,  0                       , 0          ,  0                 ,           &rmodel.CHANNELS.LCH_COUNT      ,       0             },
{   88   ,"LCH REVERSE"    ,       0 ,      71 ,    69 ,      89 ,  0                    ,  0                       , 0          ,  0                 ,           &rmodel.CHANNELS.LCH_COUNT      ,       0             },

{   89   ,"LCH 1 REV. "     ,     90 ,       0 ,    88 ,       0 ,  &rmodel.CHANNELS.LCH_REV[0]  ,  0               , 9          ,  0                 ,           0      ,       1             },
{   90   ,"LCH 2 REV. "     ,     91 ,      89 ,    88 ,       0 ,  &rmodel.CHANNELS.LCH_REV[1]  ,  0               , 9          ,  0                 ,           0      ,       2             },
{   91   ,"LCH 3 REV. "     ,     92 ,      90 ,    88 ,       0 ,  &rmodel.CHANNELS.LCH_REV[2]  ,  0               , 9          ,  0                 ,           0      ,       3             },
{   92   ,"LCH 4 REV. "     ,     93 ,      91 ,    88 ,       0 ,  &rmodel.CHANNELS.LCH_REV[3]  ,  0               , 9          ,  0                 ,           0      ,       4             },
{   93   ,"LCH 5 REV. "     ,     94 ,      92 ,    88 ,       0 ,  &rmodel.CHANNELS.LCH_REV[4]  ,  0               , 9          ,  0                 ,           0      ,       5             },
{   94   ,"LCH 6 REV. "     ,     95 ,      93 ,    88 ,       0 ,  &rmodel.CHANNELS.LCH_REV[5]  ,  0               , 9          ,  0                 ,           0      ,       6             },
{   95   ,"LCH 7 REV. "     ,     96 ,      94 ,    88 ,       0 ,  &rmodel.CHANNELS.LCH_REV[6]  ,  0               , 9          ,  0                 ,           0      ,       7             },
{   96   ,"LCH 8 REV. "     ,     97 ,      95 ,    88 ,       0 ,  &rmodel.CHANNELS.LCH_REV[7]  ,  0               , 9          ,  0                 ,           0      ,       8             },
{   97   ,"LCH 9 REV. "     ,     98 ,      96 ,    88 ,       0 ,  &rmodel.CHANNELS.LCH_REV[8]  ,  0               , 9          ,  0                 ,           0      ,       9             },
{   98   ,"LCH A REV. "     ,     99 ,      97 ,    88 ,       0 ,  &rmodel.CHANNELS.LCH_REV[9]  ,  0               , 9          ,  0                 ,           0      ,       10            },
{   99   ,"LCH B REV. "     ,    100 ,      98 ,    88 ,       0 ,  &rmodel.CHANNELS.LCH_REV[10]  , 0               , 9          ,  0                 ,           0      ,       11            },
{  100   ,"LCH C REV. "     ,    101 ,      99 ,    88 ,       0 ,  &rmodel.CHANNELS.LCH_REV[11]  , 0               , 9          ,  0                 ,           0      ,       12            },
{  101   ,"LCH D REV. "     ,    102 ,     100 ,    88 ,       0 ,  &rmodel.CHANNELS.LCH_REV[12]  , 0               , 9          ,  0                 ,           0      ,       13            },
{  102   ,"LCH E REV. "     ,    103 ,     101 ,    88 ,       0 ,  &rmodel.CHANNELS.LCH_REV[13]  , 0               , 9          ,  0                 ,           0      ,       14            },
{  103   ,"LCH F REV. "     ,    104 ,     102 ,    88 ,       0 ,  &rmodel.CHANNELS.LCH_REV[14]  , 0               , 9          ,  0                 ,           0      ,       15            },
{  104   ,"LCH G REV. "     ,      0 ,     103 ,    88 ,       0 ,  &rmodel.CHANNELS.LCH_REV[15]  , 0               , 9          ,  0                 ,           0      ,       16            },

{   72   ,"LCH 1 DELAY"     ,      73 ,       0 ,    71 ,       0 ,  &rmodel.CHANNELS.LCHDELDN[0]  ,  &rmodel.CHANNELS.LCHDELUP[0]  , 8          ,  0 ,           0      ,       1                             },
{   73   ,"LCH 2 DELAY"     ,      74 ,      72 ,    71 ,       0 ,  &rmodel.CHANNELS.LCHDELDN[1]  ,  &rmodel.CHANNELS.LCHDELUP[1]  , 8          ,  0 ,           0      ,       2                             },
{   74   ,"LCH 3 DELAY"     ,      75 ,      73 ,    71 ,       0 ,  &rmodel.CHANNELS.LCHDELDN[2]  ,  &rmodel.CHANNELS.LCHDELUP[2]  , 8          ,  0 ,           0      ,       3                             },
{   75   ,"LCH 4 DELAY"     ,      76 ,      74 ,    71 ,       0 ,  &rmodel.CHANNELS.LCHDELDN[3]  ,  &rmodel.CHANNELS.LCHDELUP[3]  , 8          ,  0 ,           0      ,       4                             },
{   76   ,"LCH 5 DELAY"     ,      77 ,      75 ,    71 ,       0 ,  &rmodel.CHANNELS.LCHDELDN[4]  ,  &rmodel.CHANNELS.LCHDELUP[4]  , 8          ,  0 ,           0      ,       5                             },
{   77   ,"LCH 6 DELAY"     ,      78 ,      76 ,    71 ,       0 ,  &rmodel.CHANNELS.LCHDELDN[5]  ,  &rmodel.CHANNELS.LCHDELUP[5]  , 8          ,  0 ,           0      ,       6                             },
{   78   ,"LCH 7 DELAY"     ,      79 ,      77 ,    71 ,       0 ,  &rmodel.CHANNELS.LCHDELDN[6]  ,  &rmodel.CHANNELS.LCHDELUP[6]  , 8          ,  0 ,           0      ,       7                             },
{   79   ,"LCH 8 DELAY"     ,      80 ,      78 ,    71 ,       0 ,  &rmodel.CHANNELS.LCHDELDN[7]  ,  &rmodel.CHANNELS.LCHDELUP[7]  , 8          ,  0 ,           0      ,       8                             },
{   80   ,"LCH 9 DELAY"     ,      81 ,      79 ,    71 ,       0 ,  &rmodel.CHANNELS.LCHDELDN[8]  ,  &rmodel.CHANNELS.LCHDELUP[8]  , 8          ,  0 ,           0      ,       9                             },
{   81   ,"LCH A DELAY"     ,      82 ,      80 ,    71 ,       0 ,  &rmodel.CHANNELS.LCHDELDN[9]  ,  &rmodel.CHANNELS.LCHDELUP[9]  , 8          ,  0 ,           0      ,       10                            },
{   82   ,"LCH B DELAY"     ,      83 ,      81 ,    71 ,       0 ,  &rmodel.CHANNELS.LCHDELDN[10]  ,  &rmodel.CHANNELS.LCHDELUP[10]  , 8          ,  0 ,           0      ,     11                            },
{   83   ,"LCH C DELAY"     ,      84 ,      82 ,    71 ,       0 ,  &rmodel.CHANNELS.LCHDELDN[11]  ,  &rmodel.CHANNELS.LCHDELUP[11]  , 8          ,  0 ,           0      ,     12                            },
{   84   ,"LCH D DELAY"     ,      85 ,      83 ,    71 ,       0 ,  &rmodel.CHANNELS.LCHDELDN[12]  ,  &rmodel.CHANNELS.LCHDELUP[12]  , 8          ,  0 ,           0      ,     13                            },
{   85   ,"LCH E DELAY"     ,      86 ,      84 ,    71 ,       0 ,  &rmodel.CHANNELS.LCHDELDN[13]  ,  &rmodel.CHANNELS.LCHDELUP[13]  , 8          ,  0 ,           0      ,     14                            },
{   86   ,"LCH F DELAY"     ,      87 ,      85 ,    71 ,       0 ,  &rmodel.CHANNELS.LCHDELDN[14]  ,  &rmodel.CHANNELS.LCHDELUP[14]  , 8          ,  0 ,           0      ,     15                            },
{   87   ,"LCH G DELAY"     ,       0 ,      86 ,    71 ,       0 ,  &rmodel.CHANNELS.LCHDELDN[15]  ,  &rmodel.CHANNELS.LCHDELUP[15]  , 8          ,  0 ,           0      ,     16                            },

{   44   ,"CH TO PPM"      ,      19 ,       0 ,    70 ,       0 ,  &rmodel.CHANNELS.PPM_CH_COUNT  ,  0             , 6          ,  0                 ,           0      ,       0            },
{   19   ,"FILTERS"        ,       0 ,      44 ,    70 ,      36 ,  0                    ,  0                       , 0          ,  0                 ,           &rmodel.CHANNELS.PPM_CH_COUNT      ,       0             },

{   20   ,"CH 1"           ,      21 ,       0 ,    18 ,       0 , &rmodel.CHANNELS.CH_EPL[0] , &rmodel.CHANNELS.CH_EPR[0] , 4   ,  0                 ,           0      ,       1             },
{   21   ,"CH 2"           ,      22 ,      20 ,    18 ,       0 , &rmodel.CHANNELS.CH_EPL[1] , &rmodel.CHANNELS.CH_EPR[1] , 4   ,  0                 ,           0      ,       2             },
{   22   ,"CH 3"           ,      23 ,      21 ,    18 ,       0 , &rmodel.CHANNELS.CH_EPL[2] , &rmodel.CHANNELS.CH_EPR[2] , 4   ,  0                 ,           0      ,       3             },
{   23   ,"CH 4"           ,      24 ,      22 ,    18 ,       0 , &rmodel.CHANNELS.CH_EPL[3] , &rmodel.CHANNELS.CH_EPR[3] , 4   ,  0                 ,           0      ,       4             },
{   24   ,"CH 5"           ,      25 ,      23 ,    18 ,       0 , &rmodel.CHANNELS.CH_EPL[4] , &rmodel.CHANNELS.CH_EPR[4], 4    ,  0                 ,           0      ,       5             },
{   25   ,"CH 6"           ,      26 ,      24 ,    18 ,       0 , &rmodel.CHANNELS.CH_EPL[5] , &rmodel.CHANNELS.CH_EPR[5] , 4   ,  0                 ,           0      ,       6             },
{   26   ,"CH 7"           ,      27 ,      25 ,    18 ,       0 , &rmodel.CHANNELS.CH_EPL[6] , &rmodel.CHANNELS.CH_EPR[6] , 4   ,  0                 ,           0      ,       7             },
{   27   ,"CH 8"           ,      28 ,      26 ,    18 ,       0 , &rmodel.CHANNELS.CH_EPL[7] , &rmodel.CHANNELS.CH_EPR[7] , 4   ,  0                 ,           0      ,       8             },
{   28   ,"CH 9"           ,      29 ,      27 ,    18 ,       0 , &rmodel.CHANNELS.CH_EPL[8] , &rmodel.CHANNELS.CH_EPR[8] , 4   ,  0                 ,           0      ,       9             },
{   29   ,"CH A"           ,      30 ,      28 ,    18 ,       0 , &rmodel.CHANNELS.CH_EPL[9] , &rmodel.CHANNELS.CH_EPR[9] , 4   ,  0                 ,           0      ,       10            },
{   30   ,"CH B"           ,      31 ,      29 ,    18 ,       0 , &rmodel.CHANNELS.CH_EPL[10] , &rmodel.CHANNELS.CH_EPR[10] , 4 ,  0                 ,           0      ,       11            },
{   31   ,"CH C"           ,      32 ,      30 ,    18 ,       0 , &rmodel.CHANNELS.CH_EPL[11] , &rmodel.CHANNELS.CH_EPR[11] , 4 ,  0                 ,           0      ,       12            },
{   32   ,"CH D"           ,      33 ,      31 ,    18 ,       0 , &rmodel.CHANNELS.CH_EPL[12] , &rmodel.CHANNELS.CH_EPR[12] , 4 ,  0                 ,           0      ,       13            },
{   33   ,"CH E"           ,      34 ,      32 ,    18 ,       0 , &rmodel.CHANNELS.CH_EPL[13] , &rmodel.CHANNELS.CH_EPR[13] , 4 ,  0                 ,           0      ,       14            },
{   34   ,"CH F"           ,      35 ,      33 ,    18 ,       0 , &rmodel.CHANNELS.CH_EPL[14] , &rmodel.CHANNELS.CH_EPR[14] , 4 ,  0                 ,           0      ,       15            },
{   35   ,"CH G"           ,       0 ,      34 ,    18 ,       0 , &rmodel.CHANNELS.CH_EPL[15] , &rmodel.CHANNELS.CH_EPR[15] , 4 ,  0                 ,           0      ,       16            },

{   36   ,"CH 1"           ,      37 ,       0 ,    19 ,       0 , &rmodel.CHANNELS.FILTER[0].FILTER_TYPE  , &rmodel.CHANNELS.FILTER[0].VAL1  , 5 ,  menu_EDIT_CHANNEL_FILTERS ,           0      ,       1       },
{   37   ,"CH 2"           ,      38 ,      36 ,    19 ,       0 , &rmodel.CHANNELS.FILTER[1].FILTER_TYPE  , &rmodel.CHANNELS.FILTER[1].VAL1  , 5 ,  menu_EDIT_CHANNEL_FILTERS ,           0      ,       2      },
{   38   ,"CH 3"           ,      39 ,      37 ,    19 ,       0 , &rmodel.CHANNELS.FILTER[2].FILTER_TYPE  , &rmodel.CHANNELS.FILTER[2].VAL1  , 5 ,  menu_EDIT_CHANNEL_FILTERS ,           0      ,       3      },
{   39   ,"CH 4"           ,      40 ,      38 ,    19 ,       0 , &rmodel.CHANNELS.FILTER[3].FILTER_TYPE  , &rmodel.CHANNELS.FILTER[3].VAL1  , 5 ,  menu_EDIT_CHANNEL_FILTERS ,           0      ,       4       },
{   40   ,"CH 5"           ,      41 ,      39 ,    19 ,       0 , &rmodel.CHANNELS.FILTER[4].FILTER_TYPE  , &rmodel.CHANNELS.FILTER[4].VAL1  , 5 ,  menu_EDIT_CHANNEL_FILTERS ,           0      ,       5       },
{   41   ,"CH 6"           ,      42 ,      40 ,    19 ,       0 , &rmodel.CHANNELS.FILTER[5].FILTER_TYPE  , &rmodel.CHANNELS.FILTER[5].VAL1  , 5 ,  menu_EDIT_CHANNEL_FILTERS ,           0      ,       6      },
{   42   ,"CH 7"           ,      43 ,      41 ,    19 ,       0 , &rmodel.CHANNELS.FILTER[6].FILTER_TYPE  , &rmodel.CHANNELS.FILTER[6].VAL1  , 5 ,  menu_EDIT_CHANNEL_FILTERS ,           0      ,       7      },
{   43   ,"CH 8"           ,       0 ,      42 ,    19 ,       0 , &rmodel.CHANNELS.FILTER[7].FILTER_TYPE  , &rmodel.CHANNELS.FILTER[7].VAL1  , 5 ,  menu_EDIT_CHANNEL_FILTERS ,           0      ,       8      },

{   45   ,"STICK"          ,      46 ,       0 ,    15 ,      49 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0             },
{   46   ,"VARIO"          ,      47 ,      45 ,    15 ,      53 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0             },
{   47   ,"SWITCH"         ,      48 ,      46 ,    15 ,      57 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0             },
{   48   ,"BUTTON"         ,       0 ,      47 ,    15 ,      62 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0             },

{   49   ,"AILERONS"       ,      50 ,       0 ,    45 ,       0 , &rmodel.UCH[0].UCH_LEFT , &rmodel.UCH[0].UCH_RIGHT    , 7         ,  0                ,           0      ,       0              },
{   50   ,"ELEVATOR"       ,      51 ,      49 ,    45 ,       0 , &rmodel.UCH[1].UCH_LEFT , &rmodel.UCH[1].UCH_RIGHT    , 7          ,  0               ,           0      ,       0               },
{   51   ,"THROTTLE"        ,      52 ,      50 ,   45 ,       0 , &rmodel.UCH[2].UCH_LEFT , &rmodel.UCH[2].UCH_RIGHT    , 7          ,  0               ,           0      ,       0               },
{   52   ,"RUDDER"         ,       0 ,      51 ,    45 ,       0 , &rmodel.UCH[3].UCH_LEFT , &rmodel.UCH[3].UCH_RIGHT    , 7          ,  0               ,           0      ,       0               },

{   53   ,"HOV PIT"        ,      54 ,       0 ,    46 ,       0 , &rmodel.UCH[4].UCH_LEFT , &rmodel.UCH[4].UCH_RIGHT    , 7          ,  0               ,           0      ,       0               },
{   54   ,"HOV THR"        ,      55 ,      53 ,    46 ,       0 , &rmodel.UCH[5].UCH_LEFT , &rmodel.UCH[5].UCH_RIGHT    , 7          ,  0               ,           0      ,       0               },
{   55   ,"PIT TRM"        ,       0 ,      54 ,    46 ,       0 , &rmodel.UCH[6].UCH_LEFT , &rmodel.UCH[6].UCH_RIGHT    , 7          ,  0               ,           0      ,       0               },

{   57   ,"GEAR"           ,      58 ,       0 ,    47 ,       0 , &rmodel.UCH[8].UCH_LEFT , &rmodel.UCH[8].UCH_RIGHT    , 7          ,  0               ,           0      ,       0               },
{   58   ,"THR.CUT"        ,      59 ,      57 ,    47 ,       0 , &rmodel.UCH[10].UCH_LEFT , &rmodel.UCH[10].UCH_RIGHT  , 7          ,  0             ,           0      ,       0                 },
{   59   ,"AILE DR"        ,      60 ,      58 ,    47 ,       0 , &rmodel.UCH[11].UCH_LEFT , &rmodel.UCH[11].UCH_RIGHT  , 7          ,  0             ,           0      ,       0                 },
{   60   ,"ELEV DR"        ,      61 ,      59 ,    47 ,       0 , &rmodel.UCH[12].UCH_LEFT , &rmodel.UCH[12].UCH_RIGHT  , 7          ,  0             ,           0      ,       0                 },
{   61   ,"RUDD DR"        ,       0 ,      60 ,    47 ,       0 , &rmodel.UCH[13].UCH_LEFT , &rmodel.UCH[13].UCH_RIGHT  , 7          ,  0             ,           0      ,       0                 },

{   62   ,"TRAINER"        ,       0 ,       0 ,    48 ,       0 , &rmodel.UCH[9].UCH_LEFT , &rmodel.UCH[9].UCH_RIGHT    , 7          ,  0               ,           0      ,       0               },

{  105   ,"FMODE COUNT"    ,     153 ,       0 ,    16 ,       0 ,  &rmodel.FMODE_COUNT  ,  0                            , 10          ,  0         ,           0      ,       0              },
{  153   ,"FMODE COPY"     ,     106 ,     105 ,    16 ,     154 ,  0                           ,  0                     , 0           ,  0         ,           0      ,       0                     },
{  106   ,"FMODE 1"        ,     107 ,     153 ,    16 ,     109 ,  &rmodel.FMODE[0].FMODE_NAME ,  0                     , 11          ,  0         ,           0      ,       1                     },
{  107   ,"FMODE 2"        ,     108 ,     106 ,    16 ,     114 ,  &rmodel.FMODE[1].FMODE_NAME ,  0                     , 11          ,  0         ,           0      ,       2                     },
{  108   ,"FMODE 3"        ,       0 ,     107 ,    16 ,     119 ,  &rmodel.FMODE[2].FMODE_NAME ,  0                     , 11          ,  0         ,           0      ,       3                     },

{  154   ,"FROM"           ,     155 ,       0 ,   153 ,       0 ,  &fmode_source               ,  0                     , 10          ,  0         ,           0      ,       0                      },
{  155   ,"TO"             ,     156 ,     154 ,   153 ,       0 ,  &fmode_to                   ,  0                     , 10          ,  0         ,           0      ,       0                      },
{  156   ,"COPY"           ,       0 ,     155 ,   153 ,       0 ,  0                           ,  0                     , 29          ,  0         ,           0      ,       0                      },

{  109   ,"FMODE NAME"     ,     110 ,       0 ,   106 ,       0 ,  &rmodel.FMODE[0].FMODE_NAME ,  0                     , 12          ,  0         ,           0      ,       0                     },
{  110   ,"UCH TRIM."      ,     111 ,     109 ,   106 ,     124 ,  0                           ,  0                     , 0           ,  0         ,           0      ,       0                     },
{  111   ,"LCH MIDDLE"     ,     112 ,     110 ,   106 ,     175 ,  0                           ,  0                     , 0           ,  0         ,           &rmodel.CHANNELS.LCH_COUNT      ,       0                     },
{  112   ,"LCH CURVE"      ,     113 ,     111 ,   106 ,       0 ,  0                           ,  0                     , 0           ,  menu_FMODE_CURVES,           0      ,       0              },
{  113   ,"MIXERS"         ,       0 ,     112 ,   106 ,       0 ,  0                           ,  0                     , 0           ,  menu_FMODE_MIXERS,           0      ,       0       },

{  175   ,"LCH1 MIDDLE"     ,     176 ,       0 ,   111 ,       0 ,  &rmodel.FMODE[0].LCH_MIDLE[0] ,  0                  , 14          ,  0          ,           0      ,       1                    },
{  176   ,"LCH2 MIDDLE"     ,     177 ,     175 ,   111 ,       0 ,  &rmodel.FMODE[0].LCH_MIDLE[1] ,  0                  , 14          ,  0          ,           0      ,       2                    },
{  177   ,"LCH3 MIDDLE"     ,     178 ,     176 ,   111 ,       0 ,  &rmodel.FMODE[0].LCH_MIDLE[2] ,  0                  , 14          ,  0          ,           0      ,       3                    },
{  178   ,"LCH4 MIDDLE"     ,     179 ,     177 ,   111 ,       0 ,  &rmodel.FMODE[0].LCH_MIDLE[3] ,  0                  , 14          ,  0          ,           0      ,       4                    },
{  179   ,"LCH5 MIDDLE"     ,     180 ,     178 ,   111 ,       0 ,  &rmodel.FMODE[0].LCH_MIDLE[4] ,  0                  , 14          ,  0          ,           0      ,       5                    },
{  180   ,"LCH6 MIDDLE"     ,     181 ,     179 ,   111 ,       0 ,  &rmodel.FMODE[0].LCH_MIDLE[5] ,  0                  , 14          ,  0          ,           0      ,       6                    },
{  181   ,"LCH7 MIDDLE"     ,     182 ,     180 ,   111 ,       0 ,  &rmodel.FMODE[0].LCH_MIDLE[6] ,  0                  , 14          ,  0          ,           0      ,       7                    },
{  182   ,"LCH8 MIDDLE"     ,     183 ,     181 ,   111 ,       0 ,  &rmodel.FMODE[0].LCH_MIDLE[7] ,  0                  , 14          ,  0          ,           0      ,       8                    },
{  183   ,"LCH9 MIDDLE"     ,     184 ,     182 ,   111 ,       0 ,  &rmodel.FMODE[0].LCH_MIDLE[8] ,  0                  , 14          ,  0          ,           0      ,       9                    },
{  184   ,"LCHA MIDDLE"     ,     185 ,     183 ,   111 ,       0 ,  &rmodel.FMODE[0].LCH_MIDLE[9] ,  0                  , 14          ,  0          ,           0      ,       10                   },
{  185   ,"LCHB MIDDLE"     ,     186 ,     184 ,   111 ,       0 ,  &rmodel.FMODE[0].LCH_MIDLE[10] ,  0                 , 14          ,  0         ,           0      ,       11                    },
{  186   ,"LCHC MIDDLE"     ,     187 ,     185 ,   111 ,       0 ,  &rmodel.FMODE[0].LCH_MIDLE[11] ,  0                 , 14          ,  0         ,           0      ,       12                    },
{  187   ,"LCHD MIDDLE"     ,     188 ,     186 ,   111 ,       0 ,  &rmodel.FMODE[0].LCH_MIDLE[12] ,  0                 , 14          ,  0         ,           0      ,       13                    },
{  188   ,"LCHE MIDDLE"     ,     189 ,     187 ,   111 ,       0 ,  &rmodel.FMODE[0].LCH_MIDLE[13] ,  0                 , 14          ,  0         ,           0      ,       14                    },
{  189   ,"LCHF MIDDLE"     ,     190 ,     188 ,   111 ,       0 ,  &rmodel.FMODE[0].LCH_MIDLE[14] ,  0                 , 14          ,  0         ,           0      ,       15                    },
{  190   ,"LCHG MIDDLE"     ,       0 ,     189 ,   111 ,       0 ,  &rmodel.FMODE[0].LCH_MIDLE[15] ,  0                 , 14          ,  0         ,           0      ,       16                    },  

{  124   ,"TRIM. STEP"     ,     125 ,       0 ,   110 ,       0 ,  &rmodel.FMODE[0].TRIMSTEP       ,  0                 , 10          ,  0         ,           0      ,       0                     },
{  125   ,"AILERONS"       ,     126 ,     124 ,   110 ,       0 ,  &rmodel.FMODE[0].UCH_TRIMMER[0] ,  0                 , 13          ,  0         ,           0      ,       1                     },
{  126   ,"ELEVATOR"       ,     127 ,     125 ,   110 ,       0 ,  &rmodel.FMODE[0].UCH_TRIMMER[1] ,  0                 , 13          ,  0         ,           0      ,       1                     },
{  127   ,"THROTTLE"       ,     128 ,     126 ,   110 ,       0 ,  &rmodel.FMODE[0].UCH_TRIMMER[2] , 0                 , 13          ,  0         ,           0      ,       1                     },
{  128   ,"RUDDER"         ,     129 ,     127 ,   110 ,       0 ,  &rmodel.FMODE[0].UCH_TRIMMER[3] ,  0                 , 13          ,  0         ,           0      ,       1                     },
{  129   ,"HOV PIT"        ,     130 ,     128 ,   110 ,       0 ,  &rmodel.FMODE[0].UCH_TRIMMER[4] ,  0                 , 13          ,  0         ,           0      ,       1                     },
{  130   ,"HOV THR"        ,     131 ,     129 ,   110 ,       0 ,  &rmodel.FMODE[0].UCH_TRIMMER[5] ,  0                 , 13          ,  0         ,           0      ,       1                     },
{  131   ,"PIT TRIM"       ,       0 ,     130 ,   110 ,       0 ,  &rmodel.FMODE[0].UCH_TRIMMER[6] ,  0                 , 13          ,  0         ,           0      ,       1                     },

{  132   ,"FLY TIMER"      ,     133 ,       0 ,     3 ,       0 ,  &rmodel.MODEL_FLYTIMER          , &rmodel.MODEL_FLYTIMER , 23        ,  0         ,           0      ,       1                     },
{  133   ,"LIVE TIMER"     ,     134 ,     132 ,     3 ,       0 ,  &rmodel.MODEL_LIVETIMER         , &rmodel.MODEL_LIVETIMER , 23       ,  0         ,           0      ,       1                     },
{  134   ,"SET TIMER"      ,     135 ,     133 ,     3 ,       0 ,  0                                ,  0                   , 24         ,  0         ,           0      ,       1                     },
{  135   ,"UPDATE LIFE"    ,     172 ,     134 ,     3 ,       0 ,  0                                ,  0                   , 25         ,  0         ,           0      ,       1                     },
{  172   ,"EVENT START"     ,    166 ,     135,      3 ,       0 ,  0                                ,  0                   , 20         ,  0         ,           0      ,       0                     },
{  166   ,"EVENT STOP"      ,      0 ,     172,      3 ,       0 ,  0                                ,  0                   , 27         ,  0         ,           0      ,       0                     },

{  114   ,"FMODE NAME"     ,     115 ,       0 ,   107 ,       0 ,  &rmodel.FMODE[1].FMODE_NAME ,  0                     , 12          ,  0         ,           0      ,       0                     },
{  115   ,"UCH TRIM."      ,     116 ,     114 ,   107 ,     141 ,  0                           ,  0                     , 0           ,  0         ,           0      ,       0                     },
{  116   ,"LCH MIDDLE"     ,     117 ,     115 ,   107 ,     191 ,  0                           ,  0                     , 0           ,  0         ,           &rmodel.CHANNELS.LCH_COUNT      ,       0                     },
{  117   ,"LCH CURVE"      ,     118 ,     116 ,   107 ,       0 ,  0                           ,  0                     , 0           ,  menu_FMODE_CURVES,           0      ,       0               },
{  118   ,"MIXERS"         ,       0 ,     117 ,   107 ,       0 ,  0                           ,  0                     , 0           ,  menu_FMODE_MIXERS,           0      ,       0       },

{  191   ,"LCH1 MIDDLE"     ,     192 ,       0 ,   116 ,       0 ,  &rmodel.FMODE[1].LCH_MIDLE[0] ,  0                  , 14          ,  0          ,           0      ,       1                    },
{  192   ,"LCH2 MIDDLE"     ,     193 ,     191 ,   116 ,       0 ,  &rmodel.FMODE[1].LCH_MIDLE[1] ,  0                  , 14          ,  0          ,           0      ,       2                    },
{  193   ,"LCH3 MIDDLE"     ,     194 ,     192 ,   116 ,       0 ,  &rmodel.FMODE[1].LCH_MIDLE[2] ,  0                  , 14          ,  0          ,           0      ,       3                    },
{  194   ,"LCH4 MIDDLE"     ,     195 ,     193 ,   116 ,       0 ,  &rmodel.FMODE[1].LCH_MIDLE[3] ,  0                  , 14          ,  0          ,           0      ,       4                    },
{  195   ,"LCH5 MIDDLE"     ,     196 ,     194 ,   116 ,       0 ,  &rmodel.FMODE[1].LCH_MIDLE[4] ,  0                  , 14          ,  0          ,           0      ,       5                    },
{  196   ,"LCH6 MIDDLE"     ,     197 ,     195 ,   116 ,       0 ,  &rmodel.FMODE[1].LCH_MIDLE[5] ,  0                  , 14          ,  0          ,           0      ,       6                    },
{  197   ,"LCH7 MIDDLE"     ,     198 ,     196 ,   116 ,       0 ,  &rmodel.FMODE[1].LCH_MIDLE[6] ,  0                  , 14          ,  0          ,           0      ,       7                    },
{  198   ,"LCH8 MIDDLE"     ,     199 ,     197 ,   116 ,       0 ,  &rmodel.FMODE[1].LCH_MIDLE[7] ,  0                  , 14          ,  0          ,           0      ,       8                    },
{  199   ,"LCH9 MIDDLE"     ,     200 ,     198 ,   116 ,       0 ,  &rmodel.FMODE[1].LCH_MIDLE[8] ,  0                  , 14          ,  0          ,           0      ,       9                    },
{  200   ,"LCHA MIDDLE"     ,     201 ,     199 ,   116 ,       0 ,  &rmodel.FMODE[1].LCH_MIDLE[9] ,  0                  , 14          ,  0          ,           0      ,       10                   },
{  201   ,"LCHB MIDDLE"     ,     202 ,     200 ,   116 ,       0 ,  &rmodel.FMODE[1].LCH_MIDLE[10] ,  0                 , 14          ,  0         ,           0      ,       11                    },
{  202   ,"LCHC MIDDLE"     ,     203 ,     201 ,   116 ,       0 ,  &rmodel.FMODE[1].LCH_MIDLE[11] ,  0                 , 14          ,  0         ,           0      ,       12                    },
{  203   ,"LCHD MIDDLE"     ,     204 ,     202 ,   116 ,       0 ,  &rmodel.FMODE[1].LCH_MIDLE[12] ,  0                 , 14          ,  0         ,           0      ,       13                    },
{  204   ,"LCHE MIDDLE"     ,     205 ,     203 ,   116 ,       0 ,  &rmodel.FMODE[1].LCH_MIDLE[13] ,  0                 , 14          ,  0         ,           0      ,       14                    },
{  205   ,"LCHF MIDDLE"     ,     206 ,     204 ,   116 ,       0 ,  &rmodel.FMODE[1].LCH_MIDLE[14] ,  0                 , 14          ,  0         ,           0      ,       15                    },
{  206   ,"LCHG MIDDLE"     ,       0 ,     205 ,   116 ,       0 ,  &rmodel.FMODE[1].LCH_MIDLE[15] ,  0                 , 14          ,  0         ,           0      ,       16                    },

{  141   ,"TRIM. STEP"      ,     142 ,       0 ,   115 ,       0 ,  &rmodel.FMODE[1].TRIMSTEP       ,  0                , 10          ,  0         ,           0      ,       0                         },
{  142   ,"AILERONS"        ,     143 ,     141 ,   115 ,       0 ,  &rmodel.FMODE[1].UCH_TRIMMER[0] ,  0                , 13          ,  0         ,           0      ,       1                     },
{  143   ,"ELEVATOR"        ,     144 ,     142 ,   115 ,       0 ,  &rmodel.FMODE[1].UCH_TRIMMER[1] ,  0                , 13          ,  0         ,           0      ,       1                     },
{  144   ,"THROTTLE"        ,     145 ,     143 ,   115 ,       0 ,  &rmodel.FMODE[1].UCH_TRIMMER[2] ,  0               , 13          ,  0         ,           0      ,       1                     },
{  145   ,"RUDDER"          ,     146 ,     144 ,   115 ,       0 ,  &rmodel.FMODE[1].UCH_TRIMMER[3] ,  0                , 13          ,  0         ,           0      ,       1                     },
{  146   ,"HOV PIT"         ,     147 ,     145 ,   115 ,       0 ,  &rmodel.FMODE[1].UCH_TRIMMER[4] ,  0                , 13          ,  0         ,           0      ,       1                     },
{  147   ,"HOV THR"         ,     148 ,     146 ,   115 ,       0 ,  &rmodel.FMODE[1].UCH_TRIMMER[5] ,  0                , 13          ,  0         ,           0      ,       1                     },
{  148   ,"PIT TRIM"        ,       0 ,     147 ,   115 ,       0 ,  &rmodel.FMODE[1].UCH_TRIMMER[6] ,  0                , 13          ,  0         ,           0      ,       1                     },

{  119   ,"FMODE NAME"     ,     120 ,       0 ,   108 ,       0 ,  &rmodel.FMODE[2].FMODE_NAME ,  0                     , 12          ,  0         ,           0      ,       0                     },
{  120   ,"UCH TRIM."      ,     121 ,     119 ,   108 ,     158 ,  0                           ,  0                     , 0           ,  0         ,           0      ,       0                     },
{  121   ,"LCH MIDDLE"     ,     122 ,     120 ,   108 ,     207 ,  0                           ,  0                     , 0           ,  0         ,           &rmodel.CHANNELS.LCH_COUNT      ,       0                     },
{  122   ,"LCH CURVE"      ,     123 ,     121 ,   108 ,       0 ,  0                           ,  0                     , 0           ,  menu_FMODE_CURVES,           0      ,       0              },
{  123   ,"MIXERS"         ,       0 ,     122 ,   108 ,       0 ,  0                           ,  0                     , 0           ,  menu_FMODE_MIXERS,           0      ,       0       },

{  207   ,"LCH1 MIDDLE"     ,     208 ,       0 ,   121 ,       0 ,  &rmodel.FMODE[2].LCH_MIDLE[0] ,  0                  , 14          ,  0          ,           0      ,       1                    },
{  208   ,"LCH2 MIDDLE"     ,     209 ,     207 ,   121 ,       0 ,  &rmodel.FMODE[2].LCH_MIDLE[1] ,  0                  , 14          ,  0          ,           0      ,       2                    },
{  209   ,"LCH3 MIDDLE"     ,     210 ,     208 ,   121 ,       0 ,  &rmodel.FMODE[2].LCH_MIDLE[2] ,  0                  , 14          ,  0          ,           0      ,       3                    },
{  210   ,"LCH4 MIDDLE"     ,     211 ,     209 ,   121 ,       0 ,  &rmodel.FMODE[2].LCH_MIDLE[3] ,  0                  , 14          ,  0          ,           0      ,       4                    },
{  211   ,"LCH5 MIDDLE"     ,     212 ,     210 ,   121 ,       0 ,  &rmodel.FMODE[2].LCH_MIDLE[4] ,  0                  , 14          ,  0          ,           0      ,       5                    },
{  212   ,"LCH6 MIDDLE"     ,     213 ,     211 ,   121 ,       0 ,  &rmodel.FMODE[2].LCH_MIDLE[5] ,  0                  , 14          ,  0          ,           0      ,       6                    },
{  213   ,"LCH7 MIDDLE"     ,     214 ,     212 ,   121 ,       0 ,  &rmodel.FMODE[2].LCH_MIDLE[6] ,  0                  , 14          ,  0          ,           0      ,       7                    },
{  214   ,"LCH8 MIDDLE"     ,     215 ,     213 ,   121 ,       0 ,  &rmodel.FMODE[2].LCH_MIDLE[7] ,  0                  , 14          ,  0          ,           0      ,       8                    },
{  215   ,"LCH9 MIDDLE"     ,     216 ,     214 ,   121 ,       0 ,  &rmodel.FMODE[2].LCH_MIDLE[8] ,  0                  , 14          ,  0          ,           0      ,       9                    },
{  216   ,"LCHA MIDDLE"     ,     217 ,     215 ,   121 ,       0 ,  &rmodel.FMODE[2].LCH_MIDLE[9] ,  0                  , 14          ,  0          ,           0      ,       10                   },
{  217   ,"LCHB MIDDLE"     ,     218 ,     216 ,   121 ,       0 ,  &rmodel.FMODE[2].LCH_MIDLE[10] ,  0                 , 14          ,  0         ,           0      ,       11                    },
{  218   ,"LCHC MIDDLE"     ,     219 ,     217 ,   121 ,       0 ,  &rmodel.FMODE[2].LCH_MIDLE[11] ,  0                 , 14          ,  0         ,           0      ,       12                    },
{  219   ,"LCHD MIDDLE"     ,     220 ,     218 ,   121 ,       0 ,  &rmodel.FMODE[2].LCH_MIDLE[12] ,  0                 , 14          ,  0         ,           0      ,       13                    },
{  220   ,"LCHE MIDDLE"     ,     221 ,     219 ,   121 ,       0 ,  &rmodel.FMODE[2].LCH_MIDLE[13] ,  0                 , 14          ,  0         ,           0      ,       14                    },
{  221   ,"LCHF MIDDLE"     ,     222 ,     220 ,   121 ,       0 ,  &rmodel.FMODE[2].LCH_MIDLE[14] ,  0                 , 14          ,  0         ,           0      ,       15                    },
{  222   ,"LCHG MIDDLE"     ,       0 ,     221 ,   121 ,       0 ,  &rmodel.FMODE[2].LCH_MIDLE[15] ,  0                 , 14          ,  0         ,           0      ,       16                    },                                                                                                                                                                                

{  158   ,"TRIM. STEP"     ,     159 ,       0 ,   120 ,       0 ,  &rmodel.FMODE[2].TRIMSTEP       ,  0                 , 10          ,  0         ,           0      ,       0                     },
{  159   ,"AILERONS"       ,     160 ,     158 ,   120 ,       0 ,  &rmodel.FMODE[2].UCH_TRIMMER[0] ,  0                 , 13          ,  0         ,           0      ,       1                     },
{  160   ,"ELEVATOR"       ,     161 ,     159 ,   120 ,       0 ,  &rmodel.FMODE[2].UCH_TRIMMER[1] ,  0                 , 13          ,  0         ,           0      ,       1                     },
{  161   ,"THROTTLE"       ,     162 ,     160 ,   120 ,       0 ,  &rmodel.FMODE[2].UCH_TRIMMER[2] ,  0                , 13          ,  0         ,           0      ,       1                     },
{  162   ,"RUDDER"         ,     163 ,     161 ,   120 ,       0 ,  &rmodel.FMODE[2].UCH_TRIMMER[3] ,  0                 , 13          ,  0         ,           0      ,       1                     },
{  163   ,"HOV PIT"        ,     164 ,     162 ,   120 ,       0 ,  &rmodel.FMODE[2].UCH_TRIMMER[4] ,  0                 , 13          ,  0         ,           0      ,       1                     },
{  164   ,"HOV THR"        ,     165 ,     163 ,   120 ,       0 ,  &rmodel.FMODE[2].UCH_TRIMMER[5] ,  0                 , 13          ,  0         ,           0      ,       1                     },
{  165   ,"PIT TRIM"       ,       0 ,     164 ,   120 ,       0 ,  &rmodel.FMODE[2].UCH_TRIMMER[6] ,  0                 , 13          ,  0         ,           0      ,       1                     },

{  224   ,"CLUSTER"        ,     225 ,      0 ,    223 ,       0 ,  0                                ,  0                , 15         ,  0                 ,           0      ,       0       },
{  225   ,"FORMAT VD"      ,     232 ,    224 ,    223 ,       0 ,  0                                ,  0                , 0          ,  menu_formatVDisk       ,           0      ,       0       },
{  232   ,"VDISK INFO"     ,       0 ,    225 ,    223 ,       0 ,  0                                ,  0                , 0          ,  menu_VDISK_INFO        ,           0      ,       0       },

{  226   ,"SOUND ON"       ,       0 ,      0 ,     66 ,       0 ,  &SOUND_ON                        ,  0                , 16         ,  0                      ,           0      ,       0       },

{  228   ,"KEY PRESS"      ,     229 ,      0 ,    227 ,       0 ,  &key_press_time                  ,  0                , 17         ,  0                      ,           0      ,       0       },
{  229   ,"KEY REPRESS"    ,     169 ,    228 ,    227 ,       0 ,  &key_repress_time                ,  0                , 17         ,  0                      ,           0      ,       0       },
{  169   ,"TRIM. PRESS"    ,     168 ,    229 ,    227 ,       0 ,  &trim_press_time                 ,  0                , 26         ,  0                      ,           0      ,       0       },
{  168   ,"0-TRIM BEEP"    ,       0 ,    169 ,    227 ,       0 ,  0                                ,  0                , 28         ,  0                      ,           0      ,       0       },

{  174   ,"BATTERY"         ,    173 ,      0 ,     63 ,     230 ,  0                                ,  0                , 0          ,  0                      ,           0      ,       0       },
{  173   ,"FLY TIMER"       ,      0 ,    174 ,     63 ,     171 ,  0                                ,  0                , 0          ,  0                      ,           0      ,       0       },

{  230   ,"BATT VOLT."      ,    167 ,      0 ,    174 ,       0 ,  &batt                            ,  0                , 18         ,  0                      ,           0      ,       0       },
{  167   ,"BATT CALIBR"     ,    231 ,    230 ,    174 ,       0 ,  0                                ,  0                , 32         ,  0                 ,           0      ,       0             },
{  231   ,"BATT ALARM"      ,      0 ,    167 ,    174 ,       0 ,  &battMin                         ,  0                , 19         ,  0                      ,           0      ,       0       },

{  171   ,"1 MIN. BEEP"     ,    170 ,      0 ,    173 ,       0 ,  0                                ,  0                , 21         ,  0                      ,           0      ,       0       },
{  170   ,"LAST BEEP"       ,      0 ,    171 ,    173 ,       0 ,  0                                ,  0                , 22         ,  0                      ,           0      ,       0       },

};

unsigned char numItemByID(unsigned char iditem) { 

unsigned char i;

i=0;
while (menu[i].numitem!=iditem) i++; 
return i;
} 

unsigned char getIDbefore(unsigned char colitem) { 
unsigned char i,j;                                 

j=numitem_cur;  
for (i=colitem; i!=0; i--) { 
if (menu[ numItemByID(j) ].previtem!=0) { 
j=menu[ numItemByID(j) ].previtem;
} else { break; } 
}
return j; 
} 

void decreaseValuePar(unsigned char partype, void *pvar) {
unsigned char c;
unsigned char *pvarc; 

unsigned int  i;
unsigned int  *pvari;

signed   char *pvarsc;
signed char sc;

switch (partype) {

case 1: { 
pvarc=pvar; 
c=*pvarc;   
if (c!=0) { 
(*pvarc)--; 
ModelChange=1;
}
break;
}

case 3: { 
pvarc=pvar; 
c=*pvarc;   
if (c>2) { 
(*pvarc)--; 
ModelChange=1;
}
break;
}

case 4: { 
pvari=pvar; 
i=*pvari;   
if (i>700) {
i=i-1-keyhold*9;
ModelChange=1;
}
if (i<700) i=700;
*pvari=i;
CalcCurveORD();
break; 
}

case 6: { 
pvarc=pvar; 
c=*pvarc;   
if (c>4) {
(*pvarc)--; 
ModelChange=1;
}
break;
}

case 7: { 
pvarsc=pvar; 
sc=*pvarsc;   
if (sc>-125) { 
sc=sc-1-keyhold*2; 
ModelChange=1;
}
*pvarsc=sc; 
break;
}

case 8: { 
pvarc=pvar; 
c=*pvarc;   
if (c>0)   c=c-1-keyhold*2;  
else c=255; 
*pvarc=c;
ModelChange=1; 
break;
}

case 9: { 
pvarc=pvar; 
c=*pvarc;   
if (c==0) (*pvarc)=1;  else  (*pvarc)=0; 
ModelChange=1;
break;
}

case 10: { 
pvarc=pvar; 
c=*pvarc;   
if (c>1) { 
(*pvarc)--; 
ModelChange=1;
}
break;
}

case 12: { 
pvarc=pvar; 
c=*pvarc;   
if (c>0) { 
(*pvarc)--; 
ModelChange=1;
}
break;
}

case 13: { 
pvarsc=pvar; 
sc=*pvarsc;   
if (sc>-125) { 
sc=sc-1-2*keyhold ; 
ModelChange=1;
}
if (sc<-125) sc=-125;
*pvarsc=sc;
break;
}

case 14: { 
pvari=pvar; 
i=*pvari;   
if (i>700) { 
i=i-1-keyhold*9;
ModelChange=1;
}
if (i<700) i=700;
*pvari=i;
CalcCurveORD();
break; 
}

case 15: { 
if (E_ClusterSize>16) { 
E_ClusterSize=E_ClusterSize-16;
} 
break;
}

case 16: { 
pvarc=pvar; 
c=*pvarc;   
if (c==1) (*pvarc)=0;  else  (*pvarc)=1; 
E_SOUND_ON=SOUND_ON;
break;
}

case 17: { 
pvarc=pvar; 
c=*pvarc;   
if (c>3) (*pvarc)--; 
E_key_press_time=key_press_time;
E_key_repress_time=key_repress_time;
resetKeyReader();
break;
}

case 19: { 
pvari=pvar; 
i=*pvari;   
if (i>420) i=i-7;
if (i<420) i=420;
*pvari=i;
E_battMin=i; 
break;
}

case 20: { 
c=E_eventStart;   
if (c>0) c--;  else  c=8; 
E_eventStart=c;
break;
}

case 21: { 
c=E_beep1min;   
if (c==1) c=0;  else  c=1; 
E_beep1min=c;
break;
}

case 22: { 
c=E_beep2sec;   
if (c==1) c=0;  else  c=1; 
E_beep2sec=c;
break;
}

case 23: { 
pvari=pvar; 
i=*pvari;   
if (posxmenu==1) { 
if ((i/60)>0) {
(*pvari)=((i/60)-1)*60 + i%60;
ModelChange=1;
}
} 
else { 
if ((i%60)>0) { 
(*pvari)=i-1;
ModelChange=1;
}
}
break; 
}

case 24: { 
flyCurrTimer=rmodel.MODEL_FLYTIMER;
break;
}

case 25: { 
if (flyCurrTimer<rmodel.MODEL_FLYTIMER) {

rmodel.MODEL_LIVETIMER=rmodel.MODEL_LIVETIMER+(rmodel.MODEL_FLYTIMER-flyCurrTimer)/60;
flyCurrTimer=rmodel.MODEL_FLYTIMER;
ModelChange=1;
}
break;
}

case 26: { 
pvarc=pvar; 
c=*pvarc;   
if (c>5) (*pvarc)--; 
E_trim_press_time=trim_press_time;
break;
}

case 27: { 
c=E_eventStop;   
if (c>0) c--;  else  c=8; 
E_eventStop=c;
break;
}

case 28: { 
c=E_nulTrimBeep;   
if (c==1) c=0;  else  c=1; 
E_nulTrimBeep=c;
break;
}

case 29: { 
rmodel.FMODE[fmode_to-1].FMODE_NAME=rmodel.FMODE[fmode_source-1].FMODE_NAME;
rmodel.FMODE[fmode_to-1].TRIMSTEP=rmodel.FMODE[fmode_source-1].TRIMSTEP;

for (c=0;c<7;c++) 
rmodel.FMODE[fmode_to-1].UCH_TRIMMER[c]=rmodel.FMODE[fmode_source-1].UCH_TRIMMER[c];

for (c=0;c<16;c++) 
rmodel.FMODE[fmode_to-1].LCH_MIDLE[c]=rmodel.FMODE[fmode_source-1].LCH_MIDLE[c];

for (c=0;c<16;c++) 
rmodel.FMODE[fmode_to-1].LCH_CURVE[c]=rmodel.FMODE[fmode_source-1].LCH_CURVE[c];       

for (c=0;c<40;c++)
rmodel.FMODE[fmode_to-1].MIXER[c]=rmodel.FMODE[fmode_source-1].MIXER[c];                   

break;
}

case 30: { 
if (E_var3==0) E_var3=1;  else  E_var3=0; 
break;
}

case 31: { 
if (E_var4>20) {
E_var4--; 
LCD_setContrast(E_var4);
}
break;
}

case 32: { 
if (E_var11>0) {
E_var11--; 
}
break;
}

case 33: { 
if (E_var12<4) E_var12++;
break;
}

}
}

void increaseValuePar(unsigned char partype, void *pvar) {
unsigned char c;
unsigned char *pvarc;

unsigned int  i;
unsigned int  *pvari;

signed   char *pvarsc;
signed char sc;

switch (partype) {

case 1: { 
pvarc=pvar; 
c=*pvarc;   
if (c<2 ) { 
(*pvarc)++; 
ModelChange=1;                          
}
break;
}

case 3: { 
pvarc=pvar; 
c=*pvarc;   
if (c<16) { 
(*pvarc)++; 
}
break;
}

case 4: { 
pvari=pvar; 
i=*pvari;   
if (i<2300) {
i=i+1+keyhold*9;
ModelChange=1;
}
if (i>2300) i=2300;
*pvari=i;
CalcCurveORD(); 
break;
}

case 6: { 
pvarc=pvar; 
c=*pvarc;   
if (c<8) { 
(*pvarc)++; 
ModelChange=1;
}
break;
}

case 7: { 
pvarsc=pvar; 
sc=*pvarsc;   
if (sc<125) {
sc=sc+1+2*keyhold;
ModelChange=1;
}
if (sc>125) sc=125;
*pvarsc=sc; 
break;
}

case 8: { 
pvarc=pvar; 
c=*pvarc;   
if (c<255) c=c+1+keyhold*2; else c=0; 
*pvarc=c; 
ModelChange=1;
break;
}

case 9: { 
pvarc=pvar; 
c=*pvarc;   
if (c==0) (*pvarc)=1;  else  (*pvarc)=0; 
ModelChange=1;
break;
}

case 10: { 
pvarc=pvar; 
c=*pvarc;   
if (c<3) (*pvarc)++; 
ModelChange=1;
break;
}

case 12: { 
pvarc=pvar; 
c=*pvarc;   
if (c+1<12 ) (*pvarc)++; 
ModelChange=1;
break;
}

case 13: { 
pvarsc=pvar; 
sc=*pvarsc;   
if (sc<125) sc=sc+1+2*keyhold;
if (sc>125) sc=125;
*pvarsc=sc; 
ModelChange=1;
break;
}

case 14: { 
pvari=pvar; 
i=*pvari;   
if (i<2300) i=i+1+keyhold*9;
if (i>2300) i=2300;
*pvari=i;
ModelChange=1; 
break;
}

case 15: { 
if (E_ClusterSize<64) { 
E_ClusterSize=E_ClusterSize+16;
}
break;
}

case 16: { 
pvarc=pvar; 
c=*pvarc;   
if (c==1) (*pvarc)=0;  else  (*pvarc)=1; 
E_SOUND_ON=SOUND_ON;
break; 
}

case 17: { 
pvarc=pvar; 
c=*pvarc;   
if (c<20) (*pvarc)++; 
E_key_press_time=key_press_time;
E_key_repress_time=key_repress_time;
resetKeyReader();
break;
}

case 19: { 
pvari=pvar; 
i=*pvari;   
if (i<840) i=i+7;
if (i>840) i=840;
*pvari=i;
E_battMin=i; 
break;
}

case 20: { 
c=E_eventStart;   
if (c<8) c++;  else  c=0; 
E_eventStart=c;
break;
}

case 21: { 
c=E_beep1min;   
if (c==1) c=0;  else  c=1; 
E_beep1min=c;
break;
}

case 22: { 
c=E_beep2sec;   
if (c==1) c=0;  else  c=1; 
E_beep2sec=c;
break;
}

case 23: { 
pvari=pvar; 
i=*pvari;   
if (posxmenu==1) { 
if ((i/60)<99) { 
(*pvari)=((i/60)+1)*60 + i%60;
ModelChange=1;
}
} 
else { 
if ((i%60)<59) {
(*pvari)=i+1;
ModelChange=1;
}
}
break; 
}

case 24: { 
flyCurrTimer=rmodel.MODEL_FLYTIMER;
break;
}

case 25: { 
if (flyCurrTimer<rmodel.MODEL_FLYTIMER) {

rmodel.MODEL_LIVETIMER=rmodel.MODEL_LIVETIMER+(rmodel.MODEL_FLYTIMER-flyCurrTimer)/60;
flyCurrTimer=rmodel.MODEL_FLYTIMER;
ModelChange=1;
}
break;
}

case 26: { 
pvarc=pvar; 
c=*pvarc;   
if (c<20) (*pvarc)++; 
E_trim_press_time=trim_press_time;
break;
}

case 27: { 
c=E_eventStop;   
if (c<8) c++;  else  c=0; 
E_eventStop=c;
break;
}

case 28: { 
c=E_nulTrimBeep;   
if (c==1) c=0;  else  c=1; 
E_nulTrimBeep=c;
break;
}

case 29: { 
rmodel.FMODE[fmode_to-1].FMODE_NAME=rmodel.FMODE[fmode_source-1].FMODE_NAME;
rmodel.FMODE[fmode_to-1].TRIMSTEP=rmodel.FMODE[fmode_source-1].TRIMSTEP;

for (c=0;c<7;c++) 
rmodel.FMODE[fmode_to-1].UCH_TRIMMER[c]=rmodel.FMODE[fmode_source-1].UCH_TRIMMER[c];

for (c=0;c<16;c++) 
rmodel.FMODE[fmode_to-1].LCH_MIDLE[c]=rmodel.FMODE[fmode_source-1].LCH_MIDLE[c];

for (c=0;c<16;c++) 
rmodel.FMODE[fmode_to-1].LCH_CURVE[c]=rmodel.FMODE[fmode_source-1].LCH_CURVE[c];       

for (c=0;c<40;c++)
rmodel.FMODE[fmode_to-1].MIXER[c]=rmodel.FMODE[fmode_source-1].MIXER[c];                   

break;
}

case 30: { 
if (E_var3==0) E_var3=1;  else  E_var3=0; 
break;
}

case 31: { 
if (E_var4<45) { 
E_var4++; 
LCD_setContrast(E_var4);
}

break;
}

case 32: { 
if (E_var11<254) {
E_var11++; 
}
break;
}

case 33: { 
if (E_var12>1) E_var12--;
break;
}

}
}

void disp_menu(void) { 
unsigned char printStart; 
unsigned char i,j,tmp, tmp2, tmp3, paramcount;        
unsigned char mode, mode1, mode2;       
unsigned char * pvarc;    
unsigned int  * pvari;    
unsigned int  ti; 
signed char * pvarsc; 
signed char  sc;

unsigned char itemcounter; 
unsigned char downstop; 

printStart=getIDbefore(100); 
printStart=menu[numItemByID(printStart)].upitem; 
LCD_setxy(0,0); 
while (LCD_X<20) LCD_char(' ', 1); 
LCD_wrsf(menu[numItemByID(printStart)].itemstr,1); 
while (LCD_X<123) LCD_char(' ', 1); 

pvarc=menu[numItemByID(printStart)].colitemcount; 
if (pvarc!=0) itemcounter=*pvarc; else itemcounter=255;   

printStart=getIDbefore(5); 

paramcount=0;  

for (i=0;i<6;i++) { 

tmp2=numItemByID(printStart); 

if (printStart!=numitem_cur) { 
mode=0; mode2=0;  
} 
else { 
mode=1;    
if (posxmenu==0) mode2=1; else mode2=1; 
}   

LCD_setxy(0,i+2); LCD_wrsf ( menu[ tmp2 ].itemstr, mode2); 
while (LCD_X<59) LCD_char(' ',mode2); 

LCD_setxy(60, i+2);

if ((menu[ tmp2 ].downitem!=0)||(menu[ tmp2 ].menu_proc!=0))  { LCD_char('>',0); } 
else { if (menu[ tmp2 ].partype!=0) LCD_char('=',0); else LCD_char(' ',0); }

LCD_setxy(65, i+2);

switch (mode) {       
case 0: { 
mode1=0; mode2=0; break; 
}

case 1: { 
if (posxmenu==0) { mode1=1;  mode2=1; } 
if (posxmenu==1) { mode1=2;  mode2=1; } 
if (posxmenu==2) { mode1=1;  mode2=2; }                   
break; 
} 
}
LCD_X=LCD_X+5;
tmp=menu[ tmp2 ].partype; 
switch (tmp) {
case 1: { 
pvarc=menu[ tmp2 ].pvar1; 
if (((*pvarc)>=0) && ((*pvarc)<3))
LCD_wrsf(MODEL_TYPE[*pvarc],mode1); 
if (mode==1) paramcount=1;
break;
}

case 2: { 
pvarc=menu[ tmp2 ].pvar1;
for(j=0;j<8;j++) {
LCD_char(*pvarc, mode1);
pvarc++; 
}
if (mode==1) paramcount=0;
break; 
}

case 3: { 
pvarc=menu[ tmp2 ].pvar1;
LCD_dec(*pvarc, 2, mode1);
if (mode==1) paramcount=1;
break; 
}

case 4: { 
pvari=menu[ tmp2 ].pvar1;
LCD_dec(*pvari, 4, mode1);

LCD_char(' ', 0); LCD_char(' ', 0);

pvari=menu[ tmp2 ].pvar2;
LCD_dec(*pvari, 4, mode2);
if (mode==1) paramcount=2;
break; 
}

case 5: { 
pvarc=menu[ tmp2 ].pvar1; 
LCD_wrsf(CHANNEL_FILTER_TYPE[*pvarc],mode1); 
LCD_char(' ',mode1);

pvari=menu[ tmp2 ].pvar2; 

switch (*pvarc) { 
case 1: {  
LCD_wrsf(UCH_Names[(*pvari)%256],mode1); 
break;
}
case 2: { 
ti=*pvari;
for (j=0;j<16;j++) {
if ((ti%2)==1) LCD_char(CHNUM_table[j],mode1);
ti=ti/2;
}
}
} 
if (mode==1) paramcount=0; 
break;
}

case 6: { 
pvarc=menu[ tmp2 ].pvar1;
LCD_dec(*pvarc, 1, mode1);
if (mode==1) paramcount=1;
break; 
}          

case 7: { 
pvarsc=menu[ tmp2 ].pvar1;
sc=*pvarsc;
if (sc<0) { LCD_char('-',mode1); sc=-sc; } else LCD_char('+',mode1);
LCD_dec(sc, 3, mode1); LCD_char('%',mode1);

LCD_char(' ',0);
pvarsc=menu[ tmp2 ].pvar2;
sc=*pvarsc;
if (sc<0) { LCD_char('-',mode2); sc=-sc; } else LCD_char('+',mode2);
LCD_dec(sc, 3, mode2); LCD_char('%',mode2);

if (mode==1) paramcount=2;
break; 
}          

case 8: { 
pvarc=menu[ tmp2 ].pvar1;
LCD_dec(*pvarc, 3, mode1);

LCD_char(' ', 0); LCD_char(' ', 0);

pvarc=menu[ tmp2 ].pvar2;
LCD_dec(*pvarc, 3, mode2);

if (mode==1) paramcount=2;
break; 
}

case 9: { 
pvarc=menu[ tmp2 ].pvar1;
if ((*pvarc)==0) LCD_wrsf("NORMAL", mode1); else LCD_wrsf("REVERSE", mode1);
if (mode==1) paramcount=1;
break; 
}          

case 10: { 
pvarc=menu[ tmp2 ].pvar1;
LCD_dec(*pvarc, 1, mode1);
if (mode==1) paramcount=1;
break; 
}          

case 11: { 
pvarc=menu[ tmp2 ].pvar1; 
LCD_wrsf(SL_FMODE_NAME[*pvarc],mode1); 
if (mode==1) paramcount=0;
break;
}

case 12: { 
pvarc=menu[ tmp2 ].pvar1; 
LCD_wrsf(SL_FMODE_NAME[*pvarc],mode1); 
if (mode==1) paramcount=1;
break;
}

case 13: { 
pvarsc=menu[ tmp2 ].pvar1;
sc=*pvarsc;
if (sc<0) { LCD_char('-',mode1); sc=-sc; } else LCD_char('+',mode1);
LCD_dec(sc, 3, mode1); 
if (mode==1) paramcount=1;
break; 
}          

case 14: { 
LCD_X=LCD_X-4;
pvari=menu[ tmp2 ].pvar1;

if ((printStart>=175) && (printStart<=190)) { 

tmp3=printStart-175; 
}  else
if ((printStart>=191) && (printStart<=206)) { 

tmp3=printStart-191; 
}  else
if ((printStart>=207) && (printStart<=222)) { 

tmp3=printStart-207; 
} 
ti=((*pvari)-rmodel.CHANNELS.CH_EPL[tmp3]);
if (ti<1000) LCD_dec(ti,3,0); else LCD_wrsf("---",0);
LCD_char(' ',0);

LCD_dec(*pvari, 4, mode1);

LCD_char(' ',0);
ti=(rmodel.CHANNELS.CH_EPR[tmp3]-(*pvari));
if (ti<1000) LCD_dec(ti,3,0); else LCD_wrsf("---",0);

if (mode==1) paramcount=1;
break; 
}

case 15: { 
LCD_dec(E_ClusterSize, 2, mode1);
if (mode==1) paramcount=1;
break; 
}

case 16: { 
pvarc=menu[ tmp2 ].pvar1;
if ((*pvarc)==1) LCD_wrsf("ON", mode1); else LCD_wrsf("OFF", mode1);
if (mode==1) paramcount=1;
break; 
}          

case 17: { 
pvarc=menu[ tmp2 ].pvar1;
LCD_dec(*pvarc, 2, mode1);
if (mode==1) paramcount=1;
break; 
}

case 18: { 
pvari=menu[ tmp2 ].pvar1;
ti=*pvari;
ti=ti/7;
LCD_dec(ti/10, 2, mode1);
LCD_char('.',mode1);
LCD_dec(ti%10, 1, mode1);
LCD_wrsf(" V",mode1);                                       
if (mode==1) paramcount=0;
break; 
}

case 19: { 
pvari=menu[ tmp2 ].pvar1;
ti=*pvari;
ti=ti/7;
LCD_dec(ti/10, 2, mode1);
LCD_char('.',mode1);
LCD_dec(ti%10, 1, mode1);
LCD_wrsf(" V",mode1);       

if (ti<95) {
LCD_setxy(0,5); LCD_wrsf("        WARNING !        ",1);
LCD_setxy(0,6); LCD_wrsf("  USE THIS VALUE NOT FOR ",0);
LCD_setxy(0,7); LCD_wrsf("     3S LIPO BATTERY     ",0);
}                                
if (mode==1) paramcount=1;
break; 
}

case 20: { 
if (E_eventStart==8) LCD_wrsf("MANUAL",mode1);
else { 
LCD_wrsf("CH",mode1);
LCD_dec((unsigned int)E_eventStart+1,1,mode1);
LCD_wrsf(" >20%",mode1);
}                    
if (mode==1) paramcount=1;
break; 
}

case 21: { 
if (E_beep1min==0) LCD_wrsf("OFF",mode1);
else LCD_wrsf("ON",mode1);                    
if (mode==1) paramcount=1;
break; 
}

case 22: { 
if (E_beep2sec==0) LCD_wrsf("OFF",mode1);
else LCD_wrsf("ON",mode1);                    
if (mode==1) paramcount=1;
break; 
}

case 23: { 
pvari=menu[ tmp2 ].pvar1;
LCD_dec(*pvari/60, 2, mode1);
LCD_char(' ', 0); 
if (menu[tmp2].numitem==132) LCD_char('M',0); else LCD_char('H',0); 
LCD_char(' ', 0);
LCD_dec(*pvari%60, 2, mode2);
LCD_char(' ', 0);
if (menu[tmp2].numitem==132) LCD_char('S',0); else LCD_char('M',0);                                                            
if (mode==1) paramcount=2;
break; 
}

case 24: { 
if (flyCurrTimer==rmodel.MODEL_FLYTIMER) { 
LCD_wrsf("---",mode1);
if (mode==1) { paramcount=0; posxmenu=0; }
}
else { 
LCD_wrsf("USE CURR",mode1);                    
if (mode==1) paramcount=1;
}
break; 
}

case 25: { 
if ((flyCurrTimer+60)>rmodel.MODEL_FLYTIMER) { 
LCD_wrsf("---",mode1);
if (mode==1) { paramcount=0; posxmenu=0; }
}
else { 
LCD_wrsf("ADD TIME",mode1);                    
if (mode==1) paramcount=1;
}
break; 
}

case 26: { 
pvarc=menu[ tmp2 ].pvar1;
LCD_dec(*pvarc, 2, mode1);
if (mode==1) paramcount=1;
break; 
}

case 27: { 
if (E_eventStop==8) LCD_wrsf("MANUAL",mode1);
else { 
LCD_wrsf("CH",mode1);
LCD_dec((unsigned int)E_eventStop+1,1,mode1);
LCD_wrsf(" <10%",mode1);
}                    
if (mode==1) paramcount=1;
break; 
}

case 28: { 
if (E_nulTrimBeep==0) LCD_wrsf("NO EVENT",mode1);
else LCD_wrsf("BEEP&PAUSE",mode1);                    
if (mode==1) paramcount=1;
break; 
}

case 29: { 
LCD_wrsf("COPY",mode1);
if (mode==1) paramcount=1;
break; 
}

case 30: { 
if (E_var3==0) LCD_wrsf("POSITIVE",mode1);
else LCD_wrsf("NEGATIVE",mode1);                    
if (mode==1) paramcount=1;
break; 
}

case 31: { 
LCD_dec(E_var4, 2, mode1);
if (mode==1) paramcount=1;
break; 
}

case 32: { 
if (E_var11>127) {
LCD_char('+',mode1);
ti=E_var11-127;
} else {
LCD_char('-',mode1);
ti=127-E_var11;                    
}
LCD_dec(ti, 3, mode1);
if (mode==1) paramcount=1;
break; 
}

case 33: { 
LCD_dec(E_var12, 1, mode1);
if (mode==1) paramcount=1;
break; 
}

}

downstop=0;

if ((itemcounter==menu[ tmp2 ].colitem) && (mode==1)) {

downstop=1; 
} 

if (itemcounter==menu[ tmp2 ].colitem) {
break; 
} 

printStart=menu[ tmp2 ].nextitem;   
if (printStart==0) { break; } 
}

tmp2=numItemByID(numitem_cur);
i=get_mnu_keys(); 
switch (i) { 

case 246: {  
switch (posxmenu) {

case 0: { 
if ((menu[tmp2].nextitem!=0) && (downstop==0)) { 

numitem_cur=menu[tmp2].nextitem;  
}
break; 
}  

case 1: { 
decreaseValuePar(menu[tmp2].partype,menu[tmp2].pvar1); 
break;
}

case 2: { 
decreaseValuePar(menu[tmp2].partype,menu[tmp2].pvar2); 

} 
}  
break; 
} 

case 238: { 
switch (posxmenu) {

case 0: { 
if (menu[tmp2].previtem!=0) {
numitem_cur=menu[tmp2].previtem;
}
break;
}

case 1: { 
increaseValuePar(menu[tmp2].partype,menu[tmp2].pvar1); 
break;
}

case 2: { 
increaseValuePar(menu[tmp2].partype,menu[tmp2].pvar2); 

}  
}
break;
} 

case 250: { 
if (menu[numItemByID(numitem_cur)].upitem!=0) { 
numitem_cur=menu[numItemByID(numitem_cur)].upitem;
posxmenu=0; 
} 
else { 
if (ModelChange==1) {
ModelChange=0;
menu_proc=menu_req_save_model;
menu_exe=1;
} 
else  disp_mode=2; 
}
resetKeyReader(); 
break; }

case 252: {  

resetKeyReader(); 

if (menu[numItemByID(numitem_cur)].downitem!=0) { 
numitem_cur=menu[numItemByID(numitem_cur)].downitem;
posxmenu=0;
}
else {   
if (menu[numItemByID(numitem_cur)].menu_proc!=0) {  
menu_proc=menu[numItemByID(numitem_cur)].menu_proc; 
menu_exe=1;   
} 
else {  
if (paramcount>posxmenu) posxmenu++; else posxmenu=0;
}
}          
break; 
} 

case 222: {  if (paramcount>posxmenu) posxmenu++; 
break; }

case 190: {  if (posxmenu>0) posxmenu--;          
break; }

default:

}
}              

unsigned char flyinfo_mode; 

unsigned char mess_posx, mess_char, mess_pause;
void messScroll(void) {

LCD_setxy(0,1); LCD_wrsf("   V-CODER  ver. 0.99b   ",0);
}

void printTrimMode12() {
signed char sc;

sc=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[2];
if (E_var12==2) LCD_setxy(0,3); else LCD_setxy(120,3);
if (sc<0) { LCD_char('-',0); sc=-sc; } else { LCD_char('+',0); }
if (E_var12==2) LCD_setxy(0,4); else LCD_setxy(120,4);  
LCD_V_dec(2*((unsigned int)sc) , 3, 0);

sc=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[1];
if (E_var12==2) LCD_setxy(120,3); else LCD_setxy(0,3); 
if (sc<0) { LCD_char('-',0); sc=-sc; } else { LCD_char('+',0); }
if (E_var12==2) LCD_setxy(120,4); else LCD_setxy(0,4);
LCD_V_dec(2*((unsigned int)sc) , 3, 0);

sc=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[3];
LCD_setxy(5,7);
if (sc<0) { LCD_char('-',0); sc=-sc; } else { LCD_char('+',0); }
LCD_dec(2*((unsigned int)sc) , 3, 0);

sc=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[0];
LCD_setxy(100,7);
if (sc<0) { LCD_char('-',0); sc=-sc; } else { LCD_char('+',0); }
LCD_dec(2*((unsigned int)sc) , 3, 0);
}

void printTrimMode34() {
signed char sc;

sc=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[2];
if (E_var12==4) LCD_setxy(120,3); else LCD_setxy(0,3);
if (sc<0) { LCD_char('-',0); sc=-sc; } else { LCD_char('+',0); }
if (E_var12==4) LCD_setxy(120,4); else LCD_setxy(0,4);  
LCD_V_dec(2*((unsigned int)sc) , 3, 0);

sc=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[1];
if (E_var12==4) LCD_setxy(0,3); else LCD_setxy(120,3); 
if (sc<0) { LCD_char('-',0); sc=-sc; } else { LCD_char('+',0); }
if (E_var12==4) LCD_setxy(0,4); else LCD_setxy(120,4);
LCD_V_dec(2*((unsigned int)sc) , 3, 0);

sc=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[3];
LCD_setxy(100, 7);
if (sc<0) { LCD_char('-',0); sc=-sc; } else { LCD_char('+',0); }
LCD_dec(2*((unsigned int)sc) , 3, 0);

sc=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[0];
LCD_setxy(5, 7);
if (sc<0) { LCD_char('-',0); sc=-sc; } else { LCD_char('+',0); }
LCD_dec(2*((unsigned int)sc) , 3, 0);
}

void flyInfo(void) {
unsigned char i,x,y;

unsigned int ii; 

LCD_setxy(0,0); for (i=0;i<8;i++) LCD_char(rmodel.MODEL_NAME[i], ModelChange);

LCD_setxy(50,0); 
LCD_wrsf(SL_FMODE_NAME[rmodel.FMODE[FMODE_NUM].FMODE_NAME],1);

LCD_setxy(100,0);
ii=batt/7;
LCD_dec(ii/10, 2, 0);
LCD_char('.',0);
LCD_dec(ii%10, 1, 0);
LCD_char('v',0);                                       

switch (E_var12) {
case 1: { printTrimMode12(); break; }
case 2: { printTrimMode12(); break; }
case 3: { printTrimMode34(); break; }
case 4: { printTrimMode34(); break; }
} 

if (flyinfo_mode!=4) {
LCD_big_dec(38,48, flyCurrTimer/60 ,2);
if ((flyTimerOn==1) && (BLINK==1)) LCD_big_char(58,48,' '); else LCD_big_char(58,48,':');
LCD_big_dec(68,48, flyCurrTimer%60 ,2);
} else 
{ 
LCD_big3_dec(25,25, flyCurrTimer/60 ,2);
if ((flyTimerOn==1) && (BLINK==1)) LCD_big3_char(55,25,' '); else LCD_big3_char(55,25,':');
LCD_big3_dec(70,25, flyCurrTimer%60 ,2);   

messScroll();                                  
}  

switch (flyinfo_mode) {
case 1: { 
LCD_setxy(10,3); LCD_wrsf("THRCT",PINE.0     );
LCD_setxy(10,4); LCD_wrsf("RUD.D", ((*(unsigned char *) 0x63) & 1) );
LCD_setxy(10,5); LCD_wrsf("ELE.D", PINE.2     );

LCD_setxy(90,3); LCD_wrsf("TRN.", PINE.5     );
LCD_setxy(90,4); LCD_wrsf("GEAR",PINE.4     );
LCD_setxy(90,5); LCD_wrsf("AIL.D",PINE.1     ); 

LCD_setxy(40,3); LCD_wrsf("HOVP", 0); LCD_X++; LCD_X++;
if (UCH_VAL_PROC[4]<0) { 
LCD_char('-',0); LCD_dec(-UCH_VAL_PROC[4],3,0); } 
else { LCD_char('+',0); LCD_dec(UCH_VAL_PROC[4],3,0); } 

LCD_setxy(40,4); LCD_wrsf("HOVT", 0); LCD_X++; LCD_X++;
if (UCH_VAL_PROC[5]<0) { 
LCD_char('-',0); LCD_dec(-UCH_VAL_PROC[5],3,0); } 
else { LCD_char('+',0); LCD_dec(UCH_VAL_PROC[5],3,0); } 

LCD_setxy(40,5); LCD_wrsf("PITT", 0); LCD_X++; LCD_X++;
if (UCH_VAL_PROC[6]<0) { 
LCD_char('-',0); LCD_dec(-UCH_VAL_PROC[6],3,0); } 
else { LCD_char('+',0); LCD_dec(UCH_VAL_PROC[6],3,0); }

messScroll();                                  
break; 
}

case 2: { 

for (x=0;x<2;x++) { 
for (y=0;y<4;y++) { 
if ((x*4+y)<rmodel.CHANNELS.PPM_CH_COUNT) {
LCD_setxy(10+x*65,y+2); 
LCD_wrsf("CH",0); LCD_dec((unsigned char)(x*4+y+1),1,0);
LCD_char(' ',0);
LCD_dec(CH_PPM[(unsigned char)(x*4+y)],4,0);
}
}
}      
break; 
}

case 3: { 
for (x=0;x<2;x++) { 
for (y=0;y<4;y++) { 
if ((x*4+y)<rmodel.CHANNELS.PPM_CH_COUNT) { 

LCD_setxy(10+x*60,y+2); 
LCD_wrsf("CH",0); LCD_dec((unsigned char)(x*4+y+1),1,0);
LCD_char(' ',0);

if ((CH_PPM[(unsigned char)(x*4+y)]>=rmodel.CHANNELS.CH_EPL[(unsigned char)(x*4+y)]) && 
(CH_PPM[(unsigned char)(x*4+y)]<=rmodel.CHANNELS.CH_EPR[(unsigned char)(x*4+y)]))  {

ii=(CH_PPM[(unsigned char)(x*4+y)] - rmodel.CHANNELS.CH_EPL[(unsigned char)(x*4+y)]);

ii=ii /
(( rmodel.CHANNELS.CH_EPR[(unsigned char)(x*4+y)] - 
rmodel.CHANNELS.CH_EPL[(unsigned char)(x*4+y)]) / 25) ;

for (i=0;i<(unsigned char)ii; i++) {
LCD_out(0x7E);     
}

while (i<25) {
LCD_out(0x10);
i++;
} 
}  

else {
if (CH_PPM[(unsigned char)(x*4+y)]<=rmodel.CHANNELS.CH_EPL[(unsigned char)(x*4+y)])
LCD_wrsf("<MIN ",2); else LCD_wrsf(">MAX ",2);

}

}
}
}      
break; 
}

}     

i=get_mnu_keys(); 
switch (i) {
case 190: {  if (flyinfo_mode<4) flyinfo_mode++;  
else flyinfo_mode=1; 
break; }

case 222: {  if (flyinfo_mode>1) flyinfo_mode--; 
else flyinfo_mode=4;
break; } 

case 252: {  disp_mode=1; 
break; }

case 250: {  

if (flyTimerOn!=0) flyTimerOn=0;
else { 
if (keyhold==1) {
flyTimerOn=0; 
flyCurrTimer=rmodel.MODEL_FLYTIMER; 
TimerEndBeepCounter=0;
TimerEnd=0;
}
}  
break;
} 

}

}

void resetMenu() { 
disp_mode=2; 
flyinfo_mode=1; 

posxmenu=0;    
numitem_cur=1; 

menu_exe=0; 
menu_proc=0;

system_calibration_part=0; 

temp1=0; 
temp2=0;
temp3=0;
temp4=0;
temp5=0;

fmode_source=1;
fmode_to=2;  
}

void PrintMessage() {

LCD_setxy(0,1); LCD_wrsf(messStr1,1); 

LCD_setxy(0,3); LCD_wrsf(messStr2,0); 
LCD_setxy(0,4); LCD_wrsf(messStr3,0); 
LCD_setxy(0,5); LCD_wrsf(messStr4,0); 
LCD_setxy(0,6); LCD_wrsf(messStr5,0); 

messRetCode=get_mnu_keys();   
switch (printMess) { 

case 1 : { 
if (messRetCode==250)  {
printMess=0;
resetKeyReader(); 
}   
break;
}

case 2: { 
if ( (messRetCode==250) || (messRetCode=252) )  {
printMess=0;                   
resetKeyReader(); 
}
break;   
}  

case 3 : { 
if (messRetCode==252)  {
printMess=0;
resetKeyReader(); 
}   
break;
}  
}
} 

void disp() {

if (printMess==0) { 

switch (disp_mode) {

case 1 : {  
if (menu_exe==1) {       
menu_proc();
} 
else { 

disp_menu();  
flyTimerOn=0; 
}                 
break; 
}

case 2 : {  
flyInfo();  
break;  
}
}
} 
else { 
PrintMessage();
}
}    
void OpenModel(unsigned char filenum); 
void menu_FILE_RESET(); 
void FILE_RESET(); 

eeprom unsigned char E_CurModelNum; 

eeprom unsigned char E_eventStop;   
eeprom unsigned char PPM_capture; 
eeprom unsigned char E_var3;      
eeprom unsigned char E_var4;      
eeprom unsigned char E_trim_press_time; 
eeprom unsigned char E_nulTrimBeep; 

eeprom unsigned char E_var11; 
eeprom unsigned char E_var12; 

eeprom unsigned int  E_vari2;
eeprom unsigned int  E_vari3;
eeprom unsigned int  E_vari4;

eeprom unsigned int  E_vari5;
eeprom unsigned int  E_vari6;
eeprom unsigned int  E_vari7;
eeprom unsigned int  E_vari8;
eeprom unsigned int  E_vari9;
eeprom unsigned int  E_vari10;

eeprom unsigned char E_eventStart; 

unsigned int LightOn; 
unsigned char ppmStop; 
unsigned char flyTimerOn; 
unsigned int flyCurrTimer; 
unsigned int OnCurrTimer; 
unsigned char TimerEnd; 
unsigned char TimerEndBeepCounter; 

eeprom unsigned char E_beep1min; 
eeprom unsigned char E_beep2sec; 

eeprom unsigned int E_UCHmid[7]; 
eeprom unsigned int E_UCHmin[7]; 
eeprom unsigned int E_UCHmax[7]; 

unsigned char ClusterSize; 

eeprom unsigned char E_SOUND_ON; 
unsigned char SOUND_ON; 

eeprom unsigned char E_key_press_time; 
eeprom unsigned char E_key_repress_time; 

unsigned char key_press_time; 
unsigned char key_repress_time; 

unsigned char trim_press_time; 

unsigned int UCH_VALUES[14];   
signed  char UCH_VAL_PROC[14]; 

eeprom unsigned int E_battMin; 
unsigned int battMin;    
unsigned int batt;       

unsigned int UCHmid[7]; 
unsigned int UCHmin[7]; 
unsigned int UCHmax[7]; 

unsigned int FMODE_NUM; 

unsigned int LCH_LEN[16]; 
unsigned int OLD_LCH_LEN[16]; 

unsigned char PPM_CUR_CH_NUM; 
unsigned int CH_PPM[8]; 
unsigned int PPM_PAUSE; 

unsigned char mch[8]; 

unsigned int CURVE_POINT[16][9][2]; 

unsigned char BLINK_TIMER; 
unsigned char BLINK; 

flash unsigned char *messStr1; 
flash unsigned char *messStr2; 
flash unsigned char *messStr3; 
flash unsigned char *messStr4; 
flash unsigned char *messStr5; 

unsigned char messRetCode; 

unsigned char printMess; 

unsigned int     outx1, outx2, outx3, outy1, outy2, outy3, outkk; 

unsigned char ModelChange; 

unsigned char mixercount;  
unsigned char mixtochan;   
unsigned char mixtochanlast;   

unsigned char getMixCount(unsigned char fmode) {
unsigned char i;

for (i=0;i<39;i++) { 

if (rmodel.FMODE[fmode].MIXER[i].MIX_TYPE.ACTIVE==0) {
break;
}
}
return i;
}

void MixerCalc(unsigned char mixstart, unsigned char mixend) { 

unsigned int i; 
unsigned char sw, swon; 

unsigned char soursech, destinch; 

unsigned long int chval; 
unsigned long int chmin, chmid, chmax; 
unsigned long int dchmin, dchmid, dchmax; 
unsigned long int soursesc, destsc; 
unsigned long int res; 

unsigned char signres; 

signed char mixproc; 
unsigned char mixuch; 

for (i=mixstart;i<mixend;i++) { 

if (rmodel.FMODE[FMODE_NUM].MIXER[i].MIX_TYPE.ACTIVE==1) {

if (rmodel.FMODE[FMODE_NUM].MIXER[i].MIX_TYPE.MIX_SW==1) {

sw=rmodel.FMODE[FMODE_NUM].MIXER[i].MIX_TYPE.UCH_SW+7;
if (UCH_VALUES[sw]==1) { 

if (rmodel.FMODE[FMODE_NUM].MIXER[i].MIX_TYPE.SW_INV==0) swon=1;
else swon=0; 
} 
else { 

if (rmodel.FMODE[FMODE_NUM].MIXER[i].MIX_TYPE.SW_INV==0) swon=0;
else swon=1; 
}
} 
else { 
swon=1;
}
} else swon=0;

if (swon==1) { 

destinch=rmodel.FMODE[FMODE_NUM].MIXER[i].CH_NUM.CH_DEST; 
dchmid=rmodel.FMODE[FMODE_NUM].LCH_MIDLE[destinch];       
dchmin=rmodel.CHANNELS.CH_EPL[destinch];                  
dchmax=rmodel.CHANNELS.CH_EPR[destinch];                  

soursech=rmodel.FMODE[FMODE_NUM].MIXER[i].CH_NUM.CH_SOURSE; 

if (rmodel.FMODE[FMODE_NUM].MIXER[i].MIX_TYPE.SOURSE_TYPE==1) {

chval=OLD_LCH_LEN[soursech]; 
chmid=rmodel.FMODE[FMODE_NUM].LCH_MIDLE[soursech]; 
chmin=rmodel.CHANNELS.CH_EPL[soursech];            
chmax=rmodel.CHANNELS.CH_EPR[soursech];            
}
else {

chval=UCH_VALUES[soursech]; 
if (soursech<7) { 
chmid=UCHmid[soursech]; 
chmin=UCHmin[soursech]; 
chmax=UCHmax[soursech]; 
} 
else { 
if (soursech==7) { 
chmin=0;
chmid=0;
chmax=1;
chval=1;                    
} 
else {  
chmid=0;
chmin=0;
chmax=1;                          
}
}

}

if (rmodel.FMODE[FMODE_NUM].MIXER[i].MIX_TYPE.PROC_SOURSE==1) {

mixuch=rmodel.FMODE[FMODE_NUM].MIXER[i].MIX_VAL & 0x0F;
if (mixuch==7) mixproc=100; else mixproc=UCH_VAL_PROC[mixuch]; 

if ((rmodel.FMODE[FMODE_NUM].MIXER[i].MIX_VAL & 0x10)!=0) {
mixproc=-mixproc;             
}
} 
else { 
mixproc=rmodel.FMODE[FMODE_NUM].MIXER[i].MIX_VAL;
}    

if (rmodel.CHANNELS.LCH_REV[destinch]==1) { 
mixproc=-mixproc;
}

if (chval>chmid) { 
soursesc=chmax-chmid; 
chval=chval-chmid;
if (mixproc>0) {
destsc=dchmax-dchmid; 
signres=1;
} 
else {
destsc=dchmid-dchmin; 
signres=0;
mixproc=-mixproc;
}

}  
else { 
chval=chmid-chval;
soursesc=chmid-chmin; 

if (mixproc<0) {
destsc=dchmax-dchmid; 
signres=1;
mixproc=-mixproc;
} 
else {
destsc=dchmid-dchmin; 
signres=0;
}
}

res=(destsc*chval*mixproc)/(soursesc*100); 

if (signres==1) 
LCH_LEN[destinch]=LCH_LEN[destinch]+(unsigned int)res; 
else
LCH_LEN[destinch]=LCH_LEN[destinch]+-(unsigned int)res;     
}       
}     
}

void CalcCurveORD(void) {
unsigned long int ti, til, tir; 
unsigned char tc, tc1; 
signed   char tsc; 

for (tc1=0; tc1<16; tc1++) {

CURVE_POINT[tc1][0][0]=rmodel.CHANNELS.CH_EPL[tc1]; 

ti=( rmodel.FMODE[FMODE_NUM].LCH_MIDLE[tc1] - CURVE_POINT[tc1][0][0] ) / 4; 

for (tc=1;tc<4;tc++) CURVE_POINT[tc1][tc][0]= CURVE_POINT[tc1][tc-1][0] + ti; 

CURVE_POINT[tc1][4][0]=rmodel.FMODE[FMODE_NUM].LCH_MIDLE[tc1]; 

ti=(  rmodel.CHANNELS.CH_EPR[tc1] - CURVE_POINT[tc1][4][0] ) / 4; 

for (tc=5; tc<8; tc++) CURVE_POINT[tc1][tc][0]= CURVE_POINT[tc1][tc-1][0] + ti; 

CURVE_POINT[tc1][8][0]=rmodel.CHANNELS.CH_EPR[tc1]; 

til=CURVE_POINT[tc1][4][0] - CURVE_POINT[tc1][0][0]; 
tir=CURVE_POINT[tc1][8][0] - CURVE_POINT[tc1][4][0]; 

for (tc=0; tc<9; tc++) { 
tsc=rmodel.FMODE[FMODE_NUM].LCH_CURVE[tc1].point[tc]; 
if (tsc>=0) 
CURVE_POINT[tc1][tc][1]=CURVE_POINT[tc1][4][0] + (tir * tsc) / 100;
else { 
tsc=-tsc;
CURVE_POINT[tc1][tc][1]=CURVE_POINT[tc1][4][0] - (til * tsc) / 100;              
}        
}
} 
}

unsigned int read_adc(unsigned char adc_input) {
ADMUX=adc_input|0x40 ;
delay_us(10);
ADCSRA|=0x40;               
while ((ADCSRA & 0x10)==0);
ADCSRA|=0x10; 
return ADCW;
}

unsigned char FMODE_OLD;
void read_UCH_values(void) {
int i; 
signed int s;

for(i=0; i<7; i++) {                            
if (E_var12==2)  
switch (i) {
case 1 : { UCH_VALUES[i]=read_adc(2); break; }
case 2 : { UCH_VALUES[i]=read_adc(1); break; }
default: UCH_VALUES[i]=read_adc(i);            
} else 
if (E_var12==3)  
switch (i) {
case 1 : { UCH_VALUES[i]=read_adc(2); break; }
case 2 : { UCH_VALUES[i]=read_adc(1); break; }
case 0 : { UCH_VALUES[i]=read_adc(3); break; } 
case 3 : { UCH_VALUES[i]=read_adc(0); break; } 
default: UCH_VALUES[i]=read_adc(i);            
} else
if (E_var12==4)  
switch (i) {
case 0 : { UCH_VALUES[i]=read_adc(3); break; } 
case 3 : { UCH_VALUES[i]=read_adc(0); break; } 

default: UCH_VALUES[i]=read_adc(i);            
} else    UCH_VALUES[i]=read_adc(i); 

if (UCH_VALUES[i]>UCHmax[i]) UCHmax[i]=UCH_VALUES[i];
if (UCH_VALUES[i]<UCHmin[i]) UCHmin[i]=UCH_VALUES[i];

s=((signed int)rmodel.UCH[i].UCH_RIGHT-rmodel.UCH[i].UCH_LEFT)/2; 

if (UCH_VALUES[i]>UCHmid[i]) {

UCH_VAL_PROC[i]=rmodel.UCH[i].UCH_LEFT+s+(UCH_VALUES[i]-UCHmid[i]) * s / (UCHmax[i]-UCHmid[i]) ;
} 
else {

UCH_VAL_PROC[i]=rmodel.UCH[i].UCH_LEFT+(UCH_VALUES[i]-UCHmin[i])*s/(UCHmid[i]-UCHmin[i]);     
}

if (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[i]>=0) { 
UCH_VALUES[i]=UCH_VALUES[i]+((unsigned int)rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[i])*2;
if (UCH_VALUES[i]>UCHmax[i]) UCH_VALUES[i]=UCHmax[i];    
}
else {
if (UCH_VALUES[i]>(2*((unsigned int)(-rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[i])))) 
UCH_VALUES[i]=UCH_VALUES[i]-(2*((unsigned int)(-rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[i])));
else UCH_VALUES[i]=UCHmin[i]; 
if (UCH_VALUES[i]<UCHmin[i]) UCH_VALUES[i]=UCHmin[i];
}

}

if (((*(unsigned char *) 0x63) & 8)   ==0) { UCH_VALUES[7]=0; } else UCH_VALUES[7]=1;
if (!PINE.6     ) { UCH_VALUES[7]=2; }

if (UCH_VALUES[7]<=(rmodel.FMODE_COUNT-1)) 
FMODE_NUM=UCH_VALUES[7];
else FMODE_NUM=rmodel.FMODE_COUNT-1;

mixercount=getMixCount(FMODE_NUM); 
if (mixercount<rmodel.CHANNELS.PPM_CH_COUNT) {
mixtochan=1;
mixtochanlast=0;
} else {
mixtochan=mixercount/rmodel.CHANNELS.PPM_CH_COUNT;
mixtochanlast=mixercount%rmodel.CHANNELS.PPM_CH_COUNT;
}

if (FMODE_NUM!=FMODE_OLD) {
CalcCurveORD(); 
FMODE_OLD=FMODE_NUM;
}

UCH_VALUES[8]=PINE.4     ;     if (PINE.4     ==1) { UCH_VAL_PROC[8]=rmodel.UCH[8].UCH_RIGHT; 
} else { UCH_VAL_PROC[8]=rmodel.UCH[8].UCH_LEFT; }

UCH_VALUES[9]=PINE.5     ;  if (PINE.5     ==1) { UCH_VAL_PROC[9]=rmodel.UCH[9].UCH_RIGHT; 
} else { UCH_VAL_PROC[9]=rmodel.UCH[9].UCH_LEFT; }

if (flyTimerOn==0) {
if (E_eventStart==8) {

if (PINE.5     ==1) {
flyTimerOn=1;
OnCurrTimer=flyCurrTimer;
}     
}
else { 
if (CH_PPM[E_eventStart]>(rmodel.CHANNELS.CH_EPL[E_eventStart]+
(rmodel.CHANNELS.CH_EPR[E_eventStart]-
rmodel.CHANNELS.CH_EPL[E_eventStart])*20/100)) { 
flyTimerOn=1;
OnCurrTimer=flyCurrTimer;
}        
}
}

if (flyTimerOn==1) {
if ((E_eventStop<8) && (CH_PPM[E_eventStop]<(rmodel.CHANNELS.CH_EPL[E_eventStop]+
(rmodel.CHANNELS.CH_EPR[E_eventStop]-
rmodel.CHANNELS.CH_EPL[E_eventStop])*10/100)))
flyTimerOn=0;
}

UCH_VALUES[10]=PINE.0     ; if (PINE.0     ==1) { UCH_VAL_PROC[10]=rmodel.UCH[10].UCH_RIGHT; 
} else { UCH_VAL_PROC[10]=rmodel.UCH[10].UCH_LEFT; }

UCH_VALUES[11]=PINE.1     ;  if (PINE.1     ==1) { UCH_VAL_PROC[11]=rmodel.UCH[11].UCH_RIGHT; 
} else { UCH_VAL_PROC[11]=rmodel.UCH[11].UCH_LEFT; }

UCH_VALUES[12]=PINE.2     ;  if (PINE.2     ==1) { UCH_VAL_PROC[12]=rmodel.UCH[12].UCH_RIGHT; 
} else { UCH_VAL_PROC[12]=rmodel.UCH[12].UCH_LEFT; }

UCH_VALUES[13]=((*(unsigned char *) 0x63) & 1) ;  if (((*(unsigned char *) 0x63) & 1) ==1) { UCH_VAL_PROC[13]=rmodel.UCH[13].UCH_RIGHT; 
} else { UCH_VAL_PROC[13]=rmodel.UCH[13].UCH_LEFT; }
}

unsigned char ready_key=0; 
unsigned char rkey=0; 
unsigned char presstime=0; 
unsigned int keyhold=0; 
unsigned char keyhold_t=0; 
unsigned char keyhold_wait=0; 

unsigned char BEEP; 

unsigned char get_mnu_keys(void) {
unsigned char t;

t=ready_key & 0xFE;  

if (t!=254) {
ready_key=254; 
BEEP=key_repress_time-2;
if (SOUND_ON==1) PORTE.3    =1;  
PORTB.7    =1;
LightOn=500; 

}
return t; 
}

void resetKeyReader() {
ready_key=0; 
rkey=0; 
presstime=0; 
keyhold=0; 
keyhold_t=0; 
}

unsigned char trimkey; 
unsigned char trimhold; 
unsigned char readytrim; 

unsigned char get_trim_key() {
unsigned char t;
t=readytrim;
if (t!=255) {
readytrim=255; 
BEEP=trim_press_time-3;
if (SOUND_ON==1) PORTE.3    =1;  
PORTB.7    =1;
LightOn=1500; 
}
return t; 
}

void read_trim() {
unsigned char tempkey;

tempkey=PIND; 

if (tempkey!=255) {

if (trimkey==tempkey) { 
trimhold++; 
if (trimhold==trim_press_time) { 
readytrim=trimkey; 
trimhold=0;
} 
else { trimkey=tempkey; }
} 
else { trimkey=tempkey; trimhold=0; }
} 
else { trimkey=255; trimhold=0; }
}

void read_key() {

unsigned char tempkey;

tempkey=PINB | 128; 

if (tempkey!=254) { 

if (keyhold_wait==0) {     

if (tempkey==rkey) { 

presstime++; 

if (presstime==key_press_time) { 
ready_key=tempkey;            

if ((tempkey==250)||(tempkey==252)) { 
keyhold_wait=1;
}
}

if (presstime==(key_press_time+key_repress_time)) { 

ready_key=tempkey; 

if (keyhold_t<9) keyhold_t++; else keyhold=1; 
presstime=key_press_time; 
}    
}     
else { 
rkey=tempkey; 
presstime=0;  
keyhold=0;
keyhold_t=0;  
}
} 
} 
else {  
rkey=254;      
presstime=0; 
keyhold_wait=0;  
}
}

unsigned char impPhase; 
unsigned long battAvg;  
unsigned char avgCount; 

interrupt [13] void timer1_compa_isr(void)  { 
unsigned char i, k , n, m; 
signed char   j;
unsigned int chl, bt1;
unsigned long int kk,ev,x1,x2,x3,y1,y2;

if (ppmStop==2) {
OCR1A=2000;  
return;
}

if (PPM_CUR_CH_NUM<rmodel.CHANNELS.PPM_CH_COUNT) {

if (impPhase==0) { 

OCR1A=600;  
if (E_var3==0) PORTB.0=1;  else  PORTB.0=0;
impPhase=1;

} 

else { 
OCR1A=2*CH_PPM[PPM_CUR_CH_NUM]-600;  

if (E_var3==0) PORTB.0=0;  else  PORTB.0=1;
impPhase=0;

PPM_PAUSE=PPM_PAUSE+CH_PPM[PPM_CUR_CH_NUM]; 

if ((PPM_CUR_CH_NUM+1)==rmodel.CHANNELS.PPM_CH_COUNT)
MixerCalc( mixtochan * PPM_CUR_CH_NUM, mixtochan * PPM_CUR_CH_NUM + mixtochan + mixtochanlast);           
else MixerCalc( mixtochan * PPM_CUR_CH_NUM, mixtochan * PPM_CUR_CH_NUM + mixtochan);

PPM_CUR_CH_NUM++;
}
} 
else {
OCR1A=2*(22500-PPM_PAUSE); 

if (E_var3==0) {
PORTB.0=1;
delay_us(300);
PORTB.0=0;    
} 
else {
PORTB.0=0;
delay_us(300);
PORTB.0=1;
}

PPM_PAUSE=0;     
PPM_CUR_CH_NUM=0; 

for (i=0;i<rmodel.CHANNELS.LCH_COUNT;i++) { 

if (LCH_LEN[i]<(32000+rmodel.CHANNELS.CH_EPL[i])) LCH_LEN[i]=32000+rmodel.CHANNELS.CH_EPL[i]; 
if (LCH_LEN[i]>(32000+rmodel.CHANNELS.CH_EPR[i])) LCH_LEN[i]=32000+rmodel.CHANNELS.CH_EPR[i];         
LCH_LEN[i]=LCH_LEN[i]-32000;

if (LCH_LEN[i]<OLD_LCH_LEN[i]) {

if (rmodel.CHANNELS.LCHDELDN[i]!=0) { 
if ((OLD_LCH_LEN[i]-LCH_LEN[i])>(256-rmodel.CHANNELS.LCHDELDN[i])) 
LCH_LEN[i]=OLD_LCH_LEN[i]-(256-rmodel.CHANNELS.LCHDELDN[i]); 
}
} 

else {

if (rmodel.CHANNELS.LCHDELUP[i]!=0) { 
if ((LCH_LEN[i]-OLD_LCH_LEN[i])>(256-rmodel.CHANNELS.LCHDELUP[i])) 
LCH_LEN[i]=OLD_LCH_LEN[i]+(256-rmodel.CHANNELS.LCHDELUP[i]); 
}
}

if (rmodel.FMODE[FMODE_NUM].LCH_CURVE[i].active!=0) { 
k=0;
while (k<8) {

x1=CURVE_POINT[i][k][0];            
x2=CURVE_POINT[i][(unsigned char)(k+1)][0];
y1=CURVE_POINT[i][k][1];
y2=CURVE_POINT[i][(unsigned char)(k+1)][1];

if ( (x1<=LCH_LEN[i]) && (LCH_LEN[i]<=x2) ) break; 
else k++;
}

if ( (k>=0) && (k<8) ) {

outx1=x1;
outx2=x2;
outy1=y1;
outy2=y2;

x3=LCH_LEN[i];
outx3=x3;

if (((x3-x1)==0) || ((x2-x3)==0)) {
if (x1==x3) LCH_LEN[i]=y1; else LCH_LEN[i]=y2;             
} 
else {               
kk=(x3-x1)*1000/(x2-x3); 
outkk=kk;                   
ev=(y1*1000) / (1000 + kk) + (kk*y2) / (1000 + kk);
outy3=ev;            
if (ev<700) ev=2000+ev;
LCH_LEN[i]=(unsigned int) ev;
}
} else  LCH_LEN[i]=800+k;
}

OLD_LCH_LEN[i]=LCH_LEN[i];         
}

for (i=0;i<rmodel.CHANNELS.PPM_CH_COUNT;i++) {

switch (rmodel.CHANNELS.FILTER[i].FILTER_TYPE) {

case 0: { 
CH_PPM[i]=LCH_LEN[i]; 
break;
}

case 1: { 
if (UCH_VALUES[rmodel.CHANNELS.FILTER[i].VAL1%256]==0) { 
CH_PPM[i]=LCH_LEN[i]; 
}

else { 

j=rmodel.CHANNELS.FILTER[i].VAL1/256; 
if (j<0) { 
bt1=-j; 
chl=rmodel.FMODE[FMODE_NUM].LCH_MIDLE[i] - 
((rmodel.FMODE[FMODE_NUM].LCH_MIDLE[i]-rmodel.CHANNELS.CH_EPL[i])/100) * bt1;

} else {  
bt1=j;
chl=rmodel.FMODE[FMODE_NUM].LCH_MIDLE[i] +  
((rmodel.CHANNELS.CH_EPR[i]-rmodel.FMODE[FMODE_NUM].LCH_MIDLE[i])/100) * bt1;

}
CH_PPM[i]=chl; 
}
break;
}

case 2: { 

if (mch[i]==0) { 
CH_PPM[i]=2150; mch[i]=1; 
} 

else {       

j=16; 
chl=rmodel.CHANNELS.FILTER[i].VAL1; 

m=mch[i];   

for (k=0; k<m; k++) { 
n=chl%2;                             
chl=chl/2;              
if (j!=0) j--;   
while ((j!=0) && (n==0)) { 
n=chl%2;
chl=chl/2; 
j--; 
}                                                                                                                                                            
}
CH_PPM[i]=LCH_LEN[15-j]; 

mch[i]++;
if (mch[i]==5) mch[i]=0;                          

}

break;
}

}
}

for (i=0;i<rmodel.CHANNELS.LCH_COUNT;i++) {
LCH_LEN[i]=32000+rmodel.FMODE[FMODE_NUM].LCH_MIDLE[i];
}

read_UCH_values(); 

BLINK_TIMER++;
if (BLINK_TIMER==25) BLINK=1;                      
if (BLINK_TIMER==50) { 
BLINK=0; 
BLINK_TIMER=0;  

if (flyCurrTimer==0) { 

flyTimerOn=0; 

if (TimerEnd==0) { 

PORTB.7    =1;
LightOn=1500; 
}      

if ((TimerEnd==0) && (SOUND_ON==1)) { 
TimerEnd=1; 
TimerEndBeepCounter=2; 
} 
else { 
if (TimerEnd==2) {

BEEP=50; 
PORTE.3    =1;
} 
if (TimerEnd==4) { BEEP=0; PORTE.3    =0;  } 
if (TimerEnd==5) {
if (TimerEndBeepCounter!=0) {
TimerEnd=1;
}  
else { 
TimerEnd=4; 
TimerEndBeepCounter=1; 
} 
TimerEndBeepCounter--;                
}
TimerEnd++;                              
}            
} 

if ((flyTimerOn==1) && (flyCurrTimer>0)) flyCurrTimer--;

if ((flyCurrTimer%60==0) && (flyTimerOn==1)) { 
if ((E_beep1min==1) && (SOUND_ON==1)) { BEEP=4; PORTE.3    =1; }

PORTB.7    =1;
LightOn=1500; 
} 

if ((flyCurrTimer<60) && (((flyCurrTimer%60)%2)==0) && (flyTimerOn==1)) { 
if ((E_beep2sec==1) && (SOUND_ON==1)) { BEEP=3; PORTE.3    =1; }

PORTB.7    =1;
LightOn=1500; 
}

}         

if (BEEP==1) PORTE.3    =0;
if (BEEP>0) BEEP--;      

if (LightOn==1) PORTB.7    =0;
if (LightOn>0) LightOn--;

battAvg=battAvg+read_adc(7);        
avgCount++; 
if (avgCount==25) {
avgCount=0;
batt=(unsigned int)((battAvg/25) - 127 +E_var11);
battAvg=0;

if (batt<battMin) {
PORTE.3    =1;  

PORTB.7    =1;
LightOn=1500; 
}            
}

read_key();

read_trim();

if (ppmStop==1) ppmStop=2; 

}

}

void main(void) {
unsigned char i; 

PORTA=0x00;
DDRA=0xFF;

PORTB=0xFF;
DDRB=0x81;

PORTC=0x01; 
DDRC=0xFE;  

PORTD=0xFF;
DDRD=0x00;

PORTE=0xF7;
DDRE=0x08;

(*(unsigned char *) 0x62)=0x00;
(*(unsigned char *) 0x61)=0x00;

(*(unsigned char *) 0x65)=0x0F;
(*(unsigned char *) 0x64)=0x10;

TCCR1A=0x00;
TCCR1B=0x0A;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;
(*(unsigned char *) 0x79)=0x00;
(*(unsigned char *) 0x78)=0x00;

(*(unsigned char *) 0x8b)=0x00;
(*(unsigned char *) 0x8a)=0x00;
(*(unsigned char *) 0x89)=0x00;
(*(unsigned char *) 0x88)=0x00;
(*(unsigned char *) 0x81)=0x00;
(*(unsigned char *) 0x80)=0x00;
(*(unsigned char *) 0x87)=0x00;
(*(unsigned char *) 0x86)=0x00;
(*(unsigned char *) 0x85)=0x00;
(*(unsigned char *) 0x84)=0x00;
(*(unsigned char *) 0x83)=0x00;
(*(unsigned char *) 0x82)=0x00;

(*(unsigned char *) 0x6a)=0x00; 
EICRB=0x00;
EIMSK=0x00;

TIMSK=0x10;
(*(unsigned char *) 0x7d)=0x00;

ACSR=0x80;
SFIOR=0x00;

ADMUX=0x40  & 0xff;
ADCSRA=0x87;

BLINK_TIMER=0; 
BLINK=0;       

BEEP=0; 
PORTE.3    =0;

LightOn=100; 

printMess=0; 
messStr1=" ";
messStr2=" ";
messStr3=" ";
messStr4=" ";
messStr5=" ";

SOUND_ON=E_SOUND_ON;

if (E_key_press_time==255) { 

E_key_press_time=10;
E_key_repress_time=7;
E_CurModelNum=255;
E_ClusterSize=32;
E_battMin=700; 
E_eventStart=8; 
E_eventStop=8;  
E_beep1min=0; 
E_beep2sec=0; 
E_nulTrimBeep=0; 

PPM_capture=0; 
E_var3=0;  
E_var4=32; 

E_trim_press_time=6; 

E_var11=127;
E_var12=2; 

E_vari2=0;
E_vari3=255;
E_vari4=0;
E_vari5=0;
E_vari6=0;
E_vari7=0;
E_vari8=0;
E_vari9=0;
E_vari10=0;

notUsed=0;
}

if ((E_var4<20) || (E_var4>45))  E_var4=32; 
if (E_var11==0)   E_var11=127; 
if (E_var12==0)   E_var12=2;   

mess_posx=0; 
mess_char=0;
mess_pause=0;  
battMin=E_battMin; 

key_press_time=E_key_press_time;
key_repress_time=E_key_repress_time;   
trim_press_time=E_trim_press_time; 

ClusterSize=E_ClusterSize; 

FILE_RESET(); 

flyTimerOn=0; 
flyCurrTimer=rmodel.MODEL_FLYTIMER; 
TimerEndBeepCounter=0;
TimerEnd=0;

if (E_CurModelNum<16) {
OpenModel(E_CurModelNum);  
}  

ModelChange=0; 

for (i=0; i<7; i++) { 

UCHmin[i]=E_UCHmin[i];
UCHmid[i]=E_UCHmid[i];
UCHmax[i]=E_UCHmax[i];
}

resetMenu(); 

FMODE_NUM=0; 

impPhase=0; 
PPM_CUR_CH_NUM=0;   
PPM_PAUSE=0;        
for (i=0; i<8; i++) {
CH_PPM[i]=rmodel.FMODE[FMODE_NUM].LCH_MIDLE[i]; 
}

battAvg=0;        
avgCount=0; 

LCD_init(); 
LCD_setContrast(E_var4); 

ppmStop=0; 

#asm("sei") 

while (1) { 

i=get_trim_key();
if (E_var12==1) {   
switch (i) {
case 239 : { i=251;
break;
}

case 223 : { i=247;      
break;
}                  

case 251 : { i=239;
break;
}

case 247 : { i=223;      
break;
}                           
}
} else
if (E_var12==3) {    
switch (i) {
case 127 : { i=254;
break;
}

case 191 : { i=253;      
break;
}                  

case 254 : { i=127;
break;
}

case 253 : { i=191;      
break;
}                  

}
} else
if (E_var12==4) {    
switch (i) {
case 127 : { i=254;    
break;
}
case 254 : { i=127;   
break;
}

case 191 : { i=253;   
break;
}                  
case 253 : { i=191;   
break;

}                  
case 239 : { i=251;   
break;
}

case 223 : { i=247;      
break;
}                  

case 251 : { i=239;
break;
}

case 247 : { i=223;      
break;
}                  

}
}

switch (i) {
case 239 : { 
if (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[1]<120) { 
rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[1]=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[1]+
rmodel.FMODE[FMODE_NUM].TRIMSTEP; 
ModelChange=1;
}

if ( (E_nulTrimBeep==1) && (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[1]==0) ) { 
trim_press_time=E_trim_press_time * 3;
BEEP=trim_press_time-4;
} else trim_press_time=E_trim_press_time;

break;
}

case 223 : { 
if (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[1]>-120) { 
rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[1]=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[1]-
rmodel.FMODE[FMODE_NUM].TRIMSTEP; 
ModelChange=1;
}                             

if ( (E_nulTrimBeep==1) && (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[1]==0) ) { 
trim_press_time=E_trim_press_time * 3;
BEEP=trim_press_time-4;
} else trim_press_time=E_trim_press_time;
break;
}

case 254 : { 
if (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[0]<120) { 
rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[0]=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[0]+
rmodel.FMODE[FMODE_NUM].TRIMSTEP; 
ModelChange=1;
}   

if ( (E_nulTrimBeep==1) && (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[0]==0) ) { 
trim_press_time=E_trim_press_time * 3;
BEEP=trim_press_time-4;
} else trim_press_time=E_trim_press_time;

break;
}

case 253 : { 
if (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[0]>-120) { 
rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[0]=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[0]-
rmodel.FMODE[FMODE_NUM].TRIMSTEP; 
ModelChange=1;
}                             

if ( (E_nulTrimBeep==1) && (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[0]==0) ) { 
trim_press_time=E_trim_press_time * 3;
BEEP=trim_press_time-4;
} else trim_press_time=E_trim_press_time;

break;
}

case 251 : { 
if (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[2]<120) {
rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[2]=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[2]+
rmodel.FMODE[FMODE_NUM].TRIMSTEP; 
ModelChange=1;
}     

if ( (E_nulTrimBeep==1) && (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[2]==0) ) { 
trim_press_time=E_trim_press_time * 3;
BEEP=trim_press_time-4;
} else trim_press_time=E_trim_press_time;
break;
}

case 247 : { 
if (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[2]>-120) { 
rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[2]=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[2]-
rmodel.FMODE[FMODE_NUM].TRIMSTEP; 
ModelChange=1;
}     

if ( (E_nulTrimBeep==1) && (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[2]==0) ) { 
trim_press_time=E_trim_press_time * 3;
BEEP=trim_press_time-4;
} else trim_press_time=E_trim_press_time;
break;
}

case 127 : { 
if (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[3]<120) { 
rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[3]=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[3]+
rmodel.FMODE[FMODE_NUM].TRIMSTEP; 
ModelChange=1;
}     

if ( (E_nulTrimBeep==1) && (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[3]==0) ) { 
trim_press_time=E_trim_press_time * 3;
BEEP=trim_press_time-4;
} else trim_press_time=E_trim_press_time;
break;
}

case 191 : { 
if (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[3]>-120) {
rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[3]=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[3]-
rmodel.FMODE[FMODE_NUM].TRIMSTEP;
ModelChange=1;
}     

if ( (E_nulTrimBeep==1) && (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[3]==0) ) { 
trim_press_time=E_trim_press_time * 3;
BEEP=trim_press_time-4;
} else trim_press_time=E_trim_press_time;                    
break;
}

}

LCD_clear(); 

disp(); 

LCD_refresh(); 
}
}
