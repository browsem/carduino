

#include <SoftSerial.h>
#include <TinyPinChange.h>
 
#define DEBUG_TX_RX_PIN         2 //Adjust here your Tx/Rx debug pin
 
SoftSerial MyDbgSerial(DEBUG_TX_RX_PIN, DEBUG_TX_RX_PIN, true); //true allows to connect to a regular RS232 without RS232 line driver

//

// Initialize i/o

//outputs
int onOff = 4;  //brun+orange, 0 Ohm
int resDec = 3; //gul+orange, 1,5 kOhm
int setAcc = 7; //gul+orange, 0 Ohm1
//inputs
int cruiseOn = 8; //Led input, Via optocoupler.
int led = 13;




//variables
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
  pinMode(onOff, OUTPUT);
  pinMode(resDec, OUTPUT);
  pinMode(setAcc, OUTPUT);
  pinMode(led, OUTPUT);


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
while( MyDbgSerial.available() ) {
   commandbuffer[k++] = MyDbgSerial.read();
   if (commandbuffer[0] != 9) {
     k=0;
   }
 }

//test buffer

if ((commandbuffer[0]==9) &&commandbuffer[1]==9){
  ChkSum=(commandbuffer[2]+commandbuffer[3]+commandbuffer[4]);
  if (ChkSum==commandbuffer[5]) {
    for (k=0;k<2 ;k=k+1){
      SteeringWheel[k]=commandbuffer[k+2];
    }
  }
}

     if (SteeringWheel[0] == '1') { // Der er trykket på -vol
       digitalWrite(led,LOW);
     }
     if (SteeringWheel[0] == '2') { // Der er trykket på +vol
        digitalWrite(led,HIGH);   
     }
     if (SteeringWheel[0] == '3') { // Der er trykket på mode
       
     }
     if (SteeringWheel[0] == '4') { // Der er trykket på -seek
     
     }
     if (SteeringWheel[0] == '5') { // Der er trykket på +seek
     
     }
    if (SteeringWheel[1] == '1') { // Der er trykket på Venstre  -vol
       fartPilot("res");
     }
     if (SteeringWheel[1] == '2') { // Der er trykket på høretelefon
      fartPilot("on");
}
    if (SteeringWheel[1] == '3') { // Der er trykket på Venstre +vol
     fartPilot("set");
     }
     if (SteeringWheel[1] == '4') { // Der er trykket på læg på

     }
    if (SteeringWheel[2] =='0') { //led er slukket
      
    }
    if (SteeringWheel[2] =='1') {//led er tændt
      
    }
     
    
  
  
  
  
  
  
  
//endvoid
}



void fartPilot(String mode){
  
  if (mode=="set"){ 
    digitalWrite(onOff, LOW);
    digitalWrite(resDec, LOW);
    digitalWrite(setAcc, HIGH);
  }
  else if(mode=="res"){
   digitalWrite(onOff, LOW);
   digitalWrite(setAcc, LOW);
   digitalWrite(resDec, HIGH);
  }
  else if(mode=="on"){
   Serial.write("!!!"); 
   digitalWrite(resDec, LOW);
   digitalWrite(setAcc, LOW);
   digitalWrite(onOff, HIGH);
  }
  else {
   digitalWrite(resDec, LOW);
   digitalWrite(setAcc, LOW);
   digitalWrite(onOff, LOW);
  } 
}
