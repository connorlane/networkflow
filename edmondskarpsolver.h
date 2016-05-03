// Author: Connor Cowad
// Date: 5/3/16
// Class: Algorithms I
// Instructor: Chaman Sabharwal
// TA: Ayusha Mathur

#ifndef EDMONDSKARPSOLVER_H
#define EDMONDSKARPSOLVER_H

#include "fordfulkersonsolver.h"

class EdmondsKarpSolver : public FordFulkersonSolver {
private:
	std::vector<int> findPath(const Graph& g);
};

#endif

