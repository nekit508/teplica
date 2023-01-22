#ifndef SOILMOIS_H
#define SOILMOIS_H

#include <Arduino.h>

class SoilMoisture {
public:
	SoilMoisture(uint8_t pin){
		_pin = pin;
		pinMode(pin, INPUT_PULLUP);
	}
	
	float check(){
		return (1024 - analogRead(_pin)) / (float)1024;
	}
private:
	uint8_t _pin;
};

#endif