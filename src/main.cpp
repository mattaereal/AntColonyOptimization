#include "classes/TSParse.h"
#include "classes/Grafo.h"
#include "classes/Ciudad.h"
#include "classes/Ant.h"
#include "classes/Arc.h"
#include "classes/TSPSolver.h"
#include "classes/Prim2opt.h"

/**
 * TODO:
 * - Soportar ambos ATSP/TSP sin necesidad de recompilar.
 * - Hacer más de un algoritmo, arrancar con el básico, leer paper INDRIA
 * - Multithreading? demasiado?
 * - Cambio de corte cuando convergen al mismo camino después de mucho tiempo.
 * - Const a Grafo<> & const
 * - Hormiga cambiar complejidad de búsqueda de arcos a O(1)
 * - Agregar city names?
 * - Levantar archivos
 * - Corregir complejidades.
 * - Agregar que solucione con Prim 2-opt via gui también.
 */


/**
 * Usually the termination condition is verified after a fixed
 * number of cycles, or when no improvement is obtained for a
 * fixed number of cycles.
 */

void TSPSolve(const char*, string);
void endSequence(unsigned int iters);

int main(int argc, char* argv[]) {
/**
	Main.
 */

	if (argc == 3) {
		TSPSolve(argv[1], argv[2]);

	} else {
		cout << "You must choose a TSP map." << endl;
		cout << "Usage: " << argv[0] << " eil51.tsp --nogui" << endl;
	}

	return 0;

}



void TSPSolve(const char* file, string gui) {
	srand (time(NULL));
	bool cont = false;
	double alpha, beta, ro, init_ph;
	unsigned int ants, iters;

	alpha = 10; //Pheromone weight
	beta = 10; //Distance weight
	ro = 0.1; //Decay
	ants = 40; //#Ants
	iters = 10; //#Iterations
	init_ph = 0.1; //Initial pheromone

	if (gui == (char* ) "--gui")
		do {
			ifstream lock_file("lock.txt");
			lock_file >> cont;
			lock_file.close();
		} while (!cont);

	TSParse parser;
	Grafo<Ciudad> grafito;
	parser.fileToGraph(file, grafito, init_ph);

	TSPSolver tsp(alpha, beta, ro, ants, iters);
	tsp.solveACO(grafito);
	endSequence(iters);

	Prim2opt p2opt;
	p2opt.TravelingSalesman(grafito, 1);

}

void endSequence(unsigned int iters) {
	cout << iters << endl;
	cout << "CONST_STOP" << endl;
}
