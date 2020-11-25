/*
Author  : Imam Muis Hamzah Harahap
Date    : September 9, 2019
*/

#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

#define TRIG_PIN A0
#define ECHO_PIN A1
#define MAX_DISTANCE 200

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
AF_DCMotor M_Kanan(3, MOTOR34_1KHZ);
AF_DCMotor M_Kiri (4, MOTOR34_1KHZ);
Servo M_Servo;

boolean go_Maju = false;
int Jarak = 100;
int Kecepatan = 0;

void setup(){
  M_Servo.attach(10);
  M_Servo.write(90);
  delay(2000);
  Jarak = Baca_Sensor();
  delay(10);
  Jarak = Baca_Sensor();
  delay(10);
  Jarak = Baca_Sensor();
  delay(10);
  Jarak = Baca_Sensor();
  delay(10);
}

void loop(){
  int J_Kanan = 0;
  int J_Kiri  = 0;
  delay(10);

  if (Jarak <= 20){
    Mundur();
    delay(200);
    Berhenti();
    delay(200);

    J_Kanan = L_Kanan();
    delay(200);
    J_Kiri  = L_Kiri();
    delay(200);

    if(J_Kanan>=J_Kiri){
      BelokKanan();
      Berhenti();
    }
    else{
      BelokKiri();
      Berhenti();
    }
  }
  else{
    Maju();
  }

  Jarak = Baca_Sensor();
}

int L_Kanan(){
  M_Servo.write(10);
  delay(500);
  int Jarak = Baca_Sensor();
  delay(100);
  M_Servo.write(90);
  return Jarak;
}

int L_Kiri(){
  M_Servo.write(170);
  delay(500);
  int Jarak = Baca_Sensor();
  delay(100);
  M_Servo.write(90);
  return Jarak;
  delay(100);
}

int Baca_Sensor(){
  int cm = sonar.ping_cm();
  if(cm == 0){
    cm = 250;
  }
  return cm;
}

void Berhenti(){
  M_Kanan.run(RELEASE);
  M_Kiri.run(RELEASE);
}

void Maju(){
  if(!go_Maju){
    go_Maju = true;
    M_Kanan.run(FORWARD);
    M_Kanan.setSpeed(255);
    M_Kiri.run(FORWARD);
    M_Kiri.setSpeed(255);
    delay(5);
  }
}

void Mundur(){
  go_Maju = false;
  M_Kanan.run(BACKWARD);
  M_Kanan.setSpeed(255);
  M_Kiri.run(BACKWARD);
  M_Kiri.setSpeed(255);
  delay(5);
}

void BelokKanan(){
  M_Kanan.run(BACKWARD);
  M_Kanan.setSpeed(255);
  M_Kiri.run(FORWARD);
  M_Kiri.setSpeed(255);
  delay(102);
  M_Kanan.run(FORWARD);
  M_Kanan.setSpeed(255);
  M_Kiri.run(FORWARD);
  M_Kiri.setSpeed(255);
}

void BelokKiri(){
  M_Kanan.run(FORWARD);
  M_Kanan.setSpeed(255);
  M_Kiri.run(BACKWARD);
  M_Kiri.setSpeed(190);
  delay(102);
  M_Kanan.run(FORWARD);
  M_Kanan.setSpeed(255);
  M_Kiri.run(FORWARD);
  M_Kiri.setSpeed(255);
}
