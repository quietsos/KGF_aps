#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Initialize the MPU6050 sensor
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 sensor!");
    while (1);
  }
  Serial.println("MPU6050 connected successfully!");
}

void loop() {
  // Wake up the MPU6050
  mpu.enableSleep(false);
  Serial.println("MPU6050 is awake.");

  // Read accelerometer and gyroscope data
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Print accelerometer data
  Serial.print("Accel X: "); Serial.print(a.acceleration.x);
  Serial.print(" | Accel Y: "); Serial.print(a.acceleration.y);
  Serial.print(" | Accel Z: "); Serial.println(a.acceleration.z);

  // Print gyroscope data
  Serial.print("Gyro X: "); Serial.print(g.gyro.x);
  Serial.print(" | Gyro Y: "); Serial.print(g.gyro.y);
  Serial.print(" | Gyro Z: "); Serial.println(g.gyro.z);

  // Print temperature (optional)
  Serial.print("Temperature: "); Serial.println(temp.temperature);

  // Put the MPU6050 into sleep mode for 10 seconds
  mpu.enableSleep(true);
  Serial.println("MPU6050 is now in sleep mode.");
  delay(10000); // Sleep for 10 seconds (10000 ms)
}
