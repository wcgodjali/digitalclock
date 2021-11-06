#include <TimerOne.h>
int count = 0;
// Konfigurasi PIN LED
int pinDigit0 = 10;
int pinDigit1 = 11;
int pinDigit2 = 12;
int pinA = 2; 
int pinB = 3;
int pinC = 4;
int pinD = 5;
int pinE = 6;
int pinF = 7;
int pinG = 8;

void matiin_semua(void){
  for(int j = 2; j <13; j++){
    digitalWrite(j, LOW);
  } 
}

void Nyalain_LED(int digit, int nilai){
  // Nyalain Digit
  digitalWrite(digit, HIGH);
  // Nyalain Angka
  if(nilai == 0){
    digitalWrite(2, LOW);digitalWrite(3, LOW);digitalWrite(4, LOW);digitalWrite(5, LOW);digitalWrite(6, LOW);
    digitalWrite(7, LOW);digitalWrite(8, HIGH);
  }
  else if(nilai == 1){
    digitalWrite(2, HIGH);digitalWrite(3, LOW);digitalWrite(4, LOW);digitalWrite(5, HIGH);digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);digitalWrite(8, HIGH);
  }
  else if(nilai == 2){
    digitalWrite(2, LOW);digitalWrite(3, LOW);digitalWrite(4, HIGH);digitalWrite(5, LOW);digitalWrite(6, LOW);
    digitalWrite(7, HIGH);digitalWrite(8, LOW);
  }
  else if(nilai == 3){
    digitalWrite(2, LOW);digitalWrite(3, LOW);digitalWrite(4, LOW);digitalWrite(5, LOW);digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);digitalWrite(8, LOW);
  }
  else if(nilai == 4){
    digitalWrite(2, HIGH);digitalWrite(3, LOW);digitalWrite(4, LOW);digitalWrite(5, HIGH);digitalWrite(6, HIGH);
    digitalWrite(7, LOW);digitalWrite(8, LOW);
  }
  else if(nilai == 5){
    digitalWrite(2, LOW);digitalWrite(3, HIGH);digitalWrite(4, LOW);digitalWrite(5, LOW);digitalWrite(6, HIGH);
    digitalWrite(7, LOW);digitalWrite(8, LOW);
  }
  else if(nilai == 6){
    digitalWrite(2, LOW);digitalWrite(3, HIGH);digitalWrite(4, LOW);digitalWrite(5, LOW);digitalWrite(6, LOW);
    digitalWrite(7, LOW);digitalWrite(8, LOW);
  }
  else if(nilai == 7){
    digitalWrite(2, LOW);digitalWrite(3, LOW);digitalWrite(4, LOW);digitalWrite(5, HIGH);digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);digitalWrite(8, HIGH);
  }
  else if(nilai == 8){
    digitalWrite(2, LOW);digitalWrite(3, LOW);digitalWrite(4, LOW);digitalWrite(5, LOW);digitalWrite(6, LOW);
    digitalWrite(7, LOW);digitalWrite(8, LOW);
  }
  else{
    digitalWrite(2, LOW);digitalWrite(3, LOW);digitalWrite(4, LOW);digitalWrite(5, LOW);digitalWrite(6, HIGH);
    digitalWrite(7, LOW);digitalWrite(8, LOW);
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9300);                // Transfer data dengan bitrate 9300 baud
  pinMode(pinDigit0, OUTPUT); 
  pinMode(pinDigit1, OUTPUT);
  pinMode(pinDigit2, OUTPUT);
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  //matiin_semua();
  // Disable RX/TX
  UCSR0B=0x00;
  Timer1.initialize(1000000); 
  Timer1.attachInterrupt(InterruptSubroutine);        
}

void loop() {
  if(count == 1000){
    count = 0;
  }
  matiin_semua();
  Nyalain_LED(pinDigit0, count % 10);
  delay(10);
  matiin_semua();
  Nyalain_LED(pinDigit1, (count / 10) % 10);
  delay(10);
  matiin_semua();
  Nyalain_LED(pinDigit2, count / 100);
  delay(10);
}

void InterruptSubroutine(){
  count += 1;
}
