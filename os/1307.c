#include "i2c.h"
#include "1307.h"
//#include "globals.h"

 static   uint8_t timeData [9] = { (DS1307_ADR<<1)|1,0,0,0,0,0,0,0,0};	//главное

	      
void prime () 
{
  //             (первое число  << 4) | второе число;  или можно передавать 16ричной прост
  timeData[0] = (DS1307_ADR<<1)|0;  //адресный пакет
  timeData[1] = 0;                  //адрес регистра
  timeData[2] = (4<<4)|2;           //значение секунд  смещение - первая цифра, после И - вторая
  timeData[3] = (3<<4)|1;           //значение минут
  timeData[4] = (2<<4)|0;                   //часы
  timeData[5] = 1;					//день недели 1-7
  timeData[6] = (2<<4)|0;		   //число
  timeData[7] = (1<<4)|1;		   //месяц
  timeData[8] = (2<<4)|5;		   //год
  
	};
	
	
	
	
	//****************************************************************************
	//                       Изменение времени в выбраной ячейке массива
	// *****************************************************************************
	
	
void changeTimeData (uint8_t selest, uint8_t numb) {
	
		
			switch (selest){  
//------------------- секунды---------------- 
				case 0: {   timeData[2] = numb; }
//------------------- минуты----------------  
				case 1: {	timeData[3] = numb;	}
//------------------- часы------------------- 
				case 2: {timeData[4] = numb; 	}
//------------------- дни неделди------------ 
				case 3: {timeData[5] = numb; }
//------------------- число-------------------
				case 4: {timeData[6] = numb; }
//------------------- месяц-------------------
				case 5: {timeData[7] = numb; }
//------------------- год------------------- 
				case 6: {timeData[8] = numb; }
//------------------- else ------------------- 
		     default: {};						 
					
				
			  }
			  
		 
	
	
}; 	



//****************************************************************************
//                        Редактирование время в ячейке 
// *****************************************************************************

