#ifndef BTN_H
#define BTN_H

#include <Arduino.h>

class BTN{
public:
    BTN(uint8_t p){
		_pin = p;
	}
    void checkButton(){
		uint8_t digital = digitalRead(_pin);
		if (digital == 0) {
			if (_state == 0) {
				_lastClick = millis();
				checkedState = false;
				_state = 1;
			}else if (_state == 1) {
				if (millis() - _lastClick >= _holdCooldown) {
					checkedState = false;
					_state = 2;
				}
			}
		} else if (digital == 1) {
			if (_state != 0) {
				checkedState = false;
				_state = 0;
			}
		}
	}
    void init(){
		pinMode(_pin, INPUT_PULLUP);
		_state = 0;
		_holdCooldown = 300;
	}
	
	bool available(){
		return !checkedState;
	}

    bool isClicked(){
		checkedState = true;
		return _state == 1;
	}
	
    bool isHeld(){
		checkedState = true;
		return _state == 2;
	}
	
	uint8_t getState(){
		checkedState = true;
		return _state;
	}
	
    uint8_t _pin;
	uint16_t _holdCooldown;
private:
    uint64_t _lastClick;
	uint8_t _state;
	
	bool checkedState = false;
};

#endif