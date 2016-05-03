// Author: Connor Cowad
// Date: 5/3/16
// Class: Algorithms I
// Instructor: Chaman Sabharwal
// TA: Ayusha Mathur

#ifndef MAXFLOWSOLVER_H
#define MAXFLOWSOLVER_H

#include "graph.h"

class MaxFlowSolver {
public:
	virtual int solve(const Graph& g) = 0;
};

#endif
