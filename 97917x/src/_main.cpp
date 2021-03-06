#include "_includes.h"

// system
vex::brain Brain;
vex::controller Controller;
vex::competition Competition;

void display(void) {
  while (1) {
    screen_display_choose();
    sensor_display();
    wait(50);
  }
}









//Using Competition Controller
#ifndef SimpleCompetitionControl
int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  gyro_z.calibrate();
  gyro_z.resetAngle(0, rotationUnits::deg);
  pre_auton();
  buttons_init();
  vex::thread th_display(display);
  // vex::thread th_gyro(GyroTask);

  while (1) {
    wait(50);
    special_key_handle();
  }
}










//Using Button Control( informal competition )
#else

extern vex::bumper bumperControl;


int main() {
  
  vex::thread th_control(usercontrol);
  th_control.detach();
  while (1) {
    wait(50);
    special_key_handle();


    if(!pressed && bumperControl.pressing()){
        autonomous();
    }
    else if (!bumperControl.pressing() && pressed) {

    pressed = false;
    }
  }
}
#endif