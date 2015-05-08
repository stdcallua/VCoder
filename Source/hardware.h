// -------------------------------------------------------------------------------------------
//                                                        ПРОГРАММНО - АППАРАТНАЯ КОНФИГУРАЦИЯ
// -------------------------------------------------------------------------------------------
//назначение кнопок навигации  
#define KEY_UP    PINB.4
#define KEY_DOWN  PINB.3          
#define KEY_LEFT  PINB.6
#define KEY_RIGHT PINB.5
#define KEY_EXIT  PINB.2
#define KEY_MENU  PINB.1

// назначение кнопок триммеров
#define ruddTrDN   PIND.7   // ruddTr - триммер руля направления    
#define ruddTrUP   PIND.6   //      
#define throTrDN   PIND.5    // throTr - триммер тяги   
#define throTrUP   PIND.4    //      
#define elevTrDN   PIND.3    // elev - триммер руля высоты  
#define elevTrUP   PIND.2    //    
#define aileTrDN   PIND.1    // aile - триммер элеронов  
#define aileTrUP   PIND.0    //      

// Выключатели
#define SW_Id2      PINE.6     // переключатель режимов полета
#define SW_Id1      (PING & 8)   
#define SW_Gear     PINE.4     // Выключатель GEAR 
#define SW_Trainer  PINE.5     // Выключатель Trainer
#define SW_ThroCut  PINE.0     // выключатель throCut 
#define SW_AileDR   PINE.1     // двойные расходы элеронов
#define SW_ElevDR   PINE.2     // двойные расходы руля высоты
#define SW_RuddDR   (PING & 1) // двойные расходы руля направления

// динамик
#define Buzzer      PORTE.3    // бит динамика

// подсветка
#define Light       PORTB.7    // бит подсветки
 
#define ADC_VREF_TYPE 0x40 // Параметр ADC преобразователя