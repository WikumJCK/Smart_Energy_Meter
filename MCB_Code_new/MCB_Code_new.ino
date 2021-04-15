//Importing all Libraries
//For OLED
#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"

#define I2C_ADDRESS 0x3C
#define RST_PIN -1

#include <SPI.h>
#include <Wire.h>

//For RTC
#include <Wire.h>
#include "RTClib.h"

//For SD card
#include <SD.h>
const int CSpin = 10;//Chip select pin of SD card

SSD1306AsciiAvrI2c oled;

RTC_DS1307 rtc; //making RTC object
char daysOfTheWeek[7][12] = {"Sun","Mon","Tue","Wed","Thur","Fri","Sat"};

/*Variables for Calculate Power*/

int Vpin =A0;
int Val = 0;
float Volt =0 ,I = 0;
double Power = 0,E = 0;
float R = 8.5;
String Arr[2] = {"",""};

void setup() {
  pinMode(Vpin,INPUT);//Voltage Sensing pin

  Serial.begin(9600);

  //Initializing Display
  // initialize with the I2C addr 0x3C
	#if RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS, RST_PIN);
  #else // RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  #endif // RST_PIN >= 0
  // Call oled.setI2cClock(frequency) to change from the default frequency.
	
	oled.setFont(System5x7);
  oled.clear();
  oled.set2X();
  oled.println("Smart MCB");
  delay(2000);
	oled.clear();

  //SD initializing
  oled.set1X();
  if(!SD.begin(CSpin))
 {
  Serial.println("SD Card Error");
  oled.println("SD Card Error");
  delay(1000);
  while(true);
 }
 Serial.println("SD Card found");
 oled.println("SD Card found...");
 delay(1000);
 oled.clear();
}

void loop() {
  // put your main code here, to run repeatedly
  getPandE();

}

String getDate(){
   String Date = "Date:";
   String Time = "Time:";
   String d ="";
    DateTime now = rtc.now();
    Date+=String(now.year(), DEC);
    d+=String(now.year(), DEC);
    Date+="/";
    Date+=String(now.month(), DEC);
    d+=String(now.month(), DEC);
    Date+="/";
    Date+=String(now.day(), DEC);
    d+=String(now.day(), DEC);
    Date+=String(" (");
    Date+=String(daysOfTheWeek[now.dayOfTheWeek()]);
    Date+=String(") ");
    Time+=String(now.hour(), DEC);
    Time+=String(':');
    Time+=String(now.minute(), DEC);
    Time+=String(':');
    Time+=String(now.second(), DEC);
    Serial.println(Date);
    Serial.println(Time);
    printDateTime(Date,Time);
    return d;
}

void printDateTime(String Date,String Time){
oled.println(Date);
oled.println("");
}

float getPandE(){
  for (int i=0;i<200;i++){
  Val = analogRead(Vpin);
  Volt = (1024-Val)*4.88E-3;
  I = Volt/R;
  Power = Val*4.88E-3*I;
  E += Power*0.01;
  delay(10);
  }
  oled.clear();
  String date = getDate();
  Arr[0] = "Power : "+String(Power)+" mW ";
  Arr[1] = "Energy: " +String(E)+" J ";
  File dataFile = SD.open(date+".txt",FILE_WRITE);
  dataFile.println(String(E));
  dataFile.close(); 
  oled.println(Arr[0]);
  oled.println(Arr[1]);

  
}
