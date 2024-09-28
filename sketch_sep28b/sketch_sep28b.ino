#include <Arduino_APDS9960.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  // flash red when putting up gesture
  pinMode(LEDR, OUTPUT);

  while (!Serial);
    if (!APDS.begin()) {
      Serial.println("Error initializing sensor!");
    }

  APDS.setGestureSensitivity(80);
  Serial.println("Detecting gestures ...");

  // turn off red led
  digitalWrite(LEDR, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:

  // check for only up gesture
  if (APDS.gestureAvailable()) {
    int gesture = APDS.readGesture();
    switch (gesture){
      case GESTURE_UP:
        Serial.println("Going up.");
        digitalWrite(LEDR, LOW);
        delay(1000);
        digitalWrite(LEDR, HIGH);
        break;
      default:
        break;
    }
  }
}