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
#ifndef __ASYNCSTEPPER__H_
#define __ASYNCSTEPPER__H_

#include <stdint.h>

typedef struct async_stepper_s {
	// static config
	int steps_per_rev;
	// runtime config
	int step_delay_us;
	int on;

	// runtime info
	int steps_left;
	int move_start_time_us;
	/// we count the steps done (instead of last step time) to be able to catch up if the µC hangs or similar
	int steps_done;
	/// the current position. negative is ccw and positive cw
	int position;

	// space for 8x32bit
	uint8_t pins[32];
	// extra data for stepper specific implementations. e.g. sequence for cheap stepper
	uint8_t extra_data[4];

	int (*update)(void* stepper);
} async_stepper_t;

void async_stepper_update(async_stepper_t*);
void async_stepper_set_rpm(async_stepper_t* stepper, double);
void async_stepper_move(async_stepper_t* stepper, int steps);
int async_stepper_should_step(async_stepper_t* stepper);
void async_stepper_init(async_stepper_t* stepper, int steps, double rpm);



#endif  // __ASYNCSTEPPER__H_
