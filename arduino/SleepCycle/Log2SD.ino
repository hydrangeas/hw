#include <SdFat.h>

// SD chip select pin
const uint8_t chipSelect = SS;

// file system object
SdFat sd;

// define a serial output stream
ArduinoOutStream cout(Serial);


/*
 * Append a line to LOGFILE.TXT
 */
void logEvent(const char *msg) {
  // create dir if needed
  sd.mkdir("LOGS/2011/JAN");

  // create or open a file for append
  ofstream sdlog("LOGS/2011/JAN/LOGFILE.TXT", ios::out | ios::app);

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

  // append a line to the logfile
  logEvent("Another line for the logfile");
  
  Serial.print("Done - check /LOGS/2011/JAN/LOGFILE.TXT on the SD");
}


