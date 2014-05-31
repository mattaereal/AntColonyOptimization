/*
 * Arc.cpp
 *
 *  Created on: Apr 30, 2014
 *      Author: matt
 */

#include "Arc.h"


Arc::Arc(unsigned int r, unsigned int s) {
	this->r = r;
	this->s = s;
}

Arc::~Arc() {
}

unsigned int Arc::getR() const {
	return r;
}

unsigned int Arc::getS() const {
	return s;
}
