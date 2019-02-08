#include <Wire.h>
#define SLAVE_ADDRESS 0x04
int data;
//int state = 0;
int relay1 = 2;
int relay2 = 3;
int relay3 = 4;
int relay4 = 5;
int relay5 = 6;
int relay6 = 7;
int relay7 = 8;
int relay8 = 9;

int Distance1_Trig = 10;
int Distance1_Echo = 11;
int Distance2_Trig = 12;
int Distance2_Echo = 13;

int distance1;
float distance1_temp;

int distance2;
float distance2_temp;

int delayTime = 3000;

void setup() {
Serial.begin(9600); // start serial for output
// initialize i2c as slave
Wire.begin(SLAVE_ADDRESS);
// define callbacks for i2c communication
Wire.onReceive(receiveData);//从机 接收 主机 发来的数据
Wire.onRequest(sendData); //从机 请求 主机 发送数据
Serial.println("Ready");
pinMode(relay1,OUTPUT);
pinMode(relay2,OUTPUT);
pinMode(relay3,OUTPUT);
pinMode(relay4,OUTPUT);
pinMode(relay5,OUTPUT);
pinMode(relay6,OUTPUT);
pinMode(relay7,OUTPUT);
pinMode(relay8,OUTPUT);
pinMode(Distance1_Trig,OUTPUT);
pinMode(Distance1_Echo,INPUT);
}
void loop() {
  
  getDistance(Distance1_Trig);
  distance1_temp = float(pulseIn(Distance1_Echo, HIGH)); //存储回波等待时间,
  distance1 = (distance1_temp * 17 )/1000; //把回波时间换算成cm
  //Serial.println("distance1: " + String(distance1));
  delay(50);
  
  getDistance(Distance2_Trig);
  distance2_temp = float(pulseIn(Distance2_Echo, HIGH)); //存储回波等待时间,
  distance2 = (distance2_temp * 17 )/1000; //把回波时间换算成cm
  //Serial.println("distance2: " + String(distance2));
  delay(50);
  
 }
// callback for received data
void receiveData(int byteCount){
while(Wire.available()) {
data = Wire.read();
switch(data)
{
  case 0://磨轮停
    //digitalWrite(relay3,LOW);
    for(int a=2;a<=9;a++)
    {
      digitalWrite(a,LOW);
    }
    break;
  case 21:
    digitalWrite(relay2,LOW);
    digitalWrite(relay1,HIGH);
    delay(delayTime);
    digitalWrite(relay1,LOW);
    break;
  case 22:
    digitalWrite(relay2,HIGH);
    //delay(delayTime);
    //digitalWrite(relay2,LOW);
    break;
   case 31://横梁左
    digitalWrite(relay4,LOW);
    digitalWrite(relay3,HIGH);
    break;
   case 32://横梁右
    digitalWrite(relay3,LOW);
    digitalWrite(relay4,HIGH);
    break;
   case 33://横梁移动停
    digitalWrite(relay3,LOW);
    digitalWrite(relay4,LOW);
    break;
   case 41://平台前进
    digitalWrite(relay7,HIGH);
    delay(delayTime);
    digitalWrite(relay7,LOW);
    delay(500);
    digitalWrite(relay5,HIGH);
    delay(delayTime);
    digitalWrite(relay5,LOW);
    break; 
   case 42://平台后退
    digitalWrite(relay7,HIGH);
    delay(delayTime);
    digitalWrite(relay7,LOW);
    delay(500);
    digitalWrite(relay6,HIGH);
    delay(delayTime);
    digitalWrite(relay6,LOW);
    break;
   case 43://平台暂停
    digitalWrite(relay7,HIGH);
    break;
   case 11://磨轮停
    //digitalWrite(relay3,LOW);
    digitalWrite(relay8,HIGH);
    delay(delayTime);
    digitalWrite(relay8,LOW);
    break;
}

}
}

void getDistance(int trig)
{
  digitalWrite(trig, LOW); //给Trig发送一个低电平
  delayMicroseconds(2);    //等待 2微妙
  digitalWrite(trig,HIGH); //给Trig发送一个高电平
  delayMicroseconds(10);    //等待 10微妙
  digitalWrite(trig, LOW); //给Trig发送一个低电平
}

// callback for sending data
void sendDistanceData(int id,int distance)
{
  byte distanceData[3] = {};
  distanceData[0] = id;
  distanceData[1] = distance / 256;
  distanceData[2] = distance % 256;
  Wire.write(distanceData,3);
}

void sendData(){
  sendDistanceData(1,distance1);
  sendDistanceData(2,distance2);
}
