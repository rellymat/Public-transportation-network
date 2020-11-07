/*
 * Sprinter.h
 *
 *  Created on: 24 במאי 2020
 *      Author: Harel
 */

#ifndef SPRINTER_H_
#define SPRINTER_H_
#include "Vehicle.h"

class Sprinter : public Vehicle {
public:
	Sprinter(): Vehicle(3,"sprinter"){}
	virtual ~Sprinter();
};

#endif /* SPRINTER_H_ */
