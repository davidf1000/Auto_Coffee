/* Example sketch to control a stepper motor with TB6600 stepper motor driver, AccelStepper library and Arduino: acceleration and deceleration. More info: https://www.makerguides.com */

// Library Stepper
#include <AccelStepper.h>
#include <SoftwareSerial.h>
#include <Servo.h>


// MACRO
#define relay1 A2
#define relay2 A3
#define relay3 A4
#define stepBase 12
#define dirBase 13
#define stepX 2
#define dirX 5
#define stepY 3
#define dirY 6
#define stepZ 4
#define dirZ 7
#define motorInterfaceType 1
// VARIABLE
int pos = 0;    // variable to store the servo position
int p =1;
int loc=0;
int posX=0;
int posY=0;
int posZ=0;
bool r1=1;
bool r2=1;
bool r3=1;
const int buttonPin = 10;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status
// OBJECT
Servo myservo;  // create servo object to control a servo
SoftwareSerial EEBlue(11, A2); // RX | TX
AccelStepper stepperBase = AccelStepper(motorInterfaceType, stepBase, dirBase);
AccelStepper stepperX = AccelStepper(motorInterfaceType, stepX, dirX);
AccelStepper stepperY = AccelStepper(motorInterfaceType, stepY, dirY);
AccelStepper stepperZ = AccelStepper(motorInterfaceType, stepZ, dirZ);  

void setup() {
  Serial.println("Welcome To Coffee Machine 2.0");
  //BEGIN SERIAL and Bluetooth
  Serial.begin(9600);
  EEBlue.begin(9600);
  // SWITCH AND RELAY
  pinMode(buttonPin, INPUT);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  // INIT RELAY CONDITION
  digitalWrite(relay1,HIGH);
  digitalWrite(relay2,HIGH);
  digitalWrite(relay3,HIGH);
  // STEPPER
  stepperBase.setMaxSpeed(8);
  stepperBase.setAcceleration(50);
  stepperX.setMaxSpeed(100);
  stepperX.setAcceleration(100);
  stepperY.setMaxSpeed(100);
  stepperY.setAcceleration(100);
  stepperZ.setMaxSpeed(100);
  stepperZ.setAcceleration(100);
  // SERVO
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  startServo();
}

// BASE STEPPER PIRINGAN
// MUTER SAMPE SWITCH KETEKEN
void moveBaseSwitch()
{
  Serial.println("BASE");
 buttonState = digitalRead(buttonPin);
while(!buttonState)
{
  buttonState = digitalRead(buttonPin);
  loc++;
  stepperBase.moveTo(loc);
  stepperBase.runToPosition();
}
Serial.println("STOP");
delay(2000); 
}
// DEPRECATED
// MOVE STEPPER BASE 60 DERAJAT
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

// STEPPER DISPENSER BUBUK X (KOPI)
void moveStepperXTest(int val) {
  stepperX.moveTo(posX);
  stepperX.runToPosition();
  delay(300);
  posX=posX-val;
  stepperX.moveTo(posX);
  Serial.println(posX);
  stepperX.runToPosition();
  delay(300);
    posX=posX+val;
  stepperX.moveTo(posX);
  Serial.println(posX);
  stepperX.runToPosition();
}
// ADJUST OFFSET POSISI STEPPER X (KOPI)
void adjustX(int dir)
{
  posX=posX+dir*1;
  stepperX.moveTo(posX);
  Serial.println(posX);
  stepperX.runToPosition();
  delay(300);
}

