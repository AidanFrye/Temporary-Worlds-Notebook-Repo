/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\dougl                                            */
/*    Created:      Mon Feb 15 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// OpticalSensor        optical       9               
// OpticalSensorTop     optical       7               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "functionsAndMotors.h"
using namespace vex;
float autonomousMode = 4; //1 is left, 2 is right, from outside of field from color position, 3 is skills, 4 is home row
float colorMode = 1; //1 is blue, 2 is red

int main() {
  
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  indexRed();
  indexBlue();
  OpticalSensorTop.setLightPower(100, pct);
  OpticalSensor.setLightPower(100, pct);
  if(autonomousMode == 1){
  if(colorMode == 1){
  TopShooter.stop(hold);
  Intakes.spin(fwd, 400, rpm);
  BottomShooter.spin(fwd, 400, rpm);
  DriveBase.spin(fwd, 120, rpm);
  waitUntil(OpticalSensor.isNearObject() == true);
  LeftSide.stop(hold);
  wait(0.43, sec);
  TopShooter.spin(fwd, 600, rpm);
  waitUntil(OpticalSensor.isNearObject() == true && OpticalSensor.hue() > 10 && OpticalSensor.hue() < 40);
  Shooters.stop(hold);
  Intakes.stop(hold);
  DriveBase.stop(coast);
  wait(0.3 , sec);
  TopShooter.spin(fwd, -50, rpm);
  DriveBase.resetRotation();
  DriveBase.spin(fwd, -120, rpm);
  waitUntil(LeftTop.rotation(turns) < -2);
  TopShooter.stop(hold);
  DriveBase.stop(hold);
  DriveBase.resetRotation();
  turnLeft(0.818);
  DriveBase.resetRotation();
  wait(0.2, sec);
  PIDForward(26);
  wait(0.5, sec);
  DriveBase.resetPosition();
  turnRight(0.52);
  DriveBase.spin(fwd, 130, rpm);
  wait(0.8, sec);
  DriveBase.stop(coast);
  Shooters.spin(fwd, 600, rpm);
  waitUntil(OpticalSensorTop.isNearObject()==true);
  waitUntil(OpticalSensorTop.isNearObject()==false);
  wait(0.1, sec);
  Shooters.stop(hold);
  Shooters.spin(fwd, -600, rpm);
  Intakes.spin(fwd, -200, rpm);
  DriveBase.resetRotation();
  DriveBase.spin(fwd, -100, rpm);
  waitUntil(LeftTop.rotation(turns) < -1);
  wait(0.2, sec);
  DriveBase.stop(hold);
  DriveBase.resetPosition();
  turnLeft(0.52);
  wait(0.3, sec);
  Shooters.stop(hold);
  Intakes.stop(hold);
  PIDForward(31);
  DriveBase.resetPosition();
  turnRight(0.35);
  Intakes.spin(fwd, 200, rpm);
  Shooters.spin(fwd, 600, rpm);
  DriveBase.spin(fwd, 150, rpm);
  waitUntil(OpticalSensor.isNearObject() == true);
  DriveBase.stop(hold);
  Intakes.stop(hold);
  Shooters.stop(hold);
  }
    if(colorMode == 2)
    {
  DriveBase.spin(fwd, -80, rpm);
  wait(0.5, sec);
  DriveBase.stop(hold);
  wait(0.5, sec);
  DriveBase.spin(fwd, 80, rpm);  
  Intakes.spin(fwd, 600, rpm);
  wait(0.9, sec);
  DriveBase.spin(fwd, 105, rpm);
  LeftSide.spin(fwd, 20, rpm);
  Intakes.stop(hold);
  wait(0.35, sec);
  LeftSide.spin(fwd, 95, rpm);
  wait(0.15, sec);
  DriveBase.stop(hold);
  Shooters.spin(fwd, 450, rpm);
  wait(1, sec);
  Intakes.spin(fwd, 200, rpm);
  wait(0.5, sec);
  waitUntil(OpticalSensorTop.isNearObject() == true);
  waitUntil(OpticalSensorTop.isNearObject() == false);
  TopShooter.stop(hold);
  waitUntil(OpticalSensor.isNearObject() == true && OpticalSensor.hue() > 100 && OpticalSensor.hue() < 185);
  Shooters.stop(hold);
  Intakes.stop(hold);
  Intakes.spin(fwd, -60, rpm);
  DriveBase.spin(fwd, -40, rpm);
  wait(0.5, sec);
  Intakes.stop(hold);
  DriveBase.spin(fwd, -130, rpm);
  wait(0.7, sec);
  DriveBase.stop(hold);
  LeftSide.spin(fwd, -60, rpm);
  RightSide.spin(fwd, 60, rpm);
  DriveBase.resetPosition();
  turnLeft(1.82);
  DriveBase.stop(hold);
  wait(0.5, sec);
  PIDForward(40);
  TopShooter.spin(fwd, 600, rpm);
  wait(0.4, sec);
  LeftSide.spin(fwd, 90, rpm);
  RightSide.spin(fwd, -90, rpm);
  wait(1.08, sec);
  DriveBase.stop(hold);
  DriveBase.spin(fwd, 125, rpm);
  Intakes.spin(fwd, 300, rpm);
  Shooters.spin(fwd, 450, rpm);
  wait(0.55, sec);
  DriveBase.stop(hold);
  waitUntil((OpticalSensor.isNearObject()==true) && OpticalSensor.hue() > 0 && OpticalSensor.hue() < 40);
  Intakes.stop(hold);
  BottomShooter.stop(hold);
  DriveBase.spin(fwd, -200, rpm);
  wait(0.6, sec);
  Shooters.stop(hold);
  DriveBase.stop(coast);
}
  }
if(autonomousMode == 2){
  if(colorMode == 1){
  Inertial.calibrate();
  while(Inertial.isCalibrating()){}
  DriveBase.spin(fwd, -80, rpm);
  wait(0.5, sec);
  DriveBase.stop(hold);
  wait(0.5, sec);
  DriveBase.spin(fwd, 80, rpm);  
  Intakes.spin(fwd, 600, rpm);
  wait(0.9, sec);
  DriveBase.spin(fwd, 105, rpm);
  RightSide.spin(fwd, 20, rpm);
  Intakes.stop(hold);
  wait(0.4, sec);
  RightSide.spin(fwd, 95, rpm);
  wait(0.2, sec);
  DriveBase.stop(hold);
  Shooters.spin(fwd, 600, rpm);
  wait(1, sec);
  Intakes.spin(fwd, 200, rpm);
  waitUntil(OpticalSensorTop.isNearObject() == true);
  waitUntil(OpticalSensorTop.isNearObject() == false);
  TopShooter.stop(hold);
  waitUntil(OpticalSensor.isNearObject() == true && OpticalSensor.hue() > 100 && OpticalSensor.hue() < 255);
  Shooters.stop(hold);
  Intakes.stop(hold);
  Intakes.spin(fwd, -60, rpm);
  DriveBase.spin(fwd, -40, rpm);
  wait(0.5, sec);
  Intakes.stop(hold);
  DriveBase.spin(fwd, -130, rpm);
  wait(0.5, sec);
  DriveBase.stop(hold);
  RightSide.spin(fwd, -60, rpm);
  LeftSide.spin(fwd, 60, rpm);
  Shooters.stop(hold);
  turnRight(1.82);
  DriveBase.stop(hold);
  wait(0.3, sec);
  PIDForward(41);
  TopShooter.spin(fwd, 600, rpm);
  wait(0.4, sec);
  RightSide.spin(fwd, 90, rpm);
  LeftSide.spin(fwd, -90, rpm);
  wait(0.55, sec);
  DriveBase.stop(hold);
  DriveBase.spin(fwd, 130, rpm);
  Intakes.spin(fwd, 300, rpm);
  Shooters.spin(fwd, 450, rpm);
  wait(0.61, sec);
  DriveBase.stop(hold);
  waitUntil((OpticalSensor.isNearObject()==true) && OpticalSensor.hue() > 0 && OpticalSensor.hue() < 40);
  Intakes.stop(hold);
  BottomShooter.stop(hold);
  DriveBase.spin(fwd, -200, rpm);
  wait(0.6, sec);
  Shooters.stop(hold);
  DriveBase.stop(coast);
  }
  if(colorMode == 2)
  {
    Inertial.calibrate();
  while(Inertial.isCalibrating()){}
  DriveBase.spin(fwd, -80, rpm);
  wait(0.5, sec);
  DriveBase.stop(hold);
  wait(0.5, sec);
  DriveBase.spin(fwd, 80, rpm);  
  Intakes.spin(fwd, 600, rpm);
  wait(0.9, sec);
  DriveBase.spin(fwd, 105, rpm);
  RightSide.spin(fwd, 20, rpm);
  Intakes.stop(hold);
  wait(0.4, sec);
  RightSide.spin(fwd, 95, rpm);
  wait(0.2, sec);
  DriveBase.stop(hold);
  Shooters.spin(fwd, 600, rpm);
  wait(1, sec);
  Intakes.spin(fwd, 200, rpm);
  waitUntil(OpticalSensorTop.isNearObject() == true);
  waitUntil(OpticalSensorTop.isNearObject() == false);
  TopShooter.stop(hold);
  waitUntil(OpticalSensor.isNearObject() == true && OpticalSensor.hue() > 100 && OpticalSensor.hue() < 255);
  Shooters.stop(hold);
  Intakes.stop(hold);
  Intakes.spin(fwd, -60, rpm);
  DriveBase.spin(fwd, -40, rpm);
  wait(0.5, sec);
  Intakes.stop(hold);
  DriveBase.spin(fwd, -130, rpm);
  wait(0.5, sec);
  DriveBase.stop(hold);
  RightSide.spin(fwd, -60, rpm);
  LeftSide.spin(fwd, 60, rpm);
  Shooters.stop(hold);
  turnRight(1.82);
  DriveBase.stop(hold);
  wait(0.3, sec);
  PIDForward(41);
  TopShooter.spin(fwd, 600, rpm);
  wait(0.4, sec);
  RightSide.spin(fwd, 90, rpm);
  LeftSide.spin(fwd, -90, rpm);
  wait(0.55, sec);
  DriveBase.stop(hold);
  DriveBase.spin(fwd, 130, rpm);
  Intakes.spin(fwd, 300, rpm);
  Shooters.spin(fwd, 450, rpm);
  wait(0.61, sec);
  DriveBase.stop(hold);
  waitUntil((OpticalSensor.isNearObject()==true) && OpticalSensor.hue() > 0 && OpticalSensor.hue() < 40);
  Intakes.stop(hold);
  BottomShooter.stop(hold);
  DriveBase.spin(fwd, -200, rpm);
  wait(0.6, sec);
  Shooters.stop(hold);
  DriveBase.stop(coast);
  }
}
  if(autonomousMode == 3)
  {
  Intakes.spin(fwd, 600, rpm);
  BottomShooter.spin(fwd, 200, rpm);
  PIDForwardSlow(12);
  Intakes.stop(hold);
  BottomShooter.stop(hold);
  wait(0.2, sec);
  turnLeft(0.28);
  DriveBase.spin(fwd, -130, rpm);
  wait(1.35, sec);
  DriveBase.stop(coast);
  wait(0.2, sec);
  PIDForward(63.5);
  turnLeft(0.9);
  wait(0.2, sec);
  DriveBase.spin(fwd, 105, rpm);
  Shooters.spin(fwd, 600, rpm);
  waitUntil(OpticalSensorTop.isNearObject() == true);
  waitUntil(OpticalSensorTop.isNearObject() == false);
  Shooters.stop(hold);
  DriveBase.stop(coast);
  wait(0.2, sec);
  DriveBase.spin(fwd, -90, rpm);
  wait(0.63, sec);
  DriveBase.stop(hold);
  wait(0.2, sec);
  turnRight(0.815);
  wait(0.2, sec);
  Intakes.spin(fwd, 600, rpm);
  BottomShooter.spin(fwd, 400, rpm);
  PIDForward(53);
  Intakes.stop(hold);
  BottomShooter.stop(hold);
  turnLeft(0.38);
  PIDForward(10);
  Shooters.spin(fwd, 200, rpm);
  waitUntil(OpticalSensorTop.isNearObject() == true);
  DriveBase.stop(coast);
  waitUntil(OpticalSensorTop.isNearObject() == false);
  Shooters.stop(hold);
  DriveBase.spin(fwd, -140, rpm);
  wait(0.93, sec);
  DriveBase.stop(hold);
  wait(0.2, sec);
  turnRightSlower(1.27);
  wait(0.2, sec);
  DriveBase.spin(fwd, -130, rpm);
  wait(1.2, sec);
  DriveBase.stop(coast);
  wait(0.2, sec);
  Intakes.spin(fwd, 400, rpm);
  BottomShooter.spin(fwd, 600, rpm);
  PIDForward(70);
  Intakes.stop(hold);
  BottomShooter.stop(hold);
  wait(0.2, sec);
  DriveBase.resetPosition();
  DriveBase.spin(fwd, -60, rpm);
  waitUntil(LeftTop.rotation(turns) <= -0.55);
  turnLeft(0.845);
  wait(0.2, sec);
  DriveBase.spin(fwd, 60, rpm);
  wait(0.9, sec);
  DriveBase.stop(coast);
  Shooters.spin(fwd, 600, rpm);
  DriveBase.stop(coast);
  waitUntil(OpticalSensorTop.isNearObject() == true);
  waitUntil(OpticalSensorTop.isNearObject() == false);
  Shooters.stop(hold);
  DriveBase.spin(fwd, -90, rpm);
  wait(0.63, sec);
  DriveBase.stop(hold);
  wait(0.2, sec);
  turnRightSlower(1.65);
  wait(0.2, sec);
  Intakes.spin(fwd, 400, rpm);
  BottomShooter.spin(fwd, 600, rpm);
  PIDForward(30); //switch to 55 if going back to true middle after top middle
  Intakes.stop(hold);
  BottomShooter.stop(hold);
  turnLeftSlower(1.04);
  wait(0.2, sec);
  Intakes.spin(fwd, 600, rpm);
  PIDForward(50);
  Intakes.stop(hold);
  turnLeft(0.2);
  PIDForward(23.32);
  DriveBase.stop(coast);
  DriveBase.spin(fwd, 40, rpm);
  Shooters.spin(fwd, 150, rpm);
  waitUntil(OpticalSensorTop.isNearObject() == true);
  BottomShooter.stop(hold);
  waitUntil(OpticalSensorTop.isNearObject() == false);
  DriveBase.stop(coast);
  Shooters.stop(hold);
  DriveBase.resetPosition();
  DriveBase.spin(fwd, -105, rpm);
  waitUntil(LeftBottom.position(turns) < -1.65);
  DriveBase.stop(hold);
  turnRightSlower2(1.179);
  wait(0.3, sec);
  DriveBase.spin(fwd, -150, rpm);
  wait(1.1, sec);
  DriveBase.stop(coast);
  wait(0.3, sec);
  DriveBase.spin(fwd, 40, rpm);
  Intakes.spin(fwd, 600, rpm);
  wait(0.2, sec);
  BottomShooter.spin(fwd, 600, rpm);
  wait(0.2, sec);
  PIDForward(61); //back to 110 if switching back to 95
  Intakes.stop(hold);
  /*
  turnLeft(0.22);
  PIDForward(13);
  DriveBase.spin(fwd, 70, rpm);
  TopShooter.spin(fwd, 200, rpm);
  wait(0.1, sec);
  waitUntil(OpticalSensorTop.isNearObject() == true);
  waitUntil(OpticalSensorTop.isNearObject() == false);
  Shooters.stop(hold);
  wait(0.2,sec);
  DriveBase.stop(coast);
  wait(0.2, sec);
  DriveBase.resetPosition();
  DriveBase.spin(fwd, -140, rpm);
  waitUntil(LeftTop.position(turns) < -2.2);
  DriveBase.stop(hold);
  wait(0.2, sec);
  DriveBase.resetPosition();
  turnRightSlower(0.32);
  DriveBase.resetPosition();
  wait(0.4, sec);
  DriveBase.spin(fwd, -40, rpm);
  wait(0.5, sec);
  DriveBase.spin(fwd, -140, rpm);
  waitUntil(LeftTop.position(turns) < -3.66);
  DriveBase.stop(hold);
  */
  DriveBase.resetPosition();
  turnLeft(0.892);
  wait(0.4, sec);
  DriveBase.spin(fwd, 130, rpm);
  wait(0.5, sec);
  DriveBase.spin(fwd, 60, rpm);
  wait(0.2, sec);
  Shooters.spin(fwd, -600, rpm);
  wait(0.1, sec);
  Shooters.spin(fwd, 600, rpm);
  waitUntil(OpticalSensorTop.isNearObject() == true);
  BottomShooter.stop(hold);
  waitUntil(OpticalSensorTop.isNearObject() == false);
  wait(0.2, sec);
  DriveBase.stop(coast);
  Shooters.stop(hold);
  DriveBase.spin(fwd, -120, rpm);
  wait(0.6, sec);
  DriveBase.stop(hold);
  wait(0.3, sec);
  turnLeft(1.695);
  wait(0.2, sec);
  Intakes.spin(fwd, 600, rpm);
  BottomShooter.spin(fwd, 600, rpm);
  TopShooter.spin(fwd, 600, rpm);
  DriveBase.spin(fwd, 100, rpm);
  wait(0.4, sec);
  Intakes.spin(fwd, 600, rpm);
  BottomShooter.spin(fwd, 600, rpm);
  DriveBase.spin(fwd, 200, rpm);
  wait(1.5, sec);
  Intakes.spin(fwd, -600, rpm);
  DriveBase.stop();
  Shooters.spin(fwd, 600, rpm);
  wait(1.3, sec);
  DriveBase.spin(fwd, -130, rpm);
  wait(0.4, sec);
  DriveBase.spin(fwd, 100, rpm);
  Intakes.spin(fwd, -600, rpm);
  wait(0.8, sec);
  DriveBase.stop(coast);
  wait(0.88, sec);
  DriveBase.spin(fwd, 200, rpm);
  wait(1, sec);
  /*
  wait(0.2, sec);
  TopShooter.spin(fwd, 600, rpm);
  Intakes.spin(fwd, -600, rpm);
  DriveBase.stop(hold);
  wait(0.3, sec);
  DriveBase.spin(fwd, -40, rpm);
  wait(0.5, sec);
  DriveBase.spin(fwd, 40, rpm);
  LeftSide.spin(fwd, 70, rpm);
  wait(0.8, sec);
  DriveBase.spin(fwd, 100, rpm);
  wait(0.4, sec);
  DriveBase.stop(hold);
  Intakes.stop(hold);
  wait(0.5, sec);
  DriveBase.spin(fwd, -120, rpm);
  wait(0.6, sec);
  DriveBase.stop(hold);
  turnLeft(1.415);
  Shooters.stop(hold);
  BottomShooter.spin(fwd, 600, rpm);
  Intakes.spin(fwd, 400, rpm);
  PIDForward(52);
  Intakes.stop(hold);
  BottomShooter.stop(hold);
  wait(0.4, sec);
  DriveBase.resetRotation();
  DriveBase.spin(fwd, -100, rpm);
  waitUntil(LeftTop.rotation(turns) >= 3);
  DriveBase.stop(hold);
  wait(0.5, sec);
  turnRight(0.68);
  */
  }
  if(autonomousMode == 4)
  {
    indexBlue();
    indexRed();
    DriveBase.spin(fwd, 20, rpm);
    wait(0.5, sec);
    DriveBase.resetRotation();
    if(colorMode==1)
    {
    PIDForward(25.5);
    }
    else if (colorMode == 2)
    {
      PIDForward(26.6);
    }
    wait(0.2, sec);
    DriveBase.resetRotation();
    turnLeft(0.55);
    wait(0.2, sec);
    Intakes.spin(fwd, 400, rpm);
    Shooters.spin(fwd, 600, rpm);
    if(colorMode == 1)
    {
      PIDForward(13.1);
    }
    else if (colorMode == 2)
    {
      PIDForward(12.9);
    }
    DriveBase.spin(fwd, 7, rpm);
    waitUntil(OpticalSensorTop.isNearObject()==true);
    waitUntil(OpticalSensor.isNearObject()==true);
    DriveBase.stop(hold);
    wait(0.1, sec);
    waitUntil(OpticalSensorTop.isNearObject()==true);
    wait(0.1, sec);
    Intakes.spin(fwd, -200, rpm);
    TopShooter.stop(hold);
    wait(0.2, sec);
    Intakes.stop(hold);
    Shooters.stop(hold);
    DriveBase.resetRotation();
    DriveBase.spin(fwd, -80, rpm);
    waitUntil(LeftTop.rotation(turns) < -1.1);
    DriveBase.stop(hold);
    DriveBase.resetRotation();
    wait(0.2, sec);
    Shooters.spin(fwd, -600, rpm);
    Intakes.spin(fwd, -200, rpm);
    if(colorMode == 1)
    {
    turnLeft(0.79);
    }
    else if (colorMode == 2)
    {
      turnLeft(0.77);
    }
    Shooters.stop(hold);
    Intakes.stop(hold);
    wait(0.2, sec);
    DriveBase.resetRotation();
    PIDForward(64.5);
    DriveBase.resetRotation();
    turnRight(0.2);
    DriveBase.spin(fwd, 100, rpm);
    Intakes.spin(fwd, 400, rpm);
    Shooters.spin(fwd, 600, rpm);
    waitUntil(OpticalSensorTop.isNearObject()==true);
    waitUntil(OpticalSensor.isNearObject()==true);
    DriveBase.stop(hold);
    wait(0.1, sec);
    DriveBase.stop(coast);
    if(colorMode == 1)
    {
    waitUntil(OpticalSensor.isNearObject()==true && OpticalSensor.hue() > 0 && OpticalSensor.hue() < 40);
    }
    else if(colorMode == 2)
    {
    waitUntil(OpticalSensor.isNearObject()==true && OpticalSensor.hue() > 85 && OpticalSensor.hue() < 210);
    }
    Intakes.spin(fwd, -100, rpm);
    BottomShooter.stop(hold);
    DriveBase.spin(fwd, -50, rpm);
    wait(1, sec);
    DriveBase.stop(hold);
    TopShooter.stop(hold);
  };
}