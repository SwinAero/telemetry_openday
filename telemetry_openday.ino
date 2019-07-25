#include <MPU6050_tockn.h>

#include <Wire.h>
#include <SPI.h>

MPU6050 mpu6050(Wire);
long timer = 0;

void setup() {
  Serial.begin(115200);
  while(!Serial);

  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(false);
  Serial.println("Calibrating...");

  Serial.println("Ready");
  timer = micros();
}

void loop() {
  mpu6050.update();

  long now = micros();
  long delta = now - timer;
  timer = now;

  Serial.print(delta);
  
  Serial.print(", ");Serial.print(mpu6050.getAccX(),7);
  Serial.print(", ");Serial.print(mpu6050.getAccY(),7);
  Serial.print(", ");Serial.print(mpu6050.getAccZ(),7);

  Serial.print(", ");Serial.print(mpu6050.getGyroAngleX(),7);
  Serial.print(", ");Serial.print(mpu6050.getGyroAngleY(),7);
  Serial.print(", ");Serial.println(mpu6050.getGyroAngleZ(),7);
}
