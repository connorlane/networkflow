#include "dfsfordfulkersonsolver.h"

std::vector<int> DfsFordFulkersonSolver::findPath(const Graph& g) {
	std::vector<int> parent(g.size(), -1);
	std::vector<bool> visited(g.size(), false);

	if (_findPath(g, visited, parent, g.source()))
		return parent;
	else
		return std::vector<int>();
}

bool DfsFordFulkersonSolver::_findPath(const Graph& g, std::vector<bool>& visited, std::vector<int>& parent, int node) {
	if (node == g.sink())
		return true;

	for (unsigned int link = 0; link < g.size(); link++) {
		if (visited[link] == false && g[node][link] > 0) {
			visited[link] = true;
			if (_findPath(g, visited, parent, link)) {
				parent[link] = node;
				return true;
			}
		}
	}

	return false;
}

