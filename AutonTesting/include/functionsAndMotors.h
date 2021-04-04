using namespace vex;
#include "vex.h"
extern brain Brain;


vex::inertial Inertial(vex::PORT16);
vex::motor LeftTop = vex::motor(vex::PORT14, true);
vex::motor LeftBottom = vex::motor(vex::PORT13);
vex::motor RightTop = vex::motor(vex::PORT17);
vex::motor RightBottom = vex::motor(vex::PORT18, true);
vex::motor BottomShooter = vex::motor(vex::PORT11);
vex::motor TopShooter = vex::motor(vex::PORT20);
vex::motor LeftBallIntake = vex::motor(vex::PORT1);
vex::motor RightBallIntake = vex::motor(vex::PORT10, true);
vex::controller Controller_Ruh = vex::controller();

motor_group DriveBase = motor_group(LeftTop, LeftBottom, RightTop, RightBottom);
motor_group LeftSide = motor_group(LeftTop, LeftBottom);
motor_group RightSide = motor_group(RightTop, RightBottom);
motor_group Intakes = motor_group(LeftBallIntake, RightBallIntake);
motor_group Shooters = motor_group(TopShooter, BottomShooter);



float ballOverSensor = 0;
float ballOverSensorBlue = 0;
float ballOverSensorTop = 0;
float ballOverSensorTopBlue = 0;
float currRedBalls = 0;
float currBlueBalls = 0;

float AutonomousMode = 0;
float DriveMode = 0;

float Power = 0; // Power to motors
float kP = 0.003; // Const to scale the power according to error
float kI = 60; // Const to give a boost to the power level

float turnKI = 40;

float integral = 0; // Key part in the I, which stands for integral
float error = 10; // distance between robot and destination, set to 10 to enter the while loop
float currValue = 0;
float rev = 9.42477; // 1 revolution is 9.42477 inches. 
float inch = 0.106103; // 1 inch is 0.106103 revolutions. 
float deceleration = 1;
float accelerate = 15; // variable to slowly accelerate as to not jump around

float PenX = 200;
float PenY = 200;
float intendedHeading = 0;
float intendedHeadingLeft = 0;

void resetMotorEncoder(){
  DriveBase.resetPosition();
  error = 10;
  Power = 0;
  currValue = 0;
}

void drawWildCard()
{
  repeat(150){
    Brain.Screen.drawRectangle(PenX, PenY, 2, 2);
    PenY --;
    }
    repeat (5){
    PenY = PenY - 2;
    PenX = PenX + 2;
    Brain.Screen.drawRectangle(PenX, PenY, 2, 2);
    }
    repeat(100){
      Brain.Screen.drawRectangle(PenX, PenY, 2, 2);
      PenX ++;
    }
    repeat (5){
    PenY = PenY + 2;
    PenX = PenX + 2;
    Brain.Screen.drawRectangle(PenX, PenY, 2, 2);
    }
    repeat(150){
    Brain.Screen.drawRectangle(PenX, PenY, 2, 2);
    PenY ++;
    }
    repeat (5){
    PenY = PenY + 2;
    PenX = PenX - 2;
    Brain.Screen.drawRectangle(PenX, PenY, 2, 2);
    }
    repeat(100){
      Brain.Screen.drawRectangle(PenX, PenY, 2, 2);
      PenX --;
    }
    repeat (5){
    PenY = PenY - 2;
    PenX = PenX - 2;
    Brain.Screen.drawRectangle(PenX, PenY, 2, 2);
    }
     Brain.Screen.setPenColor(red);
    Brain.Screen.setFillColor(red);
    PenX = 220;
    PenY = 60;
    Brain.Screen.drawRectangle(PenX, PenY, 5, 5);
    PenX = PenX + 10;
    Brain.Screen.setPenColor(blue);
    Brain.Screen.setFillColor(blue);
    Brain.Screen.drawRectangle(PenX, PenY, 5, 5);
    PenY = PenY + 10;
    Brain.Screen.setPenColor(green);
    Brain.Screen.setFillColor(green);
    Brain.Screen.drawRectangle(PenX, PenY, 5, 5);
    PenX = PenX - 10;
    Brain.Screen.setPenColor(yellow);
    Brain.Screen.setFillColor(yellow);
    Brain.Screen.drawRectangle(PenX, PenY, 5, 5);
}

