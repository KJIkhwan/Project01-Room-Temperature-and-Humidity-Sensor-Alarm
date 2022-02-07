// Project01: Room Temperature and Humidity Sensor Alarm
// Arduino Uno - DHT-11 - LCD Display 16x2 

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"; 

 
-------------------------------------------------- // LCD pin
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
const int i2c_addr = 0x3F;                         // Define I2C Address - change if reqiuired
 

#define DHTPIN 1                                   // DHT-11 Output Pin connection
#define DHTTYPE DHT11                              // DHT Type is DHT 11 (AM2302)
#define Buzzer 2                                   // Define some buzzer pin
 
-------------------------------------------------- // Define LCD display connections
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);
 
-------------------------------------------------- // Define Variables
float Humidity;    // Stores humidity value in percent
float RoomTemperature;   // Stores temperature value in Celcius
 
// Setup DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  Serial.begin(9600);                                                
  lcd.begin(16,2);                                  // Set display type as 16 char, 2 rows
  dht.begin();                                      // Initialize DHT-11
  pinMode(Buzzer,OUTPUT);                           // Set buzzer pin mode as an output
}

void loop() {
  
  delay(1000);                                      // Giving some delay to sensor around 1s.
  Humidity = dht.readHumidity();                    // Get Humidity
  RoomTemperature= dht.readTemperature();           // Get Room Temperature

  ------------------------------------------------- // Show the result on serial monitor
  Serial.print("Room Temperature: ");
  Serial.print(RoomTemperature);
  Serial.println(" C");
  Serial.print("Humidity: ");
  Serial.print(Humidity);
  Serial.print(" %");
  --------------------------------------------------// Show the result on LCD display
  
  lcd.clear();                                      // Clear the display
    
  ------------------------------------------------- // Print temperature on top line
  lcd.setCursor(0,0);
  lcd.print("Room Temperature:  ");
  lcd.print(RoomTemperature);
  lcd.print(" C");
  
  ------------------------------------------------- // Print humidity on bottom line
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(Humidity);
  lcd.print(" %");

  ------------------------------------------------- // Set condition warning
  if(RoomTemperature > 35){
    digitalWrite(Buzzer, HIGH);
    delay(100);
    digitalWrite(Buzzer, LOW);
    }
    

}
