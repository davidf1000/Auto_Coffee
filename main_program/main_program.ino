/* Mendefinisikan pin */
#define relay1        //Pin untuk relay pada solenoid valve
#define relay2        //Pin untuk relay pada dinamo
#define ssr           //Pin ssr untuk element heater
#define m_en          //Pin untuk mengaktifkan driver motor
#define m1_step       //Pin direction motor 1 (base)
#define m1_dir        //Pin step motor 1 (base)
#define m2_step       //Pin direction motor 2 (bubuk 1)
#define m2_dir        //Pin step motor 2 (bubuk 1)
#define m3_step       //Pin direction motor 3 (bubuk 2)
#define m3_dir        //Pin step motor 3 (bubuk2)
#define m4_step       //Pin direction motor 4 (bubuk 3)
#define m4_dir        //Pin step motor 4 (bubuk 3)
#define m5_step       //Pin direction motor 5 (mixer)
#define m5_dir        //Pin step motor 5 (mixer)
#define wat_lvl       //Pin untuk input apakah air cukup atau tidak
#define temperature   //Pin input temperatur

#define RELAY_ACTIVE_HIGH
#ifdef RELAY_ACTIVE_HIGH
#define RELAY_ON HIGH
#define RELAY_OFF LOW
#else
#define RELAY_ON LOW
#define RELAY_OFF HIGH
#endif

// Deklarasi Variabel
int temp = 0; //Sebagai penanda banyaknya putaran untuk motor piringan cup. karena piringan cup harus berputar 60 derajat dan stepper motor paling kecil 1.8 derajat.
int mb_step = 20;
int mx_step = 20;
int td = 500;
int clk = 500;
int tf = 1000/clk;
int int_motor1 = 10000    //Interval antar step untuk motor piringan cup (dalam microsecond)
int int_bubuk = 500      //Interval antar step untuk motor penuang bubuk (dalam microsecond)
int int_mixer = 2000     //Interval antar step untuk motor mixer (dalam microsecond)

