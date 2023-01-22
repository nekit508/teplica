#ifndef OS_H
#define OS_H

#include <Arduino.h>

template <uint8_t _size>
class OS{
public:
	void tick(){
		for(int i = 0; i < _size; i++){
			if(_delays[i] == 0) continue;
			if(millis() - _lastRuns[i] >= _delays[i]){
				_lastRuns[i] = millis();
				_tasks[i]();
			}
		}
	}
	
	void addTask(void (*task)(), uint16_t delay, uint8_t index){
		_tasks[index] = task;
		_delays[index] = delay;
	}
	
private:
	void (*_tasks[_size])();
	uint16_t _delays[_size];
	uint64_t _lastRuns[_size];
};

#endif