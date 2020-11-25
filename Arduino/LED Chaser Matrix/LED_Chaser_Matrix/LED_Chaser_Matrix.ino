int pin;
int potpin = 0; 
int tunda=2000;
int Baris[8]={A1, A2, A3, A4, A5,  5, 4, 3}; //negatif
int Kolom[8]={13, 12, 11, 10,  9,  8, 7, 6}; //positif

void setup(){
  for(pin=0; pin<=7; pin++){
    pinMode(Baris[pin], OUTPUT);
    pinMode(Kolom[pin], OUTPUT); 
  }
  off();
}

  
void loop(){
  test();
}

void test(){
  int j;
  for(int pina=0; pina<=7; pina++){
    digitalWrite(Kolom[pina], HIGH);
    for(int pin=0; pin<=7; pin++){
      digitalWrite(Baris[pin], LOW);
      j = analogRead(potpin);
      j = map(j, 0, 1023, 3, 65);
      delay(j);
      digitalWrite(Baris[pin], HIGH);
    }
    KolomOff();
  }
}

void smoothblink(){
  int t;
  for(t=0;t<=20;t++){
    off();
    delay(20-t);
    on();
    delay(t);
  }
  delay(tunda); 
  for(t=0;t<=20;t++){
    on();
    delay(20-t);
    off();
    delay(t);
  }
  delay(tunda); 
}

void off(){
  for(pin=0; pin<=7; pin++){
    digitalWrite(Baris[pin], HIGH);
    digitalWrite(Kolom[pin], LOW);
  }
}
void on(){
  for(pin=0; pin<=7; pin++){
    digitalWrite(Baris[pin], LOW);
    digitalWrite(Kolom[pin], HIGH);
  }
}

void BarisOff(){
  for(pin=0; pin<=7; pin++){
    digitalWrite(Baris[pin], HIGH);
  }
}
void BarisOn(){
  for(pin=0; pin<=7; pin++){
    digitalWrite(Baris[pin], LOW);
  }
}

void KolomOff(){
  for(pin=0; pin<=7; pin++){
    digitalWrite(Kolom[pin], LOW);
  }
}
void KolomOn(){
  for(pin=0; pin<=7; pin++){
    digitalWrite(Kolom[pin], HIGH);
  }
}
