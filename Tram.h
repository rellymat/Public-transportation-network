/*
 * Tram.h
 *
 *  Created on: 24 במאי 2020
 *      Author: Harel
 */

#ifndef TRAM_H_
#define TRAM_H_
#include "Vehicle.h"

class Tram : public Vehicle {
public:
	Tram(): Vehicle(2,"tram"){}
	virtual ~Tram();
};

#endif /* TRAM_H_ */
