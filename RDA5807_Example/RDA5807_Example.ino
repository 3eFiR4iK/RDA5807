#include <Wire.h>

#include <RDA5807.h>

RDA5807 radio;

char command;


void setup() {
  Serial.begin(9600);
  radio.begin();
}

void loop() {
 
  if (Serial.available()) {
    command = Serial.read();
    //freq = Serial.parseInt();
    switch (command) {
      case 'n':
        radio.seekUp();
        Serial.println("seek up");
        break;
       case 'N':
        radio.seekDown();
        Serial.println("seek down");
        break;
      case 'f':
        radio.off();
        Serial.println("radio off");
        break;
      case 'm':
        radio.mute();
        Serial.println("radio mute");
        break;
      case 'M':
        radio.unmute();
        Serial.println("radio unmute");
        break;
      case 'g':
        Serial.print("chanel = ");
        Serial.print(radio.getFrequency());
        Serial.println(" FM");
        break;
      case 'v':
       Serial.print("volume = ");
       Serial.println(radio.volumeDown());
       break;
      case 'V':
       Serial.print("volume = ");
       Serial.println(radio.volumeUp());
       break;
    }
    //if (freq > 0)
      //setFrequency(freq);
  }
  
}
