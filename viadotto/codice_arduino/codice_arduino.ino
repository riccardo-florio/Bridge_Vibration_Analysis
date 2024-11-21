#include <Servo.h>

/* --- VARIABLES AND CONSTANTS --- */

// Servomotors initialization
Servo servoVerticalRight;
Servo servoVerticalCenter;
Servo servoVerticalLeft;
Servo servoHorizontalRight;
Servo servoHorizontalCenter;
Servo servoHorizontalLeft;

// Buttons pins
const int pinButtonHeartquake = 2;
const int pinButtonVerticalRight = 3;
const int pinButtonVerticalCenter = 4;
const int pinButtonVerticalLeft = 5;
const int pinButtonCenter = 6;

// Servomotors pins
const int pinServoVerticalRight = 8;
const int pinServoVerticalCenter = 10;
const int pinServoVerticalLeft = 12;
const int pinServoHorizontalRight = 9;
const int pinServoHorizontalCenter = 11;
const int pinServoHorizontalLeft = 13;

// Calibration of servomotors
const int initialStateVerticalRight = 90;
const int initialStateVerticalCenter = 90;
const int initialStateVerticalLeft = 90;
const int initialStateHorizontalRight = 99;
const int initialStateHorizontalCenter = 101;
const int initialStateHorizontalLeft = 97;

// Servo Motor Stress Index
const int servoStressIndex = 7;

// It is used to trigger the relaxation of the servos only
// once after the earthquake
int triggerRelaxAfterHeartquake = 0;

// Movement limits
const int maxVertical = 30;
const int minVertical = -30;
const int maxHorizontal = 13;
const int minHorizontal = -13;

// Button states
bool statusButtonHeartquake = false;
bool statusButtonVerticalRight = false;
bool statusButtonVerticalCenter = false;
bool statusButtonVerticalLeft = false;
bool statusButtonCenter = false;


/* --- UTILITY FUNCTIONS --- */

/**
 * Move the servo to a target position slowly, avoiding strain.
 * 
 * @param servo The servo motor to be controlled.
 * @param target The target angle to move the servo to.
 */
void writeSlowly(Servo& servo, int target) {
  int initialValue = servo.read();

  if (initialValue > target) {
    for (int i = initialValue; i > target; i--) {
      servo.write(i);
      delay(20);
    }
  } else {
    if (initialValue != target) {
      for (int i = initialValue; i < target + servoStressIndex; i++) {
        servo.write(i);
        delay(20);
      }
      delay(200);
      servo.write(target);
    }
  }
}  //writeSlowly

/**
 * Starts heartquake
 */
void startHeartquake() {
  servoHorizontalRight.write(initialStateHorizontalRight + maxHorizontal);
  servoHorizontalCenter.write(initialStateHorizontalCenter + maxHorizontal);
  servoHorizontalLeft.write(initialStateHorizontalLeft + maxHorizontal);
  delay(100);
  servoHorizontalRight.write(initialStateHorizontalRight + minHorizontal);
  servoHorizontalCenter.write(initialStateHorizontalCenter + minHorizontal);
  servoHorizontalLeft.write(initialStateHorizontalLeft + minHorizontal);
  delay(100);
}  //startHeartquake

/**
 * Center the servos along the x-axis
 */
void centerHorizontally() {
  servoHorizontalRight.write(initialStateHorizontalRight);
  servoHorizontalCenter.write(initialStateHorizontalCenter);
  servoHorizontalLeft.write(initialStateHorizontalLeft);
}  //centerHorizontally

/**
 * Center the servos along the y-axis
 */
void centerVertically() {
  writeSlowly(servoVerticalRight, initialStateVerticalRight);
  writeSlowly(servoVerticalCenter, initialStateVerticalCenter);
  writeSlowly(servoVerticalLeft, initialStateVerticalLeft);
}  //centerVertically

/**
 * Relaxes the servos to avoid strain after stopping the earthquake.
 */
void relaxServos() {
  servoVerticalRight.write(servoVerticalRight.read() - 2);
  writeSlowly(servoVerticalRight, servoVerticalRight.read() + 2);
  servoVerticalCenter.write(servoVerticalCenter.read() - 2);
  writeSlowly(servoVerticalCenter, servoVerticalCenter.read() + 2);
  servoVerticalLeft.write(servoVerticalLeft.read() - 2);
  writeSlowly(servoVerticalLeft, servoVerticalLeft.read() + 2);
}  //relaxServos


