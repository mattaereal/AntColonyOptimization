/*
 * TSParse.cpp
 *
 *  Created on: Apr 22, 2014
 *      Author: matt
 */

#include "TSParse.h"


TSParse::TSParse() {
}

TSParse::~TSParse() {
}

void TSParse::fileToGraph(const char* tspmap, Grafo<Ciudad>& g, double init_ph) {
/*
 * Opens a *.tsp filetype and fills a desired Graph with its data.
 *
 */

	ifstream tspmap_file(tspmap);
	vector<header> headers;
	vector<coord> ciudades;

	if (tspmap_file.is_open()) {
		getHeaders(tspmap_file, headers);
		//showHeaders(headers);
		getCoordinates(tspmap_file, ciudades);
		tspmap_file.close();
		fillGrafo(ciudades, g, init_ph);
	} else {
		cout << "The file could not be opened. Choose a valid TSP map." << endl;
	}
}

void TSParse::getHeaders(ifstream &file, vector<header> &headers) {
/**
 * Gathers current TSP map headers and keeps them in a vector.
 */

	string line;
	while (file.good() && getline (file, line) && line != TSP_BEGIN) {
		int pos = line.find(TSP_SEPARATOR);
		if (pos >= 0) {
			string name = line.substr(0, pos);
			string content = line.substr(pos+2, line.size()-pos);
			headers.push_back(make_pair(name, content));
	  	}
  }
}

void TSParse::showHeaders(vector<header> headers) {
/**
 *	Shows current headers in output.
 *
 */

	for (unsigned int i = 0; i < headers.size(); i++) {
		cout << headers[i].first << ": " << headers[i].second << endl;
	}
}

void TSParse::getCoordinates(ifstream &myfile, vector<coord> &ciudades) {
/**
 *	Gathers the coordinates from the file and pushes them into a vector
 *	which has a Pair of integers, corresponding to each coordinate (x,y).
 */
	string line;

	while (myfile.good() && getline (myfile,line) && line != "EOF") {
		string::size_type first = line.find (' ');
		string::size_type second = line.rfind (' ');

		string xs = (line.substr(first+1, second-first));
		string ys = (line.substr(second+1));

		int x = atoi(xs.c_str());
		int y = atoi(ys.c_str());

		ciudades.push_back(make_pair(x, y));
	}
}

void TSParse::fillGrafo(vector<coord> &ciudades, Grafo<Ciudad> &grafito, double init_ph) {
/**
 *	Fills a graph structure with the euclidian distance between
 *	given coordinates in format of a vector with a pair of integers.
 *
 */
	for (unsigned int i = 0; i < ciudades.size(); i++) {
		for (unsigned int j = 0; j < ciudades.size(); j++) {
			if (i != j) {
				double costo = getEuclidianDistance(ciudades[i], ciudades[j]);
				Ciudad tmp(costo, "Unknown", init_ph);//Agregar nombre de la ciudad en caso de que sea necesario?
				grafito.addNonDirectionalEdge(i, j, tmp);
			}
		}
	}
}

double TSParse::getEuclidianDistance(coord p, coord q) {
/**
 * Returns Euclidian distance between two coordinates.
 *
 */
	return sqrt(pow(p.first - q.first , 2) + pow(p.second - q.second, 2));
}

