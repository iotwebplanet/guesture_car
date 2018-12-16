//Connect the Transmitter data pin to Arduino pin 12 
//If you don't want to use pin 12 use vw_set_tx_pin(transmit_pin), with transmit_pin being desired pin ,in void setup

/*
 * libary is important for coding
https://github.com/m0/Updated-Arduino-VirtualWire-Library
*/

#include <VirtualWire.h>

int xPin=A0;
int yPin=A1;

int ledPin=13;//led on pin 13 is ON except when transmitter is parallel to the ground

void setup() 
{
  vw_setup(2000);//Bits per second
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);//Initialise the serial connection debugging
}

void loop() 
{
  int xval=analogRead(xPin);
  int yval=analogRead(yPin);
  int x=xval;
  int y=yval;
  Serial.print("xval=");
  Serial.println(xval);
  
  Serial.print("yval=");
  Serial.println(yval); 
  
  //delay(1000); //used to display values after 1s delay
  
  Serial.print("\n");

/*

  if(x<490)  //Change the value for adjusting sensitivity
{
      Serial.println("forward");
      //forward();
       send("f");
    }
else if(x>510)  //Change the value for adjusting sensitivity
{ 
      Serial.println("backward");
      //backward();
      send("a");
    }  
else if(y<490)  //Change the value for adjusting sensitivity
{
      Serial.println("Left");
      // left();
        send("l");
     }
else if(y>510)  //Change the value for adjusting sensitivity
{
     Serial.println("right");
     //right();
     send("r");
    }
else
{
     Serial.println("Stop");
    //stop();
    send("s");
  } 


  delay(200);
  
*/
  
  if ((xval>332 && xval<338) && (yval>345 && yval<354)) //stationary or stop(transmitter parallel to ground)
  {
    digitalWrite(ledPin,LOW);
    send("s");
     Serial.println("Stop");
  } 
  else 
  { 
    if ((xval>290 && xval<335) && (yval>340 && yval<353)) //forward(transmitter tilted forward)
    {
      digitalWrite(ledPin,HIGH);
      send("f");
      Serial.println("forward");
    }
    if ((xval>335 && xval<390) && (yval>343 && yval<352)) //backward(transmitter tilted backward)
    {
      digitalWrite(ledPin,HIGH);
      send("a");
       Serial.println("Back");
      
    }
    if ((xval>332 && xval<340) && (yval>280 && yval<340)) //left(transmitter tilted to left)
    {
      digitalWrite(ledPin,HIGH);
      send("l");
       Serial.println("Left");
     }
     if ((xval>330 && xval<340) && (yval>355 && yval<410))//right(transmitter tilted to right)
    {
      digitalWrite(ledPin,HIGH);
      send("r");
       Serial.println("Right");
    }
  }
  delay(1000);
  
  
}


void send(char *message)//send function definition
{
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx(); // Wait until the whole message is gone
}
