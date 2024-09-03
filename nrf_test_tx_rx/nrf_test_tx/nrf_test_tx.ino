#include <SPI.h>
#include "printf.h"
#include "RF24.h"

#define CE_PIN 7
#define CSN_PIN 8

unsigned long start_timer;
unsigned long end_timer;



// instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);



//uint64_t address[6] = { 0x7878787878LL,
//                        0xB3B4B5B6F1LL,
//                        0xB3B4B5B6CDLL,
//                        0xB3B4B5B6A3LL,
//                        0xB3B4B5B60FLL,
//                        0xB3B4B5B605LL };
//

const uint64_t pipe_1 = 0x7878787878LL;
//const uint64_t pipe_2 = 0xB3B4B5B6F1LL;





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
void readData(); // function for diplaying real-time data
void displayData();

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

  radio.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX is default.
  radio.setPayloadSize(sizeof(payload));  // 2x int datatype occupy 8 bytes
  setRole();

}

void loop() {


  start_timer = micros();                  // start the timer
  bool report = radio.write(&payload, sizeof(payload));  // transmit & save the report
  end_timer = micros();                    // end the timer

  if (report) {
    // payload was delivered

    //    Serial.print(F("Transmission of payloadID "));
    //    Serial.print(payload.payloadID);  // print payloadID
    //    Serial.print(F(" as node "));
    //    Serial.print(payload.nodeID);  // print nodeID
    //    Serial.print(F(" successful!"));
    //    Serial.print(F(" Time to transmit: "));
    //    Serial.print(end_timer - start_timer);  // print the timer result
    //    Serial.println(F(" us"));

    displayData();

  } else {
    Serial.println(F("Transmission failed or timed out"));  // payload was not delivered
  }
  payload.payloadID++;  // increment payload number
  readData();

  // to make this example readable in the serial monitor
  delay(8000);  // slow transmissions down by 1 second


}  // loop

void setRole() {

  // set the payload's nodeID & reset the payload's identifying number
  payload.nodeID = 1;
//  payload.nodeID = 2;
  payload.payloadID = 0;
  payload.ax = 0;
  payload.ay = 0;
  payload.az = 0;
  payload.gx = 0;
  payload.gy = 0;
  payload.gz = 0;
  payload.sensorTemp = 0;

  // Set the address on pipe 0 to the RX node.
  radio.stopListening();  // put radio in TX mode
  radio.openWritingPipe(pipe_1);
//  radio.openWritingPipe(pipe_2);

}


void readData() {

  payload.ax = random(20, 40);
  payload.ay = random(60, 90);
  payload.az = random(20, 40);
  payload.gx = random(60, 90);
  payload.gy = random(20, 40);
  payload.gz = random(60, 90);
  payload.sensorTemp = random(20, 40);
}


void displayData() {
  Serial.print(F("Transmission of payloadID "));
  Serial.print(payload.payloadID);  // print payloadID
  Serial.print(F(" as node "));
  Serial.print(payload.nodeID);  // print nodeID
  Serial.print(F(" successful!"));
  Serial.print(F(" Time to transmit: "));
  Serial.print(end_timer - start_timer);  // print the timer result
  Serial.println(F(" us"));
  Serial.print("AX : "); Serial.println(payload.ax);
  Serial.print("AY : "); Serial.println(payload.ay);
  Serial.print("AZ : "); Serial.println(payload.az);
  Serial.print("GX: "); Serial.println(payload.gx);
  Serial.print("GY : "); Serial.println(payload.gy);
  Serial.print("GZ : "); Serial.println(payload.gz);
  Serial.print("Sensor Temp: "); Serial.println(payload.sensorTemp);
  
}
