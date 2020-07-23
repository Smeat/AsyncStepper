#ifndef __STEPPERDRIVER__H__
#define __STEPPERDRIVER__H__

#include <stdint.h>
#include "AsyncStepper.h"

void stepper_update(void* stepper);
void stepper_init(async_stepper_t* stepper, int steps, int rpm, int dir, int step, int on, int ms1, int ms2, int ms3);


#endif  // __STEPPERDRIVER__H__
