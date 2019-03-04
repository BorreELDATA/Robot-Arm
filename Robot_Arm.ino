/**
 *  This program is developed and written by Børre A. Opedal Lunde.
 *  Creation date: 2018
 *  Last updated:  04.03.2019
 */

#include <Servo.h>

Servo fingerServo, handServoOne, handServoTwo, elbowServo, shoulderServoOne, shoulderServoTwo;

byte fingerServoAngle, handServoOneAngle, handServoTwoAngle, elbowServoAngle, shoulderServoOneAngle, shoulderServoTwoAngle;
const byte fingerServoPin = 3;
const byte handServoOnePin = 5;
const byte handServoTwoPin = 6;
const byte elbowServoPin = 9;
const byte shoulderServoOnePin = 10;
const byte shoulderServoTwoPin = 11;

const byte MOTION_INTERVAL = 0;
const byte MAX_ANGLE = 180;
const byte MIN_ANGLE = 0;

/**
   Writes all respective angles to all servo motors.
*/
void updateAngles() {
  fingerServo.write(fingerServoAngle);
  handServoOne.write(handServoOneAngle);
  handServoTwo.write(handServoTwoAngle);
  elbowServo.write(elbowServoAngle);
  shoulderServoOne.write(shoulderServoOneAngle);
  shoulderServoTwo.write(shoulderServoTwoAngle);
}

/**
   Attaches the servo motor objects with the respective pin numbers.
*/
void attachServos() {
  fingerServo.attach(fingerServoPin);
  handServoOne.attach(handServoOnePin);
  handServoTwo.attach(handServoTwoPin);
  elbowServo.attach(elbowServoPin);
  shoulderServoOne.attach(shoulderServoOnePin);
  shoulderServoTwo.attach(shoulderServoTwoPin);
}

/**
   Returns a servo motor object based on its pin number.
   @param servoPin
          The pin number of the servo motor.
*/
Servo getServo(const byte servoPin) {
  switch (servoPin) {
    case fingerServoPin:
      return fingerServo;
    case handServoOnePin:
      return handServoOne;
    case handServoTwoPin:
      return handServoTwo;
    case elbowServoPin:
      return elbowServo;
    case shoulderServoOnePin:
      return shoulderServoOne;
    case shoulderServoTwoPin:
      return shoulderServoTwo;
  }
}

/**
   Returns a servo motor name based on its servo motor pin number.
   @param servoPin
          The pin number of the servo motor.
*/
String getServoName(const byte servoPin) {
  switch (servoPin) {
    case fingerServoPin:
      return "fingers";
    case handServoOnePin:
      return "hand one";
    case handServoTwoPin:
      return "hand two";
    case elbowServoPin:
      return "elbow";
    case shoulderServoOnePin:
      return "shoulder one";
    case shoulderServoTwoPin:
      return "shoulder two";
  }
}

/**
   Returns the angle of an arm part (servo motor).
   @param servoPin
          The pin number of the servo motor.
*/
byte getArmPartAngle(const byte servoPin) {
  switch (servoPin) {
    case fingerServoPin:
      return fingerServoAngle;
    case handServoOnePin:
      return handServoOneAngle;
    case handServoTwoPin:
      return handServoTwoAngle;
    case elbowServoPin:
      return elbowServoAngle;
    case shoulderServoOnePin:
      return shoulderServoOneAngle;
    case shoulderServoTwoPin:
      return shoulderServoTwoAngle;
  }
}

/**
   Sets the angle of an arm part (servo motor).
   @param servoPin
          The pin number of the servo motor.
   @param angle
          The angle that is set to servo motor.
*/
void setArmPartAngle(const byte servoPin, const byte angle) {
  switch (servoPin) {
    case fingerServoPin:
      fingerServoAngle = angle;
      break;
    case handServoOnePin:
      handServoOneAngle = angle;
      break;
    case handServoTwoPin:
      handServoTwoAngle = angle;
      break;
    case elbowServoPin:
      elbowServoAngle = angle;
      break;
    case shoulderServoOnePin:
      shoulderServoOneAngle = angle;
      break;
    case shoulderServoTwoPin:
      shoulderServoTwoAngle = angle;
      break;
  }
}

