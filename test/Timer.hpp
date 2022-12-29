#include <ctime>
#include <stack>
#include "../containers/stack.hpp"

class Timer {
	private:
		std::clock_t	_start;

	public:
		Timer();
		~Timer();
		Timer(const Timer& t);

		Timer&	operator=(const Timer& t);

		void	start();
		std::clock_t	stop();
};

template <class Stack>
std::clock_t get_push_pop_time_stack(std::size_t size, Stack st) {
	Timer t;
	t.start();
	for (std::size_t i = 0; i < size; ++i) {
		st.push(i);
	}
	{
		Stack tmp(st);
	}
	for (std::size_t i = 0; i < size; ++i) {
		st.top();
		st.pop();
	}
	return t.stop();
}
