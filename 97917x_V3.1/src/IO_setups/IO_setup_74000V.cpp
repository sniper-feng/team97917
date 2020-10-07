#include "vex.h"
#if (ROBOT == R_74000V)

#ifdef bot_97917A
// move




vex::motor mtr_LF(vex::PORT18,ratio18_1, false);
vex::motor mtr_LB(vex::PORT7, ratio18_1,false);
vex::motor mtr_RF(vex::PORT3, ratio18_1,true);
vex::motor mtr_RB(vex::PORT2,ratio18_1, true);

// intake
vex::motor mtr_intake_L(vex::PORT10, vex::ratio36_1, true);
vex::motor mtr_intake_R(vex::PORT12,ratio36_1,false); 

// other
vex::motor mtr_swing(vex::PORT1, vex::ratio36_1, true);
vex::motor mtr_push(vex::PORT14, vex::ratio36_1, false);

// sensors
vex::gyro gyro_z(Brain.ThreeWirePort.A);
vex::limit limit_push_max(Brain.ThreeWirePort.B);
vex::limit limit_push_min(Brain.ThreeWirePort.C);





#else // bot_97917G
// move
vex::motor mtr_LF(vex::PORT18,ratio18_1, false);
vex::motor mtr_LB(vex::PORT9, ratio18_1,false);
vex::motor mtr_RF(vex::PORT3, ratio18_1,true);
vex::motor mtr_RB(vex::PORT2,ratio18_1, true);

// intake
vex::motor mtr_intake_L(vex::PORT10, vex::ratio36_1, true);
vex::motor mtr_intake_R(vex::PORT11, vex::ratio36_1, false);

// other
vex::motor mtr_swing(vex::PORT1, vex::ratio36_1, true);
vex::motor mtr_push(vex::PORT14, vex::ratio36_1, false);

// sensors
vex::gyro gyro_z(Brain.ThreeWirePort.A);
vex::limit limit_push_max(Brain.ThreeWirePort.B);
vex::limit limit_push_min(Brain.ThreeWirePort.C);
#endif


#ifdef SimpleCompetitionControl
vex::bumper bumperControl(Brain.ThreeWirePort.H);
#endif
#endif