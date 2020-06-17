#include <DMXSerial.h>

const int dmxStartAddr = 1;
int timerCount;

void setup() {

  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);

  DMXSerial.init(DMXReceiver);

  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  pinMode(4, OUTPUT);
}

ISR(TIMER0_COMPA_vect){
  timerCount++;
}

void loop() {
  for (int i = 0; i <= 255; i++) {
    analogWrite(9, i);
    analogWrite(10, 255 - i);
    delay(5);
  }
  for (int i = 0; i <= 255; i++) {
    analogWrite(11, i);
    analogWrite(9, 255 - i);
    delay(5);
  }
  for (int i = 0; i <= 255; i++) {
    analogWrite(10, i);
    analogWrite(11, 255 - i);
    delay(5);
  }
  
  if (timerCount >= 100) {
    // Blink status LED if DMX receiving
    if (DMXSerial.noDataSince() < 1000) {
      digitalWrite(4, digitalRead(4) ^ 1);
      
    //   Turn status LED off if no DMX received
    }else
      digitalWrite(4, LOW);
    timerCount = 0;
  }

  int r = DMXSerial.read(dmxStartAddr);
  int g = DMXSerial.read(dmxStartAddr + 1);
  int b = DMXSerial.read(dmxStartAddr + 2);

//  Serial.println("Red in: " + r);
//  Serial.println("Green in: " + g);
//  Serial.println("Blue in: " + b);

  analogWrite(9, r);
  analogWrite(10, g);
  analogWrite(11, b);
}
