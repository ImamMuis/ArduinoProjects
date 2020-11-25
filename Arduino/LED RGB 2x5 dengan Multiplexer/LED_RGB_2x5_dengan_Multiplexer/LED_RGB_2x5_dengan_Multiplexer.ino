/*
Author  : Imam Muis Hamzah Harahap
Date    : March 18, 2019
*/

int AnodePin[6] = {3, 5, 6, 9, 10, 11};   //deklarasi variabel global AnodePin untuk kaki2 Anoda LED RGB berbentuk Array dengan jumlah indeks 6 bertipe data integer (bilangan bulat)
                                          //angka2 3, 5, 6, 9, 10 dan 11 itu sesuai dengan yang mempunyai kemampuan untuk output sinyal PWM                                          
int CathodePin[5] = {A0, A1, A2, A3, A4}; //deklarasi variabel global CathodePin untuk kaki2 Katoda LED RGB berbentuk Array dengan jumlah indeks 5 bertipe data integer (bilangan bulat)

void setup() {
  for(int num=0; num<=5; num++){          //deklarasi variabel num bertipe data integer didalam perulangan for, perulangan sebanyak 6 kali (0-5)
    pinMode(AnodePin[num],OUTPUT);        //menjadikan pin2 untuk anoda (3, 5, 6, 9, 10 dan 11) sebagai output sesuai dengan isi nilaivariabel num
    pinMode(CathodePin[num],OUTPUT);      //menjadikan pin2 untuk anoda (3, 5, 6, 9, 10 dan 11) sebagai output sesuai dengan isi nilai variabel num, indeks ke 5 akan dihiraukan
  }                                       //karena deklarasi hanya 0-4
}

void loop() {
  int i;
  for(i=0;i<=5000;i++){
    AllLEDOn();
  }
  for(i=0;i<=15;i++){
    LEDChaser2();
  }
  for(i=0;i<=15;i++){
    LEDChaser3();
  }
  for(i=0;i<=2;i++){
    LEDChaser1();
  }
  for(i=0;i<=2;i++){
    LEDTest();
  }
}

void AllOff(){                            //fungsi untuk mengnonaktifkan LED RGB
  for(int num=0; num<=5; num++){          //deklarasi variabel lokal num bertipe data integer didalam perulangan for, perulangan sebanyak 6 kali (0-5)
    digitalWrite(AnodePin[num], LOW);     //kaki2 anoda akan diberikan logika LOW   (0 V) sesuai dengan isi variabel num yang berisi nilai 0-5
    digitalWrite(CathodePin[num], HIGH);  //kaki2 katoda akan diberikan logika HIGH (5 V)  sesuai dengan isi variabel num yang berisi nilai 0-5, indeks ke-5 akan dihiraukan
  }                                       //karena jumlah indeks pada array CathodePin hanya 0-4
}

void AnoOff(){                            //fungsi untuk mengnonaktifkan kaki Anoda LED RGB
  for(int num=0; num<=5; num++){          //deklarasi variabel lokal num bertipe data integer didalam perulangan for, perulangan sebanyak 6 kali (0-5)
    digitalWrite(AnodePin[num], LOW);     //kaki2 anoda akan diberikan logika LOW sesuai dengan isi variabel num yang berisi nilai 0-5
  }
}

void CatOff(){                           //fungsi untuk mengnonaktifkan kaki Katoda LED RGB
  for(int num=0; num<=4; num++){         //deklarasi variabel lokal num bertipe data integer didalam perulangan for, perulangan sebanyak 5 kali (0-4)
    digitalWrite(CathodePin[num], HIGH); //kaki2 katoda akan diberikan logika HIGH sesuai dengan isi variabel num yang berisi nilai 0-4
  }
}

void AnoOn(){                            //fungsi untuk mengaktifkan kaki Anoda LED RGB
  for(int num=0; num<=5; num++){         //deklarasi variabel lokal num bertipe data integer didalam perulangan for, perulangan sebanyak 6 kali (0-5)
    digitalWrite(AnodePin[num], HIGH);   //kaki2 anoda akan diberikan logika HIGH sesuai dengan isi variabel num yang berisi nilai 0-5
  }
}

void AllLEDOn(){
  int num1, num2;
  float speeds=0.1;
  CatOff();
  for(num1=0; num1<=4; num1++){
    digitalWrite(CathodePin[num1], LOW);
    for(num2=0; num2<=5; num2++){
      digitalWrite(AnodePin[num2], HIGH);
      delay(speeds);
      AnoOff();
    }
    CatOff();
  }
}

void LEDTest(){
  int num1, num2;
  CatOff();
  for(int speeds=10; speeds<=100; speeds=speeds+10){
    for(num1=0; num1<=4; num1++){
      digitalWrite(CathodePin[num1], LOW);
      for(num2=0; num2<=5; num2++){
        digitalWrite(AnodePin[num2], HIGH);
        delay(speeds);
        AnoOff();
      }
      CatOff();
    }
  }
}

void LEDChaser1(){
  int num1, num2;
  CatOff();
  for(int speeds=10;speeds<=100;speeds=speeds+10){
    for(num1=0; num1<=4; num1++){
      digitalWrite(CathodePin[num1], LOW);
      for(num2=0; num2<=2; num2++){
        digitalWrite(AnodePin[num2], HIGH);
        delay(speeds);
        AnoOff();
      }
      CatOff();
    }
    for(num1=4; num1>=0; num1--){
      digitalWrite(CathodePin[num1], LOW);
      for(num2=3; num2<=5; num2++){
        digitalWrite(AnodePin[num2], HIGH);
        delay(speeds);
        AnoOff();
      }
      CatOff();
    }
  }
}

void LEDChaser2(){
  int num1, num2;
  CatOff();
  int speeds=30;
    for(num1=0; num1<=2; num1++){
      int num3=num1+3;
      digitalWrite(AnodePin[num1], HIGH);
      digitalWrite(AnodePin[num3], HIGH);
      for(num2=0; num2<=4; num2++){
        digitalWrite(CathodePin[num2], LOW);
        delay(speeds);
        CatOff();
      }
      for(num2=3; num2>=0; num2--){
        digitalWrite(CathodePin[num2], LOW);
        delay(speeds);
        CatOff();
      }
      AnoOff();
    }

}

void LEDChaser3(){
  int num1, num2;
  CatOff();
  int speeds=50;
  for(num1=0; num1<=2; num1++){
    int num3=num1+3;
    digitalWrite(AnodePin[num1], HIGH);
    for(num2=0; num2<=4; num2++){
      digitalWrite(CathodePin[num2], LOW);
      delay(speeds);
      CatOff();
    }
    AnoOff();
    digitalWrite(AnodePin[num3], HIGH);
    for(num2=4; num2>=0; num2--){
      digitalWrite(CathodePin[num2], LOW);
      delay(speeds);
      CatOff();
    }
    AnoOff();     
  }
}
