#include "../Globals/Globals.h"
#define swing_loaded_hold_voltage -4000
#define swing_empty_hold_voltage -2000



void swing_set_voltage(int mV);
int get_swing_enc();
void swing_enc_reset();
void swingRotate(double speed);
void handle_swing(int v, int slow_mode);