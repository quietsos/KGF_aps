#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>


const char* ssid = "APS_OFFICE";
const char* password = "WelcomeTo@APS#22";
const char* mqtt_server = "test.mosquitto.org";
//const char* mqtt_server = "localhost";
const int port = 1883;
//
//const char* ssid = "VIRUS.COM"; //choose your wireless ssid
//const char* password =  "mnrs996318"; //put your wireless password here.

const char* tag_1 = "baseStation1/tag1";

 

WiFiClient espClient;
PubSubClient client(espClient);


void setup_wifi();
void callback(char* topic, byte* message, unsigned int length);
void reconnect();
void msgSent();

void setup() {

  
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, port);
  client.setCallback(callback);
  
}

void loop() {

 if(!client.connected()){
   reconnect();
  }
  client.loop();

  
  msgSent();
  delay(1000);

}




void setup_wifi(){
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(100);
    Serial.print(".");
  }


  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address : ");
  Serial.println(WiFi.localIP());

  
}


void callback(char* topic, byte* message, unsigned int length){

  Serial.print("Message arrived [" );
  Serial.print(topic);
  Serial.println("]");
  for (unsigned int i=0; i<length; i++){
    Serial.print((char)message[i]);
  }
  Serial.println();
  
}


void reconnect(){
  while(!client.connected()){
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX); // add a unique identifier to the client ID

    if(client.connect(clientId.c_str())){
      Serial.println("Connected");
      client.subscribe("dashboard/tag1");
    } 
    else{
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Try again in 2 seconds");
      delay(2000);
    }
    
  }
}



void msgSent(){


  // Publish temperature data

  StaticJsonDocument<200> doc;

  String accl, gyro;
  
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
//  doc["temperature"] = random(20, 30);
//  doc["humidity"] = random(40, 99);
//  doc["random val"] = random(1, 1000);

  doc["nodeID"] = nodeID;
  doc["payloadID"] = payloadID;
  doc["Accelerometer"] = accl;
  doc["Gyroscope"] = gyro;
  doc["Temperature"] = sensorTemp;
  
  
  char buffer[256];
  serializeJson(doc, buffer);
  client.publish(tag_1, buffer);
  Serial.println("Data sent to mqtt broker!");

}
