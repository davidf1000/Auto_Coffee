/* Example sketch to control a stepper motor with TB6600 stepper motor driver, AccelStepper library and Arduino: acceleration and deceleration. More info: https://www.makerguides.com */

// Library Stepper
#include <AccelStepper.h>
// Library serial untuk Bluetooth
#include <SoftwareSerial.h>
// Library Servo 
#include <Servo.h>


// MACRO (variabel konstan)
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
// Variabel yang terpakai pada program 
int pos = 0;    // variable to store the servo position
int p =1; 
int loc=0;
int posX=0;   // Tracking posisi stepper x 
int posY=0;   // Tracking posisi stepper y
int posZ=0;   // Tracking posisi stepper z 
bool r1=1;    // Kondisi relay pompa
bool r2=1;    // Kondisi relay mixer
bool r3=1;    // relay backup 
const int buttonPin = 10;     // pin switch piringan 
int buttonState = 0;         // kondisi switch piringan 
// OBJECT
Servo myservo;  // create servo object to control a servo
SoftwareSerial EEBlue(11, A2); // RX | TX untuk bluetooth 

// Deklarasi pin-pin yang dipakai pada driver setiap stepper 
AccelStepper stepperBase = AccelStepper(motorInterfaceType, stepBase, dirBase); // stepper piringan  
AccelStepper stepperX = AccelStepper(motorInterfaceType, stepX, dirX); // stepper kopi 
AccelStepper stepperY = AccelStepper(motorInterfaceType, stepY, dirY); // stepper gula 
AccelStepper stepperZ = AccelStepper(motorInterfaceType, stepZ, dirZ); // stepper krimer 

void setup() {
  // Serial print -> untuk print nilai ke layar (hanya untuk debugging)
  Serial.println("Welcome To Coffee Machine 2.0");
  //BEGIN SERIAL communication and Bluetooth HC-05
  Serial.begin(9600);
  EEBlue.begin(9600);
  // Define pin-pin untuk switch dan relay 
  pinMode(buttonPin, INPUT);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  // Set kondisi relay ke OFF semua (Relay active low, artinya relay hanya menyala ketika sinyal bernilai LOW / 0 )
  digitalWrite(relay1,HIGH);
  digitalWrite(relay2,HIGH);
  digitalWrite(relay3,HIGH);
  // STEPPER
  // Set RPM max servo (setmaxspeed) dan percepatan sudut servo (acceleration)
  stepperBase.setMaxSpeed(8);
  stepperBase.setAcceleration(50);
  stepperX.setMaxSpeed(100);
  stepperX.setAcceleration(100);
  stepperY.setMaxSpeed(100);
  stepperY.setAcceleration(100);
  stepperZ.setMaxSpeed(100);
  stepperZ.setAcceleration(100);
  // Deklarasi servo 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  startServo();
}

// BASE STEPPER PIRINGAN
// MUTER SAMPE SWITCH KETEKEN 
void moveBaseSwitch()
{
  Serial.println("BASE");
 buttonState = digitalRead(buttonPin);
 // While loop, stepper piringan gerak sampai switch terbaca HIGH (tertekan)
while(!buttonState)
{
  buttonState = digitalRead(buttonPin);
  // loc = lokasi stepper, di increment agar stepper bergerak 
  loc++;
  stepperBase.moveTo(loc);
  stepperBase.runToPosition();
}
// jika switch tertekan, keluar dari loop
Serial.println("STOP");
delay(2000); 
}


// STEPPER DISPENSER BUBUK X (KOPI)
void moveStepperXTest(int val) {
  // Stepper pertama ada di posisi posX 
  stepperX.moveTo(posX);
  stepperX.runToPosition();
  delay(300);
  // Lalu turun sebanyak val 
  posX=posX-val;
  stepperX.moveTo(posX);
  Serial.println(posX);
  stepperX.runToPosition();
  delay(300);
  // lalu naik lagi sebanyak val (kembali ke posisi awal)
    posX=posX+val;
  stepperX.moveTo(posX);
  Serial.println(posX);
  stepperX.runToPosition();
}


// STEPPER DISPENSER BUBUK Y (GULA)
void moveStepperYTest(int val) {
  // Stepper pertama ada di posisi posY
  stepperY.moveTo(posY);
  stepperY.runToPosition();
  delay(400);
  // Lalu turun sebanyak val 
  posY=posY-val;
  stepperY.moveTo(posY);
  Serial.println(posY);
  stepperY.runToPosition();
  delay(400);
  // lalu naik lagi sebanyak val (kembali ke posisi awal)
    posY=posY+val;
  stepperY.moveTo(posY);
  Serial.println(posY);
  stepperY.runToPosition();
}
// STEPPER DISPENSER BUBUK Z (KRIMER)
void moveStepperZTest(int val) {
  // Stepper pertama ada di posisi posZ 
  stepperZ.moveTo(posZ);
  stepperZ.runToPosition();
  delay(300);
  // Lalu turun sebanyak val 
  posZ=posZ-val;
  stepperZ.moveTo(posZ);
  Serial.println(posZ);
  stepperZ.runToPosition();
  delay(300);
  // lalu naik lagi sebanyak val (kembali ke posisi awal)
    posZ=posZ+val;
  stepperZ.moveTo(posZ);
  Serial.println(posZ);
  stepperZ.runToPosition();
}
// ADJUST OFFSET POSISI STEPPER X (KOPI)
void adjustX(int dir)
{
  // Fungsi untuk menaikan/menurunkan posisi stepper X sebanyak dir kali 
  posX=posX+dir*1;
  stepperX.moveTo(posX);
  Serial.println(posX);
  stepperX.runToPosition();
  delay(300);
}
// ADJUST OFFSET POSISI AWAL STEPPER Y (GULA) 
void adjustY(int dir)
{
  // Fungsi untuk menaikan/menurunkan posisi stepper Y sebanyak dir kali 
  posY=posY+dir*1;
  stepperY.moveTo(posY);
  Serial.println(posY);
  stepperY.runToPosition();
  delay(300);
}

