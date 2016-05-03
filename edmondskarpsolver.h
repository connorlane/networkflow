#ifndef EDMONDSKARPSOLVER_H
#define EDMONDSKARPSOLVER_H

#include "fordfulkersonsolver.h"
#include <queue>

class EdmondsKarpSolver : public FordFulkersonSolver {
private:
	std::vector<int> findPath(const Graph& g);
};

#endif

