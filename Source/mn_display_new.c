#include "vcoder.h"
#include "string.h" 

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

      // ���� �������
__flash const unsigned char MODEL_TYPE[3][8]= { "ACRO  ", "PLANER", "HELI  " };
#define MODEL_TYPE_COUNT 2 // ���������� ����� ������� - 1

      // ���� ��������� ��������                 
#define CHANNEL_FILTER_TYPE_COUNT 3 // ���������� ��������� ��������                      
__flash const unsigned char CHANNEL_FILTER_TYPE[CHANNEL_FILTER_TYPE_COUNT][8]= { 
      "LINE",    // �������� ����� ������
      "SW",      // ����� � ����������� �� ��������� �����������
      "MULTI" };

      // ���� �������� �������
#define SL_FMODE_NAME_COUNT 12 
__flash const unsigned char SL_FMODE_NAME[SL_FMODE_NAME_COUNT][9]= {
      "NORMAL",  "LANDING",  "TRAINER",  "PILOTAGE",  "3D",  "4D",
      "IDLE1",   "IDLE2",    
      "START",   "SPEED",    "CRUISE",   "THERMAL"};

typedef void (*tmenu_proc)(void);

unsigned char   disp_mode; // ����� ������� 

unsigned char numitem_cur; // ������� ����� ������ ���� (������� �� ���������)
unsigned char    posxmenu; // ������� ������� � ����  (������� �� �����������)

unsigned char    menu_exe; // ������� ������� ��������� ����
tmenu_proc      menu_proc; // ��������� ��������� ��� ������� � ������ ����

unsigned char fmode_source, fmode_to; // ���������� ��� ����������� �������� �������
#include "menu_procedures.c"

// ��������� ��������� ����
typedef struct {
    unsigned char   numitem;  // ����� ������ ���� (���)
    unsigned char itemstr[12];  // ����� ������ ����
    unsigned char  nextitem;  // ��������� �����
    unsigned char  previtem;  // ���������� �����
    unsigned char    upitem;  // ����������� ����� ����
    unsigned char  downitem;  // ����������� ����� ����
    
    void            * pvar1; // ��������� �� �������� 1
    void            * pvar2; // ��������� �� �������� 2 
    unsigned char   partype; // ��� ����������
    tmenu_proc  menu_proc;  // ��������� ����������� ��� ������ ������ ����
    
    unsigned char *colitemcount; // ���������� ���������� ������� � �������
    unsigned char   colitem; // ������� ������������ ���������                                 

    
} MENU_STRUCT;


