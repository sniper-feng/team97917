#pragma once
#ifndef autoh
#define autoh autoh
#include "../_includes.h"

/*=--------------------General-------------*/
void autonomousChooser(void);
static void (*autofp)();
void bindAutonomous(void(*fp)());
//#error NoDefault

/*-------------------Init-------------------*/
void unlock_robot();
/*--------------------Motor-----------------*/
// Stuck during the Movement  to create a linear control
void moveForwardByEncoder(int aim_final, int time_out, int turn,int max_speed);
void moveByEncoder(int speed , int turn , int enc_target);
void stop();
// Stuck during the Movement  to create a linear control
void spinByAbsoluteAngle(double target,int timeOutMilli , int forward=0,int maxSpeed=100);
void spinByRelativeAngle(double angle ,int timeOutMilli,int forward=0 , int maxSpeed=100);
/*--------------------Swing------------------*/
void swingReset();
void rotateSwingByEncoder(double speed, int target);
/*--------------------Push-------------------*/
void pushToHighest();
/*-------------------Intake------------------*/

void enableIntake();
void disableIntake();



/*--------Implements of Autonoumous path------*/
void auto_role_one_1_();
#endif




