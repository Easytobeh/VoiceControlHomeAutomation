#include <VirtualWire.h>
#include <LiquidCrystal.h>
#define load1 13
#define load2 12
#define load3 11
#define load4 10
#define load5 9

uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;

const int RS = 3, EN = 4, D4 = A3, D5 = A2, D6 = A1, D7 = A0;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

void setup() {
  vw_setup(2000);         //sets bits per second
  vw_set_rx_pin(8);
  vw_rx_start();
  lcd.begin(16, 2);
  pinMode(load1, OUTPUT);
  pinMode(load2, OUTPUT);
  pinMode(load3, OUTPUT);
  pinMode(load4, OUTPUT);
  pinMode(load5, OUTPUT);

  digitalWrite(load1, HIGH);
  digitalWrite(load2, HIGH);
  digitalWrite(load3, HIGH);
  digitalWrite(load4, HIGH);
  digitalWrite(load5, HIGH);

  while (!vw_get_message(buf, &buflen))
    {
      lcd.clear();
      lcd.print("RF Receiver");
      lcd.setCursor(2,1);
      lcd.print("not found");
      Serial.println("Sensor not found");
      delay(20);
    }
   
    lcd.clear();
    lcd.print("Found Receiver");
    delay(1000);
    lcd.setCursor(3,1);
    lcd.print("READY");
    delay(1000);
    lcd.clear();
}

void loop() {
if (vw_get_message(buf, &buflen))
    {
      int i;
      //char RX_message= buf[i];      
      for (i=0; i<buflen; i++)  
        {
          
            if ()
              { 
                
            
              } 
           else if () 
              {
               
              }
        }
    }



  
  digitalWrite(load1, LOW);
  delay(3000);
  digitalWrite(load1, HIGH);
  delay(2000);

  digitalWrite(load2, LOW);
  delay(3000);
  digitalWrite(load2, HIGH);
  delay(2000);

  digitalWrite(load3, LOW);
  delay(3000);
  digitalWrite(load3, HIGH);
  delay(2000);

  digitalWrite(load4, LOW);
  delay(3000);
  digitalWrite(load4, HIGH);
  delay(2000);

  digitalWrite(load5, LOW);
  delay(3000);
  digitalWrite(load5, HIGH);
  delay(2000);
}
