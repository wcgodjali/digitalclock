#include <TimerOne.h>
// Variabel untuk menyimpan hitungan waktu
int count = 0;
// Hubungan pin seven segment dengan pinout Arduino Uno
int pinDigit1 = 5;
int pinDigit2 = 6;
int pinDigit3 = 9;
int pinDigit4 = 10;
int pinA = 0; 
int pinB = 1;
int pinC = 11;
int pinD = 13;
int pinE = 4;
int pinF = 7;
int pinG = 8;
int pinButton1 = 2;
int pinButton2 = 3;
int pinButton3 = 12;
// Informasi mengenai Button
int stateButton1 = 0;
int stateButton2 = 0;
int stateButton3 = 0;
int lastState3 = 0;
int currentState3 = 0;
// Informasi mengenai tangkapan waktu
int detik = 0;
int menit = 0;
int jam = 0 ;
int hari = 0;
int bulan = 0;
int tahun = 0;
// Informasi mengenai tangkapan waktu alarm
int alarm_detik = 0;
int alarm_menit = 0;
int alarm_jam = 0;
int alarm_set = 0;
int alarm_nyala = 0;
// Informasi mengenai tangkapan waktu stopwatch
int sw_detik = 0;
int sw_menit = 0;
int sw_trigger = 0;

