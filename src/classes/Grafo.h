/*
 * Grafo.h
 *
 *  Created on: Apr 23, 2014
 *      Author: matt
 */

#ifndef GRAFO_H_
#define GRAFO_H_

#include <list>
#include <iostream>
#include <cassert>

using namespace std;

template<typename Data> class Grafo {
public:

	Grafo();
	~Grafo();

	void addVertex(unsigned int);
	void addEdge(unsigned int origen, unsigned int destino, Data dato);
	void addNonDirectionalEdge(unsigned int origen, unsigned int destino, Data costo);

	void removeNode(unsigned int);
	void removeEdge(unsigned int origen, unsigned int destino);
	void empty();
	void showGraph();

	unsigned int getSize();
	Data& getData(unsigned int origen, unsigned int destino);
	void getNodes(list<unsigned int>& vertices);
	list<unsigned int> getNodes();
	void getAdjacents(unsigned int vertice, list<unsigned int>& adjacents);
	list<unsigned int> getAdjacents(unsigned int vertice);

	bool isEmpty();
	bool existsEdge(unsigned int origen, unsigned int destino);
	bool existsNode(unsigned int ver);

private:
	struct adjacentNodes {
		unsigned int id;
		Data cost;
	};

	struct node {
		unsigned int id;
		list<adjacentNodes> adjacents;
	};

	list<node> graph;

	bool operator = (Grafo<int> &g) {
		if (this == &g)
			return *this;

		empty();

		list<unsigned int> v;
		g.getNodes(v);

		list<unsigned int>::iterator it = v.begin();

		while (it != v.end()) {
			addVertex(*it);
			list<unsigned int> a;
			g.getAdjacents(*it, a);

			list<unsigned int>::iterator itad = a.begin();

			while (itad != a.end()) {
				Data c = g.getData(*it, *itad);
				addNonDirectionalEdge(*it, *itad, c);
				itad++;
			}
			it++;
		}
		return *this;
	}

};

template<typename Data>
Grafo<Data>::Grafo() {
}

template<typename Data>
Grafo<Data>::~Grafo() {
	empty();
}

template<typename Data>
void Grafo<Data>::addVertex(unsigned int v) {
    if (!existsNode(v)) {
        node nuevo;
        nuevo.id = v;
        graph.push_back(nuevo);
    }
}

template<typename Data>
void Grafo<Data>::addEdge(unsigned int origen, unsigned int destino, Data dato) {
    if (!existsNode(origen))
        addVertex(origen);

    if (!existsNode(destino))
        addVertex(destino);

    if (existsEdge(origen, destino))
        return;

    typename list<node>::iterator it = graph.begin();

    while (it->id != origen)
        it++;

    adjacentNodes nuevo;
    nuevo.id = destino;
    nuevo.cost = dato;
    it->adjacents.push_back(nuevo);
}

template<typename Data>
void Grafo<Data>::addNonDirectionalEdge(unsigned int origen, unsigned int destino,
		Data costo) {
    addEdge(origen, destino, costo);
    addEdge(destino, origen, costo);
}

template<typename Data>
void Grafo<Data>::removeNode(unsigned int v) {
    if (!existsNode(v))
        return;

    typename list<node>::iterator it = graph.begin();

    while (it->id != v)
        it++;

    graph.erase(it);
}

template<typename Data>
void Grafo<Data>::removeEdge(unsigned int origen, unsigned int destino) {
    if (!existsEdge(origen, destino))
        return;

    typename list<node>::iterator it = graph.begin();

    while (it->id != origen)
        it++;

    typename list<adjacentNodes>::iterator itad = it->adjacents.begin();
    while (itad->id != destino)
        itad++;

    it->adjacents.erase(itad);
}

template<typename Data>
void Grafo<Data>::empty() {
    typename list<node>::iterator it = graph.begin();

    while (it != graph.end()) {
            it->adjacents.clear();
        it++;
    }

    graph.clear();
}

template<typename Data>
void Grafo<Data>::showGraph() {
    typename list<node>::iterator it = graph.begin();

    while (it != graph.end()) {
        cout << it->id << ": ";

        typename list<adjacentNodes>::iterator itad = it->adjacents.begin();

        while (itad != it->adjacents.end()) {
            cout << itad->id << " ";
            itad++;
        }

        cout << endl;

        it++;

    }
}

template<typename Data>
unsigned int Grafo<Data>::getSize() {
	return graph.size();
}

template<typename Data>
Data& Grafo<Data>::getData(unsigned int origen, unsigned int destino) {
    if ((!existsEdge(origen, destino)) || (!existsEdge(destino, origen))) {
        assert(0);
    }

    typename list<node>::iterator it = graph.begin();

    while (it->id != origen)
        it++;

    typename list<adjacentNodes>::iterator itad = it->adjacents.begin();
    while (itad->id != destino)
        itad++;

    return itad->cost;
}

template<typename Data>
void Grafo<Data>::getNodes(list<unsigned int>& vertices) {
    typename list<node>::iterator it = graph.begin();

    while (it != graph.end()) {
        vertices.push_back(it->id);
        it++;
    }
}

template<typename Data>
list<unsigned int> Grafo<Data>::getNodes() {
    list<unsigned int> nodes;
    getNodes(nodes);

    return nodes;
}

template<typename Data>
void Grafo<Data>::getAdjacents(unsigned int vertice, list<unsigned int>& adjacents) {
    if (!existsNode(vertice))
        return;

    typename list<node>::iterator it = graph.begin();

    while (it->id != vertice)
        it++;

    typename list<adjacentNodes>::iterator itad = it->adjacents.begin();

    while (itad != it->adjacents.end()) {
        adjacents.push_back(itad->id);
        itad++;
    }
}

template<typename Data>
list<unsigned int> Grafo<Data>::getAdjacents(unsigned int vertice) {
	list<unsigned int> adjacents;
	getAdjacents(vertice, adjacents);

	return adjacents;
}

template<typename Data>
bool Grafo<Data>::isEmpty() {
	return graph.empty();
}

template<typename Data>
bool Grafo<Data>::existsEdge(unsigned int origen, unsigned int destino) {
/*
 * Returns whether an edge exists or not.
 *
 * @origen Origin node.
 * @destino Destination node.
 *
 * @return true if the edge exists in the graph,
 * false otherwise.
 *
 */
    typename list<node>::iterator it = graph.begin();

    while (it != graph.end()) {
        if (it->id == origen) {
            typename list<adjacentNodes>::iterator itad = it->adjacents.begin();
            while(itad != it->adjacents.end()) {
                if (itad->id == destino)
                    return true;
                itad++;
            }

            return false;
        }

        it++;
    }

    return false;
}

template<typename Data>
bool Grafo<Data>::existsNode(unsigned int ver) {
/*
 * Returns whether a nodes exists or not.
 *
 * @ver node.
 *
 * @return true if the node exists in the graph,
 * false otherwise.
 *
 */
    typename list<node>::iterator it = graph.begin();

    while (it != graph.end()) {
        if (it->id == ver) {
                return true;
        }

        it++;
    }

    return false;
}

#endif /* GRAFO_H_ */