void setup() {
  // Menentukan pinMode//
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(ssr, OUTPUT);
  pinMode(m_en, OUTPUT);
  pinMode(m1_step, OUTPUT);
  pinMode(m1_dir, OUTPUT);
  pinMode(m2_step, OUTPUT);
  pinMode(m2_dir, OUTPUT);
  pinMode(m3_step, OUTPUT);
  pinMode(m3_dir, OUTPUT);
  pinMode(m4_step, OUTPUT);
  pinMode(m4_dir, OUTPUT);
  pinMode(m5_step, OUTPUT);
  pinMode(m5_dir, OUTPUT);
  pinMode(wat_lvl, INPUT);
  pinMode(temperature, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

}

int compare(int x, int y){
  /* Fungsi compare untuk membandingkan dua nilai integer dan mengembalikan nilai terbesar
   * INPUT  : int x, int y
   * OUTPUT : int
   */
  if (x>y){
    return x;
  }
  else {
    return y;
  }
}

void motor_spin(int m_dir_pin, int dir, int m_step_pin, int step_val, int t){
  /* Fungsi motor_spin adalah fungsi untuk memutar stepper motor dengan arah, besar derajat, dan rpm ditentukan oleh user
   * INPUT  : Pin direction motor, arah putar, pin step motor, banyaknya step yang diinginkan, dan waktu antar step (dalam microsecond)
   */
  digitalWrite(m_dir_pin, dir);
  for(int i=0; i<step_in; i++){
    digitalWrite(m_step_pin, HIGH);
    delayMicroseconds(t);
    digitalWrite(m_step_pin, LOW);
    delayMicroseconds(t);
  }
}

void base_spin(){
  /* Fungsi base_spin adalah fungsi untuk memutar piringan cup.
   * INPUT  : interval antar step
   */
  if(temp==0 || temp == 1){
    motor_spin(m1_dir, HIGH, m1_step, 33, int_motor1); // error bertambah 0,6 derajat
  }
  else{
    motor_spin(m1_dir, HIGH, m1_step, 34, int_motor1); // mengompensasi error
  }
  temp++;
  temp%=3; // dengan ini, nilai temp akan terbatas antara 0,1, atau 2.
}

void phase1(int t){
  /* Fungsi base_phase1 adalah fungsi untuk memutar piringan setelah itu menuang bubuk 1
   * INPUT  : interval motor bubuk 1 untuk membuka dan menutup (dalam milisecond)
   */
   
  motor_spin(m2_dir, HIGH, m2_step, mb_step, int_bubuk);  // Membuka dispenser bubuk 1
  delay(t);
  motor_spin(m2_dir, HIGH, m2_step, mb_step, int_bubuk);  // Menutup dispenser bubuk 1
}

void phase12(int t_b1, int t_b2){ 
  /* Fungsi ini berfungsi untuk memutar piringan cup dan membuka dispenser bubuk 1 dan 2.
   * INPUT  : int t_b1 dan int t_b2
   */
   
  int counter = 0; // sebagai counter clock
  int max_time = compare(t_b1,t_b2);  // batas waktu maksimum

  // Membuka dispenser bubuk 1 dan bubuk 2
  digitalWrite(m2_dir, HIGH);
  digitalWrite(m3_dir, HIGH);
  for(int i=0; i<mb_step; i++){
    digitalWrite(m2_step, HIGH);
    digitalWrite(m3_step, HIGH);
    delayMicroseconds(int_bubuk);
    digitalWrite(m2_step, LOW);
    digitalWrite(m3_step, LOW);
    delayMicroseconds(int_bubuk);
  }

  // Menutup bubuk 1 atau bubuk 2 setelah t_b1 atau t_b2 milisekon
  while(counter<(max_time*tf)){
    if(counter == (t_b1*tf)){
      motor_spin(m2_dir, LOW, m2_step, mb_step, int_bubuk);
    }
    if(counter == (t_b2*tf)){
      motor_spin(m3_dir, LOW, m3_step, mb_step, int_bubuk);
    }
    delayMicroseconds(clk);
    counter++;
  }
}

void phase123(int t_b1, int t_b2, int t_b3){
  /* Fungsi ini berfungsi untuk memutar piringan cup dan membuka dispenser bubuk 1, 2, dan 3.
   * INPUT  : int t_b1 , int t_b2, dan int t_b3
   */
   
  int counter = 0; // sebagai counter clock
  int max_time = compare(compare(t_b1,t_b2), t_b3); // sebagai batas waktu maksimum

  // Membuka dispenser bubuk 1, 2, dan 3
  digitalWrite(m2_dir, HIGH);
  digitalWrite(m3_dir, HIGH);
  digitalWrite(m4_dir, HIGH);
  for(int i=0; i<mb_step; i++){
    digitalWrite(m2_step, HIGH);
    digitalWrite(m3_step, HIGH);
    digitalWrite(m4_step, HIGH);
    delayMicroseconds(int_bubuk);
    digitalWrite(m2_step, LOW);
    digitalWrite(m3_step, LOW);
    digitalWrite(m4_step, LOW);
    delayMicroseconds(int_bubuk);
  }

  // Menutup dispenser bubuk 1, 2, atau 3 setelah t_b1, t_b2, atau t_b3 milisekon
  while(counter<(max_time*tf)){
    if(counter == (t_b1*tf)){
      motor_spin(m2_dir, LOW, m2_step, mb_step, int_bubuk);
    }
    if(counter == (t_b2*tf)){
      motor_spin(m3_dir, LOW, m3_step, mb_step, int_bubuk);
    }
    if(counter == (t_b3*tf)){
      motor_spin(m4_dir, LOW, m4_step, mb_step, int_bubuk);
    }
    delayMicroseconds(clk);
    counter++;
  }
}

void phase1234(int t_b1, int t_b2, int t_b3, int t_a){
  /* Fungsi ini berfungsi untuk memutar piringan cup dan membuka dispenser bubuk 1, 2, dan 3.
   * INPUT  : int t_b1 , int t_b2, int t_b3, int t_a
   */
  int counter = 0; // sebagai batas waktu untuk selesai berputar
  int max_time = compare(compare(t_b1,t_b2), compare(t_b3,t_4));  // batas waktu maksimum

  // dispenser bubuk 1, 2, dan 3 dibuka serta solenoid valve dinyalakan
  digitalWrite(m2_dir, HIGH);
  digitalWrite(m3_dir, HIGH);
  digitalWrite(m4_dir, HIGH);
  digitalWrite(relay1, RELAY_ON);
  for(int i=0; i<20; i++){
    digitalWrite(m2_step, HIGH);
    digitalWrite(m3_step, HIGH);
    digitalWrite(m4_step, HIGH);
    delayMicroseconds(int_bubuk);
    digitalWrite(m2_step, LOW);
    digitalWrite(m3_step, LOW);
    digitalWrite(m4_step, LOW);
    delayMicroseconds(int_bubuk);
  }

  // Menutup dispenser bubuk 1, 2, dan 3 serta mematikan keran setelah waktu yang ditentukan
  while(counter<(max_time*tf)){
    if(counter == (t_b1*tf)){
      motor_spin(m2_dir, LOW, m2_step, mb_step, int_bubuk);
    }
    if(counter == (t_b2*tf)){
      motor_spin(m3_dir, LOW, m3_step, mb_step, int_bubuk);
    }
    if(counter == (t_b3*tf)){
      motor_spin(m4_dir, LOW, m4_step, mb_step, int_bubuk);
    }
    if(counter == (t_a*tf){
      digitalWrite(relay1, RELAY_OFF);
    }
    delayMicroseconds(clk);
    counter++;
  }
}

void phase12345(int t_b1, int t_b2, int t_b3, int t_a){
  /* Fungsi ini berfungsi untuk memutar piringan cup dan membuka dispenser bubuk 1, 2, dan 3.
   * INPUT  : int t_b1 , int t_b2, dan int t_b3
   */
   
  int counter = 0; // sebagai batas waktu untuk selesai berputar
  int max_time = compare(compare(t_b1,t_b2), compare(t_b3,t_4));  // batas waktu maksimum

  // motor mixer diputar, dispenser bubuk 1, 2, dan 3 dibuka serta solenoid valve dinyalakan, dan mixer dinyalakan
  digitalWrite(m2_dir, HIGH);
  digitalWrite(m3_dir, HIGH);
  digitalWrite(m4_dir, HIGH);
  digitalWrite(relay1, RELAY_ON);
  motor_spin(m5_dir, HIGH, m5_step, mx_step, int_mixer);
  for(int i=0; i<mb_step; i++){
    digitalWrite(m2_step, HIGH);
    digitalWrite(m3_step, HIGH);
    digitalWrite(m4_step, HIGH);
    delayMicroseconds(int_bubuk);
    digitalWrite(m2_step, LOW);
    digitalWrite(m3_step, LOW);
    digitalWrite(m4_step, LOW);
    delayMicroseconds(int_bubuk);
  }
  digitalWrite(relay2, RELAY_ON);

  // Menutup dispenser bubuk 1, 2, dan 3 serta mematikan keran setelah waktu yang ditentukan
  while(counter<(max_time*tf)){
    if(counter == (t_b1*tf)){
      motor_spin(m2_dir, LOW, m2_step, mb_step, int_bubuk);
    }
    if(counter == (t_b2*tf)){
      motor_spin(m3_dir, LOW, m3_step, mb_step, int_bubuk);
    }
    if(counter == (t_b3*tf)){
      motor_spin(m4_dir, LOW, m4_step, mb_step, int_bubuk);
    }
    if(counter == (t_a*tf){
      digitalWrite(relay1, RELAY_OFF);
    }
    delayMicroseconds(clk);
    counter++;
  }
  delay(500);
  digitalWrite(relay2, RELAY_OFF);
  motor_spin(m5_dir, LOW, m5_step, mx_step, int_mixer);
}

int inisialisasi(int t_b1, int t_b2, int t_b3, int t_a){
  /* Fungsi ini untuk menjalankan inisialisasi mesin ketika piringan cup masih kosong sampai terisi penuh
   * INPUT  : int t_b1, int t_b2, int t_b3, int t_a
   * OUTPUT : int
   */

   int cup = 1;

   if( cup == 1){
    base_spin();
   }
   else if(cup == 2){
    base_spin();
    phase1(t_b1);
   }
   else if(cup == 3){
    base_spin();
    phase12(t_b1, t_b2);
   }
   else if(cup == 4){
    base_spin();
    phase123(t_b1, t_b2, t_b3);
   }
   else if(cup == 5){
    base_spin();
    while(wat_lvl == LOW){
    delay(1000);
    }
    phase1234(t_b1, t_b2, t_b3, t_a);
   }
   else if(cup == 6){
    base_spin();
    while(wat_lvl == LOW){
    delay(1000);
    }
    phase12345(t_b1, t_b2, t_b3, t_a);
   }
   else if(cup == 7){
    return 1;
   }
   else{
    return 0;
   }

   cup++;
}
