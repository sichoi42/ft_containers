#include "./node.hpp"

namespace ft {
template <typename U, typename V> class tree_iterator {
public:
  typedef U value_type;
  typedef V *iterator_type;

  typedef value_type *pointer;
  typedef value_type &reference;

  typedef std::bidirectional_iterator_tag iterator_category;
  typedef typename ft::iterator_traits<iterator_type>::difference_type
      difference_type;
  typedef typename ft::iterator_traits<iterator_type>::value_type node_type;
  typedef typename ft::iterator_traits<iterator_type>::pointer node_pointer;
  typedef typename ft::iterator_traits<iterator_type>::reference node_reference;

private:
  node_pointer _cur;
  node_pointer _nil;

public:
  tree_iterator() : _cur(NULL), _nil(NULL) {}
  tree_iterator(node_pointer x, node_pointer nil) : _cur(x), _nil(nil) {}
  tree_iterator(const tree_iterator &x) : _cur(x._cur), _nil(x._nil) {}
  ~tree_iterator() {}

  tree_iterator &operator=(const tree_iterator &x) {
    if (this != &x) {
      _cur = x._cur;
      _nil = x._nil;
    }
    return *this;
  }

  // element access
  node_pointer base() const { return _cur; }

  pointer operator->() const { return &(_cur->value); }

  reference operator*() const { return _cur->value; }

  // increment / decrement
  tree_iterator &operator++(void) {
    _cur = ft::get_successor(_cur, _nil);
    return *this;
  }

  tree_iterator operator++(int) {
    tree_iterator tmp = *this;
    _cur = ft::get_successor(_cur, _nil);
    return tmp;
  }

  tree_iterator &operator--(void) {
    _cur = ft::get_predecessor(_cur, _nil);
    return *this;
  }

  tree_iterator operator--(int) {
    tree_iterator tmp = *this;
    _cur = ft::get_predecessor(_cur, _nil);
    return tmp;
  }

  // relational operators
  template <typename T>
  bool operator==(const tree_iterator<T, node_type> &x) const {
    return _cur == x.base();
  }

  template <typename T>
  bool operator!=(const tree_iterator<T, node_type> &x) const {
    return !(*this == x);
  }

  friend bool operator==(const tree_iterator &x, const tree_iterator &y) {
    return x._cur == y._cur;
  }

  friend bool operator!=(const tree_iterator &x, const tree_iterator &y) {
    return !(x == y);
  }
};
} // namespace ft
