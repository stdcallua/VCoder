unsigned char get_mnu_keys(void); // ��������� ��������� ���� ������� ������
void CalcCurveORD(void); // ������ ����� ������
unsigned char getMixCount(unsigned char fmode); // ������� ��������� ��������
extern unsigned char mixercount;  // ����� ���������� �������� � ������
extern unsigned char mixtochan;   // ���������� ������������� �������� � ����� ������
extern unsigned char mixtochanlast;   // ���������� ������������� �������� � ��������� ������
extern unsigned char mch[8]; // ������ �� ���������� �������� ����� ��� �������������������
extern unsigned int OLD_LCH_LEN[16]; // ������ ������������� LCH ������� ����������� ������ 


extern unsigned char ppmStop; // ������� �������� ��������� PPM 

extern unsigned int keyhold;      // ������� ��������� ������� �������

unsigned int read_adc(unsigned char adc_input);

extern unsigned int UCHmid[7]; // ������� �������� ���������� UCH �������
extern unsigned int UCHmin[7]; // ����������� �������� ���������� UCH �������
extern unsigned int UCHmax[7]; // ������������ �������� ���������� UCH �������

extern eeprom unsigned int E_UCHmid[7]; // ������� �������� ���������� UCH �������
extern eeprom unsigned int E_UCHmin[7]; // ����������� �������� ���������� UCH �������
extern eeprom unsigned int E_UCHmax[7]; // ������������ �������� ���������� UCH �������

extern eeprom unsigned char E_CurModelNum; // ����� ��������� ������

extern unsigned char ClusterSize; // ������ �������� �������� ������� (16, 32, 48, 64)

extern eeprom unsigned char E_SOUND_ON; // ������� ���� ��� ���� ������� 
extern unsigned char SOUND_ON; // ������� ���� ��� ���� �������

extern eeprom unsigned char E_key_press_time; // ���������� ������ ����� �������� ������� ��������� �������
extern eeprom unsigned char E_key_repress_time; // ���������� ������ ����� �������� � ������� ������� ���� ����������
extern eeprom unsigned char E_trim_press_time; // �������� �� ������� ������ �������

extern unsigned char key_press_time; // ���������� ������ ����� �������� ������� ��������� �������
extern unsigned char key_repress_time; // ���������� ������ ����� �������� � ������� ������� ���� ����������
extern unsigned char trim_press_time; // �������� �� ������� ������ �������
extern eeprom unsigned char E_nulTrimBeep; // E_var5; ������ � ���������� �������� � ����


void resetKeyReader(); // ��������� ������ ���������� ������ � �������������� ��������� (��� ���������� �����������)

extern unsigned int UCH_VALUES[14]; // ��������� �������� UCH
extern signed  char UCH_VAL_PROC[14]; // ���������� �������� ������� UCH

extern unsigned char BLINK; // ���������� ��� ������ �������� ������ LCD

extern unsigned int CH_PPM[8]; // ������������ ��������� ��������� ��� ������ �� ����������
//extern unsigned int CAP_PPM[8]; // ������������ ������������ ������� PPM

extern unsigned int batt; // ���������� �� ������� �����������
extern eeprom unsigned int E_battMin; // ���������� ���������� ���������� �� ������� �����������
extern unsigned int battMin; // ���������� ���������� ���������� �� ������� �����������

extern flash unsigned char *messStr1; // ������ ����� ��� ������ ��������� ������������
extern flash unsigned char *messStr2; // ������ ����� ��� ������ ��������� ������������
extern flash unsigned char *messStr3; // ������ ����� ��� ������ ��������� ������������
extern flash unsigned char *messStr4; // ������ ����� ��� ������ ��������� ������������
extern flash unsigned char *messStr5; // ������ ����� ��� ������ ��������� ������������
extern unsigned char messRetCode; // ��� ���������� �������� ������ ���������

extern unsigned char printMess; // ���� ���� ��� ����� ���������� ���������

extern unsigned int FMODE_NUM; // ������� �������� �����

extern eeprom unsigned char E_eventStart; // ������� �� �������� �������� ������ ������
extern eeprom unsigned char E_eventStop;   // ������� �� �������� ������������� ������

extern unsigned char flyTimerOn; // ������� ���� ��� �������� ������ �������
extern unsigned int flyCurrTimer; // ������� �������� ��������� �������
extern unsigned char  TimerEndBeepCounter;
extern unsigned char  TimerEnd;

extern eeprom unsigned char E_beep1min; // ������� ������������� ������ ����� ������ ������ ������ �������
extern eeprom unsigned char E_beep2sec; // ������� ������������� ������ ����� ������ 2 ������� � ��������� ������

extern eeprom unsigned char PPM_capture; // ������� ��������� ������� PPM �������
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
extern unsigned int  PPM_PAUSE; // ������������ �����������
extern unsigned int LCH_LEN[16]; // ������ ������������� LCH �������
extern unsigned int CURVE_POINT[16][9][2]; // ������ ����� ������ �������� ���������� ������

extern unsigned char ModelChange; // ������� ���� ��� ������ ���� ��������

extern unsigned int     outx1, outx2, outx3, outy1, outy2, outy3, outkk; // �������

