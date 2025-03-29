#include<Servo.h>
Servo myservo;

#define M_P1 4
#define M_N1 5
#define M_P2 6
#define M_N2 7

#define PM_P A0

#define GM_P 9
#define GM_N 10

#include"dht11.h"
DHT dht;

int T1, H1 = 0;
bool flag = false;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(3);
  myservo.write(90);
  pinMode(M_P1, OUTPUT);
  pinMode(M_N1, OUTPUT);
  pinMode(M_P2, OUTPUT);
  pinMode(M_N2, OUTPUT);
  pinMode(PM_P, OUTPUT);
  pinMode(GM_P, OUTPUT);
  pinMode(GM_N, OUTPUT);
  digitalWrite(M_P1, LOW);
  digitalWrite(M_N1, LOW);
  digitalWrite(M_P2, LOW);
  digitalWrite(M_N2, LOW);
  digitalWrite(PM_P, LOW);
  digitalWrite(GM_P, LOW);
  digitalWrite(GM_N, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  dht.dht_read(2);
  T1 = dht.temperature;
  H1 = dht.RH;
  if (flag == true)
  {
    digitalWrite(M_P1, LOW);
    digitalWrite(M_N1, LOW);
    digitalWrite(M_P2, LOW);
    digitalWrite(M_N2, LOW);
    delay(2000);
    myservo.write(180);
    delay(100);
    myservo.write(90);
    digitalWrite(M_P1, LOW);
    digitalWrite(M_N1, HIGH);
    digitalWrite(M_P2, HIGH);
    digitalWrite(M_N2, LOW);
    delay(2000);
  }
}
void serialEvent()
{
  while (Serial.available() > 0)
  {
    char inchar = Serial.read();
    switch (inchar)
    {
      case 'L' : digitalWrite(M_P1, HIGH);     //forward
        digitalWrite(M_N1, LOW);
        digitalWrite(M_P2, HIGH);
        digitalWrite(M_N2, LOW);
        break;
      case 'R' : digitalWrite(M_P1, LOW);     //reverse
        digitalWrite(M_N1, HIGH);
        digitalWrite(M_P2, LOW);
        digitalWrite(M_N2, HIGH);
        break;
      case 'B' : digitalWrite(M_P1, HIGH);     //right
        digitalWrite(M_N1, LOW);
        digitalWrite(M_P2, LOW);
        digitalWrite(M_N2, HIGH);
        break;
      case 'F' : digitalWrite(M_P1, LOW);     //left
        digitalWrite(M_N1, HIGH);
        digitalWrite(M_P2, HIGH);
        digitalWrite(M_N2, LOW);
        break;
      case 'P' : digitalWrite(PM_P, HIGH);     //water spray on
        break;
      case 'O' : digitalWrite(PM_P, LOW);     //water spray off
        break;
      case 'G' : digitalWrite(GM_P, HIGH);     //grass cut on
        digitalWrite(GM_N, LOW);
        break;
      case 'N' : digitalWrite(GM_P, LOW);     //grass cut off
        digitalWrite(GM_N, LOW);
        break;
      case 'A' : flag = true;                 //seed through on
               digitalWrite(GM_P, LOW);
               digitalWrite(GM_N, LOW);
               digitalWrite(PM_P, LOW);
               delay(1000);
               digitalWrite(M_P1, LOW);
               digitalWrite(M_N1, LOW);
               digitalWrite(M_P2, LOW);
               digitalWrite(M_N2, LOW);
               delay(1000);
               digitalWrite(M_P1, HIGH);
               digitalWrite(M_N1, LOW);
               digitalWrite(M_P2, HIGH);
               digitalWrite(M_N2, LOW);
        break;
      case 'Y' : flag = false;                 //seed through off
        digitalWrite(M_P1, HIGH);
        digitalWrite(M_N1, LOW);
        digitalWrite(M_P2, HIGH);
        digitalWrite(M_N2, LOW);
        break;
      case 'S' :   digitalWrite(M_P1, LOW);   //STOP
        digitalWrite(M_N1, LOW);
        digitalWrite(M_P2, LOW);
        digitalWrite(M_N2, LOW);
        digitalWrite(PM_P, LOW);
        digitalWrite(GM_P, LOW);
        digitalWrite(GM_N, LOW);
        myservo.write(90);
        flag = false;
               break;
    }
  }
}
