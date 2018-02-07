//#include "main.h"

/*int threshold = 10;
int speed = 2;
float rwheel = 5.15; //cm
int liftRatio = 7;
float DEGtoRAD = (180/3.14159); */

/*int moveTo(int motorNum, Encoder en, float distanceCM) {
  int enI = encoderGet(en);
  float distanceDEG = distanceCM/rwheel * DEGtoRAD;
  if (encoderGet(en) - enI <= distanceDEG) {
    motorSet(motorNum, speed * (encoderGet(en) + enI));
    return 1;
  }
  return 0;
}

int lift(int motorNum, Encoder en, float distanceCM) {
  int enI = encoderGet(en);
  float distanceDEG = distanceCM/5 * (180/3.14159);
  if (encoderGet(en) - enI <= distanceDEG) {
    motorSet(motorNum, speed * (encoderGet(en) + enI));
    return 1;
  }
  return 0;
}
*/
