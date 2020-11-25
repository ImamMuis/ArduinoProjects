/*
Project : Automated Color Sorting Object with 5 DOF Arm Robot Controlled by IR Remote
Author  : Imam Muis Hamzah Harahap
Date    : August 31, 2020
*/

#include <Servo.h>
#include <IRremote.h>
#define vcc 2
#define S0 3
#define S1 4
#define S2 5
#define S3 6
#define sensorOut 7

int warna, red, green, blue;
int frequency     = 0;
int color         = 1;
int pos           = 0;
int RECV_PIN      = 13;
int increment     = 10;
int tunda         = 10;
int color_data[3] ={ 0,   0,   0};
int final_color[3]={ 0,   0,   0};
int sudut[5]      ={90, 150, 130, 10, 80};
unsigned long hexcode[10][2] ={
  //    +           -
  {0xC264BDB9, 0x40876B7F}, //Servo 1
  {0x92DA21E3, 0x9F8ECFD5}, //Servo 2
  {0xAC501B83, 0x8A038C3D}, //Servo 3
  {0xEF3B295B, 0x395E479B}, //Servo 4
  {0x82AAE83D, 0x227088F9}, //Servo 5
  {0xB07D8A81, 0xD3ABAEBF}, //Reset & Play
  {0x69C6FA7D, 0xDE4001F }, //1 & 2
  {0x592FA519, 0x4DA7A0BF}, //3 & 4
  {0x3E3D6F9 , 0xFB54EA5B}, //5 & 6
  {0x26B9C4DD, 0x87E5C91F}  //7 & 8
};
 
Servo servo[5];
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(vcc, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  //Setting Frekuensi ke skala 20% dan mematikan sensor dahulu
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  digitalWrite(vcc,LOW);
  
  int i, j=0;
  for(i=12; i>=8; i--){
    servo[j].attach(i);
    j++;
  }
  irrecv.enableIRIn(); // Start the receiver
  delay(tunda);
  for(i=0; i<=4; i++){
    servo[i].write(sudut[i]);
  }
}
 
