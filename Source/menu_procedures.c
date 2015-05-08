#include "vcoder.h"

/**
                            ФАЙЛ ПРОЦЕДУР ВЫЗЫВАЕМЫХ ИЗ МЕНЮ

  переменные модуля mn_display_new:
  menu_exe: при 0 - вызов процедур не осуществляется, при 1 - осуществляется вызов процедуры указанной в 
            переменной menu_proc... вызов процедуры циклический непрерывный даже в случае ее завершения,
            пока menu_exe=1. При вызове экран очищен, после вызова видеобуфер будет выведен на экран
  
  переменные модуля vcoder - смотри файл vcoder.h
**/

// глобальные переменные которые могут использовать процедуры по своему усмотрению пока они активны
unsigned char temp1, temp2, temp3; 
unsigned int temp4;

/**
                     Р Е Д А К Т И Р О В А Н И Е    Ф И Л Ь Т Р А   К А Н А Л А
       
                 (процедура выполняется при выборе пункта EDIT - CHANNELS - FILTERS)       
**/

__flash const char CHNUM_table[] = { // номера каналов
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
unsigned char chnum; //номер канала для фильтра выключатель
signed char   valsc; // значение со знаком 


   //проверяем процедуру на первый запуск
   if (temp1==0) { // у нас первый запуск, инициализация
     temp2=0; // номер параметра для редактирования  
     temp3=0; // курсор каналов для фильтра 2 (Мультиплексирование) 
     temp1=1;
     temp4=1; // бит маски в 15м разряде
   }
    
   // Печатаем заголовок
   LCD_setxy(0,0); LCD_wrsf("       FILTER EDIT       ",1);

   filt_num=numitem_cur-36; // фильтры описаны начиная с 36 пункта меню.. вычтя 36 из номера пункта меню мы
                            // получим номер фильтра

   ftype=rmodel.CHANNELS.FILTER[filt_num].FILTER_TYPE; // берем тип фильтра 
   fval=rmodel.CHANNELS.FILTER[filt_num].VAL1; // берем доп. параметр фильтра
   
   //выводим номер канала для редактирования
   LCD_setxy(0,2); LCD_wrsf("CHANNEL: ",0); LCD_char(CHNUM_table[filt_num],0);

   if (temp2==0) mode=2; else mode=0;

   // печатаем тип фильтра из словаря
   LCD_setxy(0,3); LCD_wrsf("FILTER TYPE: ",0); LCD_wrsf(CHANNEL_FILTER_TYPE[ftype], mode); 

   switch (ftype) { // в зависимости от типа фильтра выводим параметры настройки
      case 1: { // фильтр "выключатель"
         
                // выводим название выключателя
                if (temp2==1) mode=2; else mode=0;
                chnum=fval%256;
                valsc=fval/256; // значение которое нужно вывести в % от -125 до +125        
                LCD_setxy(0,4); LCD_wrsf("SWITCH: ",0); LCD_wrsf(UCH_Names[chnum], mode);
         
                // выводим значение которое нужно вывести при включенном выключателе
                if (temp2==2) mode=2; else mode=0;
                LCD_setxy(0,5); LCD_wrsf("VALUE: ",0); 
                if (valsc<0) { LCD_char('-',mode); valsc=-valsc; } else LCD_char('+',mode); 
                LCD_dec(valsc, 3, mode); LCD_char('%',mode);
                valsc=fval/256;
                break;
      }
      
      case 2: { // фильтр "Мультиплексор"
               // покажем выбранные каналы
               LCD_setxy(0,4); LCD_wrsf("CHANNELS: [ . . . . ]",0);
               LCD_setxy(60,4);
               chcount=0;
               for (x=0;x<16;x++) {
                  if ((fval%2)==1) { LCD_char(CHNUM_table[x], 1); LCD_char(' ',0); chcount++; }
                  fval=fval/2;
               }
            
               // выводим номера каналов
               
               for (y=0; y<2; y++) {
                  LCD_setxy(40,6+y);
                  for (x=0;x<8;x++) {
                     if (((y*8+x)==temp3)&&(temp2==1)) mode=2; // на канале стоит курсор 
                        else mode=0;  // канал не выбран                                 
                     LCD_char(CHNUM_table[y*8+x], mode); // печатаем номер канала                    
                     LCD_X++; LCD_X++;
                  }
               }
               break;
      }   
   }

   mode=get_mnu_keys(); // прочитаем нажатые клавиши навигации по меню
   switch (mode) { // выбираем нажатые клавиши

     case 238: { // нажата клавиша UP (вверх)
                  if (temp2>0) { temp2--; }
                  break; } 

     case 246: {  // нажата клавиша DN (вниз)
                  switch (ftype) { // в зависимости от типа фильтра - количество настраиваемых параметров  
                      case 1: { // тип 1: выключатель, 3 параметра
                                if (temp2<2) { temp2++;  }
                                break;
                      }
                      
                      case 2: { // тип 2: Мультиплексор каналов
                                if (temp2<1) temp2++;
                                break;
                      }          
                  }
                  break; 
     }
                                 
     case 250: {  // нажата клавиша EXIT (возврат в вышестоящее меню)
                  
                  if ((ftype==2) && (chcount<4)) { // не заполнены все каналы
                     rmodel.CHANNELS.FILTER[filt_num].VAL1=0;
                     rmodel.CHANNELS.FILTER[filt_num].FILTER_TYPE=0;
                  } 
                  temp2=0; // обнуляем временные переменные 
                  temp3=0; 
                  temp1=0;
                  temp4=0;
                  resetKeyReader(); // сброс клавиатуры
                  menu_exe=0;
                  break; }
               
     case 252: {  // нажата клавиша MENU/ENT
                  ModelChange=1;
                  resetKeyReader(); // сброс клавиатуры
                  if (temp2>0)                                             
                  switch (ftype) {
                     case 1: { // фильтр выключатель
                              
                               break;
                     }        

                     case 2: { // фильтр мультиплексор
                                  x=rmodel.CHANNELS.FILTER[filt_num].VAL1 & temp4;
                                  if (x>0) rmodel.CHANNELS.FILTER[filt_num].VAL1=rmodel.CHANNELS.FILTER[filt_num].VAL1-temp4;
                                    else if (chcount<4) rmodel.CHANNELS.FILTER[filt_num].VAL1=rmodel.CHANNELS.FILTER[filt_num].VAL1+temp4; 
                               break;
                     }        

                  }
                  break; 
     } 

     case 222: {  // нажата клавиша '-' (двигаемся вправо)
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
                       case 1: { // фильтр - выключатель                                 
                                 if (temp2==1) { // увеличиваем номер UCH 
                                    if (chnum<13) { chnum++;
                                      rmodel.CHANNELS.FILTER[filt_num].VAL1=valsc*256+chnum;
                                    } 
                                 }
                                 if (temp2==2) { // увеличиваем процентное значение 
                                    if (valsc<125) { valsc++;
                                      rmodel.CHANNELS.FILTER[filt_num].VAL1=valsc*256+chnum;
                                    } 
                                 }
                                 
                                 break;
                       }

                       case 2: { // фильтр - мультиплексор
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

     case 190: { //нажата клавиша   '+' (двигаемся влево)
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
                         case 1: { // фильтр - выключатель
                                 if (temp2==1) { // уменьшаем номер UCH 
                                    if (chnum>7) { chnum--;
                                      rmodel.CHANNELS.FILTER[filt_num].VAL1=valsc*256+chnum;
                                    } 
                                 }

                                 if (temp2==2) { // уменьшаем процентное значение 
                                    if (valsc>-125) { valsc--; 
                                      rmodel.CHANNELS.FILTER[filt_num].VAL1=valsc*256+chnum;
                                    } 
                                 }
                                 
                                 break;
                         }

                         case 2: { // фильтр - мультиплексор
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
/**
                   Р Е Д А К Т И Р О В А Н И Е    И М Е Н И   М О Д Е Л И
       
                    (процедура выполняется при выборе пункта EDIT - NAME)       
**/
__flash const char Name_table[] = { // символы используемые при наборе имени модели
        ' ','_','-','+','A','B','C','D','E','F',
        'G','H','I','J','K','L','M','N','O','P',
        'Q','R','S','T','U','V','W','X','Y','Z',
        '0','1','2','3','4','5','6','7','8','9'       
                                  };

void menu_EDIT_MODEL_NAME() {
unsigned int i,j; // временные переменные циклов
unsigned char mode;

   //проверяем процедуру на первый запуск
   if (temp1==0) { // у нас первый запуск, инициализация
     temp2=0; // позиция в имени модели 
     temp3=0; // позиция в наборе символов
     temp1=1;
   }
 
   // Печатаем заголовок
   LCD_setxy(0,0); LCD_wrsf("     EDIT MODEL NAME     ",1);

   LCD_setxy(10,2); LCD_wrsf("NAME: [", 0);

   for (i=0;i<8;i++) { // печатаем имя с подсветкой буквы для редактирования
      if (i==temp2) { mode=2; } else { mode=0; }
      LCD_char(rmodel.MODEL_NAME[i], mode);
   }
   LCD_char(']', 0); 

   for (i=0;i<4;i++) { // цикл строк
      LCD_setxy(29,i+4);
      for (j=0;j<10;j++) { // цикл позиции
         if (temp3==i*10+j) mode=1; else mode=0;
         LCD_char(Name_table[i*10+j], mode);
         LCD_X++; 
         LCD_X++;
      }
   } 

   mode=get_mnu_keys(); // прочитаем нажатые клавиши навигации по меню
   switch (mode) { // выбираем нажатые клавиши

     case 238: { // нажата клавиша UP (вверх)
                  if (temp2>0) temp2--; else temp2=7;
                  break; } 

     case 246: {  // нажата клавиша DN (вниз)
                  if (temp2<7) temp2++; else temp2=0;
                  break; } 
                                 
     case 250: {  // нажата клавиша EXIT (возврат в вышестоящее меню) 
                  temp2=0; // обнуляем временные переменные 
                  temp3=0; 
                  temp1=0;
                  resetKeyReader(); // сброс клавиатуры
                  menu_exe=0;
                  break; }
               
     case 252: {  // нажата клавиша MENU/ENT (переход в нижестоящее меню/вызов процедуры)                                            
                  rmodel.MODEL_NAME[temp2]=Name_table[temp3]; // сохраняем выбранный символ
                  if (temp2<7) temp2++; else temp2=0; // двигаем курсор в имени модели
                  ModelChange=1;
                  resetKeyReader(); // сброс клавиатуры                 
                  break; } 

     case 222: {  // нажата клавиша '-' (двигаемся вправо)
                  if (temp3<39) temp3++; else temp3=0;
                  break; }

     case 190: { //нажата клавиша   '+' (двигаемся влево)
                  if (temp3>0) temp3--; else temp3=39;
                  break; }
   }
}

/**
                П Р О С М О Т Р   Р Е З У Л Ь Т А Т О В   К А Л И Б Р О В К И
                
        (процедура выполняется при выборе пункта SYSTEM - CALIBRATION - CALIBRATION INFO
**/
void menu_SYSTEM_CALIBRATION_INFO() {
unsigned int y; // переменные циклов
  LCD_setxy(0,0);
  LCD_wrsf("     CALIBRATION INFO    ", 1);
  
  for (y=0;y<7;y++) {

    LCD_setxy(0,y+1);
    LCD_wrsf(UCH_Names[y],0);   // Печатаем имя канала
    LCD_char(' ',0); 
    LCD_dec(UCHmin[y],4,0);     // печатаем минимальное значение канала
    LCD_char(' ',0); 
    LCD_dec(UCHmid[y],4,0);     // печатаем среднее значение канала
    LCD_char(' ',0); 
    LCD_dec(UCHmax[y],4,0);     // печатаем максимальное значение канала

  }

  y=get_mnu_keys();
  switch (y) {
     case 250 : { resetKeyReader(); // сброс клавиатуры
                   menu_exe=0; }
  }
  
}

/**
                   К А Л И Б Р О В К А   А Н А Л О Г О В Ы Х   К А Н А Л О В
                   
         (процедура выполняемая при выборе пункта SYSTEM - CALIBRATION - NEW CALIBRATION)                   
**/
unsigned char system_calibration_part;
void menu_SYSTEM_NEW_CALIBRATION() { 
unsigned char i, j, k; // временные переменные циклов
unsigned char ok; // количество каналов в середине 
unsigned int v, v1, v2;

  LCD_setxy(0,0); LCD_wrsf("       CALIBRATION       ",1);   LCD_line(0, 10, 127, 10, 1);
 
  if (system_calibration_part==0) { //если первый запуск..
    // устанавливаем первоначальные значения максимума и минимума каналов
    for (i=0; i<7; i++) { UCHmin[i]=UCH_VALUES[i]; UCHmax[i]=UCH_VALUES[i]; } 
    system_calibration_part=1; } // ставим признак что старт уже был     
  
  if (system_calibration_part==1) { // получение значений каналов
     ok=0;
     for (i=0; i<7; i++) { // смотрим по каналам новые значения максимумов-минимумов и запоминаем их
       if (UCHmin[i]>UCH_VALUES[i]) UCHmin[i]=UCH_VALUES[i]; 
       if (UCHmax[i]<UCH_VALUES[i]) UCHmax[i]=UCH_VALUES[i]; 
       LCD_rectangle(1+i*17, 12, 10+i*17, 42,  1);  // рисуем шкалу
       LCD_setxy(3+i*17,6);     LCD_char(i+'0', 1); // подписываем номер канала
       v=UCH_VALUES[i]-UCHmin[i];       v*=28;      v/=(UCHmax[i]-UCHmin[i]);   k=13+v;
       if (k<43)  { LCD_line(1+i*17, k, 10+i*17, k, 1); } // рисуем индикатор 
     
       // подсвечиваем индикатор при среднем положении канала
       v1=(UCHmax[i]-UCHmin[i])/2;    v2=UCH_VALUES[i]-UCHmin[i];
       if ((v2<(v1*107/100)) && (v2>(v1*100/107))) {
          for (j=k; j<42; j++) LCD_line(1+i*17, j, 10+i*17, j, 1);
          ok++;
       }     
       LCD_setxy(i*17+1, 7); LCD_dec(UCH_VALUES[i],3,0);  
     }
    // реагируем на нажатие клавиш
    j=get_mnu_keys(); 
    switch (j) {
       case 252 : { // нажали ENT\MENU - сохраняем результаты калибровки
                 resetKeyReader(); // сброс клавиатуры
//                if (ok==7) { // сохраняем результат калибровки только в случае если все 7 аналоговых
                // каналов стоят посередине своих значений
                    for (i=0; i<7; i++) { 
                      UCHmid[i]=UCH_VALUES[i]; // сохраняем середины каналов
                          // сохраняем в epprom результат калибровки
                      E_UCHmin[i]=UCHmin[i];
                      E_UCHmid[i]=UCHmid[i];
                      E_UCHmax[i]=UCHmax[i];
                    }
                           // выдаем пользователю сообщение об успешности
                      messStr1=" CALIBRATION COMPLETE !  ";

                      messStr2="All analog controls ready";
                      messStr3="";
                      messStr4="";
                      printMess=1;
                       
                // выходим                 
                    system_calibration_part=0;
                    menu_exe=0;
                    
//                }   
/**                   else {
                          messStr1="   CALIBRATION ERROR !   ";

                          messStr2="Not center for all analog";
                          messStr3="controls.";
                          messStr4="Try again.. ";
                          printMess=1;
                   }
**/               
                 break; 
       }

     case 250 : { // нажали EXIT - выходим без сохранения
                    for (i=0; i<7; i++) { 
                          // берем из еpprom результат прошлой калибровки
                      UCHmin[i]=E_UCHmin[i];
                      UCHmid[i]=E_UCHmid[i];
                      UCHmax[i]=E_UCHmax[i];
                    }
                   system_calibration_part=0; // и выходим
                   menu_exe=0;
                   resetKeyReader(); // сброс клавиатуры
                   break; } 
    }
  }
}

/**
             Р Е Д А К Т И Р О В А Н И E    К Р И В Ы Х    П О Л Е Т Н Ы Х    Р Е Ж И М О В 

                  (процедура выполняемая при выборе пункта меню EDIT- FMODES - CURVES)
**/

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


unsigned char fmode=0; // полетный режим
unsigned char mode;    // режим печати
signed char cval; // значение кривой
unsigned char ch; // временная переменная- буква канала при печати
unsigned char lpx, lpy, px, py; // координаты точек кривой
signed char curx; 

   //проверяем процедуру на первый запуск
   if (temp1==0) { // у нас первый запуск, инициализация
     temp2=0; // char позиция по Y 
     temp3=0; // char  
     temp4=0; // int  номер канала
     temp5=0; // номер позиции точки
     temp1=1; // устанавливаем признак состоявшегося первого запуска
     ModelChange=1;
   }
   
   switch (numitem_cur) {         // определяем номер полетного режима для редактирования
    case 112: { fmode=0; break; }
    case 117: { fmode=1; break; }
    case 122: { fmode=2; break; }
   }
   
   // Печатаем заголовок
   LCD_setxy(0,0); LCD_wrsf("       CURVE  EDIT       ",1);

                  // печатаем номер полетного режима
   //LCD_setxy(0,2); LCD_wrsf("F MODE: ", 0); 
   LCD_setxy(0,1); LCD_wrsf("F MODE: ", 0);
   LCD_char(fmode+0x31,0);

                  // печатаем номер канала
   if (temp2==0) mode=1; else mode=0;  
   //LCD_setxy(0,3); LCD_wrsf("LCH NUM: ", mode); 
   LCD_setxy(0,2); LCD_wrsf("LCH NUM: ", mode);
   if (mode==1) mode=2; else mode=0;
   if (temp4<9) ch=temp4+49; else ch=temp4+56; 
   LCD_char(ch,mode);
   
                 // печатаем признак включения кривой
   if (temp2==1) mode=1; else mode=0; 
   //LCD_setxy(0,4); LCD_wrsf("CURVE: ", mode);
   LCD_setxy(0,3); LCD_wrsf("CURVE: ", mode);
   if (mode==1) mode=2; else mode=0; 
   switch (rmodel.FMODE[fmode].LCH_CURVE[temp4].active) {
      case 0: { LCD_wrsf(" OFF", mode); break; }
      case 1: { LCD_wrsf(" ON", mode); break; }
   }

                // если кривая включена
if (rmodel.FMODE[fmode].LCH_CURVE[temp4].active==1) {

                 // печатаем значение экспоненты SSS
   if (temp2==2) mode=1; else mode=0; 
   LCD_setxy(0,4); LCD_wrsf("EXPO:   ", mode);
   cval=rmodel.FMODE[fmode].LCH_CURVE[temp4].expon;
   if (mode==1) mode=2; else mode=0; 
   if (cval<0) { LCD_char('-',mode); cval=-cval; } else LCD_char('+',mode); 
   LCD_dec(cval,3,mode); LCD_char('%',mode);
 
                 // печатаем позицию кривой
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

                 // печатаем значение в выбранной позиции
   if (temp2==4) mode=1; else mode=0; 
   LCD_setxy(0,6); LCD_wrsf("VALUE:  ", mode);
   
   cval=rmodel.FMODE[fmode].LCH_CURVE[temp4].point[temp5];
   if (mode==1) mode=2; else mode=0; 
   if (cval<0) { LCD_char('-',mode); cval=-cval; } else LCD_char('+',mode); 
   LCD_dec(cval,3,mode); LCD_char('%',mode);

   // рисуем сетку
   for (mode=0; mode<9; mode++) {
     LCD_dashline(     72,    12+mode*5,     112,      12+mode*5  );
     if (temp5==mode) LCD_line( 72+mode*5,    12,      72+mode*5,      52      ,1);
     else LCD_dashline( 72+mode*5,    12,      72+mode*5,      52      );  
   }

   LCD_line(72,  32, 112, 32, 1); // горизонтальная шкала    

   // рисуем кривую 
   curx=-100; //первая точка
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
   // обрабатываем нажатие управляющих кнопок меню
   mode=get_mnu_keys();
   switch (mode) {
      case 238: { // нажата клавиша UP (вверх)
                  if (temp2>0) temp2--; 
                  break; 
      } 

      case 246: {  // нажата клавиша DN (вниз)
                  if (rmodel.FMODE[fmode].LCH_CURVE[temp4].active==1) {
                     //if (temp2<3) temp2++; else temp2=0; } else {
                     if (temp2<4) temp2++; else temp2=0; } else {
                        if (temp2<1) temp2++; else temp2=0; } 
                  break; 
      } 
                                 
      case 250: {  // нажата клавиша EXIT (возврат в вышестоящее меню) 
                  temp2=0; // обнуляем временные переменные 
                  temp3=0;
                  temp4=0;
                  temp5=0; 
                  temp1=0;
                  resetKeyReader(); // сброс клавиатуры
                  menu_exe=0;
                  CalcCurveORD();
                  break; 
      }
               
      case 252: {  // нажата клавиша MENU/ENT          
                  resetKeyReader(); // сброс клавиатуры                                   
                  break; 
      } 

      case 222: {  // нажата клавиша '-' (двигаемся вправо)
                  switch (temp2) {
                     case 0: { // меняем канал 
                              if (temp4<(rmodel.CHANNELS.LCH_COUNT-1)) temp4++;
                              break;
                     }
                     case 1: { // меняем состояние выключателя кривой
                              if (rmodel.FMODE[fmode].LCH_CURVE[temp4].active==1)
                                 rmodel.FMODE[fmode].LCH_CURVE[temp4].active=0; else
                                   rmodel.FMODE[fmode].LCH_CURVE[temp4].active=1; 
                              break;  
                     }
                     case 2: { // увеличиваем %% экспоненты
                              if (rmodel.FMODE[fmode].LCH_CURVE[temp4].expon<100) {
                                rmodel.FMODE[fmode].LCH_CURVE[temp4].expon++;
                                menu_FMODE_CURVES_EXPO(fmode,temp4); // пересчитываем кривую     
                                }
                              break;  
                     }                    
                     case 3: { // меняем номер позиции
                              if (temp5<8) temp5++; 
                              break;
                     }
                     case 4: { // увеличиваем значение точки
                              if (rmodel.FMODE[fmode].LCH_CURVE[temp4].point[temp5]<100) 
                                 rmodel.FMODE[fmode].LCH_CURVE[temp4].point[temp5]++;
                              break;
                          
                     } 
                  }
                  break; 
      }

     case 190: { //нажата клавиша   '+' (двигаемся влево)
                  switch (temp2) {
                     case 0: { // меняем канал 
                              if (temp4>0) temp4--;
                              break;
                     }
                     case 1: { // меняем состояние выключателя кривой
                              if (rmodel.FMODE[fmode].LCH_CURVE[temp4].active==1)
                                 rmodel.FMODE[fmode].LCH_CURVE[temp4].active=0; else
                                   rmodel.FMODE[fmode].LCH_CURVE[temp4].active=1; 
                              break;  
                     }
                     case 2: { // уменьшаем значене экспоненты
                              if (rmodel.FMODE[fmode].LCH_CURVE[temp4].expon > -100) {
                                rmodel.FMODE[fmode].LCH_CURVE[temp4].expon--;
                                menu_FMODE_CURVES_EXPO(fmode,temp4); // пересчитываем кривую          
                                }
                              break;  
                     }       
                     case 3: { // меняем номер позиции
                              if (temp5>0) temp5--; 
                              break;
                     }
                     case 4: { // уменьшаем значение точки
                              if (rmodel.FMODE[fmode].LCH_CURVE[temp4].point[temp5]>-100) 
                                 rmodel.FMODE[fmode].LCH_CURVE[temp4].point[temp5]--;
                              break;
                     }              
                  }
                  break; 
     }     
   }
}

/**
              Р Е Д А К Т И Р О В А Н И Е   М И К Ш Е Р О В   П О Л Е Т Н О Г О   Р Е Ж И М А

                (процедура выполняемая при выборе пункта меню MODEL - FMODE - MIXER)
**/
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
void FMODE_MIXERS_editmix(unsigned char fmode, unsigned char mixnum){ // подпрограмма редактирования микшера 
unsigned char ACTIVE; // признак активности микшера

unsigned char MIX_SW; // признак выключателя микшера
unsigned char UCH_SW; // выключатель микшера
unsigned char SW_INV; // признак инверсии выключателя

unsigned char DEST_CH; //  канал получатель

unsigned char SOURSE_CH; // канал источник
unsigned char SOURSE_TYPE; // тип канала источника

unsigned char PROC_SOURSE; // тип источника коэффициента микширования
signed char MIX_VAL; // значение микширования (фиксированное)
signed char MX_VAL;
unsigned char MIX_UCH; // значение микширования канала UCH
unsigned char MIX_INV; // инверсия значения микширования канала UCH

unsigned char mode, modex; // режимы печати

unsigned char tmp; // временная переменная

// берем значения полей из микшера
 ACTIVE=rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.ACTIVE;  // микшер включен (существует)
 
 MIX_SW=rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.MIX_SW; //  тип выключателя микшера
 UCH_SW=7+rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.UCH_SW; //  номер выключателя микшера
 SW_INV=rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.SW_INV;
 
 DEST_CH=rmodel.FMODE[fmode].MIXER[mixnum].CH_NUM.CH_DEST; // канал получатель

 SOURSE_TYPE=rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.SOURSE_TYPE; // тип источника
 SOURSE_CH=rmodel.FMODE[fmode].MIXER[mixnum].CH_NUM.CH_SOURSE; // канал источник

 PROC_SOURSE=rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.PROC_SOURSE; // тип значения микширования
 MIX_VAL=rmodel.FMODE[fmode].MIXER[mixnum].MIX_VAL; // фиксированное значения микширования

 MIX_UCH=0x0F & rmodel.FMODE[fmode].MIXER[mixnum].MIX_VAL; // канал источник коэффициента микширования
 if ((0x10&rmodel.FMODE[fmode].MIXER[mixnum].MIX_VAL)!=0) MIX_INV=1;  // инверсия значения микширования
   else MIX_INV=0;
 
  
   if (temp4==0) mode=1; else mode=0; // если стоим в строке то включаем для нее выделение инверсией
   
   LCD_setxy(0,2);
   LCD_wrsf("ACTIVE: ",mode);

   if (mode==1) { 
      if (temp5==1) modex=2; else modex=1;  
   } else modex=0;
   if (ACTIVE==1) LCD_wrsf("ON", modex); else LCD_wrsf("OFF", modex);
   
// печатаем выключатель микшера   
   if (temp4==1) mode=1; else mode=0;        // печать строкового имени параметра 

   LCD_setxy(0,3);              // 
   LCD_wrsf("SWITCH: ",mode);

   if (mode==1) {                                   // печать состояния:
      if (temp5==1) modex=2; else modex=1;  
   } else modex=0;
   if (MIX_SW==0) LCD_wrsf("OFF", modex); // микшер выключен 
      else {   // выключено
         LCD_wrsf("ON ", modex);

         if (mode==1) {                                // имя выключателя
           if (temp5==2) modex=2; else modex=1;  
         } else modex=0;
          
         // печатаем ЗНАК выключатель микшера
         if (SW_INV==1) LCD_wrsf("-", modex); else LCD_wrsf("+", modex); // знак  
  
         LCD_char(' ',mode);
         
         if (mode==1) {                                // имя выключателя
           if (temp5==3) modex=2; else modex=1;  
         } else modex=0;
         LCD_wrsf(UCH_SNAMES[UCH_SW],modex);     
      }

// печатаем канал получатель   
   if (temp4==2) mode=1; else mode=0;        // печать строкового имени параметра 
   LCD_setxy(0,4);              // 
   LCD_wrsf("DEST:   ",mode);
   
   if (mode==1) { 
      if (temp5==1) modex=2; else modex=1;  
   } else modex=0;
   if (DEST_CH<9) tmp=DEST_CH+49; else tmp=DEST_CH+56; 
   LCD_char(tmp,modex);

// печатаем канал источник
   if (temp4==3) mode=1; else mode=0;        // печать строкового имени параметра
   LCD_setxy(0,5);
   LCD_wrsf("SOURCE: ",mode);
   
   if (SOURSE_TYPE==0) { // микширование с UCH
     if (mode==1) { 
       if (temp5==1) modex=2; else modex=1;  
     } else modex=0;
     LCD_wrsf("UCH ",modex);
     
     if (mode==1) { 
       if (temp5==2) modex=2; else modex=1;  
     } else modex=0;
     LCD_wrsf(UCH_SNAMES[SOURSE_CH],modex);
        
   } 
   
   else { // микширования с LCH
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

// печатаем процент микширования
   if (temp4==4) mode=1; else mode=0;        // печать строкового имени параметра
   LCD_setxy(0,6);
   LCD_wrsf("MIX %: ",mode);
   
   if (mode==1) { 
     if (temp5==1) modex=2; else modex=1;  
   } else modex=0;

   if (PROC_SOURSE==0) { // фиксированное значения микширования
     LCD_wrsf("FIX ",modex);

   if (mode==1) { 
     if (temp5==2) modex=2; else modex=1;  
   } else modex=0;
     
     if (MIX_VAL<0) { LCD_char('-',modex); MX_VAL=-MIX_VAL; } else { LCD_char('+',modex); MX_VAL=MIX_VAL;}
     LCD_dec(MX_VAL,3,modex);
   } 
   
   else { // значение микширование из канала UCH
     LCD_wrsf("UCH ",modex);

     if (mode==1) { // печатаем знак микширования UCH 
       if (temp5==2) modex=2; else modex=1;  
     } else modex=0;
   
     if (MIX_INV!=0) { LCD_char('-',modex); } else LCD_char('+',modex);  

     LCD_char(' ',mode);
     
     if (mode==1) { // печатаем номер канала UCH 
       if (temp5==3) modex=2; else modex=1;  
     } else modex=0;
     LCD_wrsf(UCH_SNAMES[MIX_UCH],modex);
   }
   

   mode=get_mnu_keys(); // прочитаем нажатые клавиши навигации по меню
   switch (mode) { // выбираем нажатые клавиши

     case 238: { // нажата клавиша UP (вверх)
                  switch (temp5) { // в зависимости от положения по Х курсора:
                  
                     case 0: { // позиция названия параметра
                               // идем вверх
                               if (temp4>0) temp4--;
                               break;
                     }
                     
                     case 1: { // в зависимости от строки изменяем первое значение  параметра
                              switch (temp4) {
                                 case 0: { // ACTIVE
                                           if (ACTIVE==0) ACTIVE=1; else ACTIVE=0;
                                          break;
                                 }
                                 
                                 case 1: { // SWITCH
                                           if (MIX_SW==0) MIX_SW=1; else MIX_SW=0;
                                          break;
                                 }

                                 case 2: { // DEST_CH
                                           if (DEST_CH<(rmodel.CHANNELS.LCH_COUNT-1)) DEST_CH++;
                                          break;
                                 }
                                 case 3: { // SOURSE
                                           if (SOURSE_TYPE==0) SOURSE_TYPE=1; else { 
                                           SOURSE_TYPE=0; }
                                           SOURSE_CH=0;
                                          break;
                                 }
                                 case 4: { // PROC
                                           if (PROC_SOURSE==0) PROC_SOURSE=1; else PROC_SOURSE=0;
                                          break;
                                 }
                              }
                              break;
                     }
                     
                     case 2: {
                              switch (temp4) {
                                 case 1: { // SWITCH
                                           if (SW_INV==0) SW_INV=1; else SW_INV=0;
                                          break;
                                 }

                                 case 3: { // SOURSE
                                           if (SOURSE_TYPE==1) {                                          
                                              if (SOURSE_CH<(rmodel.CHANNELS.LCH_COUNT-1)) SOURSE_CH++;
                                                else SOURSE_CH=0;
                                           }  else
                                           // UCH каналов всего 14 если вышли за предел то нулевой канал !
                                           if (SOURSE_CH<13) SOURSE_CH++; else SOURSE_CH=0;
                                          break;
                                 }
                                 case 4: { // PROC
                                           if (PROC_SOURSE==0) { // если микширование фиксированное
                                              if (MIX_VAL<125) MIX_VAL++; // увеличиваем MIX_VAL
                                           } 
                                             else { // если микширование UCH то изменяем знак микширования
                                              if (MIX_INV==0) MIX_INV=1; else MIX_INV=0;
                                             }
                                          break;
                                 }
                              }
                              break;
                     }
                     
                     case 3: { // редактируем третий параметр
                              switch (temp4) {
                                 case 1: { // SWITCH
                                           if (UCH_SW<13) UCH_SW++; // меняем номер UCH
                                          break;
                                 }

                                 case 4: { // PROC
                                          if (MIX_UCH<13) MIX_UCH++; // меняем номер UCH 
                                          break;
                                 }
                              }

                              break;
                     }
                     
                  }
                  break; 
     }
                  

     case 246: {  // нажата клавиша DN (вниз)
                  switch (temp5) {
                     case 0: { // позиция названия параметра
                               // идем вниз 
                               if (temp4<4) temp4++;
                               break;
                     }

                     case 1: { // в зависимости от строки изменяем первое значение  параметра
                              switch (temp4) {
                                 case 0: { // ACTIVE
                                           if (ACTIVE==0) ACTIVE=1; else ACTIVE=0;
                                          break;
                                 }
                                 
                                 case 1: { // SWITCH
                                           if (MIX_SW==0) MIX_SW=1; else MIX_SW=0;
                                          break;
                                 }

                                 case 2: { // DEST_CH
                                           if (DEST_CH>0) DEST_CH--;
                                          break;
                                 }
                                 case 3: { // SOURSE
                                           if (SOURSE_TYPE==0) SOURSE_TYPE=1; else { 
                                           SOURSE_TYPE=0; SOURSE_CH=0; }
                                          break;
                                 }
                                 case 4: { // PROC меняем тип источника коэффициента микширования
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
                                 case 1: { // SWITCH
                                           if (SW_INV==0) SW_INV=1; else SW_INV=0;
                                          break;
                                 }

                                 case 3: { // SOURSE                                          
                                           if (SOURSE_CH>0) SOURSE_CH--;
                                           // UCH каналов всего 14 если вышли за предел то нулевой канал !
                                           if ((SOURSE_TYPE==0) && (SOURSE_CH>13)) SOURSE_CH=0;
                                          break;
                                 }
                                 case 4: { // PROC
                                           if (PROC_SOURSE==0) { // если микширование фиксированное
                                              if (MIX_VAL>-125) MIX_VAL--; // уменьшаем MIX_VAL
                                           } 
                                             else { // если микширование UCH то изменяем знак микширования
                                              if (MIX_INV==0) MIX_INV=1; else MIX_INV=0;
                                             }
                                          break;
                                 }
                              }
                              break;
                     }
                     
                     case 3: { // редактируем третий параметр
                              switch (temp4) {
                                 case 1: { // SWITCH
                                           if (UCH_SW>7) UCH_SW--; // меняем номер UCH
                                          break;
                                 }

                                 case 4: { // PROC
                                          if (MIX_UCH>0) MIX_UCH--; // меняем номер UCH 
                                          break;
                                 }
                              }

                              break;
                     }
                  }
                  break; 
     } 
                                 
     case 250: {  // нажата клавиша EXIT (возврат в вышестоящее меню)
                  temp3=0; // выход из режима редактора
                  resetKeyReader(); // сброс клавиатуры
                  getMixCount(FMODE_NUM);
                  mixtochan=mixercount/rmodel.CHANNELS.PPM_CH_COUNT;
                  mixtochanlast=mixercount%rmodel.CHANNELS.PPM_CH_COUNT;                  
                  break; }
               
     case 252: {  // нажата клавиша MENU/ENT (переход в нижестоящее меню/вызов процедуры)
                  switch (temp4) { // в зависимости от строки в которой находимся
                     case 0: {  // признак ACTIVE микшера
                               if (temp5<1) temp5++; else temp5=0;
                               break;
                     }

                     case 1: {  // SWITCH
                                if (MIX_SW==0) { // нет микшера 
                                  if (temp5<1) temp5++; else temp5=0; } 
                                else {  // есть микшер
                                    if (temp5<3) temp5++; else temp5=0; }
                               break;
                     }
                     
                     case 2: {  // DEST_CH
                                if (temp5<1) temp5++; else temp5=0;
                               break;
                     }
                     
                     case 3: {  // SOURSE
                                if (temp5<2) temp5++; else temp5=0;
                               break;
                     }
                     
                     case 4: {  // PROC_VAL
                                if (PROC_SOURSE==0) { // фиксированное значение
                                   if (temp5<2) temp5++; else temp5=0; }
                                else { if (temp5<3) temp5++; else temp5=0; }// значение UCH
                               break;
                     }
                  }
                  break; } 

     case 222: {  // нажата клавиша '-' (двигаемся вправо)
                  switch (temp4) { // в зависимости от строки в которой находимся
                     case 0: {  // признак ACTIVE микшера
                                if (temp5<1) temp5++;
                               break;
                     }

                     case 1: {  // SWITCH
                                if (MIX_SW==0) { // нет микшера 
                                  if (temp5<1) temp5++; } 
                                else {  // есть микшер
                                    if (temp5<3) temp5++; }
                               break;
                     }
                     
                     case 2: {  // DEST_CH
                                if (temp5<1) temp5++;
                               break;
                     }
                     
                     case 3: {  // SOURSE
                                if (temp5<2) temp5++;
                               break;
                     }
                     
                     case 4: {  // PROC_VAL
                                if (PROC_SOURSE==0) { // фиксированное значение
                                   if (temp5<2) temp5++; }
                                else if (temp5<3) temp5++; // значение UCH
                               break;
                     }


                  }
                  break; 
     }

     case 190: { //нажата клавиша   '+' (двигаемся влево)
                  if (temp5>0) temp5--;
                  break; 
     }
   } // конец блока работы с нажатыми клавишами

// сохраняем значения полей из микшера

   if ((ACTIVE==0) && (temp3==0)) {
      for (tmp=mixnum;tmp<40;tmp++) 
        rmodel.FMODE[fmode].MIXER[tmp]=rmodel.FMODE[fmode].MIXER[(unsigned char) (tmp+1)];
   }  
   
   else {
     rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.ACTIVE=ACTIVE;  // микшер включен (существует)
 
     rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.MIX_SW=MIX_SW; //  тип выключателя микшера
 
     rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.UCH_SW=UCH_SW-7; //  номер выключателя микшера
     rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.SW_INV=SW_INV;
 
     rmodel.FMODE[fmode].MIXER[mixnum].CH_NUM.CH_DEST=DEST_CH; // канал получатель

     rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.SOURSE_TYPE=SOURSE_TYPE; // тип источника
 
     rmodel.FMODE[fmode].MIXER[mixnum].CH_NUM.CH_SOURSE=SOURSE_CH; // канал источник

     rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.PROC_SOURSE=PROC_SOURSE; // тип значения микширования
     if (PROC_SOURSE==0) 
       rmodel.FMODE[fmode].MIXER[mixnum].MIX_VAL=MIX_VAL; // фиксированное значения микширования
       else rmodel.FMODE[fmode].MIXER[mixnum].MIX_VAL=MIX_UCH+MIX_INV*16; 

   }
}

void menu_FMODE_MIXERS() {
unsigned char fmode;
// unsigned char mixcount; // количество микшеров
unsigned char offs; // смещение при печати
unsigned char i;// временная переменная циклов

unsigned char x; // - переменные цикла при выводе
unsigned char y; // -    значений каналов
unsigned int ii; // переменная подсчета для вывода значений каналов

unsigned char mode; // режим печати
unsigned char MIX_SW, SOURSE_TYPE, PROC_SOURSE; // значения соответстующих полей выбранного микшера
unsigned char mixnum; // номер микшера
unsigned char UCH_SW; // номер выключателя микшера
// unsigned char SW_INV; // инверсия выключателя микшера
unsigned char CH_DEST; // канал получатель
unsigned char CH_SOURSE; // канал источник
unsigned char tmp; // временная переменная
signed char S_MIX_VAL; // значение микширования со знаком
unsigned char MIX_VAL; // значение микширования без знака
unsigned char MIX_UCH; // канал источник коэффициента микширования
unsigned char MIX_INV; // признак инверсии значения канала
unsigned char mixmax; // максимальное значение микшера 

   //проверяем процедуру на первый запуск
   if (temp1==0) { // у нас первый запуск, инициализация
     temp2=0; // char номер микшера для редактирования 
     temp3=0; // char  
     temp4=0; // int  
     temp5=0; // char
     temp1=1; // устанавливаем признак состоявшегося первого запуска
     ModelChange=1; // признак изменения модели
   }
   
   switch (numitem_cur) {         // определяем номер полетного режима для редактирования
    case 113: { fmode=0; break; }
    case 118: { fmode=1; break; }
    case 123: { fmode=2; break; }
   }
   
   // Печатаем заголовок
   LCD_setxy(0,0); LCD_wrsf("       MIXER  EDIT       ",1);

  if (temp3==3) { // режим показа аналогового монитора значений каналов
  
      // выводим графически значение каналов 
                for (x=0;x<2;x++) { // два столбца
                   for (y=0;y<4;y++) { // 4 строки
                      if ((x*4+y)<rmodel.CHANNELS.PPM_CH_COUNT) { // если канал нужно отображать
                     
                         LCD_setxy(10+x*60,y+2); // выводим номер канала 
                         LCD_wrsf("CH",0); LCD_dec((unsigned char)(x*4+y+1),1,0);
                         LCD_char(' ',0);
                        
                         if ((CH_PPM[(unsigned char)(x*4+y)]>=rmodel.CHANNELS.CH_EPL[(unsigned char)(x*4+y)]) && 
                            (CH_PPM[(unsigned char)(x*4+y)]<=rmodel.CHANNELS.CH_EPR[(unsigned char)(x*4+y)]))  {
                            // если длительность канала внутри заданных длин импульса
                            // выводим шкалу значения 
                            ii=(CH_PPM[(unsigned char)(x*4+y)] - rmodel.CHANNELS.CH_EPL[(unsigned char)(x*4+y)]);
                        
                            ii=ii /
                                  (( rmodel.CHANNELS.CH_EPR[(unsigned char)(x*4+y)] - 
                                                       rmodel.CHANNELS.CH_EPL[(unsigned char)(x*4+y)]) / 25) ;
                        
                            for (i=0;i<(unsigned char)ii; i++) {
                               LCD_out(0x7E);     
                             }
                             // выводим свободное место
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

     mode=get_mnu_keys(); // прочитаем нажатые клавиши навигации по меню
     switch (mode) { // выбираем нажатые клавиши                                 
       case 250: {  // нажата клавиша EXIT (возврат в вышестоящее меню) 
                  temp3=0; // режим редактора
                  resetKeyReader(); // сброс клавиатуры
                  break; }             

       case 222: {  // нажата клавиша '-' (двигаемся вправо)
                  temp3=3; // показываем аналоговый монитор длительностей каналов
                  break; }

       case 190: { //нажата клавиша   '+' (двигаемся влево)
                  temp3=2; // показываем цифровой монитор длительностей каналов
                  break; }
     } // конец блока работы с нажатыми клавишами
       
  } 
  
  else

  if (temp3==2) { // режим показа цифрового монитора значений каналов
  
      // выводим в цифрах значения каналов 
      for (x=0;x<2;x++) { // два столбца
         for (y=0;y<4;y++) { // 4 строки
             if ((x*4+y)<rmodel.CHANNELS.PPM_CH_COUNT) {
                 LCD_setxy(10+x*65,y+2); 
                 LCD_wrsf("CH",0); LCD_dec((unsigned char)(x*4+y+1),1,0);
                 LCD_char(' ',0);
                 LCD_dec(CH_PPM[(unsigned char)(x*4+y)],4,0);
             }
         }
      }

     mode=get_mnu_keys(); // прочитаем нажатые клавиши навигации по меню
     switch (mode) { // выбираем нажатые клавиши                                 
       case 250: {  // нажата клавиша EXIT (возврат в вышестоящее меню) 
                  temp3=0; // режим редактора
                  resetKeyReader(); // сброс клавиатуры
                  break; }             

       case 222: {  // нажата клавиша '-' (двигаемся вправо)
                  temp3=3; // показываем аналоговый монитор длительностей каналов
                  break; }

       case 190: { //нажата клавиша   '+' (двигаемся влево)
                  temp3=2; // показываем цифровой монитор длительностей каналов
                  break; }
     } // конец блока работы с нажатыми клавишами
       
  } 
  
  else
   
   if (temp3==1) {  // - - - - - - - - - - - - - - -режим редактирования микшера
     FMODE_MIXERS_editmix(fmode, temp2);   
   }
     else 
{  // - - - - - - - - - - - - - режим просмотра и выбора микшера для редактирования
   //шапка таблицы
   LCD_setxy(0,1); LCD_wrsf("NO TYP SWIT. D SOUR PROC.", 0);
   mode=0;
   if (temp2>5) offs=temp2-5; else offs=0;

   for (i=0;i<6;i++) {

      mixmax=39;
      mixnum=i+offs;

      LCD_setxy(0,2+i); 
      
      if (mixnum==temp2) mode=1; else mode=0; // если текущий микшер в позиции курсора - выделяем его
      
      // печатаем микшеры начиная с offs 5 штуки подряд либо пока не встретим пустой микшер
      if (rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.ACTIVE==1) { // микшер есть

// печатаем номер микшера
        LCD_dec((unsigned char)(mixnum+1),2,mode);  
        LCD_char(' ',mode);

// печатаем тип микшера
         MIX_SW=rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.MIX_SW;
         if (MIX_SW==1) { // выключатель микшера
            LCD_char('S',mode); } else { LCD_char('-',mode); }

         SOURSE_TYPE=rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.SOURSE_TYPE;
         if (SOURSE_TYPE==1) { // тип источника
            LCD_char('L',mode); } else { LCD_char('U',mode); }

         PROC_SOURSE=rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.PROC_SOURSE;
         if (PROC_SOURSE==1) { // значение микширования
            LCD_char('U',mode); } else { LCD_char('F',mode); }

        LCD_char(' ',mode); // пробел после типа микшера

// печать выключателя микшера
        if (MIX_SW==1) { // если у микшера есть выключатель - печатаем его
        
           UCH_SW=rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.UCH_SW;

           // если есть инверсия выключателя - печатаем '-' иначе печатаем пробел
           if (rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.SW_INV==1) LCD_char('-',mode); 
             else LCD_char(' ',mode);

           LCD_wrsf(UCH_SNAMES[(unsigned char)(UCH_SW+7)],mode); // печатаем название выключателя
        } 
           else { // выключателя нет - печатаем прочерки
             LCD_wrsf("-----",mode);
           }
           LCD_char(' ',mode);
        
// печать канала получателя
          CH_DEST=rmodel.FMODE[fmode].MIXER[mixnum].CH_NUM.CH_DEST; // канал получатель
          if (CH_DEST<9) tmp=CH_DEST+49; else tmp=CH_DEST+56; 
          LCD_char(tmp,mode);
          LCD_char(' ', mode);
          
// печать канала источника
          CH_SOURSE=rmodel.FMODE[fmode].MIXER[mixnum].CH_NUM.CH_SOURSE; // канал источник
          
          if (SOURSE_TYPE==1) { // источник канал LCH
             LCD_char(' ', mode);
             if (CH_SOURSE<9) tmp=CH_SOURSE+49; else tmp=CH_SOURSE+56; 
             LCD_char(tmp,mode);
             LCD_char(' ', mode);
             LCD_char(' ', mode);
          }
             else { // источник канал UCH
             LCD_wrsf(UCH_SNAMES[CH_SOURSE],mode);
             }
          LCD_char(' ',mode);
          
// печать процента микширования
          if (PROC_SOURSE==1) { // регулируемый процент микширования
            MIX_VAL=rmodel.FMODE[fmode].MIXER[mixnum].MIX_VAL; // берем значение
            MIX_UCH=MIX_VAL & 0x0F; // выделяем канал источник процента микширования
            if ((MIX_VAL-MIX_UCH)!=0) { LCD_char('-',mode); MIX_INV=1; 
            } 
              else { MIX_INV=0; // заполним инверсию процента микширования
                     LCD_char(' ',mode); }
           
            LCD_wrsf(UCH_SNAMES[MIX_UCH],mode);            
           
          } else { // фиксированный процент микширования
             S_MIX_VAL=rmodel.FMODE[fmode].MIXER[mixnum].MIX_VAL;
             if (S_MIX_VAL<0) { LCD_char('-',mode); S_MIX_VAL=-S_MIX_VAL; } else LCD_char('+',mode);
             LCD_dec(S_MIX_VAL,3,mode); 
          }
      } 
         else { // микшера нет
            LCD_wrsf("-- --- ----- - ---- -----", mode);
            mixmax=mixnum;
           break; // интересно цикл прервется?
         }
   } 

   mode=get_mnu_keys(); // прочитаем нажатые клавиши навигации по меню
   switch (mode) { // выбираем нажатые клавиши

     case 238: { // нажата клавиша UP (вверх)
                  if (temp2>0) temp2--;
                  break; } 

     case 246: {  // нажата клавиша DN (вниз)
                  if (temp2<mixmax) temp2++;
                  break; } 
                                 
     case 250: {  // нажата клавиша EXIT (возврат в вышестоящее меню) 
                  temp2=0; // номер микшера для редактирования 
                  temp3=0; // режим редактора
                  temp4=0;
                  temp5=0;
                  temp1=0; // признак первого запуска
                  resetKeyReader(); // сброс клавиатуры
                  menu_exe=0;
                  break; }
               
     case 252: {  // нажата клавиша MENU/ENT (переход в нижестоящее меню/вызов процедуры)
                  temp3=1; // включаем режим редактирования микщера
                  temp4=0; // строка редактирования микшера
                  temp5=0; // позиция редактирования микшера
                  resetKeyReader(); // сброс клавиатуры                                            
                  break; } 

     case 222: {  // нажата клавиша '-' (двигаемся вправо)
                  temp3=3; // показываем аналоговый монитор длительностей каналов
                  break; }

     case 190: { //нажата клавиша   '+' (двигаемся влево)
                  temp3=2; // показываем цифровой монитор длительностей каналов
                  break; }
   } // конец блока работы с нажатыми клавишами
   
} // конец блока просмотра и выбора микшера для редактирования

} // конец подпрограммы


/**
                        С Б Р О С    М О Д Е Л И
    
               (процедура выполняемая при выборе пункта меню FILE - RESET )
**/    
void FILE_RESET() {
unsigned char rkey,i,j;
// -------------------------------------------------------------------------------------- ИНИЦИАЛИЗАЦИЯ МОДЕЛИ  
   
  rmodel.MODEL_TYPE=0;      // тип - самолет
  
  rmodel.MODEL_NAME[0]='N'; // имя модели
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
                                      // физические ограничения длительностей канальных импульсов
    rmodel.CHANNELS.CH_EPL[rkey]=1000;
    rmodel.CHANNELS.CH_EPR[rkey]=2000;
                                      // задержки изменения значений каналов
    rmodel.CHANNELS.LCHDELDN[rkey]=0;
    rmodel.CHANNELS.LCHDELUP[rkey]=0; 
                                      // признак реверса канала
    rmodel.CHANNELS.LCH_REV[rkey]=0;
                                      // количество полетных режимов 
                                      // середины каналов
    rmodel.FMODE[0].LCH_MIDLE[rkey]=1500; //
    rmodel.FMODE[1].LCH_MIDLE[rkey]=1500; //
    rmodel.FMODE[2].LCH_MIDLE[rkey]=1500; //   
                                          // кривые каналов

    rmodel.FMODE[0].LCH_CURVE[rkey].active=0; // кривую выключить   
    rmodel.FMODE[0].LCH_CURVE[rkey].expon=0; // экспоненту отключить
                                          
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
  
  rmodel.CHANNELS.LCH_COUNT=8;   // количество используемых каналов в модели 
 
  for (rkey=0; rkey<8; rkey++) { // фильтры каналов только линейные
    rmodel.CHANNELS.FILTER[rkey].FILTER_TYPE=0;
    rmodel.CHANNELS.FILTER[rkey].VAL1=0; 
  }

    for (i=0;i<3;i++) { // перебираем полетные режимы

            // шаг триммеров полетных режимов
     rmodel.FMODE[i].TRIMSTEP=1; 
  
     for (j=0;j<40;j++) { // перебираем микшеры полетного режима
        rmodel.FMODE[i].MIXER[j].MIX_TYPE.ACTIVE=0;       // микшер включен
        rmodel.FMODE[i].MIXER[j].MIX_TYPE.SOURSE_TYPE=0;  // тип источника UCH
        rmodel.FMODE[i].MIXER[j].MIX_TYPE.PROC_SOURSE=0;  // фиксированное значение микширования
        rmodel.FMODE[i].MIXER[j].MIX_TYPE.MIX_SW=0;       // выключателя микшера нет
        rmodel.FMODE[i].MIXER[j].MIX_TYPE.SW_INV=0;       // инверсия выключателя 
        rmodel.FMODE[i].MIXER[j].MIX_TYPE.UCH_SW=0;       // выключатель микшера      
        rmodel.FMODE[i].MIXER[j].CH_NUM.CH_SOURSE=0;      // канал источник 
        rmodel.FMODE[i].MIXER[j].CH_NUM.CH_DEST=0;        // канал получатель
        rmodel.FMODE[i].MIXER[j].MIX_VAL=100;             // процент микширования
     }
  }

  for (rkey=0; rkey<14; rkey++) { // процентные значения UCH
     rmodel.UCH[rkey].UCH_LEFT=-100;
     rmodel.UCH[rkey].UCH_RIGHT=100;
  }
 
     rmodel.CHANNELS.PPM_CH_COUNT=8; // количество каналов в пачке PPM
     PPM_PAUSE=0;     // паузу считаем заново
     PPM_CUR_CH_NUM=0; // номер канала заново

     // выставляем средние точки LCH в соответствии с полетным режимом и триммерами каналов
     for (i=0;i<rmodel.CHANNELS.LCH_COUNT;i++) {
         LCH_LEN[i]=rmodel.FMODE[FMODE_NUM].LCH_MIDLE[i];
     }
     
    for (i=0; i<8; i++) rmodel.PPM_TO_LCH_CAP[i]=0; // сброс списка захватываемых каналов PPM

  resetKeyReader(); // сброс клавиатуры
}

void menu_FILE_RESET() { 
unsigned char mode;

LCD_setxy(0,0);  LCD_wrsf(" RESET CURRENT MODEL     ",1);

LCD_setxy(0,2);  LCD_wrsf(" to cancel press MENU   >",0);

LCD_setxy(0,6);  LCD_wrsf("to process press - EXIT >",0);

   mode=get_mnu_keys(); // прочитаем нажатые клавиши навигации по меню
   switch (mode) { // выбираем нажатые клавиши

     case 238: { // нажата клавиша UP (вверх)
                  break; } 

     case 246: {  // нажата клавиша DN (вниз)
                  break; } 
                                 
     case 252: {  // нажата клавиша MENU/ENT (возврат в вышестоящее меню) 
                  temp2=0; // номер микшера для редактирования 
                  temp3=0; // режим редактора
                  temp4=0;
                  temp5=0;
                  temp1=0; // признак первого запуска
                  resetKeyReader(); // сброс клавиатуры
                  menu_exe=0;
                  break; }
               
     case 250: {  // нажата клавиша EXIT (переход в нижестоящее меню/вызов процедуры)
                  FILE_RESET();
                  E_CurModelNum=255;
                  ModelChange=0;
                  temp2=0; // номер микшера для редактирования 
                  temp3=0; // режим редактора
                  temp4=0;
                  temp5=0;
                  temp1=0; // признак первого запуска
                  resetKeyReader(); // сброс клавиатуры
                  menu_exe=0;                  
                  break; } 

     case 222: {  // нажата клавиша '-' (двигаемся вправо)
                  break; }

     case 190: { //нажата клавиша   '+' (двигаемся влево)
                  break; }
   } // конец блока работы с нажатыми клавишами

}

/**
                       З А Г Р У З К А    М О Д Е Л И    П О    Н О М Е Р У
**/
void OpenModel(unsigned char filenum) {
unsigned char i,j,k,tmp; // временные переменные 
unsigned int  ti,i1,i2;

FILE_RESET(); // сначала сбросим состояние модели
FMODE_NUM=0;

  if (fileToRead(filenum)==0) { // файл существует и открыт
    // читаем тип модели
    rmodel.MODEL_TYPE=fileRead();
    // читаем имя модели
    for(i=0;i<8;i++) {
      rmodel.MODEL_NAME[i]=fileRead();
    }
    // читаем полетный таймер
    i1=fileRead();
    i2=fileRead();
    ti=i1+i2*256;
    rmodel.MODEL_FLYTIMER=ti;
    flyCurrTimer=rmodel.MODEL_FLYTIMER;

    // читаем время жизни модели
    i1=fileRead();
    i2=fileRead();
    ti=i1+i2*256;
    rmodel.MODEL_LIVETIMER=ti;
    
    // чтение LCH
    rmodel.CHANNELS.LCH_COUNT=fileRead(); // количество каналов модели
    // чтение LCH EPL
    for (i=0; i<rmodel.CHANNELS.LCH_COUNT; i++) {

       i1=fileRead();
       i2=fileRead();
       ti=i1+i2*256;
       rmodel.CHANNELS.CH_EPL[i]=ti;
    } 
    // чтение LCH EPR
    for (i=0; i<rmodel.CHANNELS.LCH_COUNT; i++) {

       i1=fileRead();
       i2=fileRead();
       ti=i1+i2*256;
       rmodel.CHANNELS.CH_EPR[i]=ti;
    } 
    // LCHDELDN
    for (i=0; i<rmodel.CHANNELS.LCH_COUNT; i++) {

       rmodel.CHANNELS.LCHDELDN[i]=fileRead();
    } 
    // LCHDELUP
    for (i=0; i<rmodel.CHANNELS.LCH_COUNT; i++) {

       rmodel.CHANNELS.LCHDELUP[i]=fileRead();
    } 
    // LCH_REV
    for (i=0; i<rmodel.CHANNELS.LCH_COUNT; i++) {

       rmodel.CHANNELS.LCH_REV[i]=fileRead();
    } 
   
    // чтение информации о CH
    rmodel.CHANNELS.PPM_CH_COUNT=fileRead();
    // чтение информации о фильтрах каналов
    for (i=0; i<rmodel.CHANNELS.PPM_CH_COUNT; i++) {
       //чтение типа фильтра
       rmodel.CHANNELS.FILTER[i].FILTER_TYPE=fileRead(); 
       // чтение параметра фильтра
       i1=fileRead();
       i2=fileRead();
       ti=i1+i2*256;
       rmodel.CHANNELS.FILTER[i].VAL1=ti;
    }
    
    // чтение информации о каналах UCH
    i=fileRead();
    while (i!=0) {
       rmodel.UCH[i-1].UCH_LEFT=fileRead();
       rmodel.UCH[i-1].UCH_RIGHT=fileRead();
       i=fileRead();
    }

    // ------
    // количество полетных режимов
    rmodel.FMODE_COUNT=fileRead();
    for (i=0;i<rmodel.FMODE_COUNT;i++) {  // цикл сохранения полетных режимов

       // имя полетного режима
       rmodel.FMODE[i].FMODE_NAME=fileRead();

       // шаг триммеров
       rmodel.FMODE[i].TRIMSTEP=fileRead();

       // триммеры каналов
       for (j=0;j<7;j++) {
          rmodel.FMODE[i].UCH_TRIMMER[j]=fileRead();
       }

       // средние точки каналов
       for (j=0;j<rmodel.CHANNELS.LCH_COUNT;j++) {
         i1=fileRead();
         i2=fileRead();
         ti=i1+i2*256;
         rmodel.FMODE[i].LCH_MIDLE[j]=ti;
       }

       // кривые каналов
       for (j=0;j<rmodel.CHANNELS.LCH_COUNT;j++) {
          switch (fileRead()) {
             case 0 : { // нет кривой
                        rmodel.FMODE[i].LCH_CURVE[j].active=0; // нет кривой
                        break;
             }
             case 1 : { // только кривая без экспоненты       
                        rmodel.FMODE[i].LCH_CURVE[j].active=1; // кривая есть !
                        for (k=0;k<9;k++) { // читаем 9 точек кривой
                          rmodel.FMODE[i].LCH_CURVE[j].point[k]=fileRead();
                        }
                        break;
             }
             case 100:{ // кривая с экспонентой             
                        rmodel.FMODE[i].LCH_CURVE[j].active=1; // кривая есть !
                        rmodel.FMODE[i].LCH_CURVE[j].expon=fileRead(); // читаем значение экспоненты
                        for (k=0;k<9;k++) { // читаем 9 точек кривой
                          rmodel.FMODE[i].LCH_CURVE[j].point[k]=fileRead();
                        }           
                        break;
             }   
          }
       }

       // читаем количество микшеров
       k=fileRead(); 
        // перебираем все микшеры
       for (j=0;j<k;j++) {
          tmp=fileRead(); // тип микшера
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
                     
          tmp=fileRead(); // каналы
          rmodel.FMODE[i].MIXER[j].CH_NUM.CH_SOURSE=tmp>>4;
          rmodel.FMODE[i].MIXER[j].CH_NUM.CH_DEST=tmp & 0x0F;   
          
          rmodel.FMODE[i].MIXER[j].MIX_VAL=fileRead(); // значение микширования   
       }
    }    

/**
        // читаем захватываемые каналы
       for (i=0;i<8;i++) rmodel.PPM_TO_LCH_CAP[i]=fileRead();   
**/    
  }

//--------------------------------------------------------------------------------------
  for (i=0; i<8; i++) mch[i]=0; //  сбрасываем счетчики канального мультиплексирования
  
  //выставляем средние точки LCH в соответствии с полетным режимом
  for (i=0;i<16;i++) { 
     LCH_LEN[i]=rmodel.FMODE[FMODE_NUM].LCH_MIDLE[i];
     OLD_LCH_LEN[i]=rmodel.FMODE[FMODE_NUM].LCH_MIDLE[i];
  }
  
  CalcCurveORD(); // рассчитаем кривые текущего режима
  getMixCount(FMODE_NUM);
  mixtochan=mixercount/rmodel.CHANNELS.PPM_CH_COUNT;
  mixtochanlast=mixercount%rmodel.CHANNELS.PPM_CH_COUNT;
//------------------------------------ добавлено для выполнения после загрузки --------
}

/**
             М Е Н Ю   З А Г Р У З К А    Н О В О Й   М О Д Е Л И   С   V D I S K
**/
void menu_MODEL_OPEN() {
unsigned char i, offs, mode, tmp; // временные переменные цикла и смещения 

if (temp1==0) { // первый запуск
  temp1=1; // флаг что первый запуск произведен
  temp2=0; // номер выбранного файла
}
// печатаем заголовок
LCD_setxy(0,0); LCD_wrsf("     OPEN MODEL FILE     ",1);

LCD_setxy(0,2); LCD_wrsf("NN TYPE   MODELNAME SIZE ",0);

if (temp2>4) offs=temp2-4; else offs=0;

  for (i=0; i<5; i++) { \\ цикл вывода имен сохраненных моделей
     LCD_setxy(0,3+i);
     if (temp2==(i+offs)) mode=1; else mode=0; // выделение курсора
     LCD_dec((unsigned char)(i+offs),2,mode); // печатаем номер модели
     LCD_char(' ', mode); // печатаем пробел
  
     if (fileToRead(i+offs)==0) { // файл существует и открыт
       // первый байт - тип модели
       tmp=fileRead(); 
       LCD_wrsf(MODEL_TYPE[tmp],mode); // печатаем тип модели
    
       LCD_char(' ',mode); // печатаем пробел
       // далее следует имя модели
       for (tmp=0;tmp<8; tmp++) { // печатаем имя модели
          LCD_char(fileRead(),mode);
       }
    
       LCD_char(' ',mode);
            LCD_char(' ', mode);
                 LCD_char(' ', mode);
                      LCD_char(' ', mode);
    
       // печатаем размер модели
       tmp=fileSize(i+offs);
       LCD_dec(tmp,2,mode);    
     }
  }
   mode=get_mnu_keys(); // прочитаем нажатые клавиши навигации по меню
   switch (mode) { // выбираем нажатые клавиши

     case 238: { // нажата клавиша UP (вверх)
                  if (temp2>0) temp2--;
                  break; } 

     case 246: {  // нажата клавиша DN (вниз)
                  if (temp2<15) temp2++;
                  break; } 
                                 
     case 250: {  // нажата клавиша EXIT (возврат в вышестоящее меню) 
                  temp2=0; // номер микшера для редактирования 
                  temp3=0; // режим редактора
                  temp4=0;
                  temp5=0;
                  temp1=0; // признак первого запуска
                  resetKeyReader(); // сброс клавиатуры
                  menu_exe=0;
                  break; }
               
     case 252: {  // нажата клавиша MENU/ENT (переход в нижестоящее меню/вызов процедуры)
                  OpenModel(temp2);
                  E_CurModelNum=temp2;
                  temp2=0; // номер микшера для редактирования 
                  temp3=0; // режим редактора
                  temp4=0;
                  temp5=0;
                  temp1=0; // признак первого запуска
                  resetKeyReader(); // сброс клавиатуры
                  menu_exe=0;                  
                  break; } 

     case 222: {  // нажата клавиша '-' (двигаемся вправо)
                  break; }

     case 190: { //нажата клавиша   '+' (двигаемся влево)
                  break; }
   } // конец блока работы с нажатыми клавишами
  
}


/**
                       З А П И С Ь   М О Д Е Л И   П О   Н О М Е Р У   Н А   V D I S K
**/
void SaveModel(unsigned filenum) {
unsigned char i,j,k,tmp; // временные переменные 
  
  ppmStop=1; // останавливаем работу ppm генератора на выдачу
  
  while (ppmStop!=2);

  printMess=1;
  fileDelete(filenum); // сначала удаляем модель с этим номером
  printMess=0;

  if (fileToWrite(filenum)==0) { // файл открыт для записи
    // тип модели
    fileWrite(rmodel.MODEL_TYPE);
    // имя модели
    for(i=0;i<8;i++) {
      fileWrite(rmodel.MODEL_NAME[i]);
    }
    // полетный таймер
    fileWrite((unsigned char)(rmodel.MODEL_FLYTIMER%256));
    fileWrite((unsigned char)(rmodel.MODEL_FLYTIMER/256));
    
    // время жизни модели
    fileWrite((unsigned char)(rmodel.MODEL_LIVETIMER%256));
    fileWrite((unsigned char)(rmodel.MODEL_LIVETIMER/256));
    
    // LCH COUNT
    fileWrite(rmodel.CHANNELS.LCH_COUNT); // количество каналов модели
    // LCH EPL
    for (i=0; i<rmodel.CHANNELS.LCH_COUNT; i++) {

       fileWrite((unsigned char)(rmodel.CHANNELS.CH_EPL[i]%256));
       fileWrite((unsigned char)(rmodel.CHANNELS.CH_EPL[i]/256));
    } 
    // LCH EPR
    for (i=0; i<rmodel.CHANNELS.LCH_COUNT; i++) {

       fileWrite((unsigned char)(rmodel.CHANNELS.CH_EPR[i]%256));
       fileWrite((unsigned char)(rmodel.CHANNELS.CH_EPR[i]/256));
    } 
    // LCHDELDN
    for (i=0; i<rmodel.CHANNELS.LCH_COUNT; i++) {

       fileWrite(rmodel.CHANNELS.LCHDELDN[i]);
    } 
    // LCHDELUP
    for (i=0; i<rmodel.CHANNELS.LCH_COUNT; i++) {

       fileWrite(rmodel.CHANNELS.LCHDELUP[i]);
    } 
    // LCH_REV
    for (i=0; i<rmodel.CHANNELS.LCH_COUNT; i++) {

       fileWrite(rmodel.CHANNELS.LCH_REV[i]);
    } 
   
    // информация о CH
    fileWrite(rmodel.CHANNELS.PPM_CH_COUNT);
    // информация о фильтрах каналов
    for (i=0; i<rmodel.CHANNELS.PPM_CH_COUNT; i++) {
       // тип фильтра
       fileWrite(rmodel.CHANNELS.FILTER[i].FILTER_TYPE); 
       // параметр фильтра
       fileWrite(rmodel.CHANNELS.FILTER[i].VAL1%256);
       fileWrite(rmodel.CHANNELS.FILTER[i].VAL1/256);
    }
    
    // информация о каналах UCH
    for (i=0;i<14; i++) { // перебираем каналы UCH

       // проверяем используется ли канал
       tmp=0;
       for (j=0; j<40; j++) { // перебираем микшеры
          for (k=0; k<3; k++) { // перебираем полетные режимы
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
    fileWrite(0); // маркер конца записи об UCH   
    
    // количество полетных режимов
    fileWrite(rmodel.FMODE_COUNT);
    for (i=0;i<rmodel.FMODE_COUNT;i++) {  // цикл сохранения полетных режимов

       // имя полетного режима
       fileWrite(rmodel.FMODE[i].FMODE_NAME);

       // шаг триммеров
       fileWrite(rmodel.FMODE[i].TRIMSTEP);

       // триммеры каналов
       for (j=0;j<7;j++) {
          fileWrite(rmodel.FMODE[i].UCH_TRIMMER[j]);
       }

       // средние точки каналов
       for (j=0;j<rmodel.CHANNELS.LCH_COUNT;j++) {
          fileWrite(rmodel.FMODE[i].LCH_MIDLE[j]%256);
          fileWrite(rmodel.FMODE[i].LCH_MIDLE[j]/256);
       }

       // кривые каналов
       for (j=0;j<rmodel.CHANNELS.LCH_COUNT;j++) {
          if (rmodel.FMODE[i].LCH_CURVE[j].active!=0) { // кривая включена?

            if (rmodel.FMODE[i].LCH_CURVE[j].expon==0) // экспонента есть ?
               fileWrite(1); //признак активности кривой без экспоненты
            else { 
               fileWrite(100); // признак активности кривой с экспонентой
               fileWrite(rmodel.FMODE[i].LCH_CURVE[j].expon); // значение экспоненты
            }
            
            if (rmodel.FMODE[i].LCH_CURVE[j].active!=0) { // если кривая канала задана то...
               for (k=0;k<9;k++) { // запись 9 точек кривой
                 fileWrite(rmodel.FMODE[i].LCH_CURVE[j].point[k]);
               }      
            }
          } else fileWrite(0); // если экспоненты нет - пишем ноль
       }

       // сохранение микшеров
       k=0; // подсчитываем общее количество микшеров в полетном режиме
       while (rmodel.FMODE[i].MIXER[k].MIX_TYPE.ACTIVE==1) k++;
       fileWrite(k); // запишем количество полетных режимов

        // перебираем все микшеры
       for (j=0;j<k;j++) {
          tmp=0x80;
          
          if (rmodel.FMODE[i].MIXER[j].MIX_TYPE.SOURSE_TYPE==1) tmp=tmp|0b01000000;
          if (rmodel.FMODE[i].MIXER[j].MIX_TYPE.PROC_SOURSE==1) tmp=tmp|0b00100000;
          if (rmodel.FMODE[i].MIXER[j].MIX_TYPE.MIX_SW==1)      tmp=tmp|0b00010000;
          if (rmodel.FMODE[i].MIXER[j].MIX_TYPE.SW_INV==1)      tmp=tmp|0b00001000;
          tmp=tmp|rmodel.FMODE[i].MIXER[j].MIX_TYPE.UCH_SW;           
          fileWrite(tmp); // сохраняем тип
          tmp=0;
          tmp=tmp|rmodel.FMODE[i].MIXER[j].CH_NUM.CH_SOURSE;
          tmp=tmp<<4;
          tmp=tmp|rmodel.FMODE[i].MIXER[j].CH_NUM.CH_DEST;   
          fileWrite(tmp); // сохраняем каналы
          fileWrite(rmodel.FMODE[i].MIXER[j].MIX_VAL); // сохраняем значение микширования   
       }
    }    
/**
     // сохраняем захватываемые каналы
     for (i=0;i<8;i++) fileWrite(rmodel.PPM_TO_LCH_CAP[i]);   
**/
  } else { // V-disk не готов, возможно нет свободного места
     // выдаем пользователю об этом предупреждение
     messStr1="     V-DISK  ERROR !     ";

     messStr2="    NO FREE  SPACE !     ";
     messStr3="   delete old models     ";
     messStr4="   or format V-Disk      ";
     printMess=1;
  }
  
  ppmStop=0;
}

// УДАЛЕНИЕ ВЫБРАННОЙ МОДЕЛИ
void menu_FILE_ERASE() {
unsigned char i, offs, mode, tmp; // временные переменные цикла и смещения 

if (temp1==0) { // первый запуск
  temp1=1; // флаг что первый запуск произведен
  temp2=0; // номер выбранного файла
}
// печатаем заголовок
LCD_setxy(0,0); LCD_wrsf("   ERASE  MODEL AS..     ",1);

LCD_setxy(0,2); LCD_wrsf("NN TYPE   MODELNAME SIZE ",0);

if (temp2>4) offs=temp2-4; else offs=0;

  for (i=0; i<5; i++) { \\ цикл вывода имен сохраненных моделей
     LCD_setxy(0,3+i);
     if (temp2==(i+offs)) mode=1; else mode=0; // выделение курсора
     LCD_dec((unsigned char)(i+offs),2,mode); // печатаем номер модели
     LCD_char(' ', mode); // печатаем пробел
  
     if (fileToRead(i+offs)==0) { // файл существует и открыт
       // первый байт - тип модели
       tmp=fileRead(); 
       LCD_wrsf(MODEL_TYPE[tmp],mode); // печатаем тип модели
    
       LCD_char(' ',mode); // печатаем пробел
       // далее следует имя модели
       for (tmp=0;tmp<8; tmp++) { // печатаем имя модели
          LCD_char(fileRead(),mode);
       }
    
       LCD_char(' ',mode);
            LCD_char(' ', mode);
                 LCD_char(' ', mode);
                      LCD_char(' ', mode);
    
       // печатаем размер модели
       tmp=fileSize(i+offs);
       LCD_dec(tmp,2,mode);    
     }
  }
   mode=get_mnu_keys(); // прочитаем нажатые клавиши навигации по меню
   switch (mode) { // выбираем нажатые клавиши

     case 238: { // нажата клавиша UP (вверх)
                  if (temp2>0) temp2--;
                  break; } 

     case 246: {  // нажата клавиша DN (вниз)
                  if (temp2<15) temp2++;
                  break; } 
                                 
     case 250: {  // нажата клавиша EXIT (возврат в вышестоящее меню) 
                  temp2=0; // номер микшера для редактирования 
                  temp3=0; // режим редактора
                  temp4=0;
                  temp5=0;
                  temp1=0; // признак первого запуска
                  resetKeyReader(); // сброс клавиатуры
                  menu_exe=0;
                  break; }
               
     case 252: {  // нажата клавиша MENU/ENT (переход в нижестоящее меню/вызов процедуры)
                  fileDelete(temp2);
                  temp2=0; // номер микшера для редактирования 
                  temp3=0; // режим редактора
                  temp4=0;
                  temp5=0;
                  temp1=0; // признак первого запуска
                  resetKeyReader(); // сброс клавиатуры
                  menu_exe=0;                  
                  break; } 

     case 222: {  // нажата клавиша '-' (двигаемся вправо)
                  break; }

     case 190: { //нажата клавиша   '+' (двигаемся влево)
                  break; }
   } // конец блока работы с нажатыми клавишами
  

}
/**
             М Е Н Ю   З А П И С Ь   М О Д Е Л И   Н А    V D I S K
**/
void menu_MODEL_SAVE_AS() {
unsigned char i, offs, mode, tmp; // временные переменные цикла и смещения 

if (temp1==0) { // первый запуск
  temp1=1; // флаг что первый запуск произведен
  temp2=0; // номер выбранного файла
}
// печатаем заголовок
LCD_setxy(0,0); LCD_wrsf("     SAVE MODEL AS..     ",1);

LCD_setxy(0,2); LCD_wrsf("NN TYPE   MODELNAME SIZE ",0);

if (temp2>4) offs=temp2-4; else offs=0;

  for (i=0; i<5; i++) { \\ цикл вывода имен сохраненных моделей
     LCD_setxy(0,3+i);
     if (temp2==(i+offs)) mode=1; else mode=0; // выделение курсора
     LCD_dec((unsigned char)(i+offs),2,mode); // печатаем номер модели
     LCD_char(' ', mode); // печатаем пробел
  
     if (fileToRead(i+offs)==0) { // файл существует и открыт
       // первый байт - тип модели
       tmp=fileRead(); 
       LCD_wrsf(MODEL_TYPE[tmp],mode); // печатаем тип модели
    
       LCD_char(' ',mode); // печатаем пробел
       // далее следует имя модели
       for (tmp=0;tmp<8; tmp++) { // печатаем имя модели
          LCD_char(fileRead(),mode);
       }
    
       LCD_char(' ',mode);
            LCD_char(' ', mode);
                 LCD_char(' ', mode);
                      LCD_char(' ', mode);
    
       // печатаем размер модели
       tmp=fileSize(i+offs);
       LCD_dec(tmp,2,mode);    
     }
  }
   mode=get_mnu_keys(); // прочитаем нажатые клавиши навигации по меню
   switch (mode) { // выбираем нажатые клавиши

     case 238: { // нажата клавиша UP (вверх)
                  if (temp2>0) temp2--;
                  break; } 

     case 246: {  // нажата клавиша DN (вниз)
                  if (temp2<15) temp2++;
                  break; } 
                                 
     case 250: {  // нажата клавиша EXIT (возврат в вышестоящее меню) 
                  temp2=0; // номер микшера для редактирования 
                  temp3=0; // режим редактора
                  temp4=0;
                  temp5=0;
                  temp1=0; // признак первого запуска
                  resetKeyReader(); // сброс клавиатуры
                  menu_exe=0;
                  break; }
               
     case 252: {  // нажата клавиша MENU/ENT (переход в нижестоящее меню/вызов процедуры)
                  E_CurModelNum=temp2;
                  SaveModel(E_CurModelNum);
                  if (printMess==0) {
                     // выдаем пользователю об этом предупреждение
                     messStr1="       FILE SAVED !      "; 
                     messStr2="";
                     messStr3="";
                     messStr4="";
                     messStr5="";
                     printMess=1;
                  }
                  temp2=0; // номер микшера для редактирования 
                  temp3=0; // режим редактора
                  temp4=0;
                  temp5=0;
                  temp1=0; // признак первого запуска
                  resetKeyReader(); // сброс клавиатуры
                  menu_exe=0;                  
                  break; } 

     case 222: {  // нажата клавиша '-' (двигаемся вправо)
                  break; }

     case 190: { //нажата клавиша   '+' (двигаемся влево)
                  break; }
   } // конец блока работы с нажатыми клавишами
  
 }  
 
// ЗАПИСЬ МОДЕЛИ
void menu_MODEL_SAVE() {
unsigned char mode;

LCD_setxy(0,0);  LCD_wrsf("   SAVE CURRENT MODEL    ",1);

LCD_setxy(0,2);  LCD_wrsf("to process press - MENU >",0);

LCD_setxy(0,6);  LCD_wrsf(" to cancel press EXIT   >",0);

   mode=get_mnu_keys(); // прочитаем нажатые клавиши навигации по меню
   switch (mode) { // выбираем нажатые клавиши

     case 238: { // нажата клавиша UP (вверх)
                  break; } 

     case 246: {  // нажата клавиша DN (вниз)
                  break; } 
                                 
     case 250: {  // нажата клавиша EXIT (возврат в вышестоящее меню) 
                  temp2=0; // номер микшера для редактирования 
                  temp3=0; // режим редактора
                  temp4=0;
                  temp5=0;
                  temp1=0; // признак первого запуска
                  resetKeyReader(); // сброс клавиатуры
                  menu_exe=0;
                  break; }
               
     case 252: {  // нажата клавиша MENU/ENT (переход в нижестоящее меню/вызов процедуры)
                  if (E_CurModelNum<16) SaveModel(E_CurModelNum); // записываем модель под прежним номером
                  temp2=0; // номер микшера для редактирования 
                  temp3=0; // режим редактора
                  temp4=0;
                  temp5=0;
                  temp1=0; // признак первого запуска
                  if (printMess==0) {
                     // выдаем пользователю об этом предупреждение
                     messStr1="       FILE SAVED !      "; 
                     messStr2="";
                     messStr3="";
                     messStr4="";
                     messStr5="";
                     printMess=1;
                  }                  
                  resetKeyReader(); // сброс клавиатуры
                  menu_exe=0;                  
                  break; } 

     case 222: {  // нажата клавиша '-' (двигаемся вправо)
                  break; }

     case 190: { //нажата клавиша   '+' (двигаемся влево)
                  break; }
   } // конец блока работы с нажатыми клавишами
}

// ФОРМАТИРОВАНИЕ ДИСКА
void menu_formatVDisk() {
unsigned char mode;

LCD_setxy(0,0);  LCD_wrsf("    FORMAT V-DISK ?      ",1);

LCD_setxy(0,2);  LCD_wrsf("to process press - MENU >",0);

LCD_setxy(0,4);  LCD_wrsf("All data must be deleted!",2);

LCD_setxy(0,6);  LCD_wrsf(" to cancel press EXIT   >",0);

   mode=get_mnu_keys(); // прочитаем нажатые клавиши навигации по меню
   switch (mode) { // выбираем нажатые клавиши

     case 238: { // нажата клавиша UP (вверх)
                  break; } 

     case 246: {  // нажата клавиша DN (вниз)
                  break; } 
                                 
     case 250: {  // нажата клавиша EXIT (возврат в вышестоящее меню) 
                  temp2=0; // номер микшера для редактирования 
                  temp3=0; // режим редактора
                  temp4=0;
                  temp5=0;
                  temp1=0; // признак первого запуска
                  resetKeyReader(); // сброс клавиатуры
                  menu_exe=0;
                  break; }
               
     case 252: {  // нажата клавиша MENU/ENT (переход в нижестоящее меню/вызов процедуры)
                  formatVDisk();
                  temp2=0; // номер микшера для редактирования 
                  temp3=0; // режим редактора
                  temp4=0;
                  temp5=0;
                  temp1=0; // признак первого запуска
                  if (printMess==0) {
                                     // выдаем пользователю об этом предупреждение
                     messStr1="   V-DISK  FORMATTED !   ";

                     messStr2=" File operations enabled";
                     messStr3=" ";
                     messStr4=" ";
                     messStr5=" ";
                     printMess=1;                   
                  }
                  resetKeyReader(); // сброс клавиатуры
                  menu_exe=0;                  
                  break; } 

     case 222: {  // нажата клавиша '-' (двигаемся вправо)
                  break; }

     case 190: { //нажата клавиша   '+' (двигаемся влево)
                  break; }
   } // конец блока работы с нажатыми клавишами
}


// запрашиваем нужно ли сохранить изменившуюся модель
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

   mode=get_mnu_keys(); // прочитаем нажатые клавиши навигации по меню
   switch (mode) { // выбираем нажатые клавиши

     case 238: { // нажата клавиша UP (вверх)
                  break; } 

     case 246: {  // нажата клавиша DN (вниз)
                  break; } 
                                 
     case 250: {  // нажата клавиша EXIT (возврат в вышестоящее меню) 
                  resetKeyReader(); // сброс клавиатуры
                  menu_exe=0;
                  disp_mode=2;
                  break; }
               
     case 252: {  // нажата клавиша MENU/ENT (переход в нижестоящее меню/вызов процедуры)
                   if (E_CurModelNum<16) { 
                      SaveModel(E_CurModelNum);
                      menu_exe=0;
                      disp_mode=2;
                   }  
                      else {
                        menu_proc=menu_MODEL_SAVE_AS;
                      }
                  break; } 

     case 222: {  // нажата клавиша '-' (двигаемся вправо)
                  break; }

     case 190: { //нажата клавиша   '+' (двигаемся влево)
                  break; }
   } // конец блока работы с нажатыми клавишами
}


// процедура вывода информации о cвободном месте на V-Disk - - - - - - - - - - - - - - - - - - - - - - - -
void menu_VDISK_INFO(void) {
unsigned char mode, i;

LCD_setxy(0,0);  LCD_wrsf("       V-DISK  INFO      ", 1);

LCD_setxy(0,3);  LCD_wrsf("V-Disk sector col: ", 0); LCD_dec(VDISKSIZE/E_ClusterSize,3,1);

  mode=freesp; // берем номер первого свободного кластера
  i=0;
  while (mode!=255) {
    i++;
    mode=VDISK[(unsigned int)mode*E_ClusterSize];
  } 

LCD_setxy(0,5);  LCD_wrsf(" free space: ", 0); LCD_dec(i,3,1);

   mode=get_mnu_keys(); // прочитаем нажатые клавиши навигации по меню
   switch (mode) { // выбираем нажатые клавиши

     case 238: { // нажата клавиша UP (вверх)
                  break; } 

     case 246: {  // нажата клавиша DN (вниз)
                  break; } 
                                 
     case 250: {  // нажата клавиша EXIT (возврат в вышестоящее меню) 
                  resetKeyReader(); // сброс клавиатуры
                  menu_exe=0;
                  break; }
               
     case 252: {  // нажата клавиша MENU/ENT (переход в нижестоящее меню/вызов процедуры)
                  break; } 

     case 222: {  // нажата клавиша '-' (двигаемся вправо)
                  break; }

     case 190: { //нажата клавиша   '+' (двигаемся влево)
                  break; }
   } // конец блока работы с нажатыми клавишами

}


// процедура вывода информации о передатчике - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void menu_CODER_INFO(void) {
unsigned char mode;

LCD_setxy(0,0);  LCD_wrsf("   V-CODER  ver 0.99b    ", 1);
LCD_setxy(0,1);  LCD_wrsf("author: Vitaly V Gorbukov", 0);

LCD_setxy(0,3);  LCD_wrsf(" build: 2324  17.08.2012 ", 0);
LCD_setxy(0,4);  LCD_wrsf(" first use at 21.07.2010 ", 0);

LCD_setxy(0,6);  LCD_wrsf("   for support mail to   ", 0);
LCD_setxy(0,7);  LCD_wrsf("   gorbukov@yandex.ru    ", 1);

   mode=get_mnu_keys(); // прочитаем нажатые клавиши навигации по меню
   switch (mode) { // выбираем нажатые клавиши

     case 238: { // нажата клавиша UP (вверх)
                  break; } 

     case 246: {  // нажата клавиша DN (вниз)
                  break; } 
                                 
     case 250: {  // нажата клавиша EXIT (возврат в вышестоящее меню) 
                  resetKeyReader(); // сброс клавиатуры
                  menu_exe=0;
                  break; }
               
     case 252: {  // нажата клавиша MENU/ENT (переход в нижестоящее меню/вызов процедуры)
                  break; } 

     case 222: {  // нажата клавиша '-' (двигаемся вправо)
                  break; }

     case 190: { //нажата клавиша   '+' (двигаемся влево)
                  break; }
   } // конец блока работы с нажатыми клавишами
}

