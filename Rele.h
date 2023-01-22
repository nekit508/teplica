#ifndef DSS_H
#define DSS_H

#include <Arduino.h>

class Rele {
public:
	Rele(uint8_t pin, bool lowed){
		_pin = pin;
		_lowed = lowed;
		pinMode(_pin, OUTPUT);
	}
	void on(){
		_enabled = true;
		digitalWrite(_pin, _lowed ? LOW : HIGH);
	}
	void off(){
		_enabled = false;
		digitalWrite(_pin, _lowed ? HIGH : LOW);
	}
	bool enabled(){
		return _enabled;
	}
	void sw(){
		if (_enabled)
			off();
		else
			on();
	}
private:
	uint8_t _pin;
	bool _enabled;
	bool _lowed;
};

#endif