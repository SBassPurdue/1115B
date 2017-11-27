#include "math.h"

int neg(float x)
{
	return x < 0 ? -1 : x == 0 ? 0 : 1;
}
int repos(int position, int dposition, int initSpd)
{
  return neg(dposition-position)*sqrt((((dposition-position)/3.6*1.27)*(dposition-position)/3.6*1.27+abs(initSpd*(dposition-position))));
}