void driveForward(double desiredValue)
{
  while(currValue > desiredValue + 0.5 || currValue < desiredValue - 0.5)
  {
  Brain.Screen.printAt(30, 90, "Inertial Heading: %f",Inertial.heading());
  Brain.Screen.printAt(30, 20, "Error: %f", error);
  Brain.Screen.printAt(30, 50, "Power: %f", Power);

    if(error > 1)
    {
  Power = error * kP + error * kI; 
    }
    if(Power < 60)
    {
      Power = 60;
    }
  currValue = RightTop.position(turns);
  error = desiredValue - currValue;
  DriveBase.spin(fwd, Power, rpm);
  }
  DriveBase.stop(hold);
  resetMotorEncoder();
  desiredValue = 0;
  accelerate = 15;
}


//    Basics of a PID Loop
//
// PID loops are used widely in robotics and engineering.
//   They are a great way to provide accuracy and consistency
//   to movements. A PID loop has 3 main parts to it. My 
//   version only uses the first two however, making it a 
//   PI loop.
//
// P - Proportional
// I - Integral
// D - Derivative
//
// Proportional - This is the essential part of the loop. 
//                  The main aspect of this is explained
//                  by the name. The power to the motors
//                  are controlled by this code. The 
//                  distance between the robot and the 
//                  end destination, also called the
//                  error, is directly proportional to
//                  the power of the motors. As the robot
//                  gets closer to the destination, the
//                  power of the motors decrease. The end
//                  result is more accurate movement
//                  because the robot will not overshoot
//                  its target.
//
// Integral -     Now, the proportional part is the only
//                  necessary part of a PID loop, but what 
//                  might happen is the robot goes so slow
//                  near the end that it doesn't have 
//                  enough power to move. The integral is a
//                  constant added to the equation to 
//                  increase the power of the motors. 
//                  
// Derivative -   The Derivative is one last variable added
//                  to the equation to reduce oscillation.
//                  This is only needed in very precise
//                  movements. My partiular code does not
//                  use the derivative part of a PID loop,
//                  making it a PI loop. 

void turnRightIntegral (int degs)
{
  Inertial.calibrate(); 
  while (Inertial.isCalibrating()) { wait(100, msec); } 
  LeftSide.spin(fwd, 30, rpm); 
  RightSide.spin(fwd, -30, rpm); 
  while ((Inertial.rotation(degrees) <= degs - 0.1))
  {
    vex::task::sleep(20);
  }
  LeftSide.stop(); 
  RightSide.stop(); 
  wait(0.2, seconds); 
  while(Inertial.rotation(degrees) > degs + 0.3)
  {
  LeftSide.spin(fwd, -8, rpm); 
  RightSide.spin(fwd, 8, rpm); 
  }
  LeftSide.stop(); 
  RightSide.stop(); 
  resetMotorEncoder();
  wait(0.5, seconds); 
  }

void turnRight(float degs)
{
  DriveBase.resetPosition();
  while(currValue > degs + 0.05 || currValue < degs - 0.05)
  {
  Brain.Screen.printAt(30, 90, "Inertial Heading: %f",Inertial.heading());
  Brain.Screen.printAt(30, 20, "Error: %f", error);
  Brain.Screen.printAt(30, 50, "Power: %f", Power);

  Power = error * kP + error * turnKI; 
  currValue = LeftTop.position(turns);
  if(Power < 42)
  {
    Power = 42;
  }
  if(Power > 115){
  
    Power = 115;
  }
  error = degs - currValue;
  LeftSide.spin(fwd, Power, rpm);
  RightSide.spin(fwd, -Power, rpm);
  }
  DriveBase.stop(hold);
  resetMotorEncoder();
  DriveBase.resetPosition();
  degs = 0;
}

void turnRightSlower(float degs)
{
  DriveBase.resetPosition();
  while(currValue > degs + 0.05 || currValue < degs - 0.05)
  {
  Brain.Screen.printAt(30, 90, "Inertial Heading: %f",Inertial.heading());
  Brain.Screen.printAt(30, 20, "Error: %f", error);
  Brain.Screen.printAt(30, 50, "Power: %f", Power);

  Power = error * kP + error * turnKI; 
  currValue = LeftTop.position(turns);
  if(Power < 52)
  {
    Power = 52;
  }
  if(Power > 120)
  {
    Power = 120;
  }
  error = degs - currValue;
  LeftSide.spin(fwd, Power, rpm);
  RightSide.spin(fwd, -Power, rpm);
  }
  DriveBase.stop(hold);
  resetMotorEncoder();
  DriveBase.resetPosition();
  degs = 0;
}

