/*
 * TSPSolver.cpp
 *
 *  Created on: Apr 23, 2014
 *      Author: matt
 */

#include "TSPSolver.h"
#include <cstdlib>
#include <ctime>
#include <list>
#include <math.h>
#include <iomanip>      // std::setprecision

TSPSolver::TSPSolver(double a, double b, double r, unsigned int k, unsigned int iters) {
	this->alpha = a;
	this->beta = b;
	this->ro = r;
	this->max_iters = iters;

	for (unsigned int i = 0; i < k; i++)
		ants.push_back(Ant(i));
}

TSPSolver::~TSPSolver() {
}

double TSPSolver::tau(unsigned int r, unsigned int s, Grafo<Ciudad> &g) {

	return g.getData(r, s).getPheromone();
}

double TSPSolver::eta(unsigned int r, unsigned int s, Grafo<Ciudad> &g) {

	return pow(g.getData(r, s).getCost(), -1);
}

double TSPSolver::taueta(unsigned int r, unsigned int s, Grafo<Ciudad> &g) {

	return pow(tau(r, s, g), getAlpha()) * pow(eta(r, s, g), getBeta());
}

double TSPSolver::sumPondered(unsigned int r, Grafo<Ciudad> &g, list<unsigned int> &pendings) {
	list<unsigned int>::iterator it = pendings.begin();
	double result = 0;

	while (it != pendings.end()) {
		result += taueta(r, *it, g);
		it++;
	}

	return result;
}

double TSPSolver::P(unsigned int r, unsigned int s, Grafo<Ciudad> &g,  list<unsigned int> &pendings) {
	double result = (taueta(r, s, g) / sumPondered(r, g, pendings));

	if (!isnan(result)) {
		return result;
	}

	return 0;
}

void TSPSolver::solveACO(Grafo<Ciudad> &g) {
	list<Ant>::iterator k;
	unsigned int startingCity;

	for(unsigned int iter = 0; iter < this->max_iters; iter++) {
		resetAnts();
		k = this->ants.begin();
		while (k != this->ants.end()) {
			startingCity = getRandomCity(g);
			makeTour(startingCity, g, *k);
			k++;
		}
		globalUpdate(g); //se hace ahora.
		getBestTourIter(g, iter);
	}

	getBestTour(g);
}

void TSPSolver::resetAnts() {
	list<Ant>::iterator k;
	k = this->ants.begin();

	while (k != this->ants.end()) {
		k->reset();
		k++;
	}
}

unsigned int TSPSolver::getRandomCity(Grafo<Ciudad> &g) {

	return (rand() % g.getSize());
}

void printList(list<unsigned int> &l) {
	list<unsigned int>::iterator it = l.begin();
	while (it != l.end()) {
		cout << *it << endl;
		it++;
	}
}


void TSPSolver::makeTour(unsigned int r, Grafo<Ciudad> &g, Ant &k) {
	unsigned int s;
	list<unsigned int> pendings = g.getAdjacents(r);

	while (pendings.size() > 1) {
		pendings.remove(r);
		s = stateTransition(r, g, pendings);
		localUpdate(r, s, g);
		k.pushArc(r, s);
		k.incTour(g.getData(r, s).getCost());

		r = s;
	}

}

void TSPSolver::globalUpdate(Grafo<Ciudad> &g) {
	list<unsigned int>l  = g.getNodes();
	list<unsigned int>::iterator it = l.begin();

	list<unsigned int> l2;
	list<unsigned int>::iterator it2;
	Ciudad c;
	double ph;

	while (it != l.end()) {
		l2 = g.getAdjacents(*it);
		it2 = l2.begin();
		while (it2 != l2.begin()) {
			if (g.existsNode(*it) && g.existsNode(*it2) && g.existsEdge(*it, *it2)) {
				c = g.getData(*it, *it2);
				ph = (1 - getRo()) * c.getPheromone();
				c.setPheromone(ph);
				c = g.getData(*it2, *it);
				ph = (1 - getRo()) * c.getPheromone();
				c.setPheromone(ph);
			}
			it2++;
		}
		it++;
	}
}

