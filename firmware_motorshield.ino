#define M1_PWM 6 // Set Motor 1 PWM pin (Default: D6)
#define M1_F 2 // Set Motor 1 forward (direction) pin (Default: D2)
#define M1_R 3 // Set Motor 1 reverse (direction) pin (Default: D3)
#define M2_PWM 9 // Set Motor 2 PWM pin (Default: D9)
#define M2_F 4 // Set Motor 2 forward (direction) pin (Default: D4)
#define M1_R 5 // Set Motor 2 reverse (direction) pin (Default: D5)
#define M3_PWM 10 // Set Motor 3 PWM pin (Default: D10)
#define M3_F 7 // Set Motor 3 forward (direction) pin (Default: D7)
#define M3_R 8 // Set Motor 3 reverse (direction) pin (Default: D8)
#define M4_PWM 11 // Set Motor 4 PWM pin (Default: D11)
#define M4_F 12 // Set Motor 4 forward (direction) pin (Default: D12)
#define M4_R 13 // Set Motor 4 reverse (direction) pin (Default: D13)

//Define Pins
//Motor 1
int pwm1 = M1_PWM;
int m1forward = M1_F;
int m1reverse = M!_R;
int M1_VAL;
//Motor 2
int pwm2 = M2_PWM;
int m2forward = M2_F;
int m2reverse = M2_R;
int M2_VAL;
//Motor 3
int pwm3 = M3_PWM;
int m3forward = M3_F;
int m3reverse = M3_R;
int M3_VAL;
//Motor 4
int pwm4 = M4_PWM;
int m4forward = M4_F;
int m4reverse = M4_R;
int M4_VAL;
int ALARM;
int serialdata;
int pin;
int val;
int inbyte;

void driveFwd() {
	Serial.print ("Drive Engaged! Moving forward at ");
	Serial.println (M1_VAL, M2_VAL);
	digitalWrite (m1forward, 1);
	digitalWrite (m1reverse, 0);
	digitalWrite (m2forward, 1);
	digitalWrite (m2reverse, 0);
	analogWrite (pwm1, M1_VAL);
	analogWrite (pwm2, M2_VAL);
	M1_VAL = 0;
	M2_VAL = 0;
}
void driveRev() {
	Serial.print ("Drive Engaged! Reversing at ");
	Serial.println (M1_VAL, M2_VAL);
	digitalWrite (m1forward, LOW);
	digitalWrite (m1reverse, HIGH);
	digitalWrite (m2forward, LOW);
	digitalWrite (m2reverse, HIGH);
	analogWrite (pwm1, M1_VAL);
	analogWrite (pwm2, M2_VAL);
	M1_VAL = 0;
	M2_VAL = 0;
}
void turnRotateLeft() {
	Serial.print ("Drive Engaged! Rotating left at ");
	Serial.println (M1_VAL, M2_VAL);
	digitalWrite (m1forward, LOW);
	digitalWrite (m1reverse, HIGH);
	digitalWrite (m2forward, HIGH);
	digitalWrite (m2reverse, LOW);
	analogWrite (pwm1, M1_VAL);
	analogWrite (pwm2, M2_VAL);
	M1_VAL = 0;
	M2_VAL = 0;
}
void turnRotateRight() {
	Serial.print ("Drive Engaged! Rotating right at ");
	Serial.println (M1_VAL, M2_VAL);
	digitalWrite (m1forward, HIGH);
	digitalWrite (m1reverse, LOW);
	digitalWrite (m2forward, LOW);
	digitalWrite (m2reverse, HIGH);
	analogWrite (pwm1, M1_VAL);
	analogWrite (pwm2, M2_VAL);
	M1_VAL = 0;
	M2_VAL = 0;
}
void allStop() {
	M1_VAL = 0;
	M2_VAL = 0;
	analogWrite (pwm1, M1_VAL);
	analogWrite (pwm2, M2_VAL);
	digitalWrite (m1forward, LOW);
	digitalWrite (m1reverse, LOW);
	digitalWrite (m2forward, LOW);
	digitalWrite (m2reverse, LOW);
	Serial.println ("Engined stopped!");
}
void alarmClear() {
	digitalWrite (ALARM_PIN, 0);
	Serial.println ("Alarm cleared! Engines restored.");
}
void blink() {
	pinMode (13, OUTPUT);
	digitalWrite(pin, HIGH);
	delay 50;
	digitalWrite(pin, LOW);
}
void setup() {
	Serial.begin (115200);
	//configure pin modes (Uncomment lines to use that motor)
	pinMode (pwm1, OUTPUT);
	pinMode (m1forward, OUTPUT);
	pinMode (m1reverse, OUTPUT);
	pinMode (pwm2, OUTPUT);
	pinMode (m2forward, OUTPUT);
	pinMode (m2reverse, OUTPUT);
//	pinMode (pwm3, OUTPUT);
//	pinMode (m3forward, OUTPUT);
//	pinMode (m3reverse, OUTPUT);
//	pinMode (pwm4, OUTPUT);
//	pinMode (m4forward, OUTPUT);
//	pinMode (m4reverse, OUTPUT);
	Serial.println ("Ready! Use '8' for a list of commands.");
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
			Serial.println("Under development. Add stepper left function here!");
			break;
		  case 2:
			Serial.println("Under development. Add stepper right function here!");
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
			M1_VAL = serialdata;
			getSerial();
			M2_VAL = serialdata;
			driveFwd();
			break;
		  case 2:
			Serial.print("Reverse;");
			getSerial();
			M1_VAL = serialdata;
			getSerial();
			M2_VAL = serialdata;
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
		Serial.println("Help:");
		Serial.println("1: Read, (1=digital, 2=analog, 3=distance sensor)");
		Serial.println("2: Write, (1=digital, 2=analog)");
		Serial.println("3: Servo, (1=left, 2=right) UNDER DEVELOPMENT");
		Serial.println("4: Stepper, (1=left, 2=right)");
		Serial.println("5: Drive, (1=forward, 2=reverse)");
		Serial.println("6: 360, Rotational turn (1=right, 2=reverse)");
		Serial.println("7: Alarm, (1=off, 2=on)");
		Serial.println("8: Display this help menu.");
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
