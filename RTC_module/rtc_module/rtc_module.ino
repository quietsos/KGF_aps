#include <RTClib.h>


RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};




void setup() {
  Serial.begin(115200);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  else {
    Serial.println("Find RTC Module!");
  }

  // Uncomment the following lines to set the initial date and time if needed
  rtc.adjust(DateTime(__DATE__, __TIME__));
}




void loop() {
  
  // Read the current date and time from the DS3231
  DateTime now = rtc.now();


  Serial.print("Current Date: ");
  Serial.print(now.year(), DEC);
  Serial.print(":");
  Serial.print(now.month(), DEC);
  Serial.print(":");
  Serial.print(now.day(), DEC);
  Serial.println();
  
  
  Serial.print("Current Time: ");
  Serial.print(now.hour(), DEC);
  Serial.print(":");
  Serial.print(now.minute(), DEC);
  Serial.print(":");
  Serial.print(now.second(), DEC);
  Serial.println();

  Serial.print("Day of Week : ");
  Serial.println(daysOfTheWeek[now.dayOfTheWeek()]);


  Serial.print("Data time : ");
  String dateTime = String(now.day()) +":" + String(now.month()) + ":" + String(now.year()) + "/" + String(now.hour())+ ":" + String(now.minute())+":" + String(now.second())+"/" + String(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.println(dateTime);
  Serial.println();

  delay(1000); // Update every 1 second
}
