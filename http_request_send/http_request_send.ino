
#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2

void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);

  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  mySerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  mySerial.println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();
  mySerial.println("AT+SAPBR=3,1,Contype,GPRS");//Setting connection Mode to gprs
  updateSerial();
  mySerial.println("AT+SAPBR=3,1,APN,dialogbb");// add the apn(acess point name)
  updateSerial();
  mySerial.println("AT+SAPBR=1,1");//initialize IP adress
  updateSerial();
  mySerial.println("AT+SAPBR=2,1");//Show the IP
  updateSerial();
  delay(1000);
  mySerial.println("AT+HTTPTERM");//close current HTTP connections
  updateSerial();
  mySerial.println("AT+HTTPINIT");//initialize HTTP connection
  updateSerial();
  mySerial.println("AT+HTTPPARA=CID,1");//Default code
  updateSerial();
  mySerial.println("AT+HTTPPARA=URL,http://124.43.34.36/hp1/s/e.php?i=a2341b871&d=18032021&c=156");//url
  updateSerial();
  mySerial.println("AT+HTTPPARA=CONTENT,application/x-www-form-urlencoded");//Encoding the URL
  updateSerial();
  mySerial.println("AT+HTTPACTION=1");//Sending a set request
  updateSerial();
  mySerial.println("AT+HTTPREAD");//Read Http retun value
  updateSerial();
  mySerial.println("AT+HTTPTERM");//Terminate HTTP connection
  delay(1000);
  updateSerial();
  mySerial.println("AT+SAPBR=0,1");//stop net connction mode(Closing IP)
  updateSerial();
}

void loop()
{
  updateSerial();
}

void updateSerial()
{
  delay(500);
  while (Serial.available())
  {
    mySerial.write(Serial.read()); //Forward what Serial received to Software Serial Port
  }
  while (mySerial.available())
  {
    Serial.write(mySerial.read()); //Forward what Software Serial received to Serial Port
  }
}
