#include <Servo.h>
// Define motor control pins

#include <Servo.h>

#define IR_SENSOR_L 2 // Digital pin for IR sensor 1
#define IR_SENSOR_R 3 // Digital pin for IR sensor 2

#define MOTOR_LEFT_SPEED 9
#define MOTOR_RIGHT_SPEED 10
#define MOTOR_LEFT_DIR_1 32
#define MOTOR_LEFT_DIR_2 33
#define MOTOR_RIGHT_DIR_1 36
#define MOTOR_RIGHT_DIR_2 37

#define IR_SENSOR_1 A0
#define IR_SENSOR_2 A1
#define IR_SENSOR_3 A2
#define IR_SENSOR_4 A3
#define IR_SENSOR_5 A4

#define SERVO 11

#define IR_Switch 300

#define SENSOR1_3 A5
#define SENSOR1_2 A6
#define SENSOR1_1 A7
#define SENSOR2_3 A8
#define SENSOR2_2 A9
#define SENSOR2_1 A10
#define SENSOR3_3 A11
#define SENSOR3_2 A12
#define SENSOR3_1 A13

// make sure only one dimension is incremented, here!
bool has_incremented = false;
bool executed = true;
bool repeat = false;
int sensor_Count = 0;
//int sensor_5_count = 0;
int scanned = 0;
int time = 600;
int timer = 400; 
int lturn = 500;
int rturn = 500; //650
int sensor1 = IR_SENSOR_1;
int sensor_left = IR_SENSOR_2;
int sensor_mid = IR_SENSOR_3;
int sensor_right = IR_SENSOR_4;
int sensor5 = IR_SENSOR_5;
int ldir1 = 0;
int ldir2 = 0;
int rdir1 = 0;
int rdir2 = 0;
int leftspeed = 0;
int rightspeed = 0;
//servo variables
Servo sl;
int servol_Stop = 95;
int servor_Stop = 95;
int sl_Pick = 50;
int sl_Place = 13;

// The New Sensors :) 
int sensorValueL = 0;
int sensorValueR = 0;
int rotation;
int i = 0;
int j = 0;
int k = 0;
int l = 0;
int d = 0;
int p = 0;


int currentAxis = 2; // 1,2,3,4 as in A,S,T,C
int nextAxis;
bool neg = 1;
int counter = 0;
int prevcounter = 0;
int currentPos[2] = { 0,0 }; // starting position
int nextPos[2] = { 1,1 };
int prevPos[2];
int array_Thres = 50;
int sensor1_1;
int sensor2_1;
int sensor3_1;
int sensor1_2;
int sensor2_2;
int sensor3_2;
int sensor1_3;
int sensor2_3;
int sensor3_3;
bool finished = false;

void read_Coord()
{
    //Read sensor values
   Serial.println("Reading");
   while (scanned !=3)
   {
      sensor1_3 = analogRead(SENSOR1_3);
      sensor1_3 = sensor1_3<IR_Switch;
      sensor1_3 = (int)sensor1_3; 
      sensor2_3 = analogRead(SENSOR2_3);
      sensor2_3 = sensor2_3<IR_Switch;
      sensor2_3 = (int)sensor2_3;
      sensor3_3 = analogRead(SENSOR3_3);
      sensor3_3 = sensor3_3<IR_Switch;
      sensor3_3 = (int)sensor3_3;
      sensor1_2 = analogRead(SENSOR1_2);
      sensor1_2 = sensor1_2 <IR_Switch;
      sensor1_2 = (int)sensor1_2 ;
      sensor2_2 = analogRead(SENSOR2_2);
      sensor2_2 = sensor2_2<IR_Switch;
      sensor2_2 = (int)sensor2_2;
      sensor3_2 = analogRead(SENSOR3_2);
      sensor3_2 = sensor3_2<IR_Switch;
      sensor3_2 = (int)sensor3_2;
      sensor1_1 = analogRead(SENSOR1_1);
      sensor1_1 = sensor1_1<IR_Switch;
      sensor1_1 = (int)sensor1_1;
      sensor2_1 = analogRead(SENSOR2_1);
      sensor2_1 = sensor2_1<IR_Switch;
      sensor2_1 = (int)sensor2_1;
      sensor3_1 = analogRead(SENSOR3_1);
      sensor3_1 = sensor3_1<IR_Switch;
      sensor3_1 = (int)sensor3_1;
      if (sensor1_1+sensor2_1+sensor3_1+sensor1_2+sensor2_2+sensor3_2+sensor1_3+sensor2_3+sensor3_3 == 3)
        scanned = 3;
    }
}

bool increment()
{
  if (sensor1 < IR_Switch &&  sensor_right < IR_Switch && !has_incremented)
  //if (sensorValueR && sensorValueL && !has_incremented)  // now the leftest one is the one that contains the counter Muhahahahaha 
 {
    sensor_Count++;
    has_incremented = true;
    Serial.println("Junction no");
    Serial.println(sensor_Count);
  }
  else if (sensor1 > IR_Switch &&  sensor5 > IR_Switch)
  //else if (!sensorValueR && !sensorValueL)
  {
    has_incremented = false;
  }
  return has_incremented;
}

void straight()
{
    int t;
    for(t = 0; t<=150; t++)
    {
      pwm();
      delay(1);
    }
}

