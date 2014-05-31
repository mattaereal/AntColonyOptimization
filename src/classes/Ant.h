/*
 * Ant.h
 *
 *  Created on: Apr 30, 2014
 *      Author: matt
 */

#ifndef ANT_H_
#define ANT_H_

#include <list>
#include "Arc.h"
#include <iostream>

using namespace std;

class Ant {
private:
	unsigned int id;

	list<Arc> arcs;
	double tourLength;

public:
	Ant(unsigned int id);
	virtual ~Ant();

	void pushArc(unsigned int r, unsigned int s); //r
	void pushArc(Arc a);
	void setTourL(double l);
	void incTour(double i);
	void reset();
	void printTour();

	bool isArc(Arc a);
	bool isArc(unsigned int r, unsigned int s); //r

	double getTourL();
	unsigned int getId();
	const list<Arc> & getTour();



};

#endif /* ANT_H_ */
