#include <Wire.h>
#include <MPU6050.h>
#include <RH_ASK.h>
#include <SPI.h>

#define VIB_PIN 2

MPU6050 mpu;
RH_ASK rf_driver;  // 433 MHz RF transmitter; default TX pin is D12

void setup() {
  Serial.begin(9600);

  Wire.begin();
  pinMode(VIB_PIN, INPUT);

  mpu.initialize();
  mpu.setSleepEnabled(false);

  if (!rf_driver.init()) {
    Serial.println("RF init failed");
  }

  Serial.println("TX READY");
}

void loop() {
  int16_t ax, ay, az;

  mpu.getAcceleration(&ax, &ay, &az);

  // Convert raw accelerometer data to g.
  float Ay = ay / 16384.0;
  float Az = az / 16384.0;

  // Calculate roll angle from the Y and Z acceleration axes.
  int angle = (int)(atan2(Ay, Az) * 180.0 / PI);

  int vib = digitalRead(VIB_PIN);

  char msg[20];

  // Accident condition: vibration detected and roll angle exceeds 35 degrees.
  if (vib == HIGH && abs(angle) > 35) {
    sprintf(msg, "A,%d", angle);
  } else {
    sprintf(msg, "N,%d", angle);
  }

  rf_driver.send((uint8_t *)msg, strlen(msg));
  rf_driver.waitPacketSent();

  Serial.println(msg);

  delay(300);
}
