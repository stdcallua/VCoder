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

eeprom unsigned char E_CurModelNum; // ����� ��������� ������

eeprom unsigned char E_eventStop;   // ������� �� �������� ������������� ������
eeprom unsigned char PPM_capture; // ������� ��������� ������� PPM �������
eeprom unsigned char E_var3;      // ������ ������� PPM 0 - ������, 255 - ���������
eeprom unsigned char E_var4;      // ������������� ������
eeprom unsigned char E_trim_press_time; // �������� �� ������� ������ �������
eeprom unsigned char E_nulTrimBeep; // E_var5; ������ � ���������� �������� � ����

eeprom unsigned char E_var11; // ������������� �������� �������
eeprom unsigned char E_var12; // ��������� ������ mode\mode2

eeprom unsigned int  E_vari2;
eeprom unsigned int  E_vari3;
eeprom unsigned int  E_vari4;

eeprom unsigned int  E_vari5;
eeprom unsigned int  E_vari6;
eeprom unsigned int  E_vari7;
eeprom unsigned int  E_vari8;
eeprom unsigned int  E_vari9;
eeprom unsigned int  E_vari10;

eeprom unsigned char E_eventStart; // ������� �� �������� �������� ������ ������

unsigned int LightOn; // ����� ������� ���������
unsigned char ppmStop; // ������� �������� ��������� PPM
unsigned char flyTimerOn; // ������� ���� ��� �������� ������ �������
unsigned int flyCurrTimer; // ������� �������� ��������� �������
unsigned int OnCurrTimer; // �������� ��������� ������� ��� ������� ��� ��������
unsigned char TimerEnd; // ������� ���� ��� ������ ��� �������� ���� ������
unsigned char TimerEndBeepCounter; // ������� ������ � ����� ����� �������

eeprom unsigned char E_beep1min; // ������� ������������� ������ ����� ������ ������ ������ �������
eeprom unsigned char E_beep2sec; // ������� ������������� ������ ����� ������ 2 ������� � ��������� ������

eeprom unsigned int E_UCHmid[7]; // ������� �������� ���������� UCH ������� � EEPROM
eeprom unsigned int E_UCHmin[7]; // ����������� �������� ���������� UCH ������� � EEPROM
eeprom unsigned int E_UCHmax[7]; // ������������ �������� ���������� UCH ������� � EEPROM

unsigned char ClusterSize; // ������ �������� �������� ������� � RAM

eeprom unsigned char E_SOUND_ON; // ������� ���� ��� ���� ������� 
unsigned char SOUND_ON; // ������� ���� ��� ���� �������

eeprom unsigned char E_key_press_time; // ���������� ������ ����� �������� ������� ��������� �������
eeprom unsigned char E_key_repress_time; // ���������� ������ ����� �������� � ������� ������� ���� ����������

unsigned char key_press_time; // ���������� ������ ����� �������� ������� ��������� �������
unsigned char key_repress_time; // ���������� ������ ����� �������� � ������� ������� ���� ����������

unsigned char trim_press_time; // �������� �� ������� ������� ��������
 
unsigned int UCH_VALUES[14];   // ��������� ���������� �������� UCH
signed  char UCH_VAL_PROC[14]; // ���������� �������� ������� UCH

eeprom unsigned int E_battMin; // ���������� ���������� ���������� �� ������� �����������
unsigned int battMin;    // ���������� ���������� ���������� �� ������� �����������
unsigned int batt;       // ���������� �� ������� ����������� (�������)

// ������������� ������ ���������� �������
unsigned int UCHmid[7]; // ������� �������� ���������� UCH �������
unsigned int UCHmin[7]; // ����������� �������� ���������� UCH �������
unsigned int UCHmax[7]; // ������������ �������� ���������� UCH �������

unsigned int FMODE_NUM; // ������� �������� �����
 
unsigned int LCH_LEN[16]; // ������ ������������� LCH �������
unsigned int OLD_LCH_LEN[16]; // ������ ������������� LCH ������� ����������� ������ 
                              // (����� ��� ����������� ������� ������ � ������������ � �������)

unsigned char PPM_CUR_CH_NUM; // ������� ����� PPM ������ �� ������
unsigned int CH_PPM[8]; // ������������ ��������� ��������� ��� ������ �� ����������
unsigned int PPM_PAUSE; // ������������ �����������
//unsigned int CAP_PPM[8]; // ������������ ������������ ������� PPM
unsigned char mch[8]; // ������ �� ���������� �������� ����� ��� �������������������

unsigned int CURVE_POINT[16][9][2]; // ������ ����� ������ �������� ���������� ������

unsigned char BLINK_TIMER; // ���������� ��� ����������� ������� �������
unsigned char BLINK; // ���� �� ��������� ������� �������

flash unsigned char *messStr1; // ������ ����� ��� ������ ��������� ������������
flash unsigned char *messStr2; // ������ ����� ��� ������ ��������� ������������
flash unsigned char *messStr3; // ������ ����� ��� ������ ��������� ������������
flash unsigned char *messStr4; // ������ ����� ��� ������ ��������� ������������
flash unsigned char *messStr5; // ������ ����� ��� ������ ��������� ������������

unsigned char messRetCode; // ��� ���������� �������� ������ ���������

unsigned char printMess; // ���� ���� ��� ����� ���������� ���������

unsigned int     outx1, outx2, outx3, outy1, outy2, outy3, outkk; // �������

unsigned char ModelChange; // ������� ���� ��� ������ ���� ��������

unsigned char mixercount;  // ����� ���������� �������� � ������
unsigned char mixtochan;   // ���������� ������������� �������� � ����� ������
unsigned char mixtochanlast;   // ���������� ������������� �������� � ��������� ������


// ������� ���������� �������� � �������� ������
unsigned char getMixCount(unsigned char fmode) {
unsigned char i;

   for (i=0;i<39;i++) { // ���������� � ����� ������� �������
         // ��������� - ���� ������ �������...
      if (rmodel.FMODE[fmode].MIXER[i].MIX_TYPE.ACTIVE==0) {
        break;
      }
   }
   return i;
}

