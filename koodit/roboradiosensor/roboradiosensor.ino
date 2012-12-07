// # Editor     : Lauren from DFRobot
// # Date       : 17.02.2012
 
// # Product name: L298N motor driver module DF-MD v1.3
// # Product SKU : DRI0002
// # Version     : 1.0
 
// # Description:
// # The sketch for using the motor driver L298N
// # Run with the PWM mode
 
// # Connection:
// #        M1 pin  -> Digital pin 4
// #        E1 pin  -> Digital pin 5
// #        M2 pin  -> Digital pin 7
// #        E2 pin  -> Digital pin 6
// #        Motor Power Supply -> Centor blue screw connector(5.08mm 3p connector)
// #        Motor A  ->  Screw terminal close to E1 driver pin
// #        Motor B  ->  Screw terminal close to E2 driver pin
// # 
// # Note: You should connect the GND pin from the DF-MD v1.3 to your MCU controller. They should share the GND pins.
// #
#include <Ultrasonic.h>

Ultrasonic ultrasonic(8);
int E1 = 6;
int M1 = 7;
int E2 = 5;                         
int M2 = 4;

signed char x = 0;
signed char y = 0;
int ohjausR =0;
int ohjausL =0;
 
void setup() 
{ 
    pinMode(M1, OUTPUT);   
    pinMode(M2, OUTPUT); 
    pinMode(A5, INPUT);
    pinMode(12, OUTPUT);
    digitalWrite(12,HIGH);
    Serial.begin(9600);
    Serial1.begin(9600);
}

void goRight(){
  //digitalWrite(M1,LOW);
    digitalWrite(M1,HIGH);   
    digitalWrite(M2,HIGH);       
    analogWrite(E1, 0);   //PWM Speed Control
    analogWrite(E2, 255); 
}

void goLeft(){
  //digitalWrite(M2,LOW);
    digitalWrite(M1,HIGH);   
    digitalWrite(M2,HIGH);       
    analogWrite(E1, 255);   //PWM Speed Control
    analogWrite(E2, 0); 
}
 
 
void goStraight(){
    digitalWrite(M1,HIGH);   
    digitalWrite(M2,HIGH);       
    analogWrite(E1, 255);   //PWM Speed Control
    analogWrite(E2, 255); 

}

void goBack(){
    digitalWrite(M1,LOW);   
    digitalWrite(M2,LOW);       
    analogWrite(E1, 255);   //PWM Speed Control
    analogWrite(E2, 255); 

}

void loop() 
{ 
  //int val = analogRead(A5);    // read the input pin
 // Serial1.println(val);
  if(Serial1.available()>2){
    Serial1.print(Serial1.read());
    
    if(Serial1.read()==0x80){
      x = Serial1.read();
      y = Serial1.read(); 
      Serial1.print(x);
      Serial1.print(y);
      
    }
  }
  //rotation -45 degree :: length 0.7
  //
  int tempx=x;
  int tempy=y;
  if(y>0){
    digitalWrite(M1,HIGH);
    digitalWrite(M2,HIGH);
    
    
  }
  if(y<0){
    digitalWrite(M1,LOW);
    digitalWrite(M2,LOW);
    ultrasonic.MeasureInCentimeters();
    if(ultrasonic.RangeInCentimeters<10){
      
      digitalWrite(M1,HIGH);
    digitalWrite(M2,HIGH);
    }
    tempy=-y;
  }
 
  
  if(tempx>=0){
    
    ohjausL=tempy;
     ohjausR=(1-tempx/127)*tempy;
  }
  if(tempx<0){
    tempx=-tempx;
     ohjausR=tempy;
     ohjausL=(1-tempx/127)*tempy;
  }
 
  if(y==0){
    analogWrite(E1, 0);   //PWM Speed Control
  analogWrite(E2, 0);
  }else{
  analogWrite(E1, ohjausR*2);   //PWM Speed Control
  analogWrite(E2, ohjausL*2); 
   
  }
  ultrasonic.MeasureInCentimeters();
  Serial.println(ultrasonic.RangeInCentimeters);
  /**
  int ohjausX=x;
  if(x<0){
   digitalWrite(M1,LOW);
   ohjausX=-x;
  } else {
  digitalWrite(M1,HIGH); 
  }  
  
  int ohjausY=y;
  if(y<0){
   digitalWrite(M2,LOW);
   ohjausY=-y;
  } else {
  digitalWrite(M2,HIGH); 
  }  
             
      analogWrite(E1, ohjausX);   //PWM Speed Control
      analogWrite(E2, ohjausY); 

  */
  delay(10);
  /*
  int i;
  for(i = 0 ; i <= 1000; i+=5) 
  { 
    1
    if(i<250){
       goStraight();
       } else {
         if(i<500){
         goLeft();
         } else {
          if(i<750){
          goRight();
          }else{
           goBack();
          } 
         }
         delay(10);
    }
    
  
}  
*/
}
