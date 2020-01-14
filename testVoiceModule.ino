/**
  ******************************************************************************
    @file    vr_sample_control_led.ino
    @author  JiapengLi
    @brief   This file provides a demostration on
              how to control led by using VoiceRecognitionModule
  ******************************************************************************
    @note:
        voice control led
  ******************************************************************************
    @section  HISTORY

    2013/06/13    Initial version.
*/

#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"

/**
  Connection
  Arduino    VoiceRecognitionModule
   2   ------->     TX
   3   ------->     RX
*/
VR myVR(2, 3);   // 2:RX 3:TX, you can choose your favourite pins.

uint8_t records[7]; // save record
uint8_t buf[64];

#define ledRed 13
#define ledYellow 12
#define ledGreen 11
#define ledBlue 10
#define red    (0)
#define yellow   (1)
#define green (2)
#define blue (3)

/**
  @brief   Print signature, if the character is invisible,
           print hexible value instead.
  @param   buf     --> command length
           len     --> number of parameters
*/
void printSignature(uint8_t *buf, int len)
{
  int i;
  for (i = 0; i < len; i++) {
    if (buf[i] > 0x19 && buf[i] < 0x7F) {
      Serial.write(buf[i]);
    }
    else {
      Serial.print("[");
      Serial.print(buf[i], HEX);
      Serial.print("]");
    }
  }
}

/**
  @brief   Print signature, if the character is invisible,
           print hexible value instead.
  @param   buf  -->  VR module return value when voice is recognized.
             buf[0]  -->  Group mode(FF: None Group, 0x8n: User, 0x0n:System
             buf[1]  -->  number of record which is recognized.
             buf[2]  -->  Recognizer index(position) value of the recognized record.
             buf[3]  -->  Signature length
             buf[4]~buf[n] --> Signature
*/
void printVR(uint8_t *buf)
{
  Serial.println("VR Index\tGroup\tRecordNum\tSignature");

  Serial.print(buf[2], DEC);
  Serial.print("\t\t");

  if (buf[0] == 0xFF) {
    Serial.print("NONE");
  }
  else if (buf[0] & 0x80) {
    Serial.print("UG ");
    Serial.print(buf[0] & (~0x80), DEC);
  }
  else {
    Serial.print("SG ");
    Serial.print(buf[0], DEC);
  }
  Serial.print("\t");

  Serial.print(buf[1], DEC);
  Serial.print("\t\t");
  if (buf[3] > 0) {
    printSignature(buf + 4, buf[3]);
  }
  else {
    Serial.print("NONE");
  }
  Serial.println("\r\n");
}

void setup()
{
  /** initialize */
  myVR.begin(9600);

  Serial.begin(115200);
  Serial.println("Elechouse Voice Recognition V3 Module\r\nControl LED sample");

  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);

  if (myVR.clear() == 0) {
    Serial.println("Recognizer cleared.");
  } else {
    Serial.println("Not find VoiceRecognitionModule.");
    Serial.println("Please check connection and restart Arduino.");
    while (1);
  }

  if (myVR.load((uint8_t)red) >= 0) {
    Serial.println("red loaded");
  }

  if (myVR.load((uint8_t)yellow) >= 0) {
    Serial.println("yellow loaded");
  }
  if (myVR.load((uint8_t)green) >= 0) {
    Serial.println("yellow loaded");
  }
  if (myVR.load((uint8_t)blue) >= 0) {
    Serial.println("yellow loaded");
  }
}

void loop()
{
  int ret;
  ret = myVR.recognize(buf, 50);
  if (ret > 0) {
    switch (buf[1]) {
      case red:
        /** turn on LED */
        digitalWrite(ledRed, HIGH);
        break;
      case yellow:
        /** turn off LED*/
        digitalWrite(ledYellow, HIGH);
        break;
      case green:
        /** turn off LED*/
        digitalWrite(ledGreen, HIGH);
        break;
      case blue:
        /** turn off LED*/
        digitalWrite(ledBlue, HIGH);
        break;
      default:
        {
                    digitalWrite(ledBlue, LOW);
                    digitalWrite(ledGreen, LOW);
                    digitalWrite(ledRed, LOW);
                    digitalWrite(ledYellow, LOW);
        }
        break;
    }
    /** voice recognized */
    printVR(buf);
  }
}
