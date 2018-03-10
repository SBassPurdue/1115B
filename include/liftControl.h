#ifndef LIFTCONTROL_H_
#define LIFTCONTROL_H_

#include "main.h"

void lift(int targLift, bool wait);
//void waitForSpeed(void * parameter);
//void coneLiftSet(int pos);
void extake(int del);
void intake(int del);
void liftUp(int targLift);
void liftDown(int targLift);
void forebarSet(int pos, bool wait);
void mobileMove(float time, bool wait);
void align(int speed);
//void extakeWait(void);
//void intake(void * parameter);
//void liftSet(int pos);
//void liftHeight(float height, bool wait);
//float getHeightRight(void);
//float getHeightLeft(void);
//void stack(void * parameter);
//void stack1(void);
void forward(float dist);
void forward2(float dist);
void forward3(float dist);
void forward3t(float dist, int t);
void back(float dist);
void rotSet();
void rotGo(float speed);
void rotate(int ang, float speed);
void lMgFb(void *parameter);
//void mobleGoal(int mode);

#endif
