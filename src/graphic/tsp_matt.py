#!/usr/bin/env python2
# -*- encoding: utf-8 -*-
#
#   This script was originally made by Alessandro Presta, and was modified
#   by Matías A. Ré Medina in order to satisfy his needs.
#
#   This library is free for commercial and non-commercial use as long as
#   the following conditions are aheared to. The following conditions 
#   apply to all code found in this distribution, be it the library itself
#   or the included examples. All the documentation included with this 
#   distribution is covered by the same copyright terms.
#   
#   Copyright remains Alessandro Presta's, and as such any Copyright 
#   notices in the code are not to be removed.
#   If this package is used in a product, Alessandro Presta should be 
#   given attribution as the author of the parts of the library used.
#   This can be in the form of a textual message at program startup or
#   in documentation (online or textual) provided with the package.
#
#   Redistribution and use in source and binary forms, with or without
#   modification, are permitted provided that the following conditions
#   are met:
#   1. Redistributions of source code must retain the copyright
#      notice, this list of conditions and the following disclaimer.
#   2. Redistributions in binary form must reproduce the above copyright
#      notice, this list of conditions and the following disclaimer in the
#      documentation and/or other materials provided with the distribution.
#   3. All advertising materials mentioning features or use of this software
#      must display the following acknowledgement:
#      "This product includes the Fast Genetic Algorithm library written by
#      Alessandro Presta (alessandro.presta@gmail.com)"
#
#   THIS SOFTWARE IS PROVIDED BY ALESSANDRO PRESTA ``AS IS'' AND
#   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
#   ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
#   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
#   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
#   OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
#   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
#   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
#   OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
#   SUCH DAMAGE.
# 
#   The licence and distribution terms for any publically available version or
#   derivative of this code cannot be changed.  i.e. this code cannot simply be
#   copied and put under another distribution licence
#   (including the GNU Public Licence).

import pygame
import sys, os
import numpy as np


CURR_DIR = os.path.dirname(os.path.realpath(__file__))
CONST_LOCK_FILE = "lock.txt"
CONST_GRAPH_FILE = "%s/graph.tsp" % CURR_DIR
CONST_STOP = "STOP"
CONST_CUSTOM_FILE = None



def main():
    pygame.init()
    screen = pygame.display.set_mode((700,700))
    screen.fill((255,255,255))
    pygame.display.set_caption("Ant Colony TSP Solver - press ENTER to solve")
    graph = []
    tour = []
    cost = g = 0
    state = 0
    pygame.display.flip()
    while (True):
        for event in pygame.event.get():
            if event.type == pygame.QUIT or (event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE):
                sys.exit()
            elif event.type == pygame.MOUSEBUTTONDOWN and state == 0 and CONST_CUSTOM_FILE:
                #print "Agregando la posición del click", pygame.mouse.get_pos()
                data = np.loadtxt(CONST_CUSTOM_FILE, dtype=int, delimiter=',')
                for line in data:
                    line = (line[0]*7, line[1]*7)
                    graph.append(line)
                    pygame.draw.circle(screen, (0,0,0), line, 5, 0)
                pygame.display.flip()
            elif event.type == pygame.MOUSEBUTTONDOWN and state == 0:
                #print "Agregando la posición del click", pygame.mouse.get_pos()
                graph.append(pygame.mouse.get_pos())
                pygame.draw.circle(screen, (0,0,0), pygame.mouse.get_pos(), 5, 0)
                pygame.display.flip()
            elif event.type == pygame.KEYDOWN and event.key == pygame.K_RETURN:
                lock_file = open(CONST_LOCK_FILE, "w")
                lock_file.write("0");
                lock_file.close()    

                graph_file = open(CONST_GRAPH_FILE, "w")
                graph_file.write("NAME : %s\n" % CONST_GRAPH_FILE)
                graph_file.write("COMMENT : %s-city problem\n" % str(len(graph)))
                graph_file.write("TYPE : TSP\n")
                graph_file.write("DIMENSION : %s\n" % str(len(graph)))
                graph_file.write("EDGE_WEIGHT_TYPE : EUC_2D\n")
                graph_file.write("NODE_COORD_SECTION\n") 

                for x in range(0, len(graph)):
                    #print "%d %d %d" % (x, graph[x][0], graph[x][1])
                    graph_file.write("%d %d %d" % (x, graph[x][0], graph[x][1]))
                    graph_file.write("\n")
                graph_file.write("EOF")
                graph_file.close()

                lock_file = open("lock.txt", "w")
                lock_file.write("1");
                lock_file.close()

                # Primera salida.
                tour = input() # [0, .., n-1, n]
                cost = input() # Costo del recorrido
                g = input() # Cantidad de iteraciones

                lock_file = open("lock.txt", "w")
                lock_file.write("0");
                lock_file.close()
                state = 1
        if state == 1:
            if tour != CONST_STOP:
                pygame.display.set_caption("Ant Colony TSP Solver - current length: " + str(cost) + " | iterations: " + str(g) + " (SOLVING...)")
                screen.fill((255,255,255))
                # Vuelve a dibujar los círculos
                for i in graph:
                    pygame.draw.circle(screen, (255,0,0), i, 5, 0)

                for i in range(0, len(tour)):
                    pygame.draw.line(screen, (255, 0, 0), graph[tour[i]], graph[tour[(i + 1) % len(tour)]])
                pygame.display.flip()
                # Salidas siguientes
                tour = input()

                if tour != CONST_STOP:
                    cost = input()
                    g = input()
            else:
                pygame.display.set_caption("Ant Colony TSP Solver - current length: " + str(cost) + " | iterations: " + str(g) + " (FINISHED)")
                state = 2

if __name__ == '__main__':
    if len(sys.argv) == 2:
        CONST_CUSTOM_FILE = sys.argv[1]
    main()