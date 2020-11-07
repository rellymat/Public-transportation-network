/*
 * Vehicle.h
 *
 *  Created on: 24 במאי 2020
 *      Author: Harel
 */

#ifndef VEHICLE_H_
#define VEHICLE_H_
#include <iostream>
#include <memory>
using namespace std;

class Vehicle {
public:
	Vehicle(int time, string type){waiting = time; this->type=type;}
	int stopWaiting(){return waiting;}
	void setWaiting(int time){ waiting = time;}
	virtual ~Vehicle();

	const string& getType() const {
		return type;
	}

private:
	int waiting;
	string type;
};

#endif /* VEHICLE_H_ */
