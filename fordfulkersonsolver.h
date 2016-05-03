#ifndef FORDFULKERSONSOLVER_H
#define FORDFULKERSONSOLVER_H

#include "maxflowsolver.h"

class FordFulkersonSolver : public MaxFlowSolver {
public:
	int solve(const Graph& g);

private:
	virtual std::vector<int> findPath(const Graph& g) = 0;

	bool isPath(const Graph& g, const std::vector<int>& parent);
};

#endif
