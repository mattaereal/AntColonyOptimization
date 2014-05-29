#!/bin/bash

./tspsolver graph.tsp --gui | python2 graphic/tsp_matt.py $1

echo "Resolviendo nuevamente 5 veces más con cada algoritmo."
for i in {1..5}
do
    echo "[Iteración #$i]"
    echo "--------------------------------------"
    echo "Ant Colony Optimization:"
    ./aco graph.tsp --nogui
    echo "--------------------------------------"
    echo "Prim 2-opt:"
    ./prim2opt graph.tsp --nogui
    echo
done