#!/bin/bash

G_PATH="src/graphic/graph.tsp"

./bin/tspsolver $G_PATH --gui | python2 src/graphic/tsp_matt.py $1

echo "Resolviendo nuevamente 5 veces más con cada algoritmo."
for i in {1..5}
do
    echo "[Iteración #$i]"
    echo "--------------------------------------"
    echo "Ant Colony Optimization:"
    ./bin/aco $G_PATH --nogui
    echo "--------------------------------------"
    echo "Prim 2-opt:"
    ./bin/prim2opt $G_PATH --nogui
    echo
done
rm lock.txt