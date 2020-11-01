/*
 * Copyright (c) 2020 smeat.
 *
 * This file is part of AsyncStepper 
 * (see https://github.com/Smeat/AsyncStepper).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
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
		int step = stepper->update(stepper);
		if(step != 0) {
			stepper->steps_done += 1;
			stepper->steps_left += step;
		}
	}
}

int async_stepper_should_step(async_stepper_t* stepper) {
	uint32_t time_passed = micros() - stepper->move_start_time_us;
	uint32_t last_step_time = stepper->step_delay_us * stepper->steps_done;
	return time_passed - last_step_time >= stepper->step_delay_us;
}

void async_stepper_init(async_stepper_t* stepper, int steps, double rpm) {
	memset(stepper, 0, sizeof(async_stepper_t));
	stepper->steps_per_rev = steps;
	async_stepper_set_rpm(stepper, rpm);
}
