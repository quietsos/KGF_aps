#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <SPI.h>
#include <Wire.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"




#include "LowPower.h"
#include "serialDisplay.h"

#define CE_PIN 9
#define CSN_PIN 10

unsigned long start_timer;
unsigned long end_timer;





//#include <ArduinoJson.h>

Adafruit_MPU6050 mpu;
//StaticJsonDocument<1000> mpuData;


void mpuTest();
void setAccRange();
void setGyroRange();
void setFilter();
void sleepMode();
void displayData();
void displayDataSingleStruct();
void readData();
void displayJsonData();
void readDataSingleStruct();
void radioTest();
void transmitData();
void readOneWireTemp();
void setRole();  // declare a prototype; definition is found after the loop()



// instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);


int oneWireTemp = 8;
OneWire oneWire(oneWireTemp);
DallasTemperature tempSensor(&oneWire);


//const uint64_t pipe_1 = 0x7878787878LL;
const uint64_t pipe_2 = 0xB3B4B5B6F1LL;



//struct gyroscope {
//  float x, y, z;
//
//} gyroscope;
//
//struct accelerometer {
//  float x, y, z;
//} accelerometer;
//
//struct temperature {
//  float value;
//} temperature;
//


struct PayloadStruct {
  
  unsigned long nodeID;
//  unsigned long payloadID;
  float ax;
  float ay;
  float az;
  float gx;
  float gy;
  float gz;
//  float temp;
  float sensorTemp;
  
};

PayloadStruct payload;





void setup() {
  Serial.begin(115200);
  while (!Serial) {
    // some boards need to wait to ensure access to serial over USB
  }
  Serial.println("....Transmitter Started !....");
  Wire.begin();
  tempSensor.begin();
  
  radioTest();
  setRole();
  mpuTest();
  setAccRange();
  setGyroRange();
  setFilter();

  Serial.println("");
  delay(100);

}

void loop() {
  //  readData();
  readDataSingleStruct();
//  readOneWireTemp();
  displayDataSingleStruct();
  transmitData();
  //  displayData();
  //  displayJsonData();
  delay(100);
  sleepMode();
}


void sleepMode() {
  Serial.println();
  Serial.println("..........Going Sleep Mode..........");
  Serial.println("");
  Serial.println("");
  delay(100);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
}




void radioTest() {

  // initialize the transceiver on the SPI bus
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {}  // hold in infinite loop
  }

  radio.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX is default.
  radio.setPayloadSize(sizeof(payload));  // 2x int datatype occupy 8 bytes

}


void setRole() {

  // set the payload's nodeID & reset the payload's identifying number
//  payload.nodeID = 1;
  payload.nodeID = 2;
//  payload.payloadID = 0;
  payload.ax = 0;
  payload.ay = 0;
  payload.az = 0;
  payload.gx = 0;
  payload.gy = 0;
  payload.gz = 0;
  payload.sensorTemp = 0;

  // Set the address on pipe 0 to the RX node.
  radio.stopListening();  // put radio in TX mode
//  radio.openWritingPipe(pipe_1);
  radio.openWritingPipe(pipe_2);

}


void transmitData(){

  start_timer = micros();                  // start the timer
  bool report = radio.write(&payload, sizeof(payload));  // transmit & save the report
  end_timer = micros();                    // end the timer

  if (report) {
    // payload was delivered

    Serial.println(" Data Delivered Successfully!");
    displayDataSingleStruct();

  } else {
    Serial.println(F("Transmission failed or timed out"));  // payload was not delivered
  }
//  payload.payloadID++;  // increment payload number
  
}


void mpuTest() {
  Serial.println("\n\n......MPU6050 test!......");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("\n\n.....Failed to find MPU6050 chip.....");
    while (1) {
      delay(10);
    }
  }
  Serial.println("\n\n......MPU6050 Found!......");
}

void readDataSingleStruct() {
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  tempSensor.requestTemperatures();

  payload.ax = a.acceleration.x;
  payload.ay = a.acceleration.y;
  payload.az = a.acceleration.z;

  payload.gx = g.gyro.x;
  payload.gy = g.gyro.y;
  payload.gz = g.gyro.z;

  payload.sensorTemp = tempSensor.getTempCByIndex(0);

//  payload.temp = temp.temperature;
//  sensorData.sensorID = 2;


}

void readOneWireTemp(){
  tempSensor.requestTemperatures();
  payload.sensorTemp = tempSensor.getTempCByIndex(0);
}


//void readData() {
//
//  /* Get new sensor events with the readings */
//  sensors_event_t a, g, temp;
//  mpu.getEvent(&a, &g, &temp);
//
//  accelerometer.x = a.acceleration.x;
//  accelerometer.y = a.acceleration.y;
//  accelerometer.z = a.acceleration.z;
//
//  gyroscope.x = g.gyro.x;
//  gyroscope.y = g.gyro.y;
//  gyroscope.z = g.gyro.z;
//
//  temperature.value = temp.temperature;
//
//
//  String gyro,accl;
//  gyro = String(gyroscope.x) + "," + String(gyroscope.y) + "," + String(gyroscope.z);
//  accl = String(accelerometer.x) + "," + String(accelerometer.y) + "," + String(accelerometer.z);
//
//  mpuData["GyroscopeX"] = gyro;
//  mpuData["Accelerometer"] = accl;
//
//
//}

void setAccRange() {

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:
      Serial.println("+-2G");
      break;
    case MPU6050_RANGE_4_G:
      Serial.println("+-4G");
      break;
    case MPU6050_RANGE_8_G:
      Serial.println("+-8G");
      break;
    case MPU6050_RANGE_16_G:
      Serial.println("+-16G");
      break;
  }
}


void setGyroRange() {
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:
      Serial.println("+- 250 deg/s");
      break;
    case MPU6050_RANGE_500_DEG:
      Serial.println("+- 500 deg/s");
      break;
    case MPU6050_RANGE_1000_DEG:
      Serial.println("+- 1000 deg/s");
      break;
    case MPU6050_RANGE_2000_DEG:
      Serial.println("+- 2000 deg/s");
      break;
  }
}

void setFilter() {
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ:
      Serial.println("260 Hz");
      break;
    case MPU6050_BAND_184_HZ:
      Serial.println("184 Hz");
      break;
    case MPU6050_BAND_94_HZ:
      Serial.println("94 Hz");
      break;
    case MPU6050_BAND_44_HZ:
      Serial.println("44 Hz");
      break;
    case MPU6050_BAND_21_HZ:
      Serial.println("21 Hz");
      break;
    case MPU6050_BAND_10_HZ:
      Serial.println("10 Hz");
      break;
    case MPU6050_BAND_5_HZ:
      Serial.println("5 Hz");
      break;
  }
}


//void displayJsonData(){
//  for (int i = 0; i < 3; i++) {
//      serializeJsonPretty(mpuData, Serial);
//    }
//}
//
//void displayData(){
//
//   /* Print out the values */
//  Serial.print("Acceleration X: ");
//  Serial.print(accelerometer.x);
//  Serial.print(", Y: ");
//  Serial.print(accelerometer.y);
//  Serial.print(", Z: ");
//  Serial.print(accelerometer.z);
//  Serial.println(" m/s^2");
//
//  Serial.print("Rotation X: ");
//  Serial.print(gyroscope.x);
//  Serial.print(", Y: ");
//  Serial.print(gyroscope.y);
//  Serial.print(", Z: ");
//  Serial.print(gyroscope.z);
//  Serial.println(" rad/s");
//
//  Serial.print("Temperature: ");
//  Serial.print(temperature.value);
//  Serial.println(" degC");
//
//  Serial.println("");
//  delay(500);
//}

void displayDataSingleStruct() {

  /* Print out the values */

  Serial.println("........MPU Sensor Data............");
  Serial.println();
  Serial.println("                 X    |   Y   |  Z");
  Serial.println();
  Serial.print("Sensor ID    :  ");
  Serial.println(payload.nodeID);

  for (int i = 0; i < 3; i++) {
    Serial.print("Acceleration :  ");

    Serial.print(payload.ax);
    Serial.print("    ");
    Serial.print(payload.ay);
    Serial.print("    ");
    Serial.print(payload.az);

    Serial.println();

    Serial.print("Rotation     : ");
    Serial.print(payload.gx);
    Serial.print("    ");
    Serial.print(payload.gy);
    Serial.print("    ");
    Serial.print(payload.gz);
    Serial.println();
//
//    Serial.print("Temperature  :  ");
//    Serial.print(payload.temp);
//    Serial.println(" degC");


    Serial.print("Temperature(OW):  ");
    Serial.print(payload.sensorTemp);
    Serial.println(" degC");

    Serial.println("");
    delay(500);
  }

}