// �������� ����
flash const MENU_STRUCT menu[]={
//numitem, itemstr         , nextitem, previtem, upitem, downitem,  *pvar1               , *pvar2                   , partype    ,         *menu_proc ,     *colitemcount,    colitem 
{    0   ,"MAIN MENU"      ,       0 ,       0 ,     0 ,       1 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0       },

{    1   ,"FILE"           ,       2 ,       0 ,     0 ,       7 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0       },
{    2   ,"EDIT"           ,       3 ,       1 ,     0 ,      12 ,  &rmodel.MODEL_NAME   ,  0                       , 2          ,  0                 ,           0      ,       0       },
{    3   ,"TIMERS"         ,       4 ,       2 ,     0 ,     132 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0       },
{    4   ,"SYSTEM"         ,       5 ,       3 ,     0 ,      63 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0       },
{    5   ,"INFO"           ,       0 ,       4 ,     0 ,       0 ,  0                    ,  0                       , 0          ,  menu_CODER_INFO   ,           0      ,       0       },
   // ������� SYSTEM
{   63   ,"ALARM"          ,      64 ,       0 ,     4 ,     174 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0       },
{   64   ,"CONTROLS"       ,      65 ,      63 ,     4 ,     157 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0       },
{   65   ,"CONTRAST"       ,     136 ,      64 ,     4 ,       0 ,  0                    ,  0                       , 31         ,  0                 ,           0      ,       0       },
{  136   ,"PPM FORMAT"     ,      66 ,      65 ,     4 ,       0 ,  0                    ,  0                       , 30         ,  0                 ,           0      ,       0             },
{   66   ,"SOUND"          ,     227 ,     136 ,     4 ,     226 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0       },
{  227   ,"KEYS & TRIM"    ,     223 ,      66 ,     4 ,     228 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0       },
{  223   ,"V-DISK"         ,       0 ,     227 ,     4 ,     224 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0       },

   // ������� SYSTEM - CONTROLS
{  157   ,"STICK MODE"     ,      67 ,       0 ,    64 ,       0 ,  0                    ,  0                       , 33         ,  0                 ,           0      ,       0       },
{   67   ,"VIEW CALIBR"    ,      68 ,     157 ,    64 ,       0 ,  0                    ,  0                       , 0          ,  menu_SYSTEM_CALIBRATION_INFO, 0      ,       0       },
{   68   ,"CALIBRATION"    ,       0 ,      67 ,    64 ,       0 ,  0                    ,  0                       , 0          ,  menu_SYSTEM_NEW_CALIBRATION,  0      ,       0       },
   
   // ������� FILE
//{    6   ,"NEW MODEL"      ,       7 ,       0 ,     1 ,       0 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0       },
{    7   ,"RESET MODEL"    ,       8 ,       0 ,     1 ,       0 ,  0                    ,  0                       , 0          , menu_FILE_RESET    ,           0      ,       0       },
{    8   ,"OPEN MODEL"     ,       9 ,       7 ,     1 ,       0 ,  0                    ,  0                       , 0          , menu_MODEL_OPEN    ,           0      ,       0       },
{    9   ,"SAVE MODEL"     ,      10 ,       8 ,     1 ,       0 ,  0                    ,  0                       , 0          , menu_MODEL_SAVE    ,           0      ,       0              },
{   10   ,"SAVE AS.."      ,      11 ,       9 ,     1 ,       0 ,  0                    ,  0                       , 0          , menu_MODEL_SAVE_AS ,           0      ,       0              },
{   11   ,"ERASE MODEL"    ,       0 ,      10 ,     1 ,       0 ,  0                    ,  0                       , 0          , menu_FILE_ERASE    ,           0      ,       0              },
   // ������� EDIT
{   12   ,"TYPE"           ,      13 ,       0 ,     2 ,       0 ,  &rmodel.MODEL_TYPE   ,  0                       , 1          ,  0                 ,           0      ,       0              },
{   13   ,"NAME"           ,      14 ,      12 ,     2 ,       0 ,  &rmodel.MODEL_NAME   ,  0                       , 2          ,  menu_EDIT_MODEL_NAME,         0      ,       0           },
{   14   ,"CHANNELS"       ,      15 ,      13 ,     2 ,      69 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0             },
{   15   ,"CONTROLS"       ,      16 ,      14 ,     2 ,      45 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0             },
{   16   ,"FLY MODES"      ,       0 ,      15 ,     2 ,     105 ,  0                    ,  0                       , 0          ,  0                 ,           &rmodel.FMODE_COUNT      ,       0             },
   // ������� EDIT - CHANNELS
{   69   ,"LCH SET"        ,      70 ,       0 ,    14 ,      17 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0           },
{   70   ,"CH SET"         ,       0 ,      69 ,    14 ,      44 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0           },
   // ������� EDIT - CHANNELS - LCH SET   
{   17   ,"LCH COUNT"      ,      18 ,       0 ,    69 ,       0 ,  &rmodel.CHANNELS.LCH_COUNT  ,  0                , 3          ,  0                 ,           0      ,       0           },
{   18   ,"LCH EPA"        ,      71 ,      17 ,    69 ,      20 ,  0                    ,  0                       , 0          ,  0                 ,           &rmodel.CHANNELS.LCH_COUNT      ,       0             },
{   71   ,"LCH DELAY"      ,      88 ,      18 ,    69 ,      72 ,  0                    ,  0                       , 0          ,  0                 ,           &rmodel.CHANNELS.LCH_COUNT      ,       0             },
{   88   ,"LCH REVERSE"    ,       0 ,      71 ,    69 ,      89 ,  0                    ,  0                       , 0          ,  0                 ,           &rmodel.CHANNELS.LCH_COUNT      ,       0             },
   // ������� EDIT- CHANNELS - LCH SET - LCH REVERSE
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

   // ������� EDIT- CHANNELS - LCH SET - LCH DELAY
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
   
   // ������� EDIT - CHANNELS - CH SET
{   44   ,"CH TO PPM"      ,      19 ,       0 ,    70 ,       0 ,  &rmodel.CHANNELS.PPM_CH_COUNT  ,  0             , 6          ,  0                 ,           0      ,       0            },
{   19   ,"FILTERS"        ,       0 ,      44 ,    70 ,      36 ,  0                    ,  0                       , 0          ,  0                 ,           &rmodel.CHANNELS.PPM_CH_COUNT      ,       0             },
   // ������� EDIT - CHANNELS - LCH EPA  
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
   // ������� EDIT - CHANNELS - FILTERS   
{   36   ,"CH 1"           ,      37 ,       0 ,    19 ,       0 , &rmodel.CHANNELS.FILTER[0].FILTER_TYPE  , &rmodel.CHANNELS.FILTER[0].VAL1  , 5 ,  menu_EDIT_CHANNEL_FILTERS ,           0      ,       1       },
{   37   ,"CH 2"           ,      38 ,      36 ,    19 ,       0 , &rmodel.CHANNELS.FILTER[1].FILTER_TYPE  , &rmodel.CHANNELS.FILTER[1].VAL1  , 5 ,  menu_EDIT_CHANNEL_FILTERS ,           0      ,       2      },
{   38   ,"CH 3"           ,      39 ,      37 ,    19 ,       0 , &rmodel.CHANNELS.FILTER[2].FILTER_TYPE  , &rmodel.CHANNELS.FILTER[2].VAL1  , 5 ,  menu_EDIT_CHANNEL_FILTERS ,           0      ,       3      },
{   39   ,"CH 4"           ,      40 ,      38 ,    19 ,       0 , &rmodel.CHANNELS.FILTER[3].FILTER_TYPE  , &rmodel.CHANNELS.FILTER[3].VAL1  , 5 ,  menu_EDIT_CHANNEL_FILTERS ,           0      ,       4       },
{   40   ,"CH 5"           ,      41 ,      39 ,    19 ,       0 , &rmodel.CHANNELS.FILTER[4].FILTER_TYPE  , &rmodel.CHANNELS.FILTER[4].VAL1  , 5 ,  menu_EDIT_CHANNEL_FILTERS ,           0      ,       5       },
{   41   ,"CH 6"           ,      42 ,      40 ,    19 ,       0 , &rmodel.CHANNELS.FILTER[5].FILTER_TYPE  , &rmodel.CHANNELS.FILTER[5].VAL1  , 5 ,  menu_EDIT_CHANNEL_FILTERS ,           0      ,       6      },
{   42   ,"CH 7"           ,      43 ,      41 ,    19 ,       0 , &rmodel.CHANNELS.FILTER[6].FILTER_TYPE  , &rmodel.CHANNELS.FILTER[6].VAL1  , 5 ,  menu_EDIT_CHANNEL_FILTERS ,           0      ,       7      },
{   43   ,"CH 8"           ,       0 ,      42 ,    19 ,       0 , &rmodel.CHANNELS.FILTER[7].FILTER_TYPE  , &rmodel.CHANNELS.FILTER[7].VAL1  , 5 ,  menu_EDIT_CHANNEL_FILTERS ,           0      ,       8      },
   // ������� EDIT - CONTROLS 
{   45   ,"STICK"          ,      46 ,       0 ,    15 ,      49 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0             },
{   46   ,"VARIO"          ,      47 ,      45 ,    15 ,      53 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0             },
{   47   ,"SWITCH"         ,      48 ,      46 ,    15 ,      57 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0             },
{   48   ,"BUTTON"         ,       0 ,      47 ,    15 ,      62 ,  0                    ,  0                       , 0          ,  0                 ,           0      ,       0             },
/**
   // ������� EDIT - CONTROLS - PPM CAPTURE
{  137   ,"PPM CH1"        ,     138 ,     167 ,   136 ,       0 ,  &rmodel.PPM_TO_LCH_CAP[0] ,  0                  , 29          ,  0                 ,           0      ,       0             },
{  138   ,"PPM CH2"        ,     139 ,     137 ,   136 ,       0 ,  &rmodel.PPM_TO_LCH_CAP[1] ,  0                  , 29          ,  0                 ,           0      ,       0             },
{  139   ,"PPM CH3"        ,     140 ,     138 ,   136 ,       0 ,  &rmodel.PPM_TO_LCH_CAP[2] ,  0                  , 29          ,  0                 ,           0      ,       0             },
{  140   ,"PPM CH4"        ,     149 ,     139 ,   136 ,       0 ,  &rmodel.PPM_TO_LCH_CAP[3] ,  0                  , 29          ,  0                 ,           0      ,       0             },
{  149   ,"PPM CH5"        ,     150 ,     140 ,   136 ,       0 ,  &rmodel.PPM_TO_LCH_CAP[4] ,  0                  , 29          ,  0                 ,           0      ,       0             },
{  150   ,"PPM CH6"        ,     151 ,     149 ,   136 ,       0 ,  &rmodel.PPM_TO_LCH_CAP[5] ,  0                  , 29          ,  0                 ,           0      ,       0             },
{  151   ,"PPM CH7"        ,     152 ,     150 ,   136 ,       0 ,  &rmodel.PPM_TO_LCH_CAP[6] ,  0                  , 29          ,  0                 ,           0      ,       0             },
{  152   ,"PPM CH8"        ,       0 ,     151 ,   136 ,       0 ,  &rmodel.PPM_TO_LCH_CAP[7] ,  0                  , 29          ,  0                 ,           0      ,       0             },
**/   
   // ������� EDIT - CONTROLS - STICK
{   49   ,"AILERONS"       ,      50 ,       0 ,    45 ,       0 , &rmodel.UCH[0].UCH_LEFT , &rmodel.UCH[0].UCH_RIGHT    , 7         ,  0                ,           0      ,       0              },
{   50   ,"ELEVATOR"       ,      51 ,      49 ,    45 ,       0 , &rmodel.UCH[1].UCH_LEFT , &rmodel.UCH[1].UCH_RIGHT    , 7          ,  0               ,           0      ,       0               },
{   51   ,"THROTTLE"        ,      52 ,      50 ,   45 ,       0 , &rmodel.UCH[2].UCH_LEFT , &rmodel.UCH[2].UCH_RIGHT    , 7          ,  0               ,           0      ,       0               },
{   52   ,"RUDDER"         ,       0 ,      51 ,    45 ,       0 , &rmodel.UCH[3].UCH_LEFT , &rmodel.UCH[3].UCH_RIGHT    , 7          ,  0               ,           0      ,       0               },
   // ������� EDIT - CONTROLS - VARIO
{   53   ,"HOV PIT"        ,      54 ,       0 ,    46 ,       0 , &rmodel.UCH[4].UCH_LEFT , &rmodel.UCH[4].UCH_RIGHT    , 7          ,  0               ,           0      ,       0               },
{   54   ,"HOV THR"        ,      55 ,      53 ,    46 ,       0 , &rmodel.UCH[5].UCH_LEFT , &rmodel.UCH[5].UCH_RIGHT    , 7          ,  0               ,           0      ,       0               },
{   55   ,"PIT TRM"        ,       0 ,      54 ,    46 ,       0 , &rmodel.UCH[6].UCH_LEFT , &rmodel.UCH[6].UCH_RIGHT    , 7          ,  0               ,           0      ,       0               },
   // ������� EDIT - CONTROLS - SWITCH
// {   56   ,"F MODE"         ,      57 ,       0 ,    47 ,       0 , &rmodel.UCH[7].UCH_LEFT , &rmodel.UCH[7].UCH_RIGHT    , 7          ,  0               ,           0      ,       0               },
{   57   ,"GEAR"           ,      58 ,       0 ,    47 ,       0 , &rmodel.UCH[8].UCH_LEFT , &rmodel.UCH[8].UCH_RIGHT    , 7          ,  0               ,           0      ,       0               },
{   58   ,"THR.CUT"        ,      59 ,      57 ,    47 ,       0 , &rmodel.UCH[10].UCH_LEFT , &rmodel.UCH[10].UCH_RIGHT  , 7          ,  0             ,           0      ,       0                 },
{   59   ,"AILE DR"        ,      60 ,      58 ,    47 ,       0 , &rmodel.UCH[11].UCH_LEFT , &rmodel.UCH[11].UCH_RIGHT  , 7          ,  0             ,           0      ,       0                 },
{   60   ,"ELEV DR"        ,      61 ,      59 ,    47 ,       0 , &rmodel.UCH[12].UCH_LEFT , &rmodel.UCH[12].UCH_RIGHT  , 7          ,  0             ,           0      ,       0                 },
{   61   ,"RUDD DR"        ,       0 ,      60 ,    47 ,       0 , &rmodel.UCH[13].UCH_LEFT , &rmodel.UCH[13].UCH_RIGHT  , 7          ,  0             ,           0      ,       0                 },
   // ������� EDIT - CONTROLS - BUTTON 
{   62   ,"TRAINER"        ,       0 ,       0 ,    48 ,       0 , &rmodel.UCH[9].UCH_LEFT , &rmodel.UCH[9].UCH_RIGHT    , 7          ,  0               ,           0      ,       0               },
   // ������� EDIT - FLY MODES
{  105   ,"FMODE COUNT"    ,     153 ,       0 ,    16 ,       0 ,  &rmodel.FMODE_COUNT  ,  0                            , 10          ,  0         ,           0      ,       0              },
{  153   ,"FMODE COPY"     ,     106 ,     105 ,    16 ,     154 ,  0                           ,  0                     , 0           ,  0         ,           0      ,       0                     },
{  106   ,"FMODE 1"        ,     107 ,     153 ,    16 ,     109 ,  &rmodel.FMODE[0].FMODE_NAME ,  0                     , 11          ,  0         ,           0      ,       1                     },
{  107   ,"FMODE 2"        ,     108 ,     106 ,    16 ,     114 ,  &rmodel.FMODE[1].FMODE_NAME ,  0                     , 11          ,  0         ,           0      ,       2                     },
{  108   ,"FMODE 3"        ,       0 ,     107 ,    16 ,     119 ,  &rmodel.FMODE[2].FMODE_NAME ,  0                     , 11          ,  0         ,           0      ,       3                     },
  // ������� EDIT - FLY MODES - FMODE COPY
{  154   ,"FROM"           ,     155 ,       0 ,   153 ,       0 ,  &fmode_source               ,  0                     , 10          ,  0         ,           0      ,       0                      },
{  155   ,"TO"             ,     156 ,     154 ,   153 ,       0 ,  &fmode_to                   ,  0                     , 10          ,  0         ,           0      ,       0                      },
{  156   ,"COPY"           ,       0 ,     155 ,   153 ,       0 ,  0                           ,  0                     , 29          ,  0         ,           0      ,       0                      },
   // ������� EDIT - FLY MODES - FMODE 1
{  109   ,"FMODE NAME"     ,     110 ,       0 ,   106 ,       0 ,  &rmodel.FMODE[0].FMODE_NAME ,  0                     , 12          ,  0         ,           0      ,       0                     },
{  110   ,"UCH TRIM."      ,     111 ,     109 ,   106 ,     124 ,  0                           ,  0                     , 0           ,  0         ,           0      ,       0                     },
{  111   ,"LCH MIDDLE"     ,     112 ,     110 ,   106 ,     175 ,  0                           ,  0                     , 0           ,  0         ,           &rmodel.CHANNELS.LCH_COUNT      ,       0                     },
{  112   ,"LCH CURVE"      ,     113 ,     111 ,   106 ,       0 ,  0                           ,  0                     , 0           ,  menu_FMODE_CURVES,           0      ,       0              },
{  113   ,"MIXERS"         ,       0 ,     112 ,   106 ,       0 ,  0                           ,  0                     , 0           ,  menu_FMODE_MIXERS,           0      ,       0       },
    // ������� EDIT - FLY MODES - FMODE 1 - LCH MIDLE
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
    // ������� EDIT - FLY MODES - FMODE 1 - UCH TRIM.  
{  124   ,"TRIM. STEP"     ,     125 ,       0 ,   110 ,       0 ,  &rmodel.FMODE[0].TRIMSTEP       ,  0                 , 10          ,  0         ,           0      ,       0                     },
{  125   ,"AILERONS"       ,     126 ,     124 ,   110 ,       0 ,  &rmodel.FMODE[0].UCH_TRIMMER[0] ,  0                 , 13          ,  0         ,           0      ,       1                     },
{  126   ,"ELEVATOR"       ,     127 ,     125 ,   110 ,       0 ,  &rmodel.FMODE[0].UCH_TRIMMER[1] ,  0                 , 13          ,  0         ,           0      ,       1                     },
{  127   ,"THROTTLE"       ,     128 ,     126 ,   110 ,       0 ,  &rmodel.FMODE[0].UCH_TRIMMER[2] , 0                 , 13          ,  0         ,           0      ,       1                     },
{  128   ,"RUDDER"         ,     129 ,     127 ,   110 ,       0 ,  &rmodel.FMODE[0].UCH_TRIMMER[3] ,  0                 , 13          ,  0         ,           0      ,       1                     },
{  129   ,"HOV PIT"        ,     130 ,     128 ,   110 ,       0 ,  &rmodel.FMODE[0].UCH_TRIMMER[4] ,  0                 , 13          ,  0         ,           0      ,       1                     },
{  130   ,"HOV THR"        ,     131 ,     129 ,   110 ,       0 ,  &rmodel.FMODE[0].UCH_TRIMMER[5] ,  0                 , 13          ,  0         ,           0      ,       1                     },
{  131   ,"PIT TRIM"       ,       0 ,     130 ,   110 ,       0 ,  &rmodel.FMODE[0].UCH_TRIMMER[6] ,  0                 , 13          ,  0         ,           0      ,       1                     },
   //������� TIMERS
{  132   ,"FLY TIMER"      ,     133 ,       0 ,     3 ,       0 ,  &rmodel.MODEL_FLYTIMER          , &rmodel.MODEL_FLYTIMER , 23        ,  0         ,           0      ,       1                     },
{  133   ,"LIVE TIMER"     ,     134 ,     132 ,     3 ,       0 ,  &rmodel.MODEL_LIVETIMER         , &rmodel.MODEL_LIVETIMER , 23       ,  0         ,           0      ,       1                     },
{  134   ,"SET TIMER"      ,     135 ,     133 ,     3 ,       0 ,  0                                ,  0                   , 24         ,  0         ,           0      ,       1                     },
{  135   ,"UPDATE LIFE"    ,     172 ,     134 ,     3 ,       0 ,  0                                ,  0                   , 25         ,  0         ,           0      ,       1                     },
{  172   ,"EVENT START"     ,    166 ,     135,      3 ,       0 ,  0                                ,  0                   , 20         ,  0         ,           0      ,       0                     },
{  166   ,"EVENT STOP"      ,      0 ,     172,      3 ,       0 ,  0                                ,  0                   , 27         ,  0         ,           0      ,       0                     },
   // ������� EDIT - FLY MODES - FMODE 2
{  114   ,"FMODE NAME"     ,     115 ,       0 ,   107 ,       0 ,  &rmodel.FMODE[1].FMODE_NAME ,  0                     , 12          ,  0         ,           0      ,       0                     },
{  115   ,"UCH TRIM."      ,     116 ,     114 ,   107 ,     141 ,  0                           ,  0                     , 0           ,  0         ,           0      ,       0                     },
{  116   ,"LCH MIDDLE"     ,     117 ,     115 ,   107 ,     191 ,  0                           ,  0                     , 0           ,  0         ,           &rmodel.CHANNELS.LCH_COUNT      ,       0                     },
{  117   ,"LCH CURVE"      ,     118 ,     116 ,   107 ,       0 ,  0                           ,  0                     , 0           ,  menu_FMODE_CURVES,           0      ,       0               },
{  118   ,"MIXERS"         ,       0 ,     117 ,   107 ,       0 ,  0                           ,  0                     , 0           ,  menu_FMODE_MIXERS,           0      ,       0       },
    // ������� EDIT - FLY MODES - FMODE 2 - LCH MIDLE
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
    // ������� EDIT - FLY MODES - FMODE 2- LCH TRIMMER
{  141   ,"TRIM. STEP"      ,     142 ,       0 ,   115 ,       0 ,  &rmodel.FMODE[1].TRIMSTEP       ,  0                , 10          ,  0         ,           0      ,       0                         },
{  142   ,"AILERONS"        ,     143 ,     141 ,   115 ,       0 ,  &rmodel.FMODE[1].UCH_TRIMMER[0] ,  0                , 13          ,  0         ,           0      ,       1                     },
{  143   ,"ELEVATOR"        ,     144 ,     142 ,   115 ,       0 ,  &rmodel.FMODE[1].UCH_TRIMMER[1] ,  0                , 13          ,  0         ,           0      ,       1                     },
{  144   ,"THROTTLE"        ,     145 ,     143 ,   115 ,       0 ,  &rmodel.FMODE[1].UCH_TRIMMER[2] ,  0               , 13          ,  0         ,           0      ,       1                     },
{  145   ,"RUDDER"          ,     146 ,     144 ,   115 ,       0 ,  &rmodel.FMODE[1].UCH_TRIMMER[3] ,  0                , 13          ,  0         ,           0      ,       1                     },
{  146   ,"HOV PIT"         ,     147 ,     145 ,   115 ,       0 ,  &rmodel.FMODE[1].UCH_TRIMMER[4] ,  0                , 13          ,  0         ,           0      ,       1                     },
{  147   ,"HOV THR"         ,     148 ,     146 ,   115 ,       0 ,  &rmodel.FMODE[1].UCH_TRIMMER[5] ,  0                , 13          ,  0         ,           0      ,       1                     },
{  148   ,"PIT TRIM"        ,       0 ,     147 ,   115 ,       0 ,  &rmodel.FMODE[1].UCH_TRIMMER[6] ,  0                , 13          ,  0         ,           0      ,       1                     },
   // ������� EDIT - FLY MODES - FMODE 3
{  119   ,"FMODE NAME"     ,     120 ,       0 ,   108 ,       0 ,  &rmodel.FMODE[2].FMODE_NAME ,  0                     , 12          ,  0         ,           0      ,       0                     },
{  120   ,"UCH TRIM."      ,     121 ,     119 ,   108 ,     158 ,  0                           ,  0                     , 0           ,  0         ,           0      ,       0                     },
{  121   ,"LCH MIDDLE"     ,     122 ,     120 ,   108 ,     207 ,  0                           ,  0                     , 0           ,  0         ,           &rmodel.CHANNELS.LCH_COUNT      ,       0                     },
{  122   ,"LCH CURVE"      ,     123 ,     121 ,   108 ,       0 ,  0                           ,  0                     , 0           ,  menu_FMODE_CURVES,           0      ,       0              },
{  123   ,"MIXERS"         ,       0 ,     122 ,   108 ,       0 ,  0                           ,  0                     , 0           ,  menu_FMODE_MIXERS,           0      ,       0       },
    // ������� EDIT - FLY MODES - FMODE 3 - LCH MIDLE
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
    // ������� EDIT - FLY MODES - FMODE 3 - LCH TRIMMER
{  158   ,"TRIM. STEP"     ,     159 ,       0 ,   120 ,       0 ,  &rmodel.FMODE[2].TRIMSTEP       ,  0                 , 10          ,  0         ,           0      ,       0                     },
{  159   ,"AILERONS"       ,     160 ,     158 ,   120 ,       0 ,  &rmodel.FMODE[2].UCH_TRIMMER[0] ,  0                 , 13          ,  0         ,           0      ,       1                     },
{  160   ,"ELEVATOR"       ,     161 ,     159 ,   120 ,       0 ,  &rmodel.FMODE[2].UCH_TRIMMER[1] ,  0                 , 13          ,  0         ,           0      ,       1                     },
{  161   ,"THROTTLE"       ,     162 ,     160 ,   120 ,       0 ,  &rmodel.FMODE[2].UCH_TRIMMER[2] ,  0                , 13          ,  0         ,           0      ,       1                     },
{  162   ,"RUDDER"         ,     163 ,     161 ,   120 ,       0 ,  &rmodel.FMODE[2].UCH_TRIMMER[3] ,  0                 , 13          ,  0         ,           0      ,       1                     },
{  163   ,"HOV PIT"        ,     164 ,     162 ,   120 ,       0 ,  &rmodel.FMODE[2].UCH_TRIMMER[4] ,  0                 , 13          ,  0         ,           0      ,       1                     },
{  164   ,"HOV THR"        ,     165 ,     163 ,   120 ,       0 ,  &rmodel.FMODE[2].UCH_TRIMMER[5] ,  0                 , 13          ,  0         ,           0      ,       1                     },
{  165   ,"PIT TRIM"       ,       0 ,     164 ,   120 ,       0 ,  &rmodel.FMODE[2].UCH_TRIMMER[6] ,  0                 , 13          ,  0         ,           0      ,       1                     },
    // ������� SYSTEM - V-DISK
{  224   ,"CLUSTER"        ,     225 ,      0 ,    223 ,       0 ,  0                                ,  0                , 15         ,  0                 ,           0      ,       0       },
{  225   ,"FORMAT VD"      ,     232 ,    224 ,    223 ,       0 ,  0                                ,  0                , 0          ,  menu_formatVDisk       ,           0      ,       0       },
{  232   ,"VDISK INFO"     ,       0 ,    225 ,    223 ,       0 ,  0                                ,  0                , 0          ,  menu_VDISK_INFO        ,           0      ,       0       },

    // ������� SYSTEM - SOUND
{  226   ,"SOUND ON"       ,       0 ,      0 ,     66 ,       0 ,  &SOUND_ON                        ,  0                , 16         ,  0                      ,           0      ,       0       },
   // ������� SYSTEM - KEYS & TRIM
{  228   ,"KEY PRESS"      ,     229 ,      0 ,    227 ,       0 ,  &key_press_time                  ,  0                , 17         ,  0                      ,           0      ,       0       },
{  229   ,"KEY REPRESS"    ,     169 ,    228 ,    227 ,       0 ,  &key_repress_time                ,  0                , 17         ,  0                      ,           0      ,       0       },
{  169   ,"TRIM. PRESS"    ,     168 ,    229 ,    227 ,       0 ,  &trim_press_time                 ,  0                , 26         ,  0                      ,           0      ,       0       },
{  168   ,"0-TRIM BEEP"    ,       0 ,    169 ,    227 ,       0 ,  0                                ,  0                , 28         ,  0                      ,           0      ,       0       },

   // ������� SYSTEM - ALARM
{  174   ,"BATTERY"         ,    173 ,      0 ,     63 ,     230 ,  0                                ,  0                , 0          ,  0                      ,           0      ,       0       },
{  173   ,"FLY TIMER"       ,      0 ,    174 ,     63 ,     171 ,  0                                ,  0                , 0          ,  0                      ,           0      ,       0       },

   // ������� SYSTEM - ALARM - BATTERY
{  230   ,"BATT VOLT."      ,    167 ,      0 ,    174 ,       0 ,  &batt                            ,  0                , 18         ,  0                      ,           0      ,       0       },
{  167   ,"BATT CALIBR"     ,    231 ,    230 ,    174 ,       0 ,  0                                ,  0                , 32         ,  0                 ,           0      ,       0             },
{  231   ,"BATT ALARM"      ,      0 ,    167 ,    174 ,       0 ,  &battMin                         ,  0                , 19         ,  0                      ,           0      ,       0       },
   // ������� SYSTEM - ALARM - FLY TIMER
{  171   ,"1 MIN. BEEP"     ,    170 ,      0 ,    173 ,       0 ,  0                                ,  0                , 21         ,  0                      ,           0      ,       0       },
{  170   ,"LAST BEEP"       ,      0 ,    171 ,    173 ,       0 ,  0                                ,  0                , 22         ,  0                      ,           0      ,       0       },

// 233
};


