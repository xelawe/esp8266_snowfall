#define serdebug
#ifdef serdebug
#define DebugPrint(...) {  Serial.print(__VA_ARGS__); }
#define DebugPrintln(...) {  Serial.println(__VA_ARGS__); }
#else
#define DebugPrint(...) { }
#define DebugPrintln(...) { }
#endif

#include "tools_wifi.h"
#include "ota_tool.h"

void setup() {
  // put your setup code here, to run once:

  wifi_init("NightLight");

  init_ota("SnowFall");
}

void loop() {
  // put your main code here, to run repeatedly:

  check_ota();
}
