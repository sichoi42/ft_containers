#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft {
template <typename T1, typename T2> struct pair {
  typedef T1 first_type;
  typedef T2 second_type;

  first_type first;
  second_type second;

  pair() : first(first_type()), second(second_type()) {}
  pair(const first_type &a, const second_type &b) : first(a), second(b) {}

  template <typename U1, typename U2>
  pair(const pair<U1, U2> &p) : first(p.first), second(p.second) {}

  pair &operator=(const pair &p) {
    if (this != &p) {
      first = p.first;
      second = p.second;
    }
    return *this;
  }
  ~pair() {}
};

// Non-member functions
template <typename T1, typename T2> ft::pair<T1, T2> make_pair(T1 x, T2 y) {
  return ft::pair<T1, T2>(x, y);
}

template <typename T1, typename T2>
bool operator==(const ft::pair<T1, T2> &x, const ft::pair<T1, T2> &y) {
  return x.first == y.first && x.second == y.second;
}

template <typename T1, typename T2>
bool operator!=(const ft::pair<T1, T2> &x, const ft::pair<T1, T2> &y) {
  return !(x == y);
}

template <typename T1, typename T2>
bool operator<(const ft::pair<T1, T2> &x, const ft::pair<T1, T2> &y) {
  return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
}

template <typename T1, typename T2>
bool operator<=(const ft::pair<T1, T2> &x, const ft::pair<T1, T2> &y) {
  return !(y < x);
}

template <typename T1, typename T2>
bool operator>(const ft::pair<T1, T2> &x, const ft::pair<T1, T2> &y) {
  return y < x;
}

template <typename T1, typename T2>
bool operator>=(const ft::pair<T1, T2> &x, const ft::pair<T1, T2> &y) {
  return !(x < y);
}
} // namespace ft

#endif