void MixerCalc(unsigned char mixstart, unsigned char mixend) { // - - - - - - - - - ��������� ������� ������������ ��������� ������

unsigned int i; // ������� �����
unsigned char sw, swon; // ����������� � �������� �������

unsigned char soursech, destinch; // ������ �������

unsigned long int chval; // �������� ������ ���������
unsigned long int chmin, chmid, chmax; // ����� ������ ���������
unsigned long int dchmin, dchmid, dchmax; // ����� ������ ����������
unsigned long int soursesc, destsc; // ������ ����� ��������� � ����������
unsigned long int res; // �������������� �������� ��� ����� ����������

unsigned char signres; // ���� ���������� ������������

signed char mixproc; // ������� ������������ ������
unsigned char mixuch; // ����� UCH ����������� ������� ������������

   for (i=mixstart;i<mixend;i++) { // ���������� � ����� ������� �������

         // ��������� - ���� ������ �������...
      if (rmodel.FMODE[FMODE_NUM].MIXER[i].MIX_TYPE.ACTIVE==1) {
      
         //��������� ������������ �� � ������� �����������
         if (rmodel.FMODE[FMODE_NUM].MIXER[i].MIX_TYPE.MIX_SW==1) {
            // ������������ ����������� 

            sw=rmodel.FMODE[FMODE_NUM].MIXER[i].MIX_TYPE.UCH_SW+7;
            if (UCH_VALUES[sw]==1) { //����������� �������
               // ����������� ��������
               if (rmodel.FMODE[FMODE_NUM].MIXER[i].MIX_TYPE.SW_INV==0) swon=1;
                  else swon=0; 
            } 
               else { // ����������� ��������
                 // ����������� ��������
                 if (rmodel.FMODE[FMODE_NUM].MIXER[i].MIX_TYPE.SW_INV==0) swon=0;
                    else swon=1; 
               }
         } 
            else { // ����������� �� ������������
               swon=1;
            }
      } else swon=0;
      
      if (swon==1) { // ������ ������� ������ ��� ������������...
      
         destinch=rmodel.FMODE[FMODE_NUM].MIXER[i].CH_NUM.CH_DEST; // ����� ����������
         dchmid=rmodel.FMODE[FMODE_NUM].LCH_MIDLE[destinch];       // ������� �������� ������
         dchmin=rmodel.CHANNELS.CH_EPL[destinch];                  // �����������  �������� ���������� ��������
         dchmax=rmodel.CHANNELS.CH_EPR[destinch];                  // ������������ �������� ���������� ��������

         soursech=rmodel.FMODE[FMODE_NUM].MIXER[i].CH_NUM.CH_SOURSE; // ����� ������ ���������
         // ��������� �������� ������ ���������        
         if (rmodel.FMODE[FMODE_NUM].MIXER[i].MIX_TYPE.SOURSE_TYPE==1) {
            // ��� ����� LCH
            chval=OLD_LCH_LEN[soursech]; // LCH_LEN[soursech]; // ����� �������� ������
            chmid=rmodel.FMODE[FMODE_NUM].LCH_MIDLE[soursech]; // ������� �������� ������
            chmin=rmodel.CHANNELS.CH_EPL[soursech];            // �����������  �������� ���������� ��������
            chmax=rmodel.CHANNELS.CH_EPR[soursech];            // ������������ �������� ���������� ��������
         }
            else {
               // ��� ����� UCH
               chval=UCH_VALUES[soursech]; // ����� �������� UCH
               if (soursech<7) { // ����� ���� � ���������� UCH
                  chmid=UCHmid[soursech]; // ������� ��������
                  chmin=UCHmin[soursech]; // ����������� ��������
                  chmax=UCHmax[soursech]; // ������������ ��������
               } 
                 else { // ����� ���� � ���������� UCH
                    if (soursech==7) { // ����������� FMODE (���������������)
                      chmin=0;
                      chmid=0;
                      chmax=1;
                      chval=1;                    
                    } 
                        else {  // ��������� �����������
                          chmid=0;
                          chmin=0;
                          chmax=1;                          
                        }
                 }
                 
            }
         // ������ ������� ����������� ������������ ������
         if (rmodel.FMODE[FMODE_NUM].MIXER[i].MIX_TYPE.PROC_SOURSE==1) {
            // ������� ������������ ����� �� UCH
            mixuch=rmodel.FMODE[FMODE_NUM].MIXER[i].MIX_VAL & 0x0F;
            if (mixuch==7) mixproc=100; else mixproc=UCH_VAL_PROC[mixuch]; // ����� ������� ������������ �� ������
                         
            // �������� �������� ������������ ���� � ���� ���� �������������
            if ((rmodel.FMODE[FMODE_NUM].MIXER[i].MIX_VAL & 0x10)!=0) {
                 mixproc=-mixproc;             
            }
         } 
           else { // ������� ������������ �������������
               mixproc=rmodel.FMODE[FMODE_NUM].MIXER[i].MIX_VAL;
           }    

          //  !!!!!!!!!!!!!!!!!!  ����� ��������� ������� ������
            
          if (rmodel.CHANNELS.LCH_REV[destinch]==1) { // ������ ������ !!
               mixproc=-mixproc;
          }
          //  !!!!!!!!!!!!!!!!!! 

         // ������ ���������
         
         // ���������� ����������� ����
         if (chval>chmid) { // ���� �������� � ������ ����� �����
            soursesc=chmax-chmid; // ������ ����� ������ - ��������
            chval=chval-chmid;
            if (mixproc>0) {
              destsc=dchmax-dchmid; // ������ ����� ������ - ����������
              signres=1;
            } 
               else {
                  destsc=dchmid-dchmin; // ������ ����� ����� - ����������
                  signres=0;
                  mixproc=-mixproc;
               }

         }  
            else { 
               chval=chmid-chval;
               soursesc=chmid-chmin; // ������ ����� �����
               
               if (mixproc<0) {
                  destsc=dchmax-dchmid; // ������ ����� ������
                  signres=1;
                  mixproc=-mixproc;
               } 
                  else {
                    destsc=dchmid-dchmin; // ������ ����� �����
                    signres=0;
                  }
            }

         
         res=(destsc*chval*mixproc)/(soursesc*100); // ������������ ��������  ����� �����
//         chval1=destinch;
         if (signres==1) 
            LCH_LEN[destinch]=LCH_LEN[destinch]+(unsigned int)res; 
            else
              LCH_LEN[destinch]=LCH_LEN[destinch]+-(unsigned int)res;     
      }       
   }     
}

