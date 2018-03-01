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
#ifndef _EXAMPLE_H_
#define _EXAMPLE_H_

#include <API.h>

#define dDB 15 // the motors don't do much betlow this speed
#define TOLERANCE 20 //??? Don't change
#define CONFIDENCE 5 //~200ms tolerance band

#define dKP 1.0f
#define dKI 0.001f
#define dKD 100.0f
#define INTEG_CAP 100000

void exampleInit();
void exampleSetPos(int position);
void exampleMoveToPos();

#endif
