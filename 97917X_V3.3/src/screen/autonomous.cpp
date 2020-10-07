#include "../_includes.h"

void autonomousChooser(void) {
  int line = 200;

  vex::timer t_auto;

  all_motor_brake();
  // reset_all_encoders();
//TODO  : using binding to run different funcs
  if (auto_info.role == ROLE_ONE) {
    if (auto_info.route_number == 1){
      bindAutonomous(auto_role_one_1_);
    }
     // auto_role_one_1();
    if (auto_info.route_number == 2){
       bindAutonomous(auto_role_one_1_);
    }
     // auto_role_one_2();
  }

  if (auto_info.role == ROLE_TWO) {
    if (auto_info.route_number == 1){
       bindAutonomous(auto_role_one_1_);
    }
     // auto_role_two_1();
    if (auto_info.route_number == 2){
       bindAutonomous(auto_role_one_1_);
    }
     // auto_role_two_2();
  }

  //Print(0, line, "auto time:%.1fs  ", t_auto.time() / 1000.0);
}