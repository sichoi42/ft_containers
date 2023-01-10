#include <iostream>
#include <stack>
#include <vector>
#include <list>
#include <deque>
#include "../containers/stack.hpp"
#include "Timer.hpp"

# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define RESET "\033[0m"

class Tester
{
	private:

	public:
		Tester();
		~Tester();
		Tester(const Tester& t);

		Tester&	operator=(const Tester& t);

		static void	simple_test_stack();
};
