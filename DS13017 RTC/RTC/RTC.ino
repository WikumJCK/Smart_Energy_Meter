/*----RTC-DS1307 Clock Module_Arduino Uno----
-----------------Wikum_JCK--------------
--Pin Configuration
VCC-5V
GND-GND
SDA-A4
SCL-A5

Before start make sure that RTCLib library by Adafruit is installed

---Important-
DS1307 contains 24C32 EEPROM of 32bytes(4kB)

*/


//Including Libraries
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc; //making RTC object

//Making 2D array and store days
char daysOftheWeek[7][12] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"}

void setup(){
  Serial.begin(9600);
  delay(3000);//wait untill console open

//Check whether RTC is working 
  if(!rtc.begin()){
    Serial.println("RTC not connected!")
    while(1);
  }

  if(!rtc.isrunning()){
    Serial.println("RTC lost power, lets set the time");
    // Comment out below lines once you set the date & time.
    // Following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
	
    // Following line sets the RTC with an explicit date & time
    // for example to set January 27 2017 at 12:56 you would call:
    // rtc.adjust(DateTime(2017, 1, 27, 12, 56, 0));
  }
}

void loop(){
  DateTime now = rtc.now();
  PrintDateTime()


}

//print Current Date and time
void PrintDateTime(){
    DateTime now = rtc.now();
    Serial.println("Current Date & Time: ");
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
}