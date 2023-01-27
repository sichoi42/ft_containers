#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP
# include "./iterator_traits.hpp"

namespace ft {
	template <typename Iterator>
	class reverse_iterator {
		public:
			typedef Iterator																							iterator_type;
			typedef typename ft::iterator_traits<iterator_type>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<iterator_type>::value_type				value_type;
			typedef typename ft::iterator_traits<iterator_type>::difference_type		difference_type;
			typedef typename ft::iterator_traits<iterator_type>::pointer						pointer;
			typedef typename ft::iterator_traits<iterator_type>::reference					reference;

		private:
			iterator_type _cur;

		public:
			// Constrcutor
			reverse_iterator() : _cur() {}
			explicit reverse_iterator(iterator_type x) : _cur(x) {}

			// Copy constructor
			template <typename Iter>
			reverse_iterator(const reverse_iterator<Iter>& x) : _cur(x.base()) {}

			// Copy assignment operator
			reverse_iterator& operator=(const reverse_iterator& x) {
				if (this != &x) {
					_cur = x._cur;
				}
				return *this;
			}
			template <typename Iter>
			reverse_iterator& operator=(const reverse_iterator<Iter>& x) {
				// if (this != &x) {
					_cur = x.base();
				// }
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

			reverse_iterator& operator++() {
				--_cur;
				return *this;
			}

			reverse_iterator operator++(int) {
				reverse_iterator tmp = *this;
				--_cur;
				return tmp;
			}

			reverse_iterator& operator--() {
				++_cur;
				return *this;
			}

			reverse_iterator operator--(int) {
				reverse_iterator tmp = *this;
				++_cur;
				return tmp;
			}

			reverse_iterator operator+(difference_type n) const {
				return reverse_iterator(_cur - n);
			}

			reverse_iterator& operator+=(difference_type n) {
				_cur -= n;
				return *this;
			}

			reverse_iterator operator-(difference_type n) const {
				return reverse_iterator(_cur + n);
			}

			reverse_iterator& operator-=(difference_type n) {
				_cur += n;
				return *this;
			}

			reference operator[](difference_type n) const {
				return *(*this + n);
			}
	};

	// Non-member function overloads
	template <typename T1, typename T2>
	inline bool operator==(const reverse_iterator<T1>& x, const reverse_iterator<T2>& y) {
		return x.base() == y.base();
	}

	template <typename T1, typename T2>
	inline bool operator<(const reverse_iterator<T1>& x, const reverse_iterator<T2>& y) {
		return y.base() < x.base();
	}

	template <typename T1, typename T2>
	inline bool operator!=(const reverse_iterator<T1>& x, const reverse_iterator<T2>& y) {
		return !(x == y);
	}


	template <typename T1, typename T2>
	inline bool operator>(const reverse_iterator<T1>& x, const reverse_iterator<T2>& y) {
		return y < x;
	}

	template <typename T1, typename T2>
	inline bool operator<=(const reverse_iterator<T1>& x, const reverse_iterator<T2>& y) {
		return !(y < x);
	}

	template <typename T1, typename T2>
	inline bool operator>=(const reverse_iterator<T1>& x, const reverse_iterator<T2>& y) {
		return !(x < y);
	}

	template <typename T1, typename T2>
	inline typename reverse_iterator<T1>::difference_type
	operator-(const reverse_iterator<T1>& x, const reverse_iterator<T2>& y) {
		return y.base() - x.base();
	}

	template <typename T>
	inline reverse_iterator<T>
	operator+(typename reverse_iterator<T>::difference_type n, const reverse_iterator<T>& x) {
		return reverse_iterator<T>(x.base() - n);
	}
}

#endif
