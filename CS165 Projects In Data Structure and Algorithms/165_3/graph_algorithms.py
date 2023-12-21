# explanations for these functions are provided in requirements.py

from graph import Graph
import random

def BFS(graph: Graph, node: int):
	level = -1
	explored = [0] * graph.get_num_nodes()
	need_to = [node]
	last_exp = None
	while len(need_to) > 0:
		new_nodes = []
		for n in need_to:
			for i in graph.get_neighbors(n):
				if explored[i] == 0:
					new_nodes.append(i)
					explored[i] = 1
		last_exp = n
		need_to = new_nodes
		level += 1
	return level, last_exp

def get_diameter(graph: Graph) -> int:
	d = 0
	node = random.randint(0, graph.get_num_nodes()-1)
	stop = False
	while not stop:
		distance, furthest = BFS(graph, node)
		if distance > d:
			d = distance
			node = furthest
		else:
			stop = True
	return d




def get_clustering_coefficient(graph: Graph) -> float:
	num = graph.get_num_nodes()

	denominator = 0
	each_node_degree = {}
	dict_neighbors = []
	for i in range(num):
		indiv = {}
		i_neighbors = graph.get_neighbors(i)
		for j in i_neighbors:
			indiv[j] = 1
		dict_neighbors.append(indiv)

	ordered_l = []
	l = {}
	d = []
	n = []
	for node in range(num):
		d.append(list())
		n.append(list())

	for node in range(num):
		
		degree = len(graph.get_neighbors(node))
		denominator += ((degree) * (degree -1)) / 2

		each_node_degree[node] = degree
		d[degree].append(node)

	k = 0

	for _ in range(num):
		for j in range(num):
			if d[j]:
				i = j
				break
		k = max(k,i)
		v = d[i][0]
		d[i].pop(0)
		ordered_l = [v] + ordered_l
		for w in graph.get_neighbors(v):
			if w not in l:
				dw = each_node_degree[w]
				d[dw].remove(w)
				each_node_degree[w] -= 1
				dw -= 1
				d[dw].append(w)
				n[v].append(w)
		l[v] = 1

	numerator = 0

	for v in ordered_l:
		for i in range(len(n[v])):
			u = n[v][i]
			for j in range(i+1, len(n[v])):
				w = n[v][j]
				if w in dict_neighbors[u]:
					numerator += 3

	return numerator / denominator
	

def get_degree_distribution(graph: Graph) -> dict[int, int]:
	count = {}
	for node in range(graph.get_num_nodes()):
		degree = len(graph.get_neighbors(node))
		if degree in count:
			count[degree] += 1
		else:
			count[degree] = 1
	return count
