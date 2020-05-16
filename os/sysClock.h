//как реализовать систему таймеров?
//http://we.easyelectronics.ru/AVR/avrasm-primer-ispolzovaniya-dispetchera-zadach-rtos-20-ustanovka-i-nastroyka.html
//осмотреть
//у меня в мыслях сделать аналогию класса с собственной перегруженной инициализацией и дескриптором
//в котором каким-то образом совемтестить дженерик тайм, который будет запоминатся в темп, и условное время от таймера. 
// заход в функцию, выславление времени, окей - запоминание конечного времени  и опрос до того времени пока конечное не равно настоящему. При совпадение имитация нажатия выхода. 
//но в уме нужно еще держать критические системы защиты, которые в любой момент времени должны стопарить все опасные функции микроволновки. 

//еще нужен режим вейт же.
//дверка
//датчик огня и дыма  MQ2 MQ-2
//наверное системы защиты стоит сразу делать, в первую очередь, чтоб потом не добавлять их ко всем функциям, а сразу?


void sysClockInit ();
void ReversTimerFirsMenu ();
void TimerStart ();

void displayNumb ( uint8_t * numbIn);
void convertNumberToMassiv (uint8_t *Otrisovka, uint32_t *PolForConvert  );
//uint8_t VichitanieStolb (uint8_t  *timerMass);
void  SecTransform (uint8_t * timerMass, uint32_t *sec);
void  vichitanieSec (uint32_t *osnova, uint32_t *Vichitaemoe, uint8_t *resultMassiv);
uint8_t SixteenToTenDenJ (uint8_t *Sixteen);
uint8_t TenSixJ (uint8_t *Sixteen) ;
void timeCalc ();  //функция чисто для расчета ендтайма
void changeTimer (uint8_t selestNumber, uint8_t timeToChange);

//uint8_t SixToTen (); 342