/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LMotor               motor         10              
// RMotor               motor         4               
// Arm                  motor         13              
// Claw                 motor         16              
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
void v_Set(){ // Function created to set initial velocity of robot!
  LMotor.setVelocity(50, percent); // Left motor speed!
  RMotor.setVelocity(50, percent); // Right motor speed!
  Arm.setVelocity(40, percent); // Arm speed!
  Claw.setVelocity(50, percent); // Claw speed!
}
void autonomous(void) {
  v_Set(); // Sets velocity of robot's main motors!
  wait(1, seconds); // Stops all motor function for net time of 1 second!
  LMotor.spinFor(forward, 360, degrees, false); // (L) Moves drivetrain forward!
  RMotor.spinFor(forward, 360, degrees, false); // (R) Moves drivetrain forward!
  wait(2, seconds); // Stops all motor function for net time of 2 seconds!
  Claw.spinFor(reverse, 145, degrees); // Closes claw
  wait(1, seconds); // Stops all motor function for net time of 1 second!
  Arm.spinFor(forward, 300, degrees); // Picks up claw!

  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

int deadband = 8;

void usercontrol(void) {
  
  // User control code here, inside the loop
  while (1) {

    if (Controller1.ButtonL1.pressing()){ //Checking to see if the L1 button on the controller is being pressed.
      Arm.spin(forward); 
    } else if (Controller1.ButtonL2.pressing()){
      Arm.spin(reverse); 
    } else {
      Arm.stop(hold);
    }
    /* if(Controller1.Axis3.position()){
       LMotor.spin(forward);
     }
     if(Controller1.Axis2.position()) {

    } */

    int leftMotorSpeed = Controller1.Axis3.position();
    int rightMotorSpeed = Controller1.Axis2.position();

    if (abs(leftMotorSpeed) > deadband) {
          LMotor.setVelocity(leftMotorSpeed, percent);
    } else {
          LMotor.setVelocity(0, percent);
    }

    if (abs(rightMotorSpeed) > deadband) {
            RMotor.setVelocity(rightMotorSpeed,percent);
    } else {
            RMotor.setVelocity(0, percent);
    }

    LMotor.spin(forward);
    RMotor.spin(forward);

    if (Controller1.ButtonR1.pressing()){
      Claw.spin(forward);
    } else if (Controller1.ButtonR2.pressing()){
      Claw.spin(reverse);
    } else {
      Claw.stop(hold);
    }
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  // Drivetrain.setDriveVelocity(drivespeed, percent);
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
