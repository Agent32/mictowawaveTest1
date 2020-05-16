
#include "i2c.h"

#define TWSR_MASK     0xfc  

volatile static uint8_t twiBuf[TWI_BUFFER_SIZE];  //�����, ������� ����� ���������
volatile static uint8_t twiState = TWI_NO_STATE;     //����� ���������
volatile static uint8_t twiMsgSize;       //���������� ���� ������� ����� ���������

/*������������ ��� ��������� �������� ������ twi ������*/
uint8_t pre[4] = {2, 8, 32, 128};

/****************************************************************************
 ������������� � ��������� ������� SCL �������
****************************************************************************/
uint8_t TWI_MasterInit(uint16_t fr)  //�������� ������ �������
{
	asm("cli");
	
  uint8_t i;       
  uint16_t twbrValue;   //��� ������������?
  
  for(i = 0; i<4; i++){  //?
    twbrValue = ((((F_CPU)/1000UL)/fr)-16)/pre[i];   //������ ������� , ���������� ��������� ������������ ��� ����� �������, ��� �� 1000�� - ��
    if ((twbrValue > 0)&& (twbrValue < 256)){		//�������� ��� �������� BitRate 255<N>0
       TWBR = (uint8_t)twbrValue;  //������ �������, ����� � ������� �����?
       TWSR = i;  //i<4 ������������ �������
       TWDR = 0xFF; // ���� = 255 - �����?
       TWCR = (1<<TWEN);   //��������� ���� ���
       return TWI_SUCCESS;
    }    //���������� � ������ ����� ��� 0 ��� �����
  }

     asm("sei");    
  return 0;  
}    






ISR(TWI_vect)
{
  assCLI;
  
  static uint8_t ptr;  // �������
  uint8_t stat = TWSR & TWSR_MASK;  //������������ ����� �� ��������, ���� �������� ������ ����
  
  switch (stat){
	  
	  //  -------------------  ������, ��������� �����    -------------------
	  
	  case TWI_START:                   // 0x08 - ��������� ����� ������� ��������
	  case TWI_REP_START:               // 0x10 - ��������� ��������� ����� ������ ��������
	  ptr = 0;   //��������� ��������

      //-------------------   ��������-------------------
	  
	  case TWI_MTX_ADR_ACK:             // 0x18 - ��� ������� �������� ����� SLA-W � �������� ������������� �� ��������
	  case TWI_MTX_DATA_ACK:            // 0x28 - ��� ������� ���� ������ � �������� ������������� �� ��������
	  if (ptr < twiMsgSize){			//�� ��� ���, ���� ���������� ����, ������� ����� ���������, ������ ��������
		  TWDR = twiBuf[ptr];                    //��������� � ������� ������ ��������� ����
		  TWCR = (1<<TWEN)|(1<<TWIE)|(1<<TWINT); //���������� ���� TWINT
		  ptr++;
	  }
	  else{
		  twiState = TWI_SUCCESS;
		  TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWSTO)|(0<<TWIE); //��������� ��������� ����, ���������� ����, ��������� ����������
	  }
	  break;
	  
	  // -------------------   �����   -------------------
	  
	  case TWI_MRX_DATA_ACK:          //0x50 - ��� ������ ���� ������ � ���������� ������������� �������� 
	  twiBuf[ptr] = TWDR;
	  ptr++;
	  
	  //-------------------  �������, �� ��� ������ -------------------
	  
	  case TWI_MRX_ADR_ACK:           //0x40 - ��� ������� �������� ����� SLA+R � �������� ������������� �� ��������
	  if (ptr < (twiMsgSize-1)){
		  TWCR = (1<<TWEN)|(1<<TWIE)|(1<<TWINT)|(1<<TWEA);  //���� ��� �� ������������� �������� ����, ��������� �������������
	  }
	  else {
		  TWCR = (1<<TWEN)|(1<<TWIE)|(1<<TWINT);            //���� ������� ������������� ����, ������������� �� ���������
	  }
	  break;
	  
	  //------------------- ������, �� �� ������� ------------------- 
	  
	  case TWI_MRX_DATA_NACK:       //0x58 - ��� ������ ���� ������ ��� �������� ������������� ��������
	  twiBuf[ptr] = TWDR;
	  twiState = TWI_SUCCESS;     //0xff
	  TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWSTO); //��������� ��������� ����
	  break;
	  
	   //-------------------������ � ������ ����-------------------
	   
	  case TWI_ARB_LOST:          //0x38 - ������ ���������� (��� ����� ���� ��� ��������� ������� ������ �������� ������ ������������ � ���� � ���-�� �� ��� � ����� ����� ����)
	  TWCR = (1<<TWEN)|(1<<TWIE)|(1<<TWINT)|(1<<TWSTA); // ���������� ���� TWINT, ��������� ��������� �����
	  break;
	  	 
	  case TWI_MTX_ADR_NACK:      // 0x20 - ��� ������� �������� ����� SLA-W ��� ������������� ��������
	  case TWI_MRX_ADR_NACK:      // 0x48 - ��� ������� �������� ����� SLA+R ��� ������������� ��������
	  case TWI_MTX_DATA_NACK:     // 0x30 - ��� ������� ���� ������ ��� ������������� �������� 
	  case TWI_BUS_ERROR:         // 0x00 - ������ ���� ��-�� ������������ ��������� ����� ��� ���� 
	  default:
	  twiState = stat;
	  TWCR = (1<<TWEN)|(0<<TWIE)|(0<<TWINT)|(0<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|(0<<TWWC); //��������� ����������
  }


    assSEI;   
}


