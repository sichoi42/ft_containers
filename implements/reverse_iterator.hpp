#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP
# include <iterator>

namespace ft {
	template <typename Iterator>
	class reverse_iterator
	: public std::iterator<typename std::iterator_traits<Iterator>::iterator_category,
										typename std::iterator_traits<Iterator>::value_type,
										typename std::iterator_traits<Iterator>::difference_type,
										typename std::iterator_traits<Iterator>::pointer,
										typename std::iterator_traits<Iterator>::reference> {
		protected:
			Iterator _cur;

		public:
			typedef Iterator																							iterator_type;
			typedef typename std::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename std::iterator_traits<Iterator>::value_type				value_type;
			typedef typename std::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename std::iterator_traits<Iterator>::pointer						pointer;
			typedef typename std::iterator_traits<Iterator>::reference					reference;

		public:
			// Constrcutor
			reverse_iterator() {}
			explicit reverse_iterator(iterator_type x) : _cur(x) {}

			// Copy constructor
			reverse_iterator(const reverse_iterator& x) : _cur(x._cur) {}
			template <typename Iter>
			reverse_iterator(const reverse_iterator<Iterator>& x) : _cur(x.base()) {}

			// Copy assignment operator
			reverse_iterator& operator=(const reverse_iterator& x) {
				if (this != &x) {
					_cur = x._cur;
				}
				return *this;
			}
			template <typename Iter>
			reverse_iterator& operator=(const reverse_iterator<Iterator>& x) {
				if (this != &x) {
					_cur = x.base();
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
	template <class Iterator>
	inline bool operator==(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return x.base() == y.base();
	}

	template <class Iterator>
	inline bool operator<(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return y.base() < x.base();
	}

	template <class Iterator>
	inline bool operator!=(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return !(x == y);
	}


	template <class Iterator>
	inline bool operator>(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return y < x;
	}

	template <class Iterator>
	inline bool operator<=(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return !(y < x);
	}

	template <class Iterator>
	inline bool operator>=(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return !(x < y);
	}

	template <class Iterator>
	inline typename reverse_iterator<Iterator>::difference_type
	operator-(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return y.base() - x.base();
	}

	template <class Iterator>
	inline reverse_iterator<Iterator>
	operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& x) {
		return reverse_iterator<Iterator>(x.base() - n);
	}
}

#endif
