// This program is for the Arduino Uno

#include <Adafruit_SSD1306.h>
#include <splash.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <Wire.h>

#include "TinyGPS++.h"
#include "SoftwareSerial.h"
#include "BatteryData.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
 
#define GreenLED 12 
#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//#if (SSD1306_LCDHEIGHT != 64)

//#error("Height incorrect, please fix Adafruit_SSD1306.h!");
//#endif

#define Width 25
#define Height 16

SoftwareSerial serial_connection(11, 10); // RX = pin 10 and TX = pin 11 
TinyGPSPlus gps;

#define BATTERY_WIDTH  64
#define BATTERY_HEIGHT  20

int analogValue;
const float vpp = 0.0043988269794721407624633431085;
float batteryVoltage;
float maxBatteryLife = 5.00;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  //try 0x7A
  Serial.begin(9600);
  serial_connection.begin(9600);
  Serial.println("GPS Start");
  pinMode(GreenLED, OUTPUT);
  display.clearDisplay();
  display.display();
}


void loop() {
  runGPS();
  drawBattery(batteryLife());
}

void runGPS()
{
  while(serial_connection.available())
  {
    gps.encode(serial_connection.read());
  }
  if(gps.location.isUpdated())
  {
    // Get GPS location data
    digitalWrite(GreenLED, HIGH);
    Serial.println("Satellite Count:");
    Serial.println(gps.satellites.value());
    Serial.println("Latitude:");
    Serial.println(gps.location.lat(), 6);
    Serial.println("Longitude:");
    Serial.println(gps.location.lng(), 6);
    Serial.println("Speed MPH:");
    Serial.println(gps.speed.mph());
    Serial.println("Altitude Feet:");
    Serial.println(gps.altitude.feet());
    Serial.println("");
    delay(15000);
    digitalWrite(GreenLED, LOW);
  }
  /*else
  {
    Serial.println("GPS is not connected");
    //delay(5000);
  }*/
}

void drawBattery(float batteryLife)
{
  if(batteryLife <= maxBatteryLife && batteryLife >= 4.35)
  {
    display.clearDisplay();
    //display.drawPixel(15, 10, WHITE);
    display.drawBitmap(35, 8, battery_100, BATTERY_WIDTH,BATTERY_HEIGHT, WHITE);
    display.display();
  }
  else if(batteryLife <= 4.35 && batteryLife >= 4.20)
  {
    display.clearDisplay();
    //display.drawPixel(15, 10, WHITE);
    display.drawBitmap(35, 8, battery_83, BATTERY_WIDTH,BATTERY_HEIGHT, WHITE);
    display.display(); 
  }
  else if(batteryLife <= 4.20 && batteryLife >= 4.05)
  {
    display.clearDisplay();
    //display.drawPixel(15, 10, WHITE);
    display.drawBitmap(35, 8, battery_66, BATTERY_WIDTH,BATTERY_HEIGHT, WHITE);
    display.display();
  }
  else if(batteryLife <= 4.05 && batteryLife >= 3.90)
  {
    display.clearDisplay();
    //display.drawPixel(15, 10, WHITE);
    display.drawBitmap(35, 8, battery_50, BATTERY_WIDTH,BATTERY_HEIGHT, WHITE);
    display.display();
  }
  else if(batteryLife <= 3.90 && batteryLife >= 3.75)
  {
    display.clearDisplay();
    //display.drawPixel(15, 10, WHITE);
    display.drawBitmap(35, 8, battery_33, BATTERY_WIDTH,BATTERY_HEIGHT, WHITE);
    display.display();
  }
  else if(batteryLife <= 3.75 && batteryLife >= 3.60)
  {
    display.clearDisplay();
    //display.drawPixel(15, 10, WHITE);
    display.drawBitmap(35, 8, battery_16, BATTERY_WIDTH,BATTERY_HEIGHT, WHITE);
    display.display();
  }
  else
  {
    display.clearDisplay();
    //display.drawPixel(15, 10, WHITE);
    display.drawBitmap(35, 8, battery_0, BATTERY_WIDTH,BATTERY_HEIGHT, WHITE);
    display.display();
  }
}

float batteryLife()
{
  analogValue = analogRead(A0);
  batteryVoltage = (analogValue * vpp);
  Serial.println(batteryVoltage);

  return batteryVoltage;
}
