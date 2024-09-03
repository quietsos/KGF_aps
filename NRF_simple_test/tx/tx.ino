#include <SPI.h>
#include <nRF24L01.h>
#include "RF24.h"
#include "printf.h"


#define CE_PIN 4
#define CSN_PIN 5


RF24 radio(CE_PIN, CSN_PIN);


const uint64_t pipe_1 = 0x7878787878LL;
const uint64_t pipe_1 = 0xB3B4B5B6F1LL;
const uint64_t pipe_1 = 0xB3B4B5B6CDLL;
const uint64_t pipe_1 = 0xB3B4B5B6A3LL;
const uint64_t pipe_1 = 0xB3B4B5B60FLL;
const uint64_t pipe_1 = 0xB3B4B5B605LL;



struct PayloadStruct {

//  float ax;
//  float ay;
//  float az;
//  float gx;
//  float gy;
//  float gz;
//  float sensorTemp;
//  int sensorNum;
    unsigned long nodeID;
    unsigned long payloadID;


};
PayloadStruct payload;



char role = 'T';


void setRole();  // declare a prototype; definition is found after the loop()
void transmitt();

void setup() {

  Serial.begin(115200);
  while (!Serial) {
    // some boards need to wait to ensure access to serial over USB
  }

  // initialize the transceiver on the SPI bus
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {}  // hold in infinite loop
  }
  else{
    Serial.println(F("radio start working!!"));
  }

 

  // Set the PA Level low to try preventing power supply related problems
  // because these examples are likely run with nodes in close proximity of
  // each other.
  radio.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX is default.

  // save on transmission time by setting the radio to only transmit the
  // number of bytes we need to transmit a float
  radio.setPayloadSize(sizeof(payload));  // 2x int datatype occupy 8 bytes

  // Set the pipe addresses accordingly. This function additionally also
  // calls startListening() or stopListening() and sets the payload's nodeID
  setRole();

  // For debugging info
  // printf_begin();             // needed only once for printing details
  // radio.printDetails();       // (smaller) function that prints raw register values
  // radio.printPrettyDetails(); // (larger) function that prints human readable data



}

void loop() {


  sensorData.ax = random(20, 40);
  sensorData.ay = random(60, 90);
  sensorData.az = random(20, 40);
  sensorData.gx = random(60, 90);
  sensorData.gy = random(20, 40);
  sensorData.gz = random(60, 90);
  sensorData.sensorTemp = random(20, 40);
  delay(10);
  Serial.println("Radio Found");
  radio.write(&sensorData, sizeof(sensorData));
  Serial.println("Data Send");

  dataDisplay();

  delay(1000);
}


void setRole(){

  if(role = 'T'){
    // For the TX node

    // set the payload's nodeID & reset the payload's identifying number
    payload.nodeID = role;
    payload.payloadID = 0;

    // Set the address on pipe 0 to the RX node.
    radio.stopListening();  // put radio in TX mode
    radio.openWritingPipe(pipe_1);
  }
}




void dataDisplay() {
  Serial.print("Sensor ID: "); Serial.println(sensorData.sensorNum);

  Serial.print("AX : "); Serial.println(sensorData.ax);
  Serial.print("AY : "); Serial.println(sensorData.ay);
  Serial.print("AZ : "); Serial.println(sensorData.az);
  Serial.print("GX: "); Serial.println(sensorData.gx);
  Serial.print("GY : "); Serial.println(sensorData.gy);
  Serial.print("GZ : "); Serial.println(sensorData.gz);
  Serial.print("Sensor Temp: "); Serial.println(sensorData.sensorTemp);
  //
  //  Serial.println();

}
