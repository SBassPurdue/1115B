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

#include "API.h"
#include "liftControl.h"
#include "repos.h"
#include "main.h"

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

void getMobile(void) {

  motorSet(1, -15);
  forebarSet(fbrUp, 0);
  mobileMove(1800, 0);
  delay(350);

  forward3t(150, 1800);

  mobileMove(-1800, 0);
  delay(1400);
}

void Right22(void) {

  getMobile();

  forward3(-140);

  extake(100);

  rotate(45, 2);

  forward3(-65);

  rotate(90, 2);

  mobileMove(1000, 0);
  align(127);

  mobileMove(700, 0);
  delay(700);

  motorSet(4, 127);
  motorSet(6, 127);
  motorSet(5, -127);
  motorSet(7, -127);
  mobileMove(-500, 0);
  delay(1000);
  motorStop(4);
  motorStop(5);
  motorStop(6);
  motorStop(7);
}

void Right12(void) {

  getMobile();

  forward3(-140);

  extake(100);

  rotate(45, 2);

  forward3(-20);

  rotate(90, 2);

  mobileMove(1000, 0);
  align(40);

  mobileMove(700, 0);
  delay(700);

  motorSet(4, 127);
  motorSet(6, 127);
  motorSet(5, -127);
  motorSet(7, -127);
  mobileMove(-500, 0);
  delay(4000);
  motorStop(4);
  motorStop(5);
  motorStop(6);
  motorStop(7);
}

void Right7(void) {

  getMobile();

  forward3(-125);

  extake(100);

  rotate(-180, 2);

  mobileMove(1800, 0);
  delay(1800);

  forward3(-30);
}

void Left7(void) {

  getMobile();

  forward3(-125);

  extake(100);

  rotate(180, 2);

  mobileMove(1800, 0);
  delay(1800);

  forward3(-30);
}

void Left12(void) {

  getMobile();

  forward3(-140);

  extake(100);

  rotate(-45, 2);

  forward3(-10);

  rotate(-90, 2);

  mobileMove(1000, 0);
  align(40);

  mobileMove(700, 0);
  delay(700);

  motorSet(4, 127);
  motorSet(6, 127);
  motorSet(5, -127);
  motorSet(7, -127);
  mobileMove(-500, 0);
  delay(4000);
  motorStop(4);
  motorStop(5);
  motorStop(6);
  motorStop(7);
}

void Left22(void) {

  getMobile();

  forward3(-140);

  extake(100);

  rotate(-45, 2);

  forward3(-65);

  rotate(-90, 2);

  mobileMove(1000, 0);
  align(127);

  mobileMove(700, 0);
  delay(400);

  motorSet(4, 127);
  motorSet(6, 127);
  motorSet(5, -127);
  motorSet(7, -127);
  mobileMove(-500, 0);
  delay(1000);
  motorStop(4);
  motorStop(5);
  motorStop(6);
  motorStop(7);
}

void pylon(void) {

  encoderReset(enLeftLift);
  encoderReset(enRightLift);

  motorSet(1, -80);
  forebarSet(fbrUp, 0);
  lift(280, 0);

  delay(2000);

  motorSet(1, -15);
  forward3(55);

  lift(190, 0);
  delay(500);

  extake(400);

  lift(330, 0);
  extake(1600);

  forward3(-50);

  lift(80, 0);
}

void pylonL(void) {

  encoderReset(enLeftLift);
  encoderReset(enRightLift);

  pylon();

  forebarSet(fbrUp, 0);
  mobileMove(1400, 0);

  rotate(-90, 1.5);

  forward3(130);
}

void pylonR(void) {

  pylon();

  forebarSet(fbrUp, 0);
  mobileMove(1400, 0);

  rotate(90, 1.5);

  forward3(130);
}

void defense(void) {
  motorSet(5, 127); //Drive Left Back
  motorSet(7, 127); //Drive Left Front
  motorSet(4, -127); //Drive Right Back
  motorSet(6, -127); //Drive Right Front

  delay(1000);

  while (abs(getSpeed(enLeftDrive)) > 70) {
    motorSet(5, 127); //Drive Left Back
    motorSet(7, 127); //Drive Left Front
    motorSet(4, -127); //Drive Right Back
    motorSet(6, -127); //Drive Right Front
  }

motorStopAll();
}