// ADJUST OFFSET POSISI STEPPER Z (KRIMER)
void adjustZ(int dir)
{
  // Fungsi untuk menaikan/menurunkan posisi stepper Z sebanyak dir kali 
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


// Fungsi dengan abstraksi yang lebih tinggi ( menggunakan fungsi penggerakan stepper yang telah dideklarasikan sebelumnya)
// Tujuannya adalah agar kode lebih enak dibaca 

// Mengaktifkan dispenser bubuk kopi
void addCoffee(int t,int deg)
{
  // variabel t -> stepper mau naik-turun sebanyak t kali 
  // variabel deg -> mau naik turun sebanyak berapa derajat (deg/200 * 360 derajat)
  Serial.println("KOPI");
  for(int i=0;i<t;i++)
  {
       moveStepperXTest(deg);
  }
}
// Mengaktifkan dispenser bubuk gula
void addSugar(int t,int deg)
{
    // variabel t -> stepper mau naik-turun sebanyak t kali 
  // variabel deg -> mau naik turun sebanyak berapa derajat (deg/200 * 360 derajat)
  Serial.println("GULA");
    for(int i=0;i<t;i++)
  {
       moveStepperYTest(deg);
  }
}
// Mengaktifkan dispenser bubuk krimer
void addCreamer(int t,int deg)
{
    // variabel t -> stepper mau naik-turun sebanyak t kali 
  // variabel deg -> mau naik turun sebanyak berapa derajat (deg/200 * 360 derajat)
  Serial.println("KRIM");
    for(int i=0;i<t;i++)
  {
       moveStepperZTest(deg);
  }
}

// Fungsi untuk mengaktifkan pompa air, mengaktifkan relay lalu menunggu (del) detik lalu mematikannya kembali
void addWater(int del)
{
  Serial.println("AIR");
    digitalWrite(relay1,!r1);
   r1=!r1;
   delay(del);
   Serial.println("Relay pompa toggle OFF");
   digitalWrite(relay1,!r1);
   r1=!r1;
   // dikasi delay supaya biarin selangnya netes dulu 
   delay(1500);
}

// Fungsi untuk mengaktifkan Mixer, pertama akan menggerakan servo , 
// lalu memutar relay DC motor sebanyak del detik, lalu berhenti dan menaikan servo kembali 
void moveMixer(int del)
{
  Serial.println("MIXER");
       for (pos = 65; pos >= 0; pos -= 1) { // goes from 65 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }
   digitalWrite(relay2,!r2);
   r2=!r2;
   delay(del);
   digitalWrite(relay2,!r2);
   r2=!r2;
  for (pos = 0; pos <= 65; pos += 1) { // goes from 0 degrees to 65 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }
}
// Fungsi dengan abstraksi tertinggi (menggunakan fungsi-fungsi sebelumnya)
// Mengotomatisasi komponen apa yang ingin diaktifkan dalam 1 siklus 
void combinationMove(bool x,bool y, bool z,bool a,bool b)
{
  moveBaseSwitch();
  if(x) addCoffee(5,7);
  if(y) addSugar(2,3);
  if(z) addCreamer(2,4);
  if(a) addWater(10000);
  if(b) moveMixer(7000);
}
// FUNGSI UTAMA , membaca input integer dari user, lalu menentukan tindakan apa yang akan dilakukan selanjutnya 
void readBluetooth()
{
 String x;
if (EEBlue.available())
{
 x=EEBlue.readString(); 
}
if(x!=""){
  // Switch case 
  switch (x.toInt()){
    // Case 1 - 10 => Case untuk mengetes setiap aktuator secara manual 
    // misalkan nyalakan relay, gerakan stepper, gerakan servo, dll 
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
   // Case 11 - 90 adalah case untuk Melakukan fine tuning terhadap posisi stepper, agar 
   // tidak perlu melakukan adjusting manual ke posisi setiap stepper nya 
   // Misalkan case 11 -> naikan stepper X (bubuk kopi) naik sebanyak (1/200 * 360) derajat
   // case 23 => turunkan stepper X (bubuk kopi) turun sebanyak (3/200)*360 derajat 
   // case 3x dan 4x untuk stepper Y (Gula)
   // case 5x dan 6x untuk stepper Z (krimer )
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

   // Case 90-99 untuk mengetes komponen lengkap dari mesin 
   // Contoh  case 96 -> Jalankan fungsionalitas mixer secara lengkap 
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


   
   // CASE 101
   // ketika 6 gelas kosong, jalankan fungsi ini untuk menggerakan mesin sampai gelas pertama penuh. 
   // Setelah gelas pertama penuh, ambil gelas pertama lalu taro gelas kosong. Lalu jalankan case 101 
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

   //CASE 102 
   // Jalankan setelah case 101 dijalankan 
    case 102: // TAHAP 2
   Serial.println("Autopilot Mode 6 glass !");
   combinationMove(1,1,1,1,1);
   Serial.println("DONE");
   break;


   // CASE 103 
   // Untuk hanya mengisi 1 gelas saja (gelas lain tidak diisi)

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

// LOOP UTAMA, hanya akan terus-menerus membaca input bluetooth user lalu menentukan eksekusi program selanjutnya
void loop() {
readBluetooth();
}


// DEPRECATED (Gak terpakai lagi )
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

// DEPRECATED (gak terpakai)
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