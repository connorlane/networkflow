// Author: Connor Coward
// Date: 3/17/2015
// Description: Driver code to test merge sort and heap sort

#include <iostream>
#include <vector>
#include <cassert>
#include <queue>

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

	std::vector<int>& operator[] (const int index) {
		return m_nodemap[index];
	};

	std::vector<int> findPath() {
		std::vector<int> parent(m_size);
		std::vector<bool> visited(m_size);

		

		return parent;
	};
};

class MaxFlowSolver {
public:
	virtual int solve(const Graph& g) = 0;
};

class FordFulkersonSolver : public MaxFlowSolver {
public:
	int solve(const Graph& g) {
		Graph residual = g;
		//int maxFlow = 0;
		while (!residual.findPath().empty()) {
			
		}
		return residual[0][0];
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
}

