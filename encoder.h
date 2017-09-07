/** @file main.h
 * @brief Header file for global functions
 *
 * Any experienced C or C++ programmer knows the importance of header files. For those who
 * do not, a header file allows multiple files to reference functions in other files without
 * necessarily having to see the code (and therefore causing a multiple definition). To make
 * a function in "opcontrol.c", "auto.c", "main.c", or any other C file visible to the core
 * implementation files, prototype it here.
 *
 * This file is included by default in the predefined stubs in each VEX Cortex PROS Project.
 *
 * Copyright (c) 2011-2016, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#ifndef ENCODER_H_

// This prevents multiple inclusion, which isn't bad for this file but is good practice
#define ENCODER_H_

#include <API.h>

// Allow usage of this file in C++ programs
#ifdef __cplusplus
extern "C" {
#endif

typedef void * Encoder;
/**
 * Gets the number of ticks recorded by the encoder.
 *
 * There are 360 ticks in one revolution.
 *
 * @param enc the Encoder object from encoderInit() to read
 * @return the signed and cumulative number of counts since the last start or reset
 */
int encoderGet(Encoder enc);
/**
 * Initializes and enables a quadrature encoder on two digital ports.
 *
 * Neither the top port nor the bottom port can be digital port 10. NULL will be returned if
 * either port is invalid or the encoder is already in use. Initializing an encoder implicitly
 * resets its count.
 *
 * @param portTop the "top" wire from the encoder sensor with the removable cover side UP
 * @param portBottom the "bottom" wire from the encoder sensor
 * @param reverse if "true", the sensor will count in the opposite direction
 * @return an Encoder object to be stored and used for later calls to encoder functions
 */
Encoder encoderInit(unsigned char portTop, unsigned char portBottom, bool reverse);
/**
 * Resets the encoder to zero.
 *
 * It is safe to use this method while an encoder is enabled. It is not necessary to call this
 * method before stopping or starting an encoder.
 *
 * @param enc the Encoder object from encoderInit() to reset
 */
void encoderReset(Encoder enc);
/**
 * Stops and disables the encoder.
 *
 * Encoders use processing power, so disabling unused encoders increases code performance.
 * The encoder's count will be retained.
 *
 * @param enc the Encoder object from encoderInit() to stop
 */
void encoderShutdown(Encoder enc);

/**
 * Reference type for an initialized ultrasonic sensor.
 *
 * Ultrasonic information is stored as an opaque pointer to a structure in memory; as this is a
 * pointer type, it can be safely passed or stored by value.
 */

void meetEncoderValue(Encoder encod, float target, unsigned char threshold) {
  while(abs(encoderGet(encod) - target) <= target) {

  }
}

// End C++ export structure
#ifdef __cplusplus
}
#endif

#endif
