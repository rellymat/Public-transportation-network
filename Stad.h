/*
 * Stad.h
 *
 *  Created on: 24 במאי 2020
 *      Author: Harel
 */

#ifndef STAD_H_
#define STAD_H_
#include "Station.h"

class Stad: public Station {
private:
	shared_ptr<Station> mainStation;
public:
	Stad(): Station(5,"stad","") {}
	Stad(string name): Station(5,"stad",name) {}
	Stad(shared_ptr<Station>& rhs, string name){
		mainStation = rhs;
		setName(name);
	}
	int stopWaiting() {return mainStation.get()->Station::stopWaiting();}
	virtual ~Stad();
};

#endif /* STAD_H_ */
