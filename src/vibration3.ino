#include <SoftwareSerial.h>
 
#define BT_RXD 8
#define BT_TXD 9
SoftwareSerial bluetooth(BT_TXD, BT_RXD);


int trigPin = 6;
int echoPin = 7;

int vib1 = 11;

int data = -1;

long duration1, duration, distance1; //진동센서 연결 설정.

int ranges[3]={0,0,0}; // range 설정.
 
void setup(){
  Serial.begin(9600);       // 시리얼 속도 설정      
  
  bluetooth.begin(9600);

  pinMode(echoPin, INPUT);   // echoPin 입력    
  pinMode(trigPin, OUTPUT);  // trigPin 출력   
  pinMode(vib1, OUTPUT);
}
 
void loop(){
  if (bluetooth.available()) {
      data = bluetooth.parseInt();
      Serial.print(data);
  }
  while (data!=1){
    /*if (Serial.available()) {
      bluetooth.write(Serial.read());
    }*/
    data=bluetooth.parseInt();
    if(data==1){
      analogWrite(vib1, 0);
      break;
    }
    digitalWrite(trigPin, HIGH);  // trigPin에서 초음파 발생(echoPin도 HIGH)        
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration1 = pulseIn(echoPin, HIGH);    // echoPin 이 HIGH를 유지한 시간을 저장 한다.
    distance1 = ((float)(340 * duration1) / 10000) / 2; 
 
    Serial.print("\nDIstance:"); // 물체와 초음파 센서간 거리를 표시        
    Serial.print(distance1);
    Serial.print("cm\n");
    bluetooth.write(distance1);
    
    switch(data){
      case 150:
        Serial.print(150);
        ranges[0]=150;
        ranges[1]=100;
        ranges[2]=50;
        break;
      case 100:
        Serial.print(100);
        ranges[0]=100;
        ranges[1]=50;
        ranges[2]=25;
        break;
      case 50:
        Serial.print(50);
        ranges[0]=50;
        ranges[1]=25;
        ranges[2]=10;
        break;
      default:
        break;
    }
    if(distance1 < ranges[0] && distance1 >= ranges[1]) {
        Serial.print("\nOK1:");
        analogWrite(vib1, 100);
        delay(1000);
        analogWrite(vib1, 0);
        delay(3000);
     }
     else if(distance1 < ranges[1] && distance1 > 0){
        Serial.print("\nOK2:");
        analogWrite(vib1, 250);
        delay(1000);
        analogWrite(vib1, 0);
        delay(1500);
     }
     else{
        analogWrite(vib1, 0);
     }
  }
  if(data==1){
    analogWrite(vib1, 0);
  }
  delay(300);
}
