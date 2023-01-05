#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP
# include <memory>
# include "../implements/reverse_iterator.hpp"

namespace ft {
	template <class T, class Allocator = std::allocator<T> >
	class vector {
		public:
			typedef T																										value_type;
			typedef Allocator																						allocator_type;
			typedef value_type*																					pointer;
			typedef const value_type*																		const_pointer;
			typedef value_type&																					reference;
			typedef const value_type&																		const_reference;
			// typedef TODO: 구현 필요																		size_type;
			// typedef TODO: 구현 필요																		difference_type;
			// typedef TODO: 구현 필요																		iterator_type;
			// typedef TODO: 구현 필요																		const_iterator_type;
			// TODO: random_access_iterator 구현 필요
			typedef ft::reverse_iterator<iterator>											reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>								const_reverse_iterator;
	};
}

#endif

/*
	STL Reference
	https://en.cppreference.com/w/cpp/container/stack

	STL Base Header
	https://en.cppreference.com/w/cpp/header/stack
*/
