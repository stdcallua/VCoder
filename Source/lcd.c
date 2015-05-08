#include <mega64.h>
#include <delay.h>
#include <stdio.h>
#include "vcoder.h"

unsigned char buff[8][128]; // буфер экрана

/**
unsigned char LCD_Status(void) // получение статуса дисплея
{
    unsigned char tmp;
    PORTC &= 0xF5;    
    PORTC |= 0x30;
    DDRA = 0x00;
    tmp = PINA;
    PORTC &= 0xDF;
    PORTC |= 0x02;
    return tmp;
}
**/
void LCD_command(unsigned char command) // отправка команды на дисплей
{
//    while((LCD_Status() & 0x80));
     
    PORTC &= 0xE5;
    DDRA = 0xFF;
    PORTA = command;
    PORTC |= 0x20;
    PORTC &= 0xDF;
    PORTC |= 0x02;
}

void LCD_data(unsigned char data) // отправка данных на дисплей
{
//        while((LCD_Status() & 0x80));
        
    PORTC &= ~18;
    PORTC |= 8;
    DDRA = 0xFF;
    PORTA = data;
    PORTC |= 32;
    PORTC &= ~32;
    PORTC |= 2;
}

void LCD_refresh (void)  //------------------------------------- Обновление дисплея (отображение буффера)
{
unsigned char i,j;
for(i=0; i<8; i++)
  { LCD_command(0xB0  |  i);
	LCD_command(0x10);	
	LCD_command(0x04);
  for (j=0; j<128; j++) LCD_data(buff[i][j]);
   }
}

void LCD_clear (void) //------------------------------------------------------------------ очистка экрана
{
unsigned char x, y;
for (y=0; y<8; y++)    
  for (x=0; x<128; x++) buff[y][x]=0;   
}           

void LCD_init(void) //------------------------------------------------------------- инициализация дисплея
{
  PORTC &= 0x04;            //Посылка сброса
  delay_us(1);
  delay_us(1);              //   
  PORTC |= 0x04;            //  
  delay_us(1500);
  LCD_command(0xe2); //Initialize the internal functions
  LCD_command(0xae); //DON = 0: display OFF
  LCD_command(0xa1); //ADC = 1: reverse direction(SEG132->SEG1)
  LCD_command(0xA6); //REV = 0: non-reverse display
  LCD_command(0xA4); //EON = 0: normal display. non-entire
  LCD_command(0xA2); // Select LCD bias=0
  LCD_command(0xC0); //SHL = 0: normal direction (COM1->COM64)
  LCD_command(0x2F); //Control power circuit operation VC=VR=VF=1 
  LCD_command(0x25); //Select int resistance ratio R2 R1 R0 =5
  LCD_command(0x81); //Set reference voltage Mode
  LCD_command(0x22); // 24 SV5 SV4 SV3 SV2 SV1 SV0 = 0x18
  LCD_command(0xAF); //DON = 1: display ON
  LCD_clear();  
  LCD_refresh();  
}

void LCD_setContrast(unsigned char contr) {
    LCD_command(0x81); // установим контраст
    LCD_command(contr); // установим контраст

}

