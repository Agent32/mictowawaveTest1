#include "sysClock.h"

//� ���� ���� ����� ������, ����� �����, ������� �����, � ������� ����� �������.
//����� ������� ������� ���������� ��������� �� ��������. �� ������ � �������� ���������. ���� �� ����� ��� 23.30 � ������� 2 ����, 
//����� ������������� ������� �������� �����. ����� ������� �����-�� ��������, ��� ������, ���� ������������� ������� �� ����� �����, � ����� ��������� ����� ������ � ���������� ��������


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
	   uint8_t endTime[3]={0,0,0};  //2-��� 1-��� 0-���
		   uint8_t endDate=0;  //���� ���������� �����, ���� ������������ ��������� �����, � ��������� ���� ��� �� ���������� ���� ������
		   uint8_t endNewDay[3]={0,0,0};//������ ��� ���������� �����
			   
		    uint8_t nowTime[3]={0,0,0};  //������������� ��� ������� ������� ������?
				
				uint8_t Timer[3]={0,0,0};  //���������� � ������� ����������� �������� ������������� ����� - ������������ �������
					//uint8_t TimerForTrans[3]={0,0,0};


// ����� ���� ��� ������� �� 1307, �� ��� ���� ��������� �� 1 �������, � �������� ������� ������ � �������� ����.
// 
// ���� � ������� � ��������� � ������, ��������� ����� ���������� � ���������� 
//����� ������� ��� ������� ������� ���� � ����. �������������� ����� ������� ��������� ����-����
//��� ����� ��� � �����������?


//������ �������� - ��������� ������������� �����, � �����(1)    �� �������� �����������. ��� ����������� � �������� ����? 
///��� � ������ �������� ���� ���� ��������: 1 �����, � ����� ������������� ������� ��� �������, ����������. ������ �������, � �� ����� ������.
//� ���-����� ���� ������� ������� ����� ����� � �������������� 2 ������� �������� ������ �� ������� ( ������ ��������, �� ������� �������)

//�������� ��

void ReversTimerFirsMenu ()  //������� ������������� ����� ������ "����" � ����
{
	//��� ����������, ������� ����� ������ ��������������.
	//��� �������� �� �� �������?
	//����������?
	//���� �������� ��, �� ��� �����? ��������� �� 
	
	
	//� �� ���� �������� ������� ����� ����������� �������, ��� ��� ������� � ������, � �� �������� ����������.
	//���� ��������� ������� � �������������� ��� � ������ �������
	//� ���� ������� ��������� ����� ���� ������� � ����, ��� ������� � �������, ����� ��� �������� � ����. 3
		//� ���������� � ��������� �������� ���� �� ����������. ������ �� �������.
	//������ ����� ������� ���������	
	
	
if (!biteCode.bFunctEnter){ selestChar=0; menupunkt=0;  timeToSend=0; endTime[0]=0; endTime[1]=0; endTime[2]=0; Timer[0]=0; Timer[1]=0; Timer[2]=0;  biteCode.bFunctEnter=TRUE;}
	
	//  timeData[2] = (4<<4)|2;           //�������� ������  �������� - ������ �����, ����� � - ������
	//  timeData[3] = (3<<4)|1;           //�������� �����
	//  timeData[4] = (2<<4)|0;                   //����

	
	switch (menupunkt){
		//����� ������ ������ �������. ����� ����� ������� �������� ���� ������������ ����� �� 1
		case 0 : {     
			
//-----------------------��, ��� ����� ��������������, �� ��� ���, ���� ������������ �� ������ "��" 
			dot=13;
			dataDisp[5]= 'k';       //(Timer[2]& Jnibble);
			dataDisp[4]= 'o';

			dataDisp[3]=(converterTenSix(Timer[2] & Enibble));
			dataDisp[2]=(Timer[1] & Jnibble);

			dataDisp[1]=(converterTenSix(Timer[1] & Enibble));
			dataDisp[0]= (Timer[0] & Jnibble);
			
		

			//������� �������������, ��� ���������� ������ �����

			//timeToSend=dataDisp[selestChar];


			//-----------------------------����� ��� ������ � ������, � ���� ��������� �������------------------------------------------
			switch (nowKey){
				

				case 0 : {break;}
				case 1<<KEY_LEFT: { timeToSend++;  break; }  //dataDisp[selestChar]= timeToSend;
				
				case 1<<KEY_RIGHT: {   selestChar++;
					if (selestChar>4 )	{selestChar=0;}	 //���� ��������� ���������� ��������� ��������� ������� � �������
					if (selestChar<4)	{timeToSend=dataDisp[selestChar];}	 //�������� ������ � ������� �������
				break; }
				
				case 1<<KEY_OK: {   if (selestChar<4)	{changeTimer(selestChar,timeToSend);}
				if (selestChar==4) {
					
					//timeCalc ();
					
					
				   menupunkt=1; //��� ���������� ���������� ������� ����� ������� ������, ����� ������� "��"
				   
				   
					//������ ��������
					//���� �� �����

				
					
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
			
			
		case 1: {    //���� ������[] ��� ����� ���������� ������ ����
			
			
			/*	dot=10;   //
			dataDisp[5]=(endTime[2] & Jnibble);
			dataDisp[4]=(converterTenSix(endTime[2]& Enibble));
			
			dataDisp[3]=(endTime[1] & Jnibble);
			dataDisp[2]=(converterTenSix(endTime[1]& Enibble));
			
			dataDisp[1]=(endTime[0] & Jnibble); 
			dataDisp[0]=(converterTenSix(endTime[0]& Enibble));  */
			
		 displayNumb (test3);  //������������ �� ���������� ������ ��� ����������
	
				

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
	//����� ��������� ���� �� ��� �����, ����� ���� ���� ������� ������� ���� ��� �������, � ������� ���������� ����, ��� �������
	
	//���� �������� ����� ����� �� �� 0 �� 6, ��� ��� ����, ������ 6 ���� ������ �� �����, ��������������, ���� ���, ��� ��������� ��� ������� �������� �� �����.
	ten=(sixteen  & Enibble);
	
	for (uint8_t i=0; i<converterTenSix(sixteen & Enibble); i++)
	{
		ten=ten+10;
	}
	
	
	
	
	ten=ten+ ( sixteen & Jnibble);
	
	
	
	
	//�������. �������� ����� ���-�� ����������� ���� ����?
	

return ten; 
}

//������� �� ������� 16 � ���� ��� 10
//��� ������� ��������� �������?
void changeTimer (uint8_t selestNumber, uint8_t timeToChange) {
	

	

	switch (selestNumber){
		
		case 0: { Timer[0] = (Timer[0]& Enibble) |timeToChange;    break; }      //���  Timer[0] = (timeToChange<<4)| (Timer[0]& Jnibble);  break; 
		case 1: {   Timer[1] = (timeToChange<<4)| (Timer[1]& Jnibble);  break;     }  // Timer[0] = (Timer[0]& Enibble) |timeToChange;    break;   ������ �����
		case 2: {Timer[1] = (Timer[1]& Enibble) |timeToChange;    break;   } //   Timer[1] = (timeToChange<<4)| (Timer[1]& Jnibble);  break; //������?
		case 3: { Timer[2] = (timeToChange<<4)| (Timer[2]& Jnibble);  break; }    //  ������� ������
		//case 4: { Timer[2] = (timeToChange<<4)| (Timer[2]& Jnibble);  break; } 
		//case 5: { Timer[2] = (Timer[2]& Enibble) |timeToChange;    break;  } 
		
		
		default: {};
		
		
	}


};



//------------------------------------------------------------------------------------------------------------------------

void TimerStart ()  //������� ������� ������ ����1, ��� ���������� ������ �� ����� �������, � ������������ � ������ ������ ��� ����������
{
	//24 ���� - ��������� timeData[6]
	
/*	if ( endDate )
	{
		
		
		if (endDate==timeData[6])
		{
			//������������ = 24���� - 1307 + ��������������������	
			
		} 
		else { //������������ = �������������������� - 1307 } 
		
	
		
	} 
		}
	else
	{
		//������������ =������� - 1307 
		//�������
		
		//����� ����������� ��������� � ������� 
		//������� � �������
		//���� ������ ������ ��������, ��������� �������� � �����������
		//������ ���� ������� ��������� ������� - �������� ��������
		
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
	// nowTime[0]=timeData[4]; //����
	 
	// SecTransform (nowTime, &secFrom1307);
	 
	 //convertNumberToMassiv(Timer, &secFrom1307 );
	 
	// vichitanieSec(&test1, &secFrom1307, test3 );	
	 vichitanieSec(&test1, &test2, test3 );	 

	 //���� ��������� ������ � ������������ ���� ����������. �� ������� �������� ����� �������� ��� � ������.
	 // �������� ���������� ������� �������� ������� �������� ���-�� �� ���? � ������� ������� ��� ���������
	 //����������� ������ ��� ���������.
	 //������� ���������� ��� ��������. ���������� ������ � ������ �������
	 
	 
	 //������������ �������� ���1-���2=���������
	

	 
/*	 
	

*/

//������ ������� ����� ������! ��������� �������� ������[3] � ������ �� � ������� � �����
	   
	 
	 //������� ��������� ������������ �� �������

//SecTransform (nowTime, &secFrom1307);




//vichitanieSec(&secFromTimeEnd, &secFrom1307, &Timer );
	
	//test2= 0; //72000 7200  1800 180    22 33  
	//test1= 85300;
	//test1= test1+1;
	
//vichitanieSec(&test1, &secFrom1307, test3 );	



//������ ���������� ����� ������? ��� � ������, �������� �������� ��� ���������� ���1307 ����� ��� � ������, ��� ���-��?  ����� 1.01 ������. ������ �������� ����� -1.01 ������ ���
//����� ��� � �������
//��� ��������� ������ � �������� �������������� ��������� ������ � �������
//����� �� ��������� � ��������� ������ �������� �����,  �� ��� �������� � ��������� ����� � �������
//����� ���� � ������� ���������
		
		//������� ������
		
		//tempForTimer=0;
	//	tempForTimer= TenSixJ(endTime[2]) - TenSixJ(timeData[2])  ;
		//	if (tempForTimer<0)
	//		{ tempForTimer=0;
	//		}
//		nowTime [2]= nowTime[2]& Jnibble;
//		nowTime[2] = (tempForTimer<<4)| nowTime[2];
		
	
	
	
	
	
	
};

	//���������� ��������� � ������. ����� ���-���� ������� � �������?
	//����� ����������� ������� �������. ������� ����� ���������� ����������. 
	
	
	
	/*
	
	uint8_t FuncForVichitanie (
	
uint8_t VichitanieStolb (uint8_t  *osnova, uint8_t  *vichitaimoe)
{

	tempForTimer=0;
	
	
	
	
	if (SixteenToTenDenJ(endTime[2])<SixteenToTenDenJ(timeData[2]))  //���������
	{
		if (TenSixJ(endTime[2])>0)  //���� � ������� ctr ����� ����� 10 ���
		{ 
			tempForTimer=tempForTimer+10;
			nowTime [2] |= (TenSixJ (endTime[2]) -1);  //��������?
			
		}
		else
		 {
			 if (SixteenToTenDenJ(endTime[1])>0)    //���� � ����� ����� �����  60 ���
			 {
			 }
			 else
			 {
				 if (TenSixJ(endTime[1])>0)    //���� �  ������� ����� ����� �����  10 ���
				 {
				 }
				 else
				 {
					 if (SixteenToTenDenJ(endTime[0])>0)    //���� � �����  ����� �����  60 ���
					 {
					 }
					 else
					 {
						 
						 if (TenSixJ(endTime[0])>0)    //���� � �������� ����� ����� �����  10 �
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
		
		
		
	

	
	
	tempForTimer= ( tempForTimer+ SixteenToTenDenJ (endTime[2])) - SixteenToTenDenJ (timeData[2]) ;  //���� ��� ������� �� �������� �������
	
	
	
	
	nowTime [2]= nowTime[2]& Enibble;
	
	 timerMass[2] = (TenSixJ (timerMass[2])<<4)|tempForTimer;
	//�������� ��� ���� ����������? 
	
	//������� ������ (uint8_t *)

	
	
	return	timerMass;

	
};
*/

//secFromTime EndsecFrom1307
void  SecTransform (uint8_t * timerMass, uint32_t * sec)  //��������� �� �����, ������ �� ��������� � �������. � ��������� �� ������� ��� ������� �������
{
//TenSixJ - �������  SixteenToTenDenJ - �������

	
	//ConvertArray("banzai", 2);
	 //*sec =40000020;  - �������


	 
	
*sec=0;


	 tempForTimer=0;
	tempForTimer = TenSixJ(&timerMass[0]) ;  // for ( ;tempForTimer ; tempForTimer--) {**sec = **sec +36000;}
	while (tempForTimer)  { *sec = *sec +36000; tempForTimer--; } //������ �����
	
	//tempForTimer=0;		
	tempForTimer = SixteenToTenDenJ(&timerMass[0]) ; // for ( ;tempForTimer ; tempForTimer--) {*sec = *sec +3600;}
	while (tempForTimer)  { *sec = *sec +3600; tempForTimer--; }   //���
	
		
		 //tempForTimer=0;
		 tempForTimer = TenSixJ(&timerMass[1]) ; // for ( ;tempForTimer ; tempForTimer--) {*sec = *sec +600;}
		 while (tempForTimer)  { *sec = *sec +600; tempForTimer--; }  //������ �����
		 
		// tempForTimer=0;
		 tempForTimer = SixteenToTenDenJ(&timerMass[1]) ; // for ( ;tempForTimer ; tempForTimer--) {*sec = *sec +60;}
		  while (tempForTimer)  { *sec = *sec +60; tempForTimer--; }	//������
		
	 
	// tempForTimer=0;
	 tempForTimer = TenSixJ(&timerMass[1]) ; // for ( ;tempForTimer ; tempForTimer--) {*sec = *sec +10;}
	 while (tempForTimer)  { *sec = *sec +10; tempForTimer--; }
	 
// tempForTimer=0;
	 tempForTimer = SixteenToTenDenJ(&timerMass[1]) ; // for ( ;tempForTimer ; tempForTimer--) {*sec = *sec +1;}
	 while (tempForTimer)  { *sec = *sec +1; tempForTimer--; }		 

	
		// 
			
		//������ � ����� 36000 ��� 2 ��������  timeData ����� �����������, � �� �������. ��� �� ������� ������?
		//��� 	 *sec =  *sec+2;  ����� ���������� � ����������, ���� � ������
		//��� �������� ������ ���� �������� ������ ���������� �������� ������ ���
		//��� ������� ������������� ������ ���������� ������ ����� ������ ����� � ������ ���������. ���� ����� ���������� - �� ����� ��� � ������
		//����� ���� � ���, ��� ������ ����������, � ������� ������ � �����  � ��� �� �����.
		
	//���� = ������� �����;  ���� ���� !=0 { ������� = ������� + 36000 }   TenSixJ (timerMass[0])
	//���� =  ����; ���� ���� !=0 { ������� = ������� + 3600 } 	
	//���� =  ������� �����; ���� ���� !=0 { ������� = ������� + 600 } 
	//���� =   �����; ���� ���� !=0 { ������� = ������� + 60 } 	
	//���� =   ������� ������; ���� ���� !=0 { ������� = ������� + 10 } 	
	//���� =    ������; ���� ���� !=0 { ������� = ������� + 1 } 
		
		//����� ���� ����� � ����������� ��������
		
	//����� �������� �������
	
	//�������� ��������������:
	
	//�������� �� 3600 �� ���������. ����� �������� �� 60. ������� � �������
	
	//���� �������>3600 {����_����++;  �� ����_����>10, ���������� � �������_�������_������������. } ����� ���������� ����� ������[0] ������� = ����_���� 
		
		
		//86400 - �������� ������ � ������			uint32_t - 4 �����  � ��� �� ������
	
	

	
};


void  vichitanieSec (uint32_t *osnova, uint32_t *Vichitaemoe, uint8_t *resultMassiv )  //����� �������� ��������� �� 2 32����� � 1 ������
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


 //��������� � ���, ��� ��������� ������ � ����� ������. ������ ���� �� �����
 

}



//������ ������������� �������� ��������
//���� �������� �������� ���������� �� ����� � ��� (�� ����������� == 00.00, �� ����������������� =  �������;  �����������������= 23.59.59 - �������;
void timeCalc ()  //----------------------������� ����� ��� ������� ��������
{
	assCLI;
		//  timeData[2] = (4<<4)|2;           //�������� ������  �������� - ������ �����, ����� � - ������
		//  timeData[3] = (3<<4)|1;           //�������� �����
		//  timeData[4] = (2<<4)|0;                   //����
		
		//������ + ����� = �������
		//������ ���������� ����� ����� ������� ��������?  ����� ���������� �� ���� 23.59.59 ?
		
		//��� ����� ����������� �������� ������. ������� ����� ���� �� 9 � ������ �������, �� �������� � ���, ��� ���� ��� ������ 8, �� 16 ������, ������
	
	
	//��������� �� ����� �����, ��� ������-�� � ��������� �� ��������. �� ������� ������. 
	//��������� �����, ������ ����� ���� �� �������
	
	//------------------------- ��������� ����� ������ ---------------------------- 
	StartTime[2]=timeData[2];
	StartTime[1]=timeData[3];
	StartTime[0]=timeData[4];
	
	//------------------------- ������� ---------------------------- 
	tempForTimer=0;
	tempForTimer=(SixteenToTenDenJ (&timeData[2]) ) + (SixteenToTenDenJ (&Timer[2])) + (SixteenToTenDenJ (&endTime[2]));
	endTime [2]= endTime[2]& Enibble;

	while (tempForTimer > 9) {tempForTimer=tempForTimer- 10; endTime[2]=  endTime[2] +0x10; }
		
	endTime[2] = (TenSixJ (&endTime[2])<<4)|tempForTimer;
	//------------------------- ������� ������---------------------------- 
	
		tempForTimer=0;
		
		tempForTimer=TenSixJ(&timeData[2]) + TenSixJ(&Timer[2]) + TenSixJ(&endTime[2]);
		endTime [2]= endTime[2]& Jnibble;
		while (tempForTimer > 5) {tempForTimer=tempForTimer-6; endTime[1]++; }  
				
		endTime[2]= (tempForTimer<<4)| endTime[2];	
		
	//------------------------- ������  ---------------------------- 	
	tempForTimer=0;
	tempForTimer=(SixteenToTenDenJ (&timeData[3]) ) + (SixteenToTenDenJ (&Timer[1])) + (SixteenToTenDenJ (&endTime[1]));
	endTime [1]= endTime[1]& Enibble;

	while (tempForTimer > 9) {tempForTimer=tempForTimer- 10; endTime[1]=  endTime[1] +0x10; }
	
	endTime[1] = (TenSixJ (&endTime[1]) <<4)|tempForTimer;
	
		//------------------------- ������� �����---------------------------- 
			tempForTimer=0;
			
			tempForTimer=TenSixJ(&timeData[3]) + TenSixJ(&Timer[1]) + TenSixJ(&endTime[1]);
			endTime [1]= endTime[1]& Jnibble;
			while (tempForTimer > 5) {tempForTimer=tempForTimer-6; endTime[0]++; }
			
			endTime[1]= (tempForTimer<<4)| endTime[1];
		//------------------------- ����  ---------------------------- 
		//���� ����� ���� �� 4 ��� 2 ������ ����� ������ ������� �� �������� �����
			tempForTimer=0;
			tempForTimer=(SixteenToTenDenJ (&timeData[4]) ) + (SixteenToTenDenJ (&Timer[0])) + (SixteenToTenDenJ (&endTime[0]));
			endTime [0]= endTime[0]& Enibble;
			if (SixteenToTenDenJ (&timeData[4]) < 2)
			{  while (tempForTimer > 9) {tempForTimer=tempForTimer- 10; endTime[0]=  endTime[0] +0x10; }
			} 
			else
			{ if  (tempForTimer > 4) { endDate= timeData[6]; //���������� �����
				endNewDay[2]=endTime[2];
				endNewDay[1]=endTime[1];
				endNewDay[0]= (TenSixJ (&endTime[0])) -4; }
			}
			
		
			
			
			endTime[0] = (TenSixJ (&endTime[0]) <<4)|tempForTimer;
		
		//------------------------- ������� �����---------------------------- 
				tempForTimer=0;
				
				tempForTimer=TenSixJ(&timeData[4]) + TenSixJ(&Timer[0]) + TenSixJ(&endTime[0]);
				endTime [0]= endTime[0]& Jnibble;
				if (tempForTimer >1 && SixteenToTenDenJ (&endTime[0]) > 3 ) {}
				if (tempForTimer > 2) {tempForTimer=tempForTimer-2;    }
				
				endTime[0]= (tempForTimer<<4)| endTime[0];

	assSEI;		
		
		
		//��� ������� �������������� ���? �� ������� ��������? ����� ������� �� �������������� ����� 24 ����, ������� �������� � ����������
		
		//����� ��������� ������������� �����, ��������� ����.
		//����� ������� ++ - ��������� ����� ���� �����, �������� 59     endNewDay
	
	//���� = ����������+�������� 
	//while (����>9) {����-9; �������������++; }
	//e���������=����;
	//������������� ���
	//���� � �� � ��� �������sec =0;�. � ���������.
	
	//� ��� �������, ��� ����� ������� ���� 4 ������� ���������� ��� 16��10��� 16��10����� 10��16��� 10��16����
	//����� ����� ���� ��������� ����������� � ����� �������� ������ ���� � ����� �������� �� ���������� �����.
	//���� +1 � �������� ����� ���� � �����������, �� ������, �����, ������ ����������� ��� �������� � ����� �����.
	//��� ����� ���������� ������, ���� ���� ���������� �����? ������ �������������� � ������� ���������� �����? 
	
	
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
			
			case 0x1: { return 1;}      //���  Timer[0] = (timeToChange<<4)| (Timer[0]& Jnibble);  break;
			case 0x2: {   return 2;   }  // Timer[0] = (Timer[0]& Enibble) |timeToChange;    break;   ������ �����
			case 0x3: {  return 3;  } //   Timer[1] = (timeToChange<<4)| (Timer[1]& Jnibble);  break; //������?
			case 0x4: {  return 4; }    //  ������� ������
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

