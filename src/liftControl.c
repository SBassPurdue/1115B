#include "liftControl.h"
#include "main.h"
#include "repos.h"
#include "math.h"

#define PI 3.14159

int wheeld = 11;
int robotd = 39;
int speed = 2;

bool lift(int motorNum, Encoder en, float distanceCM) {
  int enI = encoderGet(en);
  float distanceDEG = distanceCM/5 * (180/3.14159);
  if (encoderGet(en) - enI <= distanceDEG) {
    motorSet(motorNum, speed * (encoderGet(en) + enI));
    return 1;
  }
  return 0;
}
/*
void waitForSpeed(void *parameter) {
  while (true) {
    delay(1000);
    speedWait = false;
    if(holdLift){
      motorSet(6, reposIME(IMECounts0, lastLiftPosLeft, 1)*4);
      motorSet(7, -reposIME(-IMECounts1, lastLiftPosRight, 1)*4);
    }
  }
}
*/

/*
void coneLiftSet(int pos) {
  while (true) {
    motorSet(8, -repos(encoderGet(intakeLift), pos, 30)*3);
    if ((pos - 8 <= encoderGet(intakeLift) && encoderGet(intakeLift) <= pos + 8) && getSpeed(intakeLift) == 0) {
      break;
    }
  }
}
*/
void extake(int del) {
  motorSet(1, 100);
  motorSet(3, 20); //Lift Left
  motorSet(2, 20); //Lift Right
  delay(del);
  motorStop(1);


}

/*
void extakeWait(void) {
  motorStop(9);
  speedWait = true;
  rollerHoldValue = encoderGet(intakeE);
  while (true) {
    motorSet(9, repos(encoderGet(intakeE), rollerHoldValue - 180, 10));
    if (getSpeed(intakeE) == 0 && !speedWait) {
      break;
    }
  }
}
*/
/*
void intake(void *parameter) {
  motorStop(9);
  speedWait = false;
  while (true) {
    delay(20);
    rollerHoldValue = encoderGet(intakeE);
    motorSet(9, 63);
    // fprintf(stdout, "%s\n", "Intake Running");
    if (getSpeed(intakeE) == 0 && !speedWait) {
      fprintf(stdout, "%s\n", "Intake Task Stopped");
      motorStop(9);
      rollerHold = true;
      taskSuspend(NULL);
    }
  }
}
*/
/*
void liftHeight(float height, bool wait) {

}
*/

void forward(float dist) {
  encoderReset(enLeftDrive);
  encoderReset(enRightDrive);
  float calc = ceil((dist / (wheeld*PI))*360);
  int tick = 10; // Amout of seconds*10 after the bot moves to correct any final
  while (true) {
    delay(20);
    motorSet(5, repos(encoderGet(enLeftDrive), calc, 30));
    motorSet(7, repos(encoderGet(enLeftDrive), calc, 30));
    motorSet(4, -repos(encoderGet(enRightDrive), calc, 30));
    motorSet(6, -repos(encoderGet(enRightDrive), calc, 30));

    lcdPrint(uart1, 1, "enR: %d", encoderGet(enRightDrive));
    lcdPrint(uart1, 2, "enL: %d", encoderGet(enLeftDrive));

    /*motorSet(2, repos2(-encoderGet(leftBack), calc, getSpeed(leftBack), 1, 1));
    motorSet(3, repos2(-encoderGet(leftBack), calc, getSpeed(leftBack), 1, 1));
    motorSet(4, -repos2(encoderGet(rightBack), calc, getSpeed(rightBack), 1, 1));
    motorSet(5, -repos2(encoderGet(rightBack), calc, getSpeed(rightBack), 1, 1));*/
    if (inr(max(encoderGet(enLeftDrive), encoderGet(enRightDrive)), calc, 20)) {
      tick -= 1;
      if (tick <= 0) {
        motorStop(5);
        motorStop(7);
        motorStop(4);
        motorStop(6);
        break;
      }
      delay(100);
    }
  }
}

void back(float dist) {
  encoderReset(enLeftDrive);
  encoderReset(enRightDrive);
  float calc = -ceil((dist / (wheeld*PI))*360);
  int tick = 10; // Amout of seconds*10 after the bot moves to correct any final
  while (true) {
    delay(20);
    motorSet(5, repos(encoderGet(enLeftDrive), calc, 30));
    motorSet(7, repos(encoderGet(enLeftDrive), calc, 30));
    motorSet(4, -repos(encoderGet(enRightDrive), calc, 30));
    motorSet(6, -repos(encoderGet(enRightDrive), calc, 30));

    lcdPrint(uart1, 1, "enR: %d", encoderGet(enRightDrive));
    lcdPrint(uart1, 2, "enL: %d", encoderGet(enLeftDrive));

    /*motorSet(2, repos2(-encoderGet(leftBack), calc, getSpeed(leftBack), 1, 1));
    motorSet(3, repos2(-encoderGet(leftBack), calc, getSpeed(leftBack), 1, 1));
    motorSet(4, -repos2(encoderGet(rightBack), calc, getSpeed(rightBack), 1, 1));
    motorSet(5, -repos2(encoderGet(rightBack), calc, getSpeed(rightBack), 1, 1));*/
    if (inr(min(encoderGet(enLeftDrive), encoderGet(enRightDrive)), calc, 20)) {
      tick -= 1;
      if (tick <= 0) {
        motorStop(5);
        motorStop(7);
        motorStop(4);
        motorStop(6);
        break;
      }
      delay(100);
    }
  }
}

