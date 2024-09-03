#include <SPI.h>
#include <Wire.h>
#include <nRF24L01.h>
#include <RF24.h>


void radioTest();
void transmitData();
void displayData();

RF24 radio(10, 9); // (CE, CSN)


const uint64_t pipe_1 = 0xF0F0F0F0AA;

struct MyData {
  float ax;
  float ay;
  float az;
  float gx;
  float gy;
  float gz;
  float temp;
//  float sensorTemp;
  int sensorID;
};

MyData sensorData;







void setup() {

  Serial.begin(115200);
  Wire.begin();


  if (radio.begin()) {
    Serial.println(".......Radio is ready......");
    radio.openWritingPipe(pipe_1);
    radio.setPALevel(RF24_PA_LOW);
    radio.setDataRate(RF24_250KBPS);
    radio.stopListening();
  }
  else {
    Serial.println("....Radio Not Found....");
  }




  //  radio.begin();
  //  radio.openWritingPipe(pipe1);
  //  radio.setPALevel(RF24_PA_LOW);
  //  radio.setDataRate(RF24_250KBPS);
  //  radio.stopListening();



}

void loop() {


  radioTest();
  delay(1000);

}



void radioTest() {


  if (radio.begin()) {
    Serial.println(".......Radio is ready......");
    transmitData();
    displayData();
  }
  else {
    Serial.println("....Radio Not Found....");
  }

}


void transmitData() {

  sensorData.sensorID = 1;
  sensorData.ax = random(1, 10);
  sensorData.ay = random(11, 20);
  sensorData.az = random(21, 30);
  sensorData.gx = random(1, 10);
  sensorData.gy = random(11, 20);
  sensorData.gz = random(21, 30);
  sensorData.temp = random(30, 40);
//  sensorData.sensorTemp = random(30, 40);



  delay(10);
  Serial.println("........Data sent to radio.......");
  delay(10);
  radio.write(&sensorData, sizeof(MyData));

  displayData();
  //
  //  Serial.println();
  //  Serial.print("Sensor ID: ");
  //  Serial.println(sensorData.sensorID);
  //  Serial.print("Accelerometer Data : ");Serial.print("X: "); Serial.print(sensorData.x); Serial.print(" Y: "); Serial.print(sensorData.y); Serial.print(" Z: "); Serial.println(sensorData.z);
  //  Serial.print("gyroscope Data : ");Serial.print("X: "); Serial.print(sensorData.gx); Serial.print(" Y: "); Serial.print(sensorData.gy); Serial.print(" Z: "); Serial.println(sensorData.gz);
  //  Serial.print("Temperature : ");Serial.println(sensorData.temp);
  //  Serial.print("Temperature(OW):  ");Serial.print(sensorData.sensorTemp);Serial.println(" degC");
  //
  //  Serial.println();



}


void displayData() {

  Serial.println();
  Serial.print("Sensor ID: ");
  Serial.println(sensorData.sensorID);
  Serial.print("Accelerometer Data : "); Serial.print("X: "); Serial.print(sensorData.ax); Serial.print(" Y: "); Serial.print(sensorData.ay); Serial.print(" Z: "); Serial.println(sensorData.az);
  Serial.print("gyroscope Data : "); Serial.print("X: "); Serial.print(sensorData.gx); Serial.print(" Y: "); Serial.print(sensorData.gy); Serial.print(" Z: "); Serial.println(sensorData.gz);
  Serial.print("Temperature : "); Serial.println(sensorData.temp);
//  Serial.print("Temperature(OW):  "); Serial.print(sensorData.sensorTemp); Serial.println(" degC");

  Serial.println();

}
