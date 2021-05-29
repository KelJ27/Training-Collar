// This program is for the Esp32. RECEIVES DATA FROM ARDUINO

// Playing a digital WAV recording repeatadly using the XTronical DAC Audio library
// prints out to the serial monitor numbers counting up showing that the sound plays 
// independently of the main loop
// See www.xtronical.com for write ups on sound, the hardware required and how to make
// the wav files and include them in your code

#include "BluetoothSerial.h"
#include "SoundData.h"
#include "XT_DAC_Audio.h"
#include "TinyGPS++.h"
//#include "SoftwareSerial.h"

#define RXD2 16
#define TXD2 17

BluetoothSerial SerialBT;
char recievedString;
const char sit = 'a';
const char layDown = 'd';
const char getLocation = 'l';
const char lightOn = 'o';
int i;

XT_Wav_Class ForceWithYou(Force);     // create an object of type XT_Wav_Class that is used by 
                                      // the dac audio class (below), passing wav data as parameter.
                                      
XT_DAC_Audio_Class DacAudio(25,0);    // Create the main player class object. 
                                      // Use GPIO 25, one of the 2 DAC pins and timer 0

uint32_t DemoCounter=0;               // Just a counter to use in the serial monitor
                                      // not essential to playing the sound

void setup() {
  Serial.begin(115200);               // Not needed for sound, just to demo printing to the serial
  SerialBT.begin("ESP32");       // Bluetooth device name
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
}


void loop() {
  recievedString = (char)SerialBT.read();

  if(Serial.available())
  {
    SerialBT.write(Serial.read());
  }
  sendSignals();

  //Serial.print("Data Received:");
  //printLocation();
  //delay(200);

}


void sendSignals()
{
  if (SerialBT.available())
  {
    // Print to the app
    SerialBT.print("Recieved: ");
    SerialBT.println(recievedString);

    // Print to the serial monitor
    Serial.print("Recieved: ");
    Serial.println(recievedString);
  }

  if (recievedString == sit)
  {
    SerialBT.println("Sit: ");
    Serial.println("Sit: ");
    for (i = 0; i < 10000; i++)
    {
      playSound();
    }
    i = 0;
  }
  /*else if(recievedString == getLocation)
  {
    Serial.println(getLocation);
  }*/
  
}

void printLocation()
{
  if (SerialBT.available())
  {
    // Print to the app
    SerialBT.print(Serial2.readString());
  }
}
void playSound()
{
  DacAudio.FillBuffer();                // Fill the sound buffer with data
  if (ForceWithYou.Playing == false)    // if not playing,
    DacAudio.Play(&ForceWithYou);       // play it, this will cause it to repeat and repeat...
  Serial.println(DemoCounter++);        // Showing that the sound will play as well as your code running here.
}
