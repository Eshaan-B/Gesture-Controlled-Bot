#include <RH_ASK.h>
#include <SPI.h>

int TL = 12;
int BL = 4;
int TR = 13;
int BR = 7;

void forward()
{
  digitalWrite(TL, 1);
  digitalWrite(BL, 0);
  digitalWrite(TR, 1);
  digitalWrite(BR, 0);
}

void Stop()
{
  digitalWrite(TL, 0);
  digitalWrite(BL, 0);
  digitalWrite(TR, 0);
  digitalWrite(BR, 0);
}

void reverse()
{
  digitalWrite(TL, 0);
  digitalWrite(BL, 1);
  digitalWrite(TR, 0);
  digitalWrite(BR, 1);
}

void right()
{
  digitalWrite(TL, 1);
  digitalWrite(BL, 0);
  digitalWrite(TR, 0);
  digitalWrite(BR, 1);
}

void left()
{
  digitalWrite(TL, 0);
  digitalWrite(BL, 1);
  digitalWrite(TR, 1);
  digitalWrite(BR, 0);
}


RH_ASK Radio(2000,2,2,5);// bits per second,reciever pin,transmitter pin, push to talk
void setup()
{
 Serial.begin(9600); // Debugging only
 if (!Radio.init())
 Serial.println("init failed");
}
void loop()
{
 uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
 uint8_t buflen = sizeof(buf);
 if (Radio.recv(buf,&buflen)) // Non-blocking
 {
    String rcv;
    // Message with a good checksum received, dump it.  
       for(int i=0;i<buflen;i++)
      {
        rcv+=(char)buf[i];
      }
    Serial.println(rcv);
 if(rcv=="S")
  Stop();
 else if(rcv=="F")
  forward();
 else if(rcv=="B")
  reverse();
 else if(rcv=="L")
  left();
 else if(rcv=="R")
  right();  

 }
 else Serial.println("Not recieving");


 delay(200);
}
