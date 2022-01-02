#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <semphr.h>
#include <timer.h>

void vTimerCallback1SecExpired_gas();
void vTimerCallback1SecExpired_distance();

void TaskDistance( void *pvParameters );
void TaskGas( void *pvParameters );
void get_gas_sensor();
void get_gas_concentration();
void get_distance_sensor();
void moveFan(int is_move);
void moveFanWithConcentration(int concentration);
void moveMotor(int dir);

Timer timer1;
Timer timer2;

QueueHandle_t gasQueue;
QueueHandle_t distanceQueue;

// The setup function runs once when you press reset or power the board
void setup()
{
  // motor 2
  pinMode(7,OUTPUT); //en2
  pinMode(6,OUTPUT); //int3
  pinMode(5,OUTPUT);//int4

  // motor 1
  pinMode(10,OUTPUT);//int1
  pinMode(9,OUTPUT);//int2
  pinMode(8,OUTPUT);//en1

  pinMode(13,OUTPUT); //trigger 
  pinMode(12,INPUT); //echo
  pinMode(11,INPUT); //out gas

  /*--------- Initialize serial communication at 9600 bits per second-------------*/
  Serial.begin( 9600 );
  while( !Serial )
  {
    ;  // wait for serial port to connect
  }
  /*---------------------- Create a Timer and start it ---------------------------*/

  //================================== timer 1 ==================================

  // The timer will repeat every 1 sec
  timer1.setInterval(1000); 

  // The function to be called
  timer1.setCallback(vTimerCallback1SecExpired_gas);

  // Start the timer
  timer1.start();

  //================================== timer 2 ==================================

  // The timer will repeat every 1 sec
  timer2.setInterval(1000); 

  // The function to be called
  timer2.setCallback(vTimerCallback1SecExpired_distance);

  // Start the timer
  timer2.start();

  /*------------------------------ Create a Queue --------------------------------*/
  gasQueue = xQueueCreate(
    1                  // Queue length
    , sizeof( int )  // Queue item size
  );

  distanceQueue = xQueueCreate(
    1                  // Queue length
    , sizeof( int )  // Queue item size
  );

  /*------------------------------- Create Tasks ---------------------------------*/
if( distanceQueue != NULL )
  {
    // This task consumes the queue if it was created
    xTaskCreate(
      TaskDistance      
      ,  "Distance"     
      ,  128                   
      ,  NULL                  
      ,  1                     
      ,  NULL                 
    );
  }
if( gasQueue != NULL )
{
  xTaskCreate(
      TaskGas      
      ,  "Gas"         
      ,  128                   
      ,  NULL                 
      ,  1                    
      ,  NULL                  
  );
}
}

void loop()
{
  timer1.update();
  timer2.update();
}

/*-------------------------------------- Tasks -------------------------------------*/
/*------------------------------------- Sensors -----------------------------------*/

// This function publish gas data in the queue if it was created
void vTimerCallback1SecExpired_gas() 
{
  get_gas_sensor();
  // get_gas_concentration();
}

// This function publish distance data in the queue if it was created
void vTimerCallback1SecExpired_distance() 
{
  get_distance_sensor();
}

void get_gas_sensor(){
  const int gas_out = 11;
  int gas_sensor_val = digitalRead(gas_out);
  xQueueSend( gasQueue, &gas_sensor_val, portMAX_DELAY );
  Serial.println("Gas Sensor Value: ");
  Serial.println( gas_sensor_val );
}

void get_gas_concentration(){
  const int gas_out = 4;
  float gas_sensor_val = analogRead(gas_out);
  int concentration = (int)(1944*gas_sensor_val + 300);
  xQueueSend( gasQueue, &concentration, portMAX_DELAY );
  Serial.println("Gas concentration Value: ");
  Serial.println( concentration );
}

void get_distance_sensor(){
  const int echo = 12; 
  const int trigger = 13; 

  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigger, LOW);

  long duration;
  int cm;
  duration = pulseIn(echo, HIGH);
  cm = duration/ 29 / 2;

  xQueueSend( distanceQueue, &cm, portMAX_DELAY );
  Serial.print("Distance Sensor Value: ");
  Serial.println( cm );
  Serial.println(" cm"); 
}

/*-------------------------------------- Tasks -------------------------------------*/
/*------------------------------------- DC Motors -----------------------------------*/

void TaskDistance(void *pvParameters )
{
  char *pcTaskName = ( char * ) pvParameters;
  int queue_val = 0;
  int critical_dist = 300;


  for ( ;; )
  {
    // Read an item from a queue
    if ( xQueueReceive( distanceQueue, &queue_val, portMAX_DELAY ) == pdPASS ) { // If can retrieve an item from queue
      Serial.println("Task Distance Queue Value: ");
      Serial.println( queue_val );

      if(queue_val > critical_dist ) //forward
      {
        moveMotor(1);
      }
      else //backward
      {
        moveMotor(2);
      }
    }
  }
}

void TaskGas( void *pvParameters ) 
{
  char *pcTaskName = ( char * ) pvParameters;
  int queue_val = 0;

  for ( ;; )
  {
    // Read an item from a queue
    if ( xQueueReceive( gasQueue, &queue_val, portMAX_DELAY ) == pdPASS ) { // If can retrieve an item from queue
      Serial.println("Task Gas Sensor Value: ");
      Serial.println( queue_val );

    // if with speed based on concentration
    // moveFanWithConcentration(queue_val);
  
    if(queue_val==1){
      moveFan(1);
    }else{
      moveFan(0);
    }
    }
  }
}
// motor
void moveMotor(int dir){
  int const en1 = 8;
  int const motor_int1 =10;
  int const motor_int2 =9;

  digitalWrite(en1,100);

  if(dir == 1){ // forward
   digitalWrite(motor_int1, HIGH);
   digitalWrite(motor_int2, LOW );  
  }
  if(dir == 3){ // stop
   digitalWrite(motor_int1, LOW);
   digitalWrite(motor_int2, LOW);
  }
  if(dir == 2){ // backward
   digitalWrite(motor_int1, LOW);
   digitalWrite(motor_int2, HIGH);
  }
}
// fan 
void moveFan(int is_move){
  
  int const en2 = 7;
  int const fan_int1 =6;
  int const fan_int2 =5;

  if( is_move == 1){  
  digitalWrite(en2, 100);
  digitalWrite(fan_int1, HIGH);
  digitalWrite(fan_int2, LOW);
  }
  else{
  digitalWrite(en2, 0);
  digitalWrite(fan_int1, HIGH);
  digitalWrite(fan_int2, LOW);
  }

}

// fan with speed related to gas concentration
void moveFanWithConcentration(int concentration){
  int const en2 = 7;
  int const fan_int1 =6;
  int const fan_int2 =5;

  float speed = 0.0263 *concentration + -7.886;
  Serial.println("Speed Value: ");
  Serial.println(speed);
 
  digitalWrite(en2, speed);
  digitalWrite(fan_int1, HIGH);
  digitalWrite(fan_int2, LOW);
}