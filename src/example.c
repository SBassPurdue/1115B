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
#include "example.h"
#include "fbc.h"
#include "fbc_pid.h"
#include "main.h"

fbc_t driveLController;
fbc_pid_t driveLPID;

static void _driveLMove(int power) {
  motorSet(5, power); //Drive Left Back
  motorSet(7, power); //Drive Left Front
}

static int _driveLSense() {
  return encoderGet(enLeftDrive);
}

static void _driveLReset() {
  encoderReset(enLeftDrive);
}

void driveLPIDInit() {
  fbcInit(&driveLController, _driveLMove, _driveLSense, _driveLReset,
          fbcStallDetect, -dDB, dDB, TOLERANCE, CONFIDENCE);
  fbcPIDInitializeData(&driveLPID, dKP, dKI, dKD, -INTEG_CAP, INTEG_CAP);
  fbcPIDInit(&driveLController, &driveLPID);
}

void driveLSetPos(int position) {
  fbcSetGoal(&driveLController, position);
}

void driveLMove() {
  fbcRunContinuous(&driveLController);
}
