/*
 * Intercity.h
 *
 *  Created on: 24 במאי 2020
 *      Author: Harel
 */

#ifndef INTERCITY_H_
#define INTERCITY_H_
#include "Station.h"

class Intercity : public Station {
private:
	shared_ptr<Station> mainStation;
public:
	Intercity() : Station(15,"intercity", ""){}
	Intercity(string name) : Station(15,"intercity", name){}
	Intercity(shared_ptr<Station>& rhs, string name){
		mainStation = rhs;
		setName(name);
	}
	int stopWaiting() {return mainStation.get()->Station::stopWaiting();}
	virtual ~Intercity();
};

#endif /* INTERCITY_H_ */
