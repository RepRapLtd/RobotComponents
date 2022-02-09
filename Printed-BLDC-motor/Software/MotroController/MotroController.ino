 /*

Simple control program for the motor controller.

RepRap Ltd
https://reprapltd.com

Adrian Bowyer
19 January 2022

Licence: GPL


*/


int speedPin = 3;
int enablePin = 4;
int directionPin = 5;
int brakePin = 6;
int tachoPin = 7;

void Help()
{
  Serial.println("\nCommands:");
  Serial.println(" sN, N = [0, 255] - set speed");
  Serial.println(" f - go forwards");
  Serial.println(" b - go backwards");
  Serial.println(" k - break");
  Serial.println(" d - disable");
  Serial.println(" tN - measure speed for N seconds\n");
}

void setup()
{

  pinMode(speedPin, OUTPUT);
  analogWrite(speedPin, 0);
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, 0);
  pinMode(directionPin, OUTPUT);
  digitalWrite(directionPin, 1);
  pinMode(brakePin, OUTPUT);
  digitalWrite(brakePin, 1);
  pinMode(tachoPin, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Motor controller");
  Help();
}

void MeasureSpeed(int seconds)
{
  long startTime = micros();
  long lastTime = startTime;
  int count = 0;
  double average = 0;
  int secs = 0;
  int state = digitalRead(tachoPin);
  do
  {
    int s = digitalRead(tachoPin);
    long t = micros();
    secs = (t - startTime)/1000000;
    
    if(s ^ state)
    {
      state = s;
      if(s == 0)
      {
        t = t - lastTime;
        lastTime = t;
        average = count*average + t;
        count++;
        average = average/count;
      }
    }
    
  } while(secs < seconds);
  Serial.print("\nAverage tacho pulse (us) = ");
  Serial.println(average);
}

void loop()
{
  int command;
  int speed;
  int seconds;
  if(Serial.available() > 0)
  {
    command = Serial.read();
    switch(command)
    {
      case 's':
        speed = Serial.parseInt();
        analogWrite(speedPin, speed);
        break;

      case 'f':
        digitalWrite(enablePin, 1);
        digitalWrite(brakePin, 1);
        digitalWrite(directionPin, 1);
        break;

      case 'b':
        digitalWrite(enablePin, 1);
        digitalWrite(brakePin, 1);
        digitalWrite(directionPin, 0);
        break;

      case 'k':
        digitalWrite(brakePin, 0);
        break;

      case 'd':
        digitalWrite(enablePin, 0);
        break;

      case 't':
        seconds = Serial.parseInt();
        MeasureSpeed(seconds);
        break;

      case '\r':
      case '\n':
        break;
        
      default:
       Serial.print("Unrecognised command - ");
       Serial.println((char)command);
       Help();
    }
    while(Serial.available() > 0)
      command = Serial.read();
  }
}
