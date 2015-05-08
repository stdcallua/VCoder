// -------------------------------------------------------------------------------------------
//                                                        ���������� - ���������� ������������
// -------------------------------------------------------------------------------------------
//���������� ������ ���������  
#define KEY_UP    PINB.4
#define KEY_DOWN  PINB.3          
#define KEY_LEFT  PINB.6
#define KEY_RIGHT PINB.5
#define KEY_EXIT  PINB.2
#define KEY_MENU  PINB.1

// ���������� ������ ���������
#define ruddTrDN   PIND.7   // ruddTr - ������� ���� �����������    
#define ruddTrUP   PIND.6   //      
#define throTrDN   PIND.5    // throTr - ������� ����   
#define throTrUP   PIND.4    //      
#define elevTrDN   PIND.3    // elev - ������� ���� ������  
#define elevTrUP   PIND.2    //    
#define aileTrDN   PIND.1    // aile - ������� ��������  
#define aileTrUP   PIND.0    //      

// �����������
#define SW_Id2      PINE.6     // ������������� ������� ������
#define SW_Id1      (PING & 8)   
#define SW_Gear     PINE.4     // ����������� GEAR 
#define SW_Trainer  PINE.5     // ����������� Trainer
#define SW_ThroCut  PINE.0     // ����������� throCut 
#define SW_AileDR   PINE.1     // ������� ������� ��������
#define SW_ElevDR   PINE.2     // ������� ������� ���� ������
#define SW_RuddDR   (PING & 1) // ������� ������� ���� �����������

// �������
#define Buzzer      PORTE.3    // ��� ��������

// ���������
#define Light       PORTB.7    // ��� ���������
 
#define ADC_VREF_TYPE 0x40 // �������� ADC ���������������