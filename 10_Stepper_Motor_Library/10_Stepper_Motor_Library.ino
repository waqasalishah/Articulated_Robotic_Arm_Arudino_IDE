#include <AccelStepper.h>
#include <ESP32Servo.h>

// Stepper Motor 0 Base 
#define dirPin_0 18   //Yellow
#define stepPin_0 19  //Green
#define EnaPin_0 32  //Red


// Stepper Motor 1 Lower Arm
#define dirPin 26   //Yellow
#define stepPin 27  //Green
#define EnaPin 25  //Red
#define motorInterfaceType 1

// Stepper Motor 2 Upper Arm
#define dirPin_2 16   //Yellow
#define stepPin_2 17  //Green
#define EnaPin_2 32  //Red

//Servo pin 
#define ServoPin 33  //Orange

// Create a new instance of the AccelStepper class:
AccelStepper stepper_0 = AccelStepper(motorInterfaceType, stepPin_0, dirPin_0);
AccelStepper stepper_1 = AccelStepper(motorInterfaceType, stepPin, dirPin);
AccelStepper stepper_2 = AccelStepper(motorInterfaceType, stepPin_2, dirPin_2);

Servo myservo;  // create servo object to control a servo
// 16 servo objects can be created on the ESP32

//Define Global Variables
float Move = 0; 
int pos = 0;    // variable to store the servo position
int Delay_0=3000;

void setup() {

// Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	myservo.setPeriodHertz(50);    // standard 50 hz servo
	myservo.attach(ServoPin, 500, 2400); // attaches the servo on pin 34 to the servo object
	// using default min/max of 1000us and 2000us
	// different servos may require different min/max settings
	// for an accurate 0 to 180 sweep




  // setting max speed and acceleration
stepper_0.setMaxSpeed(600);
stepper_0.setAcceleration(100);

stepper_1.setMaxSpeed(300);
stepper_1.setAcceleration(100);

stepper_2.setMaxSpeed(300);
stepper_2.setAcceleration(100);

 Serial.begin(115200);
  delay(1000); // give me time to bring up serial moniton

  

}









void loop(){
int P0_1=700;
int P1_1=-1000;
int P2_1=-800;

int P0_2=-200;
int P1_2=-500;
int P2_2=-400;


Delay_0=3000;
int number_1;


// Starting Delay of 6 seconds
delay(6000);

 number_1 = Read_Number();



//Bend and pick object

stepper_0.moveTo(P0_1);
stepper_0.runToPosition();
delay(Delay_0);

stepper_2.moveTo(P2_1);
stepper_2.runToPosition();
delay(Delay_0);

stepper_1.moveTo(P1_1);
stepper_1.runToPosition();
delay(Delay_0);


Servo_close();



// lift object up and place

stepper_2.moveTo(P2_2);
stepper_2.runToPosition();
delay(Delay_0);

stepper_1.moveTo(P1_2);
stepper_1.runToPosition();
delay(Delay_0);

stepper_0.moveTo(P0_2);
stepper_0.runToPosition();
delay(Delay_0);

Servo_open();



Home();
number_1 = Read_Number();



}



// Functions
void Forward (int posn){
stepper_1.moveTo(posn);
stepper_1.runToPosition();
}

void Reverse (int posn){
stepper_1.moveTo(posn);
stepper_1.runToPosition();
}

void Servo_close(){
  //Servo Motor Routine CLOSE
	for (pos = 0; pos <= 62; pos += 1) { // goes from 0 degrees to 180 degrees
		// in steps of 1 degree
		myservo.write(pos);    // tell servo to go to position in variable 'pos'
		delay(15);             // waits 15ms for the servo to reach the position
	}
  delay (1000);
}

void Servo_open(){
//Servo Motor Routine OPEN
	for (pos = 62; pos >= 00; pos -= 1) { // goes from 180 degrees to 0 degrees
		myservo.write(pos);    // tell servo to go to position in variable 'pos'
		delay(15);             // waits 15ms for the servo to reach the position
	}
            // waits 15ms for the servo to reach the position
	
    delay (1000);
  }


int Read_Number(){
 Serial.println("Please enter a number:");
while (!Serial.available()); // Wait for input
  int pos = Serial.parseInt();
  Serial.print("You entered: ");
  Serial.println(pos);
	return pos;
}


void Home(){
  Serial.println("Going to Homing");

stepper_1.moveTo(0);
stepper_1.runToPosition();
delay(Delay_0);

stepper_0.moveTo(0);
stepper_0.runToPosition();
delay(Delay_0);

stepper_2.moveTo(0);
stepper_2.runToPosition();
delay(Delay_0);

  Serial.println("Finished Homing");

}

//Extra Code


// //Servo Motor Routine
// 	for (pos = 0; pos <= 62; pos += 1) { // goes from 0 degrees to 180 degrees
// 		// in steps of 1 degree
// 		myservo.write(pos);    // tell servo to go to position in variable 'pos'
// 		delay(15);             // waits 15ms for the servo to reach the position
// 	}
  
//   delay (1000);
// 	for (pos = 62; pos >= 00; pos -= 1) { // goes from 180 degrees to 0 degrees
// 		myservo.write(pos);    // tell servo to go to position in variable 'pos'
// 		delay(15);             // waits 15ms for the servo to reach the position
// 	}
