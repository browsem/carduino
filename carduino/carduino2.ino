/* My Cardoino setup



*/

//Define serial port
#include <SoftwareSerialWithHalfDuplex.h>
#define comPin 2

SoftwareSerialWithHalfDuplex debugPort(comPin,comPin,false,false);

// Initialize i/o

//outputs
int onOff = 4;  //brun+orange, 0 Ohm
int resDec = 3; //gul+orange, 1,5 kOhm
int setAcc = 7; //gul+orange, 0 Ohm1
//inputs
int cruiseOn = 8; //Led input, Via optocoupler.
int led = 13;
int i=0;
int ledval=0;

//variable 
boolean cruiseVal =LOW;

//int  venstre =0; 
//int hoejre =0;
//int ratLed=0;
//int ComInt=2; 
int intArray[6];
//char CharArray2[6];
//char inchar;
//byte index=0;

// the setup routine runs once when you press reset:
void setup() {
 //Initialise inputs and outputs
  pinMode(onOff, OUTPUT);
  pinMode(resDec, OUTPUT);
  pinMode(setAcc, OUTPUT);
  Serial.begin(9600);
 debugPort.begin(9600); 
 
 }
 
 
 
 // the main code body
 void ReadDuplex(){
//start med at sende hvilken status led'en bør have
    if( debugPort.available() ){
      //bed om data
      //hvis ikke i er defineret, så set ledval til 4
      //dette ændrer ikke noget i rattet, men sender data retur
      if (i==0) {
        ledval=4;
      }
      else{
        ledval=i;
      }
      //bed rat om data/ændre status på led
     debugPort.write(ledval);
     //læs de data, der kommer retur
     while (debugPort.available()>0){
          for(int y = 0 ; y < 5 ; y++ ) {
            
           intArray[y]=debugPort.parseInt();
         }  
        }
     }
}
     

 void loop(){

  //læs seriel
if( Serial.available()){
  i = int(Serial.read())-48;
}   
                
ReadDuplex();

for(int y = 0 ; y < 4 ; y++ ) {
  
  Serial.print(intArray[y]);
}
Serial.println();


 }
 
// void later(){
//
//
//
//
//      char i= debugPort.read();
//      if (i=='9' ) {
//        CharArray[0] = i;
//        CharArray[1] = debugPort.read();
//        CharArray[2] = debugPort.read();
//        CharArray[3] = debugPort.read();
//      }
//      Serial.write(CharArray[0]);
//      Serial.write(CharArray[1]);
//      Serial.write(CharArray[2]);
//      Serial.write(CharArray[3]);
//       
//     }
//     //Gør noget med inputs
//     if (CharArray[1] == '1') { // Der er trykket på -vol
//       digitalWrite(led,LOW);
//     }
//     if (CharArray[1] == '2') { // Der er trykket på +vol
//        digitalWrite(led,HIGH);   
//     }
//     if (CharArray[1] == '3') { // Der er trykket på mode
//       
//     }
//     if (CharArray[1] == '4') { // Der er trykket på -seek
//     
//     }
//     if (CharArray[1] == '5') { // Der er trykket på +seek
//     
//     }
//     if (CharArray[2] == '1') { // Der er trykket på Venstre  -vol
//       fartPilot("res");
//     }
//     if (CharArray[2] == '2') { // Der er trykket på høretelefon
//       fartPilot("on");
//     }
//     if (CharArray[2] == '3') { // Der er trykket på Venstre +vol
//     fartPilot("set");
//     }
//     if (CharArray[2] == '4') { // Der er trykket på læg på
//         ComInt=2; //on led
//        Serial.print (" LED ON ");
//        debugPort.write(ComInt);
//        delay (1000);
//     }
//    if (CharArray[3] =='0') { //led er slukket
//      
//    }
//    if (CharArray[3] =='1') {//led er tændt
//      
//    }
//    if (cruiseVal==HIGH){
//        ComInt=2; //tænd
//        Serial.print (" Cruiseval:HIGH ");
//        debugPort.write(ComInt);
//     }
//     if (cruiseVal==LOW){
//        ComInt=3; //sluk
//        Serial.print (" Cruiseval:LOW ");
//        debugPort.write(ComInt);
//     }
//     
// Serial.println();     
//     
  //tænd for fartpiloten, hvis den er slukket
  
//  if (cruiseVal==LOW ){
//    fartPilot("on");
//   Serial.write(" LOW");
//   Serial.println();
//  } 
//  else {
//   Serial.write("HIGH");
//    Serial.println();
//    fartPilot(" ");
// }
  
  
// }
 
 
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
