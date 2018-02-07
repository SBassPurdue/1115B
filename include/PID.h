#include <math.h>

int absV(float x) {
  return x <= 0 ? -x : x;
}

int targetApproach(int input, int target, int threshold) {
  if (absV(input-target) >= threshold) {
    return (-1.27*(input-target)*abs(input-target));
  } else {
    return 0;
  }
}
