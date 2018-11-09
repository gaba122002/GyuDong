#include<stdio.h>
#include<wiringPi.h>
#include <stdlib.h>
#include<pthread.h>
#include "/usr/include/mysql/mysql.h"

#define SEN1 17
#define SEN3 27


#define SPKR 26

#define LED1 21
#define LED2 20
#define LED3 16
#define LED4 12

#define LCD_RS  25               
#define LCD_E   24               
#define LCD_D4  18               
#define LCD_D5  5               
#define LCD_D6  7               
#define LCD_D7  8   

#define AIN 19
#define BIN 13

#define MAX_COUNT 85
#define DHT_PIN 4

#define HOST "183.111.141.63"
#define USER "sil5759"
#define PW "rbgh8447"
#define DB "sil5759"

int dhtVal[5] = {0,0,0,0,0};
int mode;

pthread_mutex_t mid;

MYSQL* conn_ptr;
MYSQL_ROW row;
int len;
MYSQL_RES* res;

void *dth(){
	
	

	

	

	int lcd; 
	lcd = lcdInit (2, 16,4, LCD_RS, LCD_E ,LCD_D4 , LCD_D5, LCD_D6,LCD_D7,0,0,0,0);
	lcdPosition(lcd,0,0);
	
	unsigned short state = HIGH;
		unsigned short counter = 0;
		unsigned short j = 0, i;
		float farenheit;

		pthread_mutex_trylock(&mid);
		for(i=0; i<5; i++)
			dhtVal[i] = 0;
	
		pinMode(DHT_PIN, OUTPUT);
		digitalWrite(DHT_PIN, LOW);
		delay(18);
		digitalWrite(DHT_PIN, HIGH);
		delayMicroseconds(40);
		pinMode(DHT_PIN, INPUT);
	while(1){
		
		char* query="select mode from semode where num=1004";
		len=mysql_query(conn_ptr,query);
		res=mysql_store_result(conn_ptr);
		while((row=mysql_fetch_row(res))!=NULL){
			printf("%s\n",row[0]);
			mode=atol(row[0]);
		}
		lcdClear(lcd);
		if(mode==1)
			lcdPrintf(lcd, "SECURITY MODE ONH:19.0%% T:22.0*C");
		else
			lcdPrintf(lcd, "ORDINARY MODE   H:19.0%% T:22.0*C");
		
		for(i=0; i<MAX_COUNT; i++)
		{
			counter = 0;
		
			while(digitalRead(DHT_PIN) == state)
			{
				counter++;
				delayMicroseconds(1);
				if(counter == 255)
					break;
			}
			state = digitalRead(DHT_PIN);
			if(counter == 255)
				break;

			if((i>=4)&&(i%2 == 0))
			{
				dhtVal[j/8] <<= 1;
				if(counter > 16)
					dhtVal[j/8] |= 1;
				j++;
			}
		}
		if((j>=40)&&(dhtVal[4] == ((dhtVal[0] + dhtVal[1] + dhtVal[2] + dhtVal[3]) & 0xFF)))
		{
			farenheit = dhtVal[2]*9./5.+32;
			printf("Humidity = %d.%d %% Temperature = %d.%d 'C (%.1f *F)\n", dhtVal[0], dhtVal[1], dhtVal[2], dhtVal[3], farenheit);
			lcdClear(lcd);
			if(mode==1)
				lcdPrintf(lcd, "SECURITY MODE ONH:%d.%d%% T:%d.%d*C",dhtVal[0], dhtVal[1], dhtVal[2], dhtVal[3]);
			else
				lcdPrintf(lcd, "ORDINARY MODE   H:%d.%d%% T:%d.%d*C",dhtVal[0], dhtVal[1], dhtVal[2], dhtVal[3]);
		}
		else
			printf("Invalid Data!! %d %d %d %d\n",dhtVal[0], dhtVal[1], dhtVal[2], dhtVal[3]);lcdClear(lcd);
			if(mode==1)
				lcdPrintf(lcd, "SECURITY MODE ONH:19.0%% T:22.0*C");
			else
				lcdPrintf(lcd, "ORDINARY MODE   H:19.0%% T:22.0*C");
		
		delay(1000);
		pthread_mutex_unlock(&mid);
	}
	

}


void *room1(){
			printf("room1\n");
	
	pthread_mutex_lock(&mid);
	softToneCreate(SPKR); 
	pinMode(SEN1,INPUT);
	pinMode(LED2,OUTPUT);
	pinMode(LED4,OUTPUT);
	pinMode(AIN,OUTPUT); 
	pinMode(BIN,OUTPUT);
	int i;
	while(1){
		if(digitalRead(SEN1)==0&&mode==1){

			char* q="insert into fire(room) values(1)";
			mysql_query(conn_ptr,q);
		

			printf("Room1\n");
			for(i=0;i<6;i++){
				
				digitalWrite(AIN,0);
				digitalWrite(BIN,1);
				softToneWrite(SPKR, 391);
				digitalWrite(LED2,1);
				digitalWrite(LED4,1);
				delay(300);
				softToneWrite(SPKR, 293.66);
				digitalWrite(LED2,0);
				digitalWrite(LED4,0);
				delay(300);
			}
		softToneWrite(SPKR,0);
	digitalWrite(AIN,0);
	digitalWrite(BIN,0);
		}
	}

	pthread_mutex_unlock(&mid);
}


void *room3(){
		printf("room3\n");
	
	pthread_mutex_lock(&mid);
	softToneCreate(SPKR); 
	pinMode(SEN3,INPUT);
	pinMode(LED4,OUTPUT);
	pinMode(LED3,OUTPUT);
	pinMode(AIN,OUTPUT); 
	pinMode(BIN,OUTPUT);
	int i;	
	while(1){
		if(digitalRead(SEN3)==0&&mode==1){

			char* q="insert into fire(room) values(3)";
			mysql_query(conn_ptr,q);
			printf("Room3\n");
			for(i=0;i<6;i++){
				digitalWrite(AIN,0);
				digitalWrite(BIN,1);
				softToneWrite(SPKR, 391);
				digitalWrite(LED3,1);
				digitalWrite(LED4,1);
				delay(300);
				softToneWrite(SPKR, 293.66);
				digitalWrite(LED3,0);
				digitalWrite(LED4,0);
				delay(300);
			}
			softToneWrite(SPKR,0);
	digitalWrite(AIN,0);
	digitalWrite(BIN,0);
			
		}
	}
	pthread_mutex_unlock(&mid);

}



main(){
	conn_ptr=mysql_init(NULL);
	if(!conn_ptr){ printf("mysql init 실패\n");}
	conn_ptr=mysql_real_connect(conn_ptr,HOST,USER,PW,DB,3306,(char*)NULL,0);

	if(conn_ptr){ printf("연결 성공\n");}
	else{ printf("연결 실패\n");}


	wiringPiSetupGpio();


	pthread_t ptDth,ptMotor,ptRoom1,ptRoom2,ptRoom3;
	
		pthread_mutex_init(&mid,NULL);

		pthread_create(&ptDth,NULL,dth,NULL);
		pthread_create(&ptRoom1,NULL,room1,NULL);
		//pthread_create(&ptRoom2,NULL,room2,NULL);
		pthread_create(&ptRoom3,NULL,room3,NULL);
		pthread_join(ptDth,NULL);
		pthread_join(ptRoom1,NULL);
		//pthread_join(ptRoom2,NULL);
		pthread_join(ptRoom3,NULL);
	
		pthread_mutex_destroy(&mid);


}
