/*
 * Rail.h
 *
 *  Created on: 24 במאי 2020
 *      Author: Harel
 */

#ifndef RAIL_H_
#define RAIL_H_
#include "Vehicle.h"

class Rail : public Vehicle{
public:
	Rail(): Vehicle(5,"rail"){}
	virtual ~Rail();
};

#endif /* RAIL_H_ */