unsigned char numItemByID(unsigned char iditem) { // ��������� ������ ������ � ������� �� ��� ID

unsigned char i;

i=0;
while (menu[i].numitem!=iditem) i++; // ���� ����� � ������ ��� ID
return i;
} //------------------------------------------------------------------------------------------------------

unsigned char getIDbefore(unsigned char colitem) { // ��������� ������ ID ������ ���� ��������������� 
unsigned char i,j;                                 // colitem ������� �������� ������ ����

    j=numitem_cur;  // ����� ������� �����
    for (i=colitem; i!=0; i--) { // � ��������� 6 ��� �����
       if (menu[ numItemByID(j) ].previtem!=0) { // ���� ������� ������� ����� �� �������� ����� �������
          j=menu[ numItemByID(j) ].previtem;
          } else { break; } // ���� �� ����� ����� ������� ����� - ������� �� �����
    }
    return j; // ���������� ID ������ ���� ��������������� �������� �� colitem �������
} //------------------------------------------------------------------------------------------------------


// ��������� ���������� �������� (�����)
void decreaseValuePar(unsigned char partype, void *pvar) {
unsigned char c;
unsigned char *pvarc; 

unsigned int  i;
unsigned int  *pvari;

signed   char *pvarsc;
signed char sc;

   switch (partype) {

      case 1: { // ��� ������
                pvarc=pvar; // ����� ���������
                c=*pvarc;   // ������ ��������
                if (c!=0) { 
                   (*pvarc)--; // ���� �������� ������ ���� - �� ��������� ��������
                   ModelChange=1;
                }
                break;
      }

      case 3: { // ���������� ������� ������������ �������
                pvarc=pvar; // ����� ���������
                c=*pvarc;   // ������ ��������
                if (c>2) { 
                    (*pvarc)--; // ���� �������� ������ 2 - �� ��������� ��������
                    ModelChange=1;
                }
                break;
      }

      case 4: { // ����������� ������������ ���������� �������� ������
                pvari=pvar; // ����� ���������
                i=*pvari;   // ������ ��������
                if (i>700) {
                    i=i-1-keyhold*9;
                    ModelChange=1;
                }
                if (i<700) i=700;
                *pvari=i;
                CalcCurveORD();
                break; 
      }

      case 6: { // ���������� ������� � ����� PPM 
                pvarc=pvar; // ����� ���������
                c=*pvarc;   // ������ ��������
                if (c>4) {
                   (*pvarc)--; // ���� �������� ������ 4 - �� ��������� ��������
                   ModelChange=1;
                }
                break;
      }

      case 7: { // ���������� �������� UCH -125..+125
                pvarsc=pvar; // ����� ���������
                sc=*pvarsc;   // ������ ��������
                if (sc>-125) { 
                   sc=sc-1-keyhold*2; // ���� �������� ������ -125 �� ��������� ��������
                   ModelChange=1;
                }
                *pvarsc=sc; 
                break;
      }

      case 8: { // �������� ��������� �������� ������
                pvarc=pvar; // ����� ���������
                c=*pvarc;   // ������ ��������
                if (c>0)   c=c-1-keyhold*2;  
                     else c=255; // ���� �������� ������ ���� - �� ��������� ��������
                *pvarc=c;
                ModelChange=1; 
                break;
      }

      case 9: { // ���� ������� ������
                pvarc=pvar; // ����� ���������
                c=*pvarc;   // ������ ��������
                if (c==0) (*pvarc)=1;  else  (*pvarc)=0; // ������ �������� �� ���������������
                ModelChange=1;
                break;
      }

      case 10: { // ���������� �������� ������� 1..3
                pvarc=pvar; // ����� ���������
                c=*pvarc;   // ������ ��������
                if (c>1) { 
                   (*pvarc)--; // ���� �������� ������ ������� - �� ��������� ��������
                   ModelChange=1;
                }
                break;
      }

      case 12: { // �������� ��������� ������ 
                pvarc=pvar; // ����� ���������
                c=*pvarc;   // ������ ��������
                if (c>0) { 
                   (*pvarc)--; // ���� �������� ������ ������� - �� ��������� ��������
                   ModelChange=1;
                }
                break;
      }

      case 13: { // �������� �������� -125..+125
                pvarsc=pvar; // ����� ���������
                sc=*pvarsc;   // ������ ��������
                if (sc>-125) { 
                    sc=sc-1-2*keyhold ; // ���� �������� ������ -125 �� ��������� ��������
                    ModelChange=1;
                }
                if (sc<-125) sc=-125;
                *pvarsc=sc;
                break;
      }

      case 14: { // ������� ������������ ���������� �������� 
                pvari=pvar; // ����� ���������
                i=*pvari;   // ������ ��������
                if (i>700) { 
                   i=i-1-keyhold*9;
                   ModelChange=1;
                }
                if (i<700) i=700;
                *pvari=i;
                CalcCurveORD();
                break; 
      }

      case 15: { // ������ �������� �������� ������� (16, 32, 48, 64) 
                if (E_ClusterSize>16) { 
                   E_ClusterSize=E_ClusterSize-16;
                } 
                break;
      }

      case 16: { // ���� ��������� �����
                pvarc=pvar; // ����� ���������
                c=*pvarc;   // ������ ��������
                if (c==1) (*pvarc)=0;  else  (*pvarc)=1; // ������ �������� �� ���������������
                E_SOUND_ON=SOUND_ON;
                break;
      }

      case 17: { // �������� �� ������� ������
                pvarc=pvar; // ����� ���������
                c=*pvarc;   // ������ ��������
                if (c>3) (*pvarc)--; // ���� �������� ������ 3 - �� ��������� ��������
                E_key_press_time=key_press_time;
                E_key_repress_time=key_repress_time;
                resetKeyReader();
                break;
      }

      case 19: { // ����������� ���������� �� ������� �����������
                pvari=pvar; // ����� ���������
                i=*pvari;   // ������ ��������
                if (i>420) i=i-7;
                if (i<420) i=420;
                *pvari=i;
                E_battMin=i; 
                break;
      }

      case 20: { // ������� ��������� �������
                c=E_eventStart;   // ������ ��������
                if (c>0) c--;  else  c=8; 
                E_eventStart=c;
                break;
      }

      case 21: { // ��������� ��������� ������� ������ 1 ������ ������ �������
                c=E_beep1min;   // ������ ��������
                if (c==1) c=0;  else  c=1; // ������ �������� �� ���������������
                E_beep1min=c;
                break;
      }

      case 22: { // ��������� ��������� ������� ������ 1 ������ ������ �������
                c=E_beep2sec;   // ������ ��������
                if (c==1) c=0;  else  c=1; // ������ �������� �� ���������������
                E_beep2sec=c;
                break;
      }

      case 23: { // ��������� ������� �������
                pvari=pvar; // ����� ���������
                i=*pvari;   // ������ ��������
                if (posxmenu==1) { // ����������� ������ (����)
                    if ((i/60)>0) {
                        (*pvari)=((i/60)-1)*60 + i%60;
                        ModelChange=1;
                    }
                } 
                  else { //����������� ������� (������)                 
                      if ((i%60)>0) { 
                          (*pvari)=i-1;
                          ModelChange=1;
                      }
                  }
                break; 
      }

      case 24: { //  ��������� ��������� ������� ��������� ������� ������
                 flyCurrTimer=rmodel.MODEL_FLYTIMER;
                break;
      }

      case 25: { //  ���������� ������� ����� ������
                 if (flyCurrTimer<rmodel.MODEL_FLYTIMER) {
                  // ����������� ����� ����� ������
                  rmodel.MODEL_LIVETIMER=rmodel.MODEL_LIVETIMER+(rmodel.MODEL_FLYTIMER-flyCurrTimer)/60;
                  flyCurrTimer=rmodel.MODEL_FLYTIMER;
                  ModelChange=1;
                 }
                break;
      }

      case 26: { // �������� �� ������� ������ ��������
                pvarc=pvar; // ����� ���������
                c=*pvarc;   // ������ ��������
                if (c>5) (*pvarc)--; // ���� �������� ������ 5 - �� ��������� ��������
                E_trim_press_time=trim_press_time;
                break;
      }

      case 27: { // ����� ���������� �������
                c=E_eventStop;   // ������ ��������
                if (c>0) c--;  else  c=8; 
                E_eventStop=c;
                break;
      }

      case 28: { // ���������� � ������� ��������� ��������
                c=E_nulTrimBeep;   // ������ ��������
                if (c==1) c=0;  else  c=1; // ������ �������� �� ���������������
                E_nulTrimBeep=c;
                break;
      }

      case 29: { // ����������� �������� �������
                rmodel.FMODE[fmode_to-1].FMODE_NAME=rmodel.FMODE[fmode_source-1].FMODE_NAME;
                rmodel.FMODE[fmode_to-1].TRIMSTEP=rmodel.FMODE[fmode_source-1].TRIMSTEP;
                // ��������
                for (c=0;c<7;c++) 
                    rmodel.FMODE[fmode_to-1].UCH_TRIMMER[c]=rmodel.FMODE[fmode_source-1].UCH_TRIMMER[c];
                // ������� �����
                for (c=0;c<16;c++) 
                    rmodel.FMODE[fmode_to-1].LCH_MIDLE[c]=rmodel.FMODE[fmode_source-1].LCH_MIDLE[c];
                // ������
                for (c=0;c<16;c++) 
                   rmodel.FMODE[fmode_to-1].LCH_CURVE[c]=rmodel.FMODE[fmode_source-1].LCH_CURVE[c];       
                // �������
                for (c=0;c<40;c++)
                   rmodel.FMODE[fmode_to-1].MIXER[c]=rmodel.FMODE[fmode_source-1].MIXER[c];                   
                
                break;
      }

      case 30: { // ���������� ������� PPM
                if (E_var3==0) E_var3=1;  else  E_var3=0; // ������ �������� �� ���������������
                break;
      }

      case 31: { // �������� ������
                if (E_var4>20) {
                   E_var4--; // ���� �������� ������ 20 - �� ��������� ��������
                   LCD_setContrast(E_var4);
                }
                break;
      }

      case 32: { // ���������� �������� �������
                if (E_var11>0) {
                   E_var11--; // ���� �������� ������ 0 - �� ��������� ��������
                }
                break;
      }

      case 33: { // ��������� ������� ����������
                if (E_var12<4) E_var12++;
                break;
      }


   }
}

