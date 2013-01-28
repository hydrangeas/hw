#include <Metro.h>
#include "sc.h"

Metro watchColon = Metro(500);
Metro watchNum   = Metro(250);

void setup() {
  Serial.begin(57600);

  dateSetup();
  sdSetup();

  delay(2000);
}

void loop() {
  if (watchNum.check() == 1) {
    getDateDs1307();
  }
  if (watchColon.check() == 1) {
    output2seg();
  }
}




