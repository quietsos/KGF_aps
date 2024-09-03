#include <SPI.h>
#include "printf.h"
#include "RF24.h"

#define CE_PIN 4
#define CSN_PIN 5
// instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);



uint64_t address[6] = { 0x7878787878LL,
                        0xB3B4B5B6F1LL,
                        0xB3B4B5B6CDLL,
                        0xB3B4B5B6A3LL,
                        0xB3B4B5B60FLL,
                        0xB3B4B5B605LL
                      };


char role = 'R';  // integers 0-5 = TX node; character 'R' or integer 82 = RX node


// Make a data structure to use as a payload.
struct PayloadStruct {
  unsigned long nodeID;
  unsigned long payloadID;
  float ax;
  float ay;
  float az;
  float gx;
  float gy;
  float gz;
  float sensorTemp;
};
PayloadStruct payload;



void setRole();  // declare a prototype; definition is found after the loop()
void radioTest();
void receivedData();

void setup() {

  Serial.begin(115200);
  while (!Serial) {
    // some boards need to wait to ensure access to serial over USB
  }

  radioTest();
  setRole();

} 

void loop() {

  receivedData();


}  // loop


void radioTest(){
    // initialize the transceiver on the SPI bus
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {}  // hold in infinite loop
  }

  Serial.println(F("Base Station Multi Receiver"));
  radio.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX is default.
  radio.setPayloadSize(sizeof(payload));  // 2x int datatype occupy 8 bytes
  
  
}



void setRole() {
  if (role == 'R') {
    // For the RX node

    // Set the addresses for all pipes to TX nodes
    for (uint8_t i = 0; i < 6; ++i) {
      radio.openReadingPipe(i, address[i]);
    }
    radio.startListening();  // put radio in RX mode

  }
}


void receivedData(){
  if (role == 'R') {
    // This device is the RX node

    uint8_t pipe;
    if (radio.available(&pipe)) {              // is there a payload? get the pipe number that recieved it
      uint8_t bytes = radio.getPayloadSize();  // get the size of the payload
      radio.read(&payload, bytes);             // fetch payload from FIFO


      if (payload.nodeID == 0) {
        Serial.print(F("Received From Node(0): "));
        Serial.print(bytes);  // print the size of the payload
        Serial.print(F(" bytes on pipe "));
        Serial.print(pipe);  // print the pipe number
        Serial.print(F(" from node "));
        Serial.print(payload.nodeID);  // print the payload's origin
        Serial.print(F(". PayloadID: "));
        Serial.println(payload.payloadID);  // print the payload's number
        Serial.print("AX : "); Serial.println(payload.ax);
        Serial.print("AY : "); Serial.println(payload.ay);
        Serial.print("AZ : "); Serial.println(payload.az);
        Serial.print("GX: "); Serial.println(payload.gx);
        Serial.print("GY : "); Serial.println(payload.gy);
        Serial.print("GZ : "); Serial.println(payload.gz);
        Serial.print("Sensor Temp: "); Serial.println(payload.sensorTemp);
      }

      if (payload.nodeID == 1) {
        Serial.print(F("Received From Node(1): "));
        Serial.print(bytes);  // print the size of the payload
        Serial.print(F(" bytes on pipe "));
        Serial.print(pipe);  // print the pipe number
        Serial.print(F(" from node "));
        Serial.print(payload.nodeID);  // print the payload's origin
        Serial.print(F(". PayloadID: "));
        Serial.println(payload.payloadID);  // print the payload's number
        Serial.print("AX : "); Serial.println(payload.ax);
        Serial.print("AY : "); Serial.println(payload.ay);
        Serial.print("AZ : "); Serial.println(payload.az);
        Serial.print("GX: "); Serial.println(payload.gx);
        Serial.print("GY : "); Serial.println(payload.gy);
        Serial.print("GZ : "); Serial.println(payload.gz);
        Serial.print("Sensor Temp: "); Serial.println(payload.sensorTemp);
      }
      if (payload.nodeID == 2) {
        Serial.print(F("Received From Node(2): "));
        Serial.print(bytes);  // print the size of the payload
        Serial.print(F(" bytes on pipe "));
        Serial.print(pipe);  // print the pipe number
        Serial.print(F(" from node "));
        Serial.print(payload.nodeID);  // print the payload's origin
        Serial.print(F(". PayloadID: "));
        Serial.println(payload.payloadID);  // print the payload's number
        Serial.print("AX : "); Serial.println(payload.ax);
        Serial.print("AY : "); Serial.println(payload.ay);
        Serial.print("AZ : "); Serial.println(payload.az);
        Serial.print("GX: "); Serial.println(payload.gx);
        Serial.print("GY : "); Serial.println(payload.gy);
        Serial.print("GZ : "); Serial.println(payload.gz);
        Serial.print("Sensor Temp: "); Serial.println(payload.sensorTemp);
      }
      if (payload.nodeID == 3) {
        Serial.print(F("Received From Node(3): "));
        Serial.print(bytes);  // print the size of the payload
        Serial.print(F(" bytes on pipe "));
        Serial.print(pipe);  // print the pipe number
        Serial.print(F(" from node "));
        Serial.print(payload.nodeID);  // print the payload's origin
        Serial.print(F(". PayloadID: "));
        Serial.println(payload.payloadID);  // print the payload's number
        Serial.print("AX : "); Serial.println(payload.ax);
        Serial.print("AY : "); Serial.println(payload.ay);
        Serial.print("AZ : "); Serial.println(payload.az);
        Serial.print("GX: "); Serial.println(payload.gx);
        Serial.print("GY : "); Serial.println(payload.gy);
        Serial.print("GZ : "); Serial.println(payload.gz);
        Serial.print("Sensor Temp: "); Serial.println(payload.sensorTemp);
      }
      if (payload.nodeID == 4) {
        Serial.print(F("Received From Node(4): "));
        Serial.print(bytes);  // print the size of the payload
        Serial.print(F(" bytes on pipe "));
        Serial.print(pipe);  // print the pipe number
        Serial.print(F(" from node "));
        Serial.print(payload.nodeID);  // print the payload's origin
        Serial.print(F(". PayloadID: "));
        Serial.println(payload.payloadID);  // print the payload's number
        Serial.print("AX : "); Serial.println(payload.ax);
        Serial.print("AY : "); Serial.println(payload.ay);
        Serial.print("AZ : "); Serial.println(payload.az);
        Serial.print("GX: "); Serial.println(payload.gx);
        Serial.print("GY : "); Serial.println(payload.gy);
        Serial.print("GZ : "); Serial.println(payload.gz);
        Serial.print("Sensor Temp: "); Serial.println(payload.sensorTemp);
      }
      if (payload.nodeID == 5) {
        Serial.print(F("Received From Node(5): "));
        Serial.print(bytes);  // print the size of the payload
        Serial.print(F(" bytes on pipe "));
        Serial.print(pipe);  // print the pipe number
        Serial.print(F(" from node "));
        Serial.print(payload.nodeID);  // print the payload's origin
        Serial.print(F(". PayloadID: "));
        Serial.println(payload.payloadID);  // print the payload's number
        Serial.print("AX : "); Serial.println(payload.ax);
        Serial.print("AY : "); Serial.println(payload.ay);
        Serial.print("AZ : "); Serial.println(payload.az);
        Serial.print("GX: "); Serial.println(payload.gx);
        Serial.print("GY : "); Serial.println(payload.gy);
        Serial.print("GZ : "); Serial.println(payload.gz);
        Serial.print("Sensor Temp: "); Serial.println(payload.sensorTemp);
      }

    }
  }

}
