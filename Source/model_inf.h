// ���� �������� �������� ��������� � �������
#define CH_COUNT 8 // ���������� ��������� ������������ �������
#define UCH_COUNT 14 // ���������� ���������������� �������
#define MIXER_COL 40 // ������������ ���������� �������� � �������� ������

// �������� ������ ������
typedef struct {
      unsigned char active; // ������� ��������� ������ ������
        signed char point[9];   // �������� �����
                        // �� ��� ������ -100%  -75%  -50%  -25%  0  25%  50%  75%  100% 
        signed char expon; // �������� ���������� ������
} CURVE_STRUCT;

typedef struct {
unsigned       ACTIVE:1, // ������ ������� (����������)
    
          SOURSE_TYPE:1, // 0 - ������������ c UCH, 1 - ������������ c LCH
          
          PROC_SOURSE:1, // 0 - �������������, 1 - ������������ ������������

               MIX_SW:1, // 0 - ��� �����������, 1 - ����������� �������
               
               SW_INV:1, // �������� ����������� �������
               
               UCH_SW:3; // ����������� �������
} TMIX_TYPE;

typedef struct {
unsigned    CH_SOURSE:4, // ����� �������� - ������� �� SOURSE_TYPE !!
            CH_DEST:4;   // ����� ����������
} TCH_NUM;

// �������� ������ � ������� ������
typedef struct {
  TMIX_TYPE    MIX_TYPE;  // ��� ������������
  TCH_NUM        CH_NUM;  // ������ ��� ������������ 
  unsigned char MIX_VAL;  // ��� PROC_SOURSE=0 ������� ������������(-128..+127)
                          // ��� PROC_SOURSE=1 bit3210 - �������� ������������ ������������ (UCH �����)
                          //                   bit4 - ���� ������������ UCH ������
} MIXER_STRUCT;

// �������� ������ � �������� �������
typedef struct {
    unsigned char  FMODE_NAME;       // ����� ����� ��������� ������ (����� �� �����������)
    unsigned char  TRIMSTEP;         // ��������� �������� �������
    signed char    UCH_TRIMMER[7];   // �������� ���������� ������� ����������
    unsigned int   LCH_MIDLE[16];    // ����� ��������� ��������������� ��������� �������
    CURVE_STRUCT   LCH_CURVE[16];    // ������ ������� ��������� ������
    MIXER_STRUCT   MIXER[MIXER_COL]; // MIXER - ������� ��������� ������
} FMODE_STRUCT;

// �������� ������ � ���������������� ������� ���������� ������������ � ������
typedef struct {
   signed char UCH_LEFT;  // ������� ����� �������� ����������������� ������, �������� � % -128.. +127 
   signed char UCH_RIGHT; // ������� ������ �������� ����������������� ������, �������� � % -128.. +127
} UCH_STRUCT;

typedef struct {
   unsigned char FILTER_TYPE; // ��� �������, � ��������� ����� ����������� ���������:
/**                                 0 - ������ ������ � ����� ��� �������
                                    1 - ������ � ����� � ������������
                                    2 - ������������������� ������
**/
   unsigned int        VAL1; // �������� �������
/**                                  - ��� ������� 1:
                                          ������� ���� - ����� ����������� 
                                          ������� ���� - �������� � % ��� ���������� �����������
                                    - ��� ������� 2 ���� ���������� ����� ������ ������������������ (����-
                                                (������ ���������������� ���� � 1)
                                                ������������������ �������: 1 2 3 4 5 6 7 8 9 A B C D E F G
                                                  

**/
                                   
                                   //   unsigned char        VAL2; // ������ �������� �������
} TCHFILTERS;

typedef struct {   // ���������� ������
  unsigned char    LCH_COUNT; // ���������� ������������ ������� ���������� ������� - �� 1 �� 16 !!
  unsigned int    CH_EPL[16]; // ����� ������� ����� ���������� �������
  unsigned int    CH_EPR[16]; // ������ ������� ����� ���������� �������
  
  unsigned char   LCHDELDN[16]; // �������� ��� ��������� �������� ������ ��� ��������� ����
      unsigned char   LCHDELUP[16]; // �������� ��� ��������� �������� ������ ��� ��������� �����
  
  unsigned char    LCH_REV[16]; // ������� �������� ������� LCH
   
                   // ���������� ������
  unsigned char PPM_CH_COUNT; // ���������� ������� ������������ � ����� PPM (�� ����� ������� ���������� ��������)
  TCHFILTERS       FILTER[8]; // ������� ����- ��������� LCH � CH  
} TCHANNELS;

// �������� ������ � ������
typedef struct {
    unsigned char       MODEL_TYPE;       // ��� ������: 0- �������, 1 - ������, 2 - ��������
    unsigned char       MODEL_NAME[8];    // ��� ������

    unsigned int        MODEL_FLYTIMER;   // �������� ��������� ������� �� ����� ������
    unsigned int        MODEL_LIVETIMER;  // ����� ����� ������ ������

    TCHANNELS           CHANNELS;         // ��������� ���������� � ���������� ������� ������� ������
    UCH_STRUCT          UCH[UCH_COUNT];   // ���������� � ������ �� 14 ������� UCH    
    unsigned char       PPM_TO_LCH_CAP[8]; // ������ LCH ������� ��� ��� ������� PPM ������� � ����������� �������
    unsigned char       FMODE_COUNT;      // ���������� �������� �������� �������
    FMODE_STRUCT        FMODE[3];         // ���������� � �������� �������    

} MODEL_INFO_STRUCT;

MODEL_INFO_STRUCT rmodel;