void turnRightSlower2(float degs)
{
  DriveBase.resetPosition();
  while(currValue > degs + 0.02 || currValue < degs - 0.02)
  {
  Brain.Screen.printAt(30, 90, "Inertial Heading: %f",Inertial.heading());
  Brain.Screen.printAt(30, 20, "Error: %f", error);
  Brain.Screen.printAt(30, 50, "Power: %f", Power);

  Power = error * kP + error * turnKI; 
  currValue = LeftTop.position(turns);
  if(Power < 36)
  {
    Power = 36;
  }
  if(Power > 120)
  {
    Power = 120;
  }
  error = degs - currValue;
  LeftSide.spin(fwd, Power, rpm);
  RightSide.spin(fwd, -Power, rpm);
  }
  DriveBase.stop(hold);
  resetMotorEncoder();
  DriveBase.resetPosition();
  degs = 0;
}

void turnLeft(float degs)
{
  DriveBase.resetPosition();
  while(currValue > degs + 0.05 || currValue < degs - 0.05)
  {
  Brain.Screen.printAt(30, 90, "Inertial Heading: %f",Inertial.heading());
  Brain.Screen.printAt(30, 20, "Error: %f", error);
  Brain.Screen.printAt(30, 50, "Power: %f", Power);

  Power = error * kP + error * turnKI; 
  currValue = RightTop.position(turns);
  if(Power < 42)
  {
    Power = 42;
  }
  if(Power > 120)
  {
    Power = 120;
  }
  error = degs - currValue;
  LeftSide.spin(fwd, -Power, rpm);
  RightSide.spin(fwd, Power, rpm);
  }
  DriveBase.stop(hold);
  resetMotorEncoder();
  DriveBase.resetPosition();
  degs = 0;
  currValue = 0;
}

void turnLeftSlower(float degs)
{
  DriveBase.resetPosition();
  while(currValue > degs + 0.05 || currValue < degs - 0.05)
  {
  Brain.Screen.printAt(30, 90, "Inertial Heading: %f",Inertial.heading());
  Brain.Screen.printAt(30, 20, "Error: %f", error);
  Brain.Screen.printAt(30, 50, "Power: %f", Power);

  Power = error * kP + error * turnKI; 
  currValue = RightTop.position(turns);
  if(Power < 52)
  {
    Power = 52;
  }
  if(Power > 120)
  {
    Power = 120;
  }
  error = degs - currValue;
  LeftSide.spin(fwd, -Power, rpm);
  RightSide.spin(fwd, Power, rpm);
  }
  DriveBase.stop(hold);
  resetMotorEncoder();
  DriveBase.resetPosition();
  degs = 0;
  currValue = 0;
}

void waitUntilRedBall()
{
  OpticalSensor.setLightPower(100, percent);
  Intakes.spin(fwd, 100, rpm);
  BottomShooter.spin(fwd, 100, rpm);
  TopShooter.spin(fwd, 300, rpm);
waitUntil(OpticalSensor.hue() > 0 && OpticalSensor.hue() < 45);
  Intakes.stop(hold);
  BottomShooter.stop(hold);
  TopShooter.stop(hold);
}

void waitUntilRedBallSlow()
{
  OpticalSensor.setLightPower(100, percent);
  Intakes.spin(fwd, 100, rpm);
  BottomShooter.spin(fwd, 100, rpm);
  TopShooter.spin(fwd, 100, rpm);
waitUntil(OpticalSensor.hue() > 0 && OpticalSensor.hue() < 55);
  Intakes.stop(hold);
  BottomShooter.stop(hold);
  TopShooter.stop(hold);
}

void waitUntilBlueBall()
{
  OpticalSensor.setLightPower(100, percent);
  Intakes.spin(fwd, 400, rpm);
  BottomShooter.spin(fwd, 400, rpm);
  TopShooter.spin(fwd, 500, rpm);
  waitUntil(OpticalSensor.hue() > 95 && OpticalSensor.hue() < 175);
  Intakes.stop(hold);
  BottomShooter.stop(hold);
  TopShooter.stop(hold);
}

void waitUntilBlueBallLeft()
{
  OpticalSensor.setLightPower(100, percent);
  Intakes.spin(fwd, 500, rpm);
  BottomShooter.spin(fwd, 500, rpm);
  TopShooter.spin(fwd, 500, rpm);
  waitUntil(OpticalSensor.hue() > 95 && OpticalSensor.hue() < 175);
  Intakes.stop(hold);
  BottomShooter.stop(hold);
  TopShooter.stop(hold);
}

