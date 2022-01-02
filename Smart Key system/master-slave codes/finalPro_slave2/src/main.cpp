#include <Arduino.h>
#include <slave_model.c> 



# define LED1 13
# define LED2 12
# define LED3 11
# define LED4 10

# define key1 9
# define key2 8
# define key3 7
# define key4 6

#define myAddr 11

void setup() {
  
  slave_model_initialize();

  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);

  pinMode(key1,INPUT);
  pinMode(key2,INPUT);
  pinMode(key3,INPUT);
  pinMode(key4,INPUT);

  pinMode(3,OUTPUT);

  slave_model_U.thisAddr=myAddr;
  slave_model_U.msg=0;

  Serial.begin (9600);
}

int state = 0;
int startMillis = 0;
int period = 300;

int report [] ={0,0,0,0};

void loop() {
  int currentMillies = millis();
  if(currentMillies - startMillis < period && startMillis!=0){
      return;
  }
  startMillis = currentMillies;

  slave_model_U.thisAddr=myAddr;

  int isPush1 = digitalRead(key1);
  int isPush2 = digitalRead(key2);
  int isPush3 = digitalRead(key3);
  int isPush4 = digitalRead(key4);

  if(isPush1==1 || ((slave_model_DW.is_c3_slave_model== slave_model_IN_getMsg || slave_model_DW.is_c3_slave_model==slave_model_IN_sendReport) && slave_model_U.msg==2)){
    if(report[0]==0){
        report[0] = 1;
         digitalWrite(LED1,HIGH);
    }else{
      report[0] = 0;
       digitalWrite(LED1,LOW);
    }
  }
  if(isPush2==1 || ((slave_model_DW.is_c3_slave_model== slave_model_IN_getMsg || slave_model_DW.is_c3_slave_model==slave_model_IN_sendReport) && slave_model_U.msg==3)){
    if(report[1]==0){
        report[1] = 1;
         digitalWrite(LED2,HIGH);
    }else{
      report[1] = 0;
       digitalWrite(LED2,LOW);
    }
  }
  if(isPush3==1 || ((slave_model_DW.is_c3_slave_model== slave_model_IN_getMsg || slave_model_DW.is_c3_slave_model==slave_model_IN_sendReport) && slave_model_U.msg==4)){
    if(report[2]==0){
        report[2] = 1;
        digitalWrite(LED3,HIGH);
    }else{
      report[2] = 0;
       digitalWrite(LED3,LOW);
    }
  }
  if(isPush4==1 || ((slave_model_DW.is_c3_slave_model== slave_model_IN_getMsg || slave_model_DW.is_c3_slave_model==slave_model_IN_sendReport) && slave_model_U.msg==5)){
    if(report[3]==0){
        report[3] = 1;
         digitalWrite(LED4,HIGH);
    }else{
      report[3] = 0;
       digitalWrite(LED4,LOW);
    } 
  }

  slave_model_U.report= report[0]*8 + report[1]*4 + report[2]*2 + report[3];

  slave_model_step();

  if(slave_model_Y.modeBus==0){ //read
    Serial.print(slave_model_U.report);

  }else{
    while (!Serial.available())
    {
      /* code */
    }
    slave_model_U.msg=Serial.read(); 
  }
  if(slave_model_U.msg == slave_model_U.thisAddr){
    digitalWrite(3,HIGH);
  }
}
