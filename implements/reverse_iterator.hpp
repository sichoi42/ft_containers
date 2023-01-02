#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP
# include <iterator>

namespace ft {
	template <class Iter>
	class reverse_iterator
	: public std::iterator<typename iterator_traits<Iter>::iterator_category,
										typename iterator_traits<Iter>::value_type,
										typename iterator_traits<Iter>::difference_type,
										typename iterator_traits<Iter>::pointer,
										typename iterator_traits<Iter>::reference> {
		protected:
			Iter _cur;

		public:
			typedef Iter																							iterator_type;
			typedef typename iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iter>::value_type				value_type;
			typedef typename iterator_traits<Iter>::difference_type		difference_type;
			typedef typename iterator_traits<Iter>::pointer						pointer;
			typedef typename iterator_traits<Iter>::reference					reference;

		public:
			// Constrcutor
			reverse_iterator() {}
			explicit reverse_iterator(iterator_type x) : _cur(x) {}

			// Copy constructor
			reverse_iterator(const reverse_iterator& x) : _cur(x._cur) {}
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
				Iter tmp = _cur;
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
	template <class Iter>
	inline bool operator==(const reverse_iterator<Iter>& x, const reverse_iterator<Iter>& y) {
		return x.base() == y.base();
	}

	template <class Iter>
	inline bool operator<(const reverse_iterator<Iter>& x, const reverse_iterator<Iter>& y) {
		return y.base() < x.base();
	}

	template <class Iter>
	inline bool operator!=(const reverse_iterator<Iter>& x, const reverse_iterator<Iter>& y) {
		return !(x == y);
	}


	template <class Iter>
	inline bool operator>(const reverse_iterator<Iter>& x, const reverse_iterator<Iter>& y) {
		return y < x;
	}

	template <class Iter>
	inline bool operator<=(const reverse_iterator<Iter>& x, const reverse_iterator<Iter>& y) {
		return !(y < x);
	}

	template <class Iter>
	inline bool operator>=(const reverse_iterator<Iter>& x, const reverse_iterator<Iter>& y) {
		return !(x < y);
	}

	template <class Iter>
	inline typename reverse_iterator<Iter>::difference_type
	operator-(const reverse_iterator<Iter>& x, const reverse_iterator<Iter>& y) {
		return y.base() - x.base();
	}

	template <class Iter>
	inline reverse_iterator<Iter>
	operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& x) {
		return reverse_iterator<Iter>(x.base() - n);
	}
}

#endif
