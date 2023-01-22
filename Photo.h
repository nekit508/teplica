#ifndef PHOTO_H
#define PHOTO_H

#include <Arduino.h>

class Photo {
public:
	Photo(int8_t pin){
		this->pin = pin;
	}
	
	void begin(){
		pinMode(pin, INPUT);
	}
	
	float readSensor(){
		return (analogRead(pin)) / (float)1024;
	}
private:
	uint8_t pin;
};

#endif