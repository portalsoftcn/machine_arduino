
int Trig = 11;
int Echo = 10;

float cm;
float temp;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("setup");
  pinMode(Trig,OUTPUT);
  pinMode(Echo,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(Trig, LOW); //给Trig发送一个低电平
  delayMicroseconds(2);    //等待 2微妙
  digitalWrite(Trig,HIGH); //给Trig发送一个高电平
  delayMicroseconds(10);    //等待 10微妙
  digitalWrite(Trig, LOW); //给Trig发送一个低电平
  
  temp = float(pulseIn(Echo, HIGH)); //存储回波等待时间,
  cm = (temp * 17 )/1000; //把回波时间换算成cm

  Serial.print("Echo =");
  Serial.print(temp);//串口输出等待时间的原始数据
  Serial.print(" | | Distance = ");
  Serial.print(int(cm));//串口输出距离换算成cm的结果
  Serial.println("cm");

  delay(100);

}