/**
   Writes an angle to a servo motor.
   @param servoPin
          The pin number of the servo motor.
   @param angle
          The angle to be written to the servo motor.
*/
void writeToServo(const byte servoPin, const byte angle) {
  switch (servoPin) {
    case fingerServoPin:
      fingerServo.write(angle);
      break;
    case handServoOnePin:
      handServoOne.write(angle);
      break;
    case handServoTwoPin:
      handServoTwo.write(angle);
      break;
    case elbowServoPin:
      elbowServo.write(angle);
      break;
    case shoulderServoOnePin:
      shoulderServoOne.write(angle);
      break;
    case shoulderServoTwoPin:
      shoulderServoTwo.write(angle);
      break;
  }
}

/**
   Moves a part (servo motor) of the arm to a certain angle.
   @param servoPin
          The pin number of the servo motor.
   @param destinationAngle
          The angle the servo motor will go to.
*/
void moveArmPart(const byte servoPin, const byte destinationAngle) {
  const String servoName = getServoName(servoPin);
  const byte previousAngle = getArmPartAngle(servoPin);

  Serial.println("Arm part: " + servoName + ", current angle: " + (String) previousAngle + ", destination angle: " + (String) destinationAngle + ".");

  if (destinationAngle > previousAngle) {
    for (int currentAngle = previousAngle; currentAngle <= destinationAngle; currentAngle += 1) {
      if (currentAngle > MAX_ANGLE) currentAngle = MAX_ANGLE;
      setArmPartAngle(servoPin, currentAngle);
      writeToServo(servoPin, currentAngle);
      Serial.println("Arm part: " + servoName + ", current angle (in motion): " + (String) currentAngle + ".");
      delay(MOTION_INTERVAL);
    }
  } else {
    for (int currentAngle = previousAngle; currentAngle >= destinationAngle; currentAngle -= 1) {
      if (currentAngle < MIN_ANGLE) currentAngle = MIN_ANGLE;
      setArmPartAngle(servoPin, currentAngle);
      writeToServo(servoPin, currentAngle);
      Serial.println("Arm part: " + servoName + ", current angle (in motion): " + (String) currentAngle + ".");
      delay(MOTION_INTERVAL);
    }
  }
}

/**
   Resets the angles of all servo motors
   of the robot arm to the min. angle (zero).
*/
void reset() {
  moveArmPart(fingerServoPin, MIN_ANGLE);
  moveArmPart(handServoOnePin, MIN_ANGLE);
  moveArmPart(handServoTwoPin, MIN_ANGLE);
  moveArmPart(elbowServoPin, MIN_ANGLE);
  moveArmPart(shoulderServoOnePin, MIN_ANGLE);
  moveArmPart(shoulderServoTwoPin, MIN_ANGLE);
}

/**
   A twist motion for robot arm testing purposes.
   The hand twists back and forth.
*/
void twist() {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 180; j += 4) {
      moveArmPart(handServoOnePin, j);
      moveArmPart(handServoTwoPin, j);
    }
    for (int j = 180; j > 0; j -= 4) {
      moveArmPart(handServoOnePin, j);
      moveArmPart(handServoTwoPin, j);
    }
  }
}

/**
   Setup method, necessary startup processes are run.
   The robot arm is controlled in this function.
*/
void setup() {
  Serial.begin(9600);
  Serial.println("Servos are being attached.");
  attachServos();
  Serial.println("Servos have been attached.\nStarting motion in 5 seconds...");
  delay(5000);
  twist();
}

/**
   Loop is not used in this program.
*/
void loop() {}
