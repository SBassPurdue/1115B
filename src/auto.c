/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "auto.h"
#include "liftControl.h"

/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost, the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */
void autonomous() {

encoderReset(enRightLift);
encoderReset(enLeftLift);
lcdSetBacklight(uart1, 1);

int targLift = 320;

  while (encoderGet(enRightLift) < targLift || encoderGet(enLeftLift) < targLift) {
    delay(20);

    lcdPrint(uart1, 1, "enL: %d", encoderGet(enLeftLift));
    lcdPrint(uart1, 2, "enR: %d", encoderGet(enRightLift));

    if(encoderGet(enLeftLift) < targLift) {
      motorSet(2, 127);
    } else {motorStop(2);}
    if(encoderGet(enRightLift) < targLift) {
      motorSet(3, -127);
    } else {motorStop(3);}
  }

  forward(55);

  targLift = 275;

  while (encoderGet(enRightLift) < targLift || encoderGet(enLeftLift) < targLift) {
    delay(20);

    lcdPrint(uart1, 1, "enL: %d", encoderGet(enLeftLift));
    lcdPrint(uart1, 2, "enR: %d", encoderGet(enRightLift));

    if(encoderGet(enLeftLift) > targLift) {
      motorSet(2, -127);
    } else {motorStop(2);}
    if(encoderGet(enRightLift) > targLift) {
      motorSet(3, 127);
    } else {motorStop(3);}
  }

  extake(1000);

  back(25);

/*while (lift(2, enRightLift, 65) || lift(3, enLeftLift, 65)) {}
while (moveTo(5, enLeftDrive, 48.3) || moveTo(7, enLeftDrive, 48.3) || moveTo(4, enRightDrive, 48.3) || moveTo(6, enRightDrive, 48.3)) {}*/
}
