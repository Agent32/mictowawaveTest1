


/*адреса регистров*/
#define RTC_SEC_ADR     0x00
#define RTC_MIN_ADR     0x01
#define RTC_HOUR_ADR    0x02

#define DS1307_ADR  0x68   //получается  в мануале указано как 1101000 - последний бит для ANS  (?)




	
void prime ();
void changeTimeData (uint8_t selest, uint8_t numb);
void changeClockSelest (uint8_t selestNumber, uint8_t timeToChange);
void changedataSelest (uint8_t selestNumber, uint8_t dataToChange);
uint8_t getTimeData (uint8_t selest);
uint8_t converterTenSix (uint8_t convert);
void timeWrite ( ) ;
void timeRead () ;



		