__flash const unsigned char font[] = { 

                           0x00,0x00,0x00,0x00,0x00, // 32  0x20    ' '
                           0x00,0x00,0x5e,0x00,0x00, // 33  0x21     !
                           0x00,0x08,0x06,0x08,0x06, // 34  0x22     "
                           0x28,0x7e,0x28,0x7e,0x28, // 35  0x23     #
                           0x04,0x2a,0x7e,0x2a,0x10, // 36  0x24     $
                           0x4c,0x2c,0x10,0x68,0x64, // 37  0x25     %
                           0x34,0x4a,0x56,0x20,0x50, // 38  0x26     _
                           0x00,0x00,0x00,0x08,0x06, // 39  0x27     '
                           0x00,0x00,0x18,0x24,0x42, // 40  0x28     (
                           0x00,0x00,0x42,0x24,0x18, // 41  0x29     )
                           0x14,0x08,0x3e,0x08,0x14, // 42  0x2a     *
                           0x08,0x08,0x3e,0x08,0x08, // 43  0x2b     +
                           0x00,0x00,0xb0,0x70,0x00, // 44  0x2c     ,
                           0x00,0x08,0x08,0x08,0x08, // 45  0x2d     -
                           0x00,0x00,0x60,0x60,0x00, // 46  0x2e     .
                           0x00,0x60,0x18,0x06,0x00, // 47  0x2f     /
                           0x00,0x3c,0x42,0x42,0x3c, // 48  0x30     0
                           0x00,0x00,0x44,0x7e,0x40, // 49  0x31     1
                           0x00,0x44,0x62,0x52,0x4c, // 50  0x32     2
                           0x00,0x42,0x4a,0x4a,0x34, // 51  0x33     3
                           0x00,0x18,0x14,0x7a,0x10, // 52  0x34     4
                           0x00,0x2e,0x4a,0x4a,0x32, // 53  0x35     5
                           0x00,0x3c,0x4a,0x4a,0x30, // 54  0x36     6
                           0x00,0x02,0x72,0x0a,0x06, // 55  0x37     7
                           0x00,0x34,0x4a,0x4a,0x34, // 56  0x38     8
                           0x00,0x0c,0x52,0x52,0x3c, // 57  0x39     0
                           0x00,0x00,0x6c,0x6c,0x00, // 58  0x3a     :
                           0x00,0x00,0xa8,0x68,0x00, // 59  0x3b     ;
                           0x00,0x00,0x08,0x14,0x22, // 60  0x3c     <
                           0x00,0x14,0x14,0x14,0x14, // 61  0x3d     =
                           0x00,0x00,0x22,0x14,0x08, // 62  0x3e     >
                           0x00,0x04,0x52,0x0a,0x04, // 63  0x3f     ?
                           0x3c,0x42,0x5a,0x5a,0x1c, // 64  0x40     @
                           0x00,0x7c,0x12,0x12,0x7c, // 65  0x41     A
                           0x00,0x7e,0x4a,0x4a,0x34, // 66  0x42     B
                           0x00,0x3c,0x42,0x42,0x24, // 67  0x43     C
                           0x00,0x7e,0x42,0x42,0x3c, // 68  0x44     D
                           0x00,0x7e,0x4a,0x4a,0x42, // 69  0x45     E
                           0x00,0x7e,0x0a,0x0a,0x02, // 70  0x46     F
                           0x00,0x3c,0x42,0x52,0x34, // 71  0x47     G
                           0x00,0x7e,0x10,0x10,0x7e, // 72  0x48     H
                           0x00,0x42,0x7e,0x42,0x00, // 73  0x49     I
                           0x00,0x20,0x40,0x40,0x3e, // 74  0x4a     J
                           0x00,0x7e,0x18,0x24,0x42, // 75  0x4b     K
                           0x00,0x7e,0x40,0x40,0x40, // 76  0x4c     L
                           0x7e,0x04,0x08,0x04,0x7e, // 77  0x4d     M
                           0x00,0x7e,0x08,0x10,0x7e, // 78  0x4e     N
                           0x00,0x3c,0x42,0x42,0x3c, // 79  0x4f     O
                           0x00,0x7e,0x12,0x12,0x0c, // 80  0x50     P
                           0x00,0x3c,0x42,0x22,0x5c, // 81  0x51     Q
                           0x00,0x7e,0x12,0x32,0x4c, // 82  0x52     R
                           0x00,0x24,0x4a,0x52,0x24, // 83  0x53     S
                           0x02,0x02,0x7e,0x02,0x02, // 84  0x54     T
                           0x00,0x3e,0x40,0x40,0x3e, // 85  0x55     U
                           0x1e,0x20,0x40,0x20,0x1e, // 86  0x56     V
                           0x7e,0x20,0x18,0x20,0x7e, // 87  0x57     W
                           0x42,0x24,0x18,0x24,0x42, // 88  0x58     X
                           0x02,0x04,0x78,0x04,0x02, // 89  0x59     Y
                           0x00,0x62,0x52,0x4a,0x46, // 90  0x5a     Z
                           0x00,0x7e,0x42,0x42,0x00, // 91  0x5b     [
                           0x00,0x06,0x18,0x60,0x00, // 92  0x5c     \
                           0x00,0x42,0x42,0x7e,0x00, // 93  0x5d     ]
                           0x08,0x04,0x02,0x04,0x08, // 94  0x5e     ^
                           0x40,0x40,0x40,0x40,0x40, // 95  0x5f     -
                           0x00,0x00,0x06,0x08,0x00, // 96  0x60     '
                           0x00,0x30,0x48,0x48,0x78, // 97  0x61     a
                           0x00,0x7e,0x48,0x48,0x30, // 98  0x62     b
                           0x00,0x30,0x48,0x48,0x48, // 99  0x63     c
                           0x00,0x30,0x48,0x48,0x7e, // 100 0x64     d
                           0x00,0x78,0x48,0x58,0x58, // 101 0x65     e
                           0x00,0x08,0xfe,0x0a,0x08, // 102 0x66     f
                           0x00,0x10,0xa8,0xa8,0x78, // 103 0x67     g
                           0x00,0x7e,0x08,0x08,0x70, // 104 0x68     h
                           0x00,0x48,0x7a,0x40,0x00, // 105 0x69     i
                           0x00,0x80,0x88,0xfa,0x00, // 106 0x6a     j
                           0x00,0x7e,0x10,0x28,0x40, // 107 0x6b     k
                           0x00,0x42,0x7e,0x40,0x00, // 108 0x6c     l
                           0x78,0x08,0x70,0x08,0x70, // 109 0x6d     m
                           0x00,0x78,0x08,0x08,0x70, // 110 0x6e     n
                           0x00,0x30,0x48,0x48,0x30, // 111 0x6f     o
                           0x00,0xf8,0x28,0x28,0x10, // 112 0x70     p
                           0x00,0x10,0x28,0x28,0xf8, // 113 0x71     q
                           0x00,0x78,0x10,0x08,0x08, // 114 0x72     r
                           0x00,0x50,0x58,0x68,0x28, // 115 0x73     s
                           0x00,0x08,0x7e,0x48,0x48, // 116 0x74     t
                           0x00,0x38,0x40,0x40,0x78, // 117 0x75     u
                           0x18,0x20,0x40,0x20,0x18, // 118 0x76     v
                           0x38,0x40,0x30,0x40,0x38, // 119 0x77     w
                           0x00,0x48,0x30,0x30,0x48, // 120 0x78     x
                           0x00,0x98,0xa0,0xa0,0x78, // 121 0x79     y
                           0x00,0x48,0x68,0x58,0x48, // 122 0x7a     z
                           0x00,0x10,0x7c,0x44,0x00, // 123 0x7b     {
                           0x00,0x00,0x7e,0x00,0x00, // 124 0x7c     |
                           0x00,0x00,0x44,0x7c,0x10, // 125 0x7d     }
                           0x10,0x10,0x44,0x38,0x10, // 126 0x7e     ~
                           0x10,0x38,0x44,0x10,0x10  // 127 0x7f     del

};

