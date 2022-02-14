#include <stdbool.h>

unsigned int getT(void);
void update_HMI(unsigned int temp,unsigned int* tTarget);
void defrost(void);
//void update_HMI2(unsigned int temp);

static _Bool   off = false;  
static unsigned int TempSys = 0; 
static _Bool   T_target_reached = false;   // variable used to notify if the temperature target is reached
static _Bool   GO_defrost       = false;         // status variable used to start the de frost
static unsigned int*  TTarg           = &T_target_reached;