#include<stdio.h>
#include<wiringPi.h>
#include "/usr/include/mysql/mysql.h"

#define SEN1 17
#define SEN2 27
#define SEN3 22

#define SPKR 26

#define LED1 21
#define LED2 20
#define LED3 16
#define LED4 12

#define HOST "183.111.141.63"
#define USER "sil5759"
#define PW "rbgh8447"
#define DB "sil5759"

MYSQL* conn_ptr;
MYSQL_ROW row;
int len;
MYSQL_RES* res;
int mode;



int main(){ 
	wiringPiSetupGpio();

	pinMode(SEN1,INPUT);
	pinMode(SEN2,INPUT);
	pinMode(SEN3,INPUT);
	pinMode(LED1,OUTPUT);
	pinMode(LED2,OUTPUT);
	pinMode(LED3,OUTPUT);
	pinMode(LED4,OUTPUT);
	softToneCreate(SPKR); 
	conn_ptr=mysql_init(NULL);
	if(!conn_ptr){ printf("mysql init 실패\n");}
	conn_ptr=mysql_real_connect(conn_ptr,HOST,USER,PW,DB,3306,(char*)NULL,0);
 
	if(conn_ptr){ printf("연결 성공\n");}
	else{ printf("연결 실패\n");}

	int i=0;
	
	while(1){
		char* query="select mode from semode where num=1004";
		len=mysql_query(conn_ptr,query);
		res=mysql_store_result(conn_ptr);
		while((row=mysql_fetch_row(res))!=NULL){
			printf("%s\n",row[0]);
			mode=atol(row[0]);
		}
		if(digitalRead(SEN1)== 0 && mode == 1){
			char* q="insert into person(room) values(1)";
			printf("Room1\n");

			mysql_query(conn_ptr,q);
			for(i=0;i<6;i++){
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
		}else if(digitalRead(SEN2)== 0 && mode == 1){
			char* q="insert into person(room) values(2)";
			printf("Room2\n");

			mysql_query(conn_ptr,q);
			for(i=0;i<6;i++){
				softToneWrite(SPKR, 391);
				digitalWrite(LED1,1);
				digitalWrite(LED4,1);
				delay(300);
				softToneWrite(SPKR, 293.66);
				digitalWrite(LED1,0);
				digitalWrite(LED4,0);
				delay(300);
			}
			softToneWrite(SPKR,0);
		}else if(digitalRead(SEN3)==0 && mode == 1){
			char* q="insert into person(room) values(3)";
			printf("Room3\n");

			mysql_query(conn_ptr,q);
			for(i=0;i<6;i++){
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
		}
	}
	

}
