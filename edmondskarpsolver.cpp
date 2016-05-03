#include "edmondskarpsolver.h"

std::vector<int> EdmondsKarpSolver::findPath(const Graph& g) {
	std::vector<int> parent(g.size());
	std::vector<bool> visited(g.size());
	std::queue<int> q;

	q.push(g.source());
	visited[g.source()] = true;
	parent[g.source()] = -1;

	while(!q.empty()) {
		int u = q.front();
		q.pop();

		for (unsigned int v = 0; v < g.size(); v++) {
			if (visited[v] == false && g[u][v] > 0) {
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}	

	return (visited[g.sink()] == true) ? parent : std::vector<int>();
}