void TSPSolver::localUpdate(unsigned int r, unsigned int s, Grafo<Ciudad> &g) {
	Ciudad c;
	double ph;
	c = g.getData(r, s);

	ph = (1 - getRo()) * c.getPheromone() + delta(r, s);
	c.setPheromone(ph);

	c = g.getData(s, r);
	ph = (1 - getRo()) * c.getPheromone() + delta(s, r);
}


double TSPSolver::delta(unsigned int r, unsigned int s) {
	double result = 0;
	list<Ant>::iterator k = this->ants.begin();

	while (k != this->ants.end()) {
		if (k->isArc(r, s)) {
			result += (1/k->getTourL());
		}
		k++;
	}

	return result;
}

void TSPSolver::removeVisitedFromPendings(list<unsigned int> &visited, list<unsigned int> &pendings) {
	list<unsigned int>::iterator itl;
	itl = visited.begin();

	while (itl != visited.end()) {
		pendings.remove(*itl);
		itl++;
	}
}

void TSPSolver::getBestTour(Grafo<Ciudad> &g) {
	list<Arc> result;
	unsigned int s, r;
	list<unsigned int> cities, pendings, visited;
	double tourLength = 0;

	cities = g.getNodes();
	r = cities.front();

	while (cities.size() > 1) {
		pendings = g.getAdjacents(r);
		cities.remove(r);
		visited.push_front(r);
		removeVisitedFromPendings(visited, pendings);
		s = stateTransition(r, g, pendings);
		result.push_back(Arc(r, s));
		tourLength += g.getData(r, s).getCost();
		r = s;
	}

	visited.push_front(r);

	//printBestTourEdges(result);
	printBestTourVertex(visited);
	printTourLength(tourLength);
}

void TSPSolver::getBestTourIter(Grafo<Ciudad> &g, unsigned int const& iter) {
	getBestTour(g);
	cout << iter << endl; // Este va.

}
void TSPSolver::printBestTourEdges(list<Arc> const& result) {
	list<Arc>::const_iterator it = result.begin();
	while (it != result.end()) {
		cout << it->getR()+1 << ", " << it->getS()+1 << endl;
		it++;
	}
}

void TSPSolver::printBestTourVertex(list<unsigned int> const& visited) {
	list<unsigned int>::const_iterator it_n, it = visited.begin();
	cout << "[";
	it_n = visited.begin();
	it_n++;
	while (it_n++ != visited.end()) {
		cout << *it << ", ";
		it++;
	}
	cout << *it << "]" << endl;
}

void TSPSolver::printTourLength(double & tourLength) {
	cout << tourLength << endl;
}
void TSPSolver::printIterations(unsigned int const & iters) {
	cout << iters << endl;
}


void TSPSolver::pfy(unsigned int r, list<unsigned int> &pendings, list<CityP> &candidates, Grafo<Ciudad> &g) {
	list<unsigned int>::iterator it = pendings.begin();

	while (it != pendings.end()) {
		CityP cP(*it);
		cP.F = -1;
		cP.P = P(r, *it, g, pendings);
		candidates.push_front(cP);
		it++;
	}
}

void TSPSolver::ffy(list<CityP>& candidates) {
	list<CityP>::iterator itc = candidates.begin();
	list<CityP>::iterator aux;
	itc->F = itc->P;
	itc++;

	while (itc != candidates.end()) {
		aux = itc;
		itc--;
		aux-> F = aux->P + itc->F;
		itc = aux;
		itc++;
	}
}

unsigned int TSPSolver::nextCity(list<CityP> const& candidates) {
	list<CityP>::const_iterator itc = candidates.begin();
	double u = (double)rand() / RAND_MAX;
	itc = candidates.begin();
	while(itc != candidates.end()) {
		if (u <= itc->F) {
			return itc->id;
		}
		itc++;
	}

	return itc->id; //Este caso no debería ocurrir nunca, a menos que toque 1 y devuelva el último.
}

unsigned int TSPSolver::stateTransition(unsigned int r, Grafo<Ciudad> &g, list<unsigned int> &pendings) {
	list<CityP> candidates;

	pfy(r, pendings, candidates, g); // Prob para todos
	candidates.sort(); //Ordenar por mayor
	ffy(candidates); // FAcum para todos
	return nextCity(candidates);
}

double TSPSolver::getAlpha() const {
	return alpha;
}

double TSPSolver::getBeta() const {
	return beta;
}

double TSPSolver::getRo() const {
	return ro;
}
