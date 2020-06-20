#include <LiquidCrystal_I2C.h>
//#include <LiquidCrystal.h>
#include<Wire.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);//Ports
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); 
int Contrast=5;
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
float sensor=A0;
float gas_value;
float threshold = 600;
const int buzzer = 7;
void setup()
{
  mySerial.begin(9600);
pinMode(buzzer, OUTPUT);
analogWrite(6,Contrast);
pinMode(sensor,INPUT);
Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}
void loop()
{
gas_value=analogRead(sensor);
Serial.println(gas_value);
if(gas_value >= threshold)
{
  lcd.setCursor(5, 0);
  lcd.print("Gas      ");
  lcd.setCursor(4, 1);
  lcd.print("Leakage");
  tone(buzzer, 1000);
  delay(1000);        
  noTone(buzzer);     
  delay(100);
  detect();        
}
else{
  lcd.setCursor(5, 0);
  lcd.print("No Gas");
  lcd.setCursor(4, 1);
  lcd.print("Leakage");
  noTone(buzzer);
}
}
int detect()
{
     mySerial.println("AT+CMGF=1");    
     delay(1000);  // Delay of 1 second
     mySerial.println("AT+CMGS=\"+919963014855\"\r");// change to your number where you want to rececive msg
     delay(1000);
     mySerial.println("Lpg gas leak detected!");
     delay(100);
     mySerial.println((char)26);
     delay(1000); 
}
