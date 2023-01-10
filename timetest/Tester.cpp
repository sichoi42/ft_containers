#include "Tester.hpp"

Tester::Tester() {}

Tester::~Tester() {}

Tester::Tester(const Tester& t) {}

Tester&	Tester::operator=(const Tester& t) {
	if (this != &t) {}
	return *this;
}

void Tester::simple_test_stack() {
	std::cout << GREEN << "================Simple Test for Stack================" << RESET << std::endl;
	std::clock_t std_clock;
	std::clock_t ft_clock;

	// Test Stack with vector
	std::stack<int, std::vector<int> > st1;
	std_clock = get_simple_test_time_stack(1000000, st1);
	ft::stack<int, std::vector<int> > ft_st1;
	ft_clock = get_simple_test_time_stack(1000000, ft_st1);
	std::cout << "Our stack with vector is " << static_cast<double>(std_clock) / static_cast<double>(ft_clock) << " times faster." << std::endl;
	std::cout << "Our stack with vector is " << static_cast<double>(ft_clock) / static_cast<double>(std_clock) << " times slower." << std::endl;
	if (static_cast<double>(ft_clock) / static_cast<double>(std_clock) >= 20.0000) {
		std::cout << RED << "[FAIL] Our stack with vector is too slow." << RESET << std::endl;
	} else {
		std::cout << GREEN << "[PASS] Our stack with vector is fast enough." << RESET << std::endl;
	}

	// Test Stack with list
	std::stack<int, std::list<int> > st2;
	std_clock = get_simple_test_time_stack(1000000, st2);
	ft::stack<int, std::list<int> > ft_st2;
	ft_clock = get_simple_test_time_stack(1000000, ft_st2);
	std::cout << "Our stack with list is " << static_cast<double>(std_clock) / static_cast<double>(ft_clock) << " times faster." << std::endl;
	std::cout << "Our stack with lsit is " << static_cast<double>(ft_clock) / static_cast<double>(std_clock) << " times slower." << std::endl;
	if (static_cast<double>(ft_clock) / static_cast<double>(std_clock) >= 20.0000) {
		std::cout << RED << "[FAIL] Our stack with list is too slow." << RESET << std::endl;
	} else {
		std::cout << GREEN << "[PASS] Our stack with list is fast enough." << RESET << std::endl;
	}

	// Test Stack with deque
	std::stack<int, std::deque<int> > st3;
	std_clock = get_simple_test_time_stack(1000000, st3);
	ft::stack<int, std::deque<int> > ft_st3;
	ft_clock = get_simple_test_time_stack(1000000, ft_st3);
	std::cout << "Our stack with deque is " << static_cast<double>(std_clock) / static_cast<double>(ft_clock) << " times faster." << std::endl;
	std::cout << "Our stack with deque is " << static_cast<double>(ft_clock) / static_cast<double>(std_clock) << " times slower." << std::endl;
	if (static_cast<double>(ft_clock) / static_cast<double>(std_clock) >= 20.0000) {
		std::cout << RED << "[FAIL] Our stack with deque is too slow." << RESET << std::endl;
	} else {
		std::cout << GREEN << "[PASS] Our stack with deque is fast enough." << RESET << std::endl;
	}
}
