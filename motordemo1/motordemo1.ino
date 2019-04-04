
const unsigned char pins[]  = { 2,3,4,5 };
const unsigned char pinNum  = sizeof(pins) / sizeof(pins[0]);
const unsigned char delayMs = 10;   // 每步动作间隔，控制速度
const char dir = 1;                 // 正负一用来控制转动方向
 
void setup()
{
    for (unsigned char i = 0; i < pinNum; ++i)
    {
        pinMode(pins[i], OUTPUT);
        digitalWrite(pins[i], LOW);
    }
}
 
// 每次进入函数时轮换引脚，在轮换到的引脚上发出高电平后经 uln2003 反相成低电平给电机上电
void loop()
{
    static unsigned char pulsePin = 0;
 
    digitalWrite(pins[pulsePin], HIGH);
    delay(delayMs);
 
    digitalWrite(pins[pulsePin], LOW);
    pulsePin = (pulsePin + dir + pinNum) % pinNum;
}
