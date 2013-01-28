#include <SdFat.h>

// SD chip select pin
const uint8_t chipSelect = SS;

// file system object
SdFat sd;

// define a serial output stream
ArduinoOutStream cout(Serial);

String dirName = "";
String fileName = "";

/*
 * Append a line to LOGFILE.TXT
 */
void logEvent(const char *msg) {
  char fileName_c[fileName.length()+1];
  fileName.toCharArray(fileName_c, fileName.length()+1);

  // create or open a file for append
  ofstream sdlog(fileName_c, ios::out | ios::app);

  // append a line to the file
  sdlog << msg << endl;

  // check for errors
  if (!sdlog) sd.errorHalt("append failed");

  sdlog.close();
}

/*
 *
 */
void sdSetup(void) {
  delay(400);

  // initialize the SD card at SPI_HALF_SPEED to avoid bus errors with
  // breadboards.  use SPI_FULL_SPEED for better performance.
  if (!sd.begin(chipSelect, SPI_HALF_SPEED)) sd.initErrorHalt();

  // create dir if needed
  dirName = "LOGS/2013/" +
    (String(month / 10)) + (String(month % 10)) + "/" +
    (dayOfMonth / 10) + (dayOfMonth % 10) + "/" +
    (hour / 10) + (hour % 10) +
    (minute / 10) + (minute % 10) + 
    (second / 10) + (second % 10);
  char dirName_c[dirName.length()+1];
  dirName.toCharArray(dirName_c, dirName.length()+1);
  sd.mkdir(dirName_c);

  fileName = dirName + "/LOGFILE.TXT";
  
  // append a line to the logfile
  logEvent("Another line for the logfile");

  Serial.println("Done - check " + fileName + " on the SD");
}

void Log2SD() {
  char msg[Log.length() + 1];
  Log.toCharArray(msg, Log.length() + 1);
  logEvent(msg);
  Log = "";

  Serial.println("Done - saved data");
}