void turn_left()
{
  while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH){
    pwm();
  }
  stop_here();
  leftspeed = 170;
  rightspeed = 150;
  ldir1 = 1;
  ldir2 = 0;
  rdir1 = 1;
  rdir2 = 0;
  apply_motors();
  delay(timer);
  while((analogRead(IR_SENSOR_3) > IR_Switch) && (analogRead(IR_SENSOR_2) > IR_Switch) && (analogRead(IR_SENSOR_4) > IR_Switch))
  {
    delay(0.1);
  } 
    // right to turn left 
  sensor_Count++;
}

void turn_right()
{
   while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH){
    pwm();
  }
  stop_here();
  leftspeed = 170;
  rightspeed = 150;
  ldir1 = 0;
  ldir2 = 1;
  rdir1 = 0;
  rdir2 = 1;
  apply_motors();
  delay(timer);
 while((analogRead(IR_SENSOR_3) > IR_Switch) && (analogRead(IR_SENSOR_2) > IR_Switch) && (analogRead(IR_SENSOR_4) > IR_Switch))
  {
    delay(0.1);
  }
  // left to turn right
  sensor_Count++;
}
void turn_rightSE()
{
   while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH){
    pwm();
  }
  stop_here();
  leftspeed = 180;
  rightspeed = 150;
  ldir1 = 0;
  ldir2 = 1;
  rdir1 = 0;
  rdir2 = 1;
  apply_motors();
  delay(timer);
  while((analogRead(IR_SENSOR_3) > IR_Switch))
  {
    delay(0.1);
  }
  // leftspeed = 0;
  // rightspeed = 0;
  // ldir1 = 0;
  // ldir2 = 0;
  // rdir2 = 0;
  // rdir1 = 0;
  // apply_motors();
  // delay(100);
  // leftspeed = 160;
  // rightspeed = 130;
  // ldir1 = 0;
  // ldir2 = 1;
  // rdir1 = 0;
  // rdir2 = 1;
  // // apply_motors();
  // while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH){
  //   delay(0.1);
  // }
  
  
  // left to turn right
  sensor_Count++;
}

void apply_motors()
{
  digitalWrite(MOTOR_LEFT_DIR_1,ldir1);
  digitalWrite(MOTOR_LEFT_DIR_2,ldir2);
  digitalWrite(MOTOR_RIGHT_DIR_1,rdir1);
  digitalWrite(MOTOR_RIGHT_DIR_2,rdir2);
  analogWrite(MOTOR_LEFT_SPEED,leftspeed);
  analogWrite(MOTOR_RIGHT_SPEED,rightspeed);
}

void pwm()
{
  read_Value();
  if(sensor_mid < IR_Switch && sensor_left > IR_Switch && sensor_right > IR_Switch)
  {
    leftspeed = 100;
    rightspeed = 100;
    ldir1 = 1;
    ldir2 = 0;
    rdir1 = 0;
    rdir2 = 1;
  
    apply_motors();
  }
  //  if(sensor_mid > IR_Switch && sensor_left > IR_Switch && sensor_right > IR_Switch)
  // {
  //   leftspeed = 80;
  //   rightspeed = 80;
  //   ldir1 = 1;
  //   ldir2 = 0;
  //   rdir1 = 0;
  //   rdir2 = 1;
  
  //   apply_motors();
  // }

   else if(sensor_mid > IR_Switch && sensor_left < IR_Switch && sensor_right > IR_Switch)
  {
    leftspeed = 0;
  rightspeed = 0;
  ldir1 = 0;
  ldir2 = 0;
  rdir2 = 0;
  rdir1 = 0;
  apply_motors();

    leftspeed = 120;
    rightspeed = 120;
    ldir1 = 1;
    ldir2 = 0;
    rdir1 = 1;
    rdir2 = 0;
    apply_motors();
  }
   else if(sensor_mid < IR_Switch && sensor_left < IR_Switch && sensor_right > IR_Switch)
  {
    leftspeed = 0;
  rightspeed = 0;
  ldir1 = 0;
  ldir2 = 0;
  rdir2 = 0;
  rdir1 = 0;
  apply_motors();

    leftspeed = 120;
    rightspeed = 120;
    ldir1 = 1;
    ldir2 = 0;
    rdir1 = 1;
    rdir2 = 0;
    apply_motors();
  }
  else if(sensor_mid > IR_Switch && sensor_left > IR_Switch && sensor_right < IR_Switch)
  {
    leftspeed = 0;
  rightspeed = 0;
  ldir1 = 0;
  ldir2 = 0;
  rdir2 = 0;
  rdir1 = 0;
  apply_motors();

    leftspeed = 120;
    rightspeed = 120;
    ldir1 = 0;
    ldir2 = 1;
    rdir1 = 0;
    rdir2 = 1;
    apply_motors();
  }
  else if(sensor_mid < IR_Switch && sensor_left > IR_Switch && sensor_right < IR_Switch)
  {
    leftspeed = 0;
  rightspeed = 0;
  ldir1 = 0;
  ldir2 = 0;
  rdir2 = 0;
  rdir1 = 0;
  apply_motors();

    leftspeed = 120;
    rightspeed = 120;
    ldir1 = 0;
    ldir2 = 1;
    rdir1 = 0;
    rdir2 = 1;
    apply_motors();
  }

  else if((sensor1 < IR_Switch || sensor_left < IR_Switch) && (sensor5 < IR_Switch || sensor_right < IR_Switch))
  {
    leftspeed = 70;
    rightspeed = 70;
    ldir1 = 1;
    ldir2 = 0;
    rdir1 = 0;
    rdir2 = 1;
    apply_motors();
  }
  return;
}

