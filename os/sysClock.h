//��� ����������� ������� ��������?
//http://we.easyelectronics.ru/AVR/avrasm-primer-ispolzovaniya-dispetchera-zadach-rtos-20-ustanovka-i-nastroyka.html
//���������
//� ���� � ������ ������� �������� ������ � ����������� ������������� �������������� � ������������
//� ������� �����-�� ������� ������������ �������� ����, ������� ����� ����������� � ����, � �������� ����� �� �������. 
// ����� � �������, ����������� �������, ���� - ����������� ��������� �������  � ����� �� ���� ������� ���� �������� �� ����� ����������. ��� ���������� �������� ������� ������. 
//�� � ��� ����� ��� ������� ����������� ������� ������, ������� � ����� ������ ������� ������ ��������� ��� ������� ������� �������������. 

//��� ����� ����� ���� ��.
//������
//������ ���� � ����  MQ2 MQ-2
//�������� ������� ������ ����� ����� ������, � ������ �������, ���� ����� �� ��������� �� �� ���� ��������, � �����?


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
void timeCalc ();  //������� ����� ��� ������� ��������
void changeTimer (uint8_t selestNumber, uint8_t timeToChange);

//uint8_t SixToTen (); 342