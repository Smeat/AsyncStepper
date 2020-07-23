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
	int steps_done;

	// space for 8x32bit
	uint8_t pins[32];
	// extra data for stepper specific implementations. e.g. sequence for cheap stepper
	uint8_t extra_data[4];

	void (*update)(void* stepper);
} async_stepper_t;

void async_stepper_update(async_stepper_t*);
void async_stepper_set_rpm(async_stepper_t* stepper, double);
void async_stepper_move(async_stepper_t* stepper, int steps);
int async_stepper_should_step(async_stepper_t* stepper);
void async_stepper_init(async_stepper_t* stepper, int steps, double rpm);



#endif  // __ASYNCSTEPPER__H_
