#include <Adafruit_CircuitPlayground.h>
#include <Keyboard.h>

#define CAP_THRESHOLD 200

bool capSensor(int sensor, char key) {
  int reading;
  reading = CircuitPlayground.readCap(sensor);
  if (reading > CAP_THRESHOLD) {
    Keyboard.print(key);
    flashLights();
  }
}

void flashLights() {
      CircuitPlayground.clearPixels();
      int i;
      for (i = 0; i < 10; ++i) {
        CircuitPlayground.strip.setPixelColor(i,255,255,255);
      }
      CircuitPlayground.strip.show();
      delay(100);
      CircuitPlayground.clearPixels();
}

void cycleLights() {
    static int sequence=0;
    static unsigned long previousMillis=0;

    //Only change the light sequence if 250ms have passed
    if (!((unsigned long)(millis() - previousMillis) >= 250)) return;

    int i;
    for (i = 0; i < 10; ++i) {
        CircuitPlayground.strip.setPixelColor(i,(((sequence + i) % 3) == 0) * 255,(((sequence + i) % 3) == 2) * 255,(((sequence + i) % 3) == 1) * 255);
    }
    CircuitPlayground.strip.show();
    sequence = (sequence + 1) % 3;

    previousMillis = millis();
}

void setup() {
  Keyboard.begin();

  CircuitPlayground.begin();
  CircuitPlayground.setBrightness(30); // Lights not too bright

  delay(250);
  cycleLights();
}

void leftButton() {
  static int previousButtonState=LOW;
  int buttonState = CircuitPlayground.leftButton();
    // if the button state has changed
    if ((buttonState != previousButtonState)
        // and it's currently pressed:
        && (buttonState == HIGH)) {
            // TODO: Check what keys are useful in StepMania
            Keyboard.print("You pressed the left button ");
    }
    // save the current button state for comparison next time:
    previousButtonState = buttonState;
}

void loop() {
  bool slideSwitch;
  slideSwitch = CircuitPlayground.slideSwitch();
  
  if (slideSwitch) {
    capSensor(3,KEY_LEFT_ARROW);
    capSensor(2,KEY_RIGHT_ARROW);
    capSensor(0,KEY_UP_ARROW);
    capSensor(1,KEY_DOWN_ARROW);
  
    leftButton();

    cycleLights();
  }
  delay(25);
}
