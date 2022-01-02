#include <Arduino.h>
#include <master_model.c>

# define LED1 10
# define LED2 11
# define LED3 12
# define LED4 13

# define key1 4
# define key2 5
# define key3 6
# define key4 7

# define SELECT1 8
# define SELECT2 9

# define SLAVE1 10
# define SLAVE2 11

void setup() {
  master_model_initialize();
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);

  pinMode(SELECT1,INPUT);
  pinMode(SELECT2,INPUT);

  pinMode(key1,INPUT);
  pinMode(key2,INPUT);
  pinMode(key3,INPUT);
  pinMode(key4,INPUT);
  Serial.begin (9600);
}
int state = 0;
int startMillis = 0;
int period =300;

int led_status[] = {0,0,0,0};
int selected_slave [] = {0,0};
int report;

int selected_address=0;
//0 -> motazere slave befreste if ferestad  switchPIN ON  if BTN -> state=1
//1 -> nafrest dige -> send 0 to slave -> state =2
//2 -> age ferestadd errorr

void loop() {
  int currentMillies = millis();
  if(currentMillies - startMillis < period && startMillis!=0){
      return;
  }
  startMillis = currentMillies;


  // int isSelect1 = digitalRead(SELECT1);
  // int isSelect2 = digitalRead(SELECT2);

  master_model_U.deviceSelect=0;
  if(digitalRead(SELECT1)){
    master_model_U.deviceSelect=1;
    if(selected_slave[0]==1){
      selected_slave[0]=0;
    }else{
      selected_slave[0]=1;
    }
    
    if( selected_slave[0]==1){
      
      master_model_U.address=SLAVE1;
      selected_slave[1]=0;
    }
  }else if(digitalRead(SELECT2)){
    master_model_U.deviceSelect=2;
    if(selected_slave[1]==1){
      selected_slave[1]=0;
    }else{
      selected_slave[1]=1;
    }
    if( selected_slave[1]==1){    
      master_model_U.address=SLAVE2;
      selected_slave[0]=0;
    }
  }
  // else{
  //     // master_model_U.deviceSelect=0;
  //     // master_model_U.address=18;
  // }
  
  int isPush1 = digitalRead(key1);
  int isPush2 = digitalRead(key2);
  int isPush3 = digitalRead(key3);
  int isPush4 = digitalRead(key4);

  if(selected_slave[0]==1 || selected_slave[1]==1){
    if(isPush1==1){
      master_model_U.in=2;
    }else if(isPush2==1){
      master_model_U.in=3;
    }else if(isPush3==1){
      master_model_U.in=4;
    }else if(isPush4==1){
      master_model_U.in=5;
    }else{
      master_model_U.in = 20;
    }
  }
  else{ 
  if(isPush1==1 ){
      if(led_status[0]==0){
          led_status[0] = 1;
          digitalWrite(LED1,HIGH);
      }else{
        led_status[0] = 0;
        digitalWrite(LED1,LOW);
      }
    }
    if(isPush2==1){
      if(led_status[1]==0){
          led_status[1] = 1;
          digitalWrite(LED2,HIGH);
      }else{
        led_status[1] = 0;
        digitalWrite(LED2,LOW);
      }
    }
    if(isPush3==1 ){
      if(led_status[2]==0){
          led_status[2] = 1;
          digitalWrite(LED3,HIGH);
      }else{
        led_status[2] = 0;
        digitalWrite(LED3,LOW);
      }
    }
    if(isPush4==1 ){
      if(led_status[3]==0){
          led_status[3] = 1;
          digitalWrite(LED4,HIGH);
      }else{
        led_status[3] = 0;
        digitalWrite(LED4,LOW);
      } 
    }
  }
  

  master_model_step();


  // if(master_model_Y.dataBus==1 || master_model_Y.dataBus==0 || master_model_Y.dataBus==SLAVE1 || master_model_Y.dataBus==SLAVE2){
  //   Serial.write(master_model_Y.dataBus);
  // }else
  //  if(master_model_Y.modeBus==0){   // write
  //   Serial.write(master_model_Y.dataBus);
  // }else
   if(master_model_Y.modeBus==1)  //read
  {
    while (!Serial.available())
    {
      /* code */
    }
    report=Serial.read();
  }else { 
    // Serial.print(master_model_Y.dataBus);
    Serial.write(master_model_Y.dataBus);
  }
}

