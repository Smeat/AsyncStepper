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
