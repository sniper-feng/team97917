#include "../Globals/Globals.h"
#include "../_includes.h"
#include "auto.h"
void auto_role_two_1_(){
  enableIntake_In(false);
 moveByEncoder(60, 0, distanceToTick(105),3000);
disableIntake();
 wait(1500, msec);
 spinByEncoder_degree(130, -30, 7000);
 moveByEncoder(60, 0, distanceToTick(160), 7000);
 pushToMaxium();
}