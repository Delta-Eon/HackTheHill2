#include <Wire.h>
#include "MAX30100_PulseOximeter.h" // heart rate

#include "Arduino_BMI270_BMM150.h" // gyroscope

float x, y, z;
int plusThreshold = 30, minusThreshold = -30;
int reps = 0;

#define REPORTING_PERIOD_MS 2000

PulseOximeter pox;
uint32_t tsLastReport = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
  }

  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

}

void loop() {
  // put your main code here, to run repeatedly:

  pox.update();

  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    tsLastReport = millis();
    Serial.print("Current Heart Rate: ");
    Serial.print(pox.getHeartRate());
    Serial.println(" ");
  }

  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(x, y, z);

  if(y > plusThreshold)
  {
  Serial.println("Shake Front");
  reps += 1;
  Serial.print("Reps: ");
  Serial.print(reps);
  Serial.println(" ");
  delay(500);
  }
  if(y < minusThreshold)
  {
  Serial.println("Shake Back");
  reps += 1;
  Serial.print("Reps: ");
  Serial.print(reps);
  Serial.println(" ");
  delay(500);
  }
  if(x < minusThreshold)
  {
  Serial.println("Shake Right");
  reps += 1;
  Serial.print("Reps: ");
  Serial.print(reps);
  Serial.println(" ");
  delay(500);
  }
  if(x > plusThreshold)
  {
  Serial.println("Shake Left");
  reps += 1;
  Serial.print("Reps: ");
  Serial.print(reps);
  Serial.println(" ");
  delay(500);
  }
  }

}
