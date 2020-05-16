#include "sysClock.h"

//у меня есть время начала, время конца, текущее время, и заданое время таймера.
//можно сделать простым вычитанием конечного из текущего. Но вопрос в конечных значениях. Если на часах уде 23.30 и зададут 2 часа, 
//нужно реализовывать функцию перехода суток. Можно сделать каким-то костылем, как всегда, чтоб высчитывалось сколько до конца суток, а потом начинался новый таймер с оставшимся временем


 struct nible {
	 uint8_t  hourH: 4;
    uint8_t hourL: 4;
	uint8_t  minH: 4;
	uint8_t  MinLow: 4;

	 } test = {0};
		 
		uint8_t menupunkt=0;
 uint8_t tempForTimer=0;	
 	 uint8_t tempForTimer2=0;	 
 uint8_t hourTemp=0;
  uint8_t minTemp=0;
  	 uint32_t secFrom1307=0;	
	    uint32_t secFromTimeEnd=0;	  
		 uint32_t Temp32bit=0;	
		 
		  uint32_t test1;//, test2;
		uint8_t test3 [3]={0,0,0};   //static volatile
	   
	     uint8_t StartTime[3]={0,0,0};
	   uint8_t endTime[3]={0,0,0};  //2-сек 1-мин 0-час
		   uint8_t endDate=0;  //если превышение суток, сюда записываются настоящее число, и ожидается пока оно не перестанет быть равным
		   uint8_t endNewDay[3]={0,0,0};//массив для превышения суток
			   
		    uint8_t nowTime[3]={0,0,0};  //использовался для старого способа общета?
				
				uint8_t Timer[3]={0,0,0};  //переменная в которой содержиться введеное пользователем число - длительность нагрева
					//uint8_t TimerForTrans[3]={0,0,0};


// нужно чтоб тик зависил от 1307, но при этом отщитывал не 1 единицу, а считывал сколько прошло с прошлого тика.
// 
// если я работаю с вычитание и прочим, прийдется время переводить в десятичные 
//можно сделать две функции перевод туда и сюда. Соответственно можно сделать конвертер туда-сюда
//ИЛИ вести все в ШЕСНАДЦЕТОЙ?


//первое действие - получение шестнадцетого числа, в ТИМЕР(1)    ну допустим скопировали. Как перекатится в следущее меню? 
///мне в голову приходят пока джва варианта: 1 ждать, и после определенного времени без нажатий, переходить. Сложно сделать, и не очень удобно.
//Я все-равно буду убирать десятки часов можно в освободившиеся 2 символа засунуть ссылку на переход ( херово выглядит, но удобнее таймера)

//попробую сл

