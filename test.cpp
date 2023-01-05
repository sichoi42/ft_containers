#include <iostream>
#include "./implements/iterator_traits.hpp"
#include <vector>
#include <list>
#include "./implements/reverse_iterator.hpp"

#include <cstddef>
#include <iostream>
#include <iterator>

#include "./implements/enable_if.hpp"
#include "./implements/is_integral.hpp"
#include "./implements/equal.hpp"
#include "./implements/lexicographical_compare.hpp"

#include <type_traits>
#include <algorithm>

template <typename T>
typename ft::enable_if<ft::is_integral<T>::value>::type
do_something(const T& foo) {
	std::cout << "type integral" << std::endl;
}

template<typename T>
typename ft::enable_if<std::is_class<T>::value>::type
do_something(const T& foo) {
	std::cout << "type class" << std::endl;
}

class B {
public:
	B() {}
};

template <typename T>
bool compare(const T& a, const T& b) {
	return a == b;
}

template <typename T>
bool compare2(const T& a, const T& b) {
	return a < b;
}

int main(){
	typedef ft::integral_constant<int, 2> two_t;
	typedef ft::integral_constant<int, 4> four_t;

	std::cout << two_t::value << std::endl;

	enum class my_e { e1, e2 };
	typedef ft::integral_constant<my_e, my_e::e1> my_e_e1;
	typedef ft::integral_constant<my_e, my_e::e2> my_e_e2;
	std::cout << (my_e_e1() == my_e::e1) << std::endl;
	// const volatile int a = 1;
	// do_something(a);
	// B b = B();
	// do_something(b);

	// std::vector<int> v1;
	// v1.push_back(1);
	// v1.push_back(2);
	// v1.push_back(3);
	// v1.push_back(4);
	// // v1.push_back(5);
	// std::vector<int> v2;
	// v2.push_back(1);
	// v2.push_back(2);
	// v2.push_back(3);
	// v2.push_back(4);
	// v2.push_back(5);

	// std::cout << ft::equal(v1.begin(), v1.end(), v2.begin()) << std::endl;
	// std::cout << ft::equal(v1.begin(), v1.end(), v2.begin(), compare<int>) << std::endl;

	// std::cout << std::equal(v1.begin(), v1.end(), v2.begin()) << std::endl;
	// std::cout << std::equal(v1.begin(), v1.end(), v2.begin(), compare<int>) << std::endl;

	// std::cout << ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end()) << std::endl;
	// std::cout << ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end(), compare2<int>) << std::endl;
	return 0;
}
