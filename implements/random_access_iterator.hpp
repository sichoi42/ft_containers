#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP
# include "../implements/iterator_traits.hpp"

namespace ft {
	template <typename Iterator>
	class random_access_iterator {
		public:
			typedef Iterator		iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type	value_type;
			typedef typename iterator_traits<Iterator>::difference_type	difference_type;
			typedef typename iterator_traits<Iterator>::pointer	pointer;
			typedef typename iterator_traits<Iterator>::reference	reference;

		private:
			Iterator _cur;

		public:
			// Constrcutor
			random_access_iterator() {}
			explicit random_access_iterator(iterator_type x) : _cur(x) {}

			// Copy constructor
			random_access_iterator(const random_access_iterator& x) : _cur(x._cur) {}
			template <typename Iter>
			random_access_iterator(const random_access_iterator<Iterator>& x) : _cur(x.base()) {}

			// Copy assignment operator
			random_access_iterator& operator=(const random_access_iterator& x) {
				if (this != &x) {
					_cur = x._cur;
				}
				return *this;
			}

			// Getter
			iterator_type base() const {
				return _cur;
			}

			// Operator overloads
			reference operator*() const {
				Iterator tmp = _cur;
				return *--tmp;
			}

			pointer operator->() const {
				return &(operator*());
			}

			random_access_iterator& operator++() {
				++_cur;
				return *this;
			}

			random_access_iterator operator++(int) {
				random_access_iterator tmp = *this;
				++_cur;
				return tmp;
			}

			random_access_iterator& operator--() {
				--_cur;
				return *this;
			}

			random_access_iterator operator--(int) {
				random_access_iterator tmp = *this;
				--_cur;
				return tmp;
			}

			random_access_iterator operator+(difference_type n) const {
				return random_access_iterator(_cur + n);
			}

			random_access_iterator& operator+=(difference_type n) {
				_cur += n;
				return *this;
			}

			random_access_iterator operator-(difference_type n) const {
				return random_access_iterator(_cur - n);
			}

			random_access_iterator& operator-=(difference_type n) {
				_cur -= n;
				return *this;
			}

			reference operator[](difference_type n) const {
				return *(*this + n);
			}
	};

	// Non-member function overloads
	template <typename Iterator>
	inline bool operator==(const random_access_iterator<Iterator>& x, const random_access_iterator<Iterator>& y) {
		return x.base() == y.base();
	}

	template <typename Iterator>
	inline bool operator<(const random_access_iterator<Iterator>& x, const random_access_iterator<Iterator>& y) {
		return x.base() < y.base();
	}

	template <typename Iterator>
	inline bool operator!=(const random_access_iterator<Iterator>& x, const random_access_iterator<Iterator>& y) {
		return !(x == y);
	}


	template <typename Iterator>
	inline bool operator>(const random_access_iterator<Iterator>& x, const random_access_iterator<Iterator>& y) {
		return y < x;
	}

	template <typename Iterator>
	inline bool operator<=(const random_access_iterator<Iterator>& x, const random_access_iterator<Iterator>& y) {
		return !(y < x);
	}

	template <typename Iterator>
	inline bool operator>=(const random_access_iterator<Iterator>& x, const random_access_iterator<Iterator>& y) {
		return !(x < y);
	}

	template <typename Iterator>
	inline typename random_access_iterator<Iterator>::difference_type
	operator+(const random_access_iterator<Iterator>& x, const random_access_iterator<Iterator>& y) {
		return x.base() + y.base();
	}

	template <typename Iterator>
	inline random_access_iterator<Iterator>
	operator+(typename random_access_iterator<Iterator>::difference_type n, const random_access_iterator<Iterator>& x) {
		return random_access_iterator<Iterator>(x.base() + n);
	}
}

#endif
