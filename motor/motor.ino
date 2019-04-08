#include <Stepper.h>
#include <Wire.h>

#define STEPS_PER_ROTOR_REV 32 //Motor inner step amount of one circle
#define GEAR_REDUCTION 64 //speed


#define SLAVE_ADDRESS 0x04

Stepper stepperBR(STEPS_PER_ROTOR_REV,2,4,3,5);
Stepper stepperBL(STEPS_PER_ROTOR_REV,6,7,8,9);
Stepper stepperFR(STEPS_PER_ROTOR_REV,10,12,11,13);
Stepper stepperFL(STEPS_PER_ROTOR_REV,A0,A2,A1,A3);

int data;
const float STEP_PER_OUR_REV = STEPS_PER_ROTOR_REV * GEAR_REDUCTION;

void setup()
{
    Serial.begin(9600);
    // initialize i2c as slave
    Wire.begin(SLAVE_ADDRESS);
    // define callbacks for i2c communication
    Wire.onReceive(receiveData);//从机 接收 主机 发来的数据
    stepperFL.setSpeed(STEPS_PER_ROTOR_REV * 5);
    stepperFR.setSpeed(STEPS_PER_ROTOR_REV * 5);
    stepperBL.setSpeed(STEPS_PER_ROTOR_REV * 5);
    stepperBR.setSpeed(STEPS_PER_ROTOR_REV * 5);
    Serial.println("Ready");
}

void loop()
{  
    switch(data)
    {
      case 1://FL,Up
        stepperFL.step(0);
       break;
      case 10://FL,Up
        stepperFL.step(1);
       break;
      case 11://FL,Down
        stepperFL.step(-1);
       break;
      case 2://FL,Up
        stepperFR.step(0);
       break;
      case 20://FL,Up
        stepperFR.step(1);
       break;
      case 21://FL,Down
        stepperFR.step(-1);
       break; 
      case 3://FL,Up
        stepperBL.step(0);
       break;
      case 30://FL,Up
        stepperBL.step(1);
       break;
      case 31://FL,Down
        stepperBL.step(-1);
       break; 
      case 4://FL,Up
        stepperBR.step(0);
       break;
      case 40://FL,Up
        stepperBR.step(1);
       break;
      case 41://FL,Down
        stepperBR.step(-1);
       break; 
       
    }
}

void receiveData(int byteCount){
  while(Wire.available()) 
  {
    data = Wire.read();
    Serial.println(data);
  }
}