void ReversTimerFirsMenu ()  //функция запускающаяся после выбора "хеат" в меню
{
	//тут десятичные, поэтому нужно делать преобразования.
	//как отметить их на дисплее?
	//сумировать?
	//если сдвигать их, то что будет? умножение же 
	
	
	//я не могу вызывать функцию через стандартную функцию, ибо она прошита в фшлеше, и не является переменной.
	//либо добавлять костыли и дополнительные ифы в вызове цепочек
	//я могу создать ОТДЕЛЬНЫЙ пункт меню глубоко в меню, без предков и прочего, чисто для перехода в него. 3
		//с указателем и невидимой строчкой меню не получилось. Сделаю со свитчем.
	//теперь нужно сделать конвертер	
	
	
if (!biteCode.bFunctEnter){ selestChar=0; menupunkt=0;  timeToSend=0; endTime[0]=0; endTime[1]=0; endTime[2]=0; Timer[0]=0; Timer[1]=0; Timer[2]=0;  biteCode.bFunctEnter=TRUE;}
	
	//  timeData[2] = (4<<4)|2;           //значение секунд  смещение - первая цифра, после И - вторая
	//  timeData[3] = (3<<4)|1;           //значение минут
	//  timeData[4] = (2<<4)|0;                   //часы

	
	switch (menupunkt){
		//свитч меняет повтор функции. После ввода нужного значения идет переключение свича на 1
		case 0 : {     
			
//-----------------------то, что будет отрисовываться, до тех пор, пока пользователь не нажмет "ок" 
			dot=13;
			dataDisp[5]= 'k';       //(Timer[2]& Jnibble);
			dataDisp[4]= 'o';

			dataDisp[3]=(converterTenSix(Timer[2] & Enibble));
			dataDisp[2]=(Timer[1] & Jnibble);

			dataDisp[1]=(converterTenSix(Timer[1] & Enibble));
			dataDisp[0]= (Timer[0] & Jnibble);
			
		

			//костыль инициализации, для объявления первой цифры

			//timeToSend=dataDisp[selestChar];


			//-----------------------------свитч для работы с клавой, в этом стороннем подменю------------------------------------------
			switch (nowKey){
				

				case 0 : {break;}
				case 1<<KEY_LEFT: { timeToSend++;  break; }  //dataDisp[selestChar]= timeToSend;
				
				case 1<<KEY_RIGHT: {   selestChar++;
					if (selestChar>4 )	{selestChar=0;}	 //если случилось привышение возможных выбранных циферок в дисплее
					if (selestChar<4)	{timeToSend=dataDisp[selestChar];}	 //работать только с цифрами таймера
				break; }
				
				case 1<<KEY_OK: {   if (selestChar<4)	{changeTimer(selestChar,timeToSend);}
				if (selestChar==4) {
					
					//timeCalc ();
					
					
				   menupunkt=1; //это завернешие повторения функции ввода времени работы, после нажатия "ок"
				   
				   
					//расчет тайменда
					//есть ли сутки

				
					
				}   
			break; }

			default: return;
			//default: return 0x00;
		}







		//-----------------------------   ------------------------------------------

	

		//-----------------------
		if (selestChar<4)	{dataDisp[selestChar]= timeToSend;}


		if (takt)
		{
			dataDisp[selestChar]= " ";
			if (selestChar==4)
			{dataDisp[5]= " ";
			}
		}

			
			break;}
			
			
		case 1: {    //если таймер[] уже ввели вызывается другое меню
			
			
			/*	dot=10;   //
			dataDisp[5]=(endTime[2] & Jnibble);
			dataDisp[4]=(converterTenSix(endTime[2]& Enibble));
			
			dataDisp[3]=(endTime[1] & Jnibble);
			dataDisp[2]=(converterTenSix(endTime[1]& Enibble));
			
			dataDisp[1]=(endTime[0] & Jnibble); 
			dataDisp[0]=(converterTenSix(endTime[0]& Enibble));  */
			
		 displayNumb (test3);  //отрисовываем на постоянной основе для обновления
	
				

TimerStart ();
			
				 break; }  //dataDisp[selestChar]= timeToSend;   
		
		case 2: {  		break; }
		
		case 3: {  	break; }

	default: return;
	//default: return 0x00;
}

		nowKey=0;
		asm("sei");
		
}


uint8_t SixToTen ( uint8_t sixteen, uint8_t ten)
{
	//нужно разделить байт на два нибла, после чего тупо сложить младший нибл как обычные, а старший пририсовав ноль, как десятки
	
	//счет старщего нибла будет от от 0 до 6, Ибо это часы, больше 6 быть просто не может, соответственно, пока что, мне конвертер для полного перевода не нужен.
	ten=(sixteen  & Enibble);
	
	for (uint8_t i=0; i<converterTenSix(sixteen & Enibble); i++)
	{
		ten=ten+10;
	}
	
	
	
	
	ten=ten+ ( sixteen & Jnibble);
	
	
	
	
	//таблица. Возможно можно как-то переместить биты вниз?
	

return ten; 
}

