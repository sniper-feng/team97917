#pragma once
#ifndef autoh
#define autoh autoh
#include "../_includes.h"

/*=--------------------General-------------*/
void autonomousChooser(void);
static void (*autofp)();
void bindAutonomous(void(*fp)());
int distanceToTick(double centimeter);
//#error NoDefault

/*-------------------Init-------------------*/
void unlock_robot();
/*--------------------Motor-----------------*/
// Stuck during the Movement  to create a linear control
void moveByEncoder(int speed , int turn , int enc_target ,int timeOutMilli);
void stop();
// Stuck during the Movement  to create a linear control
void spinByAbsoluteAngle(double target,int timeOutMilli , int forward=0,int maxSpeed=100);
void spinByRelativeAngle(double angle ,int timeOutMilli,int forward=0 , int maxSpeed=100);
void spinByEncoder_target(int target,int speed,int timeOutMilli);
void spinByEncoder_degree(int degree,int speed,int timeOutMilli);

/*--------------------Swing------------------*/
void swingReset();
void rotateSwingByEncoder(double speed, int target);
/*--------------------Push-------------------*/
void pushToHighest();
void pushToMaxium();
/*-------------------Intake------------------*/

static void intakeSpinIn();
static void intakeSpinOut();
void enableIntake_In(bool isSlowMode);
void enableIntake_Out(bool isSlowMode);
void disableIntake();


/*--------Implements of Autonoumous path------*/
void auto_role_one_1_();
#endif




