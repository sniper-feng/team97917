#include "../src/auto/auto.h"
void moveForwardByEncoder(int aim_final, int time_out, int turn=0 ,int max_speed=100);
void swingReset();
void moveByEncoder(int speed , int turn , int enc_target);
/*----------------------------Attention---------------------*/
/* Unless specified, all the control 
functions will block until operation is complete or timeout.*/








/*-------------------Init-------------------*/




//block

void resetPush_Vibration(){
  push_set_voltage(12800); // push hold out
  while (get_push_enc() < push_enc_unlock_support_board)
    ;

  push_set_voltage(-12800); // push hold out
  while (get_push_enc() > push_enc_support_delta)
    ;
  push_enc_reset();
  push_set_voltage(-1500);
}




//void preLockPush;
void unlock_robot(){
  //TODO 解锁： swing抬升下降 + push抬升下降（可以转吸盘）
  reset_all_encoders();
  swing_set_voltage(-2000); // swing

  moveForwardByEncoder(450, 400, 0, 60); // push preload forward and unlock anti-down
  moveForwardByEncoder(300, 200);        // push preload forward and unlock anti-down

  swing_set_voltage(128000);    // unlock tray
  thread(resetPush_Vibration).detach();

  move_set_voltage(-3500, 0); // stick to back wall

  //while (get_swing_enc() < 1000)
    ;
  swing_set_voltage(0);
  intake_unlock_service(); // block function
  thread(swingReset).detach();
  wait(300);

  // intake_unlock_thread_start();
  wait(100);               // wait for intake roller set
}











/*--------------------Motor-----------------*/









// Block during the Movement  to create a linear control

void moveByEncoder(int speed , int turn , int enc_target){
  int temp = get_move_enc();
  while(get_move_enc()-temp <= enc_target)
  move_set_speed(speed, turn);
  move_stop();
}




//using p controller
void moveForwardByEncoder(int aim_final, int time_out, int turn ,int max_speed) {
  float kp = 0.5;
  float output, err;

  vex::timer t0;

  while (t0.time() < time_out) {
    err = aim_final - get_move_enc();
    output = kp * err;

    if (output > max_speed)
      output = max_speed;
    if (output < -max_speed)
      output = -max_speed;

    move(output, turn);
    wait(10);

    // err break
    if (abs(err) <= 10)
      break;
  }
  move_stop();
}





void stop(){
  move_stop();
}




// Stuck during the Movement  to create a linear control
bool firstEntry = true;
double err;
double output;



// target: the angle based on the robot's angle when booted.
void spinByAbsoluteAngle(double target,int timeOutMilli , int forward,int maxSpeed){
 vex::timer time;
 while(time.time(msec) < timeOutMilli){
  //linear p controller
  // Line Formula : Power = currentErr * (-(maxSpeed / err)) + maxSpeed
  output = (target-gyro_z.value(rotationUnits::deg)) * (-maxSpeed/err) + maxSpeed;
  move(forward, output);
 }
}











double target;
void spinByRelativeAngle(double angle ,int timeOutMilli,int forward, int maxSpeed){
  if(firstEntry)
  {
  target = angle +gyro_z.value(rotationUnits::deg);
  }
  firstEntry = false;
  spinByAbsoluteAngle(target, timeOutMilli,forward,maxSpeed);
}



/*------------------------------------Swing-------------------------------*/
void swingReset() {
  swing_set_voltage(-12800); // push hold out
  while (get_swing_enc() > 100)
    ;
  swing_set_voltage(-1500);
}








/*-----------------------------------Push--------------------------------*/
void pushToHighest() {
  push_set_voltage(12800);
  while (get_push_enc() < 5000)
    ;

  intake_set_voltage(-1000);

  while (1) {
    int err;

    err = push_enc_highest - abs(get_push_enc());

    if (err > 1350) {
      push_set_voltage(7000);
      intake_set_voltage(2000);
    } else if (err > 600)
      push_set_voltage(5000);
    else if (err > 300) {
      push_set_speed(5);
      move_set_voltage(3000, 0);
    } else // almost straight
      push_set_speed(5);

    // Stop Condition
    if (abs(mtr_push.velocity(velocityUnits::rpm)) <= 3 || limit_push_max) {
     //push stuck
      push_set_voltage(3000);
      break;
    }

    if (get_push_enc() > push_enc_highest - 200) {
      //push beyond limit...
      push_set_voltage(2000);
      wait(400);
      break;
    }

    wait(5);
  }
}