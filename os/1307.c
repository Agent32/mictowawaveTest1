#include "i2c.h"
#include "1307.h"
//#include "globals.h"

 static   uint8_t timeData [9] = { (DS1307_ADR<<1)|1,0,0,0,0,0,0,0,0};	//�������

	      
void prime () 
{
  //             (������ �����  << 4) | ������ �����;  ��� ����� ���������� 16������ �����
  timeData[0] = (DS1307_ADR<<1)|0;  //�������� �����
  timeData[1] = 0;                  //����� ��������
  timeData[2] = (4<<4)|2;           //�������� ������  �������� - ������ �����, ����� � - ������
  timeData[3] = (3<<4)|1;           //�������� �����
  timeData[4] = (2<<4)|0;                   //����
  timeData[5] = 1;					//���� ������ 1-7
  timeData[6] = (2<<4)|0;		   //�����
  timeData[7] = (1<<4)|1;		   //�����
  timeData[8] = (2<<4)|5;		   //���
  
	};
	
	
	
	
	//****************************************************************************
	//                       ��������� ������� � �������� ������ �������
	// *****************************************************************************
	
	
void changeTimeData (uint8_t selest, uint8_t numb) {
	
		
			switch (selest){  
//------------------- �������---------------- 
				case 0: {   timeData[2] = numb; }
//------------------- ������----------------  
				case 1: {	timeData[3] = numb;	}
//------------------- ����------------------- 
				case 2: {timeData[4] = numb; 	}
//------------------- ��� �������------------ 
				case 3: {timeData[5] = numb; }
//------------------- �����-------------------
				case 4: {timeData[6] = numb; }
//------------------- �����-------------------
				case 5: {timeData[7] = numb; }
//------------------- ���------------------- 
				case 6: {timeData[8] = numb; }
//------------------- else ------------------- 
		     default: {};						 
					
				
			  }
			  
		 
	
	
}; 	



//****************************************************************************
//                        �������������� ����� � ������ 
// *****************************************************************************

void changeClockSelest (uint8_t selestNumber, uint8_t timeToChange) {
	
	//���� ������� ����, �� selestNumber ������� ���������� ����
	//����� ������� ����� ��� �������� �����/�������� ����� (��� ��� ����?)
	//�������� ���������� ����� ������
	//� ��������� �������, ���������� ����, ������ ��� ����������, ���� � �����������, ��� ���������� ��������
	//����� ��������� ����� �����
	
	
	
timeRead();

assCLI;
switch (selestNumber){
	
	case 0: { timeData[4] = (timeToChange<<4)| (timeData[4]& Jnibble);  break; }      //�������� ������  �������� - ������ �����, ����� � - ������return 1;  } timeData[2] = (timeData[2]& 0xf0) |timeToChange;
	case 1: {   timeData[4] = (timeData[4]& Enibble) |timeToChange;    break;  break;  }
	case 2: {timeData[3] = (timeToChange<<4)| (timeData[3]& Jnibble);  break; }   //������ ���
	case 3: {timeData[3] = (timeData[3]& Enibble) |timeToChange;    break; }  //������
	case 4: { timeData[2] = (timeToChange<<4)| (timeData[2]& Jnibble);  break; }  //������ ���
	case 5: { timeData[2] = (timeData[2]& Enibble) |timeToChange;    break;  }  //c��
	
	
	default: {};
	
	
}


assNOP;

timeData[0] = (DS1307_ADR<<1)|0;
TWI_SendData(timeData, 5);

assNOP;
timeData[0] = (DS1307_ADR<<1)|0;
TWI_SendData(timeData, 2);
assNOP;

assSEI;
		
		
	};
	
	
	
	//****************************************************************************
	//                        �������������� ���� � ������ � ����
	// *****************************************************************************
	
	//�������� �������� ���� ��� ������/������� �� ������, ��� � �����
	//��� �������� �� � ���, � ���-�� ���, � ����
	//�������� � ���-���������,  ���� ����������� ������� ���� ������ ���� ������ � ���
	
	void changedataSelest (uint8_t selestNumber, uint8_t dataToChange) {
		

		timeRead();
		
		assCLI;
		switch (selestNumber){
			
			case 0: { timeData[6] = (dataToChange<<4)| (timeData[6]& Jnibble);  break; }  //������� ����
			case 1: {   timeData[6] = (timeData[6]& Enibble) |dataToChange;    break;  break;  }  // ����
			case 2: {timeData[7] = (dataToChange<<4)| (timeData[7]& Jnibble);  break; }   //������� ������� 
			case 3: {timeData[7] = (timeData[7]& Enibble) |dataToChange;    break; }  //�����
			case 4: { timeData[8] = (dataToChange<<4)| (timeData[8]& Jnibble);  break; }  //������� �����
			case 5: { timeData[8] = (timeData[8]& Enibble) |dataToChange;    break;  }  //���
			case 6:  { timeData[5] = dataToChange;    break;  }
			
			default: {};
			
			
		}
		
		
		
		assNOP;
		
		timeData[0] = (DS1307_ADR<<1)|0;
		TWI_SendData(timeData, 9);
		
		
		
		assNOP;
		timeData[0] = (DS1307_ADR<<1)|0;
		timeData[1] = 0x00;
		TWI_SendData(timeData, 2);
		assNOP;
		
		assSEI;
		
		
		
		
	};
	