void waitUntilBlueBallSlow()
{
  OpticalSensor.setLightPower(100, percent);
  Intakes.spin(fwd, 100, rpm);
  BottomShooter.spin(fwd, 100, rpm);
  TopShooter.spin(fwd, 100, rpm);
waitUntil(OpticalSensor.hue() > 95 && OpticalSensor.hue() < 175);
  Intakes.stop(hold);
  BottomShooter.stop(hold);
  TopShooter.stop(hold);
}

void MovePID(double dist)
{
  DriveBase.resetRotation();
  kP = 0.028;
  kI = 100000;
  float kD = 10000;
  float totalError = 0;
  float lastError = 0;
  float error = 0;
  float currSpeed = 0;
  float mseconds = 0;
  while(dist > LeftTop.rotation(turns))
{
  lastError = error;
  error = dist - LeftTop.rotation(turns);
  totalError = totalError + error;
  float diffError = error - lastError;
  currSpeed = (error /kP) + (totalError / kI) + 40;
  mseconds = mseconds + 1;
  DriveBase.spin(fwd, currSpeed, rpm);
  Brain.Screen.printAt(30, 20, "Error: %f", error);
  Brain.Screen.printAt(30, 40, "Distance: %f", dist);
  Brain.Screen.printAt(30, 60, "Current Speed: %f", currSpeed);
  Brain.Screen.printAt(30, 80, "Total Error: %f", totalError);
  Brain.Screen.printAt(30, 100, "Last Error: %f", lastError);
  Brain.Screen.printAt(30, 120, "Rate of Change in Error: %f", diffError);
  Brain.Screen.printAt(30, 120, "Time elapsed: %f", mseconds / 1000);
  wait(1, msec);
}
DriveBase.stop(hold);
}

void MoveAccel(float dist)
{
  DriveBase.resetRotation();
  while(LeftTop.position(turns) < dist)
  {
    float error = dist - LeftTop.position(turns);
    float speed = sqrt(10000 * error);
    DriveBase.spin(fwd, speed, rpm);
    Brain.Screen.printAt(30, 20, "Speed: %f", speed);
  }
  DriveBase.stop(hold);
}

void NewPIDMove(float dist)
{
  DriveBase.resetPosition();
  float error = 0.06;
  float kP = 0.01;
  float kD = 10000;
  float speed = 0;
  float errorDiff = 0;
  float lastError = 0;
  while (0.05 < error || error < -0.05)
  {
    DriveBase.spin(fwd, speed + 15, rpm);
    lastError = error;
    error = dist - LeftTop.position(turns);
    errorDiff = error - lastError;
    speed = error / kP ;
  }
  DriveBase.stop(hold);
}

void NewPIDTurnRight(float degs)
{
  intendedHeading = intendedHeading + degs;
  DriveBase.resetPosition();
  degs = degs / (degs / 1.1);
  float error = 0.06;
  float kP = 0.01;
  float kD = 10000;
  float speed = 0;
  float errorDiff = 0;
  float lastError = 0;
  while (0.05 < error || error < -0.05)
  {
    LeftSide.spin(fwd, speed + 15, rpm);
    RightSide.spin(fwd, -speed - 15, rpm);
    lastError = error;
    error = degs - LeftTop.position(turns);
    errorDiff = error - lastError;
    speed = error / kP;
    Brain.Screen.printAt(30, 20, "Heading: %f", Inertial.heading());
  }
  while(Inertial.heading() > intendedHeading)
  {
    RightSide.spin(fwd, 10, rpm);
    LeftSide.spin(fwd, -10, rpm);
  } 
  if(intendedHeading > 340)
  {
    while(Inertial.heading() > 0.1)
    {
    RightSide.spin(fwd, 10, rpm);
    LeftSide.spin(fwd, -10, rpm);
    Brain.Screen.printAt(30, 20, "Heading: %f", Inertial.heading());
    }
  }
  DriveBase.stop(hold);
}

void NewPIDTurnLeft(float degs)
{
  intendedHeadingLeft = intendedHeadingLeft + degs;
  DriveBase.resetPosition();
  degs = degs / (degs / 1.1);
  float error = 0.06;
  float kP = 0.01;
  float kD = 10000;
  float speed = 0;
  float errorDiff = 0;
  float lastError = 0;
  while (0.05 < error || error < -0.05)
  {
    LeftSide.spin(fwd, -speed - 10, rpm);
    RightSide.spin(fwd, +speed + 10, rpm);
    lastError = error;
    error = degs - RightTop.position(turns);
    errorDiff = error - lastError;
    speed = error / kP;
    Brain.Screen.printAt(30, 20, "Heading: %f", Inertial.heading());
  }
  DriveBase.stop(hold);
}