/* --- BUTTONS MANAGEMENT FUNCTIONS --- */

/**
 * Toggles the status of a button-controlled servo and moves it to the target position.
 * 
 * @param pin The pin number associated with the button.
 * @param status The current status of the button (true or false).
 * @param servo The servo motor to control.
 * @param initialState The initial position of the servo.
 */
void handleButton(int pin, bool& status, Servo& servo, int initialState) {
  if (statusButtonCenter == false) {
    if (digitalRead(pin) == LOW) {
      status = !status;
      delay(50);  // Debounce delay
    }

    if (status == true) {
      writeSlowly(servo, initialState + minVertical);  // Collapse position
    } else {
      writeSlowly(servo, initialState + maxVertical);  // Raised position
    }
  }
}  //handleButton

/**
 * Start/stop earthquake
 */
void handleButtonHeartquake() {
  if (statusButtonCenter == false) {
    if (digitalRead(pinButtonHeartquake) == LOW) {
      statusButtonHeartquake = !statusButtonHeartquake;
      delay(200);  // Debounce delay
    }

    if (statusButtonHeartquake == true) {
      startHeartquake();
      triggerRelaxAfterHeartquake = 0;
    } else {
      centerHorizontally();
      triggerRelaxAfterHeartquake = triggerRelaxAfterHeartquake + 1;
      if (triggerRelaxAfterHeartquake == 1) {
        relaxServos();
        if (triggerRelaxAfterHeartquake >= 200) {
          triggerRelaxAfterHeartquake = 50;
        }
      }
    }
  }
}  //handleButtonHeartquake

/**
 * Centers/resets both horizontal and vertical servos when 
 * the corresponding button is pressed
 */
void handleButtonCenter() {
  if (digitalRead(pinButtonCenter) == LOW) {
    statusButtonCenter = !statusButtonCenter;
    delay(50);  // Debounce delay
  }

  if (statusButtonCenter == true) {
    centerHorizontally();
    centerVertically();
  }
}  //handleButtonCenter


/* --- SETUP AND LOOP --- */

void setup() {
  // Attaching the servo motors to the corresponding pins
  servoVerticalRight.attach(pinServoVerticalRight);
  servoVerticalCenter.attach(pinServoVerticalCenter);
  servoVerticalLeft.attach(pinServoVerticalLeft);
  servoHorizontalRight.attach(pinServoHorizontalRight);
  servoHorizontalCenter.attach(pinServoHorizontalCenter);
  servoHorizontalLeft.attach(pinServoHorizontalLeft);

  // Setting up buttons with internal pull-up resistors
  pinMode(pinButtonVerticalRight, INPUT_PULLUP);
  pinMode(pinButtonVerticalCenter, INPUT_PULLUP);
  pinMode(pinButtonVerticalLeft, INPUT_PULLUP);
  pinMode(pinButtonCenter, INPUT_PULLUP);
  pinMode(pinButtonHeartquake, INPUT_PULLUP);

  // Initial positions
  int vGap = maxVertical + servoStressIndex;
  servoVerticalRight.write(initialStateVerticalRight + vGap);
  servoVerticalCenter.write(initialStateVerticalCenter + vGap);
  servoVerticalLeft.write(initialStateVerticalLeft + vGap);
  servoHorizontalRight.write(initialStateHorizontalRight);
  servoHorizontalCenter.write(initialStateHorizontalCenter);
  servoHorizontalLeft.write(initialStateHorizontalLeft);
  delay(200);

  Serial.begin(9600);
}  //setup

void loop() {
  handleButton(pinButtonVerticalRight, statusButtonVerticalRight, servoVerticalRight, initialStateVerticalRight);
  handleButton(pinButtonVerticalCenter, statusButtonVerticalCenter, servoVerticalCenter, initialStateVerticalCenter);
  handleButton(pinButtonVerticalLeft, statusButtonVerticalLeft, servoVerticalLeft, initialStateVerticalLeft);

  handleButtonCenter();
  handleButtonHeartquake();
}  //loop
