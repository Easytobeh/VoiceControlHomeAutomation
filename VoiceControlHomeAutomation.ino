
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <VirtualWire.h>
#include "VoiceRecognitionV3.h"

VR myVR(6, 7);   // RX:6, TX:7 you can choose your favourite pins.

uint8_t records[7]; // save record
uint8_t buf[64];

#define load1 13
#define load2 12
#define _TV 11
#define _AC 10
#define _FAN 9

//Define variable for Record address in Voice module memory
#define TV    (0)
#define TVoff   (1)
#define AC    (2)
#define ACoff   (3)
#define FAN   (4)
#define FANoff  (5)


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 3, en = 4, d4 = A3, d5 = A2, d6 = A1, d7 = A0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {

  lcd.begin(16, 2);
  myVR.begin(9600);
  Serial.begin(115200);

  //setup wireless RF Receiver
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_set_rx_pin(8);
  vw_setup(2000);   // Bits per sec

  vw_rx_start();       // Start the receiver PLL running
  pinMode(load1, OUTPUT);
  pinMode(load2, OUTPUT);
  pinMode(_TV, OUTPUT);
  pinMode(_AC, OUTPUT);
  pinMode(_FAN, OUTPUT);

  digitalWrite(load1, HIGH);
  digitalWrite(load2, HIGH);
  digitalWrite(_TV, HIGH);
  digitalWrite(_AC, HIGH);
  digitalWrite(_FAN, HIGH);

  //check for voice recognition module
  if (myVR.clear() == 0) {
    lcd.print("Found VR module");
  } else {
    lcd.print("VR Module");
    lcd.setCursor(0, 1);
    lcd.print("Not Found");
    // Serial.println("Please check connection and restart Arduino.");
    //while (1);
  }

  //Load Records from module
  myVR.load((uint8_t)TV);
  myVR.load((uint8_t)TVoff);
  myVR.load((uint8_t)AC);
  myVR.load((uint8_t)ACoff);
  myVR.load((uint8_t)FAN);
  myVR.load((uint8_t)FANoff);

  // Print a message to the LCD.
 // delay(2000);
  lcd.home();
  lcd.print("Device is Ready");
  //delay(500);
}

void loop() {

  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  String msg = "";
  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    int i;

    //digitalWrite(13, true); // Flash a light to show received good message
    // Message with a good checksum received, dump it.
    Serial.print("Got: ");

    for (i = 0; i < buflen; i++)
    {
      msg += (char)buf[i];
    }
    if (msg == "B1")
      digitalWrite(load1, LOW);

    else if (msg == "B0")
      digitalWrite(load1, HIGH);
    else if (msg == "C1")
      digitalWrite(load2, LOW);

    else if (msg == "C0")
      digitalWrite(load2, HIGH);
  }

  //Listen to VR 
   int captureSpeech;
  captureSpeech = myVR.recognize(buf, 50);
  if (captureSpeech > 0) {
    switch (buf[1]) {
      case TV:
        /** turn on LED */
        digitalWrite(_TV, LOW);
        break;
      case TVoff:
        /** turn on LED */
        digitalWrite(_TV, HIGH);
        break;
      case AC:
        /** turn off LED*/
        digitalWrite(_AC, LOW);
        break;
      case ACoff:
        /** turn off LED*/
        digitalWrite(_AC, HIGH);
        break;
      case FAN:
        /** turn off LED*/
        digitalWrite(_FAN, LOW);
        break;
      case FANoff:
        /** turn off LED*/
        digitalWrite(_FAN, HIGH);
        break;
    }
  }
}
