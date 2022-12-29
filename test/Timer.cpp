#include "Timer.hpp"

Timer::Timer() : _start(0) {}

Timer::~Timer() {}

Timer::Timer(const Timer& t) : _start(t._start) {}

Timer&	Timer::operator=(const Timer& t) {
	if (this != &t) {
		_start = t._start;
	}
	return *this;
}

void	Timer::start() {
	_start = std::clock();
}

std::clock_t	Timer::stop() {
	return std::clock() - _start;
}

