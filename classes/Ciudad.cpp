/*
 * Ciudad.cpp
 *
 *  Created on: May 3, 2014
 *      Author: matt
 */

#include "Ciudad.h"

Ciudad::Ciudad(double c, string n, double p) {
	this->pheromone = p;
	this->cost = c;
	this->name = n;
}

Ciudad::Ciudad() {
	this->cost = 0;
	this->pheromone = 0;
	this->name = "Undefined, please define city";
}

Ciudad::~Ciudad() {

}

double Ciudad::getCost() const {
	return cost;
}

void Ciudad::setCost(double c) {
	this->cost = c;
}

const string & Ciudad::getName() const {
	return name;
}

void Ciudad::setName(const string& n) {
	this->name = n;
}

double Ciudad::getPheromone() const {
	return pheromone;
}

void Ciudad::setPheromone(double ph) {
	this->pheromone = ph;
}

