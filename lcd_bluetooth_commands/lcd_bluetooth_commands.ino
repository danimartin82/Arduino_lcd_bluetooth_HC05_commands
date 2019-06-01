
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>


/***************************************************************************/
// LCD connected to A4, A5, GND, 5V
// https://www.geekfactory.mx/tutoriales/tutoriales-arduino/lcd-16x2-por-i2c-con-arduino/
//
// BT MODULE HC-05:
//https://www.instructables.com/id/How-to-Set-AT-Command-Mode-for-HC-05-Bluetooth-Mod/
//
// RX PIN --------- ARDUINO 11 PIN 
// TX PIN --------- ARDUINO 10 PIN
// EN PIN --------- ARDUINO 9 PIN
// STATUS PIN ------ARDUINO 13 PIN
// VCC PIN --------- ARDUINO 5V
// GND PIN --------- ARDUINO GND
//
//comandos AT:
//http://www.naylampmechatronics.com/blog/24_configuracion-del-modulo-bluetooth-hc-05-usa.html
/***************************************************************************/


/***************************************************************************/
#define I2C_ADDR    0x27


LiquidCrystal_I2C             lcd(I2C_ADDR,2, 1, 0, 4, 5, 6, 7);

SoftwareSerial BTSerial(10, 11); // CONNECT BT RX PIN TO ARDUINO 11 PIN | CONNECT BT TX PIN TO ARDUINO 10 PIN




String data;
static byte ndx = 0;
char command;
char hc_05_status_pin_value =0;
int hc_05_status_pin = 13; 
int hc_05_enable_pin = 9; 
int val;

/***************************************************************************/
void setup()
   {
       lcd.begin (16,2);    // Inicializar el display con 16 caraceres 2 lineas
       lcd.setBacklightPin(3,POSITIVE);
       lcd.setBacklight(HIGH);  



        pinMode(hc_05_status_pin, INPUT);  
        pinMode(hc_05_enable_pin, OUTPUT);  
        digitalWrite(hc_05_enable_pin, HIGH); // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
      //  digitalWrite(9, LOW); // Normal mode

        
        Serial.begin(9600);
        BTSerial.begin(9600 );  // HC-05 default speed in AT command more
        Serial.println("FicoApp demo 1");
        lcd.clear();
        lcd.home();

        lcd.print("FicoApp demo 1");
   }


   /***************************************************************************/
void loop() 
   {

  // Keep reading from HC-05 and send to Arduino Serial Monitor
 // if (BTSerial.available())

  //  char rc = BTSerial.read();
  //  Serial.write(rc);
    //lcd.print(rc);
    val = digitalRead(hc_05_status_pin);
    if (val!=hc_05_status_pin_value)
    {
      hc_05_status_pin_value=val;
      Serial.print("HC-05 STATUS pin changed to : ");
      Serial.println(val);
      lcd.clear();
      lcd.home();
      if (val==0)
      {
          lcd.print("Disconnected");
      }
      else
      {

        lcd.print("Connected");
      }
    }
    
   while(BTSerial.available() > 0)
    {
      command = ((byte)BTSerial.read());
      if(command == ':')
      {
        
        Serial.print("HC-05 Command received: ");
        Serial.println(data);
        lcd.clear();
        lcd.home();
        lcd.print(data);
        data = "";

        BTSerial.write("OK:");
        break;
      }
      else
      {
        data += command;
      }
      delay(1);  
    }

      
}

      //   Serial.write(BTSerial.read());


    
  // Keep reading from Arduino Serial Monitor and send to HC-05
//  if (Serial.available())
//  {
//    BTSerial.write(Serial.read());
//  }
    


