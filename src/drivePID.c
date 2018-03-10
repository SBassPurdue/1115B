/** @file example.h
 *
 * ========= DEMO CODE =========
 * This file contains example code using BLRS's libfbc
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */
#include "drivePID.h"
#include "fbc.h"
#include "fbc_pid.h"
#include "main.h"

fbc_t driveLController;
fbc_t driveRController;
fbc_pid_t driveLPID;
fbc_pid_t driveRPID;

static void _driveLMove(int power) {
  motorSet(5, power); //Drive Left Back
  motorSet(7, power); //Drive Left Front
}

static void _driveRMove(int power) {
  motorSet(4, -power); //Drive Left Back
  motorSet(6, -power); //Drive Left Front
}

static int _driveLSense() {
  return encoderGet(enLeftDrive);
}

static int _driveRSense() {
  return encoderGet(enRightDrive);
}

static void _driveLReset() {
  encoderReset(enLeftDrive);
}

static void _driveRReset() {
  encoderReset(enRightDrive);
}

void drivePIDInit() {
  //Left Side Drive
  fbcInit(&driveLController, _driveLMove, _driveLSense, _driveLReset,
          fbcStallDetect, -dDB, dDB, TOLERANCE, CONFIDENCE);
  fbcPIDInitializeData(&driveLPID, dKP, dKI, dKD, -INTEG_CAP, INTEG_CAP);
  fbcPIDInit(&driveLController, &driveLPID);

  //Right Side Drive
  fbcInit(&driveRController, _driveRMove, _driveRSense, _driveRReset,
          fbcStallDetect, -dDB, dDB, TOLERANCE, CONFIDENCE);
  fbcPIDInitializeData(&driveRPID, dKP, dKI, dKD, -INTEG_CAP, INTEG_CAP);
  fbcPIDInit(&driveRController, &driveRPID);
}

void driveSetPos(int position) {
  fbcSetGoal(&driveLController, position);
  fbcSetGoal(&driveRController, position);
}

void driveMove() {
  fbcRunContinuous(&driveLController);
  fbcRunContinuous(&driveRController);
}
