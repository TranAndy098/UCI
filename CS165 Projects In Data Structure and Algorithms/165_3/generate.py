import math
import random
from graph import Graph
from graph_algorithms import get_diameter
from graph_algorithms import get_clustering_coefficient
from graph_algorithms import get_degree_distribution

import time

def erdos_old(n):
    edges = set()
    p = 2 * (math.log(n)) / n
    picks = [0,1]
    probability = [1-p, p]

    for v in range(n):
        for w in range(v+1, n):
            r = random.choices(picks, probability)[0]
            if r == 1:
                edges.add((v, w))
    
    return Graph(n,edges)

def erdos(n):
    edges = set()
    p = 2 * (math.log(n)) / n
    v = 1
    w = -1

    while v < n:
        r = random.random()

        w += 1 + math.floor(math.log2(1-r)/math.log2(1-p))
        while w >= v and v < n:
            w -= v
            v += 1
        if v < n:
            edges.add((v, w))

    return Graph(n,edges)


def barabasi(n):
    edges = set()
    d = 5
    m = [0] * (2 * n * d)

    for v in range(n):
        for i in range(d):
            m[2*(v*d+i)] = v
            r = random.randint(0, 2*(v*d+i))
            m[2*(v*d+i) + 1] = m[r]
    
    for i in range((n * d) - 1):
        if m[2*i] != m[2*i + 1]:
            if m[2*i] < m[2*i + 1]:
                edges.add((m[2*i], m[2*i + 1]))
            else:
                edges.add((m[2*i+1], m[2*i]))

    return Graph(n,edges)




