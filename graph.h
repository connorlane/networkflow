// Author: Connor Cowad
// Date: 5/3/16
// Class: Algorithms I
// Instructor: Chaman Sabharwal
// TA: Ayusha Mathur

#ifndef GRAPH_H
#define GRAPH_H

#include <vector> // std::vector
#include <cstdlib> // size_t
#include <cassert> // assert
#include <climits> // INT_MAX
#include <ostream> // std::ostream

class Graph {
private:
	std::vector< std::vector<int> > m_nodemap;
	int m_source;
	int m_sink;
	size_t m_size;

public:
	Graph(const std::vector< std::vector<int> >& nodemap, std::vector<int> source, std::vector<int> sink);

	int source() const;

	size_t size() const;

	int sink() const;

	const std::vector<int>& operator[] (const int index) const;

	std::vector<int>& operator[] (const int index);

	friend std::ostream& operator<< (std::ostream& os, const Graph& g);
};

#endif
