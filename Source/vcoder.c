#include <mega64.h>
#include <delay.h>
#include <stdio.h>
#include <math.h>
#include "hardware.h" 
#include "model_inf.h"
#include "lcd.c"
#include "vdisk.c" 
#include "mn_display_new.c"
#include "menu_procedures.h"

eeprom unsigned char E_CurModelNum; // номер выбранной модели

eeprom unsigned char E_eventStop;   // событие по которому останавливаем таймер
eeprom unsigned char PPM_capture; // признак включения захвата PPM сигнала
eeprom unsigned char E_var3;      // формат сигнала PPM 0 - прямой, 255 - инверсный
eeprom unsigned char E_var4;      // контрастность экрана
eeprom unsigned char E_trim_press_time; // задержка на нажатие кнопки тримера
eeprom unsigned char E_nulTrimBeep; // E_var5; сигнал о нахождении триммера в нуле

eeprom unsigned char E_var11; // калибровочное значение батареи
eeprom unsigned char E_var12; // раскладка стиков mode\mode2

eeprom unsigned int  E_vari2;
eeprom unsigned int  E_vari3;
eeprom unsigned int  E_vari4;

eeprom unsigned int  E_vari5;
eeprom unsigned int  E_vari6;
eeprom unsigned int  E_vari7;
eeprom unsigned int  E_vari8;
eeprom unsigned int  E_vari9;
eeprom unsigned int  E_vari10;

eeprom unsigned char E_eventStart; // событие по которому стартует таймер модели

unsigned int LightOn; // время горения подсветки
unsigned char ppmStop; // признак останова генерации PPM
unsigned char flyTimerOn; // признак того что полетный таймер включен
unsigned int flyCurrTimer; // текущее значение полетного таймера
unsigned int OnCurrTimer; // значение полетного таймера при котором его включили
unsigned char TimerEnd; // признак того что таймер уже закончил свой отсчет
unsigned char TimerEndBeepCounter; // счетчик писков в конце счета таймера

eeprom unsigned char E_beep1min; // признак необходимости давать гудок каждую минуту работы таймера
eeprom unsigned char E_beep2sec; // признак необходимости давать гудки каждые 2 секунды в последнюю минуту

eeprom unsigned int E_UCHmid[7]; // средние значения аналоговых UCH каналов в EEPROM
eeprom unsigned int E_UCHmin[7]; // минимальные значения аналоговых UCH каналов в EEPROM
eeprom unsigned int E_UCHmax[7]; // максимальные значения аналоговых UCH каналов в EEPROM

unsigned char ClusterSize; // размер кластера файловой системы в RAM

eeprom unsigned char E_SOUND_ON; // признак того что звук включен 
unsigned char SOUND_ON; // признак того что звук включен

eeprom unsigned char E_key_press_time; // количество циклов после которого клавиша считается нажатой
eeprom unsigned char E_key_repress_time; // количество циклов после которого у нажатой клавиши идет автоповтор

unsigned char key_press_time; // количество циклов после которого клавиша считается нажатой
unsigned char key_repress_time; // количество циклов после которого у нажатой клавиши идет автоповтор

unsigned char trim_press_time; // задержка на нажатие клавиши тримеров
 
unsigned int UCH_VALUES[14];   // Считанные абсолютные значения UCH
signed  char UCH_VAL_PROC[14]; // Процентные значения каналов UCH

eeprom unsigned int E_battMin; // минимально допустимое напряжение на батарее передатчика
unsigned int battMin;    // минимально допустимое напряжение на батарее передатчика
unsigned int batt;       // напряжение на батарее передатчика (текущее)

// калибровочные данные аналоговых каналов
unsigned int UCHmid[7]; // средние значения аналоговых UCH каналов
unsigned int UCHmin[7]; // минимальные значения аналоговых UCH каналов
unsigned int UCHmax[7]; // максимальные значения аналоговых UCH каналов

unsigned int FMODE_NUM; // текущий полетный режим
 
unsigned int LCH_LEN[16]; // массив длительностей LCH каналов
unsigned int OLD_LCH_LEN[16]; // массив длительностей LCH каналов предыдущего пакета 
                              // (нужно для организации тормоза канала и микширования с кривыми)

unsigned char PPM_CUR_CH_NUM; // текущий номер PPM канала на выдачу
unsigned int CH_PPM[8]; // длительности канальных импульсов для выдачи на передатчик
unsigned int PPM_PAUSE; // длительность синхропаузы
//unsigned int CAP_PPM[8]; // длительности захваченного сигнала PPM
unsigned char mch[8]; // память на предыдущий выданный канал при мультипликсировании

unsigned int CURVE_POINT[16][9][2]; // массив точек кривой текущего выбранного режима

unsigned char BLINK_TIMER; // переменная для организации эффекта мигания
unsigned char BLINK; // одно из состояний эффекта мигания

flash unsigned char *messStr1; // массив строк для печати сообщений пользователю
flash unsigned char *messStr2; // массив строк для печати сообщений пользователю
flash unsigned char *messStr3; // массив строк для печати сообщений пользователю
flash unsigned char *messStr4; // массив строк для печати сообщений пользователю
flash unsigned char *messStr5; // массив строк для печати сообщений пользователю

unsigned char messRetCode; // код завершения операции печати сообщений

unsigned char printMess; // флаг того что нужно напечатать сообщение

unsigned int     outx1, outx2, outx3, outy1, outy2, outy3, outkk; // отладка

unsigned char ModelChange; // признак того что модель была изменена

unsigned char mixercount;  // общее количество микшеров в режиме
unsigned char mixtochan;   // количество обсчитываемых микшеров в одном канале
unsigned char mixtochanlast;   // количество обсчитываемых микшеров в последнем канале


// подсчет количества микшеров в полетном режиме
unsigned char getMixCount(unsigned char fmode) {
unsigned char i;

   for (i=0;i<39;i++) { // перебираем в цикле микшеры каналов
         // проверяем - если микшер включен...
      if (rmodel.FMODE[fmode].MIXER[i].MIX_TYPE.ACTIVE==0) {
        break;
      }
   }
   return i;
}

