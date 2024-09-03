#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>


//// WiFi
//const char *ssid = "VIRUS.COM"; // Enter your Wi-Fi name
//const char *password = "mnrs996318";  // Enter Wi-Fi password


const char *ssid = "APS_OFFICE"; // Enter your Wi-Fi name
const char *password = "WelcomeTo@APS#22";  // Enter Wi-Fi password


// MQTT Broker
const char *mqtt_broker = "test.mosquitto.org";
const int mqtt_port = 1883;



const char *tag1_baseStation1 = "tag1_baseStation1";
const char *tag2_baseStation1 = "tag2_baseStation1";
const char *tag3_baseStation1 = "tag3_baseStation1";
const char *tag4_baseStation1 = "tag4_baseStation1";
const char *tag5_baseStation1 = "tag5_baseStation1";
const char *tag6_baseStation1 = "tag6_baseStation1";



WiFiClient espClient;
PubSubClient client(espClient);




void tag_1();
void tag_2();
void tag_3();
void tag_4();
void tag_5();



void setup() {
  // Set software serial baud to 115200;
  Serial.begin(115200);
  // Connecting to a WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the Wi-Fi network");
  //connecting to a mqtt broker
  client.setServer(mqtt_broker, mqtt_port);
  // client.setCallback(callback);
  while (!client.connected()) {
    String client_id = "esp32-client-";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to the public MQTT broker\n", client_id.c_str());
    if (client.connect(client_id.c_str())) {
      Serial.println("Public Mosquitto MQTT broker connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
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


void loop() {
  


  tag_1();
  tag_2();
  tag_3();
  tag_4();
  tag_5();
  tag_6();
  
  delay(5000);


}




void tag_1(){

  client.loop();
  String accl, gyro;
  
  StaticJsonDocument<2048> JSONData;
  unsigned long nodeID = 1;
  unsigned long payloadID = 1;
  float ax = random(-10, 10);
  float ay = random(-10, 10);
  float az = random(-10, 10);
  float gx = random(-10, 10);
  float gy = random(-10, 10);
  float gz = random(-10, 10);
  float sensorTemp = random(15, 40);

  
  accl = String(ax) + "," + String(ay) + "," + String(az);
  gyro = String(gx) + "," + String(gy) + "," + String(gz);

  JSONData["NodeID"] = nodeID;
  JSONData["PayloadID"] = payloadID;
  JSONData["Accelerometer"] = accl;
  JSONData["Gyroscope"] = gyro;
  JSONData["Temperature"] = sensorTemp;


  

  char data[1024];
  serializeJson(JSONData, data);
  Serial.println(data);
 

  client.publish(tag1_baseStation1, data);
  
}

void tag_2(){

  client.loop();
  
  String accl, gyro;
  
  StaticJsonDocument<2048> JSONData;
  
  unsigned long nodeID = 2;
  unsigned long payloadID = 2;
  float ax = random(-10, 10);
  float ay = random(-10, 10);
  float az = random(-10, 10);
  float gx = random(-10, 10);
  float gy = random(-10, 10);
  float gz = random(-10, 10);
  float sensorTemp = random(15, 40);

  
  accl = String(ax) + "," + String(ay) + "," + String(az);
  gyro = String(gx) + "," + String(gy) + "," + String(gz);

  JSONData["NodeID"] = nodeID;
  JSONData["PayloadID"] = payloadID;
  JSONData["Accelerometer"] = accl;
  JSONData["Gyroscope"] = gyro;
  JSONData["Temperature"] = sensorTemp;


  

  char data[1024];
  serializeJson(JSONData, data);
  Serial.println(data);
 

  client.publish(tag2_baseStation1, data);
}

void tag_3(){

  client.loop();
  
  String accl, gyro;
  
  StaticJsonDocument<2048> JSONData;
  unsigned long nodeID = 3;
  unsigned long payloadID = 3;
  float ax = random(-10, 10);
  float ay = random(-10, 10);
  float az = random(-10, 10);
  float gx = random(-10, 10);
  float gy = random(-10, 10);
  float gz = random(-10, 10);
  float sensorTemp = random(15, 40);

  
  accl = String(ax) + "," + String(ay) + "," + String(az);
  gyro = String(gx) + "," + String(gy) + "," + String(gz);

  JSONData["NodeID"] = nodeID;
  JSONData["PayloadID"] = payloadID;
  JSONData["Accelerometer"] = accl;
  JSONData["Gyroscope"] = gyro;
  JSONData["Temperature"] = sensorTemp;


  

  char data[1024];
  serializeJson(JSONData, data);
  Serial.println(data);
 

  client.publish(tag3_baseStation1, data);
}

void tag_4(){


  client.loop();
  String accl, gyro;
  
  StaticJsonDocument<2048> JSONData;
  unsigned long nodeID = 4;
  unsigned long payloadID = 4;
  float ax = random(-10, 10);
  float ay = random(-10, 10);
  float az = random(-10, 10);
  float gx = random(-10, 10);
  float gy = random(-10, 10);
  float gz = random(-10, 10);
  float sensorTemp = random(15, 40);

  
  accl = String(ax) + "," + String(ay) + "," + String(az);
  gyro = String(gx) + "," + String(gy) + "," + String(gz);

  JSONData["NodeID"] = nodeID;
  JSONData["PayloadID"] = payloadID;
  JSONData["Accelerometer"] = accl;
  JSONData["Gyroscope"] = gyro;
  JSONData["Temperature"] = sensorTemp;


  

  char data[1024];
  serializeJson(JSONData, data);
  Serial.println(data);
 

  client.publish(tag4_baseStation1, data);
}


void tag_5(){

  client.loop();
  String accl, gyro;
  
  StaticJsonDocument<2048> JSONData;
  unsigned long nodeID = 5;
  unsigned long payloadID = 5;
  float ax = random(-10, 10);
  float ay = random(-10, 10);
  float az = random(-10, 10);
  float gx = random(-10, 10);
  float gy = random(-10, 10);
  float gz = random(-10, 10);
  float sensorTemp = random(15, 40);

  
  accl = String(ax) + "," + String(ay) + "," + String(az);
  gyro = String(gx) + "," + String(gy) + "," + String(gz);

  JSONData["NodeID"] = nodeID;
  JSONData["PayloadID"] = payloadID;
  JSONData["Accelerometer"] = accl;
  JSONData["Gyroscope"] = gyro;
  JSONData["Temperature"] = sensorTemp;


  

  char data[1024];
  serializeJson(JSONData, data);
  Serial.println(data);
 

  client.publish(tag5_baseStation1, data);
  
}


void tag_6(){


  client.loop();
  String accl, gyro;
  
  StaticJsonDocument<2048> JSONData;
  unsigned long nodeID = 6;
  unsigned long payloadID = 6;
  float ax = random(-10, 10);
  float ay = random(-10, 10);
  float az = random(-10, 10);
  float gx = random(-10, 10);
  float gy = random(-10, 10);
  float gz = random(-10, 10);
  float sensorTemp = random(15, 40);

  
  accl = String(ax) + "," + String(ay) + "," + String(az);
  gyro = String(gx) + "," + String(gy) + "," + String(gz);

  JSONData["NodeID"] = nodeID;
  JSONData["PayloadID"] = payloadID;
  JSONData["Accelerometer"] = accl;
  JSONData["Gyroscope"] = gyro;
  JSONData["Temperature"] = sensorTemp;


  

  char data[1024];
  serializeJson(JSONData, data);
  Serial.println(data);
 

  client.publish(tag6_baseStation1, data);
  
}