// ��������� ���������� �������� (�����)
void increaseValuePar(unsigned char partype, void *pvar) {
unsigned char c;
unsigned char *pvarc;

unsigned int  i;
unsigned int  *pvari;

signed   char *pvarsc;
signed char sc;

 
   switch (partype) {

      case 1: { // ��� ������ 1..3 (���������!)
                pvarc=pvar; // ����� ���������
                c=*pvarc;   // ������ ��������
                if (c<MODEL_TYPE_COUNT) { 
                    (*pvarc)++; // ���� �������� ������ ���������� �����
                    ModelChange=1;                          // �� ����������� ��������
                }
                break;
      }

      case 3: { // ���������� ������� ������ (1..16)
                pvarc=pvar; // ����� ���������
                c=*pvarc;   // ������ ��������
                if (c<16) { 
                    (*pvarc)++; // ���� �������� ������ 16, �� ����������� ��������
                }
                break;
      }

      case 4: { // ������������ ���������� �������� 700..2300
                pvari=pvar; // ����� ���������
                i=*pvari;   // ������ ��������
                if (i<2300) {
                   i=i+1+keyhold*9;
                   ModelChange=1;
                }
                if (i>2300) i=2300;
                *pvari=i;
                CalcCurveORD(); 
                break;
      }

      case 6: { // ���������� ������� � ����� PPM (4..8) / ��� ��������� �������� ��������� ������
                pvarc=pvar; // ����� ���������
                c=*pvarc;   // ������ ��������
                if (c<8) { 
                   (*pvarc)++; // ���� �������� ������ 8, �� ����������� ��������
                   ModelChange=1;
                }
                break;
      }

      case 7: { // ���������� �������� UCH -125..+125
                pvarsc=pvar; // ����� ���������
                sc=*pvarsc;   // ������ ��������
                if (sc<125) {
                   sc=sc+1+2*keyhold;
                   ModelChange=1;
                }
                if (sc>125) sc=125;
                *pvarsc=sc; // ���� �������� ������ 125, �� ����������� ��������
                break;
      }

      case 8: { // �������� ��������� �������� ������� 0..255
                pvarc=pvar; // ����� ���������
                c=*pvarc;   // ������ ��������
                if (c<255) c=c+1+keyhold*2; else c=0; // �� ����������� ��������
                *pvarc=c; 
                ModelChange=1;
                break;
      }

      case 9: { // ���� ������� ������   0..1
                pvarc=pvar; // ����� ���������
                c=*pvarc;   // ������ ��������
                if (c==0) (*pvarc)=1;  else  (*pvarc)=0; // ������ �������� �� ���������������
                ModelChange=1;
                break;
      }

      case 10: { // ���������� �������� ������� (1..3)
                pvarc=pvar; // ����� ���������
                c=*pvarc;   // ������ ��������
                if (c<3) (*pvarc)++; // ���� �������� ������ 3, �� ����������� ��������
                ModelChange=1;
                break;
      }

      case 12: { // ��� ��������� ������ (1..SL_FMODE_NAME_COUNT)
                pvarc=pvar; // ����� ���������
                c=*pvarc;   // ������ ��������
                if (c+1<SL_FMODE_NAME_COUNT) (*pvarc)++; // ���� �������� ������ SL_FMODE_NAME_COUNT, �� ++
                ModelChange=1;
                break;
      }

      case 13: { // �������� �������� -125..+125
                pvarsc=pvar; // ����� ���������
                sc=*pvarsc;   // ������ ��������
                if (sc<125) sc=sc+1+2*keyhold;
                if (sc>125) sc=125;
                *pvarsc=sc; 
                ModelChange=1;
                break;
      }

      case 14: { // ������� �������� ���������� �������� 700..2300
                pvari=pvar; // ����� ���������
                i=*pvari;   // ������ ��������
                if (i<2300) i=i+1+keyhold*9;
                if (i>2300) i=2300;
                *pvari=i;
                ModelChange=1; 
                break;
      }

      case 15: { // ������ �������� �������� ������� (16, 32, 48, 64)
                if (E_ClusterSize<64) { 
                   E_ClusterSize=E_ClusterSize+16;
                }
                break;
      }

      case 16: { // ���� ��������� �����
                pvarc=pvar; // ����� ���������
                c=*pvarc;   // ������ ��������
                if (c==1) (*pvarc)=0;  else  (*pvarc)=1; // ������ �������� �� ���������������
                E_SOUND_ON=SOUND_ON;
                break; 
      }

      case 17: { // �������� �� ������� ������
                pvarc=pvar; // ����� ���������
                c=*pvarc;   // ������ ��������
                if (c<20) (*pvarc)++; // ���� �������� ������ 20 - �� ����������� ��������                
                E_key_press_time=key_press_time;
                E_key_repress_time=key_repress_time;
                resetKeyReader();
                break;
      }

      case 19: { // ����������� ���������� �� ������� �����������
                pvari=pvar; // ����� ���������
                i=*pvari;   // ������ ��������
                if (i<840) i=i+7;
                if (i>840) i=840;
                *pvari=i;
                E_battMin=i; 
                break;
      }

      case 20: { // ������� ��������� �������
                c=E_eventStart;   // ������ ��������
                if (c<8) c++;  else  c=0; 
                E_eventStart=c;
                break;
      }

      case 21: { // ��������� ��������� ������� ������ 1 ������ ������ �������
                c=E_beep1min;   // ������ ��������
                if (c==1) c=0;  else  c=1; // ������ �������� �� ���������������
                E_beep1min=c;
                break;
      }

      case 22: { // ��������� ��������� ������� ������ 1 ������ ������ �������
                c=E_beep2sec;   // ������ ��������
                if (c==1) c=0;  else  c=1; // ������ �������� �� ���������������
                E_beep2sec=c;
                break;
      }

      case 23: { // ��������� ������� �������
                pvari=pvar; // ����� ���������
                i=*pvari;   // ������ ��������
                if (posxmenu==1) { // ����������� ������ (����)
                    if ((i/60)<99) { 
                      (*pvari)=((i/60)+1)*60 + i%60;
                      ModelChange=1;
                    }
                } 
                  else { //����������� ������� (������)                 
                    if ((i%60)<59) {
                       (*pvari)=i+1;
                       ModelChange=1;
                    }
                  }
                break; 
      }

      case 24: { //  ��������� ��������� ������� ��������� ������� ������
                 flyCurrTimer=rmodel.MODEL_FLYTIMER;
                 break;
      }

      case 25: { //  ���������� ������� ����� ������
                 if (flyCurrTimer<rmodel.MODEL_FLYTIMER) {
                   // ����������� ����� ����� ������
                   rmodel.MODEL_LIVETIMER=rmodel.MODEL_LIVETIMER+(rmodel.MODEL_FLYTIMER-flyCurrTimer)/60;
                   flyCurrTimer=rmodel.MODEL_FLYTIMER;
                   ModelChange=1;
                 }
                break;
      }

      case 26: { // �������� �� ������� ������ ��������
                pvarc=pvar; // ����� ���������
                c=*pvarc;   // ������ ��������
                if (c<20) (*pvarc)++; // ���� �������� ������ 20 - �� ����������� ��������
                E_trim_press_time=trim_press_time;
                break;
      }

      case 27: { // ����� ���������� �������
                c=E_eventStop;   // ������ ��������
                if (c<8) c++;  else  c=0; 
                E_eventStop=c;
                break;
      }

      case 28: { // ���������� � ������� ��������� ��������
                c=E_nulTrimBeep;   // ������ ��������
                if (c==1) c=0;  else  c=1; // ������ �������� �� ���������������
                E_nulTrimBeep=c;
                break;
      }

      case 29: { // ����������� �������� �������
                rmodel.FMODE[fmode_to-1].FMODE_NAME=rmodel.FMODE[fmode_source-1].FMODE_NAME;
                rmodel.FMODE[fmode_to-1].TRIMSTEP=rmodel.FMODE[fmode_source-1].TRIMSTEP;
                // ��������
                for (c=0;c<7;c++) 
                    rmodel.FMODE[fmode_to-1].UCH_TRIMMER[c]=rmodel.FMODE[fmode_source-1].UCH_TRIMMER[c];
                // ������� �����
                for (c=0;c<16;c++) 
                    rmodel.FMODE[fmode_to-1].LCH_MIDLE[c]=rmodel.FMODE[fmode_source-1].LCH_MIDLE[c];
                // ������
                for (c=0;c<16;c++) 
                   rmodel.FMODE[fmode_to-1].LCH_CURVE[c]=rmodel.FMODE[fmode_source-1].LCH_CURVE[c];       
                // �������
                for (c=0;c<40;c++)
                   rmodel.FMODE[fmode_to-1].MIXER[c]=rmodel.FMODE[fmode_source-1].MIXER[c];                   
                
                break;
      }

      case 30: { // ���������� ������� PPM
                if (E_var3==0) E_var3=1;  else  E_var3=0; // ������ �������� �� ���������������
                break;
      }

      case 31: { // �������� ������
                if (E_var4<45) { 
                    E_var4++; // ���� �������� ������ 40 - �� ����������� ��������
                    LCD_setContrast(E_var4);
                }

                break;
      }

      case 32: { // ���������� �������� �������
                if (E_var11<254) {
                   E_var11++; // ���� �������� ������ 254 - �� ����������� ��������
                }
                break;
      }

      case 33: { // ��������� ������� ����������
                if (E_var12>1) E_var12--;
                break;
      }

   }
}


