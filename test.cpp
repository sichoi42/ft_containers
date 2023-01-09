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
#include <memory>

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
	// typedef ft::integral_constant<int, 2> two_t;
	// typedef ft::integral_constant<int, 4> four_t;

	// std::cout << two_t::value << std::endl;

	// enum class my_e { e1, e2 };
	// typedef ft::integral_constant<my_e, my_e::e1> my_e_e1;
	// typedef ft::integral_constant<my_e, my_e::e2> my_e_e2;
	// std::cout << (my_e_e1() == my_e::e1) << std::endl;


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

	// {
	// 	std::allocator<int> alloc;

	// 	std::cout << std::is_same_v<int, decltype(alloc)::value_type> << std::endl;
	// 	int *p = alloc.allocate(1);
	// 	alloc.deallocate(p, 1);

	// 	using traits_t = std::allocator_traits<decltype(alloc)>;
	// 	p = traits_t::allocate(alloc, 1);
	// 	traits_t::construct(alloc, p, 7);
	// 	std::cout << *p << std::endl;
	// 	traits_t::deallocate(alloc, p, 1);
	// }
	// {
	// 	std::allocator<std::string> alloc;
	// 	using traits_t = std::allocator_traits<decltype(alloc)>;
	// 	traits_t::rebind_alloc<std::string> alloc_ = alloc;
	// 	std::string *p = traits_t::allocate(alloc, 2);
	// 	traits_t::construct(alloc, p, "foo");
	// 	traits_t::construct(alloc, p + 1, "bar");
	// 	std::cout << p[0] << ' ' << p[1] << std::endl;
	// 	traits_t::destroy(alloc, p + 1);
	// 	traits_t::destroy(alloc, p);
	// 	traits_t::deallocate(alloc, p, 2);
	// }

	// int prev = 0, cur;
	// std::vector<int> v;
	// std::cout << "capacity: " << v.capacity() << std::endl;
	// for (size_t i = 0; i < (1 << 19) + 1; i++)
	// {
	// 	v.push_back(i);
	// 	cur = v.capacity();
	// 	if (cur != prev)
	// 	{
	// 		std::cout << "capacity: " << cur << std::endl;
	// 		prev = cur;
	// 	}
	// }

	// std::vector<int> v(5, 5);
	// std::cout << "size: " << v.size() << std::endl;
	// std::cout << "capacity: " << v.capacity() << std::endl;
	// for (size_t i = 0; i < v.size(); i++) {
	// 	std::cout << v[i] << std::endl;
	// }
	// std::cout << "------------" << std::endl;
	// v.resize(3);
	// std::cout << "size: " << v.size() << std::endl;
	// std::cout << "capacity: " << v.capacity() << std::endl;
	// for (size_t i = 0; i < v.size(); i++) {
	// 	std::cout << v[i] << std::endl;
	// }

	// int n = 7;

	// std::vector<int> v(n, 5);
	// std::cout << "size: " << v.size() << std::endl;
	// std::cout << "capacity: " << v.capacity() << std::endl;
	// for (size_t i = 0; i < v.size(); i++) {
	// 	std::cout << v[i] << std::endl;
	// }
	// std::cout << "------------" << std::endl;
	// std::cout << v[10] << std::endl;

	// std::vector<int> anothervector = { 1, 2, 3, 4, 5 };
	// std::vector<int>::iterator it;

	// it = anothervector.begin();
	// std::cout << "size: " << anothervector.size() << std::endl;
	// std::cout << "capacity: " << anothervector.capacity() << std::endl;
	// for (size_t i = 0; i < anothervector.size(); i++) {
	// 	std::cout << anothervector[i] << std::endl;
	// }

	std::vector<int> myvector = { 1, 2, 3, 4, 5 };
	std::vector<int>::iterator it2;
	it2 = myvector.begin();
	myvector.erase(it2 + 1, it2 + 3);
	// myvector.insert(it2 + 1, anothervector.begin(), anothervector.end());
	std::cout << "size: " << myvector.size() << std::endl;
	std::cout << "capacity: " << myvector.capacity() << std::endl;
	for (size_t i = 0; i < myvector.size(); i++) {
		std::cout << myvector[i] << std::endl;
	}

  // myvector.insert(it, 2, 300);

  // // "it" no longer valid, get a new one:
  // it = myvector.begin();

  // std::vector<int> anothervector(2, 400);
  // myvector.insert(it + 2, anothervector.begin(), anothervector.end());

  // int myarray[] = {501, 502, 503};
  // myvector.insert(myvector.begin(), myarray, myarray + 3);

  // std::cout << "myvector contains:";
  // for (it = myvector.begin(); it < myvector.end(); it++) std::cout << " " << *it;
  // std::cout << std::endl;
	return 0;
}
