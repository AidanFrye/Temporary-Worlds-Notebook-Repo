/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\dougl                                            */
/*    Created:      Mon Apr 26 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// OpticalSensorTop     optical       7               
// OpticalSensor        optical       9               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "functionsAndMotors.h"

// PLACEMENT FOR AUTONS

// U HOME - intake on the goal, indent in connectors lined up w/ middle of V, straight as possible, indent non-visible
// R HOME - intake on the goal, indent in connectors lined up w/ top edge of V, straight as possible, indent barely visible 
// U TRIANGLE - intake axle touching the outside of goal, indent in connectors lined up w/ top edge of V, straight as possible, somewhat visible
// R TRIANGLE - intake axle touching the outside of goal, indent in connectors lined up w/ top edge of V, straight as possible, somewhat visible


using namespace vex;
float controlMode = 0;
float autonColor = 0; // 1 is blue, 2 is red
float autonMode = 0;
int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  vex::color background = vex::color(179, 132, 143);
  Brain.Screen.setFillColor(background);
  Brain.Screen.drawRectangle(0, 0, 480, 240);
  Brain.Screen.setFillColor(green);
  Brain.Screen.setPenColor(black);
  if(controlMode != 1){Brain.Screen.drawRectangle(20, 20, 150, 30);}
  if(controlMode !=2 ){Brain.Screen.drawRectangle(310, 20, 150, 30);}
  Brain.Screen.printAt(42, 40, "Autonomous");
  Brain.Screen.printAt(350, 40, "Driver");
  while(controlMode == 0)
  {
    if(Brain.Screen.yPosition() > 20 && Brain.Screen.yPosition() < 50)
    {
      if(Brain.Screen.xPosition() > 20 && Brain.Screen.xPosition() < 170)
      {
        controlMode = 1;
      }
      if(Brain.Screen.xPosition() > 310 && Brain.Screen.xPosition() < 460)
      {
        controlMode = 2;
        Brain.Screen.clearScreen();
        vex::color background = vex::color(179, 132, 143);
        Brain.Screen.setFillColor(background);
        Brain.Screen.drawRectangle(0, 0, 480, 240);
        Brain.Screen.setFillColor(green);
        Brain.Screen.drawRectangle(310, 20, 150, 30);
        Brain.Screen.printAt(350, 40, "Driver");
        Brain.Screen.printAt(30, 200, "Running Driver Control. Press A when ready.");
      }
    }

  }
  if(controlMode == 2)
  {
    waitUntil(Controller_Ruh.ButtonA.pressing() == true);
    while(1)
    {
    indexRed();
    indexBlue();
    if(Controller_Ruh.Axis3.position()> 0)
    {
      LeftSide.spin(fwd, Controller_Ruh.Axis3.position()*1.8, rpm);
    }
    else if(Controller_Ruh.Axis3.position()< 0)
    {
      LeftSide.spin(fwd, Controller_Ruh.Axis3.position()*1.8, rpm);
    }
    else{LeftSide.stop(coast);}
    // ^^ Left side tank ^^
   if(Controller_Ruh.Axis2.position()> 0)
    {
      RightSide.spin(fwd, Controller_Ruh.Axis2.position()*1.8, rpm);
    }
    else if(Controller_Ruh.Axis2.position()< 0)
    {
      RightSide.spin(fwd, Controller_Ruh.Axis2.position()*1.8, rpm);
    }
    else{RightSide.stop(coast);}
    //^^ Right side tank ^^

if(Controller_Ruh.Axis2.position()> 0 && Controller_Ruh.Axis3.position()< 0)
{
  RightSide.spin(fwd, Controller_Ruh.Axis2.position()*0.75, rpm);
  LeftSide.spin(fwd, Controller_Ruh.Axis3.position()*0.75, rpm);
}
if(Controller_Ruh.Axis2.position()< 0 && Controller_Ruh.Axis3.position()> 0)
{
  RightSide.spin(fwd, Controller_Ruh.Axis2.position()*0.75, rpm);
  LeftSide.spin(fwd, Controller_Ruh.Axis3.position()*0.75, rpm);
}
    if(Controller_Ruh.ButtonL2.pressing())
    {
      Intakes.spin(fwd, 105, rpm);
      BottomShooter.spin(fwd, 600, rpm);
      TopShooter.stop(hold);
    }
    else if(Controller_Ruh.ButtonL1.pressing())
    {
      Intakes.spin(fwd, -170, rpm);
      BottomShooter.spin(fwd, -300, rpm);
      TopShooter.stop(hold);
    }
  else if(Controller_Ruh.ButtonR2.pressing())
    {
      Intakes.spin(fwd, 105, rpm);
      BottomShooter.spin(fwd, 600, rpm);
      TopShooter.spin(fwd, 600, rpm);
    }
    else if(Controller_Ruh.ButtonR1.pressing())
    {
      Intakes.spin(fwd, -170, rpm);
      BottomShooter.spin(fwd, -300, rpm);
      TopShooter.spin(fwd, -300, rpm);
    }
    else if(Controller_Ruh.ButtonA.pressing())
    {
      TopShooter.spin(fwd, 600, rpm);
      BottomShooter.spin(fwd, 600, rpm);
    }
    else
    {
    LeftBallIntake.stop(coast);
    RightBallIntake.stop(coast);
    BottomShooter.stop(hold);
    TopShooter.stop(hold);
    }
    }
  }
  if(controlMode == 1)
  {
    Brain.Screen.drawRectangle(20, 60, 70, 30);
    Brain.Screen.drawRectangle(100, 60, 70, 30);
    Brain.Screen.printAt(40, 82, "Red");
    Brain.Screen.printAt(115, 82, "Blue");
    while(autonColor == 0)
    {
      if(Brain.Screen.yPosition() > 60 && Brain.Screen.yPosition() < 90)
    {
      if(Brain.Screen.xPosition() > 100 && Brain.Screen.xPosition() < 170)
      {
      autonColor = 1;
      Brain.Screen.clearScreen();
      vex::color background = vex::color(179, 132, 143);
      Brain.Screen.setFillColor(background);
      Brain.Screen.drawRectangle(0, 0, 480, 240);
      Brain.Screen.setFillColor(green);
      Brain.Screen.setPenColor(black);
      Brain.Screen.drawRectangle(20, 20, 150, 30);
      Brain.Screen.printAt(42, 40, "Autonomous");
      Brain.Screen.drawRectangle(100, 60, 70, 30);
      Brain.Screen.printAt(115, 82, "Blue");
      }
      if(Brain.Screen.xPosition() > 60 && Brain.Screen.xPosition() < 90)
      {
      autonColor = 2;
      Brain.Screen.clearScreen();
      vex::color background = vex::color(179, 132, 143);
      Brain.Screen.setFillColor(background);
      Brain.Screen.drawRectangle(0, 0, 480, 240);
      Brain.Screen.setFillColor(green);
      Brain.Screen.setPenColor(black);
      Brain.Screen.drawRectangle(20, 20, 150, 30);
      Brain.Screen.printAt(42, 40, "Autonomous");
      Brain.Screen.drawRectangle(20, 60, 70, 30);
      Brain.Screen.printAt(40, 82, "Red");
      }
    }
    }
    Brain.Screen.drawRectangle(20, 100, 70, 50);
    Brain.Screen.drawRectangle(100, 100, 70, 50);
    Brain.Screen.printAt(35, 122, "Home");
    Brain.Screen.printAt(40, 142, "Row");
    Brain.Screen.printAt(105, 122, "2 Home");
    Brain.Screen.printAt(105, 142, "1 Mid");
    while(autonMode == 0)
  {
    if(Brain.Screen.yPosition() > 100 && Brain.Screen.yPosition() < 150)
    {
      if(Brain.Screen.xPosition() > 20 && Brain.Screen.xPosition() < 90)
      {
        autonMode = 1;
        if(autonColor == 1)
        {
      Brain.Screen.clearScreen();
      vex::color background = vex::color(179, 132, 143);
      Brain.Screen.setFillColor(background);
      Brain.Screen.drawRectangle(0, 0, 480, 240);
      Brain.Screen.setFillColor(green);
      Brain.Screen.setPenColor(black);
      Brain.Screen.drawRectangle(20, 20, 150, 30);
      Brain.Screen.printAt(42, 40, "Autonomous");
      Brain.Screen.drawRectangle(100, 60, 70, 30);
      Brain.Screen.printAt(115, 82, "Blue");
      Brain.Screen.drawRectangle(20, 100, 70, 50);
      Brain.Screen.printAt(35, 122, "Home");
      Brain.Screen.printAt(40, 142, "Row");
        }
        if(autonColor == 2)
        {
      Brain.Screen.clearScreen();
      vex::color background = vex::color(179, 132, 143);
      Brain.Screen.setFillColor(background);
      Brain.Screen.drawRectangle(0, 0, 480, 240);
      Brain.Screen.setFillColor(green);
      Brain.Screen.setPenColor(black);
      Brain.Screen.drawRectangle(20, 20, 150, 30);
      Brain.Screen.printAt(42, 40, "Autonomous");
      Brain.Screen.drawRectangle(20, 60, 70, 30);
      Brain.Screen.printAt(40, 82, "Red");
      Brain.Screen.drawRectangle(20, 100, 70, 50);
      Brain.Screen.printAt(35, 122, "Home");
      Brain.Screen.printAt(40, 142, "Row");
        }
      }
      if(Brain.Screen.xPosition() > 100 && Brain.Screen.xPosition() < 170)
      {
        if(autonColor == 1)
        {
      autonMode = 2;
      Brain.Screen.clearScreen();
      vex::color background = vex::color(179, 132, 143);
      Brain.Screen.setFillColor(background);
      Brain.Screen.drawRectangle(0, 0, 480, 240);
      Brain.Screen.setFillColor(green);
      Brain.Screen.setPenColor(black);
      Brain.Screen.drawRectangle(20, 20, 150, 30);
      Brain.Screen.printAt(42, 40, "Autonomous");
      Brain.Screen.drawRectangle(100, 60, 70, 30);
      Brain.Screen.printAt(115, 82, "Blue");
      Brain.Screen.drawRectangle(100, 100, 70, 50);
      Brain.Screen.printAt(105, 122, "2 Home");
      Brain.Screen.printAt(105, 142, "1 Mid");
        }
        if(autonColor == 2)
        {
      autonMode = 2;
      Brain.Screen.clearScreen();
      vex::color background = vex::color(179, 132, 143);
      Brain.Screen.setFillColor(background);
      Brain.Screen.drawRectangle(0, 0, 480, 240);
      Brain.Screen.setFillColor(green);
      Brain.Screen.setPenColor(black);
      Brain.Screen.drawRectangle(20, 20, 150, 30);
      Brain.Screen.printAt(42, 40, "Autonomous");
      Brain.Screen.drawRectangle(20, 60, 70, 30);
      Brain.Screen.printAt(40, 82, "Red");
      Brain.Screen.drawRectangle(100, 100, 70, 50);
      Brain.Screen.printAt(105, 122, "2 Home");
      Brain.Screen.printAt(105, 142, "1 Mid");
      }   
      }

    }

  }
    if(autonColor == 1)
    {
      if(autonMode == 1)
      {
      Brain.Screen.printAt(50, 200, "Running blue home row. Press A when ready.");
      waitUntil(Controller_Ruh.ButtonA.pressing() == true);
      DriveBase.spin(fwd, -25, rpm);
      wait(0.4, sec);
      DriveBase.stop(hold);
      DriveBase.resetRotation();
      indexBlue();
      indexRed();
      Shooters.spin(fwd, 600, rpm);
      waitUntil(OpticalSensorTop.isNearObject()==true);
      wait(0.3, sec);
      Shooters.stop(hold);
      DriveBase.spin(fwd, -130, rpm);
      waitUntil(LeftTop.rotation(turns) < -2.74);
      DriveBase.stop(hold);
      wait(0.3, sec);
      DriveBase.resetRotation();
      turnRight(0.668);
      wait(0.35, sec);
      DriveBase.resetRotation();
      Intakes.spin(fwd, 600, rpm); 
      PIDForward(12);
      Shooters.spin(fwd, 600, rpm);
      DriveBase.spin(fwd, 40, rpm);
      Intakes.stop(hold);
      waitUntil(OpticalSensorTop.isNearObject()==true);
      wait(0.3, sec);
      Intakes.stop(hold);
      wait(0.2, sec);
      DriveBase.stop(hold);
      Shooters.stop(hold);
      DriveBase.resetRotation();
      DriveBase.spin(fwd, -120, rpm);
      waitUntil(LeftTop.rotation(turns) < -1.3895);
      DriveBase.stop(hold);
      wait(0.2, sec);
      turnLeft(0.84);
      wait(0.3, sec);
      PIDForward(68);
      wait(0.3, sec);
      turnRight(0.45);
      DriveBase.spin(fwd, 50, rpm);
      Intakes.spin(fwd, 600, rpm);
      Shooters.spin(fwd, 600, rpm);
      waitUntil(OpticalSensor.isNearObject()==true);
      Intakes.stop(hold);
      waitUntil(OpticalSensorTop.isNearObject()==true);
      wait(0.2, sec);
      DriveBase.spin(fwd, -50, rpm);
      wait(1, sec);
      DriveBase.stop(hold);
      Shooters.stop(hold);
      }
      if(autonMode == 2)
      {
        Brain.Screen.printAt(50, 200, "Running blue triangle. Press A when ready.");
        waitUntil(Controller_Ruh.ButtonA.pressing() == true);
        DriveBase.resetRotation();
        DriveBase.spin(fwd, -20, rpm);
        wait(0.5, sec);
        DriveBase.stop(hold);
        Shooters.spin(fwd, 600, rpm);
        waitUntil(OpticalSensorTop.isNearObject()==true);
        wait(0.2, sec);
        Shooters.stop(hold);
        DriveBase.spin(fwd, -130, rpm);
        waitUntil(LeftTop.rotation(turns) < -2.74);
        DriveBase.stop(hold);
        wait(0.2, sec);
        DriveBase.resetRotation();
        turnRight(0.675);
        wait(0.25, sec);
        DriveBase.resetRotation();
        Intakes.spin(fwd, 600, rpm); 
        PIDForward(11);
        Shooters.spin(fwd, 600, rpm);
        DriveBase.spin(fwd, 10, rpm);
        Intakes.stop(hold);
        waitUntil(OpticalSensorTop.isNearObject()==true);
        wait(0.2, sec);
        Intakes.stop(hold);
        wait(0.2, sec);
        DriveBase.stop(hold);
        Shooters.stop(hold);
        DriveBase.spin(fwd, -125, rpm);
        waitUntil(LeftTop.rotation(turns) < -2.837);
        DriveBase.stop(hold);
        wait(0.4, sec);
        DriveBase.resetRotation();
        RightSide.spin(fwd, -70, rpm);
        waitUntil(RightTop.rotation(turns) < -1.3);
        DriveBase.stop(hold);
      }
    }
    if(autonColor == 2)
    {
      if(autonMode == 1)
      {
        Brain.Screen.printAt(50, 200, "Running red home row. Press A when ready.");
        waitUntil(Controller_Ruh.ButtonA.pressing() == true);
        DriveBase.spin(fwd, -25, rpm);
        wait(0.4, sec);
        DriveBase.stop(hold);
        DriveBase.resetRotation();
        indexBlue();
        indexRed();
        Shooters.spin(fwd, 600, rpm);
        waitUntil(OpticalSensorTop.isNearObject()==true);
        wait(0.3, sec);
        Shooters.stop(hold);
        DriveBase.spin(fwd, -130, rpm);
        waitUntil(LeftTop.rotation(turns) < -2.81);
        DriveBase.stop(hold);
        wait(0.3, sec);
        DriveBase.resetRotation();
        turnRight(0.665);
        wait(0.35, sec);
        DriveBase.resetRotation();
        Intakes.spin(fwd, 600, rpm); 
        PIDForward(12);
        Shooters.spin(fwd, 600, rpm);
        DriveBase.spin(fwd, 40, rpm);
        Intakes.stop(hold);
        waitUntil(OpticalSensorTop.isNearObject()==true);
        wait(0.3, sec);
        Intakes.stop(hold);
        wait(0.2, sec);
        DriveBase.stop(hold);
        Shooters.stop(hold);
        DriveBase.resetRotation();
        DriveBase.spin(fwd, -120, rpm);
        waitUntil(LeftTop.rotation(turns) < -1.3);
        DriveBase.stop(hold);
        wait(0.2, sec);
        turnLeft(0.83);
        wait(0.3, sec);
        PIDForward(68);
        wait(0.3, sec);
        turnRight(0.4);
        DriveBase.spin(fwd, 50, rpm);
        Intakes.spin(fwd, 600, rpm);
        Shooters.spin(fwd, 600, rpm);
        waitUntil(OpticalSensor.isNearObject()==true);
        Intakes.stop(hold);
        waitUntil(OpticalSensorTop.isNearObject()==true);
        wait(0.2, sec);
        DriveBase.spin(fwd, -50, rpm);
        wait(1, sec);
        DriveBase.stop(hold);
        Shooters.stop(hold);
      }
      if(autonMode == 2)
      {
        Brain.Screen.printAt(50, 200, "Running red triangle. Press A when ready.");
        waitUntil(Controller_Ruh.ButtonA.pressing() == true);
        DriveBase.resetRotation();
        DriveBase.spin(fwd, -20, rpm);
        wait(0.5, sec);
        DriveBase.stop(hold);
        Shooters.spin(fwd, 600, rpm);
        waitUntil(OpticalSensorTop.isNearObject()==true);
        wait(0.2, sec);
        Shooters.stop(hold);
        DriveBase.spin(fwd, -130, rpm);
        waitUntil(LeftTop.rotation(turns) < -2.74);
        DriveBase.stop(hold);
        wait(0.2, sec);
        DriveBase.resetRotation();
        turnRight(0.675);
        wait(0.25, sec);
        DriveBase.resetRotation();
        Intakes.spin(fwd, 600, rpm); 
        PIDForward(11);
        Shooters.spin(fwd, 600, rpm);
        DriveBase.spin(fwd, 10, rpm);
        Intakes.stop(hold);
        waitUntil(OpticalSensorTop.isNearObject()==true);
        wait(0.2, sec);
        Intakes.stop(hold);
        wait(0.2, sec);
        DriveBase.stop(hold);
        Shooters.stop(hold);
        DriveBase.spin(fwd, -125, rpm);
        waitUntil(LeftTop.rotation(turns) < -2.837);
        DriveBase.stop(hold);
        wait(0.4, sec);
        DriveBase.resetRotation();
        RightSide.spin(fwd, -70, rpm);
        waitUntil(RightTop.rotation(turns) < -1.3);
        DriveBase.stop(hold);
      }
    }
  }
  
}