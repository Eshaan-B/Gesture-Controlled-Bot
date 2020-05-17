

#include <RH_ASK.h>
#include <SPI.h>

RH_ASK Radio(2000,2,2,3);// bits per second,reciever pin,transmitter pin, push to talk

int x;
int y;
int xpin=A0;
int ypin=A1;

void setup()
{
  
  Serial.begin(9600);
  if(!Radio.init())
  Serial.println("Init fail");
}

void loop()
{
 char *msg="hi";
  x=analogRead(xpin);
  y=analogRead(ypin);
  
  if((x<=385)&&(x>=310) && (y<=395) && (y>=310))
    msg="S";
  else if(x>385)
    msg="F";
  else if(x<310)
    msg="B";
  else if(y>395)
   msg="L";
  else if(y<310) 
   msg="R";
   else 
   Serial.println("Not sending");
   
   

  
  Radio.send((uint8_t*)msg, strlen(msg));
  Radio.waitPacketSent();
  Serial.println(msg); 
  
  
  
}