void pwm_reverse()
{
  if(sensor_mid < IR_Switch && sensor_left > IR_Switch && sensor_right > IR_Switch)
  {
    leftspeed = 60;
    rightspeed = 80;
    ldir1 = 0;
    ldir2 = 1;
    rdir1 = 1;
    rdir2 = 0;

    apply_motors();
  }

  else if(sensor_mid > IR_Switch && sensor_left < IR_Switch && sensor_right > IR_Switch)
  {
    leftspeed = 0;
    rightspeed = 0;
    ldir1 = 0;
    ldir2 = 0;
    rdir2 = 0;
    rdir1 = 0;
    apply_motors();

    leftspeed = 120;
    rightspeed = 120;
    ldir1 = 0;
    ldir2 = 1;
    rdir1 = 0;
    rdir2 = 1;
    apply_motors();
  }
  else if(sensor_mid > IR_Switch && sensor_left > IR_Switch && sensor_right < IR_Switch)
  {
    leftspeed = 0;
    rightspeed = 0;
    ldir1 = 0;
    ldir2 = 0;
    rdir2 = 0;
    rdir1 = 0;
    apply_motors();

    leftspeed = 120;
    rightspeed = 120;
    ldir1 = 1;
    ldir2 = 0;
    rdir1 = 1;
    rdir2 = 0;
    apply_motors();
  }

  else if((sensor1 < IR_Switch || sensor_left < IR_Switch) && (sensor5 < IR_Switch || sensor_right < IR_Switch))
  {
    leftspeed = 80;
    rightspeed = 80;
    ldir1 = 0;
    ldir2 = 1;
    rdir1 = 1;
    rdir2 = 0;
    apply_motors();
  }
  return;
}


  

void read_Value()
{
  // Read sensor values
  sensor1 = analogRead(IR_SENSOR_1);
  sensor_left = analogRead(IR_SENSOR_2);
  sensor_mid = analogRead(IR_SENSOR_3);
  sensor_right = analogRead(IR_SENSOR_4);
  sensor5 = analogRead(IR_SENSOR_5);

  sensorValueL = digitalRead(IR_SENSOR_L); // Read value from IR sensor 1
  sensorValueR = digitalRead(IR_SENSOR_R); // Read value from IR sensor 2
  
  return;
}

void out_Val()
{
  // Debugging: Print sensor values
  Serial.print("Sensor Values: ");
  Serial.print(sensor1);
  Serial.print("  ");
  Serial.print(sensor_left);
  Serial.print("  ");
  Serial.print(sensor_mid);
  Serial.print("  ");
  Serial.print(sensor_right);
  Serial.print("  ");
  Serial.println(sensor5);
  return;
}

void out_Array()
{
  // Debugging: Print sensor values
  Serial.print(sensor1_1);
  Serial.print("  ");
  Serial.print(sensor1_2);
  Serial.print("  ");
  Serial.print(sensor1_3);
  Serial.println("  ");
  Serial.print(sensor2_1);
  Serial.print("  ");
  Serial.print(sensor2_2);
  Serial.print("  ");
  Serial.print(sensor2_3);
  Serial.println("  ");
  Serial.print(sensor3_1);
  Serial.print("  ");
  Serial.print(sensor3_2);
  Serial.print("  ");
  Serial.print(sensor3_3);
  Serial.println("  ");

  return;
}

void check()
{
  if((sensor1_3 == 1) && (sensor2_2 == 1) && (sensor3_1 == 1))
  {
    repeat = false;
    goto out;
  }
  if((sensor1_1 == 1) && (sensor2_2 == 1) && (sensor3_3 == 1))
  {
    repeat = false;
    goto out;
  }
  if((sensor1_1 == 1) && (sensor1_2 == 1) && (sensor1_3 == 1))
  {
    repeat = false;
    goto out;
  }
  if((sensor1_2 == 1) && (sensor2_2 == 1) && (sensor2_3 == 1))
  {
    repeat = false;
    goto out;
  }
  if((sensor1_2 == 1) && (sensor2_2 == 1) && (sensor2_1 == 1))
  {
    repeat = false;
    goto out;
  }
  repeat = true;
out:
  return;
}

void servo_Pick()
{

for (int pos = 2; pos <= 50; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    sl.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15 ms for the servo to reach the position
  }
   delay(1000);
   reverse();
}

void servo_Place()
{
  for (int pos = 50; pos >= 2 ; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    sl.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15 ms for the servo to reach the position
  }
  if(ldir2 != 1 && rdir1 != 1)
  {
    straight();
  }
}

void stop_here()
{
  if(ldir1 == 1 && rdir2 == 1)
  {
    leftspeed = 100;
    rightspeed = 100;
    ldir1 = 0;
    ldir2 = 1;
    rdir1 = 1;
    rdir2 = 0;
    apply_motors();
    delay(100);
  }
  leftspeed = 0;
  rightspeed = 0;
  ldir1 = 0;
  ldir2 = 0;
  rdir2 = 0;
  rdir1 = 0;
  apply_motors();
  delay(500);
}

