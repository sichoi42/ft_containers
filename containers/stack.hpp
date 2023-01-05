#ifndef FT_STACK_HPP
# define FT_STACK_HPP

// FIXME: stack을 테스트하기 위해 선언한 것이므로, 나중에 삭제할 것
# include <vector>

namespace ft {
	// FIXME: 추후 ft::vector로 수정 필요
	template <class T, class Container = std::vector<T> >
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
		// Constructor
		stack() : _c() {}
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
	};

	// Non-member function overloads
	template <class T, class Container>
	bool operator==(const stack<T, Container>& x, const stack<T, Container>& y) {
		return x._c == y._c;
	}

	template <class T, class Container>
	bool operator<(const stack<T, Container>& x, const stack<T, Container>& y) {
		return x._c < y._c;
	}

	template <class T, class Container>
	bool operator!=(const stack<T, Container>& x, const stack<T, Container>& y) {
		return !(x == y);
	}

	template <class T, class Container>
	bool operator>(const stack<T, Container>& x, const stack<T, Container>& y) {
		return y < x;
	}

	template <class T, class Container>
	bool operator<=(const stack<T, Container>& x, const stack<T, Container>& y) {
		return !(y < x);
	}

	template <class T, class Container>
	bool operator>=(const stack<T, Container>& x, const stack<T, Container>& y) {
		return !(y > x);
	}
}

/*
	STL Reference
	https://en.cppreference.com/w/cpp/container/stack

	STL Base Header
	https://en.cppreference.com/w/cpp/header/stack
*/

#endif
