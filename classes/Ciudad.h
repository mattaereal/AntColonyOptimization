/*
 * Ciudad.h
 *
 *  Created on: Apr 23, 2014
 *      Author: matt
 */

#ifndef CIUDAD_H_
#define CIUDAD_H_

#include <string>

using namespace std;

class Ciudad {
private:
	double pheromone;
	double cost;
	string name;

public:
	Ciudad(double c, string n, double p);
	Ciudad();
	virtual ~Ciudad();

	double getCost() const;
	void setCost(double c);
	const string& getName() const;
	void setName(const string& n);
	double getPheromone() const;
	void setPheromone(double ph);
};

#endif /* CIUDAD_H_ */
