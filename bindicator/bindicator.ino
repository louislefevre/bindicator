#include "RTClib.h"

const int greenLED = 5;
const int yellowLED = 6;
const int redLED = 7;
const int blueLED = 8;
const int whiteLED = 12;
const int delayTime = 60000;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

bool green = true; // Green bin (non-recyclable)
bool blue = true; // Blue bin (paper)
bool red = true; // Brown caddy (food waste)
bool yellow = false; // Brown bin (garden waste)
bool white = false; // White bin (plastics)

boolean switchBools = false;

RTC_DS3231 rtc;

void setup()
{
  Serial.begin(9600);
  delay(3000);
  pinSetup();
  rtcDiagnostics();
}

void loop()
{
  DateTime now = rtc.now();
  
  currentTime(now);

  if(now.dayOfTheWeek() == 1)
  {
    switchBools = true;

    if(green)
      digitalWrite(greenLED, HIGH);
    if(blue)
      digitalWrite(blueLED, HIGH);
    if(yellow)
      digitalWrite(yellowLED, HIGH);
    if(red)
      digitalWrite(redLED, HIGH);
    if(white)
      digitalWrite(whiteLED, HIGH);
  }
  else
  {
    if(switchBools)
    {
      green = !green;
      blue = !blue;
      yellow = !yellow;
      red = !red;
      white = !white;
      switchBools = false;
    }
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
    digitalWrite(whiteLED, LOW);
  }

  delay(delayTime);
}

void pinSetup()
{
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(whiteLED, OUTPUT);
}

void rtcDiagnostics()
{
  if(!rtc.begin())
  {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if(rtc.lostPower())
  {
    Serial.println("RTC lost power, setting the time...");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void currentTime(DateTime now)
{
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