// STEPPER DISPENSER BUBUK Y (GULA)
void moveStepperYTest(int val) {
  stepperY.moveTo(posY);
  stepperY.runToPosition();
  delay(400);
  posY=posY-val;
  stepperY.moveTo(posY);
  Serial.println(posY);
  stepperY.runToPosition();
  delay(400);
    posY=posY+val;
  stepperY.moveTo(posY);
  Serial.println(posY);
  stepperY.runToPosition();
}
// ADJUST OFFSET POSISI AWAL STEPPER Y (GULA) 
void adjustY(int dir)
{
  posY=posY+dir*1;
  stepperY.moveTo(posY);
  Serial.println(posY);
  stepperY.runToPosition();
  delay(300);
}
// STEPPER DISPENSER BUBUK Z (KRIMER)
void moveStepperZTest(int val) {
  stepperZ.moveTo(posZ);
  stepperZ.runToPosition();
  delay(300);
  posZ=posZ-val;
  stepperZ.moveTo(posZ);
  Serial.println(posZ);
  stepperZ.runToPosition();
  delay(300);
    posZ=posZ+val;
  stepperZ.moveTo(posZ);
  Serial.println(posZ);
  stepperZ.runToPosition();
}
// ADJUST OFFSET POSISI STEPPER Z (KRIMER)
void adjustZ(int dir)
{
  posZ=posZ+dir*1;
  stepperZ.moveTo(posZ);
  Serial.println(posZ);
  stepperZ.runToPosition();
  delay(300);
}
// INISIALISASI POSISI SERVO AWAL 
void startServo()
{
    for (pos = 0; pos <= 65; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(80);                       // waits 15ms for the servo to reach the position
  }
}
// SERVO PENGGERAK MIXER SEBESAR 65 DERAJAT
void moveServo()
{

    for (pos = 65; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
  delay(1500);
  for (pos = 0; pos <= 65; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
}

// DEPRECATED 
// TESTING PAKE FUNGSI RUNSPEED() TAPI TERNYATA GAK BISA 
void stepperBase60()
{
   buttonState = digitalRead(buttonPin);
while(!buttonState)
{
  Serial.println("DO SOMETHING");
   buttonState = digitalRead(buttonPin);
   stepperBase.runSpeed();
}
Serial.println("STOP");
delay(2000); 
}

void addCoffee(int t,int deg)
{
  Serial.println("KOPI");
  for(int i=0;i<t;i++)
  {
       moveStepperXTest(deg);
  }
}

void addSugar(int t,int deg)
{
  Serial.println("GULA");
    for(int i=0;i<t;i++)
  {
       moveStepperYTest(deg);
  }
}

void addCreamer(int t,int deg)
{
  Serial.println("KRIM");
    for(int i=0;i<t;i++)
  {
       moveStepperZTest(deg);
  }
}
void addWater(int del)
{
  Serial.println("AIR");
     digitalWrite(relay1,!r1);
   r1=!r1;
   delay(del);
   Serial.println("Relay pompa toggle OFF");
   digitalWrite(relay1,!r1);
   r1=!r1;
   delay(1500);
}

void moveMixer(int del)
{
  Serial.println("MIXER");
       for (pos = 65; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }
   digitalWrite(relay2,!r2);
   r2=!r2;
   delay(del);
   digitalWrite(relay2,!r2);
   r2=!r2;
  for (pos = 0; pos <= 65; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }
}
void combinationMove(bool x,bool y, bool z,bool a,bool b)
{
  moveBaseSwitch();
  if(x) addCoffee(5,7);
  if(y) addSugar(2,3);
  if(z) addCreamer(2,4);
  if(a) addWater(10000);
  if(b) moveMixer(7000);
}
// FUNGSI UTAMA , BACA INPUT BLUETOOTH LALU NENTUIN GERAKAN MESIN SELANJUTNYA 
void readBluetooth()
{
 String x;
if (EEBlue.available())
{
 x=EEBlue.readString(); 
}
if(x!=""){
  switch (x.toInt()){
  case 1:
   Serial.println("Relay pompa toggle ON");
   digitalWrite(relay1,!r1);
   r1=!r1;
   delay(12500);
   Serial.println("Relay pompa toggle OFF");
   digitalWrite(relay1,!r1);
   r1=!r1;
   break;
  case 2:
   Serial.println("Relay mixer toggle ON");
   digitalWrite(relay2,!r2);
   r2=!r2;
   delay(5000);
   Serial.println("Relay mixer toggle OFF");
   digitalWrite(relay2,!r2);
   r2=!r2;
   break;
  case 3:
   Serial.println("Testing Stepper Base");
    moveBaseSwitch();
   break;
  case 4:
   Serial.println("Stepper X");
   moveStepperXTest(7);
   moveStepperXTest(7);
   moveStepperXTest(7);
   moveStepperXTest(7);
   moveStepperXTest(7);
   moveStepperXTest(7);
   break;
  case 5:
   Serial.println("Stepper Y");
   moveStepperYTest(2);
   moveStepperYTest(2);
   break;
  case 6:
   Serial.println("Stepper Z");
   moveStepperZTest(3);
   moveStepperZTest(3);    
   break;
  case 7:
    Serial.println("Servo mixer !");
   moveServo();
   break;
  case 11:
   Serial.println("UP X 1 !");
   adjustX(1);
   break;
  case 12:
   Serial.println("UP X 2 !");
   adjustX(2);
   break;
  case 13:
   Serial.println("UP X 3 !");
   adjustX(3);
   break;
  case 15:
   Serial.println("UP X 5 !");
   adjustX(5);
   break;
  case 21:
   Serial.println("DN X 1 !");
   adjustX(-1);
   break;
  case 22:
   Serial.println("DN X 2 !");
   adjustX(-2);
   break;
  case 23:
   Serial.println("DN X 3 !");
   adjustX(-3);
   break;
  case 25:
   Serial.println("DN X 5 !");
   adjustX(-5);
   break;
  case 31:
   Serial.println("UP Y 1 !");
   adjustY(1);
   break;
  case 32:
   Serial.println("UP Y 2 !");
   adjustY(2);
   break;
  case 33:
   Serial.println("UP Y 3 !");
   adjustY(3);
   break;
  case 35:
   Serial.println("UP Y 5 !");
   adjustY(5);
   break;
  case 41:
   Serial.println("DN Y 1 !");
   adjustY(-1);
   break;
  case 42:
   Serial.println("DN Y 2 !");
   adjustY(-2);
   break;
  case 43:
   Serial.println("DN Y 3 !");
   adjustY(-3);
   break;
  case 45:
   Serial.println("DN Y 5 !");
   adjustY(-5);
   break;
  case 51:
   Serial.println("UP Z 1 !");
   adjustZ(1);
   break;
  case 52:
   Serial.println("UP Z 2 !");
   adjustZ(2);
   break;
  case 53:
   Serial.println("UP Z 3 !");
   adjustZ(3);
   break;
  case 55:
   Serial.println("UP Z 5 !");
   adjustZ(5);
   break;
  case 61:  
   Serial.println("DN Z 1 !");
   adjustZ(-1);
   break;
  case 62:  
   Serial.println("DN Z 2 !");
   adjustZ(-2);
   break;
  case 63:  
   Serial.println("DN Z 3 !");
   adjustZ(-3);
   break;
  case 65:  
   Serial.println("DN Z 5 !");
   adjustZ(-5);
   break;
  case 90:
   Serial.println("KOSONGIN AIR");
   Serial.println("Relay pompa toggle ON");
   digitalWrite(relay1,!r1);
   r1=!r1;
   break;
  case 91:
   Serial.println("BASE STEPPER 60 Degree !");
   moveBaseSwitch();
   break;
  case 92:
   Serial.println("Add Coffee !");
   addCoffee(6,7);
   break;
   case 93:
   Serial.println("Add Sugar !");
   addSugar(2,2);
   break;
  case 94:
   Serial.println("Add Creamer !");
   addCreamer(2,3);
   break;
  case 95:
   Serial.println("Add Hot Water !");
   addWater(10000);
   break;
  case 96:
   Serial.println("Mixer!");
   moveMixer(5000);
   break;
  case 99:
   Serial.println("Autopilot Mode 6 glass !");
   // STEP 1 -> 10000
   combinationMove(1,0,0,0,0);
   // STEP 2 -> 11000
   combinationMove(1,1,0,0,0);
   // STEP 3 -> 11100
   combinationMove(1,1,1,0,0);
   // STEP 4 -> 11110
   combinationMove(1,1,1,1,0);
   // STEP 5 -> 11111 gelas 1 diujung
   combinationMove(1,1,1,1,1);
   // STEP 6 -> 01111 gelas 1 bottom , gelas 2 awal 
   combinationMove(0,1,1,1,1);
   // STEP 7 -> 00111
   combinationMove(0,0,1,1,1);
   // STEP 8 -> 00011
   combinationMove(0,0,0,1,1);
   // STEP 9 -> 00001
   combinationMove(0,0,0,0,1);
   // STEP 10-> 00000
   Serial.println("DONE");
   break;
  case 100:
   Serial.println("Relay mixer toggle ON");
   digitalWrite(relay2,!r2);
   r2=!r2;
   break;
     case 101: // INISIALISASI
   Serial.println("Autopilot Mode 6 glass !");s
   // STEP 1 -> 10000
   combinationMove(1,0,0,0,0);
   // STEP 2 -> 11000
   combinationMove(1,1,0,0,0);
   // STEP 3 -> 11100
   combinationMove(1,1,1,0,0);
   // STEP 4 -> 11110
   combinationMove(1,1,1,1,0);
   // STEP 5 -> 11111 gelas 1 diujung
   combinationMove(1,1,1,1,1);
   // STEP 6 -> 01111 gelas 1 bottom , gelas 2 awal 
   combinationMove(0,0,0,0,0);
   Serial.println("DONE");
   break;
        case 102: // TAHAP 2
   Serial.println("Autopilot Mode 6 glass !");
   combinationMove(1,1,1,1,1);
   Serial.println("DONE");
   break;
        case 103: // SINGLE
   Serial.println("Autopilot Mode 6 glass !");
   // STEP 1 -> 10000
   combinationMove(1,0,0,0,0);
   // STEP 2 -> 11000
   combinationMove(0,1,0,0,0);
   // STEP 3 -> 11100
   combinationMove(0,0,1,0,0);
   // STEP 4 -> 11110
   combinationMove(0,0,0,1,0);
   // STEP 5 -> 11111 gelas 1 diujung
   combinationMove(0,0,0,0,1);
   // STEP 6 -> 01111 gelas 1 bottom , gelas 2 awal 
   combinationMove(0,0,0,0,0);
   Serial.println("DONE");
   break;
  default:
   break;
  }
  };
}

// LOOP BACA BLUETOOTH 
void loop() {
readBluetooth();
}
