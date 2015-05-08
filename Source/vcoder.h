unsigned char get_mnu_keys(void); // Процедура получения кода нажатых клавиш
void CalcCurveORD(void); // расчет точек кривых
unsigned char getMixCount(unsigned char fmode); // подсчет количеста микшеров
extern unsigned char mixercount;  // общее количество микшеров в режиме
extern unsigned char mixtochan;   // количество обсчитываемых микшеров в одном канале
extern unsigned char mixtochanlast;   // количество обсчитываемых микшеров в последнем канале
extern unsigned char mch[8]; // память на предыдущий выданный канал при мультипликсировании
extern unsigned int OLD_LCH_LEN[16]; // массив длительностей LCH каналов предыдущего пакета 


extern unsigned char ppmStop; // признак останова генерации PPM 

extern unsigned int keyhold;      // признак удержания клавиши нажатой

unsigned int read_adc(unsigned char adc_input);

extern unsigned int UCHmid[7]; // средние значения аналоговых UCH каналов
extern unsigned int UCHmin[7]; // минимальные значения аналоговых UCH каналов
extern unsigned int UCHmax[7]; // максимальные значения аналоговых UCH каналов

extern eeprom unsigned int E_UCHmid[7]; // средние значения аналоговых UCH каналов
extern eeprom unsigned int E_UCHmin[7]; // минимальные значения аналоговых UCH каналов
extern eeprom unsigned int E_UCHmax[7]; // максимальные значения аналоговых UCH каналов

extern eeprom unsigned char E_CurModelNum; // номер выбранной модели

extern unsigned char ClusterSize; // размер кластера файловой системы (16, 32, 48, 64)

extern eeprom unsigned char E_SOUND_ON; // признак того что звук включен 
extern unsigned char SOUND_ON; // признак того что звук включен

extern eeprom unsigned char E_key_press_time; // количество циклов после которого клавиша считается нажатой
extern eeprom unsigned char E_key_repress_time; // количество циклов после которого у нажатой клавиши идет автоповтор
extern eeprom unsigned char E_trim_press_time; // задержка на нажатие кнопки тримера

extern unsigned char key_press_time; // количество циклов после которого клавиша считается нажатой
extern unsigned char key_repress_time; // количество циклов после которого у нажатой клавиши идет автоповтор
extern unsigned char trim_press_time; // задержка на нажатие кнопки тримера
extern eeprom unsigned char E_nulTrimBeep; // E_var5; сигнал о нахождении триммера в нуле


void resetKeyReader(); // процедура сброса считывания клавиш в первоначальное состояние (для ликвидации автоповтора)

extern unsigned int UCH_VALUES[14]; // Считанные значения UCH
extern signed  char UCH_VAL_PROC[14]; // Процентные значения каналов UCH

extern unsigned char BLINK; // переменная для режима мерцания модуля LCD

extern unsigned int CH_PPM[8]; // длительности канальных импульсов для выдачи на передатчик
//extern unsigned int CAP_PPM[8]; // длительности захваченного сигнала PPM

extern unsigned int batt; // напряжение на батарее передатчика
extern eeprom unsigned int E_battMin; // минимально допустимое напряжение на батарее передатчика
extern unsigned int battMin; // минимально допустимое напряжение на батарее передатчика

extern flash unsigned char *messStr1; // массив строк для печати сообщений пользователю
extern flash unsigned char *messStr2; // массив строк для печати сообщений пользователю
extern flash unsigned char *messStr3; // массив строк для печати сообщений пользователю
extern flash unsigned char *messStr4; // массив строк для печати сообщений пользователю
extern flash unsigned char *messStr5; // массив строк для печати сообщений пользователю
extern unsigned char messRetCode; // код завершения операции печати сообщений

extern unsigned char printMess; // флаг того что нужно напечатать сообщение

extern unsigned int FMODE_NUM; // текущий полетный режим

extern eeprom unsigned char E_eventStart; // событие по которому стартуем таймер модели
extern eeprom unsigned char E_eventStop;   // событие по которому останавливаем таймер

extern unsigned char flyTimerOn; // признак того что полетный таймер включен
extern unsigned int flyCurrTimer; // текущее значение полетного таймера
extern unsigned char  TimerEndBeepCounter;
extern unsigned char  TimerEnd;

extern eeprom unsigned char E_beep1min; // признак необходимости давать гудок каждую минуту работы таймера
extern eeprom unsigned char E_beep2sec; // признак необходимости давать гудки каждые 2 секунды в последнюю минуту

extern eeprom unsigned char PPM_capture; // признак включения захвата PPM сигнала
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
extern unsigned int  PPM_PAUSE; // длительность синхропаузы
extern unsigned int LCH_LEN[16]; // массив длительностей LCH каналов
extern unsigned int CURVE_POINT[16][9][2]; // массив точек кривой текущего выбранного режима

extern unsigned char ModelChange; // признак того что модель была изменена

extern unsigned int     outx1, outx2, outx3, outy1, outy2, outy3, outkk; // отладка

