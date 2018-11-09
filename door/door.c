#include<wiringPi.h>
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include <lcd.h> 
#include "/usr/include/mysql/mysql.h"

#define SW1 21
#define SW2 20
#define SW3 16
#define SW4 12
#define SW5 25
#define SW6 24
#define SW7 23
#define SW8 18
#define SW9 19
#define SW0 13
#define SWB 6
#define SWS 5
#define SV 22
#define DELAY 300
#define LED 7
#define SPKR 26

#define LCD_RS  14               //Register select pin
#define LCD_E   15               //Enable Pin
#define LCD_D4  8               //Data pin 4
#define LCD_D5  10               //Data pin 5
#define LCD_D6  2               //Data pin 6
#define LCD_D7  3

#define R 4
#define B 17
#define G 27

#define HOST "183.111.141.63"
#define USER "sil5759"
#define PW "rbgh8447"
#define DB "sil5759"


MYSQL* conn_ptr;
MYSQL_ROW row;
int len;
MYSQL_RES* res;

int switchControl()
{
	int p[4];
	int i;
	int pw[4];
	int password;
	int count=0;
	int ppp=0;
	int x=0;
	int lcd;
	
	softPwmCreate(SV,0,200);
	
	lcd = lcdInit (2, 16,4, LCD_RS, LCD_E ,LCD_D4 , LCD_D5, LCD_D6,LCD_D7,0,0,0,0);
	lcdClear(lcd);
	lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:");

	pinMode(SW1, INPUT);
	pinMode(SW2, INPUT);
	pinMode(SW3, INPUT);
	pinMode(SW4, INPUT);
	pinMode(SW5, INPUT);
	pinMode(SW6, INPUT);
	pinMode(SW7, INPUT);
	pinMode(SW8, INPUT);
	pinMode(SW9, INPUT);
	pinMode(SW0, INPUT);
	pinMode(SWB, INPUT);
	pinMode(SWS, INPUT);
	pinMode(R, OUTPUT);
	pinMode(G, OUTPUT);
	pinMode(B, OUTPUT);
	pinMode(LED, OUTPUT);
	softToneCreate(SPKR); 

	
	digitalWrite(B,0);
	digitalWrite(G,0);
	digitalWrite(R,0);


	softToneWrite(SPKR, 0);
	len = mysql_query(conn_ptr, "select * from password;");
	res = mysql_store_result(conn_ptr);
	row = mysql_fetch_row(res);

	while(1)
	{
		//lcdClear(lcd);
		//lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:");
		if(digitalRead(SW1) == HIGH)
		{
			printf("1\n");
			pw[count]=1;
			if(count<3)	count++;
			ppp++;
			if(ppp==1){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:*");
			}else if(ppp==2){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:**");
			}else if(ppp==3){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:***");
			}else{
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:****");
			}
			delay(DELAY);
			
		}
		if(digitalRead(SW2) == HIGH)
		{
			printf("2\n");
			pw[count]=2;
			if(count<3)	count++;
			ppp++;
			if(ppp==1){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:*");
			}else if(ppp==2){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:**");
			}else if(ppp==3){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:***");
			}else{
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:****");
			}
			delay(DELAY);
		}
		if(digitalRead(SW3) == HIGH)
		{
			printf("3\n");
			pw[count]=3;
			if(count<3)	count++;
			ppp++;
			if(ppp==1){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:*");
			}else if(ppp==2){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:**");
			}else if(ppp==3){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:***");
			}else{
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:****");
			}
			delay(DELAY);
		}
		if(digitalRead(SW4) == HIGH)
		{
			printf("4\n");
			pw[count]=4;
			if(count<3)	count++;
			ppp++;
			if(ppp==1){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:*");
			}else if(ppp==2){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:**");
			}else if(ppp==3){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:***");
			}else{
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:****");
			}
			delay(DELAY);
		}
		if(digitalRead(SW5) == HIGH)
		{
			printf("5\n");
			pw[count]=5;
			if(count<3)	count++;
			ppp++;
			if(ppp==1){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:*");
			}else if(ppp==2){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:**");
			}else if(ppp==3){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:***");
			}else{
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:****");
			}
			delay(DELAY);
		}
		if(digitalRead(SW6) == HIGH)
		{
			printf("6\n");
			pw[count]=6;
			if(count<3)	count++;
			ppp++;
			if(ppp==1){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:*");
			}else if(ppp==2){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:**");
			}else if(ppp==3){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:***");
			}else{
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:****");
			}
			delay(DELAY);
		}
		if(digitalRead(SW7) == HIGH)
		{
			printf("7\n");
			pw[count]=7;
			if(count<3)	count++;
			ppp++;
			if(ppp==1){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:*");
			}else if(ppp==2){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:**");
			}else if(ppp==3){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:***");
			}else{
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:****");
			}
			delay(DELAY);
		}
		if(digitalRead(SW8) == HIGH)
		{
			printf("8\n");
			pw[count]=8;
			if(count<3)	count++;
			ppp++;
			if(ppp==1){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:*");
			}else if(ppp==2){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:**");
			}else if(ppp==3){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:***");
			}else{
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:****");
			}
			delay(DELAY);
		}
		if(digitalRead(SW9) == HIGH)
		{
			printf("9\n");
			pw[count]=9;
			if(count<3)	count++;
			ppp++;
			if(ppp==1){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:*");
			}else if(ppp==2){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:**");
			}else if(ppp==3){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:***");
			}else{
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:****");
			}
			delay(DELAY);
		}
		if(digitalRead(SW0) == HIGH)
		{
			printf("0\n");
			pw[count]=0;
			if(count<3)	count++;
			ppp++;
			if(ppp==1){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:*");
			}else if(ppp==2){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:**");
			}else if(ppp==3){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:***");
			}else{
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE  PASSWORD:****");
			}
			delay(DELAY);
		}
		if(digitalRead(SWB) == HIGH)
		{
			printf("*\n");
			password = atoi(row[0]);
			p[3] = password % 10;
			p[2] = password / 10 % 10;
			p[1] = password / 100 % 10;
			p[0] = password / 1000 % 10;
			
			if(pw[0]==p[0] && pw[1] == p[1] && pw[2]==p[2] && pw[3] == p[3]){
				printf("문이 열립니다\n");
				char* q="insert into door(door) values(1)";
				mysql_query(conn_ptr,q);
				softPwmWrite(SV,24);
				digitalWrite(B,1);
				digitalWrite(G,0);
				digitalWrite(R,1);
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE   DOOR OPEN");
				x=0;
				ppp=0;
			}else{
				printf("비밀번호가 틀렸습니다\n");
				
				digitalWrite(B,1);
				digitalWrite(G,1);
				digitalWrite(R,0);
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE   XXXXXXXXXXXXX");
				x++;
				ppp=0;
			}
			if(x==3){
				lcdClear(lcd);
				lcdPuts(lcd, "*:OPEN #:CLOSE      STRANGER");
				char* q="insert into door(door) values(3)";
				mysql_query(conn_ptr,q);
				q="update semode set mode=1 where num=1004";
				mysql_query(conn_ptr,q);
				ppp=0;
				for(i=0;i<6;i++){
					softToneWrite(SPKR, 391);
					digitalWrite(LED,1);
					delay(300);
					softToneWrite(SPKR, 293.66);
					digitalWrite(LED,0);
					delay(300);
				}
				
				softToneWrite(SPKR, 0);
				x=0;	
			}
			for(i=0;i<4;i++){
				pw[i]=-1;
			}
			count=0;
			
			delay(700);

			digitalWrite(B,0);
			digitalWrite(G,0);
			digitalWrite(R,0);
		}
		if(digitalRead(SWS) == HIGH)
		{
			lcdClear(lcd);
			lcdPuts(lcd, "*:OPEN #:CLOSE   DOOR CLOSE");
			printf("#\n");
			printf("문이 닫힙니다\n");
			char* q="insert into door(door) values(2)";
			mysql_query(conn_ptr,q);
			softPwmWrite(SV,15);
			digitalWrite(B,0);
			digitalWrite(G,0);
			digitalWrite(R,0);
			for(i=0;i<4;i++){
				pw[i]=-1;
			}
			delay(DELAY);
		}
	}
	return 0;
}
int main(int argc, char** argv)
{
	conn_ptr=mysql_init(NULL);
	if(!conn_ptr){ printf("mysql init 실패\n");}
	conn_ptr=mysql_real_connect(conn_ptr,HOST,USER,PW,DB,3306,(char*)NULL,0); 
	if(conn_ptr){ printf("연결 성공\n");}
	else{ printf("연결 실패\n");}
	wiringPiSetupGpio();

	switchControl();
	
	return 0;
}
