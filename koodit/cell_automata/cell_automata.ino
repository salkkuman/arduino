#include <Rainbowduino.h>
#include <math.h>
#include <EasyTransfer.h>

#define JOYSTICK_DEAD_ZONE 200
#define JOYSTICK_CENTER 512

//create object
EasyTransfer ET;

struct Frame{
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  unsigned char r[8][8];
  unsigned char g[8][8];
  unsigned char b[8][8];

};

Frame frame;
int mask[8][8];
int step=0;
int rule=157;

void clearFrame() {
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      frame.r[x][y] = 0;
      frame.g[x][y] = 0;
      frame.b[x][y] = 0;
    }
  }
}

//changes number to binary
void num_to_8bit(int num, int bini[]){
  int h=num;
  for(int i=8;i!=0;i--){
    bini[i]=h%2;
    h=h/2;
  }

}

void cellularautomata(int array[][8], int rule){

  int bitti[8];
  num_to_8bit(rule, bitti);


  for(int i=7;i>-1;i--){
    for(int j=0;j<8;j++){
      //clears new row
      if(i==0){
        array[i][j]=0;
      } 
      else {
        //moves old rows one down
        array[i][j] = array[i-1][j];
      }
    } 
  }
  //left right and middle bit for rule comparisons
  int l = 0;
  int r = 0;
  int m = 0;

  for(int j=0;j<8;j++){
    //finding the bits
    m = array[1][j];
    if(j>0){
      l = array[1][j - 1] ;
    }
    if(j < 7){
      r = array[1][j + 1];
    }

    //applying the rules
    if(bitti[0]&& l && m && r){
      array[0][j] = 1;
    }
    if(bitti[1]&& l && m && !r){
      array[0][j] = 1;
    }
    if(bitti[2]&& l && !m && r){
      array[0][j] = 1;
    }
    if(bitti[3]&& l && ! m && ! r){
      array[0][j] = 1;
    }
    if(bitti[4]&& ! l && m && r){
      array[0][j] = 1;
    }
    if(bitti[5]&& ! l && m && ! r){
      array[0][j] = 1;
    }
    if(bitti[6]&& ! l && ! m && r){
      array[0][j] = 1; 
    }
    if(bitti[7]&& ! l && ! m && ! r){       
      array[0][j] = 1;
    }

  }

}


void setup(){
  Serial.begin(19200);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
  ET.begin(details(frame), &Serial);

  pinMode(13, OUTPUT);

  randomSeed(analogRead(0));
  clearFrame();
}



void loop(){

  //getting the mask
  cellularautomata(mask, rule);
  if(step%10==0){
    frame.r[0][5]=255;
    rule++;
  }
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      //putting the right bits on the frame
      frame.r[x][y] = mask[x][y];

      if(mask[x][y]){
        frame.r[x][y]=255;

      }

    }

  }

  ET.sendData();
  //delay(50);
  step++;
}






