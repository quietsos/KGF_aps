#include <SPI.h>
#include <Wire.h>
#include <nRF24L01.h>
#include <RF24.h>

int recvData();
void displayData();
void radioTest();

RF24 radio(4, 5);  //(CE, CSN)

const uint64_t pipe_1 = 0xF0F0F0F0AA;
const uint64_t pipe_2 = 0xF0F0F0F0AB;


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
  radioTest();


}

void loop() {


  if (recvData()) {
    Serial.println("Data Received: ");
    displayData();
  }
  else {
    Serial.println("Data Not Received!");
  }

  delay(1000);
}

void radioTest() {

  Serial.println("Receiver Started....");

  radio.begin();
  Serial.println(".......Radio is ready......");
  radio.begin();
  radio.openReadingPipe(1, pipe_1);
  radio.openReadingPipe(2, pipe_2);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();

}


int recvData()
{
  Serial.println("...Checking Radio Availability...");
  if (radio.available() )
  {
    Serial.print("....Radio is Connected!.... : "); Serial.println(radio.available());
    radio.read(&sensorData, sizeof(sensorData));
    Serial.println("Data Received Done.");

    return 1;
  }
  Serial.println("....Radio Not Available....");
  return 0;
}





void displayData() {

  if (sensorData.sensorID == 1) {
    Serial.print("Sensor ID: ");
    Serial.println(sensorData.sensorID);
    Serial.print("Accelerometer Data : "); Serial.print("X: "); Serial.print(sensorData.ax); Serial.print(" Y: "); Serial.print(sensorData.ay); Serial.print(" Z: "); Serial.println(sensorData.az);
    Serial.print("gyroscope Data : "); Serial.print("X: "); Serial.print(sensorData.gx); Serial.print(" Y: "); Serial.print(sensorData.gy); Serial.print(" Z: "); Serial.println(sensorData.gz);
    Serial.print("Temperature : "); Serial.println(sensorData.temp);
    //    Serial.print("Temperature(OW):  "); Serial.print(sensorData.sensorTemp); Serial.println(" degC");
  }

  if (sensorData.sensorID == 2) {
    Serial.print("Sensor ID: ");
    Serial.println(sensorData.sensorID);
    Serial.print("Accelerometer Data : "); Serial.print("X: "); Serial.print(sensorData.ax); Serial.print(" Y: "); Serial.print(sensorData.ay); Serial.print(" Z: "); Serial.println(sensorData.az);
    Serial.print("gyroscope Data : "); Serial.print("X: "); Serial.print(sensorData.gx); Serial.print(" Y: "); Serial.print(sensorData.gy); Serial.print(" Z: "); Serial.println(sensorData.gz);
    Serial.print("Temperature : "); Serial.println(sensorData.temp);
    //    Serial.print("Temperature(OW):  "); Serial.print(sensorData.sensorTemp); Serial.println(" degC");

  }

}
