#include <SPI.h>
#include "printf.h"
#include "RF24.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <RTClib.h>



//// WiFi
//const char *ssid = "VIRUS.COM"; // Enter your Wi-Fi name
//const char *password = "mnrs996318";  // Enter Wi-Fi password


const char *ssid = "APS_OFFICE"; // Enter your Wi-Fi name
const char *password = "WelcomeTo@APS#22";  // Enter Wi-Fi password


// MQTT Broker
const char *mqtt_broker = "test.mosquitto.org";
const int mqtt_port = 1883;



#define CE_PIN 4
#define CSN_PIN 5

#define radioLed 13
#define wifiLed 27
#define mqttLed 32
#define dataLed 26






// instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);


// RTC module credentials
RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};



uint64_t address[6] = { 0x7878787878LL,
                        0xB3B4B5B6F1LL,
                        0xB3B4B5B6CDLL,
                        0xB3B4B5B6A3LL,
                        0xB3B4B5B60FLL,
                        0xB3B4B5B605LL
                      };


char role = 'R';  // integers 0-5 = TX node; character 'R' or integer 82 = RX node




// Structure to use as a payload for radio data

struct PayloadStruct {
  unsigned long nodeID;
  //  unsigned long payloadID;
  //  String dateTime;
  float ax;
  float ay;
  float az;
  float gx;
  float gy;
  float gz;
  float sensorTemp;
};
PayloadStruct payload;




// Topics to sent data from each harness tag number and base station number

const char *tag1_baseStation1 = "tag1_baseStation1";
const char *tag2_baseStation1 = "tag2_baseStation1";
const char *tag3_baseStation1 = "tag3_baseStation1";
const char *tag4_baseStation1 = "tag4_baseStation1";
const char *tag5_baseStation1 = "tag5_baseStation1";
const char *tag6_baseStation1 = "tag6_baseStation1";



WiFiClient espClient;
PubSubClient client(espClient);




void setRole();             // setting role of radio it will work weather transmitter or receiver mode
void radioTest();           // function to test radio is active or not
void receivedData();        // Function to received data from radio
void wifiTest();            // WiFi connection test
void mqttTest();            // MQTT connection test
//void callback(char *topic, byte *payload, unsigned int length); // callback function for receiving data from mqtt broker
void rtcTest();             // RTC module test
void ledSetup();





void setup() {

  Serial.begin(115200);
  while (!Serial) {
    // some boards need to wait to ensure access to serial over USB
  }


  ledSetup();
  radioTest();
  setRole();
  wifiTest();
  mqttTest();
  rtcTest();

}

void loop() {

  receivedData();



}  // loop


void ledSetup() {
  pinMode(radioLed, OUTPUT);
  pinMode(wifiLed, OUTPUT);
  pinMode(mqttLed, OUTPUT);
  pinMode(dataLed, OUTPUT);


  digitalWrite(radioLed, LOW);
  digitalWrite(wifiLed, LOW);
  digitalWrite(mqttLed, LOW);
  digitalWrite(dataLed, LOW);
}




void radioTest() {
  // initialize the transceiver on the SPI bus
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    digitalWrite(radioLed, LOW);
    while (1) {}  // hold in infinite loop
  }

  Serial.println(F("Base Station Multi Receiver"));
  radio.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX is default.
  radio.setPayloadSize(sizeof(payload));  // 2x int datatype occupy 8 bytes
  digitalWrite(radioLed, HIGH);


}



void setRole() {
  if (role == 'R') {
    // For the RX node

    // Set the addresses for all pipes to TX nodes
    for (uint8_t i = 0; i < 6; ++i) {
      radio.openReadingPipe(i, address[i]);
    }
    radio.startListening();  // put radio in RX mode

    digitalWrite(dataLed, HIGH);
  }
}




void wifiTest() {
  // Connecting to a WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
    digitalWrite(wifiLed, LOW);
  }
  Serial.println("Connected to the Wi-Fi network");
  digitalWrite(wifiLed, HIGH);
}


