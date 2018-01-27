#include <SoftwareServo.h>
#include "Stepper.h"
#define STEPS  34   // Number of steps per revolution of Internal shaft
//default STEP1 A0
#define STEP1 A0 //Sets stepper control pin 1
//default STEP2 A2
#define STEP2 A2 //sets stepper control pin 2
//default STEP3 A1
#define STEP3 A1 //sets stepper control pin 3
//default STEP4 A3
#define STEP4 A3 //sets stepper control pin 4
//default EN1 2
#define EN1 2 // Set left motor enable pin (ic 1)
//default ENG_LF 3
#define ENG_LF 3 // Set left forward (speed) pin (ic 2)
//default ENG_LR 5
#define ENG_LR 5 // Set left reverse (speed) pin (ic 7)
//default EN2 4
#define EN2 4 // Set right motor enable pin (ic 9)
//default ENG_RF 9
#define ENG_RF 9 // Set right forward (speed) pin (ic 10)
//default ENG_RR 6
#define ENG_RR 6 // Set Right reverse (speed) pin (ic 15)
#define ALARM_PIN 7 //Set alarm pin
#define PING_PIN 8 //Set ping sensor pin
#define ECHO_PIN 10 //Set echo sensor pin
//Define Pins
//Motor A
int enableA = EN1;
int MotorA1 = ENG_LF;
int MotorA2 = ENG_LR;
int MA_VAL;
//Motor B
int enableB = EN2;
int MotorB1 = ENG_RF;
int MotorB2 = ENG_RR;
int MB_VAL;
int ALARM;
int serialdata;
int pin;
int val;
int Steps2Take;  // Stepper: 2048 = 1 turn right, -2048 = 1 turn left
int StepperPos = 0; //Current recorded stepper position
int servoval; //Servo motor movement value (potentiometer emulation)
int inbyte;
int pingPin = PING_PIN;
int echoPin = ECHO_PIN;
long safeDistance = 14.0; //cm

/*-----( Declare objects )-----*/
// Setup of proper sequencing for Motor Driver Pins
// In1, In4, In3, In4 in the sequence 1-3-4-4
SoftwareServo servo;  // create servo object to control a servo
Stepper small_stepper(STEPS, STEP1, STEP2, STEP3, STEP4);
/*-----( End Declare Objects )-----*/

void enable() {
  digitalWrite (enableA, HIGH);
  digitalWrite (enableB, HIGH);
  Serial.println ("Engines enabled. Ready!");
}

void driveFwd() {
  Serial.print ("Drive Engaged! Moving forward at ");
  Serial.println (MA_VAL, MB_VAL);
  analogWrite (MotorA1, 0);
  analogWrite (MotorA2, MA_VAL);
  analogWrite (MotorB1, 0);
  analogWrite (MotorB2, MB_VAL);
  MA_VAL = 0;
  MB_VAL = 0;
}

void driveRev() {
  Serial.println ("Drive Engaged! Reversing...");
  analogWrite (MotorA1, MA_VAL);
  analogWrite (MotorA2, 0);
  analogWrite (MotorB1, MB_VAL);
  analogWrite (MotorB2, 0);
}
void turnRotateLeft() {
  Serial.println ("Rotating left...");
  //reverse
  analogWrite (MotorA1, MA_VAL);
  analogWrite (MotorA2, 0);
  analogWrite (MotorB1, 0);
  analogWrite (MotorB2, MB_VAL);
}
void turnRotateRight() {
  Serial.println ("Rotating right...");
  //reverse
  analogWrite (MotorA1, 0);
  analogWrite (MotorA2, MA_VAL);
  analogWrite (MotorB1, MB_VAL);
  analogWrite (MotorB2, 0);
}
void disable() {
  analogWrite (enableA, LOW);
  analogWrite (enableB, LOW);
  Serial.println ("Drive system disabled!");
}

void allStop() {
  Serial.println ("AllStop activated!");
  //stop
  analogWrite (MotorA1, 0);
  analogWrite (MotorA2, 0);
  analogWrite (MotorB1, 0);
  analogWrite (MotorB2, 0);
  if (ALARM = 1) {
    digitalWrite (ALARM_PIN, 1);
    Serial.println ("Disabling motors due to alarm state...");
    disable();
  }
}
void alarmClear() {
  digitalWrite (ALARM_PIN, 0);
  Serial.println ("Alarm cleared! Engines restored.");
  enable();
}
void stepperRotateLeft()
{
  small_stepper.setSpeed(500);
  Steps2Take = -256;
  StepperPos = StepperPos - 256;
  small_stepper.step(Steps2Take);
}
void stepperRotateRight()
{
  small_stepper.setSpeed(500);
  Steps2Take = 256;
  StepperPos = StepperPos + 256;
  small_stepper.step(Steps2Take);
}

void blink() {
	pinMode (13, OUTPUT);
        digitalWrite(pin, HIGH);
	delay 50;
	digitalWrite(pin, LOW);
}
void setup() {
	Serial.begin (115200);
	//configure pin modes
	pinMode (enableA, OUTPUT);
	pinMode (MotorA1, OUTPUT);
	pinMode (MotorA2, OUTPUT);
	pinMode (enableB, OUTPUT);
	pinMode (MotorB1, OUTPUT);
	pinMode (MotorB2, OUTPUT);
	pinMode (pingPin, OUTPUT);
	pinMode (echoPin, INPUT);
	enable();
	Serial.println ("Ready! Use '9:' for a list of commands.");
}

