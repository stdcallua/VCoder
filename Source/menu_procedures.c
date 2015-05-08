#include "vcoder.h"

/**
                            ���� �������� ���������� �� ����

  ���������� ������ mn_display_new:
  menu_exe: ��� 0 - ����� �������� �� ��������������, ��� 1 - �������������� ����� ��������� ��������� � 
            ���������� menu_proc... ����� ��������� ����������� ����������� ���� � ������ �� ����������,
            ���� menu_exe=1. ��� ������ ����� ������, ����� ������ ���������� ����� ������� �� �����
  
  ���������� ������ vcoder - ������ ���� vcoder.h
**/

// ���������� ���������� ������� ����� ������������ ��������� �� ������ ���������� ���� ��� �������
unsigned char temp1, temp2, temp3; 
unsigned int temp4;

/**
                     � � � � � � � � � � � � � �    � � � � � � �   � � � � � �
       
                 (��������� ����������� ��� ������ ������ EDIT - CHANNELS - FILTERS)       
**/

__flash const char CHNUM_table[] = { // ������ �������
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
unsigned char chnum; //����� ������ ��� ������� �����������
signed char   valsc; // �������� �� ������ 


   //��������� ��������� �� ������ ������
   if (temp1==0) { // � ��� ������ ������, �������������
     temp2=0; // ����� ��������� ��� ��������������  
     temp3=0; // ������ ������� ��� ������� 2 (�������������������) 
     temp1=1;
     temp4=1; // ��� ����� � 15� �������
   }
    
   // �������� ���������
   LCD_setxy(0,0); LCD_wrsf("       FILTER EDIT       ",1);

   filt_num=numitem_cur-36; // ������� ������� ������� � 36 ������ ����.. ����� 36 �� ������ ������ ���� ��
                            // ������� ����� �������

   ftype=rmodel.CHANNELS.FILTER[filt_num].FILTER_TYPE; // ����� ��� ������� 
   fval=rmodel.CHANNELS.FILTER[filt_num].VAL1; // ����� ���. �������� �������
   
   //������� ����� ������ ��� ��������������
   LCD_setxy(0,2); LCD_wrsf("CHANNEL: ",0); LCD_char(CHNUM_table[filt_num],0);

   if (temp2==0) mode=2; else mode=0;

   // �������� ��� ������� �� �������
   LCD_setxy(0,3); LCD_wrsf("FILTER TYPE: ",0); LCD_wrsf(CHANNEL_FILTER_TYPE[ftype], mode); 

   switch (ftype) { // � ����������� �� ���� ������� ������� ��������� ���������
      case 1: { // ������ "�����������"
         
                // ������� �������� �����������
                if (temp2==1) mode=2; else mode=0;
                chnum=fval%256;
                valsc=fval/256; // �������� ������� ����� ������� � % �� -125 �� +125        
                LCD_setxy(0,4); LCD_wrsf("SWITCH: ",0); LCD_wrsf(UCH_Names[chnum], mode);
         
                // ������� �������� ������� ����� ������� ��� ���������� �����������
                if (temp2==2) mode=2; else mode=0;
                LCD_setxy(0,5); LCD_wrsf("VALUE: ",0); 
                if (valsc<0) { LCD_char('-',mode); valsc=-valsc; } else LCD_char('+',mode); 
                LCD_dec(valsc, 3, mode); LCD_char('%',mode);
                valsc=fval/256;
                break;
      }
      
      case 2: { // ������ "�������������"
               // ������� ��������� ������
               LCD_setxy(0,4); LCD_wrsf("CHANNELS: [ . . . . ]",0);
               LCD_setxy(60,4);
               chcount=0;
               for (x=0;x<16;x++) {
                  if ((fval%2)==1) { LCD_char(CHNUM_table[x], 1); LCD_char(' ',0); chcount++; }
                  fval=fval/2;
               }
            
               // ������� ������ �������
               
               for (y=0; y<2; y++) {
                  LCD_setxy(40,6+y);
                  for (x=0;x<8;x++) {
                     if (((y*8+x)==temp3)&&(temp2==1)) mode=2; // �� ������ ����� ������ 
                        else mode=0;  // ����� �� ������                                 
                     LCD_char(CHNUM_table[y*8+x], mode); // �������� ����� ������                    
                     LCD_X++; LCD_X++;
                  }
               }
               break;
      }   
   }

   mode=get_mnu_keys(); // ��������� ������� ������� ��������� �� ����
   switch (mode) { // �������� ������� �������

     case 238: { // ������ ������� UP (�����)
                  if (temp2>0) { temp2--; }
                  break; } 

     case 246: {  // ������ ������� DN (����)
                  switch (ftype) { // � ����������� �� ���� ������� - ���������� ������������� ����������  
                      case 1: { // ��� 1: �����������, 3 ���������
                                if (temp2<2) { temp2++;  }
                                break;
                      }
                      
                      case 2: { // ��� 2: ������������� �������
                                if (temp2<1) temp2++;
                                break;
                      }          
                  }
                  break; 
     }
                                 
     case 250: {  // ������ ������� EXIT (������� � ����������� ����)
                  
                  if ((ftype==2) && (chcount<4)) { // �� ��������� ��� ������
                     rmodel.CHANNELS.FILTER[filt_num].VAL1=0;
                     rmodel.CHANNELS.FILTER[filt_num].FILTER_TYPE=0;
                  } 
                  temp2=0; // �������� ��������� ���������� 
                  temp3=0; 
                  temp1=0;
                  temp4=0;
                  resetKeyReader(); // ����� ����������
                  menu_exe=0;
                  break; }
               
     case 252: {  // ������ ������� MENU/ENT
                  ModelChange=1;
                  resetKeyReader(); // ����� ����������
                  if (temp2>0)                                             
                  switch (ftype) {
                     case 1: { // ������ �����������
                              
                               break;
                     }        

                     case 2: { // ������ �������������
                                  x=rmodel.CHANNELS.FILTER[filt_num].VAL1 & temp4;
                                  if (x>0) rmodel.CHANNELS.FILTER[filt_num].VAL1=rmodel.CHANNELS.FILTER[filt_num].VAL1-temp4;
                                    else if (chcount<4) rmodel.CHANNELS.FILTER[filt_num].VAL1=rmodel.CHANNELS.FILTER[filt_num].VAL1+temp4; 
                               break;
                     }        

                  }
                  break; 
     } 

     case 222: {  // ������ ������� '-' (��������� ������)
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
                       case 1: { // ������ - �����������                                 
                                 if (temp2==1) { // ����������� ����� UCH 
                                    if (chnum<13) { chnum++;
                                      rmodel.CHANNELS.FILTER[filt_num].VAL1=valsc*256+chnum;
                                    } 
                                 }
                                 if (temp2==2) { // ����������� ���������� �������� 
                                    if (valsc<125) { valsc++;
                                      rmodel.CHANNELS.FILTER[filt_num].VAL1=valsc*256+chnum;
                                    } 
                                 }
                                 
                                 break;
                       }

                       case 2: { // ������ - �������������
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

     case 190: { //������ �������   '+' (��������� �����)
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
                         case 1: { // ������ - �����������
                                 if (temp2==1) { // ��������� ����� UCH 
                                    if (chnum>7) { chnum--;
                                      rmodel.CHANNELS.FILTER[filt_num].VAL1=valsc*256+chnum;
                                    } 
                                 }

                                 if (temp2==2) { // ��������� ���������� �������� 
                                    if (valsc>-125) { valsc--; 
                                      rmodel.CHANNELS.FILTER[filt_num].VAL1=valsc*256+chnum;
                                    } 
                                 }
                                 
                                 break;
                         }

                         case 2: { // ������ - �������������
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
                   � � � � � � � � � � � � � �    � � � � �   � � � � � �
       
                    (��������� ����������� ��� ������ ������ EDIT - NAME)       
**/
__flash const char Name_table[] = { // ������� ������������ ��� ������ ����� ������
        ' ','_','-','+','A','B','C','D','E','F',
        'G','H','I','J','K','L','M','N','O','P',
        'Q','R','S','T','U','V','W','X','Y','Z',
        '0','1','2','3','4','5','6','7','8','9'       
                                  };

void menu_EDIT_MODEL_NAME() {
unsigned int i,j; // ��������� ���������� ������
unsigned char mode;

   //��������� ��������� �� ������ ������
   if (temp1==0) { // � ��� ������ ������, �������������
     temp2=0; // ������� � ����� ������ 
     temp3=0; // ������� � ������ ��������
     temp1=1;
   }
 
   // �������� ���������
   LCD_setxy(0,0); LCD_wrsf("     EDIT MODEL NAME     ",1);

   LCD_setxy(10,2); LCD_wrsf("NAME: [", 0);

   for (i=0;i<8;i++) { // �������� ��� � ���������� ����� ��� ��������������
      if (i==temp2) { mode=2; } else { mode=0; }
      LCD_char(rmodel.MODEL_NAME[i], mode);
   }
   LCD_char(']', 0); 

   for (i=0;i<4;i++) { // ���� �����
      LCD_setxy(29,i+4);
      for (j=0;j<10;j++) { // ���� �������
         if (temp3==i*10+j) mode=1; else mode=0;
         LCD_char(Name_table[i*10+j], mode);
         LCD_X++; 
         LCD_X++;
      }
   } 

   mode=get_mnu_keys(); // ��������� ������� ������� ��������� �� ����
   switch (mode) { // �������� ������� �������

     case 238: { // ������ ������� UP (�����)
                  if (temp2>0) temp2--; else temp2=7;
                  break; } 

     case 246: {  // ������ ������� DN (����)
                  if (temp2<7) temp2++; else temp2=0;
                  break; } 
                                 
     case 250: {  // ������ ������� EXIT (������� � ����������� ����) 
                  temp2=0; // �������� ��������� ���������� 
                  temp3=0; 
                  temp1=0;
                  resetKeyReader(); // ����� ����������
                  menu_exe=0;
                  break; }
               
     case 252: {  // ������ ������� MENU/ENT (������� � ����������� ����/����� ���������)                                            
                  rmodel.MODEL_NAME[temp2]=Name_table[temp3]; // ��������� ��������� ������
                  if (temp2<7) temp2++; else temp2=0; // ������� ������ � ����� ������
                  ModelChange=1;
                  resetKeyReader(); // ����� ����������                 
                  break; } 

     case 222: {  // ������ ������� '-' (��������� ������)
                  if (temp3<39) temp3++; else temp3=0;
                  break; }

     case 190: { //������ �������   '+' (��������� �����)
                  if (temp3>0) temp3--; else temp3=39;
                  break; }
   }
}

/**
                � � � � � � � �   � � � � � � � � � � �   � � � � � � � � � �
                
        (��������� ����������� ��� ������ ������ SYSTEM - CALIBRATION - CALIBRATION INFO
**/
void menu_SYSTEM_CALIBRATION_INFO() {
unsigned int y; // ���������� ������
  LCD_setxy(0,0);
  LCD_wrsf("     CALIBRATION INFO    ", 1);
  
  for (y=0;y<7;y++) {

    LCD_setxy(0,y+1);
    LCD_wrsf(UCH_Names[y],0);   // �������� ��� ������
    LCD_char(' ',0); 
    LCD_dec(UCHmin[y],4,0);     // �������� ����������� �������� ������
    LCD_char(' ',0); 
    LCD_dec(UCHmid[y],4,0);     // �������� ������� �������� ������
    LCD_char(' ',0); 
    LCD_dec(UCHmax[y],4,0);     // �������� ������������ �������� ������

  }

  y=get_mnu_keys();
  switch (y) {
     case 250 : { resetKeyReader(); // ����� ����������
                   menu_exe=0; }
  }
  
}

/**
                   � � � � � � � � � �   � � � � � � � � � �   � � � � � � �
                   
         (��������� ����������� ��� ������ ������ SYSTEM - CALIBRATION - NEW CALIBRATION)                   
**/
unsigned char system_calibration_part;
void menu_SYSTEM_NEW_CALIBRATION() { 
unsigned char i, j, k; // ��������� ���������� ������
unsigned char ok; // ���������� ������� � �������� 
unsigned int v, v1, v2;

  LCD_setxy(0,0); LCD_wrsf("       CALIBRATION       ",1);   LCD_line(0, 10, 127, 10, 1);
 
  if (system_calibration_part==0) { //���� ������ ������..
    // ������������� �������������� �������� ��������� � �������� �������
    for (i=0; i<7; i++) { UCHmin[i]=UCH_VALUES[i]; UCHmax[i]=UCH_VALUES[i]; } 
    system_calibration_part=1; } // ������ ������� ��� ����� ��� ���     
  
  if (system_calibration_part==1) { // ��������� �������� �������
     ok=0;
     for (i=0; i<7; i++) { // ������� �� ������� ����� �������� ����������-��������� � ���������� ��
       if (UCHmin[i]>UCH_VALUES[i]) UCHmin[i]=UCH_VALUES[i]; 
       if (UCHmax[i]<UCH_VALUES[i]) UCHmax[i]=UCH_VALUES[i]; 
       LCD_rectangle(1+i*17, 12, 10+i*17, 42,  1);  // ������ �����
       LCD_setxy(3+i*17,6);     LCD_char(i+'0', 1); // ����������� ����� ������
       v=UCH_VALUES[i]-UCHmin[i];       v*=28;      v/=(UCHmax[i]-UCHmin[i]);   k=13+v;
       if (k<43)  { LCD_line(1+i*17, k, 10+i*17, k, 1); } // ������ ��������� 
     
       // ������������ ��������� ��� ������� ��������� ������
       v1=(UCHmax[i]-UCHmin[i])/2;    v2=UCH_VALUES[i]-UCHmin[i];
       if ((v2<(v1*107/100)) && (v2>(v1*100/107))) {
          for (j=k; j<42; j++) LCD_line(1+i*17, j, 10+i*17, j, 1);
          ok++;
       }     
       LCD_setxy(i*17+1, 7); LCD_dec(UCH_VALUES[i],3,0);  
     }
    // ��������� �� ������� ������
    j=get_mnu_keys(); 
    switch (j) {
       case 252 : { // ������ ENT\MENU - ��������� ���������� ����������
                 resetKeyReader(); // ����� ����������
//                if (ok==7) { // ��������� ��������� ���������� ������ � ������ ���� ��� 7 ����������
                // ������� ����� ���������� ����� ��������
                    for (i=0; i<7; i++) { 
                      UCHmid[i]=UCH_VALUES[i]; // ��������� �������� �������
                          // ��������� � epprom ��������� ����������
                      E_UCHmin[i]=UCHmin[i];
                      E_UCHmid[i]=UCHmid[i];
                      E_UCHmax[i]=UCHmax[i];
                    }
                           // ������ ������������ ��������� �� ����������
                      messStr1=" CALIBRATION COMPLETE !  ";

                      messStr2="All analog controls ready";
                      messStr3="";
                      messStr4="";
                      printMess=1;
                       
                // �������                 
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

     case 250 : { // ������ EXIT - ������� ��� ����������
                    for (i=0; i<7; i++) { 
                          // ����� �� �pprom ��������� ������� ����������
                      UCHmin[i]=E_UCHmin[i];
                      UCHmid[i]=E_UCHmid[i];
                      UCHmax[i]=E_UCHmax[i];
                    }
                   system_calibration_part=0; // � �������
                   menu_exe=0;
                   resetKeyReader(); // ����� ����������
                   break; } 
    }
  }
}

/**
             � � � � � � � � � � � � � E    � � � � � �    � � � � � � � �    � � � � � � � 

                  (��������� ����������� ��� ������ ������ ���� EDIT- FMODES - CURVES)
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


unsigned char fmode=0; // �������� �����
unsigned char mode;    // ����� ������
signed char cval; // �������� ������
unsigned char ch; // ��������� ����������- ����� ������ ��� ������
unsigned char lpx, lpy, px, py; // ���������� ����� ������
signed char curx; 

   //��������� ��������� �� ������ ������
   if (temp1==0) { // � ��� ������ ������, �������������
     temp2=0; // char ������� �� Y 
     temp3=0; // char  
     temp4=0; // int  ����� ������
     temp5=0; // ����� ������� �����
     temp1=1; // ������������� ������� ������������� ������� �������
     ModelChange=1;
   }
   
   switch (numitem_cur) {         // ���������� ����� ��������� ������ ��� ��������������
    case 112: { fmode=0; break; }
    case 117: { fmode=1; break; }
    case 122: { fmode=2; break; }
   }
   
   // �������� ���������
   LCD_setxy(0,0); LCD_wrsf("       CURVE  EDIT       ",1);

                  // �������� ����� ��������� ������
   //LCD_setxy(0,2); LCD_wrsf("F MODE: ", 0); 
   LCD_setxy(0,1); LCD_wrsf("F MODE: ", 0);
   LCD_char(fmode+0x31,0);

                  // �������� ����� ������
   if (temp2==0) mode=1; else mode=0;  
   //LCD_setxy(0,3); LCD_wrsf("LCH NUM: ", mode); 
   LCD_setxy(0,2); LCD_wrsf("LCH NUM: ", mode);
   if (mode==1) mode=2; else mode=0;
   if (temp4<9) ch=temp4+49; else ch=temp4+56; 
   LCD_char(ch,mode);
   
                 // �������� ������� ��������� ������
   if (temp2==1) mode=1; else mode=0; 
   //LCD_setxy(0,4); LCD_wrsf("CURVE: ", mode);
   LCD_setxy(0,3); LCD_wrsf("CURVE: ", mode);
   if (mode==1) mode=2; else mode=0; 
   switch (rmodel.FMODE[fmode].LCH_CURVE[temp4].active) {
      case 0: { LCD_wrsf(" OFF", mode); break; }
      case 1: { LCD_wrsf(" ON", mode); break; }
   }

                // ���� ������ ��������
if (rmodel.FMODE[fmode].LCH_CURVE[temp4].active==1) {

                 // �������� �������� ���������� SSS
   if (temp2==2) mode=1; else mode=0; 
   LCD_setxy(0,4); LCD_wrsf("EXPO:   ", mode);
   cval=rmodel.FMODE[fmode].LCH_CURVE[temp4].expon;
   if (mode==1) mode=2; else mode=0; 
   if (cval<0) { LCD_char('-',mode); cval=-cval; } else LCD_char('+',mode); 
   LCD_dec(cval,3,mode); LCD_char('%',mode);
 
                 // �������� ������� ������
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

                 // �������� �������� � ��������� �������
   if (temp2==4) mode=1; else mode=0; 
   LCD_setxy(0,6); LCD_wrsf("VALUE:  ", mode);
   
   cval=rmodel.FMODE[fmode].LCH_CURVE[temp4].point[temp5];
   if (mode==1) mode=2; else mode=0; 
   if (cval<0) { LCD_char('-',mode); cval=-cval; } else LCD_char('+',mode); 
   LCD_dec(cval,3,mode); LCD_char('%',mode);

   // ������ �����
   for (mode=0; mode<9; mode++) {
     LCD_dashline(     72,    12+mode*5,     112,      12+mode*5  );
     if (temp5==mode) LCD_line( 72+mode*5,    12,      72+mode*5,      52      ,1);
     else LCD_dashline( 72+mode*5,    12,      72+mode*5,      52      );  
   }

   LCD_line(72,  32, 112, 32, 1); // �������������� �����    

   // ������ ������ 
   curx=-100; //������ �����
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
   // ������������ ������� ����������� ������ ����
   mode=get_mnu_keys();
   switch (mode) {
      case 238: { // ������ ������� UP (�����)
                  if (temp2>0) temp2--; 
                  break; 
      } 

      case 246: {  // ������ ������� DN (����)
                  if (rmodel.FMODE[fmode].LCH_CURVE[temp4].active==1) {
                     //if (temp2<3) temp2++; else temp2=0; } else {
                     if (temp2<4) temp2++; else temp2=0; } else {
                        if (temp2<1) temp2++; else temp2=0; } 
                  break; 
      } 
                                 
      case 250: {  // ������ ������� EXIT (������� � ����������� ����) 
                  temp2=0; // �������� ��������� ���������� 
                  temp3=0;
                  temp4=0;
                  temp5=0; 
                  temp1=0;
                  resetKeyReader(); // ����� ����������
                  menu_exe=0;
                  CalcCurveORD();
                  break; 
      }
               
      case 252: {  // ������ ������� MENU/ENT          
                  resetKeyReader(); // ����� ����������                                   
                  break; 
      } 

      case 222: {  // ������ ������� '-' (��������� ������)
                  switch (temp2) {
                     case 0: { // ������ ����� 
                              if (temp4<(rmodel.CHANNELS.LCH_COUNT-1)) temp4++;
                              break;
                     }
                     case 1: { // ������ ��������� ����������� ������
                              if (rmodel.FMODE[fmode].LCH_CURVE[temp4].active==1)
                                 rmodel.FMODE[fmode].LCH_CURVE[temp4].active=0; else
                                   rmodel.FMODE[fmode].LCH_CURVE[temp4].active=1; 
                              break;  
                     }
                     case 2: { // ����������� %% ����������
                              if (rmodel.FMODE[fmode].LCH_CURVE[temp4].expon<100) {
                                rmodel.FMODE[fmode].LCH_CURVE[temp4].expon++;
                                menu_FMODE_CURVES_EXPO(fmode,temp4); // ������������� ������     
                                }
                              break;  
                     }                    
                     case 3: { // ������ ����� �������
                              if (temp5<8) temp5++; 
                              break;
                     }
                     case 4: { // ����������� �������� �����
                              if (rmodel.FMODE[fmode].LCH_CURVE[temp4].point[temp5]<100) 
                                 rmodel.FMODE[fmode].LCH_CURVE[temp4].point[temp5]++;
                              break;
                          
                     } 
                  }
                  break; 
      }

     case 190: { //������ �������   '+' (��������� �����)
                  switch (temp2) {
                     case 0: { // ������ ����� 
                              if (temp4>0) temp4--;
                              break;
                     }
                     case 1: { // ������ ��������� ����������� ������
                              if (rmodel.FMODE[fmode].LCH_CURVE[temp4].active==1)
                                 rmodel.FMODE[fmode].LCH_CURVE[temp4].active=0; else
                                   rmodel.FMODE[fmode].LCH_CURVE[temp4].active=1; 
                              break;  
                     }
                     case 2: { // ��������� ������� ����������
                              if (rmodel.FMODE[fmode].LCH_CURVE[temp4].expon > -100) {
                                rmodel.FMODE[fmode].LCH_CURVE[temp4].expon--;
                                menu_FMODE_CURVES_EXPO(fmode,temp4); // ������������� ������          
                                }
                              break;  
                     }       
                     case 3: { // ������ ����� �������
                              if (temp5>0) temp5--; 
                              break;
                     }
                     case 4: { // ��������� �������� �����
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
              � � � � � � � � � � � � � �   � � � � � � � �   � � � � � � � � �   � � � � � �

                (��������� ����������� ��� ������ ������ ���� MODEL - FMODE - MIXER)
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
void FMODE_MIXERS_editmix(unsigned char fmode, unsigned char mixnum){ // ������������ �������������� ������� 
unsigned char ACTIVE; // ������� ���������� �������

unsigned char MIX_SW; // ������� ����������� �������
unsigned char UCH_SW; // ����������� �������
unsigned char SW_INV; // ������� �������� �����������

unsigned char DEST_CH; //  ����� ����������

unsigned char SOURSE_CH; // ����� ��������
unsigned char SOURSE_TYPE; // ��� ������ ���������

unsigned char PROC_SOURSE; // ��� ��������� ������������ ������������
signed char MIX_VAL; // �������� ������������ (�������������)
signed char MX_VAL;
unsigned char MIX_UCH; // �������� ������������ ������ UCH
unsigned char MIX_INV; // �������� �������� ������������ ������ UCH

unsigned char mode, modex; // ������ ������

unsigned char tmp; // ��������� ����������

// ����� �������� ����� �� �������
 ACTIVE=rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.ACTIVE;  // ������ ������� (����������)
 
 MIX_SW=rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.MIX_SW; //  ��� ����������� �������
 UCH_SW=7+rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.UCH_SW; //  ����� ����������� �������
 SW_INV=rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.SW_INV;
 
 DEST_CH=rmodel.FMODE[fmode].MIXER[mixnum].CH_NUM.CH_DEST; // ����� ����������

 SOURSE_TYPE=rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.SOURSE_TYPE; // ��� ���������
 SOURSE_CH=rmodel.FMODE[fmode].MIXER[mixnum].CH_NUM.CH_SOURSE; // ����� ��������

 PROC_SOURSE=rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.PROC_SOURSE; // ��� �������� ������������
 MIX_VAL=rmodel.FMODE[fmode].MIXER[mixnum].MIX_VAL; // ������������� �������� ������������

 MIX_UCH=0x0F & rmodel.FMODE[fmode].MIXER[mixnum].MIX_VAL; // ����� �������� ������������ ������������
 if ((0x10&rmodel.FMODE[fmode].MIXER[mixnum].MIX_VAL)!=0) MIX_INV=1;  // �������� �������� ������������
   else MIX_INV=0;
 
  
   if (temp4==0) mode=1; else mode=0; // ���� ����� � ������ �� �������� ��� ��� ��������� ���������
   
   LCD_setxy(0,2);
   LCD_wrsf("ACTIVE: ",mode);

   if (mode==1) { 
      if (temp5==1) modex=2; else modex=1;  
   } else modex=0;
   if (ACTIVE==1) LCD_wrsf("ON", modex); else LCD_wrsf("OFF", modex);
   
// �������� ����������� �������   
   if (temp4==1) mode=1; else mode=0;        // ������ ���������� ����� ��������� 

   LCD_setxy(0,3);              // 
   LCD_wrsf("SWITCH: ",mode);

   if (mode==1) {                                   // ������ ���������:
      if (temp5==1) modex=2; else modex=1;  
   } else modex=0;
   if (MIX_SW==0) LCD_wrsf("OFF", modex); // ������ �������� 
      else {   // ���������
         LCD_wrsf("ON ", modex);

         if (mode==1) {                                // ��� �����������
           if (temp5==2) modex=2; else modex=1;  
         } else modex=0;
          
         // �������� ���� ����������� �������
         if (SW_INV==1) LCD_wrsf("-", modex); else LCD_wrsf("+", modex); // ����  
  
         LCD_char(' ',mode);
         
         if (mode==1) {                                // ��� �����������
           if (temp5==3) modex=2; else modex=1;  
         } else modex=0;
         LCD_wrsf(UCH_SNAMES[UCH_SW],modex);     
      }

// �������� ����� ����������   
   if (temp4==2) mode=1; else mode=0;        // ������ ���������� ����� ��������� 
   LCD_setxy(0,4);              // 
   LCD_wrsf("DEST:   ",mode);
   
   if (mode==1) { 
      if (temp5==1) modex=2; else modex=1;  
   } else modex=0;
   if (DEST_CH<9) tmp=DEST_CH+49; else tmp=DEST_CH+56; 
   LCD_char(tmp,modex);

// �������� ����� ��������
   if (temp4==3) mode=1; else mode=0;        // ������ ���������� ����� ���������
   LCD_setxy(0,5);
   LCD_wrsf("SOURCE: ",mode);
   
   if (SOURSE_TYPE==0) { // ������������ � UCH
     if (mode==1) { 
       if (temp5==1) modex=2; else modex=1;  
     } else modex=0;
     LCD_wrsf("UCH ",modex);
     
     if (mode==1) { 
       if (temp5==2) modex=2; else modex=1;  
     } else modex=0;
     LCD_wrsf(UCH_SNAMES[SOURSE_CH],modex);
        
   } 
   
   else { // ������������ � LCH
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

// �������� ������� ������������
   if (temp4==4) mode=1; else mode=0;        // ������ ���������� ����� ���������
   LCD_setxy(0,6);
   LCD_wrsf("MIX %: ",mode);
   
   if (mode==1) { 
     if (temp5==1) modex=2; else modex=1;  
   } else modex=0;

   if (PROC_SOURSE==0) { // ������������� �������� ������������
     LCD_wrsf("FIX ",modex);

   if (mode==1) { 
     if (temp5==2) modex=2; else modex=1;  
   } else modex=0;
     
     if (MIX_VAL<0) { LCD_char('-',modex); MX_VAL=-MIX_VAL; } else { LCD_char('+',modex); MX_VAL=MIX_VAL;}
     LCD_dec(MX_VAL,3,modex);
   } 
   
   else { // �������� ������������ �� ������ UCH
     LCD_wrsf("UCH ",modex);

     if (mode==1) { // �������� ���� ������������ UCH 
       if (temp5==2) modex=2; else modex=1;  
     } else modex=0;
   
     if (MIX_INV!=0) { LCD_char('-',modex); } else LCD_char('+',modex);  

     LCD_char(' ',mode);
     
     if (mode==1) { // �������� ����� ������ UCH 
       if (temp5==3) modex=2; else modex=1;  
     } else modex=0;
     LCD_wrsf(UCH_SNAMES[MIX_UCH],modex);
   }
   

   mode=get_mnu_keys(); // ��������� ������� ������� ��������� �� ����
   switch (mode) { // �������� ������� �������

     case 238: { // ������ ������� UP (�����)
                  switch (temp5) { // � ����������� �� ��������� �� � �������:
                  
                     case 0: { // ������� �������� ���������
                               // ���� �����
                               if (temp4>0) temp4--;
                               break;
                     }
                     
                     case 1: { // � ����������� �� ������ �������� ������ ��������  ���������
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
                                           // UCH ������� ����� 14 ���� ����� �� ������ �� ������� ����� !
                                           if (SOURSE_CH<13) SOURSE_CH++; else SOURSE_CH=0;
                                          break;
                                 }
                                 case 4: { // PROC
                                           if (PROC_SOURSE==0) { // ���� ������������ �������������
                                              if (MIX_VAL<125) MIX_VAL++; // ����������� MIX_VAL
                                           } 
                                             else { // ���� ������������ UCH �� �������� ���� ������������
                                              if (MIX_INV==0) MIX_INV=1; else MIX_INV=0;
                                             }
                                          break;
                                 }
                              }
                              break;
                     }
                     
                     case 3: { // ����������� ������ ��������
                              switch (temp4) {
                                 case 1: { // SWITCH
                                           if (UCH_SW<13) UCH_SW++; // ������ ����� UCH
                                          break;
                                 }

                                 case 4: { // PROC
                                          if (MIX_UCH<13) MIX_UCH++; // ������ ����� UCH 
                                          break;
                                 }
                              }

                              break;
                     }
                     
                  }
                  break; 
     }
                  

     case 246: {  // ������ ������� DN (����)
                  switch (temp5) {
                     case 0: { // ������� �������� ���������
                               // ���� ���� 
                               if (temp4<4) temp4++;
                               break;
                     }

                     case 1: { // � ����������� �� ������ �������� ������ ��������  ���������
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
                                 case 4: { // PROC ������ ��� ��������� ������������ ������������
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
                                           // UCH ������� ����� 14 ���� ����� �� ������ �� ������� ����� !
                                           if ((SOURSE_TYPE==0) && (SOURSE_CH>13)) SOURSE_CH=0;
                                          break;
                                 }
                                 case 4: { // PROC
                                           if (PROC_SOURSE==0) { // ���� ������������ �������������
                                              if (MIX_VAL>-125) MIX_VAL--; // ��������� MIX_VAL
                                           } 
                                             else { // ���� ������������ UCH �� �������� ���� ������������
                                              if (MIX_INV==0) MIX_INV=1; else MIX_INV=0;
                                             }
                                          break;
                                 }
                              }
                              break;
                     }
                     
                     case 3: { // ����������� ������ ��������
                              switch (temp4) {
                                 case 1: { // SWITCH
                                           if (UCH_SW>7) UCH_SW--; // ������ ����� UCH
                                          break;
                                 }

                                 case 4: { // PROC
                                          if (MIX_UCH>0) MIX_UCH--; // ������ ����� UCH 
                                          break;
                                 }
                              }

                              break;
                     }
                  }
                  break; 
     } 
                                 
     case 250: {  // ������ ������� EXIT (������� � ����������� ����)
                  temp3=0; // ����� �� ������ ���������
                  resetKeyReader(); // ����� ����������
                  getMixCount(FMODE_NUM);
                  mixtochan=mixercount/rmodel.CHANNELS.PPM_CH_COUNT;
                  mixtochanlast=mixercount%rmodel.CHANNELS.PPM_CH_COUNT;                  
                  break; }
               
     case 252: {  // ������ ������� MENU/ENT (������� � ����������� ����/����� ���������)
                  switch (temp4) { // � ����������� �� ������ � ������� ���������
                     case 0: {  // ������� ACTIVE �������
                               if (temp5<1) temp5++; else temp5=0;
                               break;
                     }

                     case 1: {  // SWITCH
                                if (MIX_SW==0) { // ��� ������� 
                                  if (temp5<1) temp5++; else temp5=0; } 
                                else {  // ���� ������
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
                                if (PROC_SOURSE==0) { // ������������� ��������
                                   if (temp5<2) temp5++; else temp5=0; }
                                else { if (temp5<3) temp5++; else temp5=0; }// �������� UCH
                               break;
                     }
                  }
                  break; } 

     case 222: {  // ������ ������� '-' (��������� ������)
                  switch (temp4) { // � ����������� �� ������ � ������� ���������
                     case 0: {  // ������� ACTIVE �������
                                if (temp5<1) temp5++;
                               break;
                     }

                     case 1: {  // SWITCH
                                if (MIX_SW==0) { // ��� ������� 
                                  if (temp5<1) temp5++; } 
                                else {  // ���� ������
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
                                if (PROC_SOURSE==0) { // ������������� ��������
                                   if (temp5<2) temp5++; }
                                else if (temp5<3) temp5++; // �������� UCH
                               break;
                     }


                  }
                  break; 
     }

     case 190: { //������ �������   '+' (��������� �����)
                  if (temp5>0) temp5--;
                  break; 
     }
   } // ����� ����� ������ � �������� ���������

// ��������� �������� ����� �� �������

   if ((ACTIVE==0) && (temp3==0)) {
      for (tmp=mixnum;tmp<40;tmp++) 
        rmodel.FMODE[fmode].MIXER[tmp]=rmodel.FMODE[fmode].MIXER[(unsigned char) (tmp+1)];
   }  
   
   else {
     rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.ACTIVE=ACTIVE;  // ������ ������� (����������)
 
     rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.MIX_SW=MIX_SW; //  ��� ����������� �������
 
     rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.UCH_SW=UCH_SW-7; //  ����� ����������� �������
     rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.SW_INV=SW_INV;
 
     rmodel.FMODE[fmode].MIXER[mixnum].CH_NUM.CH_DEST=DEST_CH; // ����� ����������

     rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.SOURSE_TYPE=SOURSE_TYPE; // ��� ���������
 
     rmodel.FMODE[fmode].MIXER[mixnum].CH_NUM.CH_SOURSE=SOURSE_CH; // ����� ��������

     rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.PROC_SOURSE=PROC_SOURSE; // ��� �������� ������������
     if (PROC_SOURSE==0) 
       rmodel.FMODE[fmode].MIXER[mixnum].MIX_VAL=MIX_VAL; // ������������� �������� ������������
       else rmodel.FMODE[fmode].MIXER[mixnum].MIX_VAL=MIX_UCH+MIX_INV*16; 

   }
}

void menu_FMODE_MIXERS() {
unsigned char fmode;
// unsigned char mixcount; // ���������� ��������
unsigned char offs; // �������� ��� ������
unsigned char i;// ��������� ���������� ������

unsigned char x; // - ���������� ����� ��� ������
unsigned char y; // -    �������� �������
unsigned int ii; // ���������� �������� ��� ������ �������� �������

unsigned char mode; // ����� ������
unsigned char MIX_SW, SOURSE_TYPE, PROC_SOURSE; // �������� �������������� ����� ���������� �������
unsigned char mixnum; // ����� �������
unsigned char UCH_SW; // ����� ����������� �������
// unsigned char SW_INV; // �������� ����������� �������
unsigned char CH_DEST; // ����� ����������
unsigned char CH_SOURSE; // ����� ��������
unsigned char tmp; // ��������� ����������
signed char S_MIX_VAL; // �������� ������������ �� ������
unsigned char MIX_VAL; // �������� ������������ ��� �����
unsigned char MIX_UCH; // ����� �������� ������������ ������������
unsigned char MIX_INV; // ������� �������� �������� ������
unsigned char mixmax; // ������������ �������� ������� 

   //��������� ��������� �� ������ ������
   if (temp1==0) { // � ��� ������ ������, �������������
     temp2=0; // char ����� ������� ��� �������������� 
     temp3=0; // char  
     temp4=0; // int  
     temp5=0; // char
     temp1=1; // ������������� ������� ������������� ������� �������
     ModelChange=1; // ������� ��������� ������
   }
   
   switch (numitem_cur) {         // ���������� ����� ��������� ������ ��� ��������������
    case 113: { fmode=0; break; }
    case 118: { fmode=1; break; }
    case 123: { fmode=2; break; }
   }
   
   // �������� ���������
   LCD_setxy(0,0); LCD_wrsf("       MIXER  EDIT       ",1);

  if (temp3==3) { // ����� ������ ����������� �������� �������� �������
  
      // ������� ���������� �������� ������� 
                for (x=0;x<2;x++) { // ��� �������
                   for (y=0;y<4;y++) { // 4 ������
                      if ((x*4+y)<rmodel.CHANNELS.PPM_CH_COUNT) { // ���� ����� ����� ����������
                     
                         LCD_setxy(10+x*60,y+2); // ������� ����� ������ 
                         LCD_wrsf("CH",0); LCD_dec((unsigned char)(x*4+y+1),1,0);
                         LCD_char(' ',0);
                        
                         if ((CH_PPM[(unsigned char)(x*4+y)]>=rmodel.CHANNELS.CH_EPL[(unsigned char)(x*4+y)]) && 
                            (CH_PPM[(unsigned char)(x*4+y)]<=rmodel.CHANNELS.CH_EPR[(unsigned char)(x*4+y)]))  {
                            // ���� ������������ ������ ������ �������� ���� ��������
                            // ������� ����� �������� 
                            ii=(CH_PPM[(unsigned char)(x*4+y)] - rmodel.CHANNELS.CH_EPL[(unsigned char)(x*4+y)]);
                        
                            ii=ii /
                                  (( rmodel.CHANNELS.CH_EPR[(unsigned char)(x*4+y)] - 
                                                       rmodel.CHANNELS.CH_EPL[(unsigned char)(x*4+y)]) / 25) ;
                        
                            for (i=0;i<(unsigned char)ii; i++) {
                               LCD_out(0x7E);     
                             }
                             // ������� ��������� �����
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

     mode=get_mnu_keys(); // ��������� ������� ������� ��������� �� ����
     switch (mode) { // �������� ������� �������                                 
       case 250: {  // ������ ������� EXIT (������� � ����������� ����) 
                  temp3=0; // ����� ���������
                  resetKeyReader(); // ����� ����������
                  break; }             

       case 222: {  // ������ ������� '-' (��������� ������)
                  temp3=3; // ���������� ���������� ������� ������������� �������
                  break; }

       case 190: { //������ �������   '+' (��������� �����)
                  temp3=2; // ���������� �������� ������� ������������� �������
                  break; }
     } // ����� ����� ������ � �������� ���������
       
  } 
  
  else

  if (temp3==2) { // ����� ������ ��������� �������� �������� �������
  
      // ������� � ������ �������� ������� 
      for (x=0;x<2;x++) { // ��� �������
         for (y=0;y<4;y++) { // 4 ������
             if ((x*4+y)<rmodel.CHANNELS.PPM_CH_COUNT) {
                 LCD_setxy(10+x*65,y+2); 
                 LCD_wrsf("CH",0); LCD_dec((unsigned char)(x*4+y+1),1,0);
                 LCD_char(' ',0);
                 LCD_dec(CH_PPM[(unsigned char)(x*4+y)],4,0);
             }
         }
      }

     mode=get_mnu_keys(); // ��������� ������� ������� ��������� �� ����
     switch (mode) { // �������� ������� �������                                 
       case 250: {  // ������ ������� EXIT (������� � ����������� ����) 
                  temp3=0; // ����� ���������
                  resetKeyReader(); // ����� ����������
                  break; }             

       case 222: {  // ������ ������� '-' (��������� ������)
                  temp3=3; // ���������� ���������� ������� ������������� �������
                  break; }

       case 190: { //������ �������   '+' (��������� �����)
                  temp3=2; // ���������� �������� ������� ������������� �������
                  break; }
     } // ����� ����� ������ � �������� ���������
       
  } 
  
  else
   
   if (temp3==1) {  // - - - - - - - - - - - - - - -����� �������������� �������
     FMODE_MIXERS_editmix(fmode, temp2);   
   }
     else 
{  // - - - - - - - - - - - - - ����� ��������� � ������ ������� ��� ��������������
   //����� �������
   LCD_setxy(0,1); LCD_wrsf("NO TYP SWIT. D SOUR PROC.", 0);
   mode=0;
   if (temp2>5) offs=temp2-5; else offs=0;

   for (i=0;i<6;i++) {

      mixmax=39;
      mixnum=i+offs;

      LCD_setxy(0,2+i); 
      
      if (mixnum==temp2) mode=1; else mode=0; // ���� ������� ������ � ������� ������� - �������� ���
      
      // �������� ������� ������� � offs 5 ����� ������ ���� ���� �� �������� ������ ������
      if (rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.ACTIVE==1) { // ������ ����

// �������� ����� �������
        LCD_dec((unsigned char)(mixnum+1),2,mode);  
        LCD_char(' ',mode);

// �������� ��� �������
         MIX_SW=rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.MIX_SW;
         if (MIX_SW==1) { // ����������� �������
            LCD_char('S',mode); } else { LCD_char('-',mode); }

         SOURSE_TYPE=rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.SOURSE_TYPE;
         if (SOURSE_TYPE==1) { // ��� ���������
            LCD_char('L',mode); } else { LCD_char('U',mode); }

         PROC_SOURSE=rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.PROC_SOURSE;
         if (PROC_SOURSE==1) { // �������� ������������
            LCD_char('U',mode); } else { LCD_char('F',mode); }

        LCD_char(' ',mode); // ������ ����� ���� �������

// ������ ����������� �������
        if (MIX_SW==1) { // ���� � ������� ���� ����������� - �������� ���
        
           UCH_SW=rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.UCH_SW;

           // ���� ���� �������� ����������� - �������� '-' ����� �������� ������
           if (rmodel.FMODE[fmode].MIXER[mixnum].MIX_TYPE.SW_INV==1) LCD_char('-',mode); 
             else LCD_char(' ',mode);

           LCD_wrsf(UCH_SNAMES[(unsigned char)(UCH_SW+7)],mode); // �������� �������� �����������
        } 
           else { // ����������� ��� - �������� ��������
             LCD_wrsf("-----",mode);
           }
           LCD_char(' ',mode);
        
// ������ ������ ����������
          CH_DEST=rmodel.FMODE[fmode].MIXER[mixnum].CH_NUM.CH_DEST; // ����� ����������
          if (CH_DEST<9) tmp=CH_DEST+49; else tmp=CH_DEST+56; 
          LCD_char(tmp,mode);
          LCD_char(' ', mode);
          
// ������ ������ ���������
          CH_SOURSE=rmodel.FMODE[fmode].MIXER[mixnum].CH_NUM.CH_SOURSE; // ����� ��������
          
          if (SOURSE_TYPE==1) { // �������� ����� LCH
             LCD_char(' ', mode);
             if (CH_SOURSE<9) tmp=CH_SOURSE+49; else tmp=CH_SOURSE+56; 
             LCD_char(tmp,mode);
             LCD_char(' ', mode);
             LCD_char(' ', mode);
          }
             else { // �������� ����� UCH
             LCD_wrsf(UCH_SNAMES[CH_SOURSE],mode);
             }
          LCD_char(' ',mode);
          
// ������ �������� ������������
          if (PROC_SOURSE==1) { // ������������ ������� ������������
            MIX_VAL=rmodel.FMODE[fmode].MIXER[mixnum].MIX_VAL; // ����� ��������
            MIX_UCH=MIX_VAL & 0x0F; // �������� ����� �������� �������� ������������
            if ((MIX_VAL-MIX_UCH)!=0) { LCD_char('-',mode); MIX_INV=1; 
            } 
              else { MIX_INV=0; // �������� �������� �������� ������������
                     LCD_char(' ',mode); }
           
            LCD_wrsf(UCH_SNAMES[MIX_UCH],mode);            
           
          } else { // ������������� ������� ������������
             S_MIX_VAL=rmodel.FMODE[fmode].MIXER[mixnum].MIX_VAL;
             if (S_MIX_VAL<0) { LCD_char('-',mode); S_MIX_VAL=-S_MIX_VAL; } else LCD_char('+',mode);
             LCD_dec(S_MIX_VAL,3,mode); 
          }
      } 
         else { // ������� ���
            LCD_wrsf("-- --- ----- - ---- -----", mode);
            mixmax=mixnum;
           break; // ��������� ���� ���������?
         }
   } 

   mode=get_mnu_keys(); // ��������� ������� ������� ��������� �� ����
   switch (mode) { // �������� ������� �������

     case 238: { // ������ ������� UP (�����)
                  if (temp2>0) temp2--;
                  break; } 

     case 246: {  // ������ ������� DN (����)
                  if (temp2<mixmax) temp2++;
                  break; } 
                                 
     case 250: {  // ������ ������� EXIT (������� � ����������� ����) 
                  temp2=0; // ����� ������� ��� �������������� 
                  temp3=0; // ����� ���������
                  temp4=0;
                  temp5=0;
                  temp1=0; // ������� ������� �������
                  resetKeyReader(); // ����� ����������
                  menu_exe=0;
                  break; }
               
     case 252: {  // ������ ������� MENU/ENT (������� � ����������� ����/����� ���������)
                  temp3=1; // �������� ����� �������������� �������
                  temp4=0; // ������ �������������� �������
                  temp5=0; // ������� �������������� �������
                  resetKeyReader(); // ����� ����������                                            
                  break; } 

     case 222: {  // ������ ������� '-' (��������� ������)
                  temp3=3; // ���������� ���������� ������� ������������� �������
                  break; }

     case 190: { //������ �������   '+' (��������� �����)
                  temp3=2; // ���������� �������� ������� ������������� �������
                  break; }
   } // ����� ����� ������ � �������� ���������
   
} // ����� ����� ��������� � ������ ������� ��� ��������������

} // ����� ������������


/**
                        � � � � �    � � � � � �
    
               (��������� ����������� ��� ������ ������ ���� FILE - RESET )
**/    
void FILE_RESET() {
unsigned char rkey,i,j;
// -------------------------------------------------------------------------------------- ������������� ������  
   
  rmodel.MODEL_TYPE=0;      // ��� - �������
  
  rmodel.MODEL_NAME[0]='N'; // ��� ������
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
                                      // ���������� ����������� ������������� ��������� ���������
    rmodel.CHANNELS.CH_EPL[rkey]=1000;
    rmodel.CHANNELS.CH_EPR[rkey]=2000;
                                      // �������� ��������� �������� �������
    rmodel.CHANNELS.LCHDELDN[rkey]=0;
    rmodel.CHANNELS.LCHDELUP[rkey]=0; 
                                      // ������� ������� ������
    rmodel.CHANNELS.LCH_REV[rkey]=0;
                                      // ���������� �������� ������� 
                                      // �������� �������
    rmodel.FMODE[0].LCH_MIDLE[rkey]=1500; //
    rmodel.FMODE[1].LCH_MIDLE[rkey]=1500; //
    rmodel.FMODE[2].LCH_MIDLE[rkey]=1500; //   
                                          // ������ �������

    rmodel.FMODE[0].LCH_CURVE[rkey].active=0; // ������ ���������   
    rmodel.FMODE[0].LCH_CURVE[rkey].expon=0; // ���������� ���������
                                          
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
  
  rmodel.CHANNELS.LCH_COUNT=8;   // ���������� ������������ ������� � ������ 
 
  for (rkey=0; rkey<8; rkey++) { // ������� ������� ������ ��������
    rmodel.CHANNELS.FILTER[rkey].FILTER_TYPE=0;
    rmodel.CHANNELS.FILTER[rkey].VAL1=0; 
  }

    for (i=0;i<3;i++) { // ���������� �������� ������

            // ��� ��������� �������� �������
     rmodel.FMODE[i].TRIMSTEP=1; 
  
     for (j=0;j<40;j++) { // ���������� ������� ��������� ������
        rmodel.FMODE[i].MIXER[j].MIX_TYPE.ACTIVE=0;       // ������ �������
        rmodel.FMODE[i].MIXER[j].MIX_TYPE.SOURSE_TYPE=0;  // ��� ��������� UCH
        rmodel.FMODE[i].MIXER[j].MIX_TYPE.PROC_SOURSE=0;  // ������������� �������� ������������
        rmodel.FMODE[i].MIXER[j].MIX_TYPE.MIX_SW=0;       // ����������� ������� ���
        rmodel.FMODE[i].MIXER[j].MIX_TYPE.SW_INV=0;       // �������� ����������� 
        rmodel.FMODE[i].MIXER[j].MIX_TYPE.UCH_SW=0;       // ����������� �������      
        rmodel.FMODE[i].MIXER[j].CH_NUM.CH_SOURSE=0;      // ����� �������� 
        rmodel.FMODE[i].MIXER[j].CH_NUM.CH_DEST=0;        // ����� ����������
        rmodel.FMODE[i].MIXER[j].MIX_VAL=100;             // ������� ������������
     }
  }

  for (rkey=0; rkey<14; rkey++) { // ���������� �������� UCH
     rmodel.UCH[rkey].UCH_LEFT=-100;
     rmodel.UCH[rkey].UCH_RIGHT=100;
  }
 
     rmodel.CHANNELS.PPM_CH_COUNT=8; // ���������� ������� � ����� PPM
     PPM_PAUSE=0;     // ����� ������� ������
     PPM_CUR_CH_NUM=0; // ����� ������ ������

     // ���������� ������� ����� LCH � ������������ � �������� ������� � ���������� �������
     for (i=0;i<rmodel.CHANNELS.LCH_COUNT;i++) {
         LCH_LEN[i]=rmodel.FMODE[FMODE_NUM].LCH_MIDLE[i];
     }
     
    for (i=0; i<8; i++) rmodel.PPM_TO_LCH_CAP[i]=0; // ����� ������ ������������� ������� PPM

  resetKeyReader(); // ����� ����������
}

void menu_FILE_RESET() { 
unsigned char mode;

LCD_setxy(0,0);  LCD_wrsf(" RESET CURRENT MODEL     ",1);

LCD_setxy(0,2);  LCD_wrsf(" to cancel press MENU   >",0);

LCD_setxy(0,6);  LCD_wrsf("to process press - EXIT >",0);

   mode=get_mnu_keys(); // ��������� ������� ������� ��������� �� ����
   switch (mode) { // �������� ������� �������

     case 238: { // ������ ������� UP (�����)
                  break; } 

     case 246: {  // ������ ������� DN (����)
                  break; } 
                                 
     case 252: {  // ������ ������� MENU/ENT (������� � ����������� ����) 
                  temp2=0; // ����� ������� ��� �������������� 
                  temp3=0; // ����� ���������
                  temp4=0;
                  temp5=0;
                  temp1=0; // ������� ������� �������
                  resetKeyReader(); // ����� ����������
                  menu_exe=0;
                  break; }
               
     case 250: {  // ������ ������� EXIT (������� � ����������� ����/����� ���������)
                  FILE_RESET();
                  E_CurModelNum=255;
                  ModelChange=0;
                  temp2=0; // ����� ������� ��� �������������� 
                  temp3=0; // ����� ���������
                  temp4=0;
                  temp5=0;
                  temp1=0; // ������� ������� �������
                  resetKeyReader(); // ����� ����������
                  menu_exe=0;                  
                  break; } 

     case 222: {  // ������ ������� '-' (��������� ������)
                  break; }

     case 190: { //������ �������   '+' (��������� �����)
                  break; }
   } // ����� ����� ������ � �������� ���������

}

/**
                       � � � � � � � �    � � � � � �    � �    � � � � � �
**/
void OpenModel(unsigned char filenum) {
unsigned char i,j,k,tmp; // ��������� ���������� 
unsigned int  ti,i1,i2;

FILE_RESET(); // ������� ������� ��������� ������
FMODE_NUM=0;

  if (fileToRead(filenum)==0) { // ���� ���������� � ������
    // ������ ��� ������
    rmodel.MODEL_TYPE=fileRead();
    // ������ ��� ������
    for(i=0;i<8;i++) {
      rmodel.MODEL_NAME[i]=fileRead();
    }
    // ������ �������� ������
    i1=fileRead();
    i2=fileRead();
    ti=i1+i2*256;
    rmodel.MODEL_FLYTIMER=ti;
    flyCurrTimer=rmodel.MODEL_FLYTIMER;

    // ������ ����� ����� ������
    i1=fileRead();
    i2=fileRead();
    ti=i1+i2*256;
    rmodel.MODEL_LIVETIMER=ti;
    
    // ������ LCH
    rmodel.CHANNELS.LCH_COUNT=fileRead(); // ���������� ������� ������
    // ������ LCH EPL
    for (i=0; i<rmodel.CHANNELS.LCH_COUNT; i++) {

       i1=fileRead();
       i2=fileRead();
       ti=i1+i2*256;
       rmodel.CHANNELS.CH_EPL[i]=ti;
    } 
    // ������ LCH EPR
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
   
    // ������ ���������� � CH
    rmodel.CHANNELS.PPM_CH_COUNT=fileRead();
    // ������ ���������� � �������� �������
    for (i=0; i<rmodel.CHANNELS.PPM_CH_COUNT; i++) {
       //������ ���� �������
       rmodel.CHANNELS.FILTER[i].FILTER_TYPE=fileRead(); 
       // ������ ��������� �������
       i1=fileRead();
       i2=fileRead();
       ti=i1+i2*256;
       rmodel.CHANNELS.FILTER[i].VAL1=ti;
    }
    
    // ������ ���������� � ������� UCH
    i=fileRead();
    while (i!=0) {
       rmodel.UCH[i-1].UCH_LEFT=fileRead();
       rmodel.UCH[i-1].UCH_RIGHT=fileRead();
       i=fileRead();
    }

    // ------
    // ���������� �������� �������
    rmodel.FMODE_COUNT=fileRead();
    for (i=0;i<rmodel.FMODE_COUNT;i++) {  // ���� ���������� �������� �������

       // ��� ��������� ������
       rmodel.FMODE[i].FMODE_NAME=fileRead();

       // ��� ���������
       rmodel.FMODE[i].TRIMSTEP=fileRead();

       // �������� �������
       for (j=0;j<7;j++) {
          rmodel.FMODE[i].UCH_TRIMMER[j]=fileRead();
       }

       // ������� ����� �������
       for (j=0;j<rmodel.CHANNELS.LCH_COUNT;j++) {
         i1=fileRead();
         i2=fileRead();
         ti=i1+i2*256;
         rmodel.FMODE[i].LCH_MIDLE[j]=ti;
       }

       // ������ �������
       for (j=0;j<rmodel.CHANNELS.LCH_COUNT;j++) {
          switch (fileRead()) {
             case 0 : { // ��� ������
                        rmodel.FMODE[i].LCH_CURVE[j].active=0; // ��� ������
                        break;
             }
             case 1 : { // ������ ������ ��� ����������       
                        rmodel.FMODE[i].LCH_CURVE[j].active=1; // ������ ���� !
                        for (k=0;k<9;k++) { // ������ 9 ����� ������
                          rmodel.FMODE[i].LCH_CURVE[j].point[k]=fileRead();
                        }
                        break;
             }
             case 100:{ // ������ � �����������             
                        rmodel.FMODE[i].LCH_CURVE[j].active=1; // ������ ���� !
                        rmodel.FMODE[i].LCH_CURVE[j].expon=fileRead(); // ������ �������� ����������
                        for (k=0;k<9;k++) { // ������ 9 ����� ������
                          rmodel.FMODE[i].LCH_CURVE[j].point[k]=fileRead();
                        }           
                        break;
             }   
          }
       }

       // ������ ���������� ��������
       k=fileRead(); 
        // ���������� ��� �������
       for (j=0;j<k;j++) {
          tmp=fileRead(); // ��� �������
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
                     
          tmp=fileRead(); // ������
          rmodel.FMODE[i].MIXER[j].CH_NUM.CH_SOURSE=tmp>>4;
          rmodel.FMODE[i].MIXER[j].CH_NUM.CH_DEST=tmp & 0x0F;   
          
          rmodel.FMODE[i].MIXER[j].MIX_VAL=fileRead(); // �������� ������������   
       }
    }    

/**
        // ������ ������������� ������
       for (i=0;i<8;i++) rmodel.PPM_TO_LCH_CAP[i]=fileRead();   
**/    
  }

//--------------------------------------------------------------------------------------
  for (i=0; i<8; i++) mch[i]=0; //  ���������� �������� ���������� �������������������
  
  //���������� ������� ����� LCH � ������������ � �������� �������
  for (i=0;i<16;i++) { 
     LCH_LEN[i]=rmodel.FMODE[FMODE_NUM].LCH_MIDLE[i];
     OLD_LCH_LEN[i]=rmodel.FMODE[FMODE_NUM].LCH_MIDLE[i];
  }
  
  CalcCurveORD(); // ���������� ������ �������� ������
  getMixCount(FMODE_NUM);
  mixtochan=mixercount/rmodel.CHANNELS.PPM_CH_COUNT;
  mixtochanlast=mixercount%rmodel.CHANNELS.PPM_CH_COUNT;
//------------------------------------ ��������� ��� ���������� ����� �������� --------
}

/**
             � � � �   � � � � � � � �    � � � � �   � � � � � �   �   V D I S K
**/
void menu_MODEL_OPEN() {
unsigned char i, offs, mode, tmp; // ��������� ���������� ����� � �������� 

if (temp1==0) { // ������ ������
  temp1=1; // ���� ��� ������ ������ ����������
  temp2=0; // ����� ���������� �����
}
// �������� ���������
LCD_setxy(0,0); LCD_wrsf("     OPEN MODEL FILE     ",1);

LCD_setxy(0,2); LCD_wrsf("NN TYPE   MODELNAME SIZE ",0);

if (temp2>4) offs=temp2-4; else offs=0;

  for (i=0; i<5; i++) { \\ ���� ������ ���� ����������� �������
     LCD_setxy(0,3+i);
     if (temp2==(i+offs)) mode=1; else mode=0; // ��������� �������
     LCD_dec((unsigned char)(i+offs),2,mode); // �������� ����� ������
     LCD_char(' ', mode); // �������� ������
  
     if (fileToRead(i+offs)==0) { // ���� ���������� � ������
       // ������ ���� - ��� ������
       tmp=fileRead(); 
       LCD_wrsf(MODEL_TYPE[tmp],mode); // �������� ��� ������
    
       LCD_char(' ',mode); // �������� ������
       // ����� ������� ��� ������
       for (tmp=0;tmp<8; tmp++) { // �������� ��� ������
          LCD_char(fileRead(),mode);
       }
    
       LCD_char(' ',mode);
            LCD_char(' ', mode);
                 LCD_char(' ', mode);
                      LCD_char(' ', mode);
    
       // �������� ������ ������
       tmp=fileSize(i+offs);
       LCD_dec(tmp,2,mode);    
     }
  }
   mode=get_mnu_keys(); // ��������� ������� ������� ��������� �� ����
   switch (mode) { // �������� ������� �������

     case 238: { // ������ ������� UP (�����)
                  if (temp2>0) temp2--;
                  break; } 

     case 246: {  // ������ ������� DN (����)
                  if (temp2<15) temp2++;
                  break; } 
                                 
     case 250: {  // ������ ������� EXIT (������� � ����������� ����) 
                  temp2=0; // ����� ������� ��� �������������� 
                  temp3=0; // ����� ���������
                  temp4=0;
                  temp5=0;
                  temp1=0; // ������� ������� �������
                  resetKeyReader(); // ����� ����������
                  menu_exe=0;
                  break; }
               
     case 252: {  // ������ ������� MENU/ENT (������� � ����������� ����/����� ���������)
                  OpenModel(temp2);
                  E_CurModelNum=temp2;
                  temp2=0; // ����� ������� ��� �������������� 
                  temp3=0; // ����� ���������
                  temp4=0;
                  temp5=0;
                  temp1=0; // ������� ������� �������
                  resetKeyReader(); // ����� ����������
                  menu_exe=0;                  
                  break; } 

     case 222: {  // ������ ������� '-' (��������� ������)
                  break; }

     case 190: { //������ �������   '+' (��������� �����)
                  break; }
   } // ����� ����� ������ � �������� ���������
  
}


/**
                       � � � � � �   � � � � � �   � �   � � � � � �   � �   V D I S K
**/
void SaveModel(unsigned filenum) {
unsigned char i,j,k,tmp; // ��������� ���������� 
  
  ppmStop=1; // ������������� ������ ppm ���������� �� ������
  
  while (ppmStop!=2);

  printMess=1;
  fileDelete(filenum); // ������� ������� ������ � ���� �������
  printMess=0;

  if (fileToWrite(filenum)==0) { // ���� ������ ��� ������
    // ��� ������
    fileWrite(rmodel.MODEL_TYPE);
    // ��� ������
    for(i=0;i<8;i++) {
      fileWrite(rmodel.MODEL_NAME[i]);
    }
    // �������� ������
    fileWrite((unsigned char)(rmodel.MODEL_FLYTIMER%256));
    fileWrite((unsigned char)(rmodel.MODEL_FLYTIMER/256));
    
    // ����� ����� ������
    fileWrite((unsigned char)(rmodel.MODEL_LIVETIMER%256));
    fileWrite((unsigned char)(rmodel.MODEL_LIVETIMER/256));
    
    // LCH COUNT
    fileWrite(rmodel.CHANNELS.LCH_COUNT); // ���������� ������� ������
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
   
    // ���������� � CH
    fileWrite(rmodel.CHANNELS.PPM_CH_COUNT);
    // ���������� � �������� �������
    for (i=0; i<rmodel.CHANNELS.PPM_CH_COUNT; i++) {
       // ��� �������
       fileWrite(rmodel.CHANNELS.FILTER[i].FILTER_TYPE); 
       // �������� �������
       fileWrite(rmodel.CHANNELS.FILTER[i].VAL1%256);
       fileWrite(rmodel.CHANNELS.FILTER[i].VAL1/256);
    }
    
    // ���������� � ������� UCH
    for (i=0;i<14; i++) { // ���������� ������ UCH

       // ��������� ������������ �� �����
       tmp=0;
       for (j=0; j<40; j++) { // ���������� �������
          for (k=0; k<3; k++) { // ���������� �������� ������
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
    fileWrite(0); // ������ ����� ������ �� UCH   
    
    // ���������� �������� �������
    fileWrite(rmodel.FMODE_COUNT);
    for (i=0;i<rmodel.FMODE_COUNT;i++) {  // ���� ���������� �������� �������

       // ��� ��������� ������
       fileWrite(rmodel.FMODE[i].FMODE_NAME);

       // ��� ���������
       fileWrite(rmodel.FMODE[i].TRIMSTEP);

       // �������� �������
       for (j=0;j<7;j++) {
          fileWrite(rmodel.FMODE[i].UCH_TRIMMER[j]);
       }

       // ������� ����� �������
       for (j=0;j<rmodel.CHANNELS.LCH_COUNT;j++) {
          fileWrite(rmodel.FMODE[i].LCH_MIDLE[j]%256);
          fileWrite(rmodel.FMODE[i].LCH_MIDLE[j]/256);
       }

       // ������ �������
       for (j=0;j<rmodel.CHANNELS.LCH_COUNT;j++) {
          if (rmodel.FMODE[i].LCH_CURVE[j].active!=0) { // ������ ��������?

            if (rmodel.FMODE[i].LCH_CURVE[j].expon==0) // ���������� ���� ?
               fileWrite(1); //������� ���������� ������ ��� ����������
            else { 
               fileWrite(100); // ������� ���������� ������ � �����������
               fileWrite(rmodel.FMODE[i].LCH_CURVE[j].expon); // �������� ����������
            }
            
            if (rmodel.FMODE[i].LCH_CURVE[j].active!=0) { // ���� ������ ������ ������ ��...
               for (k=0;k<9;k++) { // ������ 9 ����� ������
                 fileWrite(rmodel.FMODE[i].LCH_CURVE[j].point[k]);
               }      
            }
          } else fileWrite(0); // ���� ���������� ��� - ����� ����
       }

       // ���������� ��������
       k=0; // ������������ ����� ���������� �������� � �������� ������
       while (rmodel.FMODE[i].MIXER[k].MIX_TYPE.ACTIVE==1) k++;
       fileWrite(k); // ������� ���������� �������� �������

        // ���������� ��� �������
       for (j=0;j<k;j++) {
          tmp=0x80;
          
          if (rmodel.FMODE[i].MIXER[j].MIX_TYPE.SOURSE_TYPE==1) tmp=tmp|0b01000000;
          if (rmodel.FMODE[i].MIXER[j].MIX_TYPE.PROC_SOURSE==1) tmp=tmp|0b00100000;
          if (rmodel.FMODE[i].MIXER[j].MIX_TYPE.MIX_SW==1)      tmp=tmp|0b00010000;
          if (rmodel.FMODE[i].MIXER[j].MIX_TYPE.SW_INV==1)      tmp=tmp|0b00001000;
          tmp=tmp|rmodel.FMODE[i].MIXER[j].MIX_TYPE.UCH_SW;           
          fileWrite(tmp); // ��������� ���
          tmp=0;
          tmp=tmp|rmodel.FMODE[i].MIXER[j].CH_NUM.CH_SOURSE;
          tmp=tmp<<4;
          tmp=tmp|rmodel.FMODE[i].MIXER[j].CH_NUM.CH_DEST;   
          fileWrite(tmp); // ��������� ������
          fileWrite(rmodel.FMODE[i].MIXER[j].MIX_VAL); // ��������� �������� ������������   
       }
    }    
/**
     // ��������� ������������� ������
     for (i=0;i<8;i++) fileWrite(rmodel.PPM_TO_LCH_CAP[i]);   
**/
  } else { // V-disk �� �����, �������� ��� ���������� �����
     // ������ ������������ �� ���� ��������������
     messStr1="     V-DISK  ERROR !     ";

     messStr2="    NO FREE  SPACE !     ";
     messStr3="   delete old models     ";
     messStr4="   or format V-Disk      ";
     printMess=1;
  }
  
  ppmStop=0;
}

// �������� ��������� ������
void menu_FILE_ERASE() {
unsigned char i, offs, mode, tmp; // ��������� ���������� ����� � �������� 

if (temp1==0) { // ������ ������
  temp1=1; // ���� ��� ������ ������ ����������
  temp2=0; // ����� ���������� �����
}
// �������� ���������
LCD_setxy(0,0); LCD_wrsf("   ERASE  MODEL AS..     ",1);

LCD_setxy(0,2); LCD_wrsf("NN TYPE   MODELNAME SIZE ",0);

if (temp2>4) offs=temp2-4; else offs=0;

  for (i=0; i<5; i++) { \\ ���� ������ ���� ����������� �������
     LCD_setxy(0,3+i);
     if (temp2==(i+offs)) mode=1; else mode=0; // ��������� �������
     LCD_dec((unsigned char)(i+offs),2,mode); // �������� ����� ������
     LCD_char(' ', mode); // �������� ������
  
     if (fileToRead(i+offs)==0) { // ���� ���������� � ������
       // ������ ���� - ��� ������
       tmp=fileRead(); 
       LCD_wrsf(MODEL_TYPE[tmp],mode); // �������� ��� ������
    
       LCD_char(' ',mode); // �������� ������
       // ����� ������� ��� ������
       for (tmp=0;tmp<8; tmp++) { // �������� ��� ������
          LCD_char(fileRead(),mode);
       }
    
       LCD_char(' ',mode);
            LCD_char(' ', mode);
                 LCD_char(' ', mode);
                      LCD_char(' ', mode);
    
       // �������� ������ ������
       tmp=fileSize(i+offs);
       LCD_dec(tmp,2,mode);    
     }
  }
   mode=get_mnu_keys(); // ��������� ������� ������� ��������� �� ����
   switch (mode) { // �������� ������� �������

     case 238: { // ������ ������� UP (�����)
                  if (temp2>0) temp2--;
                  break; } 

     case 246: {  // ������ ������� DN (����)
                  if (temp2<15) temp2++;
                  break; } 
                                 
     case 250: {  // ������ ������� EXIT (������� � ����������� ����) 
                  temp2=0; // ����� ������� ��� �������������� 
                  temp3=0; // ����� ���������
                  temp4=0;
                  temp5=0;
                  temp1=0; // ������� ������� �������
                  resetKeyReader(); // ����� ����������
                  menu_exe=0;
                  break; }
               
     case 252: {  // ������ ������� MENU/ENT (������� � ����������� ����/����� ���������)
                  fileDelete(temp2);
                  temp2=0; // ����� ������� ��� �������������� 
                  temp3=0; // ����� ���������
                  temp4=0;
                  temp5=0;
                  temp1=0; // ������� ������� �������
                  resetKeyReader(); // ����� ����������
                  menu_exe=0;                  
                  break; } 

     case 222: {  // ������ ������� '-' (��������� ������)
                  break; }

     case 190: { //������ �������   '+' (��������� �����)
                  break; }
   } // ����� ����� ������ � �������� ���������
  

}
/**
             � � � �   � � � � � �   � � � � � �   � �    V D I S K
**/
void menu_MODEL_SAVE_AS() {
unsigned char i, offs, mode, tmp; // ��������� ���������� ����� � �������� 

if (temp1==0) { // ������ ������
  temp1=1; // ���� ��� ������ ������ ����������
  temp2=0; // ����� ���������� �����
}
// �������� ���������
LCD_setxy(0,0); LCD_wrsf("     SAVE MODEL AS..     ",1);

LCD_setxy(0,2); LCD_wrsf("NN TYPE   MODELNAME SIZE ",0);

if (temp2>4) offs=temp2-4; else offs=0;

  for (i=0; i<5; i++) { \\ ���� ������ ���� ����������� �������
     LCD_setxy(0,3+i);
     if (temp2==(i+offs)) mode=1; else mode=0; // ��������� �������
     LCD_dec((unsigned char)(i+offs),2,mode); // �������� ����� ������
     LCD_char(' ', mode); // �������� ������
  
     if (fileToRead(i+offs)==0) { // ���� ���������� � ������
       // ������ ���� - ��� ������
       tmp=fileRead(); 
       LCD_wrsf(MODEL_TYPE[tmp],mode); // �������� ��� ������
    
       LCD_char(' ',mode); // �������� ������
       // ����� ������� ��� ������
       for (tmp=0;tmp<8; tmp++) { // �������� ��� ������
          LCD_char(fileRead(),mode);
       }
    
       LCD_char(' ',mode);
            LCD_char(' ', mode);
                 LCD_char(' ', mode);
                      LCD_char(' ', mode);
    
       // �������� ������ ������
       tmp=fileSize(i+offs);
       LCD_dec(tmp,2,mode);    
     }
  }
   mode=get_mnu_keys(); // ��������� ������� ������� ��������� �� ����
   switch (mode) { // �������� ������� �������

     case 238: { // ������ ������� UP (�����)
                  if (temp2>0) temp2--;
                  break; } 

     case 246: {  // ������ ������� DN (����)
                  if (temp2<15) temp2++;
                  break; } 
                                 
     case 250: {  // ������ ������� EXIT (������� � ����������� ����) 
                  temp2=0; // ����� ������� ��� �������������� 
                  temp3=0; // ����� ���������
                  temp4=0;
                  temp5=0;
                  temp1=0; // ������� ������� �������
                  resetKeyReader(); // ����� ����������
                  menu_exe=0;
                  break; }
               
     case 252: {  // ������ ������� MENU/ENT (������� � ����������� ����/����� ���������)
                  E_CurModelNum=temp2;
                  SaveModel(E_CurModelNum);
                  if (printMess==0) {
                     // ������ ������������ �� ���� ��������������
                     messStr1="       FILE SAVED !      "; 
                     messStr2="";
                     messStr3="";
                     messStr4="";
                     messStr5="";
                     printMess=1;
                  }
                  temp2=0; // ����� ������� ��� �������������� 
                  temp3=0; // ����� ���������
                  temp4=0;
                  temp5=0;
                  temp1=0; // ������� ������� �������
                  resetKeyReader(); // ����� ����������
                  menu_exe=0;                  
                  break; } 

     case 222: {  // ������ ������� '-' (��������� ������)
                  break; }

     case 190: { //������ �������   '+' (��������� �����)
                  break; }
   } // ����� ����� ������ � �������� ���������
  
 }  
 
// ������ ������
void menu_MODEL_SAVE() {
unsigned char mode;

LCD_setxy(0,0);  LCD_wrsf("   SAVE CURRENT MODEL    ",1);

LCD_setxy(0,2);  LCD_wrsf("to process press - MENU >",0);

LCD_setxy(0,6);  LCD_wrsf(" to cancel press EXIT   >",0);

   mode=get_mnu_keys(); // ��������� ������� ������� ��������� �� ����
   switch (mode) { // �������� ������� �������

     case 238: { // ������ ������� UP (�����)
                  break; } 

     case 246: {  // ������ ������� DN (����)
                  break; } 
                                 
     case 250: {  // ������ ������� EXIT (������� � ����������� ����) 
                  temp2=0; // ����� ������� ��� �������������� 
                  temp3=0; // ����� ���������
                  temp4=0;
                  temp5=0;
                  temp1=0; // ������� ������� �������
                  resetKeyReader(); // ����� ����������
                  menu_exe=0;
                  break; }
               
     case 252: {  // ������ ������� MENU/ENT (������� � ����������� ����/����� ���������)
                  if (E_CurModelNum<16) SaveModel(E_CurModelNum); // ���������� ������ ��� ������� �������
                  temp2=0; // ����� ������� ��� �������������� 
                  temp3=0; // ����� ���������
                  temp4=0;
                  temp5=0;
                  temp1=0; // ������� ������� �������
                  if (printMess==0) {
                     // ������ ������������ �� ���� ��������������
                     messStr1="       FILE SAVED !      "; 
                     messStr2="";
                     messStr3="";
                     messStr4="";
                     messStr5="";
                     printMess=1;
                  }                  
                  resetKeyReader(); // ����� ����������
                  menu_exe=0;                  
                  break; } 

     case 222: {  // ������ ������� '-' (��������� ������)
                  break; }

     case 190: { //������ �������   '+' (��������� �����)
                  break; }
   } // ����� ����� ������ � �������� ���������
}

// �������������� �����
void menu_formatVDisk() {
unsigned char mode;

LCD_setxy(0,0);  LCD_wrsf("    FORMAT V-DISK ?      ",1);

LCD_setxy(0,2);  LCD_wrsf("to process press - MENU >",0);

LCD_setxy(0,4);  LCD_wrsf("All data must be deleted!",2);

LCD_setxy(0,6);  LCD_wrsf(" to cancel press EXIT   >",0);

   mode=get_mnu_keys(); // ��������� ������� ������� ��������� �� ����
   switch (mode) { // �������� ������� �������

     case 238: { // ������ ������� UP (�����)
                  break; } 

     case 246: {  // ������ ������� DN (����)
                  break; } 
                                 
     case 250: {  // ������ ������� EXIT (������� � ����������� ����) 
                  temp2=0; // ����� ������� ��� �������������� 
                  temp3=0; // ����� ���������
                  temp4=0;
                  temp5=0;
                  temp1=0; // ������� ������� �������
                  resetKeyReader(); // ����� ����������
                  menu_exe=0;
                  break; }
               
     case 252: {  // ������ ������� MENU/ENT (������� � ����������� ����/����� ���������)
                  formatVDisk();
                  temp2=0; // ����� ������� ��� �������������� 
                  temp3=0; // ����� ���������
                  temp4=0;
                  temp5=0;
                  temp1=0; // ������� ������� �������
                  if (printMess==0) {
                                     // ������ ������������ �� ���� ��������������
                     messStr1="   V-DISK  FORMATTED !   ";

                     messStr2=" File operations enabled";
                     messStr3=" ";
                     messStr4=" ";
                     messStr5=" ";
                     printMess=1;                   
                  }
                  resetKeyReader(); // ����� ����������
                  menu_exe=0;                  
                  break; } 

     case 222: {  // ������ ������� '-' (��������� ������)
                  break; }

     case 190: { //������ �������   '+' (��������� �����)
                  break; }
   } // ����� ����� ������ � �������� ���������
}


// ����������� ����� �� ��������� ������������ ������
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

   mode=get_mnu_keys(); // ��������� ������� ������� ��������� �� ����
   switch (mode) { // �������� ������� �������

     case 238: { // ������ ������� UP (�����)
                  break; } 

     case 246: {  // ������ ������� DN (����)
                  break; } 
                                 
     case 250: {  // ������ ������� EXIT (������� � ����������� ����) 
                  resetKeyReader(); // ����� ����������
                  menu_exe=0;
                  disp_mode=2;
                  break; }
               
     case 252: {  // ������ ������� MENU/ENT (������� � ����������� ����/����� ���������)
                   if (E_CurModelNum<16) { 
                      SaveModel(E_CurModelNum);
                      menu_exe=0;
                      disp_mode=2;
                   }  
                      else {
                        menu_proc=menu_MODEL_SAVE_AS;
                      }
                  break; } 

     case 222: {  // ������ ������� '-' (��������� ������)
                  break; }

     case 190: { //������ �������   '+' (��������� �����)
                  break; }
   } // ����� ����� ������ � �������� ���������
}


// ��������� ������ ���������� � c�������� ����� �� V-Disk - - - - - - - - - - - - - - - - - - - - - - - -
void menu_VDISK_INFO(void) {
unsigned char mode, i;

LCD_setxy(0,0);  LCD_wrsf("       V-DISK  INFO      ", 1);

LCD_setxy(0,3);  LCD_wrsf("V-Disk sector col: ", 0); LCD_dec(VDISKSIZE/E_ClusterSize,3,1);

  mode=freesp; // ����� ����� ������� ���������� ��������
  i=0;
  while (mode!=255) {
    i++;
    mode=VDISK[(unsigned int)mode*E_ClusterSize];
  } 

LCD_setxy(0,5);  LCD_wrsf(" free space: ", 0); LCD_dec(i,3,1);

   mode=get_mnu_keys(); // ��������� ������� ������� ��������� �� ����
   switch (mode) { // �������� ������� �������

     case 238: { // ������ ������� UP (�����)
                  break; } 

     case 246: {  // ������ ������� DN (����)
                  break; } 
                                 
     case 250: {  // ������ ������� EXIT (������� � ����������� ����) 
                  resetKeyReader(); // ����� ����������
                  menu_exe=0;
                  break; }
               
     case 252: {  // ������ ������� MENU/ENT (������� � ����������� ����/����� ���������)
                  break; } 

     case 222: {  // ������ ������� '-' (��������� ������)
                  break; }

     case 190: { //������ �������   '+' (��������� �����)
                  break; }
   } // ����� ����� ������ � �������� ���������

}


// ��������� ������ ���������� � ����������� - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void menu_CODER_INFO(void) {
unsigned char mode;

LCD_setxy(0,0);  LCD_wrsf("   V-CODER  ver 0.99b    ", 1);
LCD_setxy(0,1);  LCD_wrsf("author: Vitaly V Gorbukov", 0);

LCD_setxy(0,3);  LCD_wrsf(" build: 2324  17.08.2012 ", 0);
LCD_setxy(0,4);  LCD_wrsf(" first use at 21.07.2010 ", 0);

LCD_setxy(0,6);  LCD_wrsf("   for support mail to   ", 0);
LCD_setxy(0,7);  LCD_wrsf("   gorbukov@yandex.ru    ", 1);

   mode=get_mnu_keys(); // ��������� ������� ������� ��������� �� ����
   switch (mode) { // �������� ������� �������

     case 238: { // ������ ������� UP (�����)
                  break; } 

     case 246: {  // ������ ������� DN (����)
                  break; } 
                                 
     case 250: {  // ������ ������� EXIT (������� � ����������� ����) 
                  resetKeyReader(); // ����� ����������
                  menu_exe=0;
                  break; }
               
     case 252: {  // ������ ������� MENU/ENT (������� � ����������� ����/����� ���������)
                  break; } 

     case 222: {  // ������ ������� '-' (��������� ������)
                  break; }

     case 190: { //������ �������   '+' (��������� �����)
                  break; }
   } // ����� ����� ������ � �������� ���������
}