void pick_Stop()
{
  while(digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
        pwm();
  leftspeed = 0;
  rightspeed = 0;
  ldir1 = 0;
  ldir2 = 0;
  rdir2 = 0;
  rdir1 = 0;
  apply_motors();
}
void reverse_Place()
{
    leftspeed = 60;
    rightspeed = 60;
    ldir1 = 0;
    ldir2 = 1;
    rdir1 = 1;
    rdir2 = 0;
    apply_motors();
    delay(800);
    servo_Place();
     while(digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
    {
      apply_motors();
      delay(1);
    }
    stop_here();
}

void reverse()
{
    leftspeed = 60;
    rightspeed = 60;
    ldir1 = 0;
    ldir2 = 1;
    rdir1 = 1;
    rdir2 = 0;
    apply_motors();
    delay(500);
    while(digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
    {
      apply_motors();
      delay(1);
    }
    stop_here();
    delay(500);
}


void servo_Adjust()
{
    for (int pos = 4; pos <= 50; pos += 1) 
  { // goes from 0 degrees to 180 degrees
      sl.write(pos);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15 ms for the servo to reach the position
  }
}

void jhoom()
{
   while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
    {
      pwm();
    }
  bool ghoom = true;
  int k = 0;
  leftspeed = 0;
  rightspeed = 0;
  ldir1 = 0;
  ldir2 = 0;
  rdir2 = 0;
  rdir1 = 0;
  apply_motors();
  delay(700);
  leftspeed = 170;
  rightspeed = 150;
  ldir1 = 0;
  ldir2 = 1;
  rdir1 = 0;
  rdir2 = 1;
  apply_motors();
  delay(300);
  for (; k <=1; )
  {
    leftspeed = 170;
    rightspeed = 150;
    ldir1 = 0;
    ldir2 = 1;
    rdir1 = 0;
    rdir2 = 1;
    apply_motors();
    delay(1);
    if ((analogRead(IR_SENSOR_2) < IR_Switch ) && !ghoom)
    {   
        k++;
        ghoom = true;
    }
    if (analogRead(IR_SENSOR_2) > IR_Switch ) 
      ghoom = false;
  }
  sensor_Count += 2;
  

}

void setup() {
  // IR sensor pins as INPUT
  pinMode(IR_SENSOR_1, INPUT);
  pinMode(IR_SENSOR_2, INPUT);
  pinMode(IR_SENSOR_3, INPUT);
  pinMode(IR_SENSOR_4, INPUT);
  pinMode(IR_SENSOR_5, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  //Setting motor outputs
  pinMode(MOTOR_LEFT_DIR_1,OUTPUT);
  pinMode(MOTOR_LEFT_DIR_2,OUTPUT);
  pinMode(MOTOR_RIGHT_DIR_1,OUTPUT);
  pinMode(MOTOR_RIGHT_DIR_2,OUTPUT);

  //Servo settings
  sl.attach(SERVO);

  // Initialize Serial communication for debugging
  Serial.begin(9800);
}

void loop() 
{ 
  pwm();
  increment();

switch(sensor_Count){
  case 0:
  digitalWrite(LED_BUILTIN, HIGH);
  sl.write(70);
  break;
case 2:
  if (sensor_Count == 2 && !executed)
    break;
  turn_rightSE();
again:
 while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH && repeat)
 {
    pwm();
    while(digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) == HIGH)
    {
    leftspeed = 120;
    rightspeed = 120;
    ldir1 = 0;
    ldir2 = 1;
    rdir1 = 0;
    rdir2 = 1;
    apply_motors();
    }

    while(digitalRead(IR_SENSOR_R) == HIGH && digitalRead(IR_SENSOR_L) != HIGH)
    {
    leftspeed = 120;
    rightspeed = 120;
    ldir1 = 1;
    ldir2 = 0;
    rdir1 = 1;
    rdir2 = 0;
    apply_motors();
    }
    // read_Value();
    // pwm();
  }
  scanned = 0;
  leftspeed = 60;
  rightspeed = 60;
  ldir1 = 0;
  ldir2 = 1;
  rdir1 = 1;
  rdir2 = 0;
  apply_motors();
  read_Coord();
  out_Array();
  check();
  if (repeat == true)
  {
    goto again;
  }
  stop_here();
  delay(1000);
  while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH )
  {
    pwm();
  }
  turn_left();
  sensor_Count = sensor_Count - 2;
  executed = false;
  break;
  case 4:
  turn_left();
  break;

  default:
  break;
  }
  // path 1
    if( sensor1_1==1 && sensor1_2==0 && sensor1_3==0 && 
        sensor2_1==0 && sensor2_2==1 && sensor2_3==0 && 
        sensor3_1==0 && sensor3_2==0 && sensor3_3==1)
      {

      sl.write(50);
      read_Value();
      // out_Val();
      increment();
      pwm();

      switch(sensor_Count)
      {                        
      case 7:
        //delay(time);
        turn_left();
        break;
      case 11:
        //delay(50);
        //delay(time);
        turn_right();//12
        break;
      case 14:        //picking the first block 
        pick_Stop();
        servo_Place();
        while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
        {
          pwm();
        }
        stop_here();
        servo_Pick();
        sensor_Count++;  //15
        break;

      case 17:
      // delay(50);
        //delay(time);
        turn_right();  //18
        break;
      case 21:
        //delay(time);
        turn_left();    //22
        //adjust();
        break;

      case 23:  //Placing First Tree to empty
        while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
        {
          pwm();
        }
        Serial.println("OOL");
        stop_here();
        delay(1000);
        reverse_Place(); // if reverse is incrementing then after all its count will be 19
        //delay(50);//350
        //stop_here();
        //delay(time);
        servo_Adjust();
        jhoom(); //25
        break;

        // Picking first rock
      case 26:
        turn_right(); //27
        break;

      case 28:  
        turn_right();  //29
        break;

      case 30:
        pick_Stop();
        servo_Place();
         while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
        {
          pwm();
        }
        stop_here();
        servo_Pick(); 
        sensor_Count++;//31
        break;

      case 31:  
        //delay(time);
        turn_left(); //32
        break;

        // placing the first rock 
      case 34:
        turn_left(); //35
        break;

      case 36:
        while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
        {
          pwm();
        }
        Serial.println("OOL");
        stop_here();
        delay(1000);
        reverse_Place(); // if reverse is incrementing then after all its count will be 19
        //delay(50);//350
        //stop_here();
        //delay(time);

        turn_left(); //37
        break;

      case 38:
        //delay(time);
        turn_right(); //39
        break;

        //Picking Tree 2 
      case 40:
        pick_Stop();
        servo_Place();
        while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
        {
          pwm();
        }
        stop_here();
        servo_Pick(); 
        sensor_Count++; //41
        break;
      case 42:
        //delay(time);
        turn_left(); //43
        break;

      case 44:
        //delay(time);
        turn_left(); //45
        break;
        
      /// placting tree no 2
      case 48:
        while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
        {
          pwm();
        }
        Serial.println("OOL");
        stop_here();
        delay(1000);
        reverse_Place(); // if reverse is incrementing then after all its count will be 19
        //delay(50);//350
        //stop_here();
        //delay(time);
        servo_Adjust();
        sensor_Count++; //49
        break;

      case 49:
        //delay(50);
        //delay(time);
        turn_left(); //50
        break;

      case 51:
        turn_right(); //52
        break;

        //Picking ROCK 2
      case 52:
        pick_Stop();
        servo_Place();
        while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
        {
          pwm();
        }
        stop_here();
        servo_Pick(); 
        jhoom(); //54
        break;
        //Placing rock 2
      case 56:
        while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
        {
          pwm();
        }
        Serial.println("OOL");
        stop_here();
        delay(1000);
        reverse_Place(); // if reverse is incrementing then after all its count will be 19
        //delay(50);//350
        //stop_here();
        //delay(time);
        servo_Adjust();
        sensor_Count++; // 57
        break;

      case 57:
        //delay(time);
        turn_left();//58
        break;

      case 59:
        turn_right(); //60
        break;

      // picking tree 3
        case 61:
        pick_Stop();
        servo_Place();
        while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
        {
          pwm();
        }
        stop_here();
        servo_Pick(); 
        sensor_Count++; //62
        break;
      case 63:
        while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
        {
          read_Value();
          pwm();
        }
        stop_here();
        delay(1000);
        jhoom(); //65
        sensor_Count--; // 64
        break;

      case 67:
        //delay(time);
        turn_left(); //68
        break;

      case 69:
        turn_right(); //70
        break;
        // Placng tree 3
      case 71:
        while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
        {
          pwm();
        }
        Serial.println("OOL");
        stop_here();
        delay(1000);
        reverse_Place(); // if reverse is incrementing then after all its count will be 19
        //delay(50);//350
        //stop_here();
        //delay(time);
        servo_Adjust();
        sensor_Count++; //72
        break;

      case 72:
        turn_left(); // 73
        break;
      case 74:
        turn_right(); //75
        break;

        // picking rock 3
      case 75:
        pick_Stop();
        servo_Place();
        while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
        {
          pwm();
        }
        stop_here();
        servo_Pick(); 
        turn_right(); //76
        break;

      case 78:
        turn_right();//79
        break;

      // placing rock 3
      case 82:
        while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
        {
          pwm();
        }
        Serial.println("OOL");
        stop_here();
        delay(1000);
        reverse_Place(); // if reverse is incrementing then after all its count will be 19
        //delay(50);//350
        //stop_here();
        //delay(time);
        servo_Adjust();
        jhoom(); // 84
        break;


      case 86:
        turn_right(); // 87
        break;

      case 89:
        straight();
        delay(500);
        while(1){
          stop_here();
          digitalWrite(LED_BUILTIN, LOW);
          delay(1);
        };

      default:
        break;
      }
}
// path 2
if(  sensor1_1==0 && sensor1_2==0 && sensor1_3==1 && 
     sensor2_1==0 && sensor2_2==1 && sensor2_3==0 && 
     sensor3_1==1 && sensor3_2==0 && sensor3_3==0)
      {
        sl.write(50);
          read_Value();
      // out_Val();
        increment();
        pwm();
        
        switch(sensor_Count)
        {
          case 7:
          turn_left();//8
          break;

          case 9:
          turn_right();//10
          break;

          case 12:
            pick_Stop();
            servo_Place();
            while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
            {
              pwm();
            }
            stop_here();
            servo_Pick();
            sensor_Count++;//13
            break;

          case 14:
          turn_right();//15
          break;

          case 16:
          turn_left(); //17
          break;

          case 19:
          while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
            {
              pwm();
            }
            Serial.println("OOL");
            stop_here();
            delay(1000);
            reverse_Place(); // if reverse is incrementing then after all its count will be 19 //increse onle
            //delay(50);//350
            //stop_here();
            //delay(time);
            servo_Adjust();
            jhoom();//21
            break;

          case 22:
          turn_right();//23
          break;

          case 24:
          turn_right();//25
          break;

          case 26:
            pick_Stop();
            servo_Place();
            pwm();
            i = 0;
            while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
            {
              pwm();
            }
            stop_here();
            servo_Pick();
            //sensor_Count++; 
            jhoom();//28
            break;

            case 29:
            while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
            {
              pwm();
            }
            Serial.println("OOL");
            stop_here();
            delay(1000);
            reverse_Place(); 
            //delay(50);//350
            //stop_here();
            //delay(time);
            servo_Adjust();
            turn_right();//30
            break;

            case 31:
            turn_left();//32
            break;

            case 33:
            pick_Stop();
            servo_Place();
            pwm();
            while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
            {
              pwm();
            }
            stop_here();
            servo_Pick();
            jhoom();//35
            break;

            case 36:
            turn_right();//37
            break;

            case 38:
            turn_left(); //39 place at 38
            break;

            case 40: //placing tree 2
            while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
            {
              pwm();
            }
            Serial.println("OOL");
            stop_here();
            delay(1000);
            reverse_Place(); // if reverse is incrementing then after all its count will be 19
            //delay(50);//350
            //stop_here();
            //delay(time);
            servo_Adjust();
            turn_right();//41
            break;

            case 42:
            turn_right(); //43
            break;

            case 45:
            turn_right(); //46
            break;

            case 48:
            turn_right();
            break;//49   // bara u turn 

            case 51:  //picking rock 2
            pick_Stop();
            servo_Place();
            while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
            {
              pwm();
            }
            stop_here();
            servo_Pick();
            jhoom();//53
            break;

            case 55:
            while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
            {
              pwm();
            }
            Serial.println("OOL");
            stop_here();
            delay(1000);
            reverse_Place(); // if reverse is incrementing then after all its count will be 19
            //delay(50);//350
            //stop_here();
            //delay(time);
            servo_Adjust();
            turn_right(); //56
            break;

            case 57:
            turn_left();//58
            break;

            case 59:
            pick_Stop();
            servo_Place();
            while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
            {
              pwm();
            }
            stop_here();
            servo_Pick();
            jhoom();//61
            break;

            case 63:
            turn_right(); //64   
            break;

            case 65:
            turn_left();//66
            break;

            case 67:
            while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
            {
              pwm();
            }
            Serial.println("OOL");
            stop_here();
            delay(1000);
            reverse_Place(); // if reverse is incrementing then after all its count will be 19
            //delay(50);//350
            //stop_here();
            //delay(time);
            servo_Adjust();
            jhoom();//69 
            break;

            case 70:
            turn_right();//71
            break;

            case 72:
            turn_right();//6..9
            break;

            case 74: //picking rock 3
            pick_Stop();
            servo_Place();
           while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
            {
              pwm();
            }
            stop_here();
            servo_Pick();
            jhoom(); //76
            break;

            case 79:
            while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
            {
              pwm();
            }
            Serial.println("OOL");
            stop_here();
            delay(1000);
            reverse_Place(); // if reverse is incrementing then after all its count will be 19
            //delay(50);//350
            //stop_here();
            //delay(time);
            servo_Adjust();
            
            jhoom();//81
            break;

            case 83:
            turn_right();//84
            break;

            case 88:
            straight();
            delay(500);
            while(1){
              stop_here();
              digitalWrite(LED_BUILTIN, LOW);
              delay(1);
            }
            default:
            break;
        } 
}
//path 3
if(  sensor1_1==1 && sensor1_2==1 && sensor1_3==1 && 
     sensor2_1==0 && sensor2_2==0 && sensor2_3==0 && 
     sensor3_1==0 && sensor3_2==0 && sensor3_3==0)
  {
    sl.write(50);
      read_Value();
  // out_Val();
    increment();
    pwm();
    
    switch(sensor_Count)
    {
      case 7:
      turn_left();
      break;

      case 9:
      turn_right();
      break;

      case 12:
      pick_Stop();
        servo_Place();
        while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
        {
          pwm();
        }
        stop_here();
        servo_Pick();
        sensor_Count++; //13 
        turn_right(); //14
        break;

        case 15:
        turn_left();
        break;

        case 19:
          while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
        {
          pwm();
        }
        Serial.println("OOL");
        stop_here();
        delay(1000);
        reverse_Place(); // if reverse is incrementing then after all its count will be 19
        //delay(50);//350
        //stop_here();
        //delay(time);
        servo_Adjust();
        jhoom(); //21
        break;

        case 22:
        turn_right();
        break;

        case 24:
        turn_right();
        break;

        case 26:
        pick_Stop();
        servo_Place();
        while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
        {
          pwm();
        }
        stop_here();
        servo_Pick();
        jhoom();
        break;

        case 29:
          while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
        {
          pwm();
        }
        Serial.println("OOL");
        stop_here();
        delay(1000);
        reverse_Place(); // if reverse is incrementing then after all its count will be 19
        //delay(50);//350
        //stop_here();
        //delay(time);
        servo_Adjust();
        turn_left();
        break;
        
        case 31:
        turn_right();
        break;

        case 35:
        turn_right();
        break;

        case 38:
        turn_right();
        break;

        case 40:
        pick_Stop();
        servo_Place();
        while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
        {
          pwm();
        }
        stop_here();
        servo_Pick();
        sensor_Count++;
        break;
        
        case 43:
        turn_right();
        break;

        case 45:
        turn_left();
        break;

        case 47:
          while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
        {
          pwm();
        }
        Serial.println("OOL");
        stop_here();
        delay(1000);
        reverse_Place(); // if reverse is incrementing then after all its count will be 19
        //delay(50);//350
        //stop_here();
        //delay(time);
        servo_Adjust();
        turn_right();
        break;

        case 49:
        turn_right();
        break;

        case 52:
        turn_right();
        break;

        case 55:
        turn_right();
        break;

        case 58:
        pick_Stop();
        servo_Place();
        while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
        {
          pwm();
        }
        stop_here();
        servo_Pick();
        jhoom();
        break;
      
        case 61:
          while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
        {
          pwm();
        }
        Serial.println("OOL");
        stop_here();
        delay(1000);
        reverse_Place(); // if reverse is incrementing then after all its count will be 19
        //delay(50);//350
        //stop_here();
        //delay(time);
        servo_Adjust();
        turn_right();
        break;

        case 64:
        turn_left();
        break;

        case 68:
        turn_left();
        break;
        
        case 70:
        turn_left();
        break;

        case 72:
        pick_Stop();
        servo_Place();
        while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
        {
          pwm();
        }
        stop_here();
        servo_Pick();
        sensor_Count++;
        break;

        case 75:
        turn_right();
        break;

        case 77:
        turn_left();
        break;

        case 79:
        while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
        {
          pwm();
        }
        Serial.println("OOL");
        stop_here();
        delay(1000);
        reverse_Place(); // if reverse is incrementing then after all its count will be 19
        //delay(50);//350
        //stop_here();
        //delay(time);
        servo_Adjust();
        turn_left();
        break;

        case 81:
        turn_left();
        break;

        case 83:
        jhoom();
        break;

        case 86:
        pick_Stop();
        servo_Place();
        while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
        {
          pwm();
        }
        stop_here();
        servo_Pick();
        jhoom();
        break;

        case 89:
        while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
        {
          pwm();
        }
        Serial.println("OOL");
        stop_here();
        delay(1000);
        reverse_Place(); // if reverse is incrementing then after all its count will be 19
        //delay(50);//350
        //stop_here();
        //delay(time);
        servo_Adjust();
        turn_left();
        break;

        case 94:
        straight();
        delay(500);
        while(1){
          stop_here();
          digitalWrite(LED_BUILTIN, LOW);
          delay(1);
        }
        break;

        default:
        break;

  }
}
// path 4
if(  sensor1_1==0 && sensor1_2==1 && sensor1_3==0 && 
     sensor2_1==1 && sensor2_2==1 && sensor2_3==0 && 
     sensor3_1==0 && sensor3_2==0 && sensor3_3==0)
        {
          sl.write(50);
            read_Value();
        // out_Val();
          increment();
          pwm();
          
          switch(sensor_Count)
          {
            case 7:
            turn_left();
            break;

            case 9:
            turn_right();
            break;

            case 11:
              pick_Stop();
              servo_Place();
             while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
              {
                pwm();
              }
              stop_here();
              servo_Pick();
              sensor_Count++;
              break;

              case 14: 
              turn_right();
              break;

              case 16:
              turn_left();
              break;

              case 19:
              while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
              {
                pwm();
              }
              Serial.println("OOL");
              stop_here();
              delay(1000);
              reverse_Place(); // if reverse is incrementing then after all its count will be 19
              //delay(50);//350
              //stop_here();
              //delay(time);
              servo_Adjust();
              jhoom();
              break;

              case 22:
              turn_right();
              break;

              case 24:
              turn_right();
              break;

              case 26:
              pick_Stop();
              servo_Place();
              while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
              {
                pwm();
              }
              stop_here();
              servo_Pick();
              jhoom();
              break;

              case 30:
              while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
              {
                pwm();
              }
              Serial.println("OOL");
              stop_here();
              delay(1000);
              reverse_Place(); // if reverse is incrementing then after all its count will be 19
              //delay(50);//350
              //stop_here();
              //delay(time);
              servo_Adjust();
              turn_left();
              break;

              case 32:
              jhoom();
              break;

              case 35:
              pick_Stop();
              servo_Place();
              while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
              {
                pwm();
              }
              stop_here();
              servo_Pick();
              turn_right();
              break;

              case 38:
              while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
              {
                pwm();
              }
              Serial.println("OOL");
              stop_here();
              delay(1000);
              reverse_Place(); // if reverse is incrementing then after all its count will be 19
              //delay(50);//350
              //stop_here();
              //delay(time);
              servo_Adjust();
              jhoom();
              break;

              case 41:
              turn_right();
              break;
              
              case 43:
              turn_right();
              break;

              case 45:
              pick_Stop();
              servo_Place();
             while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
              {
                pwm();
              }
              stop_here();
              servo_Pick();
              jhoom();
              break;

              case 48:
              while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
              {
                pwm();
              }
              Serial.println("OOL");
              stop_here();
              delay(1000);
              reverse_Place(); // if reverse is incrementing then after all its count will be 19
              //delay(50);//350
              //stop_here();
              //delay(time);
              servo_Adjust();
              turn_right();
              break;

              case 51:
              turn_left();
              break;

              case 54:
              turn_left();
              break;

              case 56:
              pick_Stop();
              servo_Place();
             while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
              {
                pwm();
              }
              stop_here();
              servo_Pick();
              turn_left();
              break;

              case 59:
              turn_right();
              break;

              case 61:
              turn_left();
              break;

              case 63:
              while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
              {
                pwm();
              }
              Serial.println("OOL");
              stop_here();
              delay(1000);
              reverse_Place(); // if reverse is incrementing then after all its count will be 19
              //delay(50);//350
              //stop_here();
              //delay(time);
              servo_Adjust();
              turn_left();
              break;

              case 65:
              turn_left();
              break;

              case 67:
              jhoom();
              break;

              case 70:
              pick_Stop();
              servo_Place();
              while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
              {
                pwm();
              }
              stop_here();
              servo_Pick();
              jhoom();
              break;

              case 74:
              turn_left();
              break;

              case 76:
              while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
              {
                pwm();
              }
              Serial.println("OOL");
              stop_here();
              delay(1000);
              reverse_Place(); // if reverse is incrementing then after all its count will be 19
              //delay(50);//350
              //stop_here();
              //delay(time);
              servo_Adjust();
              turn_left();
              break;

              case 79:
              turn_right();
              break;

              case 84:
              straight();
              delay(500);
              while(1){
                stop_here();
                digitalWrite(LED_BUILTIN, LOW);
                delay(1);
              }
              break;

              default:
              break;
        }
    }
// path 5
if(  sensor1_1==0 && sensor1_2==1 && sensor1_3==0 && 
     sensor2_1==0 && sensor2_2==1 && sensor2_3==1 && 
     sensor3_1==0 && sensor3_2==0 && sensor3_3==0)
            {
              sl.write(50);
                read_Value();
            // out_Val();
              increment();
              pwm();
              
                switch(sensor_Count)
              {
                case 7:
                turn_left();
                break;

                case 11:
                turn_right();
                break;

                case 13:
                pick_Stop();
                servo_Place();
                while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
                {
                  pwm();
                }
                stop_here();
                servo_Pick();
                sensor_Count++;   
                break;

                case 17:
                turn_right();
                break;

                case 21:
                turn_left();
                break;

                case 23:
                while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
                {
                  pwm();
                }
                Serial.println("OOL");
                stop_here();
                delay(1000);
                reverse_Place(); // if reverse is incrementing then after all its count will be 19
                //delay(50);//350
                //stop_here();
                //delay(time);
                servo_Adjust();
                jhoom();
                break;

                case 26:
                turn_right();
                break;

                case 28:
                turn_right();
                break;

                case 30:
                pick_Stop();
                servo_Place();
                while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
                {
                  pwm();
                }
                stop_here();
                servo_Pick();
                turn_left();
                break;


                case 33:
                turn_left();
                break;

                case 36:
                  while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
                {
                  pwm();
                }
                Serial.println("OOL");
                stop_here();
                delay(1000);
                reverse_Place(); // if reverse is incrementing then after all its count will be 19
                //delay(50);//350
                //stop_here();
                //delay(time);
                servo_Adjust();
                turn_right();
                break;

                case 38:    
                jhoom();
                break;

                case 41:
                pick_Stop();
                servo_Place();
                while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
                {
                  pwm();
                }
                stop_here();
                servo_Pick();
                sensor_Count++;
                delay(1000);
                break;

                case 44: 
                turn_left();
                break;

                case 47:
                while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
                {
                  pwm();
                }
                Serial.println("OOL");
                stop_here();
                delay(1000);
                reverse_Place(); // if reverse is incrementing then after all its count will be 19
                //delay(50);//350
                //stop_here();
                //delay(time);
                servo_Adjust();
                jhoom();
                break;

                case 50:
                turn_right();
                break;

                case 52:
                turn_right();
                break;

                case 54:
                pick_Stop();
                servo_Place();
                while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
                {
                  pwm();
                }
                stop_here();
                servo_Pick();
                jhoom();
                break;


                case 57:
                while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
                {
                  pwm();
                }
                Serial.println("OOL");
                stop_here();
                delay(1000);
                reverse_Place(); // if reverse is incrementing then after all its count will be 19
                //delay(50);//350
                //stop_here();
                //delay(time);
                servo_Adjust();
                turn_left();
                break;

                case 60:
                turn_right();
                break;

                case 63:
                turn_right();
                break;

                case 65:
                pick_Stop();
                servo_Place();
                while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
                {
                  pwm();
                }
                stop_here();
                servo_Pick();
                turn_right();
                break;

                case 68:
                turn_left();
                break;

                case 70:
                turn_right();
                break;

                case 72:
                  while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
                {
                  pwm();
                }
                Serial.println("OOL");
                stop_here();
                delay(1000);
                reverse_Place(); // if reverse is incrementing then after all its count will be 19
                //delay(50);//350
                //stop_here();
                //delay(time);
                servo_Adjust();
                turn_left();
                break;

                case 74:
                turn_left();
                break;

                case 76:
                jhoom();
                break;

                case 79:
                pick_Stop();
                servo_Place();
                while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
                {
                  pwm();
                }
                stop_here();
                servo_Pick();
                turn_right();
                break;

                case 82:
                turn_right();
                break;

                case 85:
                turn_right();
                break;

                case 87:
                while (digitalRead(IR_SENSOR_R) != HIGH && digitalRead(IR_SENSOR_L) != HIGH)
                {
                  pwm();
                }
                Serial.println("OOL");
                stop_here();
                delay(1000);
                reverse_Place(); // if reverse is incrementing then after all its count will be 19
                //delay(50);//350
                //stop_here();
                //delay(time);
                servo_Adjust();
                turn_right();
                break;

                case 90:
                turn_right();
                break;

                case 93:
                straight();
                delay(500);
                while(1){
                  stop_here();
                  digitalWrite(LED_BUILTIN, LOW);
                  delay(1);
                }
        break;

        default:
        break;
          }
        }                    
}