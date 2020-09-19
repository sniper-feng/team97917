#pragma once
#ifndef autoh
#define autoh autoh
#include "../_includes.h"
/*=--------------------General-------------*/
static void (*autofp)();
//#error NoDefault

/*-------------------Init-------------------*/
void unlock_robot();
/*--------------------Motor-----------------*/
// Stuck during the Movement  to create a linear control
void moveByEncoder();
void stop();
// Stuck during the Movement  to create a linear control
void spinByRelativeAngle();
void spinByAbsoluteAngle();
/*--------------------Swing------------------*/
#endif