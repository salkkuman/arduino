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

int automaagi = 1;

signed char x = 0;
signed char y = 0;
signed char z = 0;
int vaisto = 0;
int ohjausL=0;
int ohjausR=0;
double tempx=0;
double tempy=0;

void setup() 
{ 
  pinMode(M1, OUTPUT);   
  pinMode(M2, OUTPUT); 
  pinMode(A5, INPUT);
  pinMode(12, OUTPUT);
  digitalWrite(12,HIGH);
  Serial1.begin(9600);
  Serial.begin(9600);
}

void goRight(unsigned int nopeus){
  //digitalWrite(M1,LOW);
  digitalWrite(M1,HIGH);   
  digitalWrite(M2,HIGH);       
  if(nopeus>255){
    nopeus=255; 
  }
  analogWrite(E1, 0);   //PWM Speed Control
  analogWrite(E2, nopeus); 
}

void goLeft(unsigned int nopeus){
  //digitalWrite(M2,LOW);
  digitalWrite(M1,HIGH);   
  digitalWrite(M2,HIGH);       
  if(nopeus>255){
    nopeus=255 ;
  }
  analogWrite(E1, nopeus);   //PWM Speed Control
  analogWrite(E2, 0); 
}


void goStraight(unsigned int nopeus){
  digitalWrite(M1,HIGH);   
  digitalWrite(M2,HIGH);       
  if(nopeus>255){
    nopeus=255 ;
  }
  analogWrite(E1, nopeus);   //PWM Speed Control
  analogWrite(E2, nopeus); 

}

void goBack(unsigned int nopeus){
  digitalWrite(M1,LOW);   
  digitalWrite(M2,LOW); 
  if(nopeus>255){
    nopeus=255 ;
  }  
  analogWrite(E1, nopeus);   //PWM Speed Control
  analogWrite(E2, nopeus); 

}

int zero(int xyz){

}

void loop() 
{ 
  //int val = analogRead(A5);    // read the input pin
  // Serial1.println(val);

  if(Serial1.available()>3){


    if(Serial1.read()==0x80){
      x = Serial1.read();
      y = Serial1.read();
      z = Serial1.read(); 
      //Serial1.print(x);
      //Serial1.print(y);
      //Serial1.print(z);
      //debugg
      //Serial.print(x);
      //Serial.print(y);
      Serial.print(x);
      Serial.print(" ");
      Serial.print(y);
      Serial.print(" ");
      Serial.println(z);

    }
  }

  ultrasonic.MeasureInCentimeters(); 
  //Serial.println(ultrasonic.RangeInCentimeters+1);
  if(ultrasonic.RangeInCentimeters<20 && (z != 2)){
    vaisto=50;
  }
  if(vaisto>0){
    vaisto--;
    //Serial.print("vaisto: ");
    //Serial.print(vaisto);
    if(vaisto>25){
      goStraight(150); 
      //Serial.println(" Straight");
    }
    if(vaisto<25){
      //Serial.println(" goLeft");
      goLeft(150);
    }
  } 
  

  else {
    if(z==8){
    y=120;
    x=0;
    }
    tempx=x;
    tempy=y;
    if(y<0){
      digitalWrite(M1,HIGH);
      digitalWrite(M2,HIGH);
      tempy=-y;
    }
    if(y>0){
      digitalWrite(M1,LOW);
      digitalWrite(M2,LOW);

    }
    if(tempx>=0){

      ohjausR=tempy;
      ohjausL=(1-tempx/127)*tempy;
    }
    if(tempx<0){
      tempx=-tempx;
      ohjausL=tempy;
      ohjausR=(1-tempx/127)*tempy;
    }

    
    if(y==0){
      analogWrite(E1, 0);   //PWM Speed Control
      analogWrite(E2, 0);
    } 
    else {

      analogWrite(E1, ohjausL);   //PWM Speed Control
      analogWrite(E2, ohjausR); 
    }


    if(z & 1==1 || z==8){
      analogWrite(E1, ohjausL*2);   //PWM Speed Control
      analogWrite(E2, ohjausR*2); 
    } 
    if(z == 4) {
      analogWrite(E1, ohjausL/2);   //PWM Speed Control
      analogWrite(E2, ohjausR/2);        
    } 

  }

  delay(10);

}





