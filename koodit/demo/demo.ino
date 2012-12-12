#include <Rainbowduino.h>
#include "Frame.h"
#include "Worm.h"
#include "Apple.h"
#include "Wormpart.h"
int placeOfChar=0;
int letter=0;
  int mode=3;
  int i=0;
  int iter=0;
  
Frame frame;
Worm worm;
Apple apple;
boolean alive = true;
long previousMillis = 0;
long interval = 300;
int xinput = 0;
int yinput = 0;

void drawScene() {
  worm.draw(&frame);
  apple.draw(&frame);

  
}



void getCharMask(unsigned char ascii, int poX, int poY, int mask[][8])
{
  if((ascii < 0x20)||(ascii > 0x7e))//Unsupported char.
  {
    ascii = '?';
  }
  for(int i=0;i<8;i++)
  {
    int temp = pgm_read_byte(&simpleFont[ascii-0x20][i]);
    for(int f=0;f<8;f++)
    {
      if((temp>>f)&0x01)
      {
        mask[poY+f][poX+i] = 0xFF;
      } else {
        mask[poY+f][poX+i] = 0;
      }
    }
  }
}

int r[8][8], g[8][8], b[8][8];

//ripulia looppiin asti

class linePart{
public:
  int x;
  int y;
  boolean blinkstate;

  void draw() {
    frame.r[y][x] = 255;
    frame.g[y][x] = 100;
    frame.b[y][x] = 100;
    frame.r[y][7] = 255;
    frame.g[y][7] = 100;
    frame.b[y][7] = 100;
        
        frame.r[y+1][x] = 255;
    frame.g[y+1][x] = 100;
    frame.b[y+1][x] = 100;
    frame.r[y+1][7] = 255;
    frame.g[y+1][7] = 100;
    frame.b[y+1][7] = 100;
  }

  void drawDead() {
    blinkstate = !blinkstate;
    if (blinkstate) {
      frame.r[y][x] = 255;
    }
    else {
      frame.r[y][x] = 0;
    }
  }
} 
partsPong[64];

class Line{
private:
  int head_index, tail_index;
  int xspeed, yspeed;
  boolean dead;

public:
  void init() {
    dead = false;
    head_index = 0;
    tail_index = 1;
    
    yspeed = 0;
    xspeed = 0;
    partsPong[head_index].x = 0;
    partsPong[head_index].y = 3;
    partsPong[tail_index].x = 0;
    partsPong[tail_index].y = 4;
  }

  void respawn() {
    init();
    
  }

  boolean move(int x,int y) {
    
    if(y-partsPong[head_index].y>0){
      yspeed=1;
    }
    if(y-partsPong[head_index].y<0){
      yspeed=-1;
    }
    if(y-partsPong[head_index].y==0){
      yspeed=0;
    }
    
    int newx = partsPong[head_index].x + xspeed;
    int newy = partsPong[head_index].y + yspeed;
    if (false) {
      if (newx < 0 || newx > 7 || newy <0 || newy > 6) {
        dead = true;
      }
    }
    else {
      if (newx > 7) {
        newx = 0;
      }
      if (newx < 0) {
        newx = 7;
      }
      if (newy > 6) {
        newy = 6;
      }
      if (newy < 0) {
        newy = 7;
      }
    }

    if (dead) {
      return false;
    } 
    else {
      head_index++;
      head_index = head_index % 64;
      tail_index++;
      tail_index = tail_index % 64;
      partsPong[head_index].x = newx;
      partsPong[head_index].y = newy;
      return true;
    }
  }
  int getX(){
    return partsPong[head_index].x;
  }
  int getY(){
    return partsPong[head_index].y;
  }
  void draw() {
    int i = tail_index;
    do {
      if (!dead)
        partsPong[i%64].draw();
      else
        partsPong[i%64].drawDead();
      i++;
    } 
    while(i%64 != (head_index + 1) % 64);
  }

  boolean cellReserved(int x, int y) {
    return false;
} 
}
line;


class Ball {
private:
  int x;
  int y;
  int xspeed;
  int yspeed;
  int time;
public:
  void add() {
       time=0;
      //0..7
      x = random(2, 5);
      y = random(2, 5);
      //saa olla 1 TAI -1 TAI 0
      xspeed=random(1,2);
     if(xspeed=2){
      xspeed=-1;
     } 
     //saa olla -1,1 muuteaan ajalla nopeus
     yspeed=1;
    } 
     
     
 void move(){
   time++;
   if(time>100){
    mode++;
   time=0; 
   }
   x+=xspeed;
  y+=yspeed; 
  if(x>7){
   x=7;
   add();
   mode++;
  }
  if(y>7){
   y=7 ;
   add();
   mode++;
  }
  if(y<0){
    y=1;
    add();
    mode++;
  }
  if(x<0){
   x=1; 
   add();
   mode++;
  }
 }
 void changeDirection(int linex,int liney){
    if((liney-1==y||liney==y||liney+1==y) && (x==6)){
     //tämä
     int sup=random(1,2);
     if(yspeed==0 &&sup!=0){
       //yspeed=1;
     }
     //yspeed=-sup*yspeed;
     xspeed*=-1;     
    }
    if(x==0 or x==7){
     //xspeed*=-1; 
    }
    if(y==0 or y==7){
     yspeed*=-1; 
    }
    
  
  if((liney-1==y||liney==y||liney+1==y) && (x==1)){
     //tämä
     int sup=random(1,2);
     if(yspeed==0 &&sup!=0){
       //yspeed*=-1;
     }
     //yspeed=-sup*yspeed;
     xspeed*=-1;     
    }
    if(x==0 or x==7){
      //xspeed=-1; 
    }
    if(y==0 or y==7){
    // yspeed*=-1; 
    }
    
  }

