#include "../Globals/Globals.h"
#include "../_includes.h"
#include "auto.h"
/*
#define MOVE_FULL_VOLTAGE 12800
void auto_role_one_1_(){
  swing_set_voltage(-2000); // swing
  push_set_voltage(-1500);
  unlock_robot();
   swing_set_voltage(-1500);
    intake_full_power_in();
  move(40,0);
  int temp = get_move_enc();
  //while(get_move_enc()-temp <300);
  move_stop();
  move(-90, auto_info.side * 60);
    wait(550);
    move_enc_reset();
    move(-100, 0);
    //while (get_move_enc() < -3000)
      ;
    spinByAbsoluteAngle(0, 1000);
    swing_set_voltage(-1500);
    intake_for_time_thread(12800, 3800);
    move_enc_reset();

    move(30, 0); ////////////////////////////////////////////old
   // while (get_move_enc() < 3100)
      ;
    move_stop();
    move(-100, 0);
    wait(300);
    spinByAbsoluteAngle(auto_info.side * -127, 2000);
    move(100, 0);
    push_set_voltage(6000);
    //while (get_move_enc() < 2400)
      ;
    // get stuck to the zone
    move_set_voltage(1500, 0);
    push_set_voltage(6000);
    wait(250);
    intake_set_voltage(-1500);
    // move_set_voltage(-1500, 0);
    // lay the cube into the zone
    pushToHighest();
    move(-100, 0);
    wait(400);

}
*/
void auto_role_one_1_(){
  Brain.Screen.printAt(0,150,"OnProgram : autorole one 1");
  //unlock_robot();
 // unlock_robot();
 timer time;
 time.reset();
 enableIntake_In(false);
 moveByEncoder(45, 0, distanceToTick(105),3000);
 wait(1500, msec);
 disableIntake();
spinByEncoder_degree(20, 40, 1000);
moveByEncoder(80, 0, -distanceToTick(120), 2000);
spinByEncoder_degree(10, -40, 1000);


 enableIntake_In(false);
 moveByEncoder(45, 0, distanceToTick(95),2000);
 wait(1000);
 disableIntake();
 spinByEncoder_degree(120, 30, 2000);
 moveByEncoder(80, 0, distanceToTick(205),2000);
 pushToMaxium();
 Brain.Screen.printAt(0, 100,"Auto Time :%.2f seconds" ,time.time(sec) );
}