/*
 * Centraal.h
 *
 *  Created on: 24 במאי 2020
 *      Author: Harel
 */

#ifndef CENTRAAL_H_
#define CENTRAAL_H_
#include "Station.h"

class Centraal: public Station {
private:
	shared_ptr<Station> mainStation;
public:
	Centraal() : Station(10,"centraal",""){}
	Centraal(string name) : Station(10,"centraal",name){}
	Centraal(shared_ptr<Station>& rhs, string name){
		mainStation = rhs;
		setName(name);
	}
	int stopWaiting() {return mainStation.get()->Station::stopWaiting();}
	virtual ~Centraal();
};

#endif /* CENTRAAL_H_ */
