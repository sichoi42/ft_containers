#ifndef FT_STACK_HPP
# define FT_STACK_HPP

# include "./vector.hpp"

namespace ft {
	template <class T, class Container = ft::vector<T> >
	class stack {
	public:
		typedef Container container_type;
		typedef typename container_type::value_type value_type;
		typedef typename container_type::size_type size_type;
		typedef typename container_type::reference reference;
		typedef typename container_type::const_reference const_reference;

	protected:
		container_type _c;

	public:
		explicit stack(const container_type& c_type = container_type()) : _c(c_type) {}

		// Copy constructor
		stack(const stack& st) : _c(st._c) {}

		// Destructor
		~stack() {}

		// Copy assignment operator
		stack& operator=(const stack& st) {
			if (this != &st) {
				_c = st._c;
			}
			return *this;
		}

		bool empty() const {
			return _c.empty();
		}

		size_type size() const {
			return _c.size();
		}

		reference top() {
			return _c.back();
		}

		const_reference top() const {
			return _c.back();
		}

		void push(const value_type& val) {
			_c.push_back(val);
		}

		void pop() {
			_c.pop_back();
		}

		// friend Non-member function overloads
		friend bool operator==(const stack<T, Container>& x, const stack<T, Container>& y) {
			return x._c == y._c;
		}

		friend bool operator<(const stack<T, Container>& x, const stack<T, Container>& y) {
			return x._c < y._c;
		}

		friend bool operator!=(const stack<T, Container>& x, const stack<T, Container>& y) {
			return !(x == y);
		}

		friend bool operator>(const stack<T, Container>& x, const stack<T, Container>& y) {
			return y < x;
		}

		friend bool operator<=(const stack<T, Container>& x, const stack<T, Container>& y) {
			return !(y < x);
		}

		friend bool operator>=(const stack<T, Container>& x, const stack<T, Container>& y) {
			return !(y > x);
		}
	};
}

/*
	STL Reference
	https://en.cppreference.com/w/cpp/container/stack

	STL Base Header
	https://en.cppreference.com/w/cpp/header/stack
*/

#endif
