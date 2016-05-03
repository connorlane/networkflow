// Author: Connor Coward
// Date: 3/17/2015
// Description: Driver code to test merge sort and heap sort

#include <iostream>
#include <vector>
#include <cassert>
#include <queue>
#include <climits> // INT_MAX

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

	std::vector<int>& operator[] (const int index) {
		return m_nodemap[index];
	};

	std::vector<int> findPath() {
		std::vector<int> parent(m_size);
		std::vector<bool> visited(m_size);
		std::queue<int> q;

		q.push(m_source);
		visited[m_source] = true;
		parent[m_source] = -1;

		while(!q.empty()) {
			int u = q.front();
			q.pop();

			for (int v = 0; v < m_size; v++) {
				if (visited[v] == false && m_nodemap[u][v] > 0) {
					q.push(v);
					parent[v] = u;
					visited[v] = true;
				}
			}
		}	

		return (visited[m_sink] == true) ? parent : std::vector<int>();
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

		std::vector<int> parent = residual.findPath();

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

			parent = residual.findPath();

			std::cout << "parent[]: " << std::endl;
			for(auto i: parent) {
				std::cout << i << ' ';
			}
			std::cout << std::endl;
		}

		return maxFlow;
	};
};

int main() {
	Graph g ({
		{0, 16, 13, 0, 0, 0},
		{0, 0, 10, 12, 0, 0},
		{0, 4, 0, 0, 14, 0},
		{0, 0, 9, 0, 0, 20},
		{0, 0, 0, 7, 0, 4},
		{0, 0, 0, 0, 0, 0}
	}, 0, 5);

	FordFulkersonSolver s;

	std::cout << "Is empty? " << (std::vector<int>()).empty() << std::endl;

	std::cout << "Max Flow: " << s.solve(g) << std::endl;

	std::cout << g << std::endl;
}