void loop() {
  if (irrecv.decode(&results)) {
    int i;
    if      (results.value == hexcode[5][0]) {     //Reset posisi
      posreset();
      pos=0;
    }
    else if ((results.value == hexcode[5][1]) && (pos==0)) {     //Play
      color=1;
      play();
      pos=0;
    }
    //========================FIXED POSITION=======================//
    else if ((results.value == hexcode[6][0]) && (pos == 0)) {pos1();}    //Posisi 1
    else if ((results.value == hexcode[6][1]) && (pos == 1)) {pos2();}    //Posisi 2
    else if ((results.value == hexcode[7][0]) && (pos == 2)) {pos3();}    //Posisi 3
    else if ((results.value == hexcode[7][1]) && (pos == 3)) {pos4();}    //Posisi 4
    else if ((results.value == hexcode[8][0]) && (pos == 4)) {pos_red();}     //Posisi Merah
    else if ((results.value == hexcode[8][1]) && (pos == 4)) {pos_green();}   //Posisi Hijau
    else if ((results.value == hexcode[9][0]) && (pos == 4)) {pos_blue();}    //Posisi Biru
    //=============================================================//

    //=========================MANUAL MOVE=========================//
    else if (results.value == hexcode[0][0]) {
      sudut[0] += increment; //Putar Kiri
      if(sudut[0] >= 180){sudut[0] = 180;}
    }
    else if (results.value == hexcode[0][1]){             //Putar Kiri
      sudut[0] -= increment;                  
      if(sudut[0] <= 0){sudut[0] = 0;}
    }
    else if (results.value == hexcode[1][0]){             //Atas
      sudut[1] += increment;                  
      if(sudut[1] >= 180){sudut[1] = 180;}
    }
    else if (results.value == hexcode[1][1]){             //Bawah
      sudut[1] -= increment;                  
      if(sudut[1] <= 0){sudut[1] = 0;}
    }
    else if (results.value == hexcode[2][0]){             //Atas
      sudut[2] += increment;                  
      if(sudut[2] >= 180){sudut[2] = 180;}
    }
    else if (results.value == hexcode[2][1]){             //Bawah
      sudut[2] -= increment;                  
      if(sudut[2] <= 0){sudut[2] = 0;}
    }
    else if (results.value == hexcode[3][0]){             //Atas
      sudut[3] += increment;                  
      if(sudut[3] >= 180){sudut[3] = 180;}
    }
    else if (results.value == hexcode[3][1]){             //Bawah
      sudut[3] -= increment;                  
      if(sudut[3] <= 0){sudut[3] = 0;}
    }
    else if (results.value == hexcode[4][0]){             //Tutup
      sudut[4] += increment;                  
      if(sudut[4] >= 90){sudut[4] = 80;}
    }
    else if (results.value == hexcode[4][1]){             //Buka
      sudut[4] -= increment;                  
      if(sudut[4] <= 0){sudut[4] = 40;}
    }
    //=============================================================//
    
    servo_move();

    if(pos==4){
      delay(500);
      color_final();
    }
    else if(pos==5 || pos==6 || pos==7){
      sudut[4]=40;
      servo_move();
      delay(200);
      pos=0;
    }
    
    for(i=0; i<=4; i++){
      Serial.print(sudut[i]);
      Serial.print(", ");
    }
    Serial.print("     0x");
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}

void posreset(){
  //=================PRE MOVE=================//
    if(pos==1){
      servo[2].write(90);
      servo[3].write(10);
      delay(200);
    }
    else if(pos==2){
      int pos_3[5] = {180, 130, 130, 30, 80};
      for(int i=0; i<=4; i++){
        sudut[i] = pos_3[i];
      }
      servo_move();
      delay(300);
    }
    else if(pos==4){
      int pos_4b[5] = {0, 150, 130, 10, 80};
      for(int i=0; i<=4; i++){
        sudut[i] = pos_4b[i];
      }
      servo_move();
      delay(200);
    }
  //==========================================//

  
  //================FINAL MOVE================//
    int pos_reset[5] = {90, 150, 130, 10, 80};
    for(int i=0; i<=4; i++){
      sudut[i] = pos_reset[i];
    }
    pos   = 0;
  //==========================================//
}

void pos1(){
  //=================PRE MOVE=================//
    servo[4].write(40);
    delay(200);
    servo[0].write(180);
    delay(200);
  //==========================================//

  
  //================FINAL MOVE================//
    int pos_1[5] = {180, 120, 160, 50, 40};
    for(int i=0; i<=4; i++){
      sudut[i] = pos_1[i];
    }
    pos=1;
  //==========================================//
}

void pos2(){
  //=================PRE MOVE=================//
    servo[2].write(120);
    delay(20);
    int pos_2[5] = {180, 70, 100, 50, 40};
    for(int i=0; i<=4; i++){
      sudut[i] = pos_2[i];
    }
    servo_move();
    delay(1000);
  //==========================================//


  //================FINAL MOVE================//
    sudut[4] = 70;
    pos=2;
  //==========================================//
}

void pos3(){
  //================FINAL MOVE================//
    posreset();
    pos=3;
  //==========================================//
}

void pos4(){
  //=================PRE MOVE=================//
    servo[0].write(0);
    delay(200);
  //==========================================//


  //================FINAL MOVE================//
    int pos_4[5] = {0, 110, 130, 40, 75};
    for(int i=0; i<=4; i++){
      sudut[i] = pos_4[i];
    }
    pos=4;
  //==========================================//
}

void pos_red(){
  //=================PRE MOVE=================//
    pos4tofinal();
  //==========================================//


  //================FINAL MOVE================//
    int pos_5a[5] = {130, 40, 0, 0, 75};
    for(int i=0; i<=4; i++){
      sudut[i] = pos_5a[i];
    }
    pos=5;
  //====================================//
}

void pos_green(){
  //=================PRE MOVE=================//
    pos4tofinal();
  //==========================================//


  //================FINAL MOVE================//
    int pos_5b[5] = {90, 40, 0, 0, 75};
    for(int i=0; i<=4; i++){
      sudut[i] = pos_5b[i];
    }
    pos=6;
  //==========================================//
}

void pos_blue(){
  //=================PRE MOVE=================//
    int i;
    int pos_5c[5] = {60, 150, 130, 10, 75};
    for(i=0; i<=4; i++){
      sudut[i] = pos_5c[i];
    }
    servo_move();
    delay(200);
    servo[0].write(50);
    servo[2].write(90);
    delay(70);
  //==========================================//

  
  //================FINAL MOVE================//
    int pos_5d[5] = {60, 40, 0, 0, 75};
    for(i=0; i<=4; i++){
      sudut[i] = pos_5d[i];
    }
    pos=7;
  //==========================================//
}


void pos4tofinal(){
  //=================PRE MOVE=================//
    posreset();
    servo_move();
    delay(200);
  //==========================================//

  
  //================FINAL MOVE================//
    servo[2].write(90);
    delay(70);
  //==========================================//
}

void servo_move(){
  delay(tunda);
  for(int i=0; i<=4; i++){
    servo[i].write(sudut[i]);
  }
}

void play(){
  pos1();
  servo_move();
  delay(500);
  pos2();
  servo_move();
  delay(500);
  pos3();
  servo_move();
  delay(500);
  pos4();
  servo_move();
  delay(500);
  color_final();
  delay(100);

  if( (red<=blue) & (red<=green)){//Merah
    warna = 1;
    pos_red();
    Serial.println("Warna : Merah\n");
  }
  else if(green<=blue){//Hijau
    warna = 2;
    pos_green();
    Serial.println("Warna : Hijau\n");
  }
  else if(blue<=green){//Biru
    warna = 3;
    pos_blue();
    Serial.println("Warna : Biru\n");
  }

  servo_move();
  delay(800);
  sudut[4]=40;
  A:
  servo_move();
  delay(500);
  posreset();
  servo_move();
  delay(500);
}

void color_final(){
  int i;
  Serial.print("\n");
  for(i=1; i<=10; i++){
    color_sensor();
  }
  red = final_color[0]/10;
  green = final_color[1]/10;
  blue = final_color[2]/10;
  Serial.print("\nRata-rata:\n");
  Serial.print("R= ");
  Serial.print(red);
  Serial.print("  G= ");
  Serial.print(green);
  Serial.print("  B= ");
  Serial.print(blue);
  Serial.print("\n\n");
  
  for(i=0; i<=2; i++){
    color_data[i]=0;
    final_color[i]=0;
  }
}

void color_sensor(){
  digitalWrite(vcc,HIGH);
  //Scanning kekuatan warna Merah
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  //Hasil Scanning
  frequency = pulseIn(sensorOut, LOW);
  Serial.print("R= ");
  Serial.print(frequency);
  Serial.print("  ");
  color_data[0]=frequency;
  final_color[0] += color_data[0];
  delay(10);

  //Scanning kekuatan warna Hijau
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  //Hasil Scanning
  frequency = pulseIn(sensorOut, LOW);
  Serial.print("G= ");
  Serial.print(frequency);
  Serial.print("  ");
  color_data[1]=frequency;
  final_color[1] += color_data[1];
  delay(10);

  //Scanning kekuatan warna Biru
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  //Hasil Scanning
  frequency = pulseIn(sensorOut, LOW);
  Serial.print("B= ");
  Serial.print(frequency);
  Serial.print("\n");
  color_data[2]=frequency;
  final_color[2] += color_data[2];
  delay(10);  
  digitalWrite(vcc,LOW);
  delay(10);
}
