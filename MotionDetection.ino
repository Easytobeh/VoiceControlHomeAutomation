/*
 * The following sketch is written for A PIR Motion detection device.
 * When motion is detected and light intensity radiating on the LDR is enough to 
 * assume low luminance of the sorrounding, the microcontroller sends a unique sequence of characters
 * through the RF transmitter and received by the Control device for neccessary action.
 * Note the pattern of the message sent; A1, B1, C1,... represents ON code which translates to
 * human presence for respective for motion detector A, B, and C... respectively while A0, B0, C0,... represents code
 * for OFF translating to absence of motion or human presence. This can be changed to any string or character depending 
 * on you.
 */

#include <VirtualWire.h>
#define LDR A2
#define testLed 4
#define pirSensor 8
int temp1,temp2;


void setup() {
  Serial.begin(9600);
  Serial.println("Reading and transmitting data...");
  vw_setup(2000);  //RF transmitter transfer rate: in Bits per second
  //set transmitting data pin
  vw_set_tx_pin(7);
  pinMode(testLed, OUTPUT);
  pinMode(pirSensor,INPUT);
  digitalWrite(testLed,LOW);
  
}

void loop() {
        temp1 = analogRead(LDR); //checks LDR for signal
        temp2 = digitalRead(pirSensor); //checks for motion
        //if environment is dark and motion is detected
        
        if (temp2 == true && temp1 < 200)
            {
            char *message= "C1";
            digitalWrite(testLed,HIGH);              
            vw_send((uint8_t *)message, strlen(message));  //send data to the receiver
            Serial.println(message);
            vw_wait_tx();                                   //wait until whole message is sent
            delay(10000);
            }
        
        //if no signal is detected
        else
          {
            char *message= "C0";
            digitalWrite(testLed,LOW);              
            vw_send((uint8_t *)message, strlen(message));  //send data to the receiver
            Serial.println(message);
            vw_wait_tx();                                   //wait until whole message is sent
            }
         delay(100);
            
} //loop end
