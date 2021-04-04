using namespace vex;

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
vex::optical OpticalSensor(vex::PORT9);
vex::optical OpticalSensorTop(vex::PORT7);

motor_group DriveBase = motor_group(LeftTop, LeftBottom, RightTop, RightBottom);
motor_group LeftSide = motor_group(LeftTop, LeftBottom);
motor_group RightSide = motor_group(RightTop, RightBottom);
motor_group Intakes = motor_group(LeftBallIntake, RightBallIntake);

int AutonomousMode = 0;
int DriveMode = 0;

float Power = 0; // Power to motors
float kP = 0.00007; // Const to scale the power according to error
float kI = 1.8; // Const to give a boost to the power level

float turnKP = 0.00007;
float turnKI = 1.1;

float ballOverSensor = 0;
float ballOverSensorBlue = 0;
float ballOverSensorTop = 0;
float ballOverSensorTopBlue = 0;
float currRedBalls = 0;
float currBlueBalls = 0;

float Integral = 0; // Key part in the I, which stands for integral
float Error = 1; // distance between robot and destination, set to 1 to enter the while loop

void resetMotorEncoders()
{
  Error = 1;
  Integral = 0;
  Power = 0;
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

void TeamNameArt(){  
  DriveMode = 0;
  Brain.Screen.setPenColor(cyan);
  Brain.Screen.setPenWidth(13);
  Brain.Screen.setFillColor(black);
  Brain.Screen.drawLine(200, 40, 200, 200);
  Brain.Screen.drawLine(200, 40, 260, 40);
  Brain.Screen.drawLine(255, 40, 280, 60);
  Brain.Screen.drawLine(200, 200, 260, 200);
  Brain.Screen.drawLine(255, 200, 280, 180);
  Brain.Screen.drawLine(280, 180, 280, 150);
  Brain.Screen.drawLine(280, 60, 280, 90);
  Brain.Screen.drawLine(280, 90, 250, 120);
  Brain.Screen.drawLine(250, 120, 280, 150);
  //^^B
  Brain.Screen.setPenWidth(5);
  Brain.Screen.drawRectangle(40, 90, 20, 20);
  Brain.Screen.drawLine(63, 90, 63, 150);
  //^^9
  Brain.Screen.drawLine(160, 90, 160, 150);
  Brain.Screen.drawLine(160, 115, 135, 115);
  Brain.Screen.drawLine(135, 115, 135, 90);
  //^^4

  Brain.Screen.drawLine(340, 90, 340, 150);
  Brain.Screen.drawLine(340, 115, 315, 115);
  Brain.Screen.drawLine(315, 115, 315, 90);

  Brain.Screen.drawLine(420, 90, 450, 90);
  Brain.Screen.drawLine(450, 90, 420, 150);
  wait(4, sec);
  Brain.Screen.clearScreen();
  DriveMode = 1;
}

void AutonSelectorArt(){
 Brain.Screen.setFillColor(blue);
 Brain.Screen.setPenColor(green);
 Brain.Screen.setPenWidth(4);
 Brain.Screen.drawRectangle(20, 20, 170, 60);
 Brain.Screen.drawRectangle(20, 160, 170, 60);
 Brain.Screen.setFillColor(red);
 Brain.Screen.setPenColor(orange);
 Brain.Screen.drawRectangle(290, 20, 170, 60);
 Brain.Screen.drawRectangle(290, 160, 170, 60);
 Brain.Screen.setPenColor(black);
 Brain.Screen.setFillColor(blue);
 Brain.Screen.printAt(35, 58, "");
 Brain.Screen.printAt(27, 197, "");
 Brain.Screen.setFillColor(red);
 Brain.Screen.printAt(305, 58, "");
 Brain.Screen.printAt(297, 197, "");

}

void SelectAuton(){
 while(AutonomousMode == 0){
    if(Brain.Screen.xPosition() > 20 && Brain.Screen.xPosition() < 170)
    {
      if(Brain.Screen.yPosition() > 20 && Brain.Screen.yPosition() < 80){
      AutonomousMode = 1;
      Brain.Screen.clearScreen();
      Brain.Screen.print("Blue protected zone autonomous selected.");
      }

      if(Brain.Screen.yPosition() > 160 && Brain.Screen.yPosition() < 220){
      AutonomousMode = 2;
      Brain.Screen.clearScreen();
      Brain.Screen.print("Blue unprotected zone autonomous selected.");
      }
    }
if(Brain.Screen.xPosition() > 290 && Brain.Screen.xPosition() < 350)
    {
      if(Brain.Screen.yPosition() > 20 && Brain.Screen.yPosition() < 80){
      AutonomousMode = 3;
      Brain.Screen.clearScreen();
      Brain.Screen.print("Red protected zone autonomous selected.");
      }

      if(Brain.Screen.yPosition() > 160 && Brain.Screen.yPosition() < 220){
      AutonomousMode = 4;
      Brain.Screen.clearScreen();
      Brain.Screen.print("Red unprotected zone autonomous selected.");
      }
    }
  }

}
