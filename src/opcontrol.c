/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#include "PID.h"
#include "repos.h"
//#include "string.h"

//#include "1115APID.h"

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */

void operatorControl() {

  taskSuspend(lMgFbHandler);

  //Variable Declarations

  //bool lastOut = 0;
  //int targetLeft = 0;
  //int targetRight = 0;
  //int targetLift = 0;
  //int speedLiftPID = 25;
  //float speedLift = 20;
  signed char joy = 0;
  int liftC = 0;
  int liftCL = 0;
  int liftCR = 0;
  int liftDiff = 0;
  int forebar = 0;
  int calc = 0;
  //char name[15];

  encoderReset(enLeftLift);
  encoderReset(enRightLift);

  //int leftFrontSpeed = 0;
  //int leftBackSpeed = 0;
  //int rightBackSpeed = 0;
  //int rightFrontSpeed = 0;
  int t = 0; //Timer
  int i = 0;

  //Main Loop
while (0 == 0) {
  i = i + 20;
  if (i < 200 || isJoystickConnected(2)) {
    if (isJoystickConnected(2)) {
      i = 0;
    }

    motorSet(5, joystickGetAnalog(1, 3)); //Drive Left Back
    motorSet(7, joystickGetAnalog(1, 3)); //Drive Left Front
    motorSet(4, -joystickGetAnalog(1, 2)); //Drive Right Back
    motorSet(6, -joystickGetAnalog(1, 2)); //Drive Right Front

    liftDiff = encoderGet(enLeftLift) + encoderGet(enRightLift);
    liftC = repos(liftDiff, 0, 10);
    if (abs(liftC) < 15) {
      liftC = 0;
    }
    liftC = 127*(joystickGetDigital(1, 6, JOY_UP)-joystickGetDigital(1, 6, JOY_DOWN));
    liftC = liftC + joystickGetAnalog(2, 3);
    joy = joystickGetAnalog(2, 4);
    if (abs(joy) > 50) {
      joy = 0.3 * joy;
      liftCL = liftC + joy;
      liftCR = liftC - joy;
      motorSet(2, -liftCL); //Lift Left
      motorSet(3, liftCR); //Lift Right
    } else {
      motorSet(2, -liftC); //Lift Left
      motorSet(3, liftC); //Lift Right
    }

    /*if (liftC < 10) {
      calc = 0.5*(encoderGet(enLeftLift) + encoderGet(enRightLift));
      motorSet(2, repos(encoderGet(enLeftLift), 0, 30));
      motorSet(3, -repos(encoderGet(enRightLift), 0, 30));
    }*/
    /*
    motorSet(2, joystickGetAnalog(2, 3));
    motorSet(3, -joystickGetAnalog(2, 3));
    */
    //Forebar Control

    //motorSet(10, 127*(joystickGetDigital(2, 5, JOY_UP)-joystickGetDigital(2, 5, JOY_DOWN)));
    motorSet(10, -joystickGetAnalog(2, 2));

    //Forebar Presets

    forebar = 0;
    if (joystickGetDigital(2, 8, JOY_DOWN)) {forebar = 1;} //Forebar Down
    if (joystickGetDigital(2, 8, JOY_RIGHT) || joystickGetDigital(2, 8, JOY_LEFT)) {forebar = 2;} //Forebar Out
    if (joystickGetDigital(2, 8, JOY_UP)) {forebar = 3;} //Forebar Up

    if (forebar == 1) {motorSet(10, repos(analogRead(1), fbrDown, 30));} //Forebar Down
    if (forebar == 2) {motorSet(10, repos(analogRead(1), fbrOut, 15));} //Forebar Out
    if (forebar == 3) {motorSet(10, repos(analogRead(1), fbrUp, 30));} //Forebar Up

    //Intake Control

    t = t + 20;


    if (joystickGetDigital(1, 5, JOY_DOWN) || joystickGetDigital(2, 6, JOY_UP)) { //Roller
      motorSet(1, -80); //Intake
      t = 0;
      //lastOut = 0;
    } else if (joystickGetDigital(1, 5, JOY_UP) || joystickGetDigital(2, 6, JOY_DOWN)) {
      motorSet(1, 127); //Extake
      t = 0;
      //lastOut = 1;
    } else if (t > 500) {
          motorSet(1, -15);
          t = 0;
    }

    motorSet(8, -127*(joystickGetDigital(2, 7, JOY_UP)-joystickGetDigital(2, 7, JOY_DOWN))); //Mobile Intake 1
    motorSet(9, 127*(joystickGetDigital(2, 7, JOY_UP)-joystickGetDigital(2, 7, JOY_DOWN))); //Mobile Intake 2

    //lcdPrint(uart1, 1, "Gyro: %d", gyroGet(gyro));
    //lcdPrint(uart1, 1, "Joy2: %d", isJoystickConnected(2));
    //lcdPrint(uart1, 2, "Ptmr: %d", analogRead(1));
    //lcdPrint(uart1, 2, "i: %d", i);

    delay(20);

    //Call Autonomous, Good for Debugging

    if(joystickGetDigital(1, 7, JOY_UP) && joystickGetDigital(1, 7, JOY_RIGHT)) {
      autonomous();
    }
  }
  if (isJoystickConnected(2) != 1 && i > 200) {
  if (isJoystickConnected(2)) {
    i = 0;
  }

    motorSet(5, joystickGetAnalog(1, 3)); //Drive Left Back
    motorSet(7, joystickGetAnalog(1, 3)); //Drive Left Front
    motorSet(4, -joystickGetAnalog(1, 2)); //Drive Right Back
    motorSet(6, -joystickGetAnalog(1, 2)); //Drive Right Front

    //Lift Control

    /*targetLift = targetLift + speedLift * (joystickGetDigital(1, 6, JOY_UP)-joystickGetDigital(1, 6, JOY_DOWN));

    if (targetLift > 720) {
      targetLift = 720;
    } else if (targetLift < -30) {
      targetLift = -30;
    }*/

    /*
    motorSet(2, repos2(encoderGet(enLeftLift), targetLift, 0, 0.5));
    motorSet(3, -repos2(encoderGet(enRightLift), targetLift, 0, 0.5));
    */
    /*
    motorSet(2, repos(-encoderGet(enLeftLift), targetLift, 30)); //Lift Left
    motorSet(3, -repos(encoderGet(enRightLift), targetLift, 30)); //Lift Right
    */

    motorSet(2, -127*(joystickGetDigital(1, 6, JOY_UP)-joystickGetDigital(1, 6, JOY_DOWN))); //Lift Left
    motorSet(3, 127*(joystickGetDigital(1, 6, JOY_UP)-joystickGetDigital(1, 6, JOY_DOWN))); //Lift Right


    //Forebar Control

    motorSet(10, -127*(joystickGetDigital(1, 5, JOY_UP)-joystickGetDigital(1, 5, JOY_DOWN)));

    //Intake Control


    t = t + 20;

    if (joystickGetDigital(1, 7, JOY_DOWN)) {
      motorSet(1, -80); //Intake
      t = 0;
      //lastOut = 0;
    } else if (joystickGetDigital(1, 7, JOY_UP)) {
      motorSet(1, 127); //Extake
      //lastOut = 1;
      t = 0;
    } else if (t > 500) {
          motorSet(1, -15);
          t = 0;
    }
    motorSet(8, 127*(joystickGetDigital(1, 8, JOY_DOWN)-joystickGetDigital(1, 8, JOY_RIGHT))); //Mobile Intake 1
    motorSet(9, -127*(joystickGetDigital(1, 8, JOY_DOWN)-joystickGetDigital(1, 8, JOY_RIGHT))); //Mobile Intake 2

    //lcdPrint(uart1, 1, "Spd: %f", getSpeed(enLeftDrive));
    //lcdPrint(uart1, 1, "Joy2: %d", isJoystickConnected(2));
    //lcdPrint(uart1, 2, "Ptmr: %d", analogRead(1));
    //lcdPrint(uart1, 2, "i: %d", i);
    //lcdPrint(uart1, 2, "L:%d R:%d", repos2(encoderGet(enLeftLift), targetLift, getSpeed(enLeftLift), 1), repos2(encoderGet(enRightLift), targetLift, getSpeed(enRightLift), 1));

    delay(20);

    //Call Autonomous, Good for Debugging

    if(joystickGetDigital(1, 7, JOY_UP) && joystickGetDigital(1, 7, JOY_RIGHT)) {
      autonomous();
    }
  }
  if(joystickGetDigital(1, 7, JOY_UP)) {
    taskSuspend(lMgFbHandler);
  }
}
}
