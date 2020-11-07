/*
 * Bus.h
 *
 *  Created on: 24 במאי 2020
 *      Author: Harel
 */

#ifndef BUS_H_
#define BUS_H_
#include "Vehicle.h"

class Bus: public Vehicle {
public:
	Bus() : Vehicle(1,"bus"){}
	virtual ~Bus();
};

#endif /* BUS_H_ */