// ��������� ������� ������� ����� ������ ��� �������� ��������� ������
void CalcCurveORD(void) {
unsigned long int ti, til, tir; // �������� ����������
unsigned char tc, tc1; // ��������� ����������
signed   char tsc; // ��������� ���������� �� ������

   for (tc1=0; tc1<16; tc1++) {
      //           +---------����� ������
      //           |   +-----����� ����� ������
      //           |   |  +-- ��� 0 �������� �����, ��� 1 ������� �����
      //           |   |  |  
      CURVE_POINT[tc1][0][0]=rmodel.CHANNELS.CH_EPL[tc1]; // ������� (����� ����� �����)
   
      ti=( rmodel.FMODE[FMODE_NUM].LCH_MIDLE[tc1] - CURVE_POINT[tc1][0][0] ) / 4; // ��� ����� �����
   
      for (tc=1;tc<4;tc++) CURVE_POINT[tc1][tc][0]= CURVE_POINT[tc1][tc-1][0] + ti; // ����� ����� �� ��������

   
      CURVE_POINT[tc1][4][0]=rmodel.FMODE[FMODE_NUM].LCH_MIDLE[tc1]; // ������� �����

      ti=(  rmodel.CHANNELS.CH_EPR[tc1] - CURVE_POINT[tc1][4][0] ) / 4; // ��� ����� ������
   
      for (tc=5; tc<8; tc++) CURVE_POINT[tc1][tc][0]= CURVE_POINT[tc1][tc-1][0] + ti; // ����� ������ �� ��������  

      CURVE_POINT[tc1][8][0]=rmodel.CHANNELS.CH_EPR[tc1]; // ������� (����� ����� �����)
      
      // ������ ������ ����� ������
      til=CURVE_POINT[tc1][4][0] - CURVE_POINT[tc1][0][0]; // ��������� �������� ����� �����
      tir=CURVE_POINT[tc1][8][0] - CURVE_POINT[tc1][4][0]; // ��������� �������� ����� ������
      
      for (tc=0; tc<9; tc++) { // ���� �� ���� ������
         tsc=rmodel.FMODE[FMODE_NUM].LCH_CURVE[tc1].point[tc]; // ����� �������� ������
         if (tsc>=0) // ������ ���� ������� ������������ ����������� 
           CURVE_POINT[tc1][tc][1]=CURVE_POINT[tc1][4][0] + (tir * tsc) / 100;
           else { // ������ ���� ������� ������������ �����������
              tsc=-tsc;
              CURVE_POINT[tc1][tc][1]=CURVE_POINT[tc1][4][0] - (til * tsc) / 100;              
           }        
      }
   } 
}

//--------------------------------------------------------------------------------------------------
//                                                     ��������� ������ ������ ���������� ������ ADC
// ������� ��������: adc_input - ����� ������ ��� ������
// �������� ��������: ��������� ��������
unsigned int read_adc(unsigned char adc_input) {
  ADMUX=adc_input|ADC_VREF_TYPE;
  delay_us(10);
  ADCSRA|=0x40;               
  while ((ADCSRA & 0x10)==0);
  ADCSRA|=0x10; // Stop
  return ADCW;
}


