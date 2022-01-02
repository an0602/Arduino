#include <IRremote.h> //Make sure to install the library, version 2.2.3
#include <Servo.h>

const int IRpin=11;
const int LED_PIN = 2;
const int LASER_PIN = 3;  //note, laser module does NOT use center pin for power
const int SERVO_PIN = 4;
IRrecv IR(IRpin);
decode_results cmd;
String myCom;
int laser_flag = 0;

Servo my_servo;
int servo_angle = 0;  //servo position in degrees

#define SPEED 140    
#define TURN_SPEED 160    
#define speedPinR 32   //  Front Wheel PWM pin
#define RightMotorDirPin1  22    //Front Right Motor direction pin 1
#define RightMotorDirPin2  24   //Front Right Motor direction pin 2                                 
#define LeftMotorDirPin1  30    //Front Left Motor direction pin 1
#define LeftMotorDirPin2  28   //Front Left Motor direction pin 2
#define speedPinL 34   //  Front Wheel PWM pin connect

/*motor control*/
void go_advance(int speed){
   FR_fwd(speed);
   FL_fwd(speed); 
}
void go_back(int speed){
   FR_bck(speed);
   FL_bck(speed); 
}

void left_turn(int speed){
   //RL_bck(0);
   FL_fwd(speed); 
   FR_bck(speed);   
}
void right_turn(int speed){
   //FR_bck(0);
   FR_fwd(speed);
   FL_bck(speed);
}

void FR_fwd(int speed)  //front-right wheel forward turn
{
  digitalWrite(RightMotorDirPin1,HIGH);
  digitalWrite(RightMotorDirPin2,LOW); 
  analogWrite(speedPinR,speed);
}
void FR_bck(int speed) // front-right wheel backward turn
{
  digitalWrite(RightMotorDirPin1,LOW);
  digitalWrite(RightMotorDirPin2,HIGH); 
  analogWrite(speedPinR,speed);
}
void FL_fwd(int speed) // front-left wheel forward turn
{
  digitalWrite(LeftMotorDirPin1,HIGH);
  digitalWrite(LeftMotorDirPin2,LOW);
  analogWrite(speedPinL,speed);
}
void FL_bck(int speed) // front-left wheel backward turn
{
  digitalWrite(LeftMotorDirPin1,LOW);
  digitalWrite(LeftMotorDirPin2,HIGH);
  analogWrite(speedPinL,speed);
}

void stop_Stop()    //Stop
{
  analogWrite(speedPinL,0);
  analogWrite(speedPinR,0);
}

//Pins initialize
void init_GPIO()
{
  pinMode(RightMotorDirPin1, OUTPUT); 
  pinMode(RightMotorDirPin2, OUTPUT); 
  pinMode(speedPinL, OUTPUT);  
 
  pinMode(LeftMotorDirPin1, OUTPUT);
  pinMode(LeftMotorDirPin2, OUTPUT); 
  pinMode(speedPinR, OUTPUT);
   
  stop_Stop();
}

void setup()
{  
  Serial.begin(9600);
  IR.enableIRIn();

  init_GPIO();
  /*
  go_advance(SPEED);
     delay(1000);
     stop_Stop();
     delay(1000);   
  */     
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(LASER_PIN, LOW);
  my_servo.attach(SERVO_PIN);
  
  my_servo.write(0);
  delay(500);


  
}
 
void loop() {
  while (IR.decode(&cmd)==0){ 
}
  Serial.println(cmd.value,HEX);
  delay(1000);
  IR.resume();

  if(cmd.value==0xFFA25D){
    myCom="1";
    Serial.println(myCom); 
    digitalWrite(LED_PIN,HIGH);
  } 
  else if (cmd.value==0xFF629D){
    myCom="2";
    Serial.println(myCom); 
    //fire laser!
    if(laser_flag == 0){
      digitalWrite(LASER_PIN, HIGH);
      laser_flag = 1;
      Serial.println("laser on");
      Serial.println(laser_flag);
    }
    else if(laser_flag == 1){
      digitalWrite(LASER_PIN, LOW);
      laser_flag = 0;
      Serial.println(laser_flag);
    }    
  }
  else if (cmd.value==0xFFE21D){
    myCom="3";
    Serial.println(myCom);
    digitalWrite(LED_PIN,LOW); 
  }
  else if (cmd.value==0xFF22DD){
    myCom="4";
    Serial.println(myCom);
    if(servo_angle > 50){
      for(servo_angle; servo_angle >= 30; servo_angle--){
        my_servo.write(servo_angle);
        delay(10);
      }
      delay(250);
    }
    else{
      for(servo_angle; servo_angle <=30; servo_angle++){
        my_servo.write(servo_angle);
        delay(10);
      }
      delay(250);        //wait 1 second for motor to turn 
    }
  } 
  else if (cmd.value==0xFF02FD){
    myCom="5";
    Serial.println(myCom);
    for(servo_angle; servo_angle <=60; servo_angle++){
      my_servo.write(servo_angle);
      delay(10);
    }
    delay(250);
  }
  else if (cmd.value==0xFFC23D){
    myCom="6";
    Serial.println(myCom);
    //my_servo.write(-45); //turn servo motor right by 45 degrees
    for(servo_angle; servo_angle >= 0; servo_angle--){
      my_servo.write(servo_angle);
      delay(10);
    }
    delay(250);      //wait 1 second for motor to turn
  }
  else if (cmd.value==0xFFE01F){
    myCom="7";
    Serial.println(myCom); 
  }
  else if (cmd.value==0xFFA857){
    myCom="8";
    Serial.println(myCom); 
  }         
  else if (cmd.value==0xFF906F){
    myCom="9";
    Serial.println(myCom);  
  }
  else if (cmd.value==0xFF6897){
    myCom="asterik";
    Serial.println(myCom);  
  }
  else if (cmd.value==0xFF9867){
    myCom="0";
    Serial.println(myCom);  
  }
  else if (cmd.value==0xFFB04F){
    myCom="pound";
    Serial.println(myCom);  
  }
  else if (cmd.value==0xFF18E7){
    myCom="up";
    Serial.println(myCom);
    stop_Stop();
    delay(100);
    go_advance(SPEED); 
    delay(100);      
  }     
  else if (cmd.value==0xFF10EF){
    myCom="left";
    Serial.println(myCom);
    stop_Stop();
    delay(100);
    left_turn(SPEED); 
    delay(100);  
  }
  else if (cmd.value==0xFF38C7){
    myCom="ok";
    Serial.println(myCom);
    stop_Stop();
    delay(100);      
  }
  else if (cmd.value==0xFF5AA5){
    myCom="right";
    Serial.println(myCom);
    stop_Stop();
    delay(100);
    right_turn(SPEED); 
    delay(100);       
  }
  else if (cmd.value==0xFF4AB5){
    myCom="down";
    Serial.println(myCom);
    stop_Stop();
    delay(100);
    go_back(SPEED); 
    delay(100);       
  }
/*
  //servo motor, sweep from 0 to 180 degrees
  for(servo_angle = 0; servo_angle <= 180; servo_angle += 1){
    my_servo.write(servo_angle);
    delay(15);               
  }

  //servo motor, sweep back from 180 degrees to 0 degrees
  for(servo_angle = 180; servo_angle >= 0; servo_angle -= 1){
    my_servo.write(servo_angle);
    delay(30);               
  }
  delay(1000);
*/  
}
