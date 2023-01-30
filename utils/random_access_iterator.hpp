#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP
#include "../implements/iterator_traits.hpp"

namespace ft {
template <typename T> class random_access_iterator {
public:
  typedef T iterator_type;
  typedef typename ft::iterator_traits<iterator_type>::iterator_category
      iterator_category;
  typedef typename ft::iterator_traits<iterator_type>::value_type value_type;
  typedef typename ft::iterator_traits<iterator_type>::difference_type
      difference_type;
  typedef typename ft::iterator_traits<iterator_type>::pointer pointer;
  typedef typename ft::iterator_traits<iterator_type>::reference reference;

private:
  iterator_type _cur;

public:
  // Constrcutor
  random_access_iterator() : _cur(NULL) {}
  random_access_iterator(const iterator_type &x) : _cur(x) {}

  // Copy constructor
  template <typename U>
  random_access_iterator(const random_access_iterator<U> &x) : _cur(x.base()) {}

  ~random_access_iterator() {}

  // Copy assignment operator
  random_access_iterator &operator=(const random_access_iterator &x) {
    _cur = x._cur;
    return *this;
  }

  // Getter
  iterator_type base() const { return _cur; }

  // Operator overloads
  reference operator*() const { return *_cur; }

  pointer operator->() const { return _cur; }

  random_access_iterator &operator++() {
    ++_cur;
    return *this;
  }

  random_access_iterator operator++(int) {
    random_access_iterator tmp = *this;
    ++_cur;
    return tmp;
  }

  random_access_iterator &operator--() {
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

  random_access_iterator &operator+=(difference_type n) {
    _cur += n;
    return *this;
  }

  random_access_iterator operator-(difference_type n) const {
    return random_access_iterator(_cur - n);
  }

  random_access_iterator &operator-=(difference_type n) {
    _cur -= n;
    return *this;
  }

  reference operator[](difference_type n) const { return _cur[n]; }
};

// Non-member function overloads
template <typename T1, typename T2>
inline bool operator==(const random_access_iterator<T1> &x,
                       const random_access_iterator<T2> &y) {
  return x.base() == y.base();
}

template <typename T1, typename T2>
inline bool operator<(const random_access_iterator<T1> &x,
                      const random_access_iterator<T2> &y) {
  return x.base() < y.base();
}

template <typename T1, typename T2>
inline bool operator!=(const random_access_iterator<T1> &x,
                       const random_access_iterator<T2> &y) {
  return !(x == y);
}

template <typename T1, typename T2>
inline bool operator>(const random_access_iterator<T1> &x,
                      const random_access_iterator<T2> &y) {
  return y < x;
}

template <typename T1, typename T2>
inline bool operator<=(const random_access_iterator<T1> &x,
                       const random_access_iterator<T2> &y) {
  return !(y < x);
}

template <typename T1, typename T2>
inline bool operator>=(const random_access_iterator<T1> &x,
                       const random_access_iterator<T2> &y) {
  return !(x < y);
}

template <typename T1, typename T2>
inline typename random_access_iterator<T1>::difference_type
operator+(const random_access_iterator<T1> &x,
          const random_access_iterator<T2> &y) {
  return x.base() + y.base();
}

template <typename T1, typename T2>
inline typename random_access_iterator<T1>::difference_type
operator-(const random_access_iterator<T1> &x,
          const random_access_iterator<T2> &y) {
  return x.base() - y.base();
}

template <typename T>
inline random_access_iterator<T>
operator+(typename random_access_iterator<T>::difference_type n,
          const random_access_iterator<T> &x) {
  return random_access_iterator<T>(x.base() + n);
}
} // namespace ft

#endif
