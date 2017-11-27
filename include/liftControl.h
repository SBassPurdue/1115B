#ifndef LIFTCONTROL_H_
#define LIFTCONTROL_H_

#include "main.h"

bool lift(int motorNum, Encoder en, float distanceCM);
//void waitForSpeed(void * parameter);
//void coneLiftSet(int pos);
void extake(int delay);
//void extakeWait(void);
//void intake(void * parameter);
//void liftSet(int pos);
//void liftHeight(float height, bool wait);
//float getHeightRight(void);
//float getHeightLeft(void);
//void stack(void * parameter);
//void stack1(void);
void forward(float dist);
void back(float dist);
//void rotate(float ang);
//void mobleGoal(int mode);

#endif