/****************************************************************************
 �������� - �� ����� �� TWI ������. ������������ ������ ������
****************************************************************************/
static uint8_t TWI_TransceiverBusy(void)
{
	 
  return (TWCR & (1<<TWIE));      
             
}

/****************************************************************************
 ����� ������ TWI ������
****************************************************************************/
uint8_t TWI_GetState(void)
{ 
	
  while (TWI_TransceiverBusy());             
  return twiState;                        
}

/****************************************************************************
 �������� ��������� msg �� msgSize ������ �� TWI ����
****************************************************************************/

void TWI_SendData(uint8_t *msg, uint8_t msgSize)
{
	  assSEI; 
   uint8_t i;
 
   /*���� ,����� TWI ������ �����������*/
    while(TWI_TransceiverBusy());  
 
   /*����. ���������� ���� ��� ��������
   � ������ ���� ���������*/
   twiMsgSize = msgSize;
   twiBuf[0] = msg[0]; 
 
   /*���� ������ ���� ���� SLA+W, �� 
   ��������� ��������� ���� ���������*/
   if (!(msg[0] & (TRUE<<TWI_READ_BIT))){ 
      for (i = 1; i < msgSize; i++){ 
         twiBuf[i] = msg[i];
      }
   }
 
   twiState = TWI_NO_STATE ;
 
   /*��������� ���������� � ��������� ��������� ����� */
   TWCR = (1<<TWEN)|(1<<TWIE)|(1<<TWINT)|(1<<TWSTA); 
   
   
}
	
	

	


/****************************************************************************
 ���������� ���������� ������ � ����� msg � ���������� msgSize ����. 
****************************************************************************/
uint8_t TWI_GetData(uint8_t *msg, uint8_t msgSize)
{
	   assSEI; 
	 
	uint8_t i;


	while(TWI_TransceiverBusy());    //����, ����� TWI ������ �����������

	if(twiState == TWI_SUCCESS){     //���� ��������� ������� �������,
		for(i = 1; i < msgSize; i++){  //�� ������������ ��� �� ����������� ������ � ����������
			msg[i+1] = twiBuf[i];  //�������� i=1 � msg i+1, ������� ��� ��� ����, ���� ���������� ����� � ����� ������ ��� ������. � �� ��������� �������������� ������������ �������
		}
	}
	
	
	return twiState;
}

