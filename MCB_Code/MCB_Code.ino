#include <SSD1306Ascii.h>
#include <SSD1306AsciiAvrI2c.h>
#include <SSD1306AsciiSoftSpi.h>
#include <SSD1306AsciiSpi.h>
#include <SSD1306AsciiWire.h>
#include <SSD1306init.h>

//Importing all Libraries
//For OLED
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>



//For RTC
#include <Wire.h>
#include "RTClib.h"

//For SD card
#include <SD.h>
const int CSpin = 10;//Chip select pin of SD card

Adafruit_SSD1306 display(-1);

RTC_DS1307 rtc; //making RTC object
char daysOfTheWeek[7][12] = {"Sun","Mon","Tue","Wed","Thur","Fri","Sat"};

/*Variables for Calculate Power*/

int Vpin =A0;
int Val = 0;
float Volt =0 ,I = 0;
double Power = 0,E = 0;
float R = 8.5;
String Arr[2] = {"",""};

// 'ceylon-electricity-board-logo-80B39CEA11-seeklogo', 128x64px
const unsigned char StartLogo [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x30, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x3c, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xc1, 0xf0, 0x3e, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0x81, 0xfc, 0x3e, 0x06, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0xfc, 0x3f, 0x0f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0xfe, 0x3f, 0x0f, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x7e, 0x3f, 0x0f, 0x83, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf3, 0xf8, 0x70, 0x01, 0x1f, 0x81, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xe3, 0xfc, 0x40, 0x00, 0x1f, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xc1, 0xfe, 0x18, 0xf1, 0x0f, 0x82, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x80, 0xfc, 0x7c, 0xf3, 0xc7, 0x06, 0x3e, 0x0c, 0x61, 0xc7, 0x01, 0x01, 
	0xff, 0xff, 0xff, 0xff, 0x80, 0x71, 0xfc, 0x43, 0xf1, 0x0f, 0x1c, 0x0c, 0x21, 0x87, 0x01, 0x01, 
	0xff, 0xff, 0xff, 0xff, 0x00, 0x33, 0xfc, 0x07, 0xfc, 0x1f, 0x1c, 0x3c, 0x21, 0x83, 0x11, 0xc7, 
	0xff, 0xff, 0xff, 0xfe, 0x00, 0x07, 0xfc, 0x03, 0xfe, 0x3f, 0x0e, 0x0c, 0x01, 0x13, 0x01, 0xc7, 
	0xff, 0xff, 0xff, 0xfe, 0x3e, 0x5f, 0xf0, 0x80, 0xff, 0x3f, 0x07, 0x84, 0x01, 0x03, 0x03, 0xc7, 
	0xff, 0xff, 0xff, 0xfc, 0x7f, 0x9f, 0x86, 0x04, 0x1f, 0x9f, 0x04, 0x44, 0x81, 0x01, 0x11, 0xc7, 
	0xff, 0xff, 0xff, 0xfc, 0xff, 0x3f, 0x00, 0x00, 0x0f, 0xde, 0x00, 0x0c, 0x80, 0x01, 0x11, 0xc7, 
	0xff, 0xff, 0xff, 0xf9, 0xfe, 0x7f, 0x3c, 0x0f, 0x8f, 0xce, 0x02, 0x1c, 0x9a, 0x39, 0x18, 0xc7, 
	0xff, 0xff, 0xff, 0xf8, 0x7e, 0xff, 0x3e, 0x0f, 0x8f, 0xe4, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xf8, 0x1c, 0xff, 0x3e, 0x0f, 0x8f, 0xf4, 0x19, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xf0, 0x05, 0xff, 0xf0, 0x00, 0xff, 0xf4, 0xf9, 0xfe, 0x31, 0xe3, 0x83, 0xff, 
	0xff, 0xff, 0xff, 0xf0, 0x01, 0xff, 0x82, 0x08, 0x3f, 0xf3, 0xf9, 0xfc, 0x31, 0x81, 0x80, 0xff, 
	0xff, 0xff, 0xff, 0xf0, 0x09, 0xff, 0x00, 0x00, 0x0f, 0xfb, 0xf8, 0xfc, 0x21, 0x19, 0x98, 0xff, 
	0xff, 0xff, 0xff, 0xe0, 0xfb, 0xff, 0x3e, 0x0f, 0x8f, 0xf9, 0xf8, 0xfc, 0x01, 0x1f, 0x81, 0xff, 
	0xff, 0xff, 0xff, 0xe1, 0xfb, 0xff, 0x3e, 0x0f, 0x8f, 0xf9, 0xf0, 0xfc, 0x01, 0x1f, 0x80, 0xff, 
	0xff, 0xff, 0xff, 0xe3, 0xf3, 0xff, 0x3c, 0x07, 0x8f, 0xf9, 0xe0, 0xfc, 0x01, 0x18, 0x98, 0xff, 
	0xe1, 0xc0, 0x80, 0xe7, 0xf3, 0xff, 0xe0, 0x00, 0x7f, 0xfd, 0xc0, 0xfc, 0x09, 0x81, 0x80, 0xff, 
	0xc0, 0xc0, 0x80, 0xe7, 0xf3, 0xff, 0x00, 0x00, 0x1f, 0xfd, 0x00, 0x7c, 0x49, 0xc1, 0x81, 0xff, 
	0x8c, 0xcf, 0x8c, 0xe7, 0xf7, 0xff, 0x00, 0x00, 0x0f, 0xfd, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 
	0x8f, 0xc0, 0x80, 0xe0, 0x17, 0xff, 0x3e, 0x0f, 0x8f, 0xfd, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 
	0x8f, 0xc0, 0x80, 0xe0, 0x17, 0xff, 0x3e, 0x0f, 0x8f, 0xfd, 0xfc, 0x7f, 0xff, 0xff, 0xff, 0xff, 
	0x8c, 0xcf, 0x8c, 0x60, 0x17, 0xff, 0x3e, 0x0f, 0xcf, 0xfd, 0xfc, 0x7f, 0xff, 0xff, 0xff, 0xff, 
	0xc0, 0xc0, 0x80, 0xe0, 0x33, 0xff, 0xfe, 0x07, 0xff, 0xfd, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xe1, 0xc0, 0x80, 0xe0, 0xf3, 0xff, 0xfe, 0x07, 0xff, 0xf9, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xe1, 0xfb, 0xff, 0xfe, 0x97, 0xff, 0xf9, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xe1, 0xfb, 0xff, 0xfc, 0x17, 0xff, 0xf9, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xf3, 0xfb, 0xff, 0xfc, 0x47, 0xff, 0xfa, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xf3, 0xf9, 0xff, 0xfc, 0xe7, 0xff, 0xf0, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xf3, 0xe5, 0xff, 0xf8, 0xe7, 0xff, 0xf4, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xfb, 0x80, 0xff, 0xf9, 0xf3, 0xff, 0xf7, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xf8, 0x06, 0xff, 0xf8, 0x03, 0xff, 0xe7, 0xe1, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xf8, 0x06, 0x7f, 0xf8, 0xe3, 0xff, 0xcf, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xfc, 0x0f, 0x3f, 0xfa, 0x4b, 0xff, 0xdf, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xfc, 0x1f, 0xbf, 0xf3, 0x19, 0xff, 0x9f, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xfe, 0x1f, 0x8f, 0xf7, 0x19, 0xff, 0x07, 0x87, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xfe, 0x1f, 0xcf, 0xf6, 0x4d, 0xfe, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x1f, 0x03, 0xe4, 0xe5, 0xfc, 0xc0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x1e, 0x19, 0xe1, 0xf5, 0xf1, 0xe0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x8c, 0x1c, 0x63, 0xf1, 0xe3, 0xf0, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xc0, 0x3f, 0x07, 0xfd, 0x0f, 0xf8, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xe0, 0x3f, 0x81, 0xf8, 0x07, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf0, 0x3f, 0x10, 0x01, 0xc1, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x3f, 0x1f, 0x8f, 0xe0, 0x43, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xfc, 0x1e, 0x1f, 0x8f, 0xe0, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xfe, 0x0e, 0x1f, 0x87, 0xe0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0x84, 0x0f, 0x83, 0xf0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x0f, 0x81, 0xf0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x07, 0x80, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};


