/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Aidan Frye                                       */
/*    Created:      Wed Sep 02 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "functionsAndMotors.h"

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  DriveMode = 1;
  while(1)
  {
    if(DriveMode==1){
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
    //^^ More Intake Code ^^
}
}
}