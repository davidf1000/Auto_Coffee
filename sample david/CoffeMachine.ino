/* Example sketch to control a stepper motor with TB6600 stepper motor driver, AccelStepper library and Arduino: acceleration and deceleration. More info: https://www.makerguides.com */
// Include the AccelStepper library:
#include <AccelStepper.h>
#include <SoftwareSerial.h>
#include <OneWire.h> 
#include <DallasTemperature.h>
SoftwareSerial EEBlue(11, 10); // RX | TX
// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define ONE_WIRE_BUS A5 
#define relay1 A4
#define relay2 A2
#define relay3 A3
#define stepBase 12
#define dirBase 13
#define stepX 2
#define dirX 5
#define stepY 3
#define dirY 6
#define stepZ 4
#define dirZ 7
#define stepA 8
#define dirA 9
int p =1;
int loc=0;
int stepLoc=0;
#define motorInterfaceType 1
// Create a new instance of the AccelStepper class:
AccelStepper stepperBase = AccelStepper(motorInterfaceType, stepBase, dirBase);
AccelStepper stepperX = AccelStepper(motorInterfaceType, stepX, dirX);
AccelStepper stepperY = AccelStepper(motorInterfaceType, stepY, dirY);
AccelStepper stepperZ = AccelStepper(motorInterfaceType, stepZ, dirZ);
AccelStepper stepperA = AccelStepper(motorInterfaceType, stepA, dirA);
OneWire oneWire(ONE_WIRE_BUS); 
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
void setup() {
  // Set the maximum speed and acceleration:
  stepperBase.setMaxSpeed(8);
  stepperBase.setAcceleration(50);
   stepperX.setMaxSpeed(100);
  stepperX.setAcceleration(100);
    stepperY.setMaxSpeed(8);
  stepperY.setAcceleration(8);
    stepperZ.setMaxSpeed(8);
  stepperZ.setAcceleration(8);
    stepperA.setMaxSpeed(8);
  stepperA.setAcceleration(8);
  sensors.begin(); 
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  digitalWrite(relay1,LOW);
digitalWrite(relay2,LOW);
digitalWrite(relay3,LOW);
   Serial.begin(9600);
  EEBlue.begin(9600);
}
void moveBase60() {
    if(p%3==0)
  {
    loc=loc+33;
  }
  else
  {
    loc=loc+33;
  }
  p++;
  stepperBase.moveTo(loc);
  Serial.println(loc);
  stepperBase.runToPosition();
}

void moveStepperTest() {
  stepLoc=0;
  stepperX.moveTo(stepLoc);
  Serial.println(stepLoc);
  stepperX.runToPosition();
  delay(5000);
  stepLoc=-15;
    stepperX.moveTo(stepLoc);
  Serial.println(stepLoc);
  stepperX.runToPosition();
  delay(50);
}

void readTemp(){
   Serial.print(" Requesting temperatures..."); 
 sensors.requestTemperatures(); // Send the command to get temperature readings 
 Serial.println("DONE"); 
/********************************************************************/
 Serial.print("Temperature is: "); 
 Serial.print(sensors.getTempCByIndex(0)); // Why "byIndex"?  
   // You can have more than one DS18B20 on the same bus.  
   // 0 refers to the first IC on the wire 
   delay(1000); 
}
void loop() {
//  moveBase60();
moveStepperTest();
//  delay(1500);
//readTemp();
//delay(1000);
//digitalWrite(relay1,HIGH);
//digitalWrite(relay2,HIGH);
//digitalWrite(relay3,HIGH);
//delay(1000);
//String x;
//if (EEBlue.available())
//{
// x=EEBlue.readString(); 
//Serial.println(x);
//}

}
