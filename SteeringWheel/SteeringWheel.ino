

#include <TinyPinChange.h>
#include <SoftSerial.h>
 

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPinH = 1; 
const int analogInPinV = 0;
int LedV = 0;


//Variables
int sensorValueH = 0;
int sensorValueV = 0; 
int inByte = 0;         // incoming serial byte
byte SendSer[6] ;
int i;

//setup seriel comm

#define DEBUG_TX_RX_PIN         1 //Adjust here your Tx/Rx debug pin

SoftSerial MyDbgSerial(DEBUG_TX_RX_PIN, DEBUG_TX_RX_PIN, true); //true allows to connect to a regular RS232 without RS232 line driver


void setup()
{
  MyDbgSerial.begin(38400); //After MyDbgSerial.begin(), the serial port is in rxMode by default

//  MyDbgSerial.txMode(); //Before sending a message, switch to txMode
 
//  MyDbgSerial.rxMode(); //switch to rxMode to be ready to receive some commands
  pinMode(LedV, OUTPUT);   

}

void loop(){

inByte=0;
 if(MyDbgSerial.available())
  {
   inByte= MyDbgSerial.read(); 
  }
  //command byte != 0 ;
  if (inByte == 1) {
   digitalWrite(LedV,HIGH);
  }
  else if  (inByte == 2) {
    digitalWrite(LedV,LOW);
  }

  // read the analog in value:
  sensorValueH = analogRead(analogInPinH);            
  sensorValueV = analogRead(analogInPinV);
  SendSer[0]==9;
  SendSer[1]==9;
  // map it to the range of the analog out:
//  outputValue = map(sensorValueH, 0, 1023, 0, 255);  
  if ((781 < sensorValueH) and (sensorValueH < 1000)){
   // debugPort.print("1_HVol ned" );
   SendSer[2]=1;
  }
  else if ((651 < sensorValueH) and (sensorValueH < 780)){
   // debugPort.print("2_HVol op" );
   SendSer[2]=2;
  }
  else if ((401 < sensorValueH) and (sensorValueH < 650)){
    //debugPort.print("3_HMode" );
   SendSer[2]=3;
  }
  else if ((301 < sensorValueH) and (sensorValueH < 400)){
    //debugPort.print("4_HSeek ned" );
   SendSer[2]=4;
  }
  else if ((150 < sensorValueH) and (sensorValueH < 300)){
    //debugPort.print("5_HSeek op" );
   SendSer[2]=5;
  }
  else {
   SendSer[2]=0;
  }
 if ((651 < sensorValueV) and (sensorValueV < 800)){
   // debugPort.print("6_VVol ned" );
   SendSer[3]=1;
  }
  else if ((401 < sensorValueV) and (sensorValueV < 650)){
    //debugPort.print("7_VHovedTe" );
   SendSer[3]=2;
  }
  else if ((301 < sensorValueV) and (sensorValueV < 400)){
    //debugPort.print("8_VVol op" );
   SendSer[3]=3;
  }
  else if ((150 < sensorValueV) and (sensorValueV < 300)){
    //debugPort.print("9_VRoer" );
   SendSer[3]=4;
  }
  else {
   SendSer[3]=0;
  }
  if(digitalRead(LedV) == HIGH){
   SendSer[4]=1;
  }
   else {
   SendSer[4]=0;
   }
  SendSer[5]=SendSer[2]+SendSer[3]+SendSer[4];

if (inByte != 0) {
MyDbgSerial.txMode(); //Before sending a message, switch to txMode
  for (i=0;i<5 ;i=i+1){
    MyDbgSerial.write(SendSer[i]);    
    }
MyDbgSerial.rxMode(); //switch to rxMode to be ready to receive some commands

}  
} 

