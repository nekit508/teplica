#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include "SoilMois.h"
#include "OS.h"
#include "BTN.h"
#include "Rele.h"
#include "DHT.h"
#include "Photo.h"

/*
dht -> 19 bytes
*/

namespace DMF{
	class DHTData{
	public:
		DHTData(DHT *d){
			dht = d;
		}
		float h, t;
		DHT *dht;
		
		void read(){
			t = dht->readTemperature(false);
			h = dht->readHumidity();
		}
		
		float T(){
			return t;
		}
		
		float H(){
			return h;
		}
	};
	
	uint8_t dhtOpin, dhtIpin, photoOpin, photoIpin, btnLpin;
	
	OS<2> *os;
	
	float h, t;
	
	DHT *outsideDHT, *insideDHT;
	Photo *outsidePH, *insidePH;
	BTN *btnLogDHT;
	
	DHTData *outsideDHTData, *insideDHTData;
	
	void create(uint8_t dht1pin, uint8_t dht2pin, uint8_t photo1pin, uint8_t photo2pin, uint8_t btn1pin){
		dhtOpin = dht1pin;
		dhtIpin = dht2pin;
		photoOpin = photo1pin;
		photoIpin = photo2pin;
		btnLpin = btn1pin;
	}
	
	void checkDHTs(){
		outsideDHTData->read();
		insideDHTData->read();
	}
	
	void checkButtons(){
		btnLogDHT->checkButton();
		if (btnLogDHT)
	}
	
	void logDHT(){
		Serial.println("DHT log: t, h");
		Serial.print("outside: ");
		Serial.print(outsideDHTData->T());
		Serial.print(" ");
		Serial.println(outsideDHTData->H());
		Serial.print("inside: ");
		Serial.print(insideDHTData->T());
		Serial.print(" ");
		Serial.println(insideDHTData->H());
	}
	
	void init(){
		Serial.begin(9600);
		
		os = new OS<2>();
		
		outsideDHT = new DHT(dhtOpin, DHT11);
		insideDHT = new DHT(dhtIpin, DHT11);
		outsideDHTData = new DHTData(outsideDHT);
		insideDHTData = new DHTData(insideDHT);
		
		outsidePH = new Photo(photoOpin);
		insidePH = new Photo(photoIpin);
		
		btnLogDHT = new BTN(btnLpin);
		
		outsideDHT->begin();
		insideDHT->begin();
		
		btnLogDHT->init();
		
		os->addTask(checkDHTs, 2000, 0);
		os->addTask(checkButtons, 25, 1);
	}
	
	void tick(){
		os->tick();
	}
}	

#endif