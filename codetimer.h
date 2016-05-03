#ifndef CODETIMER_H
#define CODETIMER_H

#include <chrono>

template <typename T>
class CodeTimer {
private: 
	std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_stop;
	
public:
	void start() {
		m_start = std::chrono::high_resolution_clock::now();
	}

	void stop() {
		m_stop = std::chrono::high_resolution_clock::now();
	}

	long duration() {
		return std::chrono::duration_cast<T>(m_stop - m_start).count();
	}
};

#endif
