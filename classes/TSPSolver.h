/*
 * TSPSolver.h
 *
 *  Created on: Apr 23, 2014
 *      Author: matt
 */

#ifndef TSPSOLVER_H_
#define TSPSOLVER_H_

#include "Grafo.h"
#include "Ciudad.h"
#include "Ant.h"
#include "CityP.h"

/**
 *  A TSPSolver class. It solves the TSP using ACS metaheuristics.
 */

class TSPSolver {
public:
    /**
     * A constructor.
     * @param a Alpha number, regulates the relevante of pheromone in a trail.
     * @param b Beta number, regulates the relevance of the distance in a trail.
     * @param k Ant quantity.
     * @param iters Numbers of expected iterations.
     */
	TSPSolver(double a, double b, double r, unsigned int k, unsigned int iters);

    /**
     * A simple constructor.
     */
	virtual ~TSPSolver();

    /**
     * Tries to find the optimum tour between city nodes from a graph.
     * @param g City graph.
     */
	void solveACO(Grafo<Ciudad> &g); //r



private:
	double alpha;
	double beta;
	double ro;
	unsigned int max_iters;

	list<Ant> ants;

    /**
     * Takes 2 cities and returns the pheromone amount between them.
     * @param r City r.
     * @param s City s.
     * @return Pheromone between 2 cities.
     */
	double tau(unsigned int r, unsigned int s, Grafo<Ciudad> &g);

    /**
     * Takes 2 cities and returns the pheromone amount between them.
     * @param r City r.
     * @param s City s.
     * @return Pheromone between 2 cities.
     */
	double eta(unsigned int r, unsigned int s, Grafo<Ciudad> &g);

    /**
     * Algo.
     * @param a algo.
     * @return algo.
     */
	double taueta(unsigned int r, unsigned int s, Grafo<Ciudad> &g);

    /**
     * Algo.
     * @param a algo.
     * @return algo.
     */
	double sumPondered(unsigned int r, Grafo<Ciudad> &g, list<unsigned int> &pendings); //r

    /**
     * Algo.
     * @param a algo.
     * @return algo.
     */
	double P(unsigned int r, unsigned int s, Grafo<Ciudad> &g, list<unsigned int> &pendings);

    /**
     * Algo.
     * @param a algo.
     * @return algo.
     */
	double delta(unsigned int r, unsigned int s);

    /**
     * Algo.
     * @param a algo.
     * @return algo.
     */
	unsigned int getRandomCity(Grafo<Ciudad> &g);

    /**
     * Algo.
     * @param a algo.
     * @return algo.
     */
	unsigned int stateTransition(unsigned int r, Grafo<Ciudad> &g, list<unsigned int> &pendings);

    /**
     * Algo.
     * @param a algo.
     * @return algo.
     */
	unsigned int nextCity(list<CityP> const& candidates);

    /**
     * Algo.
     * @param a algo.
     * @return algo.
     */
	void makeTour(unsigned int r, Grafo<Ciudad> &g, Ant &k);

    /**
     * Algo.
     * @param a algo.
     * @return algo.
     */
	void pfy(unsigned int r, list<unsigned int> &pendings, list<CityP> &candidates, Grafo<Ciudad> &g);

    /**
     * Algo.
     * @param a algo.
     * @return algo.
     */
	void getBestTour(Grafo<Ciudad> &g); //r

    /**
     * Algo.
     * @param a algo.
     * @return algo.
     */
	void localUpdate(unsigned int r, unsigned int s, Grafo<Ciudad> &g); //r

    /**
     * Algo.
     * @param a algo.
     * @return algo.
     */
	void globalUpdate(Grafo<Ciudad> &g); //r

    /**
     * Algo.
     * @param a algo.
     * @return algo.
     */
	void resetAnts();

    /**
     * Algo.
     * @param a algo.
     * @return algo.
     */
	void ffy(list<CityP>& candidates);

    /**
     * Algo.
     * @param a algo.
     * @return algo.
     */
	void removeVisitedFromPendings(list<unsigned int> &visited, list<unsigned int> &pendings);

    /**
     * Algo.
     * @param a algo.
     * @return algo.
     */
	void printBestTourEdges(list<Arc> const& result);

    /**
     * Algo.
     * @param a algo.
     * @return algo.
     */
	void printBestTourVertex(list<unsigned int> const& visited);

    /**
     * Algo.
     * @param a algo.
     * @return algo.
     */
	void printTourLength(double & tourLength);

    /**
     * Algo.
     * @param a algo.
     * @return algo.
     */
	void printIterations(unsigned int const & iters);

    /**
     * Algo.
     * @param a algo.
     * @return algo.
     */
	void getBestTourIter(Grafo<Ciudad> &g, unsigned int const& iter);

    /**
     * Algo.
     * @param a algo.
     * @return algo.
     */
	double getAlpha() const;

    /**
     * Algo.
     * @param a algo.
     * @return algo.
     */
	double getBeta() const;

    /**
     * Algo.
     * @param a algo.
     * @return algo.
     */
	double getRo() const;

};

#endif /* TSPSOLVER_H_ */
