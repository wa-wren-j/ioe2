// Adafruit IO Digital Input Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-digital-input
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

/************************ Example Starts Here *******************************/

// digital pin 16
#define BUTTON_PIN 16
#define CROUCH 14

// button state
bool current = false;
bool last = false;
bool current2 = false;
bool last2 = false;
// set up the 'digital' feed
AdafruitIO_Feed *secfee = io.feed("secfee"); //New!

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  pinMode(CROUCH, INPUT);

  Serial.begin(115200);
  while(! Serial);
  Serial.print("Connecting to Adafruit IO");
  io.connect();
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println(io.statusText());
}

void loop() {
  io.run();
  
  // grab the current state of the button.
  if(digitalRead(BUTTON_PIN) == HIGH){
    current = true;
  }else{
    current = false;
  }
  // return if the value hasn't changed
  if(current == last){
    return;
  }

  if(digitalRead(CROUCH) == HIGH){
    current2 = true;
  }else{
    current2 = false;
  }
  // return if the value hasn't changed
  if(current2 == last2){
    return;
  }

  Serial.print("sending button -> ");
  Serial.println(current);

  //place your specific feed name
   secfee->save(current,current2); //New!

  // store last button state
  last = current;
  last2 = current2;
}