//перевод из таймера 16 в тайм нау 10
//или сделать отдельную функцию?
void changeTimer (uint8_t selestNumber, uint8_t timeToChange) {
	

	

	switch (selestNumber){
		
		case 0: { Timer[0] = (Timer[0]& Enibble) |timeToChange;    break; }      //час  Timer[0] = (timeToChange<<4)| (Timer[0]& Jnibble);  break; 
		case 1: {   Timer[1] = (timeToChange<<4)| (Timer[1]& Jnibble);  break;     }  // Timer[0] = (Timer[0]& Enibble) |timeToChange;    break;   десять минут
		case 2: {Timer[1] = (Timer[1]& Enibble) |timeToChange;    break;   } //   Timer[1] = (timeToChange<<4)| (Timer[1]& Jnibble);  break; //минуты?
		case 3: { Timer[2] = (timeToChange<<4)| (Timer[2]& Jnibble);  break; }    //  десятки секунд
		//case 4: { Timer[2] = (timeToChange<<4)| (Timer[2]& Jnibble);  break; } 
		//case 5: { Timer[2] = (Timer[2]& Enibble) |timeToChange;    break;  } 
		
		
		default: {};
		
		
	}


};



//------------------------------------------------------------------------------------------------------------------------

void TimerStart ()  //главная функция отщета меню1, где происходит расчет до конца нагрева, и переключение в случае ошибок или завершения
{
	//24 часа - таймстарт timeData[6]
	
/*	if ( endDate )
	{
		
		
		if (endDate==timeData[6])
		{
			//времядоконца = 24часа - 1307 + времяПослеПревышения	
			
		} 
		else { //времядоконца = времяПослеПревышения - 1307 } 
		
	
		
	} 
		}
	else
	{
		//времядоконца =ендтайм - 1307 
		//секунды
		
		//нужно реализовать вычитание в столбик 
		//перевод в секунды
		//буду делать первым способом, отдельной функцией с указателями
		//сейчас если секунды вычитаемы ебольше - неоткуда вычитать
		
		//tempForTimer= SixteenToTenDenJ (endTime[2]) - SixteenToTenDenJ (timeData[2]) ;
	//if (tempForTimer<0)
	//	{ tempForTimer=0;
		//}
	//	nowTime [2]= nowTime[2]& Enibble;
		
	//	nowTime[2] = ((TenSixJ (nowTime[2]))<<4)|tempForTimer;

//SecTransform (&endTime, &secFromTimeEnd);	

} */



//SecTransform (endTime, &secFromTimeEnd);
test1= 85300;
//test2= 82299;

	// nowTime[2]=timeData[2];
	// nowTime[1]=timeData[3];
	// nowTime[0]=timeData[4]; //часы
	 
	// SecTransform (nowTime, &secFrom1307);
	 
	 //convertNumberToMassiv(Timer, &secFrom1307 );
	 
	// vichitanieSec(&test1, &secFrom1307, test3 );	
	 vichitanieSec(&test1, &test2, test3 );	 

	 //надо проверить версию с оптимизацией кода программой. Из функции сектранс число меняется раз в минуту.
	 // возможно переменная которую получает функция меняется как-то не так? С вызовом функции все нормально
	 //попробовать убрать все указатели.
	 //функция вызывается как положнно. попроьовал внутрь её сувать наутайм
	 
	 
	 //вычитаниеСек работает сек1-сек2=правильно
	

	 
/*	 
	

*/

//СДЕЛАЙ ФУНКЦИЮ РИСУЙ ЗАВТРА! принимает указател массив[3] и рисует их в дисплей и точку
	   
	 
	 //вывести результат сектрансформ на дисплей

//SecTransform (nowTime, &secFrom1307);




//vichitanieSec(&secFromTimeEnd, &secFrom1307, &Timer );
	
	//test2= 0; //72000 7200  1800 180    22 33  
	//test1= 85300;
	//test1= test1+1;
	
//vichitanieSec(&test1, &secFrom1307, test3 );	



//почему обновление такое редное? раз в минуту, возможно проблема при обновлении сек1307 ровно раз в минуту, как так-то?  ровно 1.01 минуту. Таймер вычитает ровно -1.01 каждый раз
//общет раз в секунду
//при вычитании секунд и обратном приобразовании дублирует минуты в секунды
//когда не использую в вычитании ПЕРВОЕ общетное число,  то нет пролеммы с дубляцией минут в секунды
//думаю дело в функции трансформ
		
		//десятки секунд
		
		//tempForTimer=0;
	//	tempForTimer= TenSixJ(endTime[2]) - TenSixJ(timeData[2])  ;
		//	if (tempForTimer<0)
	//		{ tempForTimer=0;
	//		}
//		nowTime [2]= nowTime[2]& Jnibble;
//		nowTime[2] = (tempForTimer<<4)| nowTime[2];
		
	
	
	
	
	
	
};

	//получается громоздко и сложно. Может все-таки перевод в секунды?
	//можно попробовать сделать функцию. КОТОРАЯ будет общитывать превышение. 
	
	
	
	/*
	
	uint8_t FuncForVichitanie (
	
uint8_t VichitanieStolb (uint8_t  *osnova, uint8_t  *vichitaimoe)
{

	tempForTimer=0;
	
	
	
	
	if (SixteenToTenDenJ(endTime[2])<SixteenToTenDenJ(timeData[2]))  //вычитание
	{
		if (TenSixJ(endTime[2])>0)  //если с десяток ctr можно взять 10 сек
		{ 
			tempForTimer=tempForTimer+10;
			nowTime [2] |= (TenSixJ (endTime[2]) -1);  //сработае?
			
		}
		else
		 {
			 if (SixteenToTenDenJ(endTime[1])>0)    //если с минут можно взять  60 сек
			 {
			 }
			 else
			 {
				 if (TenSixJ(endTime[1])>0)    //если с  десяток минут можно взять  10 мин
				 {
				 }
				 else
				 {
					 if (SixteenToTenDenJ(endTime[0])>0)    //если с часов  можно взять  60 мин
					 {
					 }
					 else
					 {
						 
						 if (TenSixJ(endTime[0])>0)    //если с десятков часов можно взять  10 ч
			 {
			 }
			 else
			 {
			 }
					 }
				 }
				 
				 
			 }
			 
			 
			 
			 }
			
		}
		
		
		
	

	
	
	tempForTimer= ( tempForTimer+ SixteenToTenDenJ (endTime[2])) - SixteenToTenDenJ (timeData[2]) ;  //если был перенос из старшего десятка
	
	
	
	
	nowTime [2]= nowTime[2]& Enibble;
	
	 timerMass[2] = (TenSixJ (timerMass[2])<<4)|tempForTimer;
	//ДОБАВИТЬ еще одну переменную? 
	
	//десятки секунд (uint8_t *)

	
	
	return	timerMass;

	
};
*/