/*
void rotate(float ang) {
  encoderReset(leftE);
  encoderReset(rightE);
  gyroReset(angle);
  int mul = 30; // Tweak this so the bot overcomes drive friction
  int flatten = 3;
  int calc =
      robotd * PI / (360 / ang) /
      (PI * wheeld /
       360);    // Calculates the rotations required to traval dist in degrees
  int tick = 5; // Amout of seconds*10 after the bot moves to correct any final
                // flaws use: tick = seconds*10
  lcdClear(uart2);
  while (true) {
    // lcdPrint(uart2, 1, "%d %d",encoderGet(leftE),encoderGet(rightE));
    lcdPrint(uart2, 1, "dAngle: %f",ang);
    lcdPrint(uart2, 2, "gyro: %d",gyroGet(angle));
    motorSet(2, repos(gyroGet(angle), ang, mul)*flatten);
    motorSet(3, repos(gyroGet(angle), ang, mul)*flatten);
    motorSet(4, repos(gyroGet(angle), ang, mul)*flatten);
    motorSet(5, repos(gyroGet(angle), ang, mul)*flatten); */
    /* FOR motorSet ^
    ** To change which drive motor ports are used by
    ** changing the rdrive[] and ldrive[] array variables
    */
/*
    if (inr(gyroGet(angle), ang, 2)) {
      tick -= 1;
      if (tick <= 0) {
        motorSet(2, 0);
        motorSet(3, 0);
        motorSet(4, 0);
        motorSet(5, 0);
        break;
      }
      wait(100);
    }
  }
}
*/
/*
float getHeightRight(void){
  int angle = (IMECounts1/(627/360))/2;
  int height = sinf(angle)*125.73;
  return height;
}
float getHeightLeft(void){
  int angle = (IMECounts0/(627/360))/2;
  int height = sinf(angle)*125.73;
  return height;
}
*/
/*
void mobleGoal(int mode){
    while(mode == 1){
      motorSet(1, -repos(analogRead(2), 790, 30)*2);
      motorSet(10, repos(analogRead(2), 790, 30)*2);
      if (inr(analogRead(2), 790, 5)){
        break;
      }
    }
    while(mode == 2){
      motorSet(1, -repos(analogRead(2), 2795, 30)*2);
      motorSet(10, repos(analogRead(2), 2795, 30)*2);
      if (inr(analogRead(2), 2795, 5)){
        break;
      }
    }
}
*/ /*
void stack(void *parameter) {
  lastLiftPosLeft = 0;
  lastLiftPosRight = 0;
  coneLiftSet(35);
    while(ultrasonicGet(coneSonar) < 36){
      motorSet(6, 127);
      motorSet(7, -127);
      lastLiftPosLeft = getHeightLeft();
      lastLiftPosRight = getHeightRight();
    }
    while(true){
    //motorSet(6, reposIME(IMECounts0, lastLiftPosLeft, 1)*4);
    //motorSet(7, -reposIME(-IMECounts1, lastLiftPosRight, 1)*4);
    liftHeight(lastLiftPosRight, true);
    lcdSetText(uart2, 1, "It Ran"); */
    /*
    coneLiftSet(113);
    rollerHold = false;
    extakeWait();
    motorStop(6);
    coneLiftSet(35);
    speedWait = true;
    coneLiftSet(5);*/
/*
  }
}

void stack1(void){
  lastLiftPosLeft = 0;
  lastLiftPosRight = 0;
  coneLiftSet(35);
    while(ultrasonicGet(coneSonar) < 36){
      imeGet(IME0, &IMECounts0);
      imeGet(IME1, &IMECounts1);
      motorSet(6, 127);
      motorSet(7, -127);
      lastLiftPosLeft = getHeightLeft();
      lastLiftPosRight = getHeightRight();
    }
    while(true){
      //motorSet(6, repos(IMECounts0, lastLiftPosLeft, 1)*4);
      //motorSet(7, -repos(-IMECounts1, lastLiftPosRight, 1)*4);
      liftHeight(lastLiftPosRight, true);
      lcdSetText(uart2, 1, "It Ran");
      lcdPrint(uart2, 2, "Lift: %d %d", lastLiftPosLeft, lastLiftPosRight); */
    /*
    coneLiftSet(113);
    rollerHold = false;
    extakeWait();
    motorStop(6);
    coneLiftSet(35);
    speedWait = true;
    coneLiftSet(5);*/
/*
  }
  //lcdSetText(uart2, 2, "It Stopped");
}
*/