void MixerCalc(unsigned char mixstart, unsigned char mixend) { // - - - - - - - - - процедура расчета длительности заданного канала

unsigned int i; // счетчик цикла
unsigned char sw, swon; // выключатель и инверсия микшера

unsigned char soursech, destinch; // каналы микшера

unsigned long int chval; // значение канала источника
unsigned long int chmin, chmid, chmax; // точки канала источника
unsigned long int dchmin, dchmid, dchmax; // точка канала получателя
unsigned long int soursesc, destsc; // размер шкалы источника и получателя
unsigned long int res; // результирующее значение для шкалы получателя

unsigned char signres; // знак результата микширования

signed char mixproc; // процент микширования канала
unsigned char mixuch; // номер UCH содержащего процент микширования

   for (i=mixstart;i<mixend;i++) { // перебираем в цикле микшеры каналов

         // проверяем - если микшер включен...
      if (rmodel.FMODE[FMODE_NUM].MIXER[i].MIX_TYPE.ACTIVE==1) {
      
         //проверяем используется ли в микшере выключатель
         if (rmodel.FMODE[FMODE_NUM].MIXER[i].MIX_TYPE.MIX_SW==1) {
            // используется выключатель 

            sw=rmodel.FMODE[FMODE_NUM].MIXER[i].MIX_TYPE.UCH_SW+7;
            if (UCH_VALUES[sw]==1) { //выключатель включен
               // накладываем инверсию
               if (rmodel.FMODE[FMODE_NUM].MIXER[i].MIX_TYPE.SW_INV==0) swon=1;
                  else swon=0; 
            } 
               else { // выключатель выключен
                 // накладываем инверсию
                 if (rmodel.FMODE[FMODE_NUM].MIXER[i].MIX_TYPE.SW_INV==0) swon=0;
                    else swon=1; 
               }
         } 
            else { // выключатель не используется
               swon=1;
            }
      } else swon=0;
      
      if (swon==1) { // микшер включен всегда или выключателем...
      
         destinch=rmodel.FMODE[FMODE_NUM].MIXER[i].CH_NUM.CH_DEST; // канал получатель
         dchmid=rmodel.FMODE[FMODE_NUM].LCH_MIDLE[destinch];       // среднее значение канала
         dchmin=rmodel.CHANNELS.CH_EPL[destinch];                  // минимальное  значение канального импульса
         dchmax=rmodel.CHANNELS.CH_EPR[destinch];                  // максимальное значение канального импульса

         soursech=rmodel.FMODE[FMODE_NUM].MIXER[i].CH_NUM.CH_SOURSE; // номер канала источника
         // загружаем значения канала источника        
         if (rmodel.FMODE[FMODE_NUM].MIXER[i].MIX_TYPE.SOURSE_TYPE==1) {
            // наш канал LCH
            chval=OLD_LCH_LEN[soursech]; // LCH_LEN[soursech]; // берем значение канала
            chmid=rmodel.FMODE[FMODE_NUM].LCH_MIDLE[soursech]; // среднее значение канала
            chmin=rmodel.CHANNELS.CH_EPL[soursech];            // минимальное  значение канального импульса
            chmax=rmodel.CHANNELS.CH_EPR[soursech];            // максимальное значение канального импульса
         }
            else {
               // наш канал UCH
               chval=UCH_VALUES[soursech]; // берем значение UCH
               if (soursech<7) { // имеем дело с аналоговым UCH
                  chmid=UCHmid[soursech]; // среднее значение
                  chmin=UCHmin[soursech]; // минимальное значение
                  chmax=UCHmax[soursech]; // максимальное значение
               } 
                 else { // имеем дело с дискретным UCH
                    if (soursech==7) { // выключатель FMODE (трехпозиционный)
                      chmin=0;
                      chmid=0;
                      chmax=1;
                      chval=1;                    
                    } 
                        else {  // остальные выключатели
                          chmid=0;
                          chmin=0;
                          chmax=1;                          
                        }
                 }
                 
            }
         // теперь получим коэффициент микширования канала
         if (rmodel.FMODE[FMODE_NUM].MIXER[i].MIX_TYPE.PROC_SOURSE==1) {
            // процент микширования берем из UCH
            mixuch=rmodel.FMODE[FMODE_NUM].MIXER[i].MIX_VAL & 0x0F;
            if (mixuch==7) mixproc=100; else mixproc=UCH_VAL_PROC[mixuch]; // берем процент микширования из канала
                         
            // инверсия значения микширования если в этом есть необходимость
            if ((rmodel.FMODE[FMODE_NUM].MIXER[i].MIX_VAL & 0x10)!=0) {
                 mixproc=-mixproc;             
            }
         } 
           else { // процент микширования фиксированный
               mixproc=rmodel.FMODE[FMODE_NUM].MIXER[i].MIX_VAL;
           }    

          //  !!!!!!!!!!!!!!!!!!  НОВАЯ ПРОЦЕДУРА РЕВЕРСА КАНАЛА
            
          if (rmodel.CHANNELS.LCH_REV[destinch]==1) { // реверс канала !!
               mixproc=-mixproc;
          }
          //  !!!!!!!!!!!!!!!!!! 

         // теперь микшируем
         
         // определяем размерность шкал
         if (chval>chmid) { // если значение в правой части шкалы
            soursesc=chmax-chmid; // размер шкалы справа - источник
            chval=chval-chmid;
            if (mixproc>0) {
              destsc=dchmax-dchmid; // размер шкалы справа - получатель
              signres=1;
            } 
               else {
                  destsc=dchmid-dchmin; // размер шкалы слева - получатель
                  signres=0;
                  mixproc=-mixproc;
               }

         }  
            else { 
               chval=chmid-chval;
               soursesc=chmid-chmin; // размер шкалы слева
               
               if (mixproc<0) {
                  destsc=dchmax-dchmid; // размер шкалы справа
                  signres=1;
                  mixproc=-mixproc;
               } 
                  else {
                    destsc=dchmid-dchmin; // размер шкалы слева
                    signres=0;
                  }
            }

         
         res=(destsc*chval*mixproc)/(soursesc*100); // рассчитываем значение  новой шкалы
//         chval1=destinch;
         if (signres==1) 
            LCH_LEN[destinch]=LCH_LEN[destinch]+(unsigned int)res; 
            else
              LCH_LEN[destinch]=LCH_LEN[destinch]+-(unsigned int)res;     
      }       
   }     
}

