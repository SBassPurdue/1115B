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

  //Variable Declarations

  //int targetLeft = 0;
  //int targetRight = 0;
  int targetLift = 0;
  //int leftFrontSpeed = 0;
  //int leftBackSpeed = 0;
  //int rightBackSpeed = 0;
  //int rightFrontSpeed = 0;

  //Main Loop (Utilizing Encoders)

goto noEncoder;

  while (0 == 0) {
    Encoder:

    //targetLift = targetLift - (joystickGetDigital(1, 6, JOY_UP)-joystickGetDigital(1, 6, JOY_DOWN));
    //targetLeft = targetLeft + (0.1 * joystickGetAnalog(1, 2));
    //targetRight = targetRight + (0.1 * joystickGetAnalog(1, 3));

    //Drive Control

    motorSet(5, joystickGetAnalog(1, 3)); //Drive Left Back
    motorSet(7, joystickGetAnalog(1, 3)); //Drive Left Front
    motorSet(4, -joystickGetAnalog(1, 2)); //Drive Right Back
    motorSet(6, -joystickGetAnalog(1, 2)); //Drive Right Front

    //Lift Control

    if (abs(encoderGet(enLeftLift) - encoderGet(enRightLift)) >= 5) {
      motorSet(2, repos(encoderGet(enRightDrive), encoderGet(enLeftDrive), 127));
    }

    motorSet(3, 127*(joystickGetDigital(1, 6, JOY_UP)-joystickGetDigital(1, 6, JOY_DOWN))); //Lift Left
    motorSet(2, 127*(joystickGetDigital(1, 6, JOY_UP)-joystickGetDigital(1, 6, JOY_DOWN))); //Lift Right

    //Intakes Control

    motorSet(1, 100*(joystickGetDigital(1, 5, JOY_UP)-joystickGetDigital(1, 5, JOY_DOWN))); //Claw
    motorSet(8, -127*(joystickGetDigital(1, 8, JOY_UP)-joystickGetDigital(1, 8, JOY_DOWN))); //Mobile Intake 1
    motorSet(9, 127*(joystickGetDigital(1, 8, JOY_UP)-joystickGetDigital(1, 8, JOY_DOWN))); //Mobile Intake 2

    //printf("LD = %d, RD = %d, TL = %d, TR = %d, LL = %d, LR = %d, TL = %d\n", encoderGet(enLeftDrive), encoderGet(enRightDrive), targetLeft, targetRight, encoderGet(enLeftLift), encoderGet(enRightLift), targetLift);
    /*
    leftBackSpeed = repos(encoderGet(enLeftBack), targetLeft, 30);
    leftFrontSpeed = repos(encoderGet(enLeftFront), targetLeft, 30);
    rightBackSpeed = repos(encoderGet(enRightBack), targetRight, 30);
    rightFrontSpeed = repos(encoderGet(enRightFront), targetRight, 30);

    motorSet(2, leftBackSpeed); //Drive Left Back
    motorSet(3, rightBackSpeed); //Drive Right Back
    motorSet(5, leftFrontSpeed); //Drive Left Front
    motorSet(4, rightFrontSpeed); //Drive Right Front
    */

    //Forebar Control

    motorSet(10, 127*(joystickGetDigital(1, 5, JOY_UP)-joystickGetDigital(1, 5, JOY_DOWN)));

    delay(20);

    if(joystickGetDigital(1, 7, JOY_LEFT) && joystickGetDigital(1, 7, JOY_RIGHT)) {
      autonomous(); //Call Autonomous (debugging)
    }

    //Swap to Encoder-Free Loop

    if(joystickGetDigital(1, 7, JOY_DOWN)) {
        goto noEncoder;
    }
  }

  //Main Loop (Encoder Independent)

  while(0 == 0) {
    noEncoder:



    motorSet(5, joystickGetAnalog(1, 3)); //Drive Left Back
    motorSet(7, joystickGetAnalog(1, 3)); //Drive Left Front
    motorSet(4, -joystickGetAnalog(1, 2)); //Drive Right Back
    motorSet(6, -joystickGetAnalog(1, 2)); //Drive Right Front

    //Lift Control

    motorSet(2, 127*(joystickGetDigital(1, 6, JOY_UP)-joystickGetDigital(1, 6, JOY_DOWN))); //Lift Left
    motorSet(3, -127*(joystickGetDigital(1, 6, JOY_UP)-joystickGetDigital(1, 6, JOY_DOWN))); //Lift Right

    //Forebar Control

    motorSet(10, 127*(joystickGetDigital(1, 5, JOY_UP)-joystickGetDigital(1, 5, JOY_DOWN)));

    //Intake Control

    motorSet(1, 127*(joystickGetDigital(1, 7, JOY_DOWN)-joystickGetDigital(1, 7, JOY_LEFT))); //Roller
    motorSet(8, -127*(joystickGetDigital(1, 8, JOY_UP)-joystickGetDigital(1, 8, JOY_DOWN))); //Mobile Intake 1
    motorSet(9, 127*(joystickGetDigital(1, 8, JOY_UP)-joystickGetDigital(1, 8, JOY_DOWN))); //Mobile Intake 2

    delay(20);

    //Call Autonomous, Good for Debugging

    if(joystickGetDigital(1, 7, JOY_UP) && joystickGetDigital(1, 7, JOY_RIGHT)) {
      autonomous();
    }

    //Swap to Encoder-Based Loop


    if(joystickGetDigital(1, 7, JOY_UP)) {
        encoderReset(enLeftDrive);
        encoderReset(enRightDrive);
        encoderReset(enLeftLift);
        encoderReset(enRightLift);
        //targetLeft = 0;
        //targetRight = 0;
        targetLift = 0;
        goto Encoder;
    }
  }
}
