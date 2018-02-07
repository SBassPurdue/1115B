#include "repos.h"
#include "math.h"
#include "main.h"

int neg(float x)
{
	return x < 0 ? -1 : x == 0 ? 0 : 1;
}
int repos(int position, int dposition, int initSpd)
{
  return neg(dposition-position)*sqrt((((dposition-position)/3.6*1.27)*(dposition-position)/3.6*1.27+abs(initSpd*(dposition-position))));
}

int reposIME(int position, int dposition, int initSpd)
{
  return neg(dposition-position)*sqrt((((dposition-position)/6.272*1.27)*(dposition-position)/6.272*1.27+abs(initSpd*(dposition-position))));
}
int repos2(int pos, int dpos, int vel, float mass)
{
	return mass*(dpos-pos-vel);
}

bool inr(float value, float value2, float scaler) {
  if (value + scaler > value2 && value - scaler < value2) {
    return true;
  } else {
    return false;
  }
}
float max(float v1, float v2) { // returns the maximum number of the two numbers supplied
  if (v1 > v2) {
    return v1;
  }
  if (v2 > v1) {
    return v2;
  }
  if (v2 == v1) {
    return (v1 + v2) / 2;
  }
	return 0;
}

float min(float v1, float v2) { // returns the minimum number of the two numbers supplied
  if (fabsf(v1) < fabsf(v2)) {
    return v1;
  }
  if (fabsf(v2) < fabsf(v1)) {
    return v2;
  }
  if (fabsf(v2) == fabsf(v1)) {
    return (v1 + v2) / 2;
  }
	return 0;
}
double getSpeed(Encoder encoder)
{
  int t = 50;
  int i = 0;
  double p[2] = {0,0};
  while (true) {
    p[i] = encoderGet(encoder);
    if(i == 1)
    {
      return (p[0] - p[1])*(1000/t);
    }
    i = !i;
    delay(t);
  }
}
