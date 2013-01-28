#include "sc.h"

String Log = "";
String Now = "";

void outputSerial() {
  Serial.println(Log);
}

void buildLog(int8_t value) {
  Log = Log + Now + String(value) + "\n";
}
