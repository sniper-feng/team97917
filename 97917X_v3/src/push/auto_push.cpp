#include "../push/push.h"

#define push_unlock_enc 500

void push_unlock_service() {
  push_set_speed(DIR_key_push_out * 80);
  while (get_push_enc() < push_unlock_enc) {
  };
  push_set_speed(DIR_key_push_out * 0);
  wait(1000);
  push_set_speed(DIR_key_push_in * 60);
  while (get_push_enc() > 100) {
  };
  push_set_voltage(DIR_key_push_in * 1300);
}

void push_unlock_thread_start() { vex::thread th(push_unlock_service); }


#ifdef bot_97917G
#define UPPER_LIMIT 4585

#define DECELERATE_POINT 2780
#else
#define UPPER_LIMIT 2522

#define DECELERATE_POINT 756
#endif
#ifdef USING_BETA
void push_goto_highest_according_to_enc(){
  static int err;
  static int output;
  static float kp = 7;

  err = UPPER_LIMIT - abs(get_push_enc());

  if(get_push_enc() < DECELERATE_POINT){
    output = err * kp;
    if (output > 12800)
      output = 12800;
    if (output < 2500)
      output = 2500;
    push_set_voltage(output);
  }
  else if(get_push_enc() >DECELERATE_POINT &&get_push_enc() < UPPER_LIMIT){
    
  }
  else/*err >=4585*/{
      output = 2000;
      push_set_voltage(output);
  } 
}





#else 

#define enc_push_begin_slow_down 2000

void push_goto_highest_according_to_enc() {
  static int err;
  static int output;
  static float kp = 7;

  err = push_enc_highest - abs(get_push_enc());

  
  if (err > enc_push_begin_slow_down) {//far from stragigt
    output = err * kp;
    if (output > 12800)
      output = 12800;
    if (output < 2500)
      output = 2500;
    push_set_voltage(output);
  } else {
    if (limit_push_max.pressing())
      push_set_voltage(2000);
    else
      push_set_speed(30);
  }

  if (limit_push_max.pressing()) {
    push_set_voltage(2000);
  
  }

  //2860 开始减速 4585停下
}


//97917 A :2522停 756减速
#endif