// процедура расчета ординат точек кривых для текущего полетного режима
void CalcCurveORD(void) {
unsigned long int ti, til, tir; // временые переменные
unsigned char tc, tc1; // временная переменная
signed   char tsc; // временная переменная со знаком

   for (tc1=0; tc1<16; tc1++) {
      //           +---------номер канала
      //           |   +-----номер точки кривой
      //           |   |  +-- при 0 ордината точки, при 1 абцисса точки
      //           |   |  |  
      CURVE_POINT[tc1][0][0]=rmodel.CHANNELS.CH_EPL[tc1]; // нулевая (самая левая точка)
   
      ti=( rmodel.FMODE[FMODE_NUM].LCH_MIDLE[tc1] - CURVE_POINT[tc1][0][0] ) / 4; // шаг точек слева
   
      for (tc=1;tc<4;tc++) CURVE_POINT[tc1][tc][0]= CURVE_POINT[tc1][tc-1][0] + ti; // точки слева от середины

   
      CURVE_POINT[tc1][4][0]=rmodel.FMODE[FMODE_NUM].LCH_MIDLE[tc1]; // средняя точка

      ti=(  rmodel.CHANNELS.CH_EPR[tc1] - CURVE_POINT[tc1][4][0] ) / 4; // шаг точек справа
   
      for (tc=5; tc<8; tc++) CURVE_POINT[tc1][tc][0]= CURVE_POINT[tc1][tc-1][0] + ti; // точки справа от середины  

      CURVE_POINT[tc1][8][0]=rmodel.CHANNELS.CH_EPR[tc1]; // нулевая (самая левая точка)
      
      // расчет абцисс точек кривой
      til=CURVE_POINT[tc1][4][0] - CURVE_POINT[tc1][0][0]; // определим диапазон шкалы слева
      tir=CURVE_POINT[tc1][8][0] - CURVE_POINT[tc1][4][0]; // определим диапазон шкалы справа
      
      for (tc=0; tc<9; tc++) { // цикл по всем точкам
         tsc=rmodel.FMODE[FMODE_NUM].LCH_CURVE[tc1].point[tc]; // берем значение кривой
         if (tsc>=0) // расчет если процент микширования положителен 
           CURVE_POINT[tc1][tc][1]=CURVE_POINT[tc1][4][0] + (tir * tsc) / 100;
           else { // расчет если процент микширования отрицателен
              tsc=-tsc;
              CURVE_POINT[tc1][tc][1]=CURVE_POINT[tc1][4][0] - (til * tsc) / 100;              
           }        
      }
   } 
}

//--------------------------------------------------------------------------------------------------
//                                                     Процедура чтения данных выбранного канала ADC
// Входной параметр: adc_input - номер канала для чтения
// Выходной параметр: считанное значение
unsigned int read_adc(unsigned char adc_input) {
  ADMUX=adc_input|ADC_VREF_TYPE;
  delay_us(10);
  ADCSRA|=0x40;               
  while ((ADCSRA & 0x10)==0);
  ADCSRA|=0x10; // Stop
  return ADCW;
}


//--------------------------------------------------------------------------------------------------
//                                           Процедура чтения значений пользовательских каналов
unsigned char FMODE_OLD;
void read_UCH_values(void) {
int i; 
signed int s;

  for(i=0; i<7; i++) {                            // в цикле перебираем аналоговые каналы
    if (E_var12==2)  // для второй моды
       switch (i) {
         case 1 : { UCH_VALUES[i]=read_adc(2); break; }
         case 2 : { UCH_VALUES[i]=read_adc(1); break; }
         default: UCH_VALUES[i]=read_adc(i);            // и запоминаем их абсолютные значения
       } else 
          if (E_var12==3)  // для третьей моды
             switch (i) {
               case 1 : { UCH_VALUES[i]=read_adc(2); break; }
               case 2 : { UCH_VALUES[i]=read_adc(1); break; }
               case 0 : { UCH_VALUES[i]=read_adc(3); break; } // меняем местами элероны и 
               case 3 : { UCH_VALUES[i]=read_adc(0); break; } // руль направления
               default: UCH_VALUES[i]=read_adc(i);            // и запоминаем их абсолютные значения                  
          } else
          if (E_var12==4)  // для четвертой моды
             switch (i) {
               case 0 : { UCH_VALUES[i]=read_adc(3); break; } // меняем местами элероны и РН 
               case 3 : { UCH_VALUES[i]=read_adc(0); break; } // меняем местами элероны и РН

               default: UCH_VALUES[i]=read_adc(i);            // и запоминаем их абсолютные значения                  
          } else    UCH_VALUES[i]=read_adc(i); // для первой моды
    
    
  
    // дополнительная автокалибровка каналов на случай если полученные значения лучше калибровочных !
    if (UCH_VALUES[i]>UCHmax[i]) UCHmax[i]=UCH_VALUES[i];
    if (UCH_VALUES[i]<UCHmin[i]) UCHmin[i]=UCH_VALUES[i];

    // рассчитываем значение органов управления   
    s=((signed int)rmodel.UCH[i].UCH_RIGHT-rmodel.UCH[i].UCH_LEFT)/2; // диапазон изменения значения канала для половины
                                                 // хода стика   
    if (UCH_VALUES[i]>UCHmid[i]) {

       // положительное процентное значение UCH - максимальное значение в % берем из настроек UCH
       UCH_VAL_PROC[i]=rmodel.UCH[i].UCH_LEFT+s+(UCH_VALUES[i]-UCHmid[i]) * s / (UCHmax[i]-UCHmid[i]) ;
    } 
       else {
          // отрицательное процентное значение UCH - минимальное значение в % берем из настроек UCH
          UCH_VAL_PROC[i]=rmodel.UCH[i].UCH_LEFT+(UCH_VALUES[i]-UCHmin[i])*s/(UCHmid[i]-UCHmin[i]);     
       }

    // накладываем триммеры на аналоговые каналы управления
    if (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[i]>=0) { // если триммер канала больше нуля
           UCH_VALUES[i]=UCH_VALUES[i]+((unsigned int)rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[i])*2;
       if (UCH_VALUES[i]>UCHmax[i]) UCH_VALUES[i]=UCHmax[i];    
    }
       else {
          if (UCH_VALUES[i]>(2*((unsigned int)(-rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[i])))) // и значение uch больше триммера
               UCH_VALUES[i]=UCH_VALUES[i]-(2*((unsigned int)(-rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[i])));
               else UCH_VALUES[i]=UCHmin[i]; 
          if (UCH_VALUES[i]<UCHmin[i]) UCH_VALUES[i]=UCHmin[i];
       }

  }
  
// Читаем значения дискретных каналов
  if (SW_Id1==0) { UCH_VALUES[7]=0; } else UCH_VALUES[7]=1;
  if (!SW_Id2) { UCH_VALUES[7]=2; }
                                                     
  if (UCH_VALUES[7]<=(rmodel.FMODE_COUNT-1)) // - - - - - новое переключение полетных режимов 
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
      CalcCurveORD(); // рассчитаем ординаты точек кривых                  
      FMODE_OLD=FMODE_NUM;
  }
  
  UCH_VALUES[8]=SW_Gear;     if (SW_Gear==1) { UCH_VAL_PROC[8]=rmodel.UCH[8].UCH_RIGHT; 
                                 } else { UCH_VAL_PROC[8]=rmodel.UCH[8].UCH_LEFT; }
                                   
  UCH_VALUES[9]=SW_Trainer;  if (SW_Trainer==1) { UCH_VAL_PROC[9]=rmodel.UCH[9].UCH_RIGHT; 
                                 } else { UCH_VAL_PROC[9]=rmodel.UCH[9].UCH_LEFT; }
                                 
  // включаем полетный таймер
  if (flyTimerOn==0) {
     if (E_eventStart==8) {
         // старт по нажатию кнопки Trainer
         if (SW_Trainer==1) {
               flyTimerOn=1;
               OnCurrTimer=flyCurrTimer;
         }     
     }
       else { // старт по положению стика на выбранном канале
               if (CH_PPM[E_eventStart]>(rmodel.CHANNELS.CH_EPL[E_eventStart]+
                                      (rmodel.CHANNELS.CH_EPR[E_eventStart]-
                                        rmodel.CHANNELS.CH_EPL[E_eventStart])*20/100)) { 
                       flyTimerOn=1;
                       OnCurrTimer=flyCurrTimer;
                    }        
       }
  }

  // выключаем полетный таймер
  if (flyTimerOn==1) {
    if ((E_eventStop<8) && (CH_PPM[E_eventStop]<(rmodel.CHANNELS.CH_EPL[E_eventStop]+
                                      (rmodel.CHANNELS.CH_EPR[E_eventStop]-
                                        rmodel.CHANNELS.CH_EPL[E_eventStop])*10/100)))
     flyTimerOn=0;
  }
 
  UCH_VALUES[10]=SW_ThroCut; if (SW_ThroCut==1) { UCH_VAL_PROC[10]=rmodel.UCH[10].UCH_RIGHT; 
                                 } else { UCH_VAL_PROC[10]=rmodel.UCH[10].UCH_LEFT; }
                                   
  UCH_VALUES[11]=SW_AileDR;  if (SW_AileDR==1) { UCH_VAL_PROC[11]=rmodel.UCH[11].UCH_RIGHT; 
                                 } else { UCH_VAL_PROC[11]=rmodel.UCH[11].UCH_LEFT; }
                                   
  UCH_VALUES[12]=SW_ElevDR;  if (SW_ElevDR==1) { UCH_VAL_PROC[12]=rmodel.UCH[12].UCH_RIGHT; 
                                 } else { UCH_VAL_PROC[12]=rmodel.UCH[12].UCH_LEFT; }
                                   
  UCH_VALUES[13]=SW_RuddDR;  if (SW_RuddDR==1) { UCH_VAL_PROC[13]=rmodel.UCH[13].UCH_RIGHT; 
                                 } else { UCH_VAL_PROC[13]=rmodel.UCH[13].UCH_LEFT; }
}

