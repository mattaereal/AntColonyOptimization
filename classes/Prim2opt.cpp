/*
 * Prim2opt.cpp
 *
 *  Created on: May 9, 2014
 *      Author: matt
 */

#include "Prim2opt.h"

#define INFINITE 9999

typedef pair<unsigned int, unsigned int> ui_ui;

using namespace std;

Prim2opt::Prim2opt() {

}

Prim2opt::~Prim2opt() {
}

Grafo<unsigned int> Prim2opt::getPrim(Grafo<Ciudad> &g, unsigned int vertice) {
	unsigned int N = g.getSize();
	int root[N];
	unsigned int distance[N];
	unsigned int visited[N];

	for (unsigned int i = 0; i < N; i++) {
		distance[i] = INFINITE;
		root[i] = -1;
		visited[i] = 0;
	}

	priority_queue <ui_ui, vector<ui_ui>, greater<ui_ui> > pq;
	distance[vertice] = 0;
	pq.push(ui_ui(0, vertice));
	while (!pq.empty()){
		unsigned int aux = pq.top().second;
		pq.pop();
		if (visited[aux] == 1)
			continue;
		visited[aux] = 1;
		list<unsigned int> adj;
		g.getAdjacents(aux, adj);
		list<unsigned int>::iterator it = adj.begin();
		while (it != adj.end()){
			unsigned int dist = g.getData(aux, *it).getCost();
			if (dist < distance[*it] && !visited[*it]){
				distance[*it] = dist;
				root[*it] = aux;
				pq.push(ui_ui(dist,*it));
			}

			it++;
		}
	}

	Grafo<unsigned int> mst = getMinimumSpanningTree(root, distance, N, vertice);
	return mst;

}

Grafo<unsigned int> Prim2opt::getMinimumSpanningTree(int raiz[], unsigned int costo[], unsigned int N, unsigned int r) {
    Grafo<unsigned int> g;

    for (unsigned int i = 1; i < N; i++) {
        g.addVertex(i);
    }
    for (unsigned int i = 1; i < N; i++) {
        if (i != r)
            g.addNonDirectionalEdge(i, raiz[i], costo[i]);
    }

    return g;
}

void Prim2opt::printList(list<unsigned int> &l) {

    list<unsigned int>::const_iterator it = l.begin();
    while ( it != l.end()) {
	cout << *it << " ";
        it++;
    }
}

void Prim2opt::preorderTreeWalk(Grafo<unsigned int> &g, unsigned int v, unsigned int visited[], list<unsigned int> &S) {
    visited[v] = 1;
    S.push_back(v);
    list<unsigned int> adj;
    g.getAdjacents(v, adj);
    list<unsigned int>::iterator it = adj.begin();

    while(it != adj.end()) {
        if(!visited[*it]){
            preorderTreeWalk(g, *it, visited, S);
        }
        it++;
    }
}

unsigned int Prim2opt::getTourCost(Grafo<Ciudad> &g, list<unsigned int> &L) {
    unsigned int tourCost = 0;
    list<unsigned int>::iterator it = L.begin();
    list<unsigned int>::iterator itant = it;
    it++;

    while ( it != L.end()) {
    	if (*itant != *it) {
			tourCost += g.getData(*itant, *it).getCost();
			itant = it;
    	}
    	it++;
    }
    return tourCost;
}



void Prim2opt::TravelingSalesman(Grafo<Ciudad> &g, unsigned int r) {
    unsigned int visited[g.getSize()];
    for (unsigned int i = 0; i <= g.getSize(); i++)
    	visited[i] = 0;

    Grafo<unsigned int> T = getPrim(g, 0);
    list<unsigned int> L;
    preorderTreeWalk(T, r, visited, L);
    //L.push_back(r); Eso por si se quiere hacer realmente hamiltoniano.
    localSearch(g, L);
    printList(L);
    cout <<" - ";
    cout << getTourCost(g, L) << endl;

}

void Prim2opt::localSearch(Grafo<Ciudad> &g, list<unsigned int> &L) {
	list<unsigned int> auxList = L;

	unsigned int initialCost = getTourCost(g, L);
	unsigned int random1, random2;
	unsigned int maxx, minx;

	for(unsigned int i = 0; i < g.getSize()*200; i++) {


		random1 = rand() % auxList.size();
		if(random1 <= 0) random1++;
		if(random1 > (auxList.size()-2)) random1--;


		random2 = rand() % auxList.size();
		if(random2 <= 0) random2++;
		if(random2 > (auxList.size()-2)) random2--;

		list<unsigned int>::iterator it = auxList.begin();
		list<unsigned int>::iterator it2 = auxList.begin();

		maxx = max(random1, random2);
		minx = min(random1, random2);

		advance(it, minx);
		advance(it2, maxx);

		list<unsigned int> rev (it, it2);
		rev.reverse();

		list<unsigned int> temp (auxList.begin(), it);
		temp.splice(temp.end(), rev);
		temp.splice(temp.end(), auxList, it2, auxList.end());
		auxList = temp;

		if(getTourCost(g, auxList) < initialCost){
			initialCost = getTourCost(g, auxList);
			L = auxList;
		} else {
			auxList = L;
		}
	}
}
