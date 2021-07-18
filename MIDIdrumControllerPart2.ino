
#include "MIDIUSB.h"
//Constants 
const int buttonBass = 10;
const int buttonSnare = 11;
const int buttonHiHat = 12; 
//Variable for reading push button status
int buttonState = 0;
//Randomized Variables
int randomNote = random(40, 100);
int randomLength = random(50, 1500);
int randomVelocity = random(75, 127);
//int randomChannel = random(0, 15);
int randomVabrato = random(0, 65);
int randomDelay = random(250, 1500);
int potPin = A0;
int potVal;
int beatCount = 0;
int hatArray[] = [42, 44, 46];
int snareArray[] = [41, 43, 45, 47, 48, 50];

void noteOn(byte channel, byte pitch, byte velocity) 
{
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}
void noteOff(byte channel, byte pitch, byte velocity) 
{
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  // initialize the pushbutton pin as an input:
  pinMode(buttonBass, INPUT);
  pinMode(buttonSnare, INPUT);
  pinMode(buttonHiHat, INPUT);
}

void controlChange(byte channel, byte control, byte value) 
{
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void loop() 
{
  int Bass = digitalRead(buttonBass);
  int Snare = digitalRead(buttonSnare);
  int HiHat = digitalRead(buttonHiHat);
  potVal = analogRead(potPin);
  Serial.println(potVal);
  
  //Percussion Notes
  if (Bass == HIGH && (beatCount % 2) ==0)
  {
    noteOn(9, 36, 127);   // Channel 0, middle C, normal velocity
    MidiUSB.flush();
    Serial.println("Sending note on 1");
  }
  if (Snare == HIGH (beatCount + 1 % 2) ==0)
  {
    int randomSnare = map(potVal, 0, 1023, 35, 81);
    noteOn(9, randomSnare, randomVelocity);   // Channel 0, middle C, normal velocity
    MidiUSB.flush();
    Serial.println("Sending note on 2");
  }
  if (HiHat == HIGH beatCount == 0)
  {
    noteOn(9, randomNote, randomVelocity);   // Channel 0, middle C, normal velocity
    MidiUSB.flush();
    Serial.println("Sending note on 3");
  }
  if (Bass == LOW)
  {
    noteOff(9, randomNote, randomVelocity);  // Channel 0, middle C, normal velocity
    MidiUSB.flush();
    Serial.println("Sending note off 1");
  }
  if (Snare == LOW)
  {
    noteOff(9, randomNote, randomVelocity);  // Channel 0, middle C, normal velocity
    MidiUSB.flush();
    Serial.println("Sending note off 2");
  }
  if (HiHat == LOW)
  {
    noteOff(9, randomNote, randomVelocity);  // Channel 0, middle C, normal velocity
    MidiUSB.flush();
    Serial.println("Sending note off 3");
  }
}
