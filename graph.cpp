#include "graph.h"

Graph::Graph(const std::vector< std::vector<int> >& nodemap, std::vector<int> source, std::vector<int> sink) {
	m_size = nodemap.size();

	// Invariant: xsize = ysize of nodemap
	for(auto n: nodemap) {
		// Invariant: m_size must be greater than zero
		assert(m_size > 0);
		assert(n.size() == static_cast<unsigned int>(m_size));
	}

	// Invariant: source & sink are valid nodes
	for (auto i: source)
		assert(i >= 0 && static_cast<unsigned int>(i) <= m_size);

	for (auto i: sink)
		assert(i >= 0 && static_cast<unsigned int>(i) <= m_size);

	m_nodemap = nodemap;	

	// Create a supersource
	m_nodemap.push_back(std::vector<int>(m_size, 0));
	m_size++;
	m_source = m_size - 1;
	for (auto& node: m_nodemap)
		node.push_back(0);

	// Set the supersource links to (effectively) infinity
	for (auto sourcenode: source)
		m_nodemap[m_source][sourcenode] = INT_MAX;

	// Create a supersink
	m_nodemap.push_back(std::vector<int>(m_size, 0));
	m_size++;
	m_sink = m_size - 1;
	for (auto& node: m_nodemap)
		node.push_back(0);

	// Set the supersink links to (effectively) infinity
	for (auto sinknode: sink)
		m_nodemap[sinknode][m_sink] = INT_MAX;

	
}

int Graph::source() const {
	return m_source;
}

size_t Graph::size() const {
	return m_size;
}

int Graph::sink() const {
	return m_sink;
}

const std::vector<int>& Graph::operator[] (const int index) const {
	return m_nodemap[index];
}

std::vector<int>& Graph::operator[] (const int index) {
	return m_nodemap[index];
}

std::ostream& operator<< (std::ostream& os, const Graph& g) {
	for (auto node: g.m_nodemap) {
		for (auto link: node) {
			os << link << ' ';
		}
		os << std::endl;
	}
	return os;
}

