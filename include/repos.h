#ifndef REPOS_H_
#define REPOS_H_

#include "main.h"

int neg(float x);
int repos(int position, int dposition, int initSpd);
int reposIME(int position, int dposition, int initSpd);
int repos2(int pos, int dpos, int vel, float mass);
bool inr(float value, float value2, float scaler);
float max(float v1, float v2);
float min(float v1, float v2);
double getSpeed(Encoder encoder);

#endif