// -------------------------------------------------------------------------------------------------
//                                                                           Процедура опроса клавиш
//
unsigned char ready_key=0; // готовый код клавиши для чтения
unsigned char rkey=0; // код нажатой клавиши
unsigned char presstime=0; // время нажатия
unsigned int keyhold=0; // признак удержания клавиши
unsigned char keyhold_t=0; // временная переменная
unsigned char keyhold_wait=0; // переменная свидетельствующая об ожидании отпускании кнопки

unsigned char BEEP; // счетчик звучания 
// процедура получения кода клавиш для обработки
unsigned char get_mnu_keys(void) {
  unsigned char t;

  t=ready_key & 0xFE;  // сохраняем код перед сбросом   

  if (t!=254) {
     ready_key=254; // сбрасываем код нажатых клавиш
     BEEP=key_repress_time-2;
     if (SOUND_ON==1) Buzzer=1;  // если звук разрешен то включаем динамик
     Light=1;
     LightOn=500; // время горения подсветки

  }
  return t; // возвращаем код клавиш 
}

// процедура сброса состояния процедуры читающей состояние клавиатуры
void resetKeyReader() {
    ready_key=0; // готовый код клавиши для чтения
    rkey=0; // код нажатой клавиши
    presstime=0; // время нажатия
    keyhold=0; // признак удержания клавиши
    keyhold_t=0; // временная переменная
}

unsigned char trimkey; // удерживаемая кнопка тримеров
unsigned char trimhold; // время удержания тримера
unsigned char readytrim; // готовый код тримера

