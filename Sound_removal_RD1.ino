// //---------------------------------Sound-----------------------------------------------//

#include "Ticker.h"
#include <U8g2lib.h>
#define dirPin 13
#define stepPin 11
#define stepsPerRevolution 200
#define M0 10
#define M1 9
#define M2 8
#define enablem 12

void stopMotor();  //WORKING WITHOUT BATCH FILE
void startMotor(); //WORKING WITHOUT BATCH FILE 2
void stepperPulse();
void prime_anima();

Ticker motor(stepperPulse, 700, 0, MICROS_MICROS); // 3ms = ~333 steps/sec //500 BEST 450
Ticker prime_anim(prime_anima, 600, 0, MILLIS);
U8G2_SSD1309_128X64_NONAME2_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=13*/ 35, /* data=11*/ 30, /* cs=10*/ 33, /* dc=9*/ 31, /* reset=8*/ 32);  

unsigned long lastUpdate = 0;
const unsigned long animationInterval = 300; 
bool motorRunning = false;
unsigned int stepCount = 0;
const unsigned int targetSteps = 100000;
int arrowStep = 0;
void setup() {
  u8g2.begin();
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablem, OUTPUT);
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);


  digitalWrite(M0, LOW);
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);

  digitalWrite(dirPin, LOW);

  startMotor(); 
  prime_anim.start();
}

void prime_anima() {
    
    // if (millis() - lastUpdate < animationInterval) return;
    // lastUpdate = millis();

    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_helvB08_te); 

     u8g2.drawStr(45, 15, "Purging"); 
    

    if (arrowStep >= 1)
        u8g2.drawStr(60, 30, "V");
    if (arrowStep >= 2)
        u8g2.drawStr(60, 40, "V");
    if (arrowStep >= 3)
        u8g2.drawStr(60, 50, "V");

    u8g2.sendBuffer();

    arrowStep++;
    if (arrowStep > 3) arrowStep = 0; 
}

void stepperPulse() {
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(1); 
  digitalWrite(stepPin, LOW);

  stepCount++;
  if (stepCount >= targetSteps) {
    stopMotor();
  }
}

void startMotor() {
  stepCount = 0;
  digitalWrite(enablem, LOW); 
  motor.start();
  motorRunning = true;
}

void stopMotor() {
  motor.stop();
  prime_anim.stop();
  digitalWrite(enablem, HIGH); 
  motorRunning = false;
}

void loop() {
  motor.update();
  prime_anim.update();
}


//----------------------------------------------------------------------------------------------
// #include <AccelStepper.h>
// #include <U8g2lib.h>

// #define dirPin 13
// #define stepPin 11
// #define M0 10
// #define M1 9
// #define M2 8
// #define enablem 12

// AccelStepper stepper(AccelStepper::DRIVER, stepPin, dirPin);

// // --- OLED animation ticker ---
// #include "Ticker.h"
// void prime_anima();
// Ticker prime_anim(prime_anima, 1200, 0, MILLIS);
// U8G2_SSD1309_128X64_NONAME2_F_4W_SW_SPI u8g2(U8G2_R0, 35, 30, 33, 31, 32);

// unsigned long lastUpdate = 0;
// const unsigned long animationInterval = 600;
// int arrowStep = 0;

// void setup() {
//   u8g2.begin();

//   pinMode(enablem, OUTPUT);
//   pinMode(M0, OUTPUT);
//   pinMode(M1, OUTPUT);
//   pinMode(M2, OUTPUT);

//   // Try 1/8 microstepping for smooth motion
//   digitalWrite(M0, LOW);
//   digitalWrite(M1, LOW);
//   digitalWrite(M2, LOW);

//   digitalWrite(enablem, LOW); // enable motor

//   stepper.setMaxSpeed(1200);      // max speed (steps/sec)
//   stepper.setAcceleration(200);   // ramp rate
//   stepper.moveTo(20000);          // target steps

//   prime_anim.start();
// }

// void loop() {
//   stepper.run();        // generates smooth pulses with ramping
//   prime_anim.update();  // safe OLED animation
// }

// void prime_anima() {
//   if (millis() - lastUpdate < animationInterval) return;
//   lastUpdate = millis();

//   u8g2.clearBuffer();
//   u8g2.setFont(u8g2_font_helvB08_te);
//   u8g2.drawStr(45, 15, "Purging");

//   if (arrowStep >= 1) u8g2.drawStr(60, 30, "V");
//   if (arrowStep >= 2) u8g2.drawStr(60, 40, "V");
//   if (arrowStep >= 3) u8g2.drawStr(60, 50, "V");

//   u8g2.sendBuffer();

//   arrowStep++;
//   if (arrowStep > 3) arrowStep = 0;
// }
