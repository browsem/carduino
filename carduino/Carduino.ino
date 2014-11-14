

#include <SoftSerial.h>
#include <TinyPinChange.h>
 
#define DEBUG_TX_RX_PIN         2 //Adjust here your Tx/Rx debug pin
 
SoftSerial MyDbgSerial(DEBUG_TX_RX_PIN, DEBUG_TX_RX_PIN, true); //true allows to connect to a regular RS232 without RS232 line driver

unsigned long Timer = 0;
unsigned long LastTimerHit = 0;
byte SteeringWheel[4] = {0,0,0};
byte commandbuffer[7] ;
int k;
int ChkSum;
 
void setup()
{
  MyDbgSerial.begin(38400); //After MyDbgSerial.begin(), the serial port is in rxMode by default
  MyDbgSerial.txMode(); //Before sending a message, switch to txMode
  MyDbgSerial.println(F("\nDebug enabled"));
  MyDbgSerial.rxMode(); //switch to rxMode to be ready to receive some commands

}
 
void loop()
{
  //every * milliseconds
if (millis()-Timer >=100) {  
  Timer=millis();
  if(MyDbgSerial.available()) // if softserial is availabe
  {
    MyDbgSerial.txMode();  //switch to send mode
    MyDbgSerial.write(1); //send a command number
    MyDbgSerial.print('\n'); //send a newline
    MyDbgSerial.rxMode(); //change to recieve mode
  }
}
k=0;
//empty command buffer
for (k=0;k<5 ;k=k+1){
  commandbuffer[k] =0;
  }
//Fill command buffer, if theres anything there
while( Serial.available() ) {
   commandbuffer[k++] = Serial.read();
   if (commandbuffer[0] != 9) {
     k=0;
   }
 }

//test buffer, and write I/O's

if ((commandbuffer[0]==9) &&commandbuffer[1]==9){
  ChkSum=(commandbuffer[2]+commandbuffer[3]+commandbuffer[4]);
  if (ChkSum==commandbuffer[5]) {
    for (k=0;k<2 ;k=k+1){
      SteeringWheel[k]=commandbuffer[0+2];
    }
  }
}

  
//endvoid
}