void PIDForward(float inches) //Coded in Inches
{

  float kP = 160;
  float kD = 0.5;
  float error = 2;
  float prevError = 0;
  float pwr = 0;
  float derivative = 0;

  DriveBase.resetRotation();
  while (0.4 < error || error < -0.2){
  error = inches - (LeftTop.position(turns)* 10.2101761242);
  derivative = error - prevError;
  prevError = error; 

  pwr = (error / 10.2101761242) * kP + derivative * kD;
  DriveBase.spin(fwd, pwr, rpm);
  wait(15, msec);

  }
  DriveBase.stop(hold);
}

void PIDForwardSlow(float inches) //Coded in Inches
{

  float kP = 160;
  float kD = 0.5;
  float error = 2;
  float prevError = 0;
  float pwr = 0;
  float derivative = 0;

  DriveBase.resetRotation();
  while (0.2 < error || error < -0.2){
  error = inches - (LeftTop.position(turns)* 10.2101761242);
  derivative = error - prevError;
  prevError = error; 

  pwr = (error / 10.2101761242) * kP + derivative * kD;
  if(pwr > 80)
  {
    pwr = 80;
  }
  DriveBase.spin(fwd, pwr, rpm);
  wait(15, msec);

  }
  DriveBase.stop(hold);
}

void indexRed()
{
  OpticalSensor.setLightPower(100, pct);
  OpticalSensorTop.setLightPower(100, pct);
  if (ballOverSensor == 0)
  {
    if(OpticalSensor.hue() > 0 && OpticalSensor.hue() < 40){
    currRedBalls = currRedBalls + 1;
    ballOverSensor = 1;
    Brain.Screen.setPenColor(red);
    }
  }
  else if (ballOverSensor == 1 && OpticalSensor.hue() > 42)
  {
    ballOverSensor = 0;
  } 
  if(ballOverSensorTop == 0){
    if (OpticalSensorTop.hue() > 0 && OpticalSensorTop.hue() < 40)
    {
      currRedBalls = currRedBalls - 1;
      ballOverSensorTop = 1;
      if (currRedBalls < 0)
      {
        currRedBalls = 0;
      }
      Brain.Screen.setPenColor(white);
      }
  }
  else if (ballOverSensorTop == 1 && OpticalSensorTop.hue() > 42)
  {
    ballOverSensorTop = 0;
  }

}

void indexBlue(){
  OpticalSensor.setLightPower(100, pct);
  OpticalSensorTop.setLightPower(75, pct);
if (ballOverSensorBlue == 0)
  {
    if(OpticalSensor.hue() > 95 && OpticalSensor.hue() < 255){
    currBlueBalls = currBlueBalls + 1;
    ballOverSensorBlue = 1;
    Brain.Screen.setPenColor(blue);
    }
  }
  else if (ballOverSensorBlue == 1 && OpticalSensor.hue() < 70)
  {
    ballOverSensorBlue = 0;
  } 
  if(ballOverSensorTopBlue == 0){
    if (OpticalSensorTop.hue() > 50 && OpticalSensorTop.isNearObject())
    {
      currBlueBalls = currBlueBalls - 1;
      ballOverSensorTopBlue = 1;
      if (currBlueBalls < 0)
      {
        currBlueBalls = 0;
      }
      Brain.Screen.setPenColor(white);
    }
  }
  else if (ballOverSensorTopBlue == 1 && OpticalSensorTop.hue() < 60 && OpticalSensorTop.isNearObject() == false)
  {
    ballOverSensorTopBlue = 0;
  }
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(30, 160, "CurrRedBalls : %f", currRedBalls);
  Brain.Screen.printAt(30, 180, "CurrBlueBalls : %f", currBlueBalls);
  Brain.Screen.printAt(30, 200, "BallOnSensorValue : %f", ballOverSensor);
  Brain.Screen.printAt(30, 220, "BallOnSensorBlueValue : %f", ballOverSensorBlue);
}

void spinUntilRedBlue(float numRed, float numBlue)
{
  while(currRedBalls != numRed || currBlueBalls != numBlue){
    LeftBallIntake.spin(fwd, 300, rpm);
    RightBallIntake.spin(fwd, 300, rpm);
    BottomShooter.spin(fwd, 200, rpm);
    indexRed();
    indexBlue();
  }
  Intakes.stop(hold);
  Shooters.stop(hold);
}