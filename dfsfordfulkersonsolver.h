#ifndef DFSFORDFULKERSONSOLVER_H
#define DFSFORDFULKERSONSOLVER_H

#include "fordfulkersonsolver.h"

class DfsFordFulkersonSolver : public FordFulkersonSolver {
private:
	std::vector<int> findPath(const Graph& g);

	bool _findPath(const Graph& g, std::vector<bool>& visited, std::vector<int>& parent, int node);
};

#endif
