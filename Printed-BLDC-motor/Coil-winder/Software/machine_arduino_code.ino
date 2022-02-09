#include <Stepper.h>
#include <Arduino.h>
#include "BasicStepperDriver.h"
#include "MultiDriver.h"
#include "SyncDriver.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX
float A = 0;
float B = 0;
int state = 0;
String message;
int QTY, numMessages, endBytes;
byte inByte;
int flag = 0;
int lastflag = 0;
int C=0;



#define MOTOR_STEPS 200
#define DIR_X 14
#define STEP_X 15
#define DIR_Y 16
#define STEP_Y 17
#define MICROSTEPS 16
#define MOTOR_X_RPM 50
#define MOTOR_Y_RPM 350
#define pause 12

BasicStepperDriver stepperX(200, DIR_X, STEP_X);
BasicStepperDriver stepperY(160, DIR_Y, STEP_Y);
SyncDriver controller(stepperX, stepperY);


void setup()
{
  numMessages, endBytes = 0;
  
  pinMode (pause,OUTPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
  stepperX.begin(MOTOR_X_RPM, MICROSTEPS);
    stepperY.begin(MOTOR_Y_RPM, MICROSTEPS);
    digitalWrite (pause,HIGH);
  delay(500);
  
}

void loop()
{
  data();
  
  if (A > 0 && B > 0) {
    delay(1000);
   


C = 360/A;
digitalWrite (pause,LOW);

    for (int i = 0; i < A; i++) {
      delay(1000);
      


if (flag == 0){

       for (int i = 0; i < B; i++){
  controller.rotate(0, 360);
   }
  flag = 1; 
}




else {
  for (int i = 0; i < B; i++){
  controller.rotate(0, -360);
   }
   flag = 0;
}

 if (i<A-1){

delay(1000);
 controller.rotate(C, 0 );

 }
 
    

    }
 
    
    A=0;
    B=0;

  }
digitalWrite (pause,HIGH);
  
}

  void data() {
    if (state < 1) {
      if (numMessages == 1) { //Did we receive the anticipated number of messages? In this case we only want to receive 1 message.
        A = QTY;
        Serial.println(A);//See what the important message is that the Arduino receives from the Nextion
        numMessages = 0; //Now that the entire set of data is received, reset the number of messages received
        state = 1;
      }
    }

    if (state > 0) {
      if (numMessages == 1) { //Did we receive the anticipated number of messages? In this case we only want to receive 1 message.
        B = QTY;
        Serial.println(B);//See what the important message is that the Arduino receives from the Nextion
        numMessages = 0; //Now that the entire set of data is received, reset the number of messages received
        state = 0;
      }
    }






    if (mySerial.available()) { //Is data coming through the serial from the Nextion?
      inByte = mySerial.read();

      // Serial.println(inByte); //See the data as it comes in

      if (inByte > 47 && inByte < 58) { //Is it data that we want to use?
        message.concat(char(inByte)); //Cast the decimal number to a character and add it to the message
      }
      else if (inByte == 255) { //Is it an end byte?
        endBytes = endBytes + 1; //If so, count it as an end byte.
      }

      if (inByte == 255 && endBytes == 3) { //Is it the 3rd (aka last) end byte?
        QTY = message.toInt(); //Because we have now received the whole message, we can save it in a variable.
        message = ""; //We received the whole message, so now we can clear the variable to avoid getting mixed messages.
        endBytes = 0; //We received the whole message, we need to clear the variable so that we can identify the next message's end
        numMessages  = numMessages + 1; //We received the whole message, therefore we increment the number of messages received.

        //Now lets test if it worked by playing around with the variable.

      }
    }
  }