void loop() {
  if (Serial.available() > 0) {
    getSerial();
    switch (serialdata) {
      case 1:
        Serial.print("Read:");
        getSerial();
        switch (serialdata) {
          case 1:
            Serial.print("Digital;");
            getSerial();
            pin = serialdata;
            pinMode(pin, INPUT);
            val = digitalRead(pin);
            Serial.print(pin);
            Serial.print(",");
            Serial.println(val);
            val = 0;
            pin = 0;
            break;
          case 2:
            Serial.print("Analog,");
            getSerial();
            pin = serialdata;
            pinMode(pin, INPUT);
            val = analogRead(pin);
            Serial.print(pin);
            Serial.print(",");
            Serial.println(val);
            val = 0;
            pin = 0;
            break;
          case 3:
            Serial.print("Distance sensor,");
            getDistance();
            Serial.println(distance);
            distance = 0;
        }
        break;
      case 2:
        Serial.print("Write:");
        getSerial();
        switch (serialdata) {
          case 1:
            Serial.print("Digital;");
            getSerial();
            pin = serialdata;
            pinMode(pin, OUTPUT);
            getSerial();
            val = serialdata;
            if (val == 1) {
              digitalWrite(pin, LOW);
              Serial.print(pin);
              Serial.print(",LOW,val =");
              Serial.println(val);
            }
            else if (val == 2) {
              digitalWrite(pin, HIGH);
              Serial.print(pin);
              Serial.println(",HIGH,val =");
              Serial.println(val);
            }
            val = 0;
            pin = 0;
            break;
          case 2:
            Serial.print("Analog;");
            getSerial();
            pin = serialdata;
            pinMode(pin, OUTPUT);
            getSerial();
            val = serialdata;
            analogWrite(pin, val);
            Serial.print(pin);
            Serial.print(",");
            Serial.println(val);
            val = 0;
            pin = 0;
            break;
        }
        break;
      case 3:
        Serial.print("Servo:");
        getSerial();
        switch (serialdata) {
          case 1:
            Serial.println("Under development. Add servo left function here!");
            break;
          case 2:
            Serial.println("Under development. Add servo right function here!");
            break;
        }
        break;
      case 4:
        Serial.print("Stepper:");
        getSerial();
        switch (serialdata) {
          case 1:
            Serial.println("Rotate left");
            stepperRotateLeft();
            break;
          case 2:
            Serial.println("Rotate Right");
            stepperRotateRight();
            break;
        }
        break;
      case 5:
        Serial.print("Drive:");
        getSerial();
        switch (serialdata) {
          case 1:
            Serial.print("Forward;");
            getSerial();
            MA_VAL = serialdata;
            getSerial();
            MB_VAL = serialdata;
            driveFwd();
            break;
          case 2:
            Serial.print("Reverse;");
            getSerial();
            MA_VAL = serialdata;
            getSerial();
            MB_VAL = serialdata;
            driveRev();
            break;
        }
        break;
      case 6:
        Serial.print("360 Turn:");
        getSerial();
        switch (serialdata) {
          case 1:
            Serial.print("Left;");
            getSerial();
            MA_VAL = serialdata;
            getSerial();
            MB_VAL = serialdata;
            Serial.print(MA_VAL);
            Serial.print(",");
            Serial.println(MB_VAL);
            turnRotateLeft();
            break;
          case 2:
            Serial.print("Right;");
            getSerial();
            MA_VAL = serialdata;
            getSerial();
            MB_VAL = serialdata;
            Serial.print(MA_VAL);
            Serial.print(",");
            Serial.println(MB_VAL);
            turnRotateRight();
            break;
        }
        break;
      case 7:
        Serial.print("Alarm:");
        getSerial();
        switch (serialdata) {
          case 1:
            Serial.println("Off");
            ALARM = 0;
            alarmClear();
            break;
          case 2:
            Serial.println("On");
            ALARM = 1;
            allStop();
            break;
        }
        break;
      case 8:
        Serial.print("Motor On/Off:");
        getSerial();
        switch (serialdata) {
          case 1:
            Serial.println("Off");
            enable();
            break;
          case 2:
            Serial.println("On");
            disable();
            break;
        }
        break;
      case 9:
        Serial.println("Help:");
        Serial.println("1: Read, (1=digital, 2=analog, 3=distance sensor)");
        Serial.println("2: Write, (1=digital, 2=analog)");
        Serial.println("3: Servo, (1=left, 2=right) UNDER DEVELOPMENT");
        Serial.println("4: Stepper, (1=left, 2=right)");
        Serial.println("5: Drive, (1=forward, 2=reverse)");
        Serial.println("6: 360, Rotational turn (1=right, 2=reverse)");
        Serial.println("7: Alarm, (1=off, 2=on)");
        Serial.println("8: Enable/Disable, motors (1=off, 2=on)");
        break;
    }
  }
}
void getSerial() {
  serialdata = 0;
  while (inbyte != '/')
  {
    inbyte = Serial.read();
    if (inbyte > 0 && inbyte != '/')
    {
      serialdata = serialdata * 10 + inbyte - '0';
    }
  }
  inbyte = 0;
  return serialdata;
}
long getDistance()
{
  long duration;

  // Sending the signal, starting LOW for a clean signal
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // Get echo and calculate distance
  duration = pulseIn(echoPin, HIGH);
  return microsecondsToCentimeters(duration);
}

long microsecondsToCentimeters(long microseconds)
{
  // speed of sound = 340 m/s or 29 microseconds per centimeter.
  return microseconds / 29 / 2;
}