void disp_menu(void) { //----------------------------------------------------------- ��������� ������ ����
unsigned char printStart; // ����� ���� ��� ������
unsigned char i,j,tmp, tmp2, tmp3, paramcount;        // ��������� ���������� - �����������
unsigned char mode, mode1, mode2;       // 0 - ������� �����, 1 - ���������� ��������
unsigned char * pvarc;    // ��������� ���������� ��������� �� ���������� ���� char
unsigned int  * pvari;    // ��������� ���������� ��������� �� ���������� ���� int
unsigned int  ti; // ��������� ����������
signed char * pvarsc; //��������� ���������� ��������� �� ���������� signed char
signed char  sc;

unsigned char itemcounter; // ������� ���������� �������
unsigned char downstop; // ������������ �������� ���� (��� ��������� 1)

 
// �������� ���������
   printStart=getIDbefore(100); // �������� ID ������� ������
   printStart=menu[numItemByID(printStart)].upitem; // ������ �� ������� ����� ����
   LCD_setxy(0,0); 
   while (LCD_X<20) LCD_char(' ', 1); 
   LCD_wrsf(menu[numItemByID(printStart)].itemstr,1); // �������� ���������
   while (LCD_X<123) LCD_char(' ', 1); 

   pvarc=menu[numItemByID(printStart)].colitemcount; // ���������� ������������ ������� ���� 
   if (pvarc!=0) itemcounter=*pvarc; else itemcounter=255;   

   printStart=getIDbefore(5); // �������� ID ������ ��������������� �� ���������� �������� �� 6 �������
   
   paramcount=0;  // ���������� ���������� ������ ����
  
   for (i=0;i<6;i++) { // ������� � ����� 6 ������� ����
    
     tmp2=numItemByID(printStart); // ���������� ���������� ����� ������ ���� � �������
                                   // ����� �� ��������� ������ ��� � �� ������ �� ��� �����               
    
     if (printStart!=numitem_cur) { // ���� ����� ������ �������� ? 
        mode=0; mode2=0;  // ���, �������� � ��������
        } 
          else { 
            mode=1;    // ���� ����� ������ !
            if (posxmenu==0) mode2=1; else mode2=1; // ������ ��������� ������ 
          }   
     
     LCD_setxy(0,i+2); LCD_wrsf ( menu[ tmp2 ].itemstr, mode2); // ������ ������
     while (LCD_X<59) LCD_char(' ',mode2); // ������� ���������
     
      LCD_setxy(60, i+2);
      // ���� ����� ��������� �� ���� ������� ������ �� ������ >
      if ((menu[ tmp2 ].downitem!=0)||(menu[ tmp2 ].menu_proc!=0))  { LCD_char('>',0); } 
      else { if (menu[ tmp2 ].partype!=0) LCD_char('=',0); else LCD_char(' ',0); }
      
       
      // �������� �������� (���� ����) ��������� ��� ������ ����
      LCD_setxy(65, i+2);

      switch (mode) {       
         case 0: { // ����� �� ������-������ �������� �� �����
                   mode1=0; mode2=0; break; 
         }
         
         case 1: { // ����� ������ - �������� ��� �������������
                   if (posxmenu==0) { mode1=1;  mode2=1; } 
                   if (posxmenu==1) { mode1=2;  mode2=1; } 
                   if (posxmenu==2) { mode1=1;  mode2=2; }                   
                   break; 
         } 
      }
      LCD_X=LCD_X+5;
      tmp=menu[ tmp2 ].partype; // ����� ��� ���������
      switch (tmp) {
         case 1: { // ������ ���������� �������� - ��� ������
                    pvarc=menu[ tmp2 ].pvar1; // ����� ���������
                    if (((*pvarc)>=0) && ((*pvarc)<3))
                       LCD_wrsf(MODEL_TYPE[*pvarc],mode1); // �������� ��� ������ �� �������
                    if (mode==1) paramcount=1;
                 break;
         }
         
         case 2: { // ������ ����� ������
                    pvarc=menu[ tmp2 ].pvar1;
                    for(j=0;j<8;j++) {
                      LCD_char(*pvarc, mode1);
                      pvarc++; 
                    }
                    if (mode==1) paramcount=0;
                 break; 
         }

         case 3: { // ���������� ������������ ������� (1..16)
                    pvarc=menu[ tmp2 ].pvar1;
                    LCD_dec(*pvarc, 2, mode1);
                    if (mode==1) paramcount=1;
                 break; 
         }

         case 4: { // �������� ����� �������. 2 �������� �� 700 �� 2300)
                    pvari=menu[ tmp2 ].pvar1;
                    LCD_dec(*pvari, 4, mode1);

                    LCD_char(' ', 0); LCD_char(' ', 0);
                   
                    pvari=menu[ tmp2 ].pvar2;
                    LCD_dec(*pvari, 4, mode2);
                    if (mode==1) paramcount=2;
                 break; 
         }
         
         case 5: { // ������ ������� ������ � ����
                    pvarc=menu[ tmp2 ].pvar1; // ����� ���������
                    LCD_wrsf(CHANNEL_FILTER_TYPE[*pvarc],mode1); // �������� ��� ������� �� �������
                    LCD_char(' ',mode1);

                    pvari=menu[ tmp2 ].pvar2; // ����� ���������
                  
                    switch (*pvarc) { // �������� ��������������� �������� �������
                        case 1: {  // ������-�����������, �������� ��� �����������
                                 LCD_wrsf(UCH_Names[(*pvari)%256],mode1); //��� �����������
                                 break;
                        }
                        case 2: { // ������ �������������, �������� ��������������� ������
                                  ti=*pvari;
                                  for (j=0;j<16;j++) {
                                     if ((ti%2)==1) LCD_char(CHNUM_table[j],mode1);
                                     ti=ti/2;
                                  }
                        }
                    } 
                    if (mode==1) paramcount=0; // ���� ����� ������������� ������ ����� ��������� 
                    break;
         }

         case 6: { // ���������� ������� � ����� PPM (1..8) / ��� ��������� �������� ��������� ������
                    pvarc=menu[ tmp2 ].pvar1;
                    LCD_dec(*pvarc, 1, mode1);
                    if (mode==1) paramcount=1;
                 break; 
         }          
         
         case 7: { // ���������� �������� UCH
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

         case 8: { // �������� ��������� �������� �������. 2 �������� �� 0 �� 255
                    pvarc=menu[ tmp2 ].pvar1;
                    LCD_dec(*pvarc, 3, mode1);

                    LCD_char(' ', 0); LCD_char(' ', 0);

                    pvarc=menu[ tmp2 ].pvar2;
                    LCD_dec(*pvarc, 3, mode2);
                                        
                    if (mode==1) paramcount=2;
                 break; 
         }

         case 9: { // ���� ������� ������
                    pvarc=menu[ tmp2 ].pvar1;
                    if ((*pvarc)==0) LCD_wrsf("NORMAL", mode1); else LCD_wrsf("REVERSE", mode1);
                    if (mode==1) paramcount=1;
                 break; 
         }          

         case 10: { // ���������� �������� ������� (1..3)
                    pvarc=menu[ tmp2 ].pvar1;
                    LCD_dec(*pvarc, 1, mode1);
                    if (mode==1) paramcount=1;
                 break; 
         }          

         case 11: { // ������ ���������� �������� - ��� ��������� ������
                    pvarc=menu[ tmp2 ].pvar1; // ����� ���������
                    LCD_wrsf(SL_FMODE_NAME[*pvarc],mode1); // �������� ��� ������ �� �������
                    if (mode==1) paramcount=0;
                 break;
         }

         case 12: { // ������ ���������� �������� - ��� ��������� ������ + �������������� ����
                    pvarc=menu[ tmp2 ].pvar1; // ����� ���������
                    LCD_wrsf(SL_FMODE_NAME[*pvarc],mode1); // �������� ��� ������ �� �������
                    if (mode==1) paramcount=1;
                 break;
         }

         case 13: { // �������� �������� -125..+125
                    pvarsc=menu[ tmp2 ].pvar1;
                    sc=*pvarsc;
                    if (sc<0) { LCD_char('-',mode1); sc=-sc; } else LCD_char('+',mode1);
                    LCD_dec(sc, 3, mode1); 
                    if (mode==1) paramcount=1;
                 break; 
         }          

         case 14: { // ������� ����� ������. 1 �������� �� 700 �� 2300
                    LCD_X=LCD_X-4;
                    pvari=menu[ tmp2 ].pvar1;
                    
                    if ((printStart>=175) && (printStart<=190)) { 
                       // �������� ����� 1
                       tmp3=printStart-175; // ����� ������                               
                    }  else
                    if ((printStart>=191) && (printStart<=206)) { 
                       // �������� ����� 2
                       tmp3=printStart-191; // ����� ������                               
                    }  else
                    if ((printStart>=207) && (printStart<=222)) { 
                       // �������� ����� 3
                       tmp3=printStart-207; // ����� ������                               
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

         case 15: { // ������ �������� �������� ������� (16, 32, 48, 64)
                    LCD_dec(E_ClusterSize, 2, mode1);
                    if (mode==1) paramcount=1;
                 break; 
         }

         case 16: { // ���� ��������� �����
                    pvarc=menu[ tmp2 ].pvar1;
                    if ((*pvarc)==1) LCD_wrsf("ON", mode1); else LCD_wrsf("OFF", mode1);
                    if (mode==1) paramcount=1;
                 break; 
         }          

         case 17: { // �������� �� ������������ ������ ����
                    pvarc=menu[ tmp2 ].pvar1;
                    LCD_dec(*pvarc, 2, mode1);
                    if (mode==1) paramcount=1;
                 break; 
         }

         case 18: { // ���������� �� ������� �����������               
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

         case 19: { // ����������� ���������� �� ������� ����������� (������������� ����)               
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

         case 20: { // ������ ��������� ��������� �������
                    if (E_eventStart==8) LCD_wrsf("MANUAL",mode1);
                       else { 
                          LCD_wrsf("CH",mode1);
                          LCD_dec((unsigned int)E_eventStart+1,1,mode1);
                          LCD_wrsf(" >20%",mode1);
                       }                    
                    if (mode==1) paramcount=1;
                 break; 
         }

         case 21: { // ��������� ������ 1 ������ ��������� ������� ��������� �������
                    if (E_beep1min==0) LCD_wrsf("OFF",mode1);
                       else LCD_wrsf("ON",mode1);                    
                    if (mode==1) paramcount=1;
                 break; 
         }

         case 22: { // ��������� ������ 2 � � ������� ��������� ������ ��������� ������� ��������� �������
                    if (E_beep2sec==0) LCD_wrsf("OFF",mode1);
                       else LCD_wrsf("ON",mode1);                    
                    if (mode==1) paramcount=1;
                 break; 
         }

         case 23: { // �������� �������
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

         case 24: { // ��������� ��������� ������� � ������������ � �������� ������
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

         case 25: { // ���������� �������� ���������� ������� ������
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

         case 26: { // �������� �� ������������ ������ ��������
                    pvarc=menu[ tmp2 ].pvar1;
                    LCD_dec(*pvarc, 2, mode1);
                    if (mode==1) paramcount=1;
                 break; 
         }

         case 27: { // ������ ��������� ��������� �������
                    if (E_eventStop==8) LCD_wrsf("MANUAL",mode1);
                       else { 
                          LCD_wrsf("CH",mode1);
                          LCD_dec((unsigned int)E_eventStop+1,1,mode1);
                          LCD_wrsf(" <10%",mode1);
                       }                    
                    if (mode==1) paramcount=1;
                 break; 
         }

         case 28: { // ��������� �� � �������� � ������� ��������� ������ � ������
                    if (E_nulTrimBeep==0) LCD_wrsf("NO EVENT",mode1);
                       else LCD_wrsf("BEEP&PAUSE",mode1);                    
                    if (mode==1) paramcount=1;
                 break; 
         }

         case 29: { // ����������� �������� �������
                    LCD_wrsf("COPY",mode1);
                    if (mode==1) paramcount=1;
                 break; 
         }

         case 30: { // ���������� ������� PPM
                    if (E_var3==0) LCD_wrsf("POSITIVE",mode1);
                       else LCD_wrsf("NEGATIVE",mode1);                    
                    if (mode==1) paramcount=1;
                 break; 
         }
         
         case 31: { // ������������� ������
                    LCD_dec(E_var4, 2, mode1);
                    if (mode==1) paramcount=1;
                 break; 
         }

         case 32: { // ���������� �������� �������
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

         case 33: { // ��������� ������ (mode)
                    LCD_dec(E_var12, 1, mode1);
                    if (mode==1) paramcount=1;
                 break; 
         }
                 
      }

      downstop=0;
      // �������� �� ������ ���� ������������ ������� ����
      if ((itemcounter==menu[ tmp2 ].colitem) && (mode==1)) {
         // ���� ������� ����� ���� ������ � �������� ��������� �� ����������� - ������ �������� ���� ! 
         downstop=1; 
      } 

      if (itemcounter==menu[ tmp2 ].colitem) {
         break; 
      } 
               
      printStart=menu[ tmp2 ].nextitem;   // ����� ����� ���������� ������ ����         
      if (printStart==0) { break; } // ���� ���������� ��� ������ �� ������� �� �����
   }
   
   tmp2=numItemByID(numitem_cur);
   i=get_mnu_keys(); // ��������� ������� ������� ��������� �� ����
   switch (i) { // �������� ������� �������

     case 246: {  // ������ ������� DN (����)
                 switch (posxmenu) {
     
                    case 0: { // �� ��������� �� ���� ����
                              if ((menu[tmp2].nextitem!=0) && (downstop==0)) { // ���� ���� ����� ����
                                                              // � ��� ������� ��������� ����
                                  
                                  numitem_cur=menu[tmp2].nextitem;  // ���� � ���������� ������
                              }
                              break; 
                    }  
                    
                    case 1: { // �� ��������� �������� ���������� ���������1
                              decreaseValuePar(menu[tmp2].partype,menu[tmp2].pvar1); // ���������� ��������
                              break;
                    }
                    
                    case 2: { // �� ��������� �������� ���������� ���������2
                              decreaseValuePar(menu[tmp2].partype,menu[tmp2].pvar2); // ���������� ��������

                    } 
                 }  
                 break; 
     } 

     case 238: { // ������ ������� UP (�����)
                   switch (posxmenu) {
     
                       case 0: { // �� ��������� �� ���� �����
                               if (menu[tmp2].previtem!=0) {
                                  numitem_cur=menu[tmp2].previtem;
                               }
                               break;
                       }

                       case 1: { // �� ����������� �������� ���������� ���������1
                              increaseValuePar(menu[tmp2].partype,menu[tmp2].pvar1); // ���������� ��������
                              break;
                       }
                    
                       case 2: { // �� ����������� �������� ���������� ���������2
                              increaseValuePar(menu[tmp2].partype,menu[tmp2].pvar2); // ���������� ��������

                       }  
                   }
                   break;
     } 
                             
     case 250: { // ������ ������� EXIT (������� � ����������� ����)
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
                  resetKeyReader(); // ����� ����������  
                  break; }
               
     case 252: {  // ������ ������� MENU/ENT (������� � ����������� ����/����� ���������)                

                   resetKeyReader(); // ����� ���������� 
                  
                   if (menu[numItemByID(numitem_cur)].downitem!=0) { // ��������� � ����������� ���� 
                       numitem_cur=menu[numItemByID(numitem_cur)].downitem;
                   posxmenu=0;
                   }
                     else {   // ������ ���������
                          if (menu[numItemByID(numitem_cur)].menu_proc!=0) {  
                             menu_proc=menu[numItemByID(numitem_cur)].menu_proc; // ���� ���� ��������� 
                             menu_exe=1;   // ��������� - ������ ���� ������� � ���������� �� �����
                          } 
                            else {  // ���� ���� ����������� ��������� ��� �������������� ������
                               if (paramcount>posxmenu) posxmenu++; else posxmenu=0;
                            }
                        }          
                  break; 
     } 

     case 222: {  if (paramcount>posxmenu) posxmenu++; // ������ ������� '-' (��������� ������)
                  break; }

     case 190: {  if (posxmenu>0) posxmenu--;          //������ ������� '+' (��������� �����)
                  break; }

      default:
   
   }
}              

// ------------------------------------------------------------- ��������� ��������� "��������� ������"
unsigned char flyinfo_mode; // ����� "��������� ������"

// - - - - - - - - - - - - �������� ������ � ������������ ��������
// __flash unsigned char rmess[]="                             8 PPM channels, 16 logical channels, variable mixers, up to 16 model memory, freendly user interface...                             ";
unsigned char mess_posx, mess_char, mess_pause;
void messScroll(void) {
// unsigned char i;
  LCD_setxy(0,1); LCD_wrsf("   V-CODER  ver. 0.99b   ",0);
}

// ��������� ������ �������� � ����1 � ����2
void printTrimMode12() {
signed char sc;
   // ������� ������ 3 -  Throtle
   sc=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[2];
   if (E_var12==2) LCD_setxy(0,3); else LCD_setxy(120,3);
   if (sc<0) { LCD_char('-',0); sc=-sc; } else { LCD_char('+',0); }
   if (E_var12==2) LCD_setxy(0,4); else LCD_setxy(120,4);  
   LCD_V_dec(2*((unsigned int)sc) , 3, 0);
 
   // ������� ������ 2 - Elevator 
   sc=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[1];
   if (E_var12==2) LCD_setxy(120,3); else LCD_setxy(0,3); 
   if (sc<0) { LCD_char('-',0); sc=-sc; } else { LCD_char('+',0); }
   if (E_var12==2) LCD_setxy(120,4); else LCD_setxy(0,4);
   LCD_V_dec(2*((unsigned int)sc) , 3, 0);

   // ������� ������ 4 - Rudder 
   sc=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[3];
   LCD_setxy(5,7);
   if (sc<0) { LCD_char('-',0); sc=-sc; } else { LCD_char('+',0); }
   LCD_dec(2*((unsigned int)sc) , 3, 0);

   // ������� ������ 1 - Aileron
   sc=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[0];
   LCD_setxy(100,7);
   if (sc<0) { LCD_char('-',0); sc=-sc; } else { LCD_char('+',0); }
   LCD_dec(2*((unsigned int)sc) , 3, 0);
}

// ��������� ������ �������� � ����3 � ����4
void printTrimMode34() {
signed char sc;
   // ������� ������ 3 -  Throtle
   sc=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[2];
   if (E_var12==4) LCD_setxy(120,3); else LCD_setxy(0,3);
   if (sc<0) { LCD_char('-',0); sc=-sc; } else { LCD_char('+',0); }
   if (E_var12==4) LCD_setxy(120,4); else LCD_setxy(0,4);  
   LCD_V_dec(2*((unsigned int)sc) , 3, 0);
 
   // ������� ������ 2 - Elevator 
   sc=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[1];
   if (E_var12==4) LCD_setxy(0,3); else LCD_setxy(120,3); 
   if (sc<0) { LCD_char('-',0); sc=-sc; } else { LCD_char('+',0); }
   if (E_var12==4) LCD_setxy(0,4); else LCD_setxy(120,4);
   LCD_V_dec(2*((unsigned int)sc) , 3, 0);

   // ������� ������ 4 - Rudder 
   sc=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[3];
   LCD_setxy(100, 7);
   if (sc<0) { LCD_char('-',0); sc=-sc; } else { LCD_char('+',0); }
   LCD_dec(2*((unsigned int)sc) , 3, 0);

   // ������� ������ 1 - Aileron
   sc=rmodel.FMODE[FMODE_NUM].UCH_TRIMMER[0];
   LCD_setxy(5, 7);
   if (sc<0) { LCD_char('-',0); sc=-sc; } else { LCD_char('+',0); }
   LCD_dec(2*((unsigned int)sc) , 3, 0);
}


// �������� ����� - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
void flyInfo(void) {
unsigned char i,x,y;
// signed char sc;
unsigned int ii; //, chl;

   // ��� ������
   LCD_setxy(0,0); for (i=0;i<8;i++) LCD_char(rmodel.MODEL_NAME[i], ModelChange);

   // �������� ��������� ������
   LCD_setxy(50,0); 
   LCD_wrsf(SL_FMODE_NAME[rmodel.FMODE[FMODE_NUM].FMODE_NAME],1);
  
   // ���������� �������
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
   
   // �������� ������
   if (flyinfo_mode!=4) {
       LCD_big_dec(38,48, flyCurrTimer/60 ,2);
       if ((flyTimerOn==1) && (BLINK==1)) LCD_big_char(58,48,' '); else LCD_big_char(58,48,':');
       LCD_big_dec(68,48, flyCurrTimer%60 ,2);
   } else 
    { // ������� ������� �������� ������
       LCD_big3_dec(25,25, flyCurrTimer/60 ,2);
       if ((flyTimerOn==1) && (BLINK==1)) LCD_big3_char(55,25,' '); else LCD_big3_char(55,25,':');
       LCD_big3_dec(70,25, flyCurrTimer%60 ,2);   

       messScroll();                                  
    }  
   
   switch (flyinfo_mode) {
      case 1: { // ������� ��������� ������������ � ��������
                LCD_setxy(10,3); LCD_wrsf("THRCT",SW_ThroCut);
                LCD_setxy(10,4); LCD_wrsf("RUD.D", SW_RuddDR);
                LCD_setxy(10,5); LCD_wrsf("ELE.D", SW_ElevDR);

                LCD_setxy(90,3); LCD_wrsf("TRN.", SW_Trainer);
                LCD_setxy(90,4); LCD_wrsf("GEAR",SW_Gear);
                LCD_setxy(90,5); LCD_wrsf("AIL.D",SW_AileDR); 

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

      case 2: { // ������� ������������ ��������� ���������
/**      
                    // ������� ������ ������� ������������������
                LCD_setxy(0,1);
                 x=16; // � ��� ����� �� 16�� �������
                 chl=rmodel.CHANNELS.FILTER[4].VAL1; // ����� �������������� ����
                 LCD_dec(chl,5,0);
                 LCD_char(' ',0);
                 // ������� ����������� ��� ����� - ��������� �� ������ ������� ��� ������
                 for (y=0; y<4; y++) { // ��������� �� ������ ������
                   i=chl%2;                             
                   chl=chl/2;              // �����!, ��������� �� ��������� �����
                   if (x!=0) x--;   
                      while ((x!=0) && (i==0)) { // ������� ����� ������ ��� ������ 
                         i=chl%2;
                         chl=chl/2; 
                         x--; 
                      }                                                                                                                                                            
                        LCD_dec((unsigned int)x,2,0);
                        LCD_char(' ', 0);
                 }
**/      
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
                break; 
      }

      case 3: { // ������� ���������� ������������ ��������� ���������
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
                break; 
      }

   }     

   i=get_mnu_keys(); // ��������� ������� ������� ��������� �� ����
   switch (i) {
     case 190: {  if (flyinfo_mode<4) flyinfo_mode++;  // ������ ������� '+' ��������� � ���������� ������
                      else flyinfo_mode=1; 
                  break; }

     case 222: {  if (flyinfo_mode>1) flyinfo_mode--; // ������ ������� '-' ��������� � ����������� ������
                      else flyinfo_mode=4;
                  break; } 

     case 252: {  disp_mode=1; // ������ ������� 'menu' ������� ����
                  break; }
                  
     case 250: {  // ������ ������� EXIT
                  // ��� �������� ������� ������������� ������
                  if (flyTimerOn!=0) flyTimerOn=0;
                  else { // ��� ������� ������� ���������� ������ � �������������� ���������
                     if (keyhold==1) {
                          flyTimerOn=0; // �������� ������ ��������
                          flyCurrTimer=rmodel.MODEL_FLYTIMER; // �������� �����
                          TimerEndBeepCounter=0;
                          TimerEnd=0;
                     }
                  }  
                  break;
     } 

   }

}

void resetMenu() { //-------------------------------------------- ����� �������� ����� ����������� ����
  disp_mode=2; // ������� : 1 - ����, 2 - �������� �����
  flyinfo_mode=1; // ����� ��������� ������

  posxmenu=0;    // ������� ������� �� �����������
  numitem_cur=1; // ������ �� ������� MODEL ����

  menu_exe=0; // ���������� �������� ��� 
  menu_proc=0;

  system_calibration_part=0; // ���� ��������� ����������

  temp1=0; // ��������� ��������� ����������
  temp2=0;
  temp3=0;
  temp4=0;
  temp5=0;
  
  fmode_source=1;
  fmode_to=2;  
}

// ----------------------------------------------- ��������� �������� ������ �� ����� ���������� ������

// ������ ������������ ��������� � ��������
void PrintMessage() {

  LCD_setxy(0,1); LCD_wrsf(messStr1,1); // �������� ���������
  
  LCD_setxy(0,3); LCD_wrsf(messStr2,0); // �������� ������ 2
  LCD_setxy(0,4); LCD_wrsf(messStr3,0); // �������� ������ 3
  LCD_setxy(0,5); LCD_wrsf(messStr4,0); // �������� ������ 4
  LCD_setxy(0,6); LCD_wrsf(messStr5,0); // �������� ������ 5
  
  
  // ��������� ������� ������� ��������� �� ����
  messRetCode=get_mnu_keys();   
   switch (printMess) { // ��������� �� ������� ������� � ����������� �� ���� �������

      case 1 : { // ����������, ����� �� ������� ������� EXT
                 if (messRetCode==250)  {
                   printMess=0;
                   resetKeyReader(); // ����� ����������  
                 }   
                 break;
      }
      
      case 2: { // ������ Yes/No - ����� �� ������� MENU\EXT
                 if ( (messRetCode==250) || (messRetCode=252) )  {
                   printMess=0;                   
                   resetKeyReader(); // ����� ����������  
                 }
                break;   
      }  

      case 3 : { // ����������, ����� �� ������� ������� MENU
                 if (messRetCode==252)  {
                   printMess=0;
                   resetKeyReader(); // ����� ����������  
                 }   
                 break;
      }  
   }
} 

void disp() {

  if (printMess==0) { // ����� �� ���������� ������������ ��������� ?
      // - �� �����
     switch (disp_mode) {
   
        case 1 : {  
                     if (menu_exe==1) {       // ���� ������� ����� �� ��������� - �� ��������� �� 
                       menu_proc();
                     } 
                       else { 
                         
                         disp_menu();  // ���� �� ������� - �� ������ ����
                         flyTimerOn=0; // ��������� ������                         
                       }                 
                    break; 
        }
                       
        case 2 : {  
                    flyInfo();  
                    break;  
        }
     }
  } 
    else { // - �����, �������� ���������
           PrintMessage();
    }
}    
