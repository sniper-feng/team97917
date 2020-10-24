#include "../Globals/Globals.h"
#include "../push/push.h"
#pragma once

int limiter(int target, int leftBound, int rightBound) {
  if (target >= leftBound && target >= rightBound)
    return target;
  else if (target > rightBound)
    return rightBound;
  else
    return leftBound;
}
bool b_push_goto_lay_tower = false;
int push_dir = DIR_PUSH_NONE;

void push_goto_lay_tower() {
  if (get_push_enc() < push_enc_lay_tower)
    push_set_voltage(DIR_key_push_out * 8000);
  else
    push_set_voltage(100);
}

/*------------------------------push handler------------------------*/
/*------------------------------definition------------------------*/

/*-----------------------------For Bot 97917G----------------------*/


#ifdef bot_97917G
#define APPROACH_MIN 500
#define APPROACH_MAX 3000

#define PUSH_LIMIT_MIN -80

#define PUSH_LIMIT_MAX 4600

#define UPPER_LIMIT 4585

#define DECELERATE_POINT 2600

#define PUSH_IN_DECELERATE_POINT 200
#define HOLD_VOLTAGE 100
#endif


/*-----------------------------For Bot 97917A----------------------*/


#if defined(bot_97917A) || defined(bot_97917F)
#define APPROACH_MIN 500
#define APPROACH_MAX 2700

#define PUSH_LIMIT_MIN -80

#define PUSH_LIMIT_MAX 3850

#define UPPER_LIMIT 4000

#define DECELERATE_POINT 3100

#define PUSH_IN_DECELERATE_POINT 270
#define HOLD_VOLTAGE 100
#endif

/*-----------------------Handler---------------------------------------------*/
//#ifdef USING_BETA
static bool lock_FirstEntry = true;
static int fixingBase = 0;
static const double kp_locker = 70;

void handle_push(int key_push_out, int key_push_in, int slow_mode) {
  static int output = 0, err = 0, kp = 7;
  err = UPPER_LIMIT - get_push_enc();
  if (key_push_out && key_push_in) {
    lock_FirstEntry = true;
    // both key pressed.hold.
    push_set_voltage(2000);
  } else if (key_push_out && get_push_enc() < DECELERATE_POINT) {
    // push out quickly...
    lock_FirstEntry = true;
    output = err * kp;
    if (output > 12800)
      output = 12800;
    if (output < 2500)
      output = 2500;
    push_set_voltage(output);
  } else if (key_push_out && get_push_enc() > DECELERATE_POINT) {
    lock_FirstEntry = true;
    // approaching maxium...slow down...
    output = (7000 - 35000 /*  delta Voltage △V*/) /
                 (UPPER_LIMIT - (DECELERATE_POINT + 200 /*temp offset*/)) *
                 limiter(err, 0, 1000000) +
             3500;
    push_set_voltage(output);
  } else if (key_push_in && get_push_enc() > PUSH_IN_DECELERATE_POINT) {
    lock_FirstEntry = true;
    //快速回收
    push_set_voltage(-12000);
  } else if (key_push_in && get_push_enc() < PUSH_IN_DECELERATE_POINT &&
             get_push_enc() > PUSH_LIMIT_MIN) {
    lock_FirstEntry = true;
    //减速回收
    err = PUSH_LIMIT_MIN - get_push_enc();
    output =
        (((-12000) - HOLD_VOLTAGE) /* △V*/ / (-210)) /*k*/ * err + HOLD_VOLTAGE;

  } else { //什么都没按住 板子加限位!
    if (lock_FirstEntry) {
      fixingBase = get_push_enc();
      lock_FirstEntry = false;
    }//修正无操作位移时用的变量
    static int err_fix = 0, output_fix = 0;
    err_fix = get_push_enc() - fixingBase;
    output_fix = err_fix * -kp_locker;
    if (output_fix > 12800)
      output_fix = 12800;
    if (output_fix < -12800)
      output_fix = -12800;
    push_set_voltage(output_fix);
  }
}
void preLockPush(){
  if (lock_FirstEntry) {
      fixingBase = get_push_enc();
      lock_FirstEntry = false;
    }//修正无操作位移时用的变量
    static int err_fix = 0, output_fix = 0;
    err_fix = get_push_enc() - fixingBase;
    output_fix = err_fix * -kp_locker;
    if (output_fix > 12800)
      output_fix = 12800;
    if (output_fix < -12800)
      output_fix = -12800;
    push_set_voltage(output_fix);
}
//#else
//Deprected
// void handle_push(int key_push_out, int key_push_in, int slow_mode) {
//   if (limit_push_min) {
//     push_enc_reset();
//   }

//   if (key_push_out && !key_push_in) {
//     push_dir = DIR_key_push_out;
//     if (limit_push_max.pressing())
//       push_set_voltage(HOLD_VOLTAGE);
//     else {
//       if (slow_mode)
//         push_set_voltage(3000);
//       else
//         push_goto_highest_according_to_enc();
//     }

//   } else if (key_push_in && !key_push_out && !limit_push_min) {
//     push_dir = DIR_key_push_in;
//     push_set_voltage(-12000);
//   } else {

//     // b_push_goto_lay_tower = (Controller.Axis2.position() > 40);
//     b_push_goto_lay_tower = false;

//     if (!b_push_goto_lay_tower) { // normal
//       if (push_dir == DIR_key_push_out)
//         push_set_voltage(2000);
//       else if (push_dir == DIR_key_push_in) {

//         if (get_push_enc() < APPROACH_MIN) // tray almost reset
//           push_set_voltage(-1500);         //-2000

//         else if (get_push_enc() < APPROACH_MAX) // tray almost reset for A :2400
//           push_set_voltage(-2000);              //-2000
//         else
//           push_set_voltage(HOLD_VOLTAGE);

//       } else
//         push_set_voltage(HOLD_VOLTAGE);
//     } // normal
//     else {
//       push_dir = DIR_PUSH_NONE;
//       push_goto_lay_tower();
//     } // swing up
//   }   // both key released
// }
//#endif