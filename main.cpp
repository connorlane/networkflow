// Author: Connor Coward
// Date: 3/17/2015
// Description: Driver code to test merge sort and heap sort

#include <iostream>
#include <vector>
#include <cassert>
#include <time.h> // for seeding pseudo-random number generator
#include <stdlib.h> // srand(), rand()
#include <chrono> // timing

#include "dfsfordfulkersonsolver.h"
#include "edmondskarpsolver.h"
#include "codetimer.h"

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

	Graph g (nodemap, {0, 5}, {2, 3});

	std::cout << "Graph: " << std::endl << g << std::endl;

	DfsFordFulkersonSolver ffs;
	EdmondsKarpSolver eks;
	CodeTimer<std::chrono::microseconds> t;

	t.start();
	int ffsResult = ffs.solve(g);
	t.stop();
	long ffsDuration = t.duration();

	t.start();
	int eksResult = eks.solve(g);
	t.stop();
	long eksDuration = t.duration();

	// Invariant: max flow from FFS = max flow from EKS
	assert(ffsResult == eksResult);

	std::cout << "Ford-Fulkerson Solver: " << ffsResult << std::endl;
	std::cout << "\tTime to solve: " << ffsDuration << std::endl;

	std::cout << "Edmonds-Karp Solver: " << eksResult << std::endl;
	std::cout << "\tTime to solve: " << eksDuration << std::endl;
}

