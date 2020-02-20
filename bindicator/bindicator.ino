#include "RTClib.h"

const int greenLED = 5;
const int yellowLED = 6;
const int redLED = 7;
const int blueLED = 8;
const int whiteLED = 12;
const int delayTime = 60000;

const char SUNDAY = "Sunday";
const char MONDAY = "Monday";
const char TUESDAY = "Tuesday";
const char WEDNESDAY = "Wednesday";
const char THURSDAY = "Thursday";
const char FRIDAY = "Friday";
const char SATURDAY = "Saturday";
const char daysOfTheWeek[7][12] = {SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY};

bool green, blue = true;
bool yellow, red, white = false;

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
  boolean switchBools = false;
  DateTime now = rtc.now();
  
  currentTime(now);
  
  if(daysOfTheWeek[now.dayOfTheWeek()] == TUESDAY)
  {
    switchBools = true;
    if(green && blue)
    {
      digitalWrite(greenLED, HIGH);
      digitalWrite(blueLED, HIGH);
    }
    else if(yellow && red && white)
    {
      digitalWrite(yellowLED, HIGH);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, HIGH);
    }
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
    Serial.println("RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0)); // This line sets the RTC with an explicit date & time, for example to set January 21, 2014 at 3am
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
