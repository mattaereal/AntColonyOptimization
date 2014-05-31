/*
 * CityP.h
 *
 *  Created on: May 3, 2014
 *      Author: matt
 */

#ifndef CITYP_H_
#define CITYP_H_

class CityP {
public:
	unsigned int id;
	double F;
	double P;

	CityP(unsigned int id);
	virtual ~CityP();

	bool operator<(CityP const& a) const {
		return this->P > a.P;
	}

};

#endif /* CITYP_H_ */
