/*
 * Arc.h
 *
 *  Created on: Apr 30, 2014
 *      Author: matt
 */

#ifndef ARC_H_
#define ARC_H_

class Arc {
public:
	Arc(unsigned int r, unsigned int s);
	virtual ~Arc();

	unsigned int getR() const;
	unsigned int getS() const;

	bool operator == (Arc a) {
		return ((this->r == a.r) && (this->s == a.s));
	}

private:
	unsigned int r;
	unsigned int s;

};

#endif /* ARC_H_ */
