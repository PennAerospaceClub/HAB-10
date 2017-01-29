#include <Time.h>
#include <TimeLib.h>

#include <QueueArray.h>
#include <IridiumSBD.h>
#include <SoftwareSerial.h>
#include "Message/Message.cpp"

int rxPin = 10;
int txPin = 11;
int sleepPin = 8;
QueueArray<Message> recMsgs;
QueueArray<Message> sentMsgs;
 
SoftwareSerial nss(rxPin, txPin);
IridiumSBD isbd(nss, sleepPin);
uint8_t buffer[200];

void setup()
{

  int signalQuality = -1;

  Serial.begin(115200);
  nss.begin(19200);

  isbd.attachConsole(Serial);
  isbd.setPowerProfile(1);
  isbd.begin();

//  int err = isbd.getSignalQuality(signalQuality);
//  if (err != 0)
//  {
//    Serial.print("SignalQuality failed: error ");
//    Serial.println(err);
//    return;
//  }

//  Serial.print("Signal quality is ");
//  Serial.println(signalQuality);
//  int err;
//  err = isbd.sendSBDText("Hello, world!");
//  if (err != 0)
//  {
//    Serial.print("sendSBDText failed: error ");
//    Serial.println(err);
//    return;
//  }
//  Serial.println("Hey, it worked!");
//  Serial.print("Messages left: ");
//  Serial.println(isbd.getWaitingMessageCount());
}

void sendMessage(Message m) 
{
  //Converts the Message class array 'message' into the required buffer format. 
  for (int i = 0; i < sizeof(m.message); i++) 
  {
      //Cast each char to a uint8_t
      buffer[i] = (uint8_t) m.message[i];
  }
  //Not sure why this is required, but this is necessary. 
  size_t bufferSize = sizeof(buffer);
  //int error = ...  (Returns non-zero value if an error arises when sending message)
  //Also, keep in mind that we pass in the buffer that has the unint8_t array, but this is overridden 
  // with the values of the newly received message (3rd param is receive buffer)
  int error = isbd.sendReceiveSBDBinary(buffer, sizeof(m.message), buffer, bufferSize);
  //WIP: Error handling 
  if (error != 0) 
  {
    Serial.print("Error: "); Serial.println(error);  
  }
  //create a new empty char array that will be used to create the recv Message obj
  char recvMsg[200];
  //timestamp (epoch timestamp)
  int ts = now();
  //iterate over buffer
  for (int i = 0; i < bufferSize; i++)
  {
     //cast each uint8_t to a char
     recvMsg[i] = (char) buffer[i];
  }
  //Create a message obj from the above params...
  //Notice "RCV".. look at Message.cpp for explanation. 
  //RCV = received msg SND
  Message newMsg = Message(ts, recvMsg, RCV);
  //add it to the queue of received messages
  addMessageToRecvQueue(newMsg);
}

void addMessageToRecvQueue(Message m) 
{
  recMsgs.push(m);
}

void addMessageToSentQueue(Message m) 
{
  sentMsgs.push(m);
}

void loop()
{

}


bool ISBDCallback()
{
   return true;
}

