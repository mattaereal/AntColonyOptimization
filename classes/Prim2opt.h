/*
 * Prim2opt.h
 *
 *  Created on: May 9, 2014
 *      Author: matt
 */

#ifndef PRIM2OPT_H_
#define PRIM2OPT_H_

#include "Grafo.h"
#include "Ciudad.h"
#include <iostream>
#include <queue>
#include <math.h>
#include <stdlib.h>
#include <time.h>

class Prim2opt {
private:
	void printList(list<unsigned int> &l);
	Grafo<unsigned int> getPrim(Grafo<Ciudad> &g, unsigned int vertex);
	Grafo<unsigned int> getMinimumSpanningTree(int raiz[], unsigned int cost[], unsigned int N, unsigned int r);
	void preorderTreeWalk(Grafo<unsigned int> &g, unsigned int v, unsigned int visited[], list<unsigned int> &S);
	unsigned int getTourCost(Grafo<Ciudad> &g, list<unsigned int> &L);
	void localSearch(Grafo<Ciudad> &g, list<unsigned int> &L);

public:
	Prim2opt();
	virtual ~Prim2opt();

	void TravelingSalesman(Grafo<Ciudad> &g, unsigned int r);

};

#endif /* PRIM2OPT_H_ */