// Prosedur untuk mencegah terjadi Ghosting
void matiin_semua(void){
  for(int j = 0; j < 13; j++){
    // Mematikan Seven Segment Secara Keseluruhan
    // Untuk pin bukan common akan diberi logika LOW
    if((j!=5) and (j!=6) and (j!=9) and (j!=10)){
      digitalWrite(j, HIGH);
  }
  // Untuk pin common akan diberi logika HIGH
  else{
    digitalWrite(j, LOW);
  }
  } 
}
// Prosedur untuk menyelakan sebuah seven segment
void Nyalain_LED(int digit, int nilai){
  // Nyalain Digit
  digitalWrite(digit, HIGH);
  // Nyalain Angka
  if(nilai == 0){
    digitalWrite(pinA, LOW);digitalWrite(pinB, LOW);digitalWrite(pinC, LOW);digitalWrite(pinD, LOW);digitalWrite(pinE, LOW);
    digitalWrite(pinF, LOW);digitalWrite(pinG, HIGH);
  }
  else if(nilai == 1){
    digitalWrite(pinA, HIGH);digitalWrite(pinB, LOW);digitalWrite(pinC, LOW);digitalWrite(pinD, HIGH);digitalWrite(pinE, HIGH);
    digitalWrite(pinF, HIGH);digitalWrite(pinG, HIGH);
  }
  else if(nilai == 2){
    digitalWrite(pinA, LOW);digitalWrite(pinB, LOW);digitalWrite(pinC, HIGH);digitalWrite(pinD, LOW);digitalWrite(pinE, LOW);
    digitalWrite(pinF, HIGH);digitalWrite(pinG, LOW);
  }
  else if(nilai == 3){
    digitalWrite(pinA, LOW);digitalWrite(pinB, LOW);digitalWrite(pinC, LOW);digitalWrite(pinD, LOW);digitalWrite(pinE, HIGH);
    digitalWrite(pinF, HIGH);digitalWrite(pinG, LOW);
  }
  else if(nilai == 4){
    digitalWrite(pinA, HIGH);digitalWrite(pinB, LOW);digitalWrite(pinC, LOW);digitalWrite(pinD, HIGH);digitalWrite(pinE, HIGH);
    digitalWrite(pinF, LOW);digitalWrite(pinG, LOW);
  }
  else if(nilai == 5){
    digitalWrite(pinA, LOW);digitalWrite(pinB, HIGH);digitalWrite(pinC, LOW);digitalWrite(pinD, LOW);digitalWrite(pinE, HIGH);
    digitalWrite(pinF, LOW);digitalWrite(pinG, LOW);
  }
  else if(nilai == 6){
    digitalWrite(pinA, LOW);digitalWrite(pinB, HIGH);digitalWrite(pinC, LOW);digitalWrite(pinD, LOW);digitalWrite(pinE, LOW);
    digitalWrite(pinF, LOW);digitalWrite(pinG, LOW);
  }
  else if(nilai == 7){
    digitalWrite(pinA, LOW);digitalWrite(pinB, LOW);digitalWrite(pinC, LOW);digitalWrite(pinD, HIGH);digitalWrite(pinE, HIGH);
    digitalWrite(pinF, HIGH);digitalWrite(pinG, HIGH);
  }
  else if(nilai == 8){
    digitalWrite(pinA, LOW);digitalWrite(pinB, LOW);digitalWrite(pinC, LOW);digitalWrite(pinD, LOW);digitalWrite(pinE, LOW);
    digitalWrite(pinF, LOW);digitalWrite(pinG, LOW);
  }
  else{
    digitalWrite(pinA, LOW);digitalWrite(pinB, LOW);digitalWrite(pinC, LOW);digitalWrite(pinD, LOW);digitalWrite(pinE, HIGH);
    digitalWrite(pinF, LOW);digitalWrite(pinG, LOW);
  }
}
// Prosedur untuk melakukan multiplexing pada seven segment 
void tampil_digit(int nilai1,int nilai2,int nilai3,int nilai4){
  matiin_semua();
  Nyalain_LED(pinDigit1, nilai4);
  delay(1);
  matiin_semua();
  Nyalain_LED(pinDigit2, nilai3);
  delay(1);
  matiin_semua();
  Nyalain_LED(pinDigit3, nilai2);
  delay(1);
  matiin_semua();
  Nyalain_LED(pinDigit4, nilai1);
  delay(1);
}
// Interupsi rutin untuk membuat jam tetap menghitung
void InterruptSubroutine(){
  // increment detik dan normalisasi waktu
  detik += 1;
  if(detik > 59){
    menit += 1;
    detik = 0;
  }
  if(menit > 59){
    jam += 1;
    menit = 0;
  }
  if(jam > 23){
    hari += 1;
    jam = 0 ;
  }
  if (hari > 30){
    bulan += 1;
    hari = 0;
  }
  if(bulan > 12){
    tahun += 1;
    bulan = 0;
  }
  // Trigger apabila alarm harus menyala
  if((alarm_detik == detik) & (alarm_menit == menit) & (alarm_jam == jam)){
    alarm_nyala = 1;
  }
  // Apabila stopwatch ditrigger, stopwatch harus mulai menghitung
  if(sw_trigger == 1){
    sw_detik += 1;
    if(sw_detik >59){
      sw_menit += 1;
    }
  }
}
// Perubahan state sistem apabila button 1 dipencet
void button1Pressed(void){
  // Reset state button 2 setiap memasuki fitur baru
  stateButton2 = 0;
  stateButton1 += 1;
  // Merealisasikan Finite State
    if(stateButton1 > 3){
      stateButton1 = 0;
  }
}
// Perubahan state sistem apabila button 2 dipencet
void button2Pressed(void){
  stateButton2 += 1;
  // Mode Penampil Waktu
  if(stateButton1 == 0){
    if(stateButton2 > 3){
      stateButton2 = 0;
    }
  }
  // Mode Penyetel Waktu
  else if (stateButton1 == 1){
    if(stateButton2 > 4){
      stateButton2 = 0;
    }
  }
  // Mode Alarm
  else if (stateButton1 == 2){
    if(stateButton2 > 3){
      stateButton2 = 0;
    }
  }
  // Mode Stopwatch
  else {
    if(stateButton2 > 3){
      stateButton2 = 0;
    } 
  }
}
// Interupsi Button yang menyebabkan perubahan
ISR (PCINT0_vect){
  currentState3 = digitalRead(pinButton3);
  if(currentState3 == LOW){
    // Mode Penyetel Waktu
    if(stateButton1 == 1){
      // Menyetel Menit
    if(stateButton2 == 0){
      menit += 1;
    }
    // Menyetel Jam
    else if(stateButton2 == 1){
      jam += 1;
    }
    // Menyetel Hari
    else if(stateButton2 == 2){
      hari += 1;
    }
    // Menyetel Bulan
    else if(stateButton2 == 3){
      bulan += 1;
      }
    }
    // Mode Alarm
    if(stateButton1 == 2){
      // Menyetel Detik
      if(stateButton2 == 0){
        alarm_detik += 1;
        if(alarm_detik > 60){
          alarm_detik = 0;
        }
      }
      // Menyetel Menit
      if(stateButton2 == 1){
        alarm_menit += 1;
        if(alarm_menit > 60){
          alarm_menit = 0;
        }
      }
      // Menyetel Jam
      if(stateButton2 == 2){
        alarm_jam += 1;
        if(alarm_jam > 23){
          alarm_menit = 0;
        }
      }
    }
  }
  delay(300);
}