//secFromTime EndsecFrom1307
void  SecTransform (uint8_t * timerMass, uint32_t * sec)  //указатель на время, которе мы переводим в секунды. И указатель на секунды для каждого массива
{
//TenSixJ - десятки  SixteenToTenDenJ - единицы

	
	//ConvertArray("banzai", 2);
	 //*sec =40000020;  - работае


	 
	
*sec=0;


	 tempForTimer=0;
	tempForTimer = TenSixJ(&timerMass[0]) ;  // for ( ;tempForTimer ; tempForTimer--) {**sec = **sec +36000;}
	while (tempForTimer)  { *sec = *sec +36000; tempForTimer--; } //десять часов
	
	//tempForTimer=0;		
	tempForTimer = SixteenToTenDenJ(&timerMass[0]) ; // for ( ;tempForTimer ; tempForTimer--) {*sec = *sec +3600;}
	while (tempForTimer)  { *sec = *sec +3600; tempForTimer--; }   //час
	
		
		 //tempForTimer=0;
		 tempForTimer = TenSixJ(&timerMass[1]) ; // for ( ;tempForTimer ; tempForTimer--) {*sec = *sec +600;}
		 while (tempForTimer)  { *sec = *sec +600; tempForTimer--; }  //десять минут
		 
		// tempForTimer=0;
		 tempForTimer = SixteenToTenDenJ(&timerMass[1]) ; // for ( ;tempForTimer ; tempForTimer--) {*sec = *sec +60;}
		  while (tempForTimer)  { *sec = *sec +60; tempForTimer--; }	//минута
		
	 
	// tempForTimer=0;
	 tempForTimer = TenSixJ(&timerMass[1]) ; // for ( ;tempForTimer ; tempForTimer--) {*sec = *sec +10;}
	 while (tempForTimer)  { *sec = *sec +10; tempForTimer--; }
	 
// tempForTimer=0;
	 tempForTimer = SixteenToTenDenJ(&timerMass[1]) ; // for ( ;tempForTimer ; tempForTimer--) {*sec = *sec +1;}
	 while (tempForTimer)  { *sec = *sec +1; tempForTimer--; }		 

	
		// 
			
		//сейчас в темпе 36000 при 2 десятках  timeData нужно отправалять, а не наутайм. что за наутайм вообще?
		//при 	 *sec =  *sec+2;  общет нормальный и обновление, дело в функии
		//сек пробовал менять ваил пробовал менять маймерМасс пробовал менять сек
		//при двойном использовании таймер изменяется только когда первая цифра и вторая одинаковы. Если брать переменную - то ровно раз в минуту
		//думаю дело в том, что обсчет одинаковый, и система лажает в одном  и том же месте.
		
	//темп = десятки часов;  ваил темп !=0 { секунды = секунды + 36000 }   TenSixJ (timerMass[0])
	//темп =  часы; ваил темп !=0 { секунды = секунды + 3600 } 	
	//темп =  десятки минут; ваил темп !=0 { секунды = секунды + 600 } 
	//темп =   минут; ваил темп !=0 { секунды = секунды + 60 } 	
	//темп =   десятки секунд; ваил темп !=0 { секунды = секунды + 10 } 	
	//темп =    секунд; ваил темп !=0 { секунды = секунды + 1 } 
		
		//потом тоже самое с действующим временем
		
	//затем вычитаем секунды
	
	//обратное преобразование:
	
	//вычитаем по 3600 по максимуму. Затем вычиатем по 60. Остаток в секунды
	
	//ваил СЕКУНДЫ>3600 {часы_темп++;  иф часы_темп>10, записываем в остаток_таймера_десяткичасов. } ПОСЛЕ выполнения вайла таймер[0] старший = часы_темп 
		
		
		//86400 - максимум секунд в сутках			uint32_t - 4 байта  в два не влезет
	
	

	
};


