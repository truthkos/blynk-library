#define BLYNK_PRINT Serial
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <BlynkSimpleEthernet.h>
#include <SimpleTimer.h>

// For this example you need to have SimpleTimer library:
//   https://github.com/jfturcot/SimpleTimer
// Visit this page for more information:
//   http://playground.arduino.cc/Code/SimpleTimer

// Auth token you get from App
char auth[] = "00000000000000000000000000000000";

#define LED_PIN 9

SimpleTimer timer;
int t1;

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth);
  pinMode(LED_PIN, OUTPUT);
  t1 = timer.setInterval(500, ledBlynk);
}

BLYNK_ON_WRITE(1)
{
  if (param[0].asInt()) {
    timer.enable(t1);
  } else {
    timer.disable(t1);
  }
  Blynk.virtualWrite(5, millis()/1000);
}

void ledBlynk()
{
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

void loop()
{
  Blynk.run();
  timer.run();
}