//--------------------------------------------------------------------------------------------------
//                                           ��������� ������ �������� ���������������� �������
unsigned char FMODE_OLD;
void read_UCH_values(void) {
int i; 
signed int s;

  for(i=0; i<7; i++) {                            // � ����� ���������� ���������� ������
    if (E_var12==2)  // ��� ������ ����
       switch (i) {
         case 1 : { UCH_VALUES[i]=read_adc(2); break; }
         case 2 : { UCH_VALUES[i]=read_adc(1); break; }
         default: UCH_VALUES[i]=read_adc(i);            // � ���������� �� ���������� ��������
       } else 
          if (E_var12==3)  // ��� ������� ����
             switch (i) {
               case 1 : { UCH_VALUES[i]=read_adc(2); break; }
               case 2 : { UCH_VALUES[i]=read_adc(1); break; }
               case 0 : { UCH_VALUES[i]=read_adc(3); break; } // ������ ������� ������� � 
               case 3 : { UCH_VALUES[i]=read_adc(0); break; } // ���� �����������
               default: UCH_VALUES[i]=read_adc(i);            // � ���������� �� ���������� ��������                  
          } else
          if (E_var12==4)  // ��� ��������� ����
             switch (i) {
               case 0 : { UCH_VALUES[i]=read_adc(3); break; } // ������ ������� ������� � �� 
               case 3 : { UCH_VALUES[i]=read_adc(0); break; } // ������ ������� ������� � ��

               default: UCH_VALUES[i]=read_adc(i);            // � ���������� �� ���������� ��������                  
          } else    UCH_VALUES[i]=read_adc(i); // ��� ������ ����
    
    
  
    // �������������� �������������� ������� �� ������ ���� ���������� �������� ����� ������������� !
    if (UCH_VALUES[i]>UCHmax[i]) UCHmax[i]=UCH_VALUES[i];
    if (UCH_VALUES[i]<UCHmin[i]) UCHmin[i]=UCH_VALUES[i];

    // ������������ �������� ������� ����������   
    s=((signed int)rmodel.UCH[i].UCH_RIGHT-rmodel.UCH[i].UCH_LEFT)/2; // �������� ��������� �������� ������ ��� ��������
                                                 // ���� �����   
    if (UCH_VALUES[i]>UCHmid[i]) {

       // ������������� ���������� �������� UCH - ������������ �������� � % ����� �� �������� UCH
       UCH_VAL_PROC[i]=rmodel.UCH[i].UCH_LEFT+s+(UCH_VALUES[i]-UCHmid[i]) * s / (UCHmax[i]-UCHmid[i]) ;
    } 
       else {
          // ������������� ���������� �������� UCH - ����������� �������� � % ����� �� �������� UCH
          UCH_VAL_PROC[i]=rmodel.UCH[i].UCH_LEFT+(UCH_VALUES[i]-UCHmin[i])*s/(UCHmid[i]-UCHmin[i]);     
       }

    // ����������� �������� �� ���������� ������ ����������
    if (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[i]>=0) { // ���� ������� ������ ������ ����
           UCH_VALUES[i]=UCH_VALUES[i]+((unsigned int)rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[i])*2;
       if (UCH_VALUES[i]>UCHmax[i]) UCH_VALUES[i]=UCHmax[i];    
    }
       else {
          if (UCH_VALUES[i]>(2*((unsigned int)(-rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[i])))) // � �������� uch ������ ��������
               UCH_VALUES[i]=UCH_VALUES[i]-(2*((unsigned int)(-rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[i])));
               else UCH_VALUES[i]=UCHmin[i]; 
          if (UCH_VALUES[i]<UCHmin[i]) UCH_VALUES[i]=UCHmin[i];
       }

  }
  
// ������ �������� ���������� �������
  if (SW_Id1==0) { UCH_VALUES[7]=0; } else UCH_VALUES[7]=1;
  if (!SW_Id2) { UCH_VALUES[7]=2; }
                                                     
  if (UCH_VALUES[7]<=(rmodel.FMODE_COUNT-1)) // - - - - - ����� ������������ �������� ������� 
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
      CalcCurveORD(); // ���������� �������� ����� ������                  
      FMODE_OLD=FMODE_NUM;
  }
  
  UCH_VALUES[8]=SW_Gear;     if (SW_Gear==1) { UCH_VAL_PROC[8]=rmodel.UCH[8].UCH_RIGHT; 
                                 } else { UCH_VAL_PROC[8]=rmodel.UCH[8].UCH_LEFT; }
                                   
  UCH_VALUES[9]=SW_Trainer;  if (SW_Trainer==1) { UCH_VAL_PROC[9]=rmodel.UCH[9].UCH_RIGHT; 
                                 } else { UCH_VAL_PROC[9]=rmodel.UCH[9].UCH_LEFT; }
                                 
  // �������� �������� ������
  if (flyTimerOn==0) {
     if (E_eventStart==8) {
         // ����� �� ������� ������ Trainer
         if (SW_Trainer==1) {
               flyTimerOn=1;
               OnCurrTimer=flyCurrTimer;
         }     
     }
       else { // ����� �� ��������� ����� �� ��������� ������
               if (CH_PPM[E_eventStart]>(rmodel.CHANNELS.CH_EPL[E_eventStart]+
                                      (rmodel.CHANNELS.CH_EPR[E_eventStart]-
                                        rmodel.CHANNELS.CH_EPL[E_eventStart])*20/100)) { 
                       flyTimerOn=1;
                       OnCurrTimer=flyCurrTimer;
                    }        
       }
  }

  // ��������� �������� ������
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
//                                                                           ��������� ������ ������
//
unsigned char ready_key=0; // ������� ��� ������� ��� ������
unsigned char rkey=0; // ��� ������� �������
unsigned char presstime=0; // ����� �������
unsigned int keyhold=0; // ������� ��������� �������
unsigned char keyhold_t=0; // ��������� ����������
unsigned char keyhold_wait=0; // ���������� ����������������� �� �������� ���������� ������

unsigned char BEEP; // ������� �������� 
// ��������� ��������� ���� ������ ��� ���������
unsigned char get_mnu_keys(void) {
  unsigned char t;

  t=ready_key & 0xFE;  // ��������� ��� ����� �������   

  if (t!=254) {
     ready_key=254; // ���������� ��� ������� ������
     BEEP=key_repress_time-2;
     if (SOUND_ON==1) Buzzer=1;  // ���� ���� �������� �� �������� �������
     Light=1;
     LightOn=500; // ����� ������� ���������

  }
  return t; // ���������� ��� ������ 
}

// ��������� ������ ��������� ��������� �������� ��������� ����������
void resetKeyReader() {
    ready_key=0; // ������� ��� ������� ��� ������
    rkey=0; // ��� ������� �������
    presstime=0; // ����� �������
    keyhold=0; // ������� ��������� �������
    keyhold_t=0; // ��������� ����������
}

unsigned char trimkey; // ������������ ������ ��������
unsigned char trimhold; // ����� ��������� �������
unsigned char readytrim; // ������� ��� �������

// ��������� ���� ������� ������ ��������
unsigned char get_trim_key() {
unsigned char t;
  t=readytrim;
  if (t!=255) {
     readytrim=255; // ���������� ��� ������� ������
     BEEP=trim_press_time-3;
     if (SOUND_ON==1) Buzzer=1;  // ���� ���� �������� �� �������� �������
     Light=1;
     LightOn=1500; // ����� ������� ���������
  }
  return t; // ���������� ��� ������� 
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ��������� ������ ������ ���������
void read_trim() {
unsigned char tempkey;

  tempkey=PIND; // ��������� ������� ������

  if (tempkey!=255) {
       
       if (trimkey==tempkey) { // ������ ������������ !
          trimhold++; // ����������� ������� ���������
          if (trimhold==trim_press_time) { // ���� ������ ������ ���������� ����������� �����
            readytrim=trimkey; // ������������ �������
            trimhold=0;
          } 
             else { trimkey=tempkey; }
       } 
          else { trimkey=tempkey; trimhold=0; }
  } 
     else { trimkey=255; trimhold=0; }
}

// ��������� ������ ������, ���������� 50 ��� � ������� �� ����������
void read_key() {
// ��������� ������ ������������ ����� ���������� � ��������� �� �������� � �������������� ��������
// � ������ ������������ ������� �� �������
unsigned char tempkey;

// ����� ������ ����
  tempkey=PINB | 128; // ��������� ������� �������
                          
  if (tempkey!=254) { // ���� ������� �������?

     if (keyhold_wait==0) {     // ���� �� �� ������� ���������� �� ��������

        if (tempkey==rkey) { // ��� ������� ������� ��������� � ��������? 

           presstime++; // �������� ������� ���������

           if (presstime==key_press_time) { // ������� ������ ���������� ����������� �����?  
              ready_key=tempkey;            //  ����������� ���� ������� �� ������

              // ���� ������ ������ MENU ��� EXIT - �� ����������� �� ����� !
              if ((tempkey==250)||(tempkey==252)) { 
                 keyhold_wait=1;
              }
           }
           
           if (presstime==(key_press_time+key_repress_time)) { // ������� ������������
              // ���������� ����������
              ready_key=tempkey; // ����������� ���� ������� �� ������


              if (keyhold_t<9) keyhold_t++; else keyhold=1; // ������������ ���� ��������� �������
              presstime=key_press_time; // ��������� ������� ��������� ��� �������� ����������� 
           }    
        }     
           else { // ��� ������� ������� �� ��������� � ��������
             rkey=tempkey; // ���������� ���
             presstime=0;  // �������� ������� ��������� ������� ������
             keyhold=0;
             keyhold_t=0;  
           }
     } 
  } 
     else {  // ������ �� ������
       rkey=254;      // ���������� ��������� ��� ������� �������
       presstime=0; // � ����� �������
       keyhold_wait=0;  // ���������� ���� �������� ���������� ������
     }
}

//--------------------------------------------------------------------------------------------------
//                           ���������� �������������� �������� ������������ ����� PPM �� ����������
//
unsigned char impPhase; // ���� �������� �� ��������
unsigned long battAvg;  // �������� �������� �������
unsigned char avgCount; // ����� ���������������� ��������
 
interrupt [TIM1_COMPA] void timer1_compa_isr(void)  { 
unsigned char i, k , n, m; // ���������� ������
signed char   j;
unsigned int chl, bt1;
unsigned long int kk,ev,x1,x2,x3,y1,y2;

if (ppmStop==2) {
    OCR1A=2000;  //�������� ������������ ��������   
    return;
}

if (PPM_CUR_CH_NUM<rmodel.CHANNELS.PPM_CH_COUNT) {

   if (impPhase==0) { // �������� ������� ������

       OCR1A=600;  //�������� ������������ ��������   
       if (E_var3==0) PORTB.0=1;  else  PORTB.0=0;
       impPhase=1;
//       if (PPM_CUR_CH_NUM<4) MixerCalc(PPM_CUR_CH_NUM*10,PPM_CUR_CH_NUM*10+4); // �������� ������ ��������
   
   } 
   
   else { // �������� ����� 
       OCR1A=2*CH_PPM[PPM_CUR_CH_NUM]-600;  //�������� ������������ �����

       if (E_var3==0) PORTB.0=0;  else  PORTB.0=1;
       impPhase=0;

       PPM_PAUSE=PPM_PAUSE+CH_PPM[PPM_CUR_CH_NUM]; // ������� ������������ ���� ���������

//       if (PPM_CUR_CH_NUM<4) MixerCalc(PPM_CUR_CH_NUM*10+4,PPM_CUR_CH_NUM*10+10); // �������� ������ ��������

//       if (PPM_CUR_CH_NUM<4) { // ������ ��������

       if ((PPM_CUR_CH_NUM+1)==rmodel.CHANNELS.PPM_CH_COUNT)
            MixerCalc( mixtochan * PPM_CUR_CH_NUM, mixtochan * PPM_CUR_CH_NUM + mixtochan + mixtochanlast);           
       else MixerCalc( mixtochan * PPM_CUR_CH_NUM, mixtochan * PPM_CUR_CH_NUM + mixtochan);
           
//       }
       PPM_CUR_CH_NUM++;
   }
} 
   else {
      OCR1A=2*(22500-PPM_PAUSE); // �������� ������������ �����

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
   
      PPM_PAUSE=0;     // ����� ������� ������
      PPM_CUR_CH_NUM=0; // ����� ������ ������

      
      // ����� ������������� �� ������������ ����� ����� ��������� PPM - - - - - - - - - - - - -
   
      // ����� PPM � LCH_LEN ����� ������ �������� 
      
   // �������� ��������� ���������� LCH
      for (i=0;i<rmodel.CHANNELS.LCH_COUNT;i++) { 

      // ��������� ����������� �������� �� ������� � ������������ � �������� �������
         if (LCH_LEN[i]<(32000+rmodel.CHANNELS.CH_EPL[i])) LCH_LEN[i]=32000+rmodel.CHANNELS.CH_EPL[i]; 
         if (LCH_LEN[i]>(32000+rmodel.CHANNELS.CH_EPR[i])) LCH_LEN[i]=32000+rmodel.CHANNELS.CH_EPR[i];         
         LCH_LEN[i]=LCH_LEN[i]-32000;
         
      // ������������ ��������� ������
         if (LCH_LEN[i]<OLD_LCH_LEN[i]) {
             // ������ ���� 
             if (rmodel.CHANNELS.LCHDELDN[i]!=0) { // ������ ���� ����� 
                  if ((OLD_LCH_LEN[i]-LCH_LEN[i])>(256-rmodel.CHANNELS.LCHDELDN[i])) 
                        LCH_LEN[i]=OLD_LCH_LEN[i]-(256-rmodel.CHANNELS.LCHDELDN[i]); 
             }
         } 
         
           else {
              // ������ �����
              if (rmodel.CHANNELS.LCHDELUP[i]!=0) { // ������ ����� ����� 
                  if ((LCH_LEN[i]-OLD_LCH_LEN[i])>(256-rmodel.CHANNELS.LCHDELUP[i])) 
                    LCH_LEN[i]=OLD_LCH_LEN[i]+(256-rmodel.CHANNELS.LCHDELUP[i]); 
               }
           }
              
         // ����������� ������
         if (rmodel.FMODE[FMODE_NUM].LCH_CURVE[i].active!=0) { // ���� ������ ��������
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
            
            // �������� ������������� ������� �� ����
            
             if (((x3-x1)==0) || ((x2-x3)==0)) {
                if (x1==x3) LCH_LEN[i]=y1; else LCH_LEN[i]=y2;             
             } 
               else {               
                 kk=(x3-x1)*1000/(x2-x3); // ������
                 outkk=kk;                   
                 ev=(y1*1000) / (1000 + kk) + (kk*y2) / (1000 + kk);
                 outy3=ev;            
                 if (ev<700) ev=2000+ev;
                 LCH_LEN[i]=(unsigned int) ev;
               }
           } else  LCH_LEN[i]=800+k;
         }

         // ���������� ������� ����� ��� ���������� ������� (������������� �������)
         OLD_LCH_LEN[i]=LCH_LEN[i];         
      }
      
      //���� ��������� �������� LCH to CH PPM - - - - - - - - - - - - - - - - - - - - - -
      // ����� PPM �� ������ LCH_LEN -> CH_PPM
      for (i=0;i<rmodel.CHANNELS.PPM_CH_COUNT;i++) {
         
         switch (rmodel.CHANNELS.FILTER[i].FILTER_TYPE) {
       
             case 0: { // �������� ������ �������
                       CH_PPM[i]=LCH_LEN[i]; 
                       break;
             }

             case 1: { // ������ ������� �� ��������� �����������
                       if (UCH_VALUES[rmodel.CHANNELS.FILTER[i].VAL1%256]==0) { // ���������  
                         CH_PPM[i]=LCH_LEN[i]; // �������� ����������� ��������
                       }
                         
                         else { // ��������
                             // �������� �������� ��������
                             j=rmodel.CHANNELS.FILTER[i].VAL1/256; // �������� ��� �������� � ����� � %%
                             if (j<0) { // ����� ������ ������
                               bt1=-j; // �������� ����
                               chl=rmodel.FMODE[FMODE_NUM].LCH_MIDLE[i] - 
                               ((rmodel.FMODE[FMODE_NUM].LCH_MIDLE[i]-rmodel.CHANNELS.CH_EPL[i])/100) * bt1;
                                                               
                             } else {  // ����� ������� ������
                               bt1=j;
                               chl=rmodel.FMODE[FMODE_NUM].LCH_MIDLE[i] +  
                               ((rmodel.CHANNELS.CH_EPR[i]-rmodel.FMODE[FMODE_NUM].LCH_MIDLE[i])/100) * bt1;
                             
                             }
                             CH_PPM[i]=chl; // ������ �������� ��������
                         }
                       break;
             }

             case 2: { // ������������������� �������
                       // � ���������� i - ����� ������ �� ������
                       
                       if (mch[i]==0) { // ��������� �� ����� �� ������ �������������... 
                            CH_PPM[i]=2150; mch[i]=1; // ������ �������������� ! 
                       } 
                         // ������������� ��� ��������� - ������ ������ 
                         else {       
/**                            CH_PPM[i]=LCH_LEN[mch[i]-1];
                            mch[i]++;
                            if (mch[i]==5) { mch[i]=0; }
**/                         

                            j=16; // � ��� ����� �� 16�� �������
                            chl=rmodel.CHANNELS.FILTER[i].VAL1; // ����� �������������� ����
                            // � mch[i] - ��������� ���������� ����� ��� ������ 1..4
                            m=mch[i];   
                            // ������� ����������� ��� ����� - ��������� �� ������ ������� ��� ������
                            for (k=0; k<m; k++) { // ��������� �� ������ ������
                               n=chl%2;                             
                               chl=chl/2;              // �����!, ��������� �� ��������� �����
                               if (j!=0) j--;   
                               while ((j!=0) && (n==0)) { // ������� ����� ������ ��� ������ 
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

      // ��������� � ������� ����� ����� PPM
      
      // ���������� ������� ����� LCH � ������������ � �������� ������� � ���������� �������
      for (i=0;i<rmodel.CHANNELS.LCH_COUNT;i++) {
           LCH_LEN[i]=32000+rmodel.FMODE[FMODE_NUM].LCH_MIDLE[i];
      }
      

      read_UCH_values(); // ��������� �������� UCH �������
              
      // ��������������� ������� - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

      // ���������� ��� ����������� ������� ������ lcd
      BLINK_TIMER++;
      if (BLINK_TIMER==25) BLINK=1;                      // ������ ���� ������� 2 ���� � �������
      if (BLINK_TIMER==50) { 
         BLINK=0; 
         BLINK_TIMER=0;  
         
         // ������������ ��������� �������
         if (flyCurrTimer==0) { 

            flyTimerOn=0; // ��������� ������

            if (TimerEnd==0) { 
                   // ���� ���������� ��������� ��� ��������� �������
                   Light=1;
                   LightOn=1500; // ����� ������� ��������� 
            }      
            
            if ((TimerEnd==0) && (SOUND_ON==1)) { // ������ ����� !
               TimerEnd=1; // ������� ���� ��� ������ ��������
               TimerEndBeepCounter=2; // ������ 3 �����
            } 
              else { //����� ������� �����
                if (TimerEnd==2) {
                   // ������� ���� 
                   BEEP=50; 
                   Buzzer=1;
                } 
                if (TimerEnd==4) { BEEP=0; Buzzer=0;  } // �������� ����
                if (TimerEnd==5) {
                   if (TimerEndBeepCounter!=0) {
                      TimerEnd=1;
                   }  
                     else { // ����� ��������� �� ������� ����� 
                        TimerEnd=4; 
                        TimerEndBeepCounter=1; 
                     } 
                   TimerEndBeepCounter--;                
                }
                TimerEnd++;                              
              }            
         } 

         // ��������� �������� ��������� �������
         if ((flyTimerOn==1) && (flyCurrTimer>0)) flyCurrTimer--;
      
         // ������ ������ ���� �������� ������ �������
         if ((flyCurrTimer%60==0) && (flyTimerOn==1)) { 
            if ((E_beep1min==1) && (SOUND_ON==1)) { BEEP=4; Buzzer=1; }
            // ���� ���������� ��������� ��� �������� �������� ������� �������
            Light=1;
            LightOn=1500; // ����� ������� ��������� 
         } 

         // ������ 2 ���. � ��������� ������ ���� �������� ������ �������
         if ((flyCurrTimer<60) && (((flyCurrTimer%60)%2)==0) && (flyTimerOn==1)) { 
            if ((E_beep2sec==1) && (SOUND_ON==1)) { BEEP=3; Buzzer=1; }
            // ���� ���������� ��������� ��� ��������� ������ ������ �������
            Light=1;
            LightOn=1500; // ����� ������� ���������             
         }
         
      }         

      // ������ �� ������
      if (BEEP==1) Buzzer=0;
      if (BEEP>0) BEEP--;      
      
      // ��������� �������
      if (LightOn==1) Light=0;
      if (LightOn>0) LightOn--;
       
      // ��������� ������� ������� 
      battAvg=battAvg+read_adc(7);        // �������� �������
      avgCount++; 
      if (avgCount==25) {
        avgCount=0;
        batt=(unsigned int)((battAvg/25) - 127 +E_var11);
        battAvg=0;

        if (batt<battMin) {
            Buzzer=1;  // ���� ���������� �� ������� ������ �������� - ����� !!
            // ���� ���������� ��������� ��� ������� �������
            Light=1;
            LightOn=1500; // ����� ������� ��������� 
        }            
      }
      // �������� ��������� ������ ������ ����
      read_key();
      
      // �������� ��������� ������ ������ ���������
      read_trim();
      
      if (ppmStop==1) ppmStop=2; // ������������� ��������� PPM
      
   }

}


//--------------------------------------------------------------------------------------------------
//                                                                                     ������� �����
void main(void) {
unsigned char i; // ��������� ���������� ������

  // ---------------------------------------------- ������������ ������ �����-������ ����������

  // Port A - ������������ ��� ���������� ��������
  // Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
  // State7=0  State6=0  State5=0  State4=0  State3=0  State2=0  State1=0  State0=0 
  PORTA=0x00;
  DDRA=0xFF;

  // Port B - ������ ���� � ����� ������� PPM
  // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=Out 
  // State7=P State6=P State5=P State4=P State3=P State2=P State1=P State0=0
  //   none     left     right    up       down     exit     menu    ppm_out
  PORTB=0xFF;
  DDRB=0x81;

  // Port C - ���������� ��������
  // Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=In 
  // State7=0  State6=0  State5=0  State4=0  State3=0  State2=0  State1=0  State0=P
  //   none      none      disp      disp      disp      disp      disp      none  
  PORTC=0x01; // ����������� ������������ �� �� ����� �������� 6 � 7 ���� �������
  DDRC=0xFE;  // �� ���������� � ������ ����� ������� �� ��������� �� ����

  //PORTC=0xC1; // ������� ��� ������ ����.....................................................!!!
  //DDRC=0x3E;

  // Port D - ��������
  // Func7=In  Func6=In  Func5=In  Func4=In  Func3=In  Func2=In  Func1=In  Func0=In 
  // State7=P  State6=P  State5=P  State4=P  State3=P  State2=P  State1=P  State0=P
  // RuddTrDN  RuddTrUP  ThroTrDN  ThroTrUP  ElevTrDN  ElevTrUP  AileTrDN  AileTrUP
  PORTD=0xFF;
  DDRD=0x00;

  // Port E - ����������� � �������
  // Func7=In  Func6=In  Func5=In  Func4=In  Func3=Out  Func2=In  Func1=In  Func0=In 
  // State7=P  State6=P  State5=P  State4=P  State3=0   State2=P  State1=P  State0=P
  //  ppm_in     id2     trainer     gear     buzzer     elevDr    aileDr   throCut 
  PORTE=0xF7;
  DDRE=0x08;

  // Port F - �������-�������� ��������������� 
  // Func7=In  Func6=In  Func5=In  Func4=In  Func3=In  Func2=In  Func1=In  Func0=In 
  // State7=T  State6=T  State5=T  State4=T  State3=T  State2=T  State1=T  State0=T
  //   batt    pit_trim  hov_thr   hov_pit   rudd_st   thro_st   elev_st   aile_st 
  PORTF=0x00;
  DDRF=0x00;

  // Port G - ����������� � ���� "ppm-������"
  //  Func4=Out    Func3=In    Func2=In    Func1=In    Func0=In 
  //  State4=0    State3=P    State2=P    State1=P    State0=P 
  // simcontrol     id1         none      verRfPow     ruddDR  
  PORTG=0x0F;
  DDRG=0x10;

// Timer/Counter 1 initialization - �������� ����� PPM
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


// Timer/Counter 3 initialization   - ��������� ��� ������� ����������� ��� ������� PPM
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

EICRA=0x00; // ��������� ���������� �� ������
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


// ������������� ���������� ��������� � ������������ ���������� �� �������
  BLINK_TIMER=0; // ������������� ���������� ������� ��� ������ �������
  BLINK=0;       // ����� ������� 0

  BEEP=0; //�������� ������ ��������
  Buzzer=0;
  
  LightOn=100; // ����� ������� ���������  
    
  // ����� ������� ��������� 
  printMess=0; // ���������
  messStr1=" ";
  messStr2=" ";
  messStr3=" ";
  messStr4=" ";
  messStr5=" ";
     
  // ��������� �����
  SOUND_ON=E_SOUND_ON;

  // ��������� ������� �� ������� ����
  if (E_key_press_time==255) { // ������������� �������� �� ���������
    // ������ ������ - ������������� ����������
    E_key_press_time=10;
    E_key_repress_time=7;
    E_CurModelNum=255;
    E_ClusterSize=32;
    E_battMin=700; // ���������� ���������� ���������� ������� ����� 10 �����
    E_eventStart=8; // ��� ������ - ������ �����
    E_eventStop=8;  // ��� �������� - ������ �������
    E_beep1min=0; // �������� ������ ������ ������ ��������� �������
    E_beep2sec=0; // �������� ������ ������ 2 ������� ��������� ������   
    E_nulTrimBeep=0; // �������� ������ � ����������� �������� ������� �����
    
    PPM_capture=0; // ���������� �������
    E_var3=0;  // ������ ������� PPM - ������
    E_var4=32; // ������������� ������
    
    E_trim_press_time=6; // �������� ��� ������ ��������� �������
      
    E_var11=127;
    E_var12=2; // ���������� ��������� mode2
    
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
  
  if ((E_var4<20) || (E_var4>45))  E_var4=32; // ������ �������� �� ������ ������� eeproma
  if (E_var11==0)   E_var11=127; // ������ �������� �� ������ ������� eeproma
  if (E_var12==0)   E_var12=2;   // ������ ��������� �� ������ ������� eeproma
  
  mess_posx=0; // ���������� ��� ��������� � ����
  mess_char=0;
  mess_pause=0;  
  battMin=E_battMin; // ���������� ���������� ���������� �������

    
  // ������������� ����� ������������� �������� ��� ������ ����������
  key_press_time=E_key_press_time;
  key_repress_time=E_key_repress_time;   
  trim_press_time=E_trim_press_time; // �������� ������ ��������
  
  ClusterSize=E_ClusterSize; // ������ �������� ��� V-DISK

  FILE_RESET(); // ����� ������ � ������ 

  flyTimerOn=0; // �������� ������ ��������
  flyCurrTimer=rmodel.MODEL_FLYTIMER; // �������� �����
  TimerEndBeepCounter=0;
  TimerEnd=0;
 
  // ���� ����� ���� ����� �� ������ ����������� - ��������� ��  
  if (E_CurModelNum<16) {
     OpenModel(E_CurModelNum);  // ��������� ��������� � ������� ��� ������
  }  
  
  ModelChange=0; // ������� ���� ��� ������ �� ����������...
           
// ������ ���������� ���������� ���������� �������
  for (i=0; i<7; i++) { 
     // ����� �� �pprom ��������� ������� ����������
     UCHmin[i]=E_UCHmin[i];
     UCHmid[i]=E_UCHmid[i];
     UCHmax[i]=E_UCHmax[i];
  }
  
  resetMenu(); // ����� �������� ����

  

  FMODE_NUM=0; // �������� ����� ������ (��� ������ ������ ���������� PPM)

  // ������������� PPM ���������� - - - - - - - - - - - - - - - - - - - - - - - - - - 
  impPhase=0; // ���� �������� ��������
  PPM_CUR_CH_NUM=0;   // ������� ����� PPM ������ �� ������
  PPM_PAUSE=0;        // ����� ������������ ����� PPM
  for (i=0; i<8; i++) {
     CH_PPM[i]=rmodel.FMODE[FMODE_NUM].LCH_MIDLE[i]; // ��������� ������������ �������
  }

                                                          
  battAvg=0;        // �������� �������
  avgCount=0; 
  
  LCD_init(); // ������������� �������   
  LCD_setContrast(E_var4); // ��������� �������������
  
  ppmStop=0; // ��������� ��������� ppm
        
  #asm("sei") 

  while (1) { // ������� ����
   
    // ������������ ������� � ������������ � ����� �����������
    i=get_trim_key();
    if (E_var12==1) {   //  �������� ������ ����
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
    if (E_var12==3) {    // �������� ������� ����
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
    if (E_var12==4) {    // �������� ��������� ����
       switch (i) {
         case 127 : { i=254;    // ������ ������� �������-254 � ��-127 ������� ����� 
                      break;
         }
         case 254 : { i=127;   // ������ ������� �������-254 � ��-127 ������� �����
                      break;
         }
         
         case 191 : { i=253;   // ������ ������� �������-253 � ��-191 ������� ����      
                      break;
         }                  
         case 253 : { i=191;   // ������ ������� �������-253 � ��-191 ������� ����      
                      break;

         }                  
         case 239 : { i=251;   // ������ ���� ������ � ����
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
       case 239 : { // ���� ������
                    if (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[1]<120) { 
                      rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[1]=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[1]+
                        rmodel.FMODE[FMODE_NUM].TRIMSTEP; 
                      ModelChange=1;
                    }
                    
                    // ��������� �� � ���� �� �������
                    if ( (E_nulTrimBeep==1) && (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[1]==0) ) { 
                       trim_press_time=E_trim_press_time * 3;
                       BEEP=trim_press_time-4;
                    } else trim_press_time=E_trim_press_time;
                                                 
                    break;
       }

       case 223 : { // ���� ������
                    if (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[1]>-120) { 
                      rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[1]=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[1]-
                        rmodel.FMODE[FMODE_NUM].TRIMSTEP; 
                      ModelChange=1;
                    }                             
                    // ��������� �� � ���� �� �������
                    if ( (E_nulTrimBeep==1) && (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[1]==0) ) { 
                       trim_press_time=E_trim_press_time * 3;
                       BEEP=trim_press_time-4;
                    } else trim_press_time=E_trim_press_time;
                    break;
       }

       case 254 : { // �������
                    if (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[0]<120) { 
                      rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[0]=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[0]+
                        rmodel.FMODE[FMODE_NUM].TRIMSTEP; 
                      ModelChange=1;
                    }   
                    // ��������� �� � ���� �� �������
                    if ( (E_nulTrimBeep==1) && (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[0]==0) ) { 
                       trim_press_time=E_trim_press_time * 3;
                       BEEP=trim_press_time-4;
                    } else trim_press_time=E_trim_press_time;
                                              
                    break;
       }

       case 253 : { // �������
                    if (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[0]>-120) { 
                      rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[0]=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[0]-
                        rmodel.FMODE[FMODE_NUM].TRIMSTEP; 
                      ModelChange=1;
                    }                             
                    // ��������� �� � ���� �� �������
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
                    // ��������� �� � ���� �� �������
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
                    // ��������� �� � ���� �� �������
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
                    // ��������� �� � ���� �� �������
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
                    // ��������� �� � ���� �� �������
                    if ( (E_nulTrimBeep==1) && (rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[3]==0) ) { 
                       trim_press_time=E_trim_press_time * 3;
                       BEEP=trim_press_time-4;
                    } else trim_press_time=E_trim_press_time;                    
                    break;
       }
  
    }
    
    LCD_clear(); // ������� �����
    
    disp(); // ����� ��������� ��������� ����

    LCD_refresh(); // ����� �� ����� �� ������
  }
}
