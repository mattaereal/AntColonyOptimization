/*
 * Ant.cpp
 *
 *  Created on: Apr 30, 2014
 *      Author: matt
 */

#include "Ant.h"

Ant::Ant(unsigned int idN) {
	this->id = idN;
	this->tourLength = 0;
}

Ant::~Ant() {
}

void Ant::reset() {
	this->tourLength = 0;
	arcs.clear();
}

const list<Arc> & Ant::getTour() {
	return arcs;
}

void Ant::printTour() {
	list<Arc>::const_iterator it = arcs.begin();
	//cout << "Printing tour for ant #" << id << endl;
	while (it != arcs.end()) {
		cout << it->getR() << " - " << it->getS() << endl;
		it++;
	}

}

void Ant::pushArc(unsigned int r, unsigned int s) {
	pushArc(Arc(r,s));
}

void Ant::pushArc(Arc a) {
	//cout << "Pushing arc for ant #" << id << endl;
	//cout << a.getR() << " - " << a.getS() << endl;
	this->arcs.push_front(a);
}

void Ant::setTourL(double l) {
	this->tourLength = l;
}

void Ant::incTour(double i) {
	this->tourLength += i;
}

bool Ant::isArc(Arc a) {
	list<Arc>::iterator it = this->arcs.begin();
	while (it != arcs.end()) {
		if (*it == a)
			return true;
	it++;
	}

	return false;
}

bool Ant::isArc(unsigned int r, unsigned int s) {
	return this->isArc(Arc(r, s));
}

double Ant::getTourL() {
	return this->tourLength;
}

unsigned int Ant::getId() {
	return this->id;
}