void  vichitanieSec (uint32_t *osnova, uint32_t *Vichitaemoe, uint8_t *resultMassiv )  //нужно получать указатель на 2 32байта и 1 массив
{
//secFrom1307

//secFromTimeEnd

//Timer
 
assCLI;

Temp32bit=*osnova- *Vichitaemoe;

 tempForTimer=0;
  tempForTimer2=0;
  while (Temp32bit>35999)  { Temp32bit = Temp32bit -36000; tempForTimer++; }
	  while (Temp32bit>3599)  { Temp32bit = Temp32bit -3600; tempForTimer2++; }
		  
		  resultMassiv[0] = (tempForTimer<<4)|tempForTimer2;
		  
		  
	 tempForTimer=0;
	 tempForTimer2=0;
	 while (Temp32bit>599)  { Temp32bit = Temp32bit -600; tempForTimer++; }
	 while (Temp32bit>59)  { Temp32bit = Temp32bit -60; tempForTimer2++; }
	 
	 resultMassiv[1] = (tempForTimer<<4)|tempForTimer2;
	 
 tempForTimer=0;
 tempForTimer2=0;
 while (Temp32bit>9)  { Temp32bit = Temp32bit -10; tempForTimer++; }
 while (Temp32bit)  { Temp32bit = Temp32bit -1; tempForTimer2++; }
 
 resultMassiv[2] = (tempForTimer<<4)|tempForTimer2;	
 
 assSEI; 


 //проблеммы с тем, что дублирует минуты в числе секунд. Почему пока не понял
 

}