void changeClockSelest (uint8_t selestNumber, uint8_t timeToChange) {
	
	//надо сделать свич, по selestNumber который отправляет даут
	//нужно сделать маску для старшего байта/младшего байта (она уже есть?)
	//добавить глобальные маски дефанй
	//в редакторе времени, вызывается дата, почему так происходит, дело в прерываниях, или отсутствия закрытия
	//сброс выделения вроде помог
	
	
	
timeRead();

assCLI;
switch (selestNumber){
	
	case 0: { timeData[4] = (timeToChange<<4)| (timeData[4]& Jnibble);  break; }      //значение секунд  смещение - первая цифра, после И - втораяreturn 1;  } timeData[2] = (timeData[2]& 0xf0) |timeToChange;
	case 1: {   timeData[4] = (timeData[4]& Enibble) |timeToChange;    break;  break;  }
	case 2: {timeData[3] = (timeToChange<<4)| (timeData[3]& Jnibble);  break; }   //десять сек
	case 3: {timeData[3] = (timeData[3]& Enibble) |timeToChange;    break; }  //минуты
	case 4: { timeData[2] = (timeToChange<<4)| (timeData[2]& Jnibble);  break; }  //десять сек
	case 5: { timeData[2] = (timeData[2]& Enibble) |timeToChange;    break;  }  //cек
	
	
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
	//                        Редактирование даты в ячейке и день
	// *****************************************************************************
	
	//проблема сбивания года при чтении/записии не решена, как я думал
	//или проблема не в нем, а где-то еще, в году
	//возможно в тви-обработке,  надо попробовать поднять свой старый фаил рабоыт с тви
	
	void changedataSelest (uint8_t selestNumber, uint8_t dataToChange) {
		

		timeRead();
		
		assCLI;
		switch (selestNumber){
			
			case 0: { timeData[6] = (dataToChange<<4)| (timeData[6]& Jnibble);  break; }  //десятки дней
			case 1: {   timeData[6] = (timeData[6]& Enibble) |dataToChange;    break;  break;  }  // день
			case 2: {timeData[7] = (dataToChange<<4)| (timeData[7]& Jnibble);  break; }   //десятки месяцов 
			case 3: {timeData[7] = (timeData[7]& Enibble) |dataToChange;    break; }  //месяц
			case 4: { timeData[8] = (dataToChange<<4)| (timeData[8]& Jnibble);  break; }  //десятки годов
			case 5: { timeData[8] = (timeData[8]& Enibble) |dataToChange;    break;  }  //год
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
//                        получение времени по запросу
// *****************************************************************************

	
	uint8_t getTimeData (uint8_t selest) {
		
		
		switch (selest){
			//------------------- секунды---------------- 
			case 0: { return  timeData[2];  }
			//------------------- минуты----------------  
			case 1: {	return timeData[3];	}
			//------------------- часы------------------- 
			case 2: {  return timeData[4]; 	}
			//------------------- дни неделди------------ 
			case 3: {return timeData[5] ; }
			//------------------- число-------------------
			case 4: {return timeData[6] ; }
			//------------------- месяц-------------------
			case 5: {return timeData[7] ; }
			//------------------- год------------------- 
			case 6: {return timeData[8]; }
			//------------------- else ------------------- 
			default: return 0x00;
			
			
		}
		
		
		
		
	};
	
	
	
	//****************************************************************************
	//                       преобразование систем 2 - 10 (частичное) 
	// *****************************************************************************
	
	
		uint8_t converterTenSix (uint8_t convert) {
			
			
			switch (convert){  //когда сделал, но не понял зачем
				
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
	//                       функции взаимодействия с СПИ
	// *****************************************************************************
	
void timeWrite ( ) 
{
	//nowKey=0;
	
	
	
 timeData[0] = (DS1307_ADR<<1)|0;  //адресный пакет
 timeData[1] = 0;                  //адрес регистра
 timeData[2] = (4<<4)|2;           //значение секунд  смещение - первая цифра, после И - вторая
 timeData[3] = (3<<4)|1;           //значение минут
 timeData[4] = (2<<4)|0;                   //часы
 timeData[5] = 1;					//день недели 1-7
 timeData[6] = (2<<4)|0;		   //число
 timeData[7] = (1<<4)|1;		   //месяц
 timeData[8] = (2<<4)|5;		   //год

	  TWI_SendData(timeData, 9);
	 
	
	};
	
void timeRead () 
{
 timeData[0] = (DS1307_ADR<<1)|1;
 TWI_SendData(timeData, 8);    
  asm ("nop");

      /*переписываем данные буфера 
      драйвера в свой буфер*/ 
    TWI_GetData(timeData,8);    //в байты buf[2]..buf[8] запишется принятое сообщение пропуская адресные байты
  asm ("nop");

 timeData[0] = (DS1307_ADR<<1)|0;
  TWI_SendData(timeData, 2); 
    asm ("nop");
	};
	
	
	
	
	//и2ц	 
/*	


 uint8_t buf [9] = { (DS1307_ADR<<1)|1,0,0,0,0};
	TWI_SendData(Test,4);
	TWI_SendData(Test,2);
	TWI_GetData(buf, 5);

TWI_SendData(Test,1);
TWI_GetData(buf, 5);

  buf[0] = (DS1307_ADR<<1)|0;  //адресный пакет
  buf[1] = 0;                  //адрес регистра
  buf[2] = (4<<4)|2;           //значение секунд  смещение - первая цифра, после И - вторая
  buf[3] = (3<<4)|1;           //значение минут
  buf[4] = (2<<4)|0;                   //часы
  buf[5] = 1;					//день недели 1-7
  buf[6] = (2<<4)|0;		   //число
  buf[7] = (1<<4)|1;		   //месяц
  buf[8] = (3<<4)|3;		   //год
  
       uint8_t sec  = buf[1];
       uint8_t  min  = buf[2];
       uint8_t  hour = buf[3];
  


TWI_SendData(buf,9);


       //устанавливаем указатель DS1307  а нулевой адрес
       н
      buf[0] = (DS1307_ADR<<1)|0; //адресный пакет
      buf[1] = 0x00;                 //адрес регистра   

      TWI_SendData(buf, 2);
   
      //считываем время с DS1307
      buf[0] = (DS1307_ADR<<1)|1;
      TWI_SendData(buf, 8);
      
      //переписываем данные буфера драйвера в свой буфер
      
      TWI_GetData(buf, 8);
	  
	  
	  
        */
      
	  /*
	       uint8_t sec  = buf[1];
     uint8_t  min  = buf[2];
     uint8_t  hour = buf[3];


  buf[0] = (DS1307_ADR<<1)|0;  //адресный пакет
  buf[1] = 0;                  //адрес регистра
  buf[2] = (4<<4)|2;           //значение секунд  смещение - первая цифра, после И - вторая
  buf[3] = (3<<4)|1;           //значение минут
  buf[4] = (2<<4)|0;                   //часы
  buf[5] = 1;					//день недели 1-7
  buf[6] = (2<<4)|0;		   //число
  buf[7] = (1<<4)|1;		   //месяц
  buf[8] = (3<<4)|3;		   //год
  
   устанавливаем указатель DS1307 
       на нулевой адрес*/
     // buf[0] = (DS1307_ADR<<1)|0; //адресный пакет
      //buf[1] = 0x00;                 //адрес регистра   

     // TWI_SendData(buf, 2);
   
      /*считываем время с DS1307*/
      //buf[0] = (DS1307_ADR<<1)|1;
      //TWI_SendData(buf, 8);
      
      /*переписываем данные буфера 
      драйвера в свой буфер*/
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
	  