// Author: Connor Cowad
// Date: 5/3/16
// Class: Algorithms I
// Instructor: Chaman Sabharwal
// TA: Ayusha Mathur

#include <iostream>
#include <vector>
#include <cassert>
#include <time.h> // for seeding pseudo-random number generator
#include <stdlib.h> // srand(), rand()
#include <chrono> // timing
#include <algorithm> // std::random_shuffle

#include "dfsfordfulkersonsolver.h"
#include "edmondskarpsolver.h"
#include "codetimer.h"

int main() {
	// Test parameters
	const int numberOfNodes = 500;
	const int maxFlowPerLink = 9;
	const int sparseness = 50; // Out of 100
	const int numSource = numberOfNodes * 0.2;
	const int numSink = numberOfNodes * 0.2;

	// Create a node map to store the links
	std::vector< std::vector<int> > nodemap(numberOfNodes, std::vector<int>(numberOfNodes));

	// Seed the PRNG
	srand(time(NULL));

	// Fill the node map with random link weights
	for (auto& node: nodemap) {
		for (auto& link: node) {
			// Used to generate sparse graphs or dense graphs
			if ( (rand() % 100) > sparseness) 
				// No link
				link = 0;
			else
				// Random link weight from 1 to maxFlowPerLink
				link = rand() % (maxFlowPerLink) + 1;
		}
	}

	// Generate a list filled with incrementing integers
	std::vector<int> randomNodes(numberOfNodes);
	int counter = 0;
	for (auto& i: randomNodes)
		i = counter++;

	// Shuffle the integers
	std::random_shuffle(randomNodes.begin(), randomNodes.end());

	// Invariant: numSource + numSink <= numberOfNodes
	assert(numSource + numSink < numberOfNodes);

	// Create random sources
	std::vector<int> source(randomNodes.begin(), randomNodes.begin() + numSource);
	randomNodes.erase(randomNodes.begin(), randomNodes.begin() + numSource);

	// Create random sinks
	std::vector<int> sink(randomNodes.begin(), randomNodes.begin() + numSink);
	randomNodes.erase(randomNodes.begin(), randomNodes.begin() + numSink);

	// Create a graph from the given node map, sources and sinks
	Graph g (nodemap, source, sink);

	// Uncomment to view input graph map
	std::cout << "Graph: " << std::endl << g << std::endl;

	// Create the solvers & timer
	DfsFordFulkersonSolver ffs;
	EdmondsKarpSolver eks;
	CodeTimer<std::chrono::microseconds> t;

	// Solve using Ford-Fulkerson (DFS)
	t.start();
	int ffsResult = ffs.solve(g);
	t.stop();
	long ffsDuration = t.duration();

	// Solve using Edmonds-Karp
	t.start();
	int eksResult = eks.solve(g);
	t.stop();
	long eksDuration = t.duration();

	// Invariant: max flow from FFS = max flow from EKS
	assert(ffsResult == eksResult);

	// Print the results
	std::cout << "Ford-Fulkerson Solver: " << ffsResult << std::endl;
	std::cout << "\tTime to solve: " << ffsDuration << std::endl;

	std::cout << "Edmonds-Karp Solver: " << eksResult << std::endl;
	std::cout << "\tTime to solve: " << eksDuration << std::endl;
}

