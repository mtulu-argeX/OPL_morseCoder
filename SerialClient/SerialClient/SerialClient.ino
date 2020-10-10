#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
int data;
unsigned long duration;
bool startTx;

double currentTime = 0;
double lastTime = 0;

double getLastTime(){
      return currentTime = millis()/1000.0 - lastTime;
}

void setup() {
  // Open serial communications and wait for port to open:
  pinMode(9, OUTPUT);
  pinMode(A0, OUTPUT);

  // set the data rate for the SoftwareSerial port
  mySerial.begin(19200);
  
  startTx = 0;
  digitalWrite(A0, HIGH);
}

void loop() { // run over and over

  if (mySerial.available()) {
    if(startTx == 0){
      digitalWrite(A0, LOW);
      startTx = 1; 
     }
    
    data = (mySerial.parseInt() * 1000) / 32;
    duration = (unsigned long)data;
    if(duration > 0){
        tone(9,  641, duration);
    }
    lastTime = millis()/1000.0;
  }

  if (getLastTime() > 0.2){

    startTx = 0;
    digitalWrite(A0, HIGH);
    
  }
  
}

