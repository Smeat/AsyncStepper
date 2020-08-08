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
#include <Arduino.h>

#include "AsyncStepper.h"
#include "StepperDriver.h"


async_stepper_t async_stepper;
void setup() {
	Serial.begin(115200);
	Serial.println("Starting init");
	stepper_init(&async_stepper, 200*16, 4.687, D1, D2, D5, D6, D7, D0);
	Serial.printf("Init done with step delay %d\n", async_stepper.step_delay_us);
	async_stepper_move(&async_stepper, 999999999);
	Serial.println("Setup done");
}


void loop() {
	//Serial.printf("Done %d steps\n", async_stepper.steps_done);
	async_stepper_update(&async_stepper);
}
