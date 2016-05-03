#ifndef MAXFLOWSOLVER_H
#define MAXFLOWSOLVER_H

#include "graph.h"

class MaxFlowSolver {
public:
	virtual int solve(const Graph& g) = 0;
};

#endif