void setup() {
  pinMode(Vpin,INPUT);//Voltage Sensing pin

  Serial.begin(9600);

  //Initializing Display
  // initialize with the I2C addr 0x3C
	display.begin(SSD1306_SWITCHCAPVCC, 0x78);  

	// Clear the buffer.
	display.clearDisplay();

	// Display bitmap
	display.drawBitmap(0, 0, StartLogo, 128, 64, WHITE);
	display.display();
  delay(5000);
  display.clearDisplay();
  display.display();

  //SD initializing
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  
  if(!SD.begin(CSpin))
 {
  Serial.println("SD Card Error");
  display.println("SD Card Error");
  display.display();
  delay(1000);
  while(true);
 }
 Serial.println("SD Card found");
 display.println("SD Card found...");
 display.display();
 delay(1000);
 display.clearDisplay();
}

void loop() {
  // put your main code here, to run repeatedly
  getPandE();

}

String getDate(){
   String Date = "Date:";
   String Time = "Time:";
    DateTime now = rtc.now();
    Date+=String(now.year(), DEC);
    Date+=String('/');
    Date+=String(now.month(), DEC);
    Date+=String('/');
    Date+=String(now.day(), DEC);
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
    return String(Date);
}

void printDateTime(String Date,String Time){
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(0,0);
display.println(Date);
display.display();
  
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
  display.clearDisplay();
  String date = getDate();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  Arr[0] = "Power : "+String(Power)+" mW ";
  Arr[1] = "Energy: " +String(E)+" J ";
  File dataFile = SD.open("Today.txt",FILE_WRITE);
  dataFile.println(date+" "+String(E));
  dataFile.close(); 
  display.setCursor(0,20);
  display.println(Arr[0]);
  display.println(Arr[1]);
  display.display();
  
}