void setup() {
  // Mengatur Pin Input/Ouput 
  pinMode(pinDigit1, OUTPUT); 
  pinMode(pinDigit2, OUTPUT);
  pinMode(pinDigit3, OUTPUT);
  pinMode(pinDigit4, OUTPUT);
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinButton1, INPUT_PULLUP);
  pinMode(pinButton2, INPUT_PULLUP);
  pinMode(pinButton3, INPUT_PULLUP);
  // Disable Serial agar dapat memanfaatkan port 1 dan 2
  UCSR0B=0x00;
  // Normalisasi Seven segment
  matiin_semua();
  // Interupsi Timer untuk memanggil subrutin setiap satu detik
  Timer1.initialize(1000000); 
  Timer1.attachInterrupt(InterruptSubroutine);
  // Perhatikan bahwa tombol di-PULLUP
  attachInterrupt(digitalPinToInterrupt(2),button1Pressed,FALLING);
  attachInterrupt(digitalPinToInterrupt(3),button2Pressed,FALLING);
  PCICR |= B00000001 ;  // Mengatur register PCICR agar mengaktifkan grup 1
  PCMSK0 |= B00010000 ; // Mengatur target pin yang dapat melakukan interupsi yaitu pin 12
}

void loop() {
  // Kondisi alarm tidak menyala
  if(alarm_nyala != 1){
  // PENAMPIL WAKTU  
  if (stateButton1 == 0){
    // Mode Menit-Detik
    if(stateButton2 == 0){
      tampil_digit(menit / 10, menit % 10, detik / 10, detik % 10);
    }
    // Mode Jam - menit
    else if(stateButton2 == 1){
      tampil_digit(jam / 10, jam % 10, menit / 10, menit % 10);
    }
    // Mode Tanggal-Bulan
    else if(stateButton2 == 2){
      tampil_digit(hari / 10, hari % 10, bulan / 10, bulan % 10);
    }
    // Mode Bulan-Tahun
    else{
      tampil_digit(bulan / 10, bulan % 10, tahun / 10, tahun % 10);
    }
  }
  // PENYETEL WAKTU
  else if(stateButton1 == 1){
    // Setel Menit
    if(stateButton2 == 0){
      tampil_digit(menit / 10, menit % 10, detik / 10, detik % 10);
    }
    // Setel Jam
    else if(stateButton2 == 1){
      tampil_digit(jam / 10, jam % 10, menit / 10, menit % 10);
    }
    // Setel Hari
    else if(stateButton2 == 2){
      tampil_digit(hari / 10, hari % 10, bulan / 10, bulan % 10);
    }
    // Setel Bulan
    else{
      tampil_digit(bulan / 10, bulan % 10, tahun / 10, tahun % 10);
    }
  }
  // ALARM
  else if(stateButton1 == 2){
    // Mode Setting
    // Setting detik
    if(stateButton2 == 0){
      tampil_digit(alarm_menit / 10, alarm_menit % 10, alarm_detik / 10, alarm_detik % 10);
    }
    // Setting menit
    else if (stateButton2 == 1){
      tampil_digit(alarm_jam / 10, alarm_jam % 10, alarm_menit / 10, alarm_menit % 10);
    }
    // Setting jam
    else if (stateButton2 == 2){
      tampil_digit(alarm_jam / 10, alarm_jam % 10, alarm_menit / 10, alarm_menit % 10);
    }
  }
  // STOPWATCH
  else if(stateButton1 == 3){
    tampil_digit(sw_menit / 10, sw_menit % 10, sw_detik / 10, sw_detik % 10);
    if(stateButton2 == 0){
      sw_menit = 0;
      sw_detik = 0;
    }
    else if(stateButton2 == 1){
      sw_trigger = 1;
    }
    else if(stateButton2 == 2){
      sw_trigger = 0;
    }
  }
  }
  // Apabila terjadi Alarm
  else{
    // LED Berkelap-kelip
    digitalWrite(14, HIGH);
    delay(1000);
    digitalWrite(14, LOW);
    delay(1000);
    digitalWrite(14, HIGH);
    delay(1000);
    digitalWrite(14, LOW);
    delay(1000);
    digitalWrite(14, HIGH);
    delay(1000);
    digitalWrite(14, LOW);
    delay(1000);
    digitalWrite(14, HIGH);
    delay(1000);
    digitalWrite(14, LOW);
    delay(1000);
    // Alarm Otomatis reset
    alarm_detik = 0;
    alarm_menit = 0;
    alarm_jam = 0;
    alarm_nyala = 0;
  }
}
