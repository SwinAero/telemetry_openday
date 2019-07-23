#include <MPU6050_tockn.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

MPU6050 mpu6050(Wire);

const long FLUSH_FREQUENCY = 50;
long now = 0;
long outerTimer = 0;
long innerTimer = 0;
File logFile;

void setup() {
  Serial.begin(9600);
  while(!Serial);

  if(!SD.begin(2)) { // SD card is attached to pin 2 on the Ethernet Shield
    Serial.println("Cannot initialize SD card! Execution has been halted");
    while(true);
  }

  int fileIndex = 0;
  String fileName = "";
  while(true) {
    fileName += "TELEM_";
    fileName += fileIndex;
    fileName += ".CSV";
    if(!SD.exists(fileName)){
      break;
    }
    
    if(fileIndex >= 999) {
      Serial.println("Unable to allocate a telemetry file, please clean up the SD card.");
      while(true);
    }

    fileName = "";
    fileIndex++;
  }

  Serial.print("Log file: ");
  Serial.println(fileName);
  logFile = SD.open(fileName, FILE_WRITE);

  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  Serial.println();
  logFile.println("deltaT, accX, accY, accZ, thetaX, thetaY, thetaZ");
}

void loop() {
  for(int i = 0; i < FLUSH_FREQUENCY; i++) {
    now = micros();
    innerLoop();
  }

  unsigned long delta = millis() - outerTimer;
  outerTimer = millis();

  logFile.flush();
  Serial.print("Logging frequency: ");
  Serial.print(FLUSH_FREQUENCY * 1000 / delta);
  Serial.println("Hz");
}

void innerLoop() {
  long delta = now - innerTimer;
  innerTimer = now;

  mpu6050.update();

  logFile.print(delta);
  
  logFile.print(", ");logFile.print(mpu6050.getAccX(),7);
  logFile.print(", ");logFile.print(mpu6050.getAccY(),7);
  logFile.print(", ");logFile.print(mpu6050.getAccZ(),7);

  logFile.print(", ");logFile.print(mpu6050.getAngleX(),7);
  logFile.print(", ");logFile.print(mpu6050.getAngleY(),7);
  logFile.print(", ");logFile.println(mpu6050.getAngleZ(),7);
}
