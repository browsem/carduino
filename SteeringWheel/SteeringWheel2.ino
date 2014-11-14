/*
Read analog inputs, evalutate as to witch button is pressed,
Send to other end of half duplex seriel.
 */

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPinH = 1; 
const int analogInPinV = 0;
int LedV = 0;
// Analog input pin that the potentiometer is attached to
//const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValueH = 0;
int sensorValueV = 0; 
int inByte = 0;         // incoming serial byte

//setup seriel comm

#include <TinyPinChange.h>
#include <SoftSerial.h>


#define DEBUG_TX_RX_PIN         1 //Adjust here your Tx/Rx debug pin

SoftSerial MyDbgSerial(DEBUG_TX_RX_PIN, DEBUG_TX_RX_PIN, true); //true allows to connect to a regular RS232 without RS232 line driver


int i=0;

struct SEND_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int RightSwitch;
  int LeftSwitch;
  int LedStatus;
};

//void setup()
//{
//  MyDbgSerial.begin(38400); //After MyDbgSerial.begin(), the serial port is in rxMode by default
//  MyDbgSerial.txMode(); //Before sending a message, switch to txMode
//  MyDbgSerial.println(F("\nDebug enabled"));
//  MyDbgSerial.rxMode(); //switch to rxMode to be ready to receive some commands
//}
// 
//void loop()
//{
//  if(MyDbgSerial.available())
//  {
//    MyDbgSerial.txMode();
//    MyDbgSerial.print(F("\nReceived: "));MyDbgSerial.write(MyDbgSerial.read());MyDbgSerial.print(F("\n"));
//    MyDbgSerial.rxMode();
//  }
//}











void setup() {
  // initialize serial communications at 9600 bps:
  pinMode(LedV, OUTPUT);   
  //*Serial.begin(9600);
   debugPort.begin(9600); 
  
 // establishContact();  // send a byte to establish contact until receiver responds 
}


void loop() {
//modtager seriel kommando fra master.
/*
1= svar med bus ide, flip led
2 = led tænd
3 = led sluk
Sender flg pakker
99abc88
99 start
a= knap til højre 0-5, hvor nul betyder intet trykket
b= knap til venstre 0-4
c= status af led 0-1

*/

//start reading serial
  if( debugPort.available() ){
    i=0;
    i = int(debugPort.read());
    if( i == 1 ){
      if(digitalRead(LedV) == HIGH){
        digitalWrite(LedV, LOW);
      }
      else {
        digitalWrite(LedV, HIGH);
      }
    }
    else if( i == 2){
      digitalWrite(LedV, HIGH);
    }
    else if( i == 3){
      digitalWrite(LedV, LOW);
    }
  if (i !=0) {
    SendVal;
  }
    
 }
  
}  
  
void SendVal(){  
  
  // read the analog in value:
  sensorValueH = analogRead(analogInPinH);            
  sensorValueV = analogRead(analogInPinV);

  // map it to the range of the analog out:
//  outputValue = map(sensorValueH, 0, 1023, 0, 255);  
  // change the analog out value:
//  analogWrite(analogOutPin, outputValue);           

  // print the results to the serial monitor:
  debugPort.print("9");
  debugPort.print(",");
  if ((781 < sensorValueH) and (sensorValueH < 1000)){
   // debugPort.print("1_HVol ned" );
   debugPort.print("1");
  }
  else if ((651 < sensorValueH) and (sensorValueH < 780)){
   // debugPort.print("2_HVol op" );
   debugPort.print("2");
  }
  else if ((401 < sensorValueH) and (sensorValueH < 650)){
    //debugPort.print("3_HMode" );
    debugPort.print("3");
  }
  else if ((301 < sensorValueH) and (sensorValueH < 400)){
    //debugPort.print("4_HSeek ned" );
    debugPort.print("4");
  }
  else if ((150 < sensorValueH) and (sensorValueH < 300)){
    //debugPort.print("5_HSeek op" );
    debugPort.print("5");
  }
  else {
    debugPort.print("0");
  }
  debugPort.print(",");
 if ((651 < sensorValueV) and (sensorValueV < 800)){
   // debugPort.print("6_VVol ned" );
   debugPort.print("1");
  }
  else if ((401 < sensorValueV) and (sensorValueV < 650)){
    //debugPort.print("7_VHovedTe" );
    debugPort.print("2");
  }
  else if ((301 < sensorValueV) and (sensorValueV < 400)){
    //debugPort.print("8_VVol op" );
    debugPort.print("3");
  }
  else if ((150 < sensorValueV) and (sensorValueV < 300)){
    //debugPort.print("9_VRoer" );
    debugPort.print("4");
  }
  else {
    debugPort.print("0");
  }
  debugPort.print(",");
  if(digitalRead(LedV) == HIGH){
    debugPort.print("1");
  }
   else {
   debugPort.print("0");
   }
   debugPort.print(",");
  debugPort.print("8");
  debugPort.println();
 
  


}


