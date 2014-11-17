/* Sweep
 by BARRAGAN <http://barraganstudio.com> 
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://arduino.cc/en/Tutorial/Sweep
*/ 

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
Servo myservo1;
Servo myservo2;
                // twelve servo objects can be created on most boards
 
int pos = 0;    // variable to store the servo position 
int button = 53;

int Counter = 0;
void setup() 
{ 
  myservo.attach(5);
  myservo1.attach(6);
  myservo2.attach(7);// attaches the servo on pin 9 to the servo object 
pinMode(button, INPUT);

} 
 
void loop() 
{ 
if (digitalRead(button)==HIGH) {
  Counter++;
}
if Counter==1{
    myservo.write(0);
}
//    myservo1.write(0);
 //   myservo2.write(0);// tell servo to go to position in variable 'pos' 
    delay(1000);                       // waits 15ms for the servo to reach the position 
    myservo.write(180);
//    myservo1.write(180);
//    myservo2.write(180);// tell servo to go to position in variable 'pos' 
    delay(1000);                       // waits 15ms for the servo to reach the position 
    myservo.write(90);
//    myservo1.write(90);
//    myservo2.write(90);// tell servo to go to position in variable 'pos' 


  
} 
