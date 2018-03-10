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
#ifndef _DRIVEPID_H_
#define _DRIVEPID_H_

#include <API.h>

#define dDB 15 // the motors don't do much betlow this speed
#define TOLERANCE 20 //??? Don't change
#define CONFIDENCE 5 //~200ms tolerance band

#define dKP 0.8f
#define dKI 1.0f
#define dKD 130.0f

#define rKP 0.8f
#define rKI 1.0f
#define rKD 130.0f

#define INTEG_CAP 10

void drivePIDInit();
void driveSetPos(int position);
void driveMove();

#endif
