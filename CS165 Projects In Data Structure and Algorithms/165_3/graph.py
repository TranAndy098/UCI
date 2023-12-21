# explanations for member functions are provided in requirements.py
# each file that uses a graph should import it from this file.

from collections.abc import Iterable

class Graph:
	def __init__(self, num_nodes: int, edges: Iterable[tuple[int, int]]):
		self.num_nodes = num_nodes
		self.num_edges = 0
		self.adj_list = []
		for i in range(num_nodes):
			self.adj_list.append(list())
		for edge in edges:
			self.num_edges += 1
			self.adj_list[edge[0]].append(edge[1])
			self.adj_list[edge[1]].append(edge[0])


	def get_num_nodes(self) -> int:
		return self.num_nodes

	def get_num_edges(self) -> int:
		return self.num_edges

	def get_neighbors(self, node: int) -> Iterable[int]:
		if node > self.num_nodes - 1:
			return []
		return self.adj_list[node]


	# feel free to define new methods in addition to the above
	# fill in the definitions of each required member function (above),
	# and for any additional member functions you define
