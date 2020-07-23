#include "AsyncStepper.h"

#include <Arduino.h>
#include <string.h>

void async_stepper_move(async_stepper_t* stepper, int steps) {
	stepper->move_start_time_us = micros();
	stepper->steps_left = steps;
}

void async_stepper_set_rpm(async_stepper_t* stepper, double rpm) {
	stepper->step_delay_us = 60000000.0 / (stepper->steps_per_rev * rpm);
}

void async_stepper_update(async_stepper_t* stepper) {
	if(stepper->update){
		stepper->update(stepper);
	}
}

int async_stepper_should_step(async_stepper_t* stepper) {
	return micros() - stepper->move_start_time_us - stepper->step_delay_us * stepper->steps_done >= stepper->step_delay_us;
}

void async_stepper_init(async_stepper_t* stepper, int steps, double rpm) {
	memset(stepper, 0, sizeof(async_stepper_t));
	stepper->steps_per_rev = steps;
	async_stepper_set_rpm(stepper, rpm);
}
