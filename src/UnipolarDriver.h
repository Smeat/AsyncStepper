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
#ifndef __UNIPOLARDRIVER__H__
#define __UNIPOLARDRIVER__H__

#include <stdint.h>
#include "AsyncStepper.h"

int unipolar_update(void* stepper);
void unipolar_init(async_stepper_t* stepper, int steps, int rpm, int pin1, int pin2, int pin3, int pin4);


#endif  // __STEPPERDRIVER__H__
