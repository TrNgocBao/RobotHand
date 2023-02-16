//Transmitter Code (Glove)

#include <SPI.h>
#include "RF24.h"

int msg[5]; //Total number of data to be sent

//define the flex sensor input pins
int finger_1 = A1;
int finger_2 = A2;
int finger_3 = A3;
int finger_4 = A4;
int finger_5 = A5;

RF24 radio(9,10); //CE and CSN
                                      
const uint64_t pipe = 0xE8E8F0F0E1LL; //the address of the modem, that will receive data from Arduino.


void setup(void){
  radio.begin();                     
  radio.setAutoAck(1);               
  radio.setRetries(1,1);             
  radio.setDataRate(RF24_1MBPS);    // Tốc độ truyền
  radio.setPALevel(RF24_PA_MAX);      // Dung lượng tối đa
  radio.setChannel(10);               // Đặt kênh
  radio.openWritingPipe(pipe);        // mở kênh
  Serial.begin(9600); // mở cổng Serial tiện debug
}

void loop(void){
  int f1 = analogRead(finger_1);
  int f2 = analogRead(finger_2);
  int f3 = analogRead(finger_3);
  int f4 = analogRead(finger_4);
  int f5 = analogRead(finger_5);
  //Serial.println(f4);
  
  int r1= ChangeValue(f1);
  int r2= ChangeValue(f2);
  int r3= ChangeValue(f3);
  int r4= ChangeValue(f4);
  int r5= ChangeValue(f5);
  Serial.println("Angle of index finger: ");
  Serial.println(r4);

  
  msg[0] = r1;
  msg[1] = r2;
  msg[2] = r3;
  msg[3] = r4;
  msg[4] = r5;
  
  radio.write(msg, sizeof(msg));
  delay(100);
}
int ChangeValue(int x){
  if(x>10 && x<=40) return x=150;
  if(x>40 && x<=70) return x=120;
  if(x>70 && x<=200) return x=90;
  if(x>200 && x<=500) return x=60;
  if(x>500 && x<=1000) return x=30;
  else return x=0;
}
