#include <IridiumSBD.h>
#include <SoftwareSerial.h>
int rxPin = 10;
int txPin = 11;
int sleepPin = 8;

SoftwareSerial nss(rxPin, txPin);
IridiumSBD isbd(nss, sleepPin);

void setup()
{
//  pinMode(8, OUTPUT);
//  digitalWrite(8, HIGH);
  int signalQuality = -1;

  Serial.begin(115200);
  nss.begin(19200);

  isbd.attachConsole(Serial);
  isbd.setPowerProfile(1);
  isbd.begin();

  int err = isbd.getSignalQuality(signalQuality);
  if (err != 0)
  {
    Serial.print("SignalQuality failed: error ");
    Serial.println(err);
    return;
  }

  Serial.print("Signal quality is ");
  Serial.println(signalQuality);

  err = isbd.sendSBDText("Hello, world!");
  Serial.println("*" + err);
  if (err != 0)
  {
    Serial.println("WTF1");
    Serial.print("sendSBDText failed: error ");
    Serial.println(err);
    Serial.println("WTF2");
    return;
  }
  Serial.println("WTF3");

  Serial.println("Hey, it worked!");
  Serial.print("Messages left: ");
  Serial.println(isbd.getWaitingMessageCount());
}

void loop()
{

}

bool ISBDCallback()
{
   return true;
}