// получение кода нажатой кнопки триммера
unsigned char get_trim_key() {
unsigned char t;
  t=readytrim;
  if (t!=255) {
     readytrim=255; // сбрасываем код нажатых клавиш
     BEEP=trim_press_time-3;
     if (SOUND_ON==1) Buzzer=1;  // если звук разрешен то включаем динамик
     Light=1;
     LightOn=1500; // время горения подсветки
  }
  return t; // возвращаем код тримера 
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - процедура опроса кнопок триммеров
void read_trim() {
unsigned char tempkey;

  tempkey=PIND; // прочитаем нажатые кнопки

  if (tempkey!=255) {
       
       if (trimkey==tempkey) { // кнопка удерживается !
          trimhold++; // увеличиваем счетчик удержания
          if (trimhold==trim_press_time) { // если кнопка нажата минимально необходимое время
            readytrim=trimkey; // регистрируем нажатие
            trimhold=0;
          } 
             else { trimkey=tempkey; }
       } 
          else { trimkey=tempkey; trimhold=0; }
  } 
     else { trimkey=255; trimhold=0; }
}

// процедура опроса клавиш, вызывается 50 раз в секунду из прерывания
void read_key() {
// Процедура должна обеспечивать опрос клавиатуры с задержкой от дребезга и автоматическим повтором
// в случае непрерывного нажатия на клавиши
unsigned char tempkey;

// Опрос клавиш меню
  tempkey=PINB | 128; // прочитаем нажатые клавиши
                          
  if (tempkey!=254) { // есть нажатые клавиши?

     if (keyhold_wait==0) {     // если мы не ожидаем отпускания то работаем

        if (tempkey==rkey) { // код нажатой клавиши совпадает с хранимым? 

           presstime++; // увеличим счетчик удержания

           if (presstime==key_press_time) { // клавиша нажата минимально необходимое время?  
              ready_key=tempkey;            //  регистрация кода клавиши на выдачу

              // если нажата кнопка MENU или EXIT - то автоповтора не будет !
              if ((tempkey==250)||(tempkey==252)) { 
                 keyhold_wait=1;
              }
           }
           
           if (presstime==(key_press_time+key_repress_time)) { // клавиша удерживается
              // генерируем автоповтор
              ready_key=tempkey; // регистрация кода клавиши на выдачу


              if (keyhold_t<9) keyhold_t++; else keyhold=1; // регистрируем факт удержания клавиши
              presstime=key_press_time; // уменьшаем счетчик удержания для подсчета автоповтора 
           }    
        }     
           else { // код нажатой клавиши не совпадает с хранимым
             rkey=tempkey; // запоминаем код
             presstime=0;  // стартуем счетчик удержания клавиши заново
             keyhold=0;
             keyhold_t=0;  
           }
     } 
  } 
     else {  // кнопки не нажаты
       rkey=254;      // сбрасываем временный код нажатой клавиши
       presstime=0; // и время нажатия
       keyhold_wait=0;  // сбрасываем флаг ожидания отпускания кнопки
     }
}

//--------------------------------------------------------------------------------------------------
//                           Прерывание осуществляющее передачу получившейся пачки PPM на передатчик
//
unsigned char impPhase; // фаза импульса на передачу
unsigned long battAvg;  // сумматор значения батареи
unsigned char avgCount; // число просуммированого значения
 
interrupt [TIM1_COMPA] void timer1_compa_isr(void)  { 
unsigned char i, k , n, m; // переменные циклов
signed char   j;
unsigned int chl, bt1;
unsigned long int kk,ev,x1,x2,x3,y1,y2;

if (ppmStop==2) {
    OCR1A=2000;  //заливаем длительность импульса   
    return;
}

if (PPM_CUR_CH_NUM<rmodel.CHANNELS.PPM_CH_COUNT) {

   if (impPhase==0) { // передаем импульс канала

       OCR1A=600;  //заливаем длительность импульса   
       if (E_var3==0) PORTB.0=1;  else  PORTB.0=0;
       impPhase=1;
//       if (PPM_CUR_CH_NUM<4) MixerCalc(PPM_CUR_CH_NUM*10,PPM_CUR_CH_NUM*10+4); // вызываем расчет микшеров
   
   } 
   
   else { // передаем паузу 
       OCR1A=2*CH_PPM[PPM_CUR_CH_NUM]-600;  //заливаем длительность паузы

       if (E_var3==0) PORTB.0=0;  else  PORTB.0=1;
       impPhase=0;

       PPM_PAUSE=PPM_PAUSE+CH_PPM[PPM_CUR_CH_NUM]; // считаем длительности всех импульсов

//       if (PPM_CUR_CH_NUM<4) MixerCalc(PPM_CUR_CH_NUM*10+4,PPM_CUR_CH_NUM*10+10); // вызываем расчет микшеров

//       if (PPM_CUR_CH_NUM<4) { // расчет микшеров

       if ((PPM_CUR_CH_NUM+1)==rmodel.CHANNELS.PPM_CH_COUNT)
            MixerCalc( mixtochan * PPM_CUR_CH_NUM, mixtochan * PPM_CUR_CH_NUM + mixtochan + mixtochanlast);           
       else MixerCalc( mixtochan * PPM_CUR_CH_NUM, mixtochan * PPM_CUR_CH_NUM + mixtochan);
           
//       }
       PPM_CUR_CH_NUM++;
   }
} 
   else {
      OCR1A=2*(22500-PPM_PAUSE); // заливаем длительность паузы

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
   
      PPM_PAUSE=0;     // паузу считаем заново
      PPM_CUR_CH_NUM=0; // номер канала заново

      
      // часть ответственная за формирование новой пачки импульсов PPM - - - - - - - - - - - - -
   
      // пачка PPM в LCH_LEN после работы микшеров 
      
   // проводим обработку полученных LCH
      for (i=0;i<rmodel.CHANNELS.LCH_COUNT;i++) { 

      // выполняем ограничение расходов по каналам в соответствии с крайними точками
         if (LCH_LEN[i]<(32000+rmodel.CHANNELS.CH_EPL[i])) LCH_LEN[i]=32000+rmodel.CHANNELS.CH_EPL[i]; 
         if (LCH_LEN[i]>(32000+rmodel.CHANNELS.CH_EPR[i])) LCH_LEN[i]=32000+rmodel.CHANNELS.CH_EPR[i];         
         LCH_LEN[i]=LCH_LEN[i]-32000;
         
      // обрабатываем канальный тормоз
         if (LCH_LEN[i]<OLD_LCH_LEN[i]) {
             // тормоз вниз 
             if (rmodel.CHANNELS.LCHDELDN[i]!=0) { // тормоз вниз нужен 
                  if ((OLD_LCH_LEN[i]-LCH_LEN[i])>(256-rmodel.CHANNELS.LCHDELDN[i])) 
                        LCH_LEN[i]=OLD_LCH_LEN[i]-(256-rmodel.CHANNELS.LCHDELDN[i]); 
             }
         } 
         
           else {
              // тормоз вверх
              if (rmodel.CHANNELS.LCHDELUP[i]!=0) { // тормоз вверх нужен 
                  if ((LCH_LEN[i]-OLD_LCH_LEN[i])>(256-rmodel.CHANNELS.LCHDELUP[i])) 
                    LCH_LEN[i]=OLD_LCH_LEN[i]+(256-rmodel.CHANNELS.LCHDELUP[i]); 
               }
           }
              
         // накладываем кривые
         if (rmodel.FMODE[FMODE_NUM].LCH_CURVE[i].active!=0) { // если кривая включена
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
            
            // устраним потенциальное деление на ноль
            
             if (((x3-x1)==0) || ((x2-x3)==0)) {
                if (x1==x3) LCH_LEN[i]=y1; else LCH_LEN[i]=y2;             
             } 
               else {               
                 kk=(x3-x1)*1000/(x2-x3); // лямбда
                 outkk=kk;                   
                 ev=(y1*1000) / (1000 + kk) + (kk*y2) / (1000 + kk);
                 outy3=ev;            
                 if (ev<700) ev=2000+ev;
                 LCH_LEN[i]=(unsigned int) ev;
               }
           } else  LCH_LEN[i]=800+k;
         }

         // запоминаем текущую пачку для следующего расчета (использования тормоза)
         OLD_LCH_LEN[i]=LCH_LEN[i];         
      }
      
      //блок обработки фильтров LCH to CH PPM - - - - - - - - - - - - - - - - - - - - - -
      // пачка PPM на выдачу LCH_LEN -> CH_PPM
      for (i=0;i<rmodel.CHANNELS.PPM_CH_COUNT;i++) {
         
         switch (rmodel.CHANNELS.FILTER[i].FILTER_TYPE) {
       
             case 0: { // линейная выдача сигнала
                       CH_PPM[i]=LCH_LEN[i]; 
                       break;
             }

             case 1: { // выдача сигнала по состоянию выключателя
                       if (UCH_VALUES[rmodel.CHANNELS.FILTER[i].VAL1%256]==0) { // выключено  
                         CH_PPM[i]=LCH_LEN[i]; // передаем расчитанное значение
                       }
                         
                         else { // включено
                             // передаем заданное значение
                             j=rmodel.CHANNELS.FILTER[i].VAL1/256; // значение для передачи в канал в %%
                             if (j<0) { // берем нижний предел
                               bt1=-j; // поменяем знак
                               chl=rmodel.FMODE[FMODE_NUM].LCH_MIDLE[i] - 
                               ((rmodel.FMODE[FMODE_NUM].LCH_MIDLE[i]-rmodel.CHANNELS.CH_EPL[i])/100) * bt1;
                                                               
                             } else {  // берем верхний предел
                               bt1=j;
                               chl=rmodel.FMODE[FMODE_NUM].LCH_MIDLE[i] +  
                               ((rmodel.CHANNELS.CH_EPR[i]-rmodel.FMODE[FMODE_NUM].LCH_MIDLE[i])/100) * bt1;
                             
                             }
                             CH_PPM[i]=chl; // выдаем заданное значение
                         }
                       break;
             }

             case 2: { // мультиплексирование каналов
                       // в переменной i - номер канала на выдачу
                       
                       if (mch[i]==0) { // проверяем не нужно ли выдать синхронизатор... 
                            CH_PPM[i]=2150; mch[i]=1; // выдача синхронизатора ! 
                       } 
                         // синхронизатор уже выдавался - выдаем каналы 
                         else {       
/**                            CH_PPM[i]=LCH_LEN[mch[i]-1];
                            mch[i]++;
                            if (mch[i]==5) { mch[i]=0; }
**/                         

                            j=16; // у нас выбор из 16ти каналов
                            chl=rmodel.CHANNELS.FILTER[i].VAL1; // берем информационный байт
                            // в mch[i] - очередной порядковый канал для выдачи 1..4
                            m=mch[i];   
                            // отберем необходимый нам канал - пропустив те каналы которые уже выданы
                            for (k=0; k<m; k++) { // пропустим не нужные каналы
                               n=chl%2;                             
                               chl=chl/2;              // нашли!, переходим на следующий канал
                               if (j!=0) j--;   
                               while ((j!=0) && (n==0)) { // находим номер канала для выдачи 
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

      // готовимся к расчету новой пачки PPM
      
      // выставляем средние точки LCH в соответствии с полетным режимом и триммерами каналов
      for (i=0;i<rmodel.CHANNELS.LCH_COUNT;i++) {
           LCH_LEN[i]=32000+rmodel.FMODE[FMODE_NUM].LCH_MIDLE[i];
      }
      

      read_UCH_values(); // считываем значения UCH каналов
              
      // вспомогательные функции - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

      // переменные для организации мигания модуля lcd
      BLINK_TIMER++;
      if (BLINK_TIMER==25) BLINK=1;                      // полный цикл мигания 2 раза в секунду
      if (BLINK_TIMER==50) { 
         BLINK=0; 
         BLINK_TIMER=0;  
         
         // обрабатываем остановку таймера
         if (flyCurrTimer==0) { 

            flyTimerOn=0; // выключаем таймер

            if (TimerEnd==0) { 
                   // блок включающий подсветку при окончании таймера
                   Light=1;
                   LightOn=1500; // время горения подсветки 
            }      
            
            if ((TimerEnd==0) && (SOUND_ON==1)) { // издаем писки !
               TimerEnd=1; // признак того что таймер кончился
               TimerEndBeepCounter=2; // издать 3 писка
            } 
              else { //писки генерим здесь
                if (TimerEnd==2) {
                   // включим звук 
                   BEEP=50; 
                   Buzzer=1;
                } 
                if (TimerEnd==4) { BEEP=0; Buzzer=0;  } // выключим звук
                if (TimerEnd==5) {
                   if (TimerEndBeepCounter!=0) {
                      TimerEnd=1;
                   }  
                     else { // такие настройки не вызовут звука 
                        TimerEnd=4; 
                        TimerEndBeepCounter=1; 
                     } 
                   TimerEndBeepCounter--;                
                }
                TimerEnd++;                              
              }            
         } 

         // изменение значения полетного таймера
         if ((flyTimerOn==1) && (flyCurrTimer>0)) flyCurrTimer--;
      
         // каждую минуту даем звуковой сигнал таймера
         if ((flyCurrTimer%60==0) && (flyTimerOn==1)) { 
            if ((E_beep1min==1) && (SOUND_ON==1)) { BEEP=4; Buzzer=1; }
            // блок включающий подсветку при минутном звуковом сигнале таймера
            Light=1;
            LightOn=1500; // время горения подсветки 
         } 

         // каждые 2 сек. в последнюю минуту даем звуковой сигнал таймера
         if ((flyCurrTimer<60) && (((flyCurrTimer%60)%2)==0) && (flyTimerOn==1)) { 
            if ((E_beep2sec==1) && (SOUND_ON==1)) { BEEP=3; Buzzer=1; }
            // блок включающий подсветку при последней минуте работы таймера
            Light=1;
            LightOn=1500; // время горения подсветки             
         }
         
      }         

      // работа со звуком
      if (BEEP==1) Buzzer=0;
      if (BEEP>0) BEEP--;      
      
      // подсветка дисплея
      if (LightOn==1) Light=0;
      if (LightOn>0) LightOn--;
       
      // обработка событий батареи 
      battAvg=battAvg+read_adc(7);        // счетчики батареи
      avgCount++; 
      if (avgCount==25) {
        avgCount=0;
        batt=(unsigned int)((battAvg/25) - 127 +E_var11);
        battAvg=0;

        if (batt<battMin) {
            Buzzer=1;  // если напряжение на батарее меньше минимума - пищим !!
            // блок включающий подсветку при разряде батареи
            Light=1;
            LightOn=1500; // время горения подсветки 
        }            
      }
      // вызываем процедуру опроса кнопок меню
      read_key();
      
      // вызываем процедуру опроса кнопок триммеров
      read_trim();
      
      if (ppmStop==1) ppmStop=2; // останавливаем генерацию PPM
      
   }

}


//--------------------------------------------------------------------------------------------------
//                                                                                     ГЛАВНЫЙ ВЫЗОВ
void main(void) {
unsigned char i; // временная переменная циклов

  // ---------------------------------------------- Конфигурация портов ввода-вывода процессора

  // Port A - используется для управления дисплеем
  // Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
  // State7=0  State6=0  State5=0  State4=0  State3=0  State2=0  State1=0  State0=0 
  PORTA=0x00;
  DDRA=0xFF;

  // Port B - кнопки меню и выход сигнала PPM
  // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=Out 
  // State7=P State6=P State5=P State4=P State3=P State2=P State1=P State0=0
  //   none     left     right    up       down     exit     menu    ppm_out
  PORTB=0xFF;
  DDRB=0x81;

  // Port C - управление дисплеем
  // Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=In 
  // State7=0  State6=0  State5=0  State4=0  State3=0  State2=0  State1=0  State0=P
  //   none      none      disp      disp      disp      disp      disp      none  
  PORTC=0x01; // Проверенная конфигурация но на выход работают 6 и 7 биты которые
  DDRC=0xFE;  // не подключены и скорее всего разумно их перевести на ввод

  //PORTC=0xC1; // Помоему так должно быть.....................................................!!!
  //DDRC=0x3E;

  // Port D - Триммеры
  // Func7=In  Func6=In  Func5=In  Func4=In  Func3=In  Func2=In  Func1=In  Func0=In 
  // State7=P  State6=P  State5=P  State4=P  State3=P  State2=P  State1=P  State0=P
  // RuddTrDN  RuddTrUP  ThroTrDN  ThroTrUP  ElevTrDN  ElevTrUP  AileTrDN  AileTrUP
  PORTD=0xFF;
  DDRD=0x00;

  // Port E - выключатели и пищалка
  // Func7=In  Func6=In  Func5=In  Func4=In  Func3=Out  Func2=In  Func1=In  Func0=In 
  // State7=P  State6=P  State5=P  State4=P  State3=0   State2=P  State1=P  State0=P
  //  ppm_in     id2     trainer     gear     buzzer     elevDr    aileDr   throCut 
  PORTE=0xF7;
  DDRE=0x08;

  // Port F - Аналого-цифровой преобразователь 
  // Func7=In  Func6=In  Func5=In  Func4=In  Func3=In  Func2=In  Func1=In  Func0=In 
  // State7=T  State6=T  State5=T  State4=T  State3=T  State2=T  State1=T  State0=T
  //   batt    pit_trim  hov_thr   hov_pit   rudd_st   thro_st   elev_st   aile_st 
  PORTF=0x00;
  DDRF=0x00;

  // Port G - выключатели и вход "ppm-ученик"
  //  Func4=Out    Func3=In    Func2=In    Func1=In    Func0=In 
  //  State4=0    State3=P    State2=P    State1=P    State0=P 
  // simcontrol     id1         none      verRfPow     ruddDR  
  PORTG=0x0F;
  DDRG=0x10;

// Timer/Counter 1 initialization - передача пачки PPM
// Clock source: System Clock
// Clock value: 2000,000 kHz
// Mode: Fast PWM top=ICR1
// OC1A output: Non-Inv.
// OC1B output: Discon.
// OC1C output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer 1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: On
// Compare B Match Interrupt: Off
// Compare C Match Interrupt: Off
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
OCR1CH=0x00;
OCR1CL=0x00;


// Timer/Counter 3 initialization   - генератор для отсчета микросекунд для захвата PPM
// Clock source: System Clock
// Clock value: 2000,000 kHz
// Mode: Normal top=FFFFh
// Noise Canceler: Off
// Input Capture on Falling Edge
// OC3A output: Discon.
// OC3B output: Discon.
// OC3C output: Discon.
// Timer 3 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
// Compare C Match Interrupt: Off
TCCR3A=0x00;
TCCR3B=0x00;
TCNT3H=0x00;
TCNT3L=0x00;
ICR3H=0x00;
ICR3L=0x00;
OCR3AH=0x00;
OCR3AL=0x00;
OCR3BH=0x00;
OCR3BL=0x00;
OCR3CH=0x00;
OCR3CL=0x00;

EICRA=0x00; // выключаем прерывание на захват
EICRB=0x00;
EIMSK=0x00;
// EIFR=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x10;
ETIMSK=0x00;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;


// ADC initialization
// ADC Clock frequency: 187,500 kHz
// ADC Voltage Reference: AREF pin
ADMUX=ADC_VREF_TYPE & 0xff;
ADCSRA=0x87;


// инициализация переменных связанных с отображением информации на дисплее
  BLINK_TIMER=0; // инициализация переменных мигания для модуля дисплея
  BLINK=0;       // режим мигания 0

  BEEP=0; //звуковой сигнал выключен
  Buzzer=0;
  
  LightOn=100; // время горения подсветки  
    
  // сброс системы сообщений 
  printMess=0; // отключить
  messStr1=" ";
  messStr2=" ";
  messStr3=" ";
  messStr4=" ";
  messStr5=" ";
     
  // настройки звука
  SOUND_ON=E_SOUND_ON;

  // настройки отклика на клавиши меню
  if (E_key_press_time==255) { // устанавливаем значения по умолчанию
    // первый запуск - инициализация переменных
    E_key_press_time=10;
    E_key_repress_time=7;
    E_CurModelNum=255;
    E_ClusterSize=32;
    E_battMin=700; // минимально допустимое напряжение батареи около 10 вольт
    E_eventStart=8; // тип старта - ручной старт
    E_eventStop=8;  // тип останова - ручной останов
    E_beep1min=0; // звуковой сигнал каждую минуту полетного таймера
    E_beep2sec=0; // звуковой сигнал каждые 2 секунды последнюю минуту   
    E_nulTrimBeep=0; // звуковой сигнал о прохождении триммера нулевой точки
    
    PPM_capture=0; // отключение захвата
    E_var3=0;  // формат сигнала PPM - прямой
    E_var4=32; // контрастность экрана
    
    E_trim_press_time=6; // задержка при опросе триммеров каналов
      
    E_var11=127;
    E_var12=2; // используем раскладку mode2
    
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
  
  if ((E_var4<20) || (E_var4>45))  E_var4=32; // правим контраст на случай старого eeproma
  if (E_var11==0)   E_var11=127; // правим контраст на случай старого eeproma
  if (E_var12==0)   E_var12=2;   // правим раскладку на случай старого eeproma
  
  mess_posx=0; // переменные для скролинга в меню
  mess_char=0;
  mess_pause=0;  
  battMin=E_battMin; // минимально допустимое напряжение батареи

    
  // устанавливаем ранее установленные значения для опроса клавиатуры
  key_press_time=E_key_press_time;
  key_repress_time=E_key_repress_time;   
  trim_press_time=E_trim_press_time; // значения опроса тримеров
  
  ClusterSize=E_ClusterSize; // размер кластера для V-DISK

  FILE_RESET(); // сброс модели в памяти 

  flyTimerOn=0; // полетный таймер выключен
  flyCurrTimer=rmodel.MODEL_FLYTIMER; // полетное время
  TimerEndBeepCounter=0;
  TimerEnd=0;
 
  // если ранее была какая то модель загруженная - загружаем ее  
  if (E_CurModelNum<16) {
     OpenModel(E_CurModelNum);  // загружаем выбранную в прошлый раз модель
  }  
  
  ModelChange=0; // признак того что модель не изменялась...
           
// Читаем результаты калибровки аналоговых каналов
  for (i=0; i<7; i++) { 
     // берем из еpprom результат прошлой калибровки
     UCHmin[i]=E_UCHmin[i];
     UCHmid[i]=E_UCHmid[i];
     UCHmax[i]=E_UCHmax[i];
  }
  
  resetMenu(); // сброс настроек меню

  

  FMODE_NUM=0; // полетный режим первый (для начала работы генератора PPM)

  // инициализация PPM генератора - - - - - - - - - - - - - - - - - - - - - - - - - - 
  impPhase=0; // фаза передачи импульса
  PPM_CUR_CH_NUM=0;   // текущий номер PPM канала на выдачу
  PPM_PAUSE=0;        // общая длительность пачки PPM
  for (i=0; i<8; i++) {
     CH_PPM[i]=rmodel.FMODE[FMODE_NUM].LCH_MIDLE[i]; // заполняем длительности каналов
  }

                                                          
  battAvg=0;        // счетчики батареи
  avgCount=0; 
  
  LCD_init(); // Инициализация дисплея   
  LCD_setContrast(E_var4); // установка контрастности
  
  ppmStop=0; // разрешаем генерацию ppm
        
  #asm("sei") 

  while (1) { // Главный цикл
   
    // обрабатываем тримеры в соответствии с модой передатчика
    i=get_trim_key();
    if (E_var12==1) {   //  триммеры первой моды
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
    if (E_var12==3) {    // триммеры третьей моды
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
    if (E_var12==4) {    // триммеры четвертой моды
       switch (i) {
         case 127 : { i=254;    // меняем местами элероны-254 и РН-127 триммер вверх 
                      break;
         }
         case 254 : { i=127;   // меняем местами элероны-254 и РН-127 триммер вверх
                      break;
         }
         
         case 191 : { i=253;   // меняем местами элероны-253 и РН-191 триммер вниз      
                      break;
         }                  
         case 253 : { i=191;   // меняем местами элероны-253 и РН-191 триммер вниз      
                      break;

         }                  
         case 239 : { i=251;   // меняем руль высоты и тягу
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
       case 239 : { // руль высоты
                    if (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[1]<120) { 
                      rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[1]=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[1]+
                        rmodel.FMODE[FMODE_NUM].TRIMSTEP; 
                      ModelChange=1;
                    }
                    
                    // проверяем не в нуле ли триммер
                    if ( (E_nulTrimBeep==1) && (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[1]==0) ) { 
                       trim_press_time=E_trim_press_time * 3;
                       BEEP=trim_press_time-4;
                    } else trim_press_time=E_trim_press_time;
                                                 
                    break;
       }

       case 223 : { // руль высоты
                    if (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[1]>-120) { 
                      rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[1]=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[1]-
                        rmodel.FMODE[FMODE_NUM].TRIMSTEP; 
                      ModelChange=1;
                    }                             
                    // проверяем не в нуле ли триммер
                    if ( (E_nulTrimBeep==1) && (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[1]==0) ) { 
                       trim_press_time=E_trim_press_time * 3;
                       BEEP=trim_press_time-4;
                    } else trim_press_time=E_trim_press_time;
                    break;
       }

       case 254 : { // элероны
                    if (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[0]<120) { 
                      rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[0]=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[0]+
                        rmodel.FMODE[FMODE_NUM].TRIMSTEP; 
                      ModelChange=1;
                    }   
                    // проверяем не в нуле ли триммер
                    if ( (E_nulTrimBeep==1) && (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[0]==0) ) { 
                       trim_press_time=E_trim_press_time * 3;
                       BEEP=trim_press_time-4;
                    } else trim_press_time=E_trim_press_time;
                                              
                    break;
       }

       case 253 : { // элероны
                    if (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[0]>-120) { 
                      rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[0]=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[0]-
                        rmodel.FMODE[FMODE_NUM].TRIMSTEP; 
                      ModelChange=1;
                    }                             
                    // проверяем не в нуле ли триммер
                    if ( (E_nulTrimBeep==1) && (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[0]==0) ) { 
                       trim_press_time=E_trim_press_time * 3;
                       BEEP=trim_press_time-4;
                    } else trim_press_time=E_trim_press_time;

                    break;
       }

       case 251 : { // throTrUP
                    if (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[2]<120) {
                      rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[2]=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[2]+
                        rmodel.FMODE[FMODE_NUM].TRIMSTEP; 
                      ModelChange=1;
                    }     
                    // проверяем не в нуле ли триммер
                    if ( (E_nulTrimBeep==1) && (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[2]==0) ) { 
                       trim_press_time=E_trim_press_time * 3;
                       BEEP=trim_press_time-4;
                    } else trim_press_time=E_trim_press_time;
                    break;
       }

       case 247 : { // throTrDN
                    if (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[2]>-120) { 
                      rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[2]=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[2]-
                        rmodel.FMODE[FMODE_NUM].TRIMSTEP; 
                      ModelChange=1;
                    }     
                    // проверяем не в нуле ли триммер
                    if ( (E_nulTrimBeep==1) && (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[2]==0) ) { 
                       trim_press_time=E_trim_press_time * 3;
                       BEEP=trim_press_time-4;
                    } else trim_press_time=E_trim_press_time;
                    break;
       }

       case 127 : { // rudTrUP
                    if (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[3]<120) { 
                      rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[3]=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[3]+
                        rmodel.FMODE[FMODE_NUM].TRIMSTEP; 
                      ModelChange=1;
                    }     
                    // проверяем не в нуле ли триммер
                    if ( (E_nulTrimBeep==1) && (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[3]==0) ) { 
                       trim_press_time=E_trim_press_time * 3;
                       BEEP=trim_press_time-4;
                    } else trim_press_time=E_trim_press_time;
                    break;
       }

       case 191 : { // rudTrDN
                    if (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[3]>-120) {
                      rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[3]=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[3]-
                        rmodel.FMODE[FMODE_NUM].TRIMSTEP;
                      ModelChange=1;
                    }     
                    // проверяем не в нуле ли триммер
                    if ( (E_nulTrimBeep==1) && (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[3]==0) ) { 
                       trim_press_time=E_trim_press_time * 3;
                       BEEP=trim_press_time-4;
                    } else trim_press_time=E_trim_press_time;                    
                    break;
       }
  
    }
    
    LCD_clear(); // очистим экран
    
    disp(); // вызов процедуры отрисовки меню

    LCD_refresh(); // вывод на экран из буфера
  }
}
