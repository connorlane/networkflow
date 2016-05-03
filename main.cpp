// Author: Connor Coward
// Date: 3/17/2015
// Description: Driver code to test merge sort and heap sort

#include <iostream>
#include <vector>
#include <cassert>
#include <queue>
#include <climits> // INT_MAX
#include <time.h> // for seeding pseudo-random number generator
#include <stdlib.h> // srand(), rand()

class Graph {
private:
	std::vector< std::vector<int> > m_nodemap;
	int m_source;
	int m_sink;
	int m_size;

public:
	Graph(const std::vector< std::vector<int> >& nodemap, int source, int sink) {
		m_size = nodemap.size();

		// Invariant: xsize = ysize of nodemap
		for(auto n: nodemap) {
			assert(n.size() == m_size);
		}

		// Invariant: source & sink are valid nodes
		assert(source >= 0 && source <= m_size);
		assert(sink >= 0 && sink <= m_size);

		m_source = source;
		m_sink = sink;

		m_nodemap = nodemap;	
	};

	int source() const {
		return m_source;
	}

	int size() const {
		return m_size;
	}

	int sink() const {
		return m_sink;
	}

	const std::vector<int>& operator[] (const int index) const {
		return m_nodemap[index];
	};

	std::vector<int>& operator[] (const int index) {
		return m_nodemap[index];
	};

	friend std::ostream& operator<< (std::ostream& os, const Graph& g) {
		for (auto node: g.m_nodemap) {
			for (auto link: node) {
				os << link << ' ';
			}
			os << std::endl;
		}
		return os;
	}
};

class MaxFlowSolver {
public:
	virtual int solve(const Graph& g) = 0;
};

class FordFulkersonSolver : public MaxFlowSolver {
public:
	int solve(const Graph& g) {
		int u, v;
		Graph residual = g;
		int maxFlow = 0;

		std::vector<int> parent = findPath(residual);

		while (!parent.empty()) {
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
	};

private:
	virtual std::vector<int> findPath(const Graph& g) = 0;
};

class EdmondsKarpSolver : public FordFulkersonSolver {
private:
	std::vector<int> findPath(const Graph& g) {
		std::vector<int> parent(g.size());
		std::vector<bool> visited(g.size());
		std::queue<int> q;

		q.push(g.source());
		visited[g.source()] = true;
		parent[g.source()] = -1;

		while(!q.empty()) {
			int u = q.front();
			q.pop();

			for (int v = 0; v < g.size(); v++) {
				if (visited[v] == false && g[u][v] > 0) {
					q.push(v);
					parent[v] = u;
					visited[v] = true;
				}
			}
		}	

		return (visited[g.sink()] == true) ? parent : std::vector<int>();
	};
};

class EdmondsKarpSolver : public FordFulkersonSolver {
private:
	std::vector<int> findPath(const Graph& g) {
		std::vector<int> parent(g.size());
		std::vector<bool> visited(g.size());
		std::queue<int> q;

		q.push(g.source());
		visited[g.source()] = true;
		parent[g.source()] = -1;

		while(!q.empty()) {
			int u = q.front();
			q.pop();

			for (int v = 0; v < g.size(); v++) {
				if (visited[v] == false && g[u][v] > 0) {
					q.push(v);
					parent[v] = u;
					visited[v] = true;
				}
			}
		}	

		return (visited[g.sink()] == true) ? parent : std::vector<int>();
	};

	std::vector<int> findPath(const Graph& g, int node) {
		std::vector<int> parent(g.size());
		std::vector<bool> visited(g.size());
		
	}
};

int main() {
	const int numberOfNodes = 100;
	const int maxFlowPerLink = 9;

	std::vector< std::vector<int> > nodemap(numberOfNodes, std::vector<int>(numberOfNodes));

	srand(time(NULL));

	for (auto& node: nodemap) {
		for (auto& link: node) {
			link = rand() % (maxFlowPerLink + 1);
		}
	}

	Graph g (nodemap, 0, numberOfNodes - 1);

	EdmondsKarpSolver s;

	std::cout << "Max Flow: " << s.solve(g) << std::endl;

	std::cout << g << std::endl;
}

