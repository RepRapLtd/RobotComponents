/*
 * 
 * 470 ohm -> 13
 * 10K -> +5
 * two centre pins -> GND
 * collector -> A0 
 * 
 */



const int modulatePin = 13;
const int sensePin = A0;
const int top = 300;
const int bottom = 4;
bool lastReading = false;
int count = 0;

void PrintInt(int v)
{
    if(v < 0) v = 0;
    if (v < 100) Serial.print('0');
    if (v < 10) Serial.print('0');
    Serial.print(v);
    Serial.print(' ');  
}

bool overTop(int reading)
{
  int d = top - bottom;
  if(reading > bottom + (d*2)/3)
    return true;
  return false;
}

bool underBottom(int reading)
{
  int d = top - bottom;
  if(reading < bottom + d/3)
    return true;
  return false;
}

bool Trigger(int reading)
{
  if(lastReading)
  {
    if(underBottom(reading))
    {
      lastReading = false;
    }
  } else
  {
    if(overTop(reading))
    {
      lastReading = true;
      return true;
    }
  }
  return false;
}

int OptoReading()
{
  int vDark = analogRead(sensePin);
  digitalWrite(modulatePin, HIGH);
  int vLight = analogRead(sensePin);
  digitalWrite(modulatePin, LOW);
  int vDiff = vDark - vLight;

/*
  PrintInt(vLight);
  PrintInt(vDiff);
  if(Trigger(vDiff))
    Serial.print('<');
  Serial.println(); 


  if(vDiff > peak)
    peak = vDiff;
  if(vDiff < trough)
    trough = vDiff; 
    */
    
  return vDiff;  
}


void setup() 
{
  Serial.begin(9600);
  Serial.println("Optosensor test");
  pinMode(modulatePin, OUTPUT);
  digitalWrite(modulatePin, LOW);
  pinMode(sensePin, INPUT);
}

void loop() 
{
  if(Trigger(OptoReading()))
  {
    count++;
    Serial.println(count);
  }

/*  Serial.print("Peak and trough: ");
  Serial.print(peak);
  Serial.print(" ");
  Serial.println(trough);
  Serial.println();
 */ 
  delay(10);
}
