#include <Wire.h>
#include <RTClib.h>

// SCL -> A5
// SDA -> A4

RTC_DS3231 rtc;

void initRTC() {
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
}

void restoreTime() {
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void setup() {
  Serial.begin(57600);
  Wire.begin();

  delay(3000); // wait for console opening

  initRTC();
  restoreTime();
}

int previous_second = -1;

void loop() {
  DateTime now = rtc.now();

  if (previous_second != now.second()) {
    previous_second = now.second();
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
  }

}