//дальше устанавлюются значения ендтайма
//если значение эндтайма закатывают за сутки в ифе (иф наутаймтайм == 00.00, то ендТаймПослеСуток =  ендтайм;  ендтаймПослеСУток= 23.59.59 - ендтайм;
void timeCalc ()  //----------------------функция чисто для расчета ендтайма
{
	assCLI;
		//  timeData[2] = (4<<4)|2;           //значение секунд  смещение - первая цифра, после И - вторая
		//  timeData[3] = (3<<4)|1;           //значение минут
		//  timeData[4] = (2<<4)|0;                   //часы
		
		//таймер + время = ендтайм
		//расчет превышение суток после расчета ендтайма?  Тупым вычитанием из него 23.59.59 ?
		
		//мне нужно реализовать сложение секунд. Секунды могут быть по 9 с каждой стороны, но проблема в том, что если обе больше 8, то 16 ричная, начина
	
	
	//отказался от всего этого, оно почему-то в симуляции не работает. Не понимаю почему. 
	//подключил кварц, теперь сутки меня не волнуют
	
	//------------------------- сохраняем время начала ---------------------------- 
	StartTime[2]=timeData[2];
	StartTime[1]=timeData[3];
	StartTime[0]=timeData[4];
	
	//------------------------- секунды ---------------------------- 
	tempForTimer=0;
	tempForTimer=(SixteenToTenDenJ (&timeData[2]) ) + (SixteenToTenDenJ (&Timer[2])) + (SixteenToTenDenJ (&endTime[2]));
	endTime [2]= endTime[2]& Enibble;

	while (tempForTimer > 9) {tempForTimer=tempForTimer- 10; endTime[2]=  endTime[2] +0x10; }
		
	endTime[2] = (TenSixJ (&endTime[2])<<4)|tempForTimer;
	//------------------------- десятки секунд---------------------------- 
	
		tempForTimer=0;
		
		tempForTimer=TenSixJ(&timeData[2]) + TenSixJ(&Timer[2]) + TenSixJ(&endTime[2]);
		endTime [2]= endTime[2]& Jnibble;
		while (tempForTimer > 5) {tempForTimer=tempForTimer-6; endTime[1]++; }  
				
		endTime[2]= (tempForTimer<<4)| endTime[2];	
		
	//------------------------- минуты  ---------------------------- 	
	tempForTimer=0;
	tempForTimer=(SixteenToTenDenJ (&timeData[3]) ) + (SixteenToTenDenJ (&Timer[1])) + (SixteenToTenDenJ (&endTime[1]));
	endTime [1]= endTime[1]& Enibble;

	while (tempForTimer > 9) {tempForTimer=tempForTimer- 10; endTime[1]=  endTime[1] +0x10; }
	
	endTime[1] = (TenSixJ (&endTime[1]) <<4)|tempForTimer;
	
		//------------------------- десятки минут---------------------------- 
			tempForTimer=0;
			
			tempForTimer=TenSixJ(&timeData[3]) + TenSixJ(&Timer[1]) + TenSixJ(&endTime[1]);
			endTime [1]= endTime[1]& Jnibble;
			while (tempForTimer > 5) {tempForTimer=tempForTimer-6; endTime[0]++; }
			
			endTime[1]= (tempForTimer<<4)| endTime[1];
		//------------------------- часы  ---------------------------- 
		//часы могут быть до 4 при 2 десятк суток сделаю костыль на десятках часов
			tempForTimer=0;
			tempForTimer=(SixteenToTenDenJ (&timeData[4]) ) + (SixteenToTenDenJ (&Timer[0])) + (SixteenToTenDenJ (&endTime[0]));
			endTime [0]= endTime[0]& Enibble;
			if (SixteenToTenDenJ (&timeData[4]) < 2)
			{  while (tempForTimer > 9) {tempForTimer=tempForTimer- 10; endTime[0]=  endTime[0] +0x10; }
			} 
			else
			{ if  (tempForTimer > 4) { endDate= timeData[6]; //превышение суток
				endNewDay[2]=endTime[2];
				endNewDay[1]=endTime[1];
				endNewDay[0]= (TenSixJ (&endTime[0])) -4; }
			}
			
		
			
			
			endTime[0] = (TenSixJ (&endTime[0]) <<4)|tempForTimer;
		
		//------------------------- десятки часов---------------------------- 
				tempForTimer=0;
				
				tempForTimer=TenSixJ(&timeData[4]) + TenSixJ(&Timer[0]) + TenSixJ(&endTime[0]);
				endTime [0]= endTime[0]& Jnibble;
				if (tempForTimer >1 && SixteenToTenDenJ (&endTime[0]) > 3 ) {}
				if (tempForTimer > 2) {tempForTimer=tempForTimer-2;    }
				
				endTime[0]= (tempForTimer<<4)| endTime[0];

	assSEI;		
		
		
		//как сделать перелистывание дня? На обсчете десятков? потом вычесть из получишевшейся суммы 24 часа, остаток записать в дайЕндТайм
		
		//после вычитания переполненого числа, случается дичь.
		//после функции ++ - получится хуйня если число, например 59     endNewDay
	
	//темп = науТаймСек+таймСекн 
	//while (темп>9) {темп-9; ендтаймДесять++; }
	//eндтаймСек=темп;
	//ендтаймДемять сек
	//надо в ра и про спроситsec =0;ь. И погуглить.
	
	//я тут подумал, что лучше сделать таки 4 функции конвертера для 16то10ЛОУ 16ту10ХАЙДЖ 10то16лоу 10ту16ХАЙД
	//вроде вышло нажо проверить ограничения и потом доделать минуты часы и потом проверку на привышение суток.
	//если +1 к старшему числу идет с превышением, то обсчет, вроде, должен происходить при переходе к этому числу.
	//как будет вычитаться таймер, если идет превышение суток? Просто приплюсовывать к таймеру оставшееся время? 
	
	
};

