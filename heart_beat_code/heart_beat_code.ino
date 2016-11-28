//Basic adafruitIO example
//post a random value every second



// edit the config.h tab and enter your Adafruit IO credentials

#include "config.h"

#define led_pin 14



int heartRate;
int l0plus;
int l0minus;
int brightness;


int sendRate = 1000;
long lastSend;



// set up the 'myRandoVal' feed
AdafruitIO_Feed *HeartRate = io.feed("HeartRate");

void setup() {
 pinMode(0,INPUT);
 pinMode(13,INPUT);
 pinMode(15,INPUT);
 pinMode(14,OUTPUT);
  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
Serial.print(".");
    delay(500);
 }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {

  io.run();
  
  //pick a random number
  l0plus=digitalRead(15);
  l0minus=digitalRead(13);
  if(l0plus==1||l0minus==1)
  {Serial.println("!");brightness=0;}else
 {heartRate=analogRead(0);

  if(millis()-lastSend>=sendRate)
  {
  // save randVal to the 'myRandoVal' feed on Adafruit IO
  HeartRate->save(heartRate);
  
  //print the value to the serial monitor so you can check if its working
  Serial.print("sending -> ");
  Serial.println(heartRate);
  
  lastSend = millis();

brightness = map(heartRate,0, 1000, 0, 255);

  }
  }analogWrite(led_pin,brightness);
  delay(50);
  }

