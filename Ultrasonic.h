/*
 * ultrasonic_lib.h
 *
 *  Created on: Nov 27, 2016
 *      Author: danig_000
 *		About: Arduino Nontimer Ultrasonic lib
 */

#ifndef ULTRASONIC_LIB_H_
#define ULTRASONIC_LIB_H_

#include "Arduino.h"

#define MAX_SENSOR_DISTANCE 450
#define CALCULATE_CM		58

#define	SAFETY_FACTOR		// for exact measurements at close to max dist values

class Ultrasonic {
	
	public:
		//Declarates Ultrasonic object. Can set maximum distance to be measured if needed. 
		Ultrasonic(int trig_pin, int echo_pin, unsigned int max_dist = MAX_SENSOR_DISTANCE); 


		//Mid program (after delcaration) can set maximum micros to wait the sonic wave to come back.
		void setTimeoutMicros(unsigned long micros);	//*1000 micros = 1millis and 58 micros ~= 1 cm

		//Mid program (after delcaration) can set maximum distance in cm to wait the sonic wave to come back.
		void setTimeoutCM(unsigned int cm);		//*lowering the range of the measure makes it faster.
		

		int measure(void);			//Returns the value read from sensor in CM.
		int measureMicros(void);	//Returns the value read from sensor in MICROS.

    bool started(void);				//Returns true if declarated correctly.


	private:
		int _trig_pin;
		int _echo_pin;
		int _max_dist;
		long _max_duration;
    bool isStarted;
};

int us_initialized(void);


#endif /* ULTRASONIC_LIB_H_ */
