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
#include <Ticker.h>

Ticker TickerLED[8];
int PinLED[] = {15, 13, 12, 14, 4, 5, 9, 10 };


void toggleLED(int iv_LEDnbr) {
  int lv_LEDstat;

  TickerLED[iv_LEDnbr].detach();

  lv_LEDstat = digitalRead(PinLED[iv_LEDnbr]);
  DebugPrint("LED ");
  DebugPrint(iv_LEDnbr);
  DebugPrint(" Pin ");
  DebugPrint(PinLED[iv_LEDnbr]);
  DebugPrint(" Status ");
  DebugPrintln(lv_LEDstat);

  if (lv_LEDstat == HIGH) {
    digitalWrite(PinLED[iv_LEDnbr], LOW);
    int lv_timeWait = random(2, 30);
    DebugPrint("LED ");
    DebugPrint(iv_LEDnbr);
    DebugPrint(" Wait ");
    DebugPrintln(lv_timeWait);
    TickerLED[iv_LEDnbr].attach( lv_timeWait, toggleLED, iv_LEDnbr);
  } else {
    digitalWrite(PinLED[iv_LEDnbr], HIGH);
    DebugPrint("LED ");
    DebugPrint(iv_LEDnbr);
    DebugPrint(" On ");
    DebugPrintln(1);
    TickerLED[iv_LEDnbr].attach(1, toggleLED, iv_LEDnbr);
  }

}

void init_LED() {
  for (int i = 0; i < 6; i++) {
    DebugPrint("LED ");
    DebugPrintln(i);
    pinMode(PinLED[i], OUTPUT);
    digitalWrite(PinLED[i], HIGH);
    TickerLED[i].attach(1, toggleLED, i);
    delay(50);
  }
}

void setup() {
  // put your setup code here, to run once:
#ifdef serdebug
  Serial.begin(115200);
#endif

  wifi_init("NightLight");

  init_ota("SnowFall");

  init_LED();
}

void loop() {
  // put your main code here, to run repeatedly:

  check_ota();

  delay(500);
}