void convertNumberToMassiv (uint8_t *Otrisovka, uint32_t *PolForConvert  )
{
	tempForTimer=0;
	tempForTimer2=0;
	
	
	while (*PolForConvert>9999)  { *PolForConvert = *PolForConvert -10000; tempForTimer++; }
	while (*PolForConvert>999)  { *PolForConvert = *PolForConvert -1000; tempForTimer2++; }
	Otrisovka[0] = (tempForTimer<<4)|tempForTimer2;
	tempForTimer=0;
	tempForTimer2=0;
	
	while (*PolForConvert>99)  { *PolForConvert = *PolForConvert -100; tempForTimer++; }
	while (*PolForConvert>9)  { *PolForConvert = *PolForConvert -10; tempForTimer2++; }
	
	Otrisovka[1] = (tempForTimer<<4)|tempForTimer2;
	tempForTimer=0;
	tempForTimer2=0;
	
	while (*PolForConvert)  { *PolForConvert = *PolForConvert -1; tempForTimer++; }
	Otrisovka[2] = (tempForTimer<<4)|tempForTimer2;
	
	
}


void displayNumb ( uint8_t * numbIn)
{
	dot=10;
	dataDisp[5]=(numbIn[2] & Jnibble);
	dataDisp[4]=(converterTenSix(numbIn[2]& Enibble));
	
	dataDisp[3]=(numbIn[1] & Jnibble);
	dataDisp[2]=(converterTenSix(numbIn[1]& Enibble));
	
	dataDisp[1]=(numbIn[0] & Jnibble);
	dataDisp[0]=(converterTenSix(numbIn[0]& Enibble));
}

uint8_t SixteenToTenDenJ (uint8_t *Sixteen)
{
	
	assCLI;
		switch (*Sixteen & Jnibble){
			
			case 0x1: { return 1;}      //час  Timer[0] = (timeToChange<<4)| (Timer[0]& Jnibble);  break;
			case 0x2: {   return 2;   }  // Timer[0] = (Timer[0]& Enibble) |timeToChange;    break;   десять минут
			case 0x3: {  return 3;  } //   Timer[1] = (timeToChange<<4)| (Timer[1]& Jnibble);  break; //минуты?
			case 0x4: {  return 4; }    //  десятки секунд
			case 0x5: {  return 5; }
			case 0x6: {  return 6; }
			case 0x7: {  return 7; }
			case 0x8: {  return 8; }
			case 0x9: {  return 9; }
			default: return 0x00;
			
			
		}
	
};


	uint8_t TenSixJ (uint8_t *Sixteen) {
		
		
		
		switch (*Sixteen & Enibble){  
			
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

