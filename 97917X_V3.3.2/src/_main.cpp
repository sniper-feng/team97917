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

#define AUTOLIMIT 2
extern vex::bumper bumperControl;

void func(void){
  Brain.Screen.printAt(0,170,"Auto");
        autonomous();
}
bool pressed = false;

int main() {
  int autoCounter = 0;
  gyro_z.calibrate();
  Brain.Screen.printAt(0,190,"Wait..");
  vex::thread th_control(usercontrol);
  th_control.detach();
  pre_auton();
  buttons_init();
  bumperControl.pressed(func);
  timer time;
  while(time.time(msec) < 800){
    mtr_push.spin(fwd, -9000,voltageUnits::mV);
    reset_all_encoders();
  }
  mtr_push.stop();
  while (1) {
    wait(50);
    special_key_handle();
    screen_display_choose();
    sensor_display();

    if(!pressed && bumperControl.pressing()){
      
      if(AUTOLIMIT > autoCounter){
        Brain.Screen.printAt(0,210,"Auto");
        autonomous();
      }
      else{
        Brain.Screen.printAt(0,230,"Auto Exectution Already Completed");
      }
    }
    else if (!bumperControl.pressing() && pressed) {

    pressed = false;
    }
  }
}
#endif