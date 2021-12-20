#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

const char *ssid     = "Enter in Progaram";//Add SID and Password here
const char *password = "****";

const long utcOffsetInSeconds = 19800;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "in.pool.ntp.org", utcOffsetInSeconds);

void setup(){
  Serial.begin(115200);
  lcd.init();                      
  lcd.backlight();

  WiFi.begin(ssid, password);
  lcd.setCursor(0,0);
  lcd.print("Setting up wifi...");

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
    lcd.setCursor(0,1);
    lcd.print(String("SSID : ")+ ssid);
  }

  timeClient.begin();

    
  lcd.setCursor(0,0);
  lcd.print("Setting time");
}

void loop() {

  if( WiFi.status() != WL_CONNECTED )
  {  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Wifi issue");

    lcd.setCursor(0,1);
    lcd.print("Check router/hotspot");
    //loop();
    return;
  }
  timeClient.update();

  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  Serial.println(timeClient.getFormattedTime());

  lcd.setCursor(0,0);
  lcd.print("Current time");
  lcd.setCursor(0,1);
  String timestr = daysOfTheWeek[timeClient.getDay()] + String(" ")+timeClient.getFormattedTime();
  lcd.print(timestr);
  delay(1000);
  lcd.clear();
}