void mqttTest() {

  //connecting to a mqtt broker
  Serial.println("Connecting to MQTT Broker");
  client.setServer(mqtt_broker, mqtt_port);

  // client.setCallback(callback);


  while (!client.connected()) {
    String client_id = "esp32-client-";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to the public MQTT broker\n", client_id.c_str());


    if (client.connect(client_id.c_str())) {
      Serial.println("Public Mosquitto MQTT broker connected");
      digitalWrite(mqttLed, HIGH);
    }
    else {
      Serial.print("failed with state ");
      digitalWrite(mqttLed, LOW);
      Serial.print(client.state());
      delay(500);
    }
  }
}


void rtcTest() {
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  else {
    Serial.println("Find RTC Module!");
  }

  // Uncomment the following lines to set the initial date and time if needed
  //  rtc.adjust(DateTime(__DATE__, __TIME__));
}



// void callback(char *topic, byte *payload, unsigned int length) {
//     Serial.print("Message arrived in topic: ");
//     Serial.println(topic);
//     Serial.print("Message:");
//     for (int i = 0; i < length; i++) {
//         Serial.print((char) payload[i]);
//     }
//     Serial.println();
//     Serial.println("-----------------------");
// }





void receivedData() {

  client.loop();


  if (role == 'R') {
    // This device is the RX node


    DateTime now = rtc.now();
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
        //        Serial.print(F(". PayloadID: "));
        //        Serial.println(payload.payloadID);  // print the payload's number
        Serial.print("AX : "); Serial.println(payload.ax);
        Serial.print("AY : "); Serial.println(payload.ay);
        Serial.print("AZ : "); Serial.println(payload.az);
        Serial.print("GX: "); Serial.println(payload.gx);
        Serial.print("GY : "); Serial.println(payload.gy);
        Serial.print("GZ : "); Serial.println(payload.gz);
        Serial.print("Sensor Temp: "); Serial.println(payload.sensorTemp);



        String accl, gyro;

        StaticJsonDocument<2048> JSONData;
        accl = String(payload.ax) + "," + String(payload.ay) + "," + String(payload.az);
        gyro = String(payload.gx) + "," + String(payload.gy) + "," + String(payload.gz);
        String dateTime = String(now.day()) + ":" + String(now.month()) + ":" + String(now.year()) + "/" + String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()) + "/" + String(daysOfTheWeek[now.dayOfTheWeek()]);
        JSONData["NodeID"] = payload.nodeID;
        //        JSONData["PayloadID"] = payload.payloadID;
        JSONData["Accelerometer"] = accl;
        JSONData["Gyroscope"] = gyro;
        JSONData["Temperature"] = payload.sensorTemp;
        JSONData["Current_Time"] = dateTime;

        char data[1024];
        serializeJson(JSONData, data);
        Serial.println(data);


        client.publish(tag1_baseStation1, data);
        digitalWrite(dataLed, HIGH);
        delay(100);
        




      }


      if (payload.nodeID == 1) {
        Serial.print(F("Received From Node(1): "));
        Serial.print(bytes);  // print the size of the payload
        Serial.print(F(" bytes on pipe "));
        Serial.print(pipe);  // print the pipe number
        Serial.print(F(" from node "));
        Serial.print(payload.nodeID);  // print the payload's origin
        //        Serial.print(F(". PayloadID: "));
        //        Serial.println(payload.payloadID);  // print the payload's number
        Serial.print("AX : "); Serial.println(payload.ax);
        Serial.print("AY : "); Serial.println(payload.ay);
        Serial.print("AZ : "); Serial.println(payload.az);
        Serial.print("GX: "); Serial.println(payload.gx);
        Serial.print("GY : "); Serial.println(payload.gy);
        Serial.print("GZ : "); Serial.println(payload.gz);
        Serial.print("Sensor Temp: "); Serial.println(payload.sensorTemp);


        String accl, gyro;

        StaticJsonDocument<2048> JSONData;
        accl = String(payload.ax) + "," + String(payload.ay) + "," + String(payload.az);
        gyro = String(payload.gx) + "," + String(payload.gy) + "," + String(payload.gz);
        String dateTime = String(now.day()) + ":" + String(now.month()) + ":" + String(now.year()) + "/" + String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()) + "/" + String(daysOfTheWeek[now.dayOfTheWeek()]);
        JSONData["NodeID"] = payload.nodeID;
        //        JSONData["PayloadID"] = payload.payloadID;
        JSONData["Accelerometer"] = accl;
        JSONData["Gyroscope"] = gyro;
        JSONData["Temperature"] = payload.sensorTemp;
        JSONData["Current_Time"] = dateTime;

        char data[1024];
        serializeJson(JSONData, data);
        Serial.println(data);


        client.publish(tag2_baseStation1, data);
        digitalWrite(dataLed, HIGH);
        delay(100);




      }
      if (payload.nodeID == 2) {

        Serial.print(F("Received From Node(2): "));
        Serial.print(bytes);  // print the size of the payload
        Serial.print(F(" bytes on pipe "));
        Serial.print(pipe);  // print the pipe number
        Serial.print(F(" from node "));
        Serial.print(payload.nodeID);  // print the payload's origin
        //        Serial.print(F(". PayloadID: "));
        //        Serial.println(payload.payloadID);  // print the payload's number
        Serial.print("AX : "); Serial.println(payload.ax);
        Serial.print("AY : "); Serial.println(payload.ay);
        Serial.print("AZ : "); Serial.println(payload.az);
        Serial.print("GX: "); Serial.println(payload.gx);
        Serial.print("GY : "); Serial.println(payload.gy);
        Serial.print("GZ : "); Serial.println(payload.gz);
        Serial.print("Sensor Temp: "); Serial.println(payload.sensorTemp);


        String accl, gyro;

        StaticJsonDocument<2048> JSONData;
        accl = String(payload.ax) + "," + String(payload.ay) + "," + String(payload.az);
        gyro = String(payload.gx) + "," + String(payload.gy) + "," + String(payload.gz);
        String dateTime = String(now.day()) + ":" + String(now.month()) + ":" + String(now.year()) + "/" + String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()) + "/" + String(daysOfTheWeek[now.dayOfTheWeek()]);
        JSONData["NodeID"] = payload.nodeID;
        //        JSONData["PayloadID"] = payload.payloadID;
        JSONData["Accelerometer"] = accl;
        JSONData["Gyroscope"] = gyro;
        JSONData["Temperature"] = payload.sensorTemp;
        JSONData["Current_Time"] = dateTime;


        char data[1024];
        serializeJson(JSONData, data);
        Serial.println(data);


        client.publish(tag3_baseStation1, data);
        digitalWrite(dataLed, HIGH);
        delay(100);



      }


      if (payload.nodeID == 3) {
        Serial.print(F("Received From Node(3): "));
        Serial.print(bytes);  // print the size of the payload
        Serial.print(F(" bytes on pipe "));
        Serial.print(pipe);  // print the pipe number
        Serial.print(F(" from node "));
        Serial.print(payload.nodeID);  // print the payload's origin
        //        Serial.print(F(". PayloadID: "));
        //        Serial.println(payload.payloadID);  // print the payload's number
        Serial.print("AX : "); Serial.println(payload.ax);
        Serial.print("AY : "); Serial.println(payload.ay);
        Serial.print("AZ : "); Serial.println(payload.az);
        Serial.print("GX: "); Serial.println(payload.gx);
        Serial.print("GY : "); Serial.println(payload.gy);
        Serial.print("GZ : "); Serial.println(payload.gz);
        Serial.print("Sensor Temp: "); Serial.println(payload.sensorTemp);

        String accl, gyro;

        StaticJsonDocument<2048> JSONData;
        accl = String(payload.ax) + "," + String(payload.ay) + "," + String(payload.az);
        gyro = String(payload.gx) + "," + String(payload.gy) + "," + String(payload.gz);
        String dateTime = String(now.day()) + ":" + String(now.month()) + ":" + String(now.year()) + "/" + String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()) + "/" + String(daysOfTheWeek[now.dayOfTheWeek()]);
        JSONData["NodeID"] = payload.nodeID;
        //        JSONData["PayloadID"] = payload.payloadID;
        JSONData["Accelerometer"] = accl;
        JSONData["Gyroscope"] = gyro;
        JSONData["Temperature"] = payload.sensorTemp;
        JSONData["Current_Time"] = dateTime;


        char data[1024];
        serializeJson(JSONData, data);
        Serial.println(data);


        client.publish(tag4_baseStation1, data);
        digitalWrite(dataLed, HIGH);
        delay(100);



      }
      if (payload.nodeID == 4) {

        Serial.print(F("Received From Node(4): "));
        Serial.print(bytes);  // print the size of the payload
        Serial.print(F(" bytes on pipe "));
        Serial.print(pipe);  // print the pipe number
        Serial.print(F(" from node "));
        Serial.print(payload.nodeID);  // print the payload's origin
        //        Serial.print(F(". PayloadID: "));
        //        Serial.println(payload.payloadID);  // print the payload's number
        Serial.print("AX : "); Serial.println(payload.ax);
        Serial.print("AY : "); Serial.println(payload.ay);
        Serial.print("AZ : "); Serial.println(payload.az);
        Serial.print("GX: "); Serial.println(payload.gx);
        Serial.print("GY : "); Serial.println(payload.gy);
        Serial.print("GZ : "); Serial.println(payload.gz);
        Serial.print("Sensor Temp: "); Serial.println(payload.sensorTemp);

        String accl, gyro;

        StaticJsonDocument<2048> JSONData;
        accl = String(payload.ax) + "," + String(payload.ay) + "," + String(payload.az);
        gyro = String(payload.gx) + "," + String(payload.gy) + "," + String(payload.gz);
        String dateTime = String(now.day()) + ":" + String(now.month()) + ":" + String(now.year()) + "/" + String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()) + "/" + String(daysOfTheWeek[now.dayOfTheWeek()]);
        JSONData["NodeID"] = payload.nodeID;
        //        JSONData["PayloadID"] = payload.payloadID;
        JSONData["Accelerometer"] = accl;
        JSONData["Gyroscope"] = gyro;
        JSONData["Temperature"] = payload.sensorTemp;
        JSONData["Current_Time"] = dateTime;


        char data[1024];
        serializeJson(JSONData, data);
        Serial.println(data);


        client.publish(tag5_baseStation1, data);
        digitalWrite(dataLed, HIGH);
        delay(100);


      }


      if (payload.nodeID == 5) {
        Serial.print(F("Received From Node(5): "));
        Serial.print(bytes);  // print the size of the payload
        Serial.print(F(" bytes on pipe "));
        Serial.print(pipe);  // print the pipe number
        Serial.print(F(" from node "));
        Serial.print(payload.nodeID);  // print the payload's origin
        //        Serial.print(F(". PayloadID: "));
        //        Serial.println(payload.payloadID);  // print the payload's number
        Serial.print("AX : "); Serial.println(payload.ax);
        Serial.print("AY : "); Serial.println(payload.ay);
        Serial.print("AZ : "); Serial.println(payload.az);
        Serial.print("GX: "); Serial.println(payload.gx);
        Serial.print("GY : "); Serial.println(payload.gy);
        Serial.print("GZ : "); Serial.println(payload.gz);
        Serial.print("Sensor Temp: "); Serial.println(payload.sensorTemp);



        String accl, gyro;

        StaticJsonDocument<2048> JSONData;
        accl = String(payload.ax) + "," + String(payload.ay) + "," + String(payload.az);
        gyro = String(payload.gx) + "," + String(payload.gy) + "," + String(payload.gz);
        String dateTime = String(now.day()) + ":" + String(now.month()) + ":" + String(now.year()) + "/" + String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()) + "/" + String(daysOfTheWeek[now.dayOfTheWeek()]);
        JSONData["NodeID"] = payload.nodeID;
        //        JSONData["PayloadID"] = payload.payloadID;
        JSONData["Accelerometer"] = accl;
        JSONData["Gyroscope"] = gyro;
        JSONData["Temperature"] = payload.sensorTemp;
        JSONData["Current_Time"] = dateTime;

        char data[1024];
        serializeJson(JSONData, data);
        Serial.println(data);


        client.publish(tag6_baseStation1, data);
        digitalWrite(dataLed, HIGH);
        delay(100);

      }

      digitalWrite(dataLed, LOW);




    }



  }

}
