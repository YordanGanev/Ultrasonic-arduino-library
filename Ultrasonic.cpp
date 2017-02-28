/*
* Ultrasonic.cpp
*
*  Created on: Nov 27, 2016
*      Author: danig_000
*/

#include "Arduino.h"
#include "Ultrasonic.h"

static int _us_initialized;

Ultrasonic::Ultrasonic(int trig_pin, int echo_pin, unsigned int max_dist) {
	_trig_pin = trig_pin;
	_echo_pin = echo_pin;
	_max_dist = min(max_dist, MAX_SENSOR_DISTANCE);
	_max_duration = _max_dist * CALCULATE_CM;
	
#ifdef SAFETY_FACTOR
	if(_max_dist < 100)
		_max_duration += _max_duration * 0.25;	
	else
		_max_duration += _max_duration * 0.15;
#endif /* SAFETY_FACTOR */

	//check for delcaration errors
	if (_trig_pin <= 0) {
		isStarted = false;
		return;
	}

	if (_echo_pin <= 0) {
		isStarted = false;
		return;
	}
	if (_max_duration == 0) {
		_max_duration = 32767; //MaxIntValue
		_max_dist = 32767;
	}
	pinMode(_trig_pin, OUTPUT);
	pinMode(_echo_pin, INPUT);
	_us_initialized += 1;
	isStarted = true;
}

int Ultrasonic::measure(void) {
	int dist;
	int duration;

	// Изходът trig  се вдига във високо ниво HIGH за 2 и повече микросекунди
	digitalWrite(_trig_pin, HIGH);
	delayMicroseconds(5);
	digitalWrite(_trig_pin, LOW);

	// Измерва се продължителността на импулса с високо ниво на пин echo.
	duration = pulseIn(_echo_pin, HIGH, _max_duration);

	// Преобразуване на измерения импулс в разстояние в сантиметри
	dist = (duration-5) / 29 / 2;
	
	if (dist > _max_dist)
		return 0;
	
	return dist;
}

bool Ultrasonic::started(void) {
	return isStarted;
}

void Ultrasonic::setTimeoutMicros(unsigned long micros) {
	if (micros == CALCULATE_CM*2)
		return;
	
	_max_duration = micros;
	_max_dist = micros / CALCULATE_CM;
}

void Ultrasonic::setTimeoutCM(unsigned int cm) {
	if (cm <= 0)
		return;

	_max_dist = cm;
	_max_duration = _max_dist * CALCULATE_CM;

#ifdef SAFETY_FACTOR
	if (_max_dist < 100)
		_max_duration += _max_duration * 0.25;
	else
		_max_duration += _max_duration * 0.15;
#endif /* SAFETY_FACTOR */
}

int us_initialized(void) {
	return _us_initialized;
}
