/*
 * TSParse.h
 *
 *  Created on: Apr 22, 2014
 *      Author: matt
 */

#ifndef TSPARSE_H_
#define TSPARSE_H_

#define TSP_BEGIN "NODE_COORD_SECTION"
#define TSP_SEPARATOR ": "

#include "Grafo.h"
#include "Ciudad.h"
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

typedef pair<string, string> header;
typedef pair<int, int> coord;

class TSParse {
public:
	TSParse();
	virtual ~TSParse();
	void fileToGraph(const char* tspfile, Grafo<Ciudad>& g, double init_ph); //r

private:
	void getHeaders(ifstream &file, vector<header> &headers);
	void showHeaders(vector<header> headers);
	void getCoordinates(ifstream &myfile, vector<coord> &ciudades); //r
	void fillGrafo(vector<coord> &ciudades, Grafo<Ciudad> &grafito, double init_ph); //r
	double getEuclidianDistance(coord p, coord q);
};



#endif /* TSPARSE_H_ */
