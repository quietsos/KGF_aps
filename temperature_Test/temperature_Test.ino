#include <OneWire.h>
#include <DallasTemperature.h>

int oneWireTemp = 8;

OneWire oneWire(oneWireTemp);  

DallasTemperature tempSensor(&oneWire);

void setup(void)
{
  tempSensor.begin();  // Start up the library
  Serial.begin(115200);
}

void loop(void)
{ 
  tempSensor.requestTemperatures(); 

  //print the temperature in Celsius
  Serial.print("Temperature: ");
  Serial.print(tempSensor.getTempCByIndex(0));
  Serial.print((char)176);//shows degrees character
  Serial.print("C  |  ");
  
  //print the temperature in Fahrenheit
  Serial.print((tempSensor.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);
  Serial.print((char)176);//shows degrees character
  Serial.println("F");
  
  delay(500);
}