//****************************************************************************
//                        ��������� ������� �� �������
// *****************************************************************************

	
	uint8_t getTimeData (uint8_t selest) {
		
		
		switch (selest){
			//------------------- �������---------------- 
			case 0: { return  timeData[2];  }
			//------------------- ������----------------  
			case 1: {	return timeData[3];	}
			//------------------- ����------------------- 
			case 2: {  return timeData[4]; 	}
			//------------------- ��� �������------------ 
			case 3: {return timeData[5] ; }
			//------------------- �����-------------------
			case 4: {return timeData[6] ; }
			//------------------- �����-------------------
			case 5: {return timeData[7] ; }
			//------------------- ���------------------- 
			case 6: {return timeData[8]; }
			//------------------- else ------------------- 
			default: return 0x00;
			
			
		}
		
		
		
		
	};
	
	
	
	//****************************************************************************
	//                       �������������� ������ 2 - 10 (���������) 
	// *****************************************************************************
	
	
		uint8_t converterTenSix (uint8_t convert) {
			
			
			switch (convert){  //����� ������, �� �� ����� �����
				
				case 0x10: {return 1;  }
				case 0x20: {return 2; }	
				case 0x30: {return 3; }
				case 0x40: {return 4; }
				case 0x50: {return 5; }
				case 0x60: {return 6; }
				case 0x70: {return 7; }
				case 0x80: {return 8; }
				case 0x90: {return 9; }
					
				default: return 0x00;
				
				
			}
			
			
			
			
		};  

	
	
	
	//****************************************************************************
	//                       ������� �������������� � ���
	// *****************************************************************************
	
void timeWrite ( ) 
{
	//nowKey=0;
	
	
	
 timeData[0] = (DS1307_ADR<<1)|0;  //�������� �����
 timeData[1] = 0;                  //����� ��������
 timeData[2] = (4<<4)|2;           //�������� ������  �������� - ������ �����, ����� � - ������
 timeData[3] = (3<<4)|1;           //�������� �����
 timeData[4] = (2<<4)|0;                   //����
 timeData[5] = 1;					//���� ������ 1-7
 timeData[6] = (2<<4)|0;		   //�����
 timeData[7] = (1<<4)|1;		   //�����
 timeData[8] = (2<<4)|5;		   //���

	  TWI_SendData(timeData, 9);
	 
	
	};
	
void timeRead () 
{
 timeData[0] = (DS1307_ADR<<1)|1;
 TWI_SendData(timeData, 8);    
  asm ("nop");

      /*������������ ������ ������ 
      �������� � ���� �����*/ 
    TWI_GetData(timeData,8);    //� ����� buf[2]..buf[8] ��������� �������� ��������� ��������� �������� �����
  asm ("nop");

 timeData[0] = (DS1307_ADR<<1)|0;
  TWI_SendData(timeData, 2); 
    asm ("nop");
	};
	
	
	
	
	//�2�	 
/*	


 uint8_t buf [9] = { (DS1307_ADR<<1)|1,0,0,0,0};
	TWI_SendData(Test,4);
	TWI_SendData(Test,2);
	TWI_GetData(buf, 5);

TWI_SendData(Test,1);
TWI_GetData(buf, 5);

  buf[0] = (DS1307_ADR<<1)|0;  //�������� �����
  buf[1] = 0;                  //����� ��������
  buf[2] = (4<<4)|2;           //�������� ������  �������� - ������ �����, ����� � - ������
  buf[3] = (3<<4)|1;           //�������� �����
  buf[4] = (2<<4)|0;                   //����
  buf[5] = 1;					//���� ������ 1-7
  buf[6] = (2<<4)|0;		   //�����
  buf[7] = (1<<4)|1;		   //�����
  buf[8] = (3<<4)|3;		   //���
  
       uint8_t sec  = buf[1];
       uint8_t  min  = buf[2];
       uint8_t  hour = buf[3];
  


TWI_SendData(buf,9);


       //������������� ��������� DS1307  � ������� �����
       �
      buf[0] = (DS1307_ADR<<1)|0; //�������� �����
      buf[1] = 0x00;                 //����� ��������   

      TWI_SendData(buf, 2);
   
      //��������� ����� � DS1307
      buf[0] = (DS1307_ADR<<1)|1;
      TWI_SendData(buf, 8);
      
      //������������ ������ ������ �������� � ���� �����
      
      TWI_GetData(buf, 8);
	  
	  
	  
        */
      
	  /*
	       uint8_t sec  = buf[1];
     uint8_t  min  = buf[2];
     uint8_t  hour = buf[3];


  buf[0] = (DS1307_ADR<<1)|0;  //�������� �����
  buf[1] = 0;                  //����� ��������
  buf[2] = (4<<4)|2;           //�������� ������  �������� - ������ �����, ����� � - ������
  buf[3] = (3<<4)|1;           //�������� �����
  buf[4] = (2<<4)|0;                   //����
  buf[5] = 1;					//���� ������ 1-7
  buf[6] = (2<<4)|0;		   //�����
  buf[7] = (1<<4)|1;		   //�����
  buf[8] = (3<<4)|3;		   //���
  
   ������������� ��������� DS1307 
       �� ������� �����*/
     // buf[0] = (DS1307_ADR<<1)|0; //�������� �����
      //buf[1] = 0x00;                 //����� ��������   

     // TWI_SendData(buf, 2);
   
      /*��������� ����� � DS1307*/
      //buf[0] = (DS1307_ADR<<1)|1;
      //TWI_SendData(buf, 8);
      
      /*������������ ������ ������ 
      �������� � ���� �����*/
      //TWI_GetData(buf, 8);
      

	/*  
	  struct timerStruct {
		  uint8_t adress;
		  uint8_t adresReg;
		  uint8_t sec;
		  uint8_t min;
		  uint8_t hours;
		  uint8_t dayOfWeek;
		  uint8_t day;
		  uint8_t month;
		  uint8_t year;
		  
		  	timerData.adress= (DS1307_ADR<<1)|0;
		  	timerData.adresReg = 0;
		  } timerData ;

*/
	  