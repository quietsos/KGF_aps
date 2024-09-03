#include <SPI.h>
#include <Wire.h>
#include <nRF24L01.h>
#include <RF24.h>

void displayData();
void radioCheck();

RF24 radio(4, 5);  //(CE, CSN)

const uint64_t pipe_6 = 0xF0F0F0F064;
const uint64_t pipe_5 = 0xF0F0F0F065;
const uint64_t pipe_1 = 0xF0F0F0F066;
const uint64_t pipe_2 = 0xF0F0F0F067;
const uint64_t pipe_3 = 0xF0F0F0F068;
const uint64_t pipe_4 = 0xF0F0F0F069;



struct sensor
{

  float ax;
  float ay;
  float az;
  float gx;
  float gy;
  float gz;
  float sensorTemp;
  int sensorNum;
};
sensor sensorData;



void setup() {

  Serial.begin(115200);
  Serial.println(" Starting Receiver ");


  radio.begin();
  Serial.print("Radio Status: ");
  Serial.println(radio.begin());
  Serial.println("Receiver Started....");
  radio.openReadingPipe(1, pipe_1);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
}




void loop() {

  radioCheck();

  delay(1000);
}

void radioCheck() {

  Serial.print("Radio Check : ");
  Serial.println(radio.available());
  if (radio.available()) {

    Serial.println("Radio Found. ");

    radio.read(&sensorData, sizeof(sensorData));
    displayData();
    Serial.println("Data Received: ");

  }
  else {
    Serial.println("Data Not Received!");
  }
}


void displayData() {

  if (sensorData.sensorNum == 1) {
    Serial.print("Sensor ID: "); Serial.println(sensorData.sensorNum);

    Serial.print("AX : "); Serial.println(sensorData.ax);
    Serial.print("AY : "); Serial.println(sensorData.ay);
    Serial.print("AZ : "); Serial.println(sensorData.az);
    Serial.print("GX: "); Serial.println(sensorData.gx);
    Serial.print("GY : "); Serial.println(sensorData.gy);
    Serial.print("GZ : "); Serial.println(sensorData.gz);
    Serial.print("Sensor Temp:  : "); Serial.println(sensorData.sensorTemp);

  }

  if (sensorData.sensorNum == 2) {
    Serial.print("Sensor ID: "); Serial.println(sensorData.sensorNum);

    Serial.print("AX : "); Serial.println(sensorData.ax);
    Serial.print("AY : "); Serial.println(sensorData.ay);
    Serial.print("AZ : "); Serial.println(sensorData.az);
    Serial.print("GX: "); Serial.println(sensorData.gx);
    Serial.print("GY : "); Serial.println(sensorData.gy);
    Serial.print("GZ : "); Serial.println(sensorData.gz);
    Serial.print("Sensor Temp:  : "); Serial.println(sensorData.sensorTemp);

  }
  if (sensorData.sensorNum == 3) {
    Serial.print("Sensor ID: "); Serial.println(sensorData.sensorNum);

    Serial.print("AX : "); Serial.println(sensorData.ax);
    Serial.print("AY : "); Serial.println(sensorData.ay);
    Serial.print("AZ : "); Serial.println(sensorData.az);
    Serial.print("GX: "); Serial.println(sensorData.gx);
    Serial.print("GY : "); Serial.println(sensorData.gy);
    Serial.print("GZ : "); Serial.println(sensorData.gz);
    Serial.print("Sensor Temp:  : "); Serial.println(sensorData.sensorTemp);

  }
  if (sensorData.sensorNum == 4) {
    Serial.print("Sensor ID: "); Serial.println(sensorData.sensorNum);

    Serial.print("AX : "); Serial.println(sensorData.ax);
    Serial.print("AY : "); Serial.println(sensorData.ay);
    Serial.print("AZ : "); Serial.println(sensorData.az);
    Serial.print("GX: "); Serial.println(sensorData.gx);
    Serial.print("GY : "); Serial.println(sensorData.gy);
    Serial.print("GZ : "); Serial.println(sensorData.gz);
    Serial.print("Sensor Temp:  : "); Serial.println(sensorData.sensorTemp);

  }
  if (sensorData.sensorNum == 5) {
    Serial.print("Sensor ID: "); Serial.println(sensorData.sensorNum);

    Serial.print("AX : "); Serial.println(sensorData.ax);
    Serial.print("AY : "); Serial.println(sensorData.ay);
    Serial.print("AZ : "); Serial.println(sensorData.az);
    Serial.print("GX: "); Serial.println(sensorData.gx);
    Serial.print("GY : "); Serial.println(sensorData.gy);
    Serial.print("GZ : "); Serial.println(sensorData.gz);
    Serial.print("Sensor Temp:  : "); Serial.println(sensorData.sensorTemp);

  }
  if (sensorData.sensorNum == 6) {
    Serial.print("Sensor ID: "); Serial.println(sensorData.sensorNum);

    Serial.print("AX : "); Serial.println(sensorData.ax);
    Serial.print("AY : "); Serial.println(sensorData.ay);
    Serial.print("AZ : "); Serial.println(sensorData.az);
    Serial.print("GX: "); Serial.println(sensorData.gx);
    Serial.print("GY : "); Serial.println(sensorData.gy);
    Serial.print("GZ : "); Serial.println(sensorData.gz);
    Serial.print("Sensor Temp:  : "); Serial.println(sensorData.sensorTemp);

  }

}
