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
#include "UnipolarDriver.h"
#include "AsyncStepper.h"

#include <Arduino.h>
#include <cstdint>
#include <string.h>

typedef struct unipolar_pins_s {
	uint32_t pins[4];
} unipolar_pins_t;

int unipolar_update(void* stepper_void) {
	async_stepper_t* stepper = (async_stepper_t*) stepper_void;
	if(async_stepper_should_step(stepper) && stepper->on) {
		const uint8_t pattern[4] = {
			0b10000011,
			0b00111000,
			0b00001110,
			0b11100000
		};
		uint8_t* step_mask = stepper->extra_data;
		unipolar_pins_t pins;
		memcpy(&pins, stepper->pins, sizeof(pins));

		// write pattern to pins
		for (int i = 0; i < 4; ++i) {
			digitalWrite(pins.pins[i], pattern[i] & *step_mask);
		}
		
		// prepare the bitmask for the next step
		if (stepper->steps_left > 0){
			*step_mask <<= 1;
			if (*step_mask == 0) *step_mask = 0b00000001;
			return -1;
		} else if (stepper->steps_left < 0) {
			*step_mask >>= 1;
			if (*step_mask == 0) *step_mask = 0b10000000;
			return 1;
		}
	}
	// Disable the motor if on is false
	if(!stepper->on) {
		uint8_t* step_mask = stepper->extra_data;
		unipolar_pins_t pins;
		memcpy(&pins, stepper->pins, sizeof(pins));
		for (int i = 0; i < 4; ++i) {
			digitalWrite(pins.pins[i], 0);
		}
	}
	return 0;
}

void unipolar_init(async_stepper_t* stepper, int steps, int rpm, int pin1, int pin2, int pin3, int pin4) {
	async_stepper_init(stepper, steps, rpm);
	unipolar_pins_t pins;
	pins.pins[0] = pin1;
	pins.pins[1] = pin2;
	pins.pins[2] = pin3;
	pins.pins[3] = pin4;
	for(int i = 0; i < 4; ++i) {
		pinMode(pins.pins[i], OUTPUT);
		digitalWrite(pins.pins[i], LOW);
	}
	memcpy(stepper->pins, &pins, sizeof(pins));
	stepper->update = unipolar_update;
}
