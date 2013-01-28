#include <Metro.h>
#include "sc.h"

Metro watch4DisplayTimeNumber = Metro(250);
Metro watch4DisplayTimeColon  = Metro(500);
Metro watch4MotionSensor = Metro(200);
//Metro watch4WriteData2SD = Metro(300000);
Metro watch4WriteData2SD = Metro(60000);

void setup() {
  Serial.begin(57600);

  dateSetup();
  sdSetup();

  /*
   * Setup Motion Sensor
   */
  pinMode(4, INPUT);

  delay(2000);
}

void loop() {
  // Display time of now, to 7 segment, without colon
  if (watch4DisplayTimeNumber.check() == 1) {
    getDateDs1307();
  }
  // Display time of now, to 7 segment, with colon
  if (watch4DisplayTimeColon.check() == 1) {
    output2seg();
  }
  // Detect motion sensor value
  if (watch4MotionSensor.check() == 1) {
    int sensorValue = digitalRead(2);
    buildLog(sensorValue);
  }
  // Save to SD
  if (watch4WriteData2SD.check() == 1) {
    Log2SD();
  }
}




