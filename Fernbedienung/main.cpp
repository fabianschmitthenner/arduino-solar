#include <WProgram.h>

const int motorId = 5;
const int turnId = 5;

void error (int errorMsg)
{
  for (;;);
}

int readReally ()
{
  int result;
  while ((result = Serial.read ()) == -1);
  return result;
}

int readTurnData ()
{
  Serial.flush();
  Serial.write('K');
  int ack;
  do {
    ack = Serial.read ();
  } while (ack != 'A');
  return readReally ();
}

int main ()
{
  init ();
  
  pinMode (motorId, OUTPUT);
  pinMode (turnId, OUTPUT);
  
  // initialisiere Motor
  analogWrite (motorId, 128);
  delay (1000);
  analogWrite (motorId, 0);
  delay (1000);
  analogWrite (motorId, 255);
  delay (1000);
  
  //bleibe zunächst stehen
  analogWrite (motorId, 128);
  
  Serial.begin (9600);
  
  while (Serial.available() == 0)
  {
    Serial.write ('B');
  }
  
  if (Serial.read() != 'I')
    error (1);
  
  //start running
  int turn = readTurnData ();
  
  
}