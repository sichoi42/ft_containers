#include <iostream>
#include <type_traits>
#include <vector>
#include "./utils/integral_constant.hpp"
#include "./implements/is_integral.hpp"
#include "./implements/enable_if.hpp"
#include <iterator>
#include "./containers/vector.hpp"

template<typename T, typename U>
struct is_same : ft::false_type {};

template<typename T>
struct is_same<T, T> : ft::true_type {};

// template <typename T>
// bool is_iterator() : ft::false_type {};

// template <typename T>
// bool is_iterator() {
// 	typedef typename std::iterator_traits<T>::iterator_category IteratorCategory;
// 	return !is_same<IteratorCategory, void>::value;
// }



// template <typename T>
// typename ft::enable_if<!ft::is_integral<T>::value>::type * = 0

template <typename T>
void test(size_t a, const T& b) {
	std::cout << "call test with int" << std::endl;
}

template <typename InputIterator>
void test(InputIterator a, InputIterator b, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {
	std::cout << "call test with iterator" << std::endl;
}



int main()
{

	// std::cout << is_iterator<std::vector<int>::iterator>::value << std::endl;
	// std::cout << is_iterator<std::vector<int>::const_iterator>::value << std::endl;
	// std::cout << is_iterator<std::vector<int>::reverse_iterator>::value << std::endl;
	// std::cout << is_iterator<std::vector<int>::const_reverse_iterator>::value << std::endl;

	test(3, 5);
	ft::vector<unsigned int> a(3);
	test(a.begin(), a.end());
}
