30j#include <Stepper.h>
#include <Wire.h>

#define STEPS_PER_ROTOR_REV 32 //Motor inner step amount of one circle
#define GEAR_REDUCTION 64 //speed


#define SLAVE_ADDRESS 0x04

Stepper stepperBR(STEPS_PER_ROTOR_REV,2,4,3,5);
Stepper stepperBL(STEPS_PER_ROTOR_REV,6,8,7,9);
Stepper stepperFR(STEPS_PER_ROTOR_REV,10,12,11,13);
Stepper stepperFL(STEPS_PER_ROTOR_REV,A0,A2,A1,A3);

int data = -1;
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
      case 0://up all
        stepperFL.step(1);
        stepperFR.step(1);
        stepperBL.step(1);
        stepperBR.step(1);
        break;
      case 1://down all
        stepperFL.step(-1);
        stepperFR.step(-1);
        stepperBL.step(-1);
        stepperBR.step(-1);
        break;  
      case 2://stop all
        stepperFL.step(0);
        stepperFR.step(0);
        stepperBL.step(0);
        stepperBR.step(0);
        break;
      case 10://FL,Up
        stepperFL.step(1);
       break;
      case 11://FL,Down
        stepperFL.step(-1);
       break;
      case 20://FR,Up
        stepperFR.step(1);
       break;
      case 21://FR,Down
        stepperFR.step(-1);
       break; 
      case 30://BL,Up
        stepperBL.step(1);
       break;
      case 31://BL,Down
        stepperBL.step(-1);
       break; 
      case 40://BR,Up
        stepperBR.step(1);
       break;
      case 41://BR,Down
        stepperBR.step(-1);
       break;
      case 12: //FL+FR
        stepperFL.step(1);
        stepperFR.step(1);
       break; 
      case 13: //FL+BL
        stepperFL.step(1);
        stepperBL.step(1);
       break; 
      case 24: //FR+BR
        stepperFR.step(1);
        stepperBR.step(1);
       break; 
      case 34: //BL+BR
        stepperBL.step(1);
        stepperBR.step(1);
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





