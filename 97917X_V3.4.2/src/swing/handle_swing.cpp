
#include "swing.h"
#define SWING_MAX 1322
/////////////////////////////////////////
static bool startFixing = false;
static int fixingBase = 0;
static const double kp = 100;//TEST!!!!
static int err = 0,output = 0;
void handle_swing(int input,int slow_mode){
  
  if (abs(input) > 30)
    b_all_motor_float = false;

  if (abs(input) <= 2)
    input = 0;
  if(input > 0 && get_swing_enc() > SWING_MAX/*超限了。不准再上升*/){
    startFixing = false;
    swing_set_voltage(swing_empty_hold_voltage);
  }
  else if(input == 0){
    //不要动OvO
      if(!startFixing){
        startFixing = true;
        fixingBase = get_swing_enc();
      }
      int err = 0,output = 0;
      err = get_swing_enc() - fixingBase;
      output = err * -kp;
      if(output > 12800)output =12800;
      if(output<-12800)output = -12800;
    swing_set_voltage(output);
    
    }
  else{
    startFixing = false;
    if(slow_mode){
      swing_set_voltage(input / 100.0 * 12000);
    }
    else{
      
      swing_set_voltage(input / 70.0 * 12000);
    }
  }
  
}
/*
void handle_swing(int chx, int slow_mode) {
  if (abs(chx) > 30)
    b_all_motor_float = false;

  static int dir = 0;
  if (abs(chx) <= 2)
    chx = 0;

  if (chx != 0) {
    dir = sgn(chx);
    if (slow_mode)
      swing_set_voltage(chx / 100.0 * 12000);
    else
      swing_set_voltage(chx / 70.0 * 12000);
  } else
    swing_set_voltage(dir * swing_hold_voltage);
}*/