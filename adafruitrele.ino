// Adafruit IO Subscription Example
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

#define rele1 16
#define rele2 5
#define rele3 4
#define rele4 14

// set up the 'relay' feed
AdafruitIO_Feed *relay1 = io.feed("relay1");
AdafruitIO_Feed *relay2 = io.feed("relay2");
AdafruitIO_Feed *relay3 = io.feed("relay3");
AdafruitIO_Feed *relay4 = io.feed("relay4");

void setup() {

  pinMode(rele1, OUTPUT);
  pinMode(rele2, OUTPUT);
  pinMode(rele3, OUTPUT);
  pinMode(rele4, OUTPUT);

  // start the serial connection
  Serial.begin(9600);

  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // start MQTT connection to io.adafruit.com
  io.connect();

  // set up a message handler for the count feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  relay1->onMessage(handleMessage);
  relay2->onMessage(handleMessage);
  relay3->onMessage(handleMessage);
  relay4->onMessage(handleMessage);

  // wait for an MQTT connection
  // NOTE: when blending the HTTP and MQTT API, always use the mqttStatus
  // method to check on MQTT connection status specifically
  while(io.mqttStatus() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // Because Adafruit IO doesn't support the MQTT retain flag, we can use the
  // get() function to ask IO to resend the last value for this feed to just
  // this MQTT client after the io client is connected.
  relay1->get();
  relay2->get();
  relay3->get();
  relay4->get();

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  // Because this sketch isn't publishing, we don't need
  // a delay() in the main program loop.

}

// this function is called whenever a 'counter' message
// is received from Adafruit IO. it was attached to
// the counter feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {

  Serial.print("received <- ");
  Serial.println(data->value());

  if(data->isTrue()){
    digitalWrite(rele1, HIGH);
  }
  else{
    digitalWrite(rele1, LOW);
  }


  if(data->isTrue()){
    digitalWrite(rele2, HIGH);
  }
  else{
    digitalWrite(rele2, LOW);
  }


  if(data->isTrue()){
    digitalWrite(rele3, HIGH);
  }
  else{
    digitalWrite(rele3, LOW);
  }


  if(data->isTrue()){
    digitalWrite(rele4, HIGH);
  }
  else{
    digitalWrite(rele4, LOW);
  }

}
