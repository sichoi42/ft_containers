#include "pair.hpp"
#include <map>
#include "../base.hpp"

int	main(void)
{
	std::pair<int, std::string> std_p = std::make_pair(1, "hello");
	ft::pair<int, std::string> ft_p = ft::make_pair(1, "hello");

	std::cout << std_p.first << ":" << std_p.second << std::endl;
	std::cout << ft_p.first << ":" << ft_p.second << std::endl;
	return (0);
}