void test(void) {

  forebarSet(fbrUp, 0);
  forward3(50);
  delay(250);
  forward3(-50);
  delay(250);
  forward3(50);
  delay(250);
  forward3(-50);

}

/*void redSkills(void) {
  forebarSet(fbrUp, 0);
  mobileMove(1400, 0);

  forward3(130);

  align(35);

  mobileMove(-1400, 0);

  delay(240);

  forward(-145);

  extake(100);

  rotate(-45, 1.5);

  forward(-45);

  rotate(-90, 1.5);

  mobileMove(700, 0);
  align(40);

  mobileMove(700, 0);
  delay(400);

  forward(-25);

  mobileMove(-200, 0);
  rotate(180, 1.5);

  mobileMove(250, 0);
  forward3(50);

  motorSet(4, -60);
  motorSet(6, -60);
  motorSet(5, 60);
  motorSet(7, 60);
  mobileMove(-1400, 0);
  delay(180);
  motorStop(4);
  motorStop(5);
  motorStop(6);
  motorStop(7);

  align(-35);

  forward(20);

  rotate(90, 1.5);

  forward(25);

  rotate(90, 1.5);

  mobileMove(700, 0);
  align(127);

  mobileMove(700, 0);
  delay(400);

  motorSet(4, 127);
  motorSet(6, 127);
  motorSet(5, -127);
  motorSet(7, -127);
  mobileMove(-500, 0);
  delay(900);
  motorStop(4);
  motorStop(5);
  motorStop(6);
  motorStop(7);

  rotate(-90, 1.5);

  forward(30);

  rotate(-90, 1.5);

  align(-40);

  mobileMove(450, 0);
  forward3(50);

  motorSet(4, -60);
  motorSet(6, -60);
  motorSet(5, 60);
  motorSet(7, 60);
  mobileMove(-1400, 0);
  delay(180);
  motorStop(4);
  motorStop(5);
  motorStop(6);
  motorStop(7);

  align(-40);

  forward(20);

  rotate(-180, 1.5);

  mobileMove(700, 0);
  align(40);

  mobileMove(700, 0);
  delay(400);

  motorSet(4, 127);
  motorSet(6, 127);
  motorSet(5, -127);
  motorSet(7, -127);
  mobileMove(-500, 0);
  delay(1000);
  motorStop(4);
  motorStop(5);
  motorStop(6);
  motorStop(7);

}*/

void redSkills (void) {

  rotSet();
  forebarSet(fbrUp, 0);
  mobileMove(1400, 0);

  delay(750);

  forward3(85);

  motorSet(4, -60);
  motorSet(6, -60);
  motorSet(5, 60);
  motorSet(7, 60);
  mobileMove(-1400, 0);
  delay(180);
  motorStop(4);
  motorStop(5);
  motorStop(6);
  motorStop(7);

  rotate(-180, 1.5);

  mobileMove(700, 0);
  align(40);

  mobileMove(700, 0);
  delay(400);

  forward3(-45);

  rotGo(1.5);

  mobileMove(-500, 0);

  forward3(55);


  rotate(-80, 1.5);

  mobileMove(750, 0);
  forward3(85);

  motorSet(4, -60);
  motorSet(6, -60);
  motorSet(5, 60);
  motorSet(7, 60);
  mobileMove(-1400, 0);
  delay(180);
  motorStop(4);
  motorStop(5);
  motorStop(6);
  motorStop(7);

  rotate(-90, 1.5);

  align(40);

  forward3(-35);

  rotate(90, 1.5);

  forward3(-35);

  rotate(-90, 1.5);

  mobileMove(700, 0);
  align(127);

  mobileMove(700, 0);
  delay(400);

  motorSet(4, 127);
  motorSet(6, 127);
  motorSet(5, -127);
  motorSet(7, -127);
  mobileMove(-500, 0);
  delay(1000);
  motorStop(4);
  motorStop(5);
  motorStop(6);
  motorStop(7);

}
