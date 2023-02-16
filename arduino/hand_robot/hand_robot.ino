//Receiver Code (Hand)

#include <Servo.h>
#include "RF24.h"

//define the servo name
Servo finger_1;
Servo finger_2;
Servo finger_3;
Servo finger_4;
Servo finger_5;

RF24 radio(9,10);

const uint64_t pipe = 0xE8E8F0F0E1LL;
int msg[5];

void setup(){
  //define the servo input pins
  Serial.begin(9600);
  finger_1.attach(A1);
  finger_2.attach(A2);
  finger_3.attach(A3);
  finger_4.attach(A4);
  finger_5.attach(A5);
  radio.begin();                    //it activates the modem.
  radio.setAutoAck(1);              
  radio.setDataRate(RF24_1MBPS);    // Tốc độ dữ liệu
  radio.setChannel(10);               // Đặt kênh
  radio.openReadingPipe(1, pipe);   //determines the address of our modem which receive data.
  radio.startListening();           //enable receiving data via modem
  }

void loop(){
  Serial.println(radio.available());
  if(radio.available())
  {
    finger_1.write(0); //A1
    finger_2.write(0); //A2
    finger_3.write(0); //A3
    finger_4.write(0); //A4
    finger_5.write(0); //A5 
    while (radio.available())
    {
      radio.read(msg, sizeof(msg));
  
      finger_1.write(msg[0]); //A1
      finger_2.write(msg[1]); //A2
      finger_3.write(msg[2]); //A3
      finger_4.write(msg[3]); //A4
      finger_5.write(msg[4]); //A5   
     
      Serial.println(msg[4]);
      delay(100);
    }
  }
}
