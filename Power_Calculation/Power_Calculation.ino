int Vpin =A0;
int Val = 0;
float Volt =0 ,I = 0, Power = 0,E = 0;
float R = 10;
void setup() {
  // put your setup code here, to run once:
  pinMode(Vpin,INPUT);
  Serial.begin(9600);
}

void loop() {
  Val = analogRead(Vpin);
  Volt = (1024-Val)*4.88E-3;
  I = Volt/R;
  Power = Val*4.88E-3*I;
  E += Power*0.01;
  Serial.print(Power);
  Serial.print(" mW :");
  Serial.print(E);
  Serial.println(" mJ");
  delay(10);

}
