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
#include "StepperDriver.h"
#include "AsyncStepper.h"

#include <Arduino.h>
#include <cstdint>
#include <string.h>

#define STEP_STAY_US 50

typedef struct stepper_pins_s {
	uint32_t step;
	uint32_t dir;
	uint32_t on;
	uint32_t ms1;
	uint32_t ms2;
	uint32_t ms3;
} stepper_pins_t;

void stepper_get_pins(async_stepper_t* stepper, stepper_pins_t* pins) {
	memcpy(pins, stepper->pins, sizeof(stepper_pins_t));
}

int stepper_update(void* stepper_void) {
	async_stepper_t* stepper = (async_stepper_t*)stepper_void;

	uint32_t* last_step_us = (uint32_t*)stepper->extra_data;
	stepper_pins_t pins;
	stepper_get_pins(stepper, &pins);
	digitalWrite(pins.on, stepper->on ? LOW : HIGH);
	//Serial.printf("Last step %d (%d) direction %d Should step %d\n", *last_step_us, micros() - *last_step_us, stepper->on, async_stepper_should_step(stepper));
	if(*last_step_us != 0) {
		if(micros() - *last_step_us > STEP_STAY_US) {
			*last_step_us = 0;
			digitalWrite(pins.step, LOW);
			return stepper->steps_left > 0 ? 1 : -1;
		}
	} else if(async_stepper_should_step(stepper)) {
		digitalWrite(pins.dir, stepper->steps_left > 0);
		digitalWrite(pins.step, HIGH);
		*last_step_us = micros();
	}
}

void stepper_init(async_stepper_t* stepper, int steps, int rpm, int dir, int step, int on, int ms1, int ms2, int ms3) {
	Serial.println("Async init");
	async_stepper_init(stepper, steps, rpm);
	stepper_pins_t pins;
	pins.dir = dir;
	pins.step = step;
	pins.on = on;
	pins.ms1 = ms1;
	pins.ms2 = ms2;
	pins.ms3 = ms3;
	Serial.println("Setting outputs");
	pinMode(dir, OUTPUT);
	pinMode(step, OUTPUT);
	pinMode(on, OUTPUT);
	pinMode(ms1, OUTPUT);
	pinMode(ms2, OUTPUT);
	pinMode(ms3, OUTPUT);
	digitalWrite(on, LOW);
	digitalWrite(ms1, HIGH);
	digitalWrite(ms2, HIGH);
	digitalWrite(ms3, HIGH);
	memcpy(stepper->pins, &pins, sizeof(pins));
	stepper->update = stepper_update;
	Serial.println("Stepper init done");
}