unsigned char LCD_Y;
unsigned char LCD_X;

void LCD_setxy(char x,unsigned char y) //------------------------------------ установка координат курсора
{
LCD_X=x+2;
LCD_Y=y;
}


void LCD_char(unsigned char ch, unsigned char mode) {   //--------------------------------- Вывод символа
  unsigned char x;
  if ((ch<127) || (ch>32)) { 
    for (x=0; x<5; x++) {
      if (mode==2) mode=BLINK; // если нужно отображать в режиме мерцания - то берем значение из BLINK
      switch (mode) {
        case 0: { buff[LCD_Y][LCD_X]=font[ (unsigned int)(ch-32)*5+x ];  break; }
        case 1: { buff[LCD_Y][LCD_X]=255-font[ (unsigned int)(ch-32)*5+x ]; break; }
      }
      LCD_X++; 
    }
  }
}


void LCD_out(unsigned char ch) { // ------------------------------------- прямой вывод байта в видеобуфер
   buff[LCD_Y][LCD_X]=ch;
   LCD_X++;
}
/**
void  LCD_wrs (unsigned char*str,unsigned char color) //----------------------------- Вывод строки из RAM
{
  while(*str!='\0') LCD_char(*str++, color);
}
**/

void LCD_wrsf (flash unsigned char*str,unsigned char color) //--------------------- Вывод строки из Flash
{
  while(*str!='\0') { LCD_char(*str, color);
    str++; } 
}

// ------------------------------------------------------------------------------ Вывод десятичного числа
void LCD_dec(unsigned int val, unsigned char len, unsigned char mode) {
  unsigned char i;
  unsigned char cx=0;
  unsigned char savePOS_X;
  
  savePOS_X=LCD_X; // сохраним значение координаты по Х 
  cx+=(len-1)*5;
  for (i=0; i<len; i++) {
    LCD_X=cx+savePOS_X; LCD_char(val%10+'0',mode);
    cx-=5;
    val/=10;
  }
  LCD_X=savePOS_X+len*5;  
}

// печать числа вертикально !
void LCD_V_dec(unsigned int val, unsigned char len, unsigned char mode) {
  unsigned char i;
  unsigned char savePOS_X, savePOS_Y;
  
  savePOS_X=LCD_X; // сохраним значение координаты по Х
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


// ---------------------------------------------------------------------------------------- Вывод пиксела
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

// Печать большого символа (Увеличенного в 2 раза), координаты с точностью до пиксела
void LCD_big_char(unsigned char x, unsigned char y, unsigned char ch) {
unsigned char px,py,i;


   for (px=0;px<5;px++) { // перебираем строки символов

         i=font[ (unsigned int)(ch-32)*5+px ]; // берем байт символа

      for (py=0; py<8;py++) { // перебираем столбец
         if ((i%2)==1) { 
            LCD_pixel(x+px*2,y+py*2,1);   LCD_pixel(x+px*2+1,y+py*2,1);
            LCD_pixel(x+px*2,y+py*2+1,1); LCD_pixel(x+px*2+1,y+py*2+1,1);
         }
         i=i/2;
      }
   }
}

// печать числа большими символами горизонтально, координаты в пикселах
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

// Печать большого символа (Увеличенного по высоте в 3 раза), координаты с точностью до пиксела
void LCD_big3_char(unsigned char x, unsigned char y, unsigned char ch) {
unsigned char px,py,i;
unsigned char ppx, ppy;

   for (px=0;px<5;px++) { // перебираем строки символов

         i=font[ (unsigned int)(ch-32)*5+px ]; // берем байт символа

   ppx=px*3; 
      for (py=0; py<8;py++) { // перебираем столбец
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

// печать числа большими символами горизонтально, координаты в пикселах
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

// точечная (пунктирная линия)
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

// новая процедура рисования линии
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

void LCD_rectangle(char x1,char y1,char x2,char y2,char mode) { //------------------- Выводим прямоугольник
   LCD_line(x1,y1, x2,y1, mode);
   LCD_line(x1,y2, x2,y2, mode);
   LCD_line(x1,y1, x1,y2, mode);
   LCD_line(x2,y1, x2,y2, mode);
}