  int getX(){
   return x; 
  }
  int getY(){
   return y; 
  }
  

  void draw() {
    frame.g[y][x] = 255;
  }
} 
ball;

void setup()
{
  Serial.begin(9600);
  Rb.init();
  randomSeed(analogRead(0));
  
  worm.init();
  apple.add(&worm);
  drawScene();
  ball.add();
  
}

void loop()
{
  

    if(mode==1 || mode==2){
      for(; i<1157561; i+=3) {
        
        for(int x=7; x>=0; x--) {
          for(int y=7; y>0; y--) {
            r[x][y] = r[x][y-1];
            g[x][y] = g[x][y-1];
            b[x][y] = b[x][y-1];
          }
        }
        for(int x=7; x>0; x--) {
          r[x][0] = r[x-1][0];
          g[x][0] = g[x-1][0];
          b[x][0] = b[x-1][0];
        }
    
        r[0][0] = 128 + 127*sin(i%73/73.0 * 2*3.14159);
        g[0][0] = 128 + 127*sin(i%157/157.0 * 2*3.14159 + 2);
        b[0][0] = 128 + 127*sin(i%101/101.0 * 2*3.14159 + 4);
        
        int charmask[8][8];
        
        if(letter==0){
        getCharMask('M', 0, 0, charmask);
        }
        
        if(letter==1){
        getCharMask('O', 0, 0, charmask);
        }
        if(letter==2){
        getCharMask('I', 1, 0, charmask);
        }
        if(letter==3){
          getCharMask('! ', 0, 0, charmask);
        }
        if(i%15==0){
          placeOfChar=placeOfChar+1;
          if(placeOfChar==4){
           placeOfChar=0;
           letter+=1;
           if(letter==4){
            letter=0;
           } 
          }
        }
        // Draw buffers
        Rb.blankDisplay();
        if(mode==2){
          for(int x=0; x<8; x++) {
            for(int y=0; y<8; y++) {
              Rb.setPixelXY(x, y, 
                                  r[x][y] & charmask[x][y],
                                  g[x][y] & charmask[x][y],
                                  b[x][y] & charmask[x][y]);
            }
          }
        }
        if(mode==1){
          for(int x=0; x<8; x++) {
            for(int y=0; y<8; y++) {
              Rb.setPixelXY(x, y, 
                                  r[x][y],
                                  g[x][y],
                                  b[x][y]);
            }
          }
        }
      
        iter++;
        
        
        if(iter>60 && letter==3 && mode==2){
         letter=0;
          iter=0;
         mode++;
        }
        if(mode==1 && iter >120){
         mode++; 
         letter=0;
         iter=0;
        }
         if (mode>2){
           break;
         } 
        
      delay(60);
      }
      
    
    }
    if(mode==3){
      
    unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;  

    // Move and draw the worm
    //deeoness of AI
    int deep=16;
    
    boolean alive = true;
    int iterr=0;
    while(iterr<7){
    alive = worm.move(apple.getX(), apple.getY(),iterr);
    if(alive){
      break;
    }
    iterr+=1;
  }
    if (!alive) {
      static int respawn = 10;
      respawn--;
      if (respawn == 0) {
        mode++;
        worm.init();
        apple.add(&worm);
        respawn = 10;
      }
    }

    if (apple.eat(&worm)) {
      worm.grow();
    }

    drawScene();
    for(int x=0; x<8; x++) {
      for(int y=0; y<8; y++) {
        Rb.setPixelXY(x, y, frame.r[x][y], frame.g[x][y], frame.b[x][y]);
      }
    }
  
  frame.clear();
  
  }
  
  if(mode==4){
  do{
    Serial.println("sup");
  line.move(ball.getX(),ball.getY());
  
  ball.move();
  
  ball.changeDirection(line.getX(),line.getY());
  line.draw();
  ball.draw();
  for(int x=0; x<8; x++) {
      for(int y=0; y<8; y++) {
        Rb.setPixelXY(x, y, frame.r[x][y], frame.g[x][y], frame.b[x][y]);
      }
    }
  
  frame.clear();
  delay(300);
  }   
    while(mode==4);
  }
    if(mode>4){
     mode=1; 
    }
    Serial.println(mode);
}
       
    
    //stop:
      //i+=6;
  }

