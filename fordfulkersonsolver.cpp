// Author: Connor Cowad
// Date: 5/3/16
// Class: Algorithms I
// Instructor: Chaman Sabharwal
// TA: Ayusha Mathur

#include "fordfulkersonsolver.h"

int FordFulkersonSolver::solve(const Graph& g) {
	int u, v;
	Graph residual = g;
	int maxFlow = 0;

	std::vector<int> parent = findPath(residual);

	while (!parent.empty()) {
		// Invariant: the parent list describes a complete path from source to sink
		assert(isPath(g, parent));

		// Invariant: the number of nodes in the parent list is equal to the number of nodes in the graph
		assert(parent.size() == g.size());

		v = g.sink();
		u = parent[v];
		int thisFlow = residual[u][v];

		do {
			thisFlow = (thisFlow < residual[u][v]) ? thisFlow : residual[u][v];
			v = parent[v];
			u = parent[v];
		} while (v != g.source());

		for (v = g.sink(); v != g.source(); v = parent[v]) {
			u = parent[v];
			residual[u][v] -= thisFlow;
			residual[v][u] += thisFlow;
		}

		maxFlow += thisFlow;

		parent = findPath(residual);
	}

	return maxFlow;
}

bool FordFulkersonSolver::isPath(const Graph& g, const std::vector<int>& parent) {
	int node = g.sink();
	std::vector<bool> visited(g.size(), false);

	while (node != g.source()) {
		if (visited[node])
			return false;

		visited[node] = true;
		node = parent[node];
	}

	return true;
}

