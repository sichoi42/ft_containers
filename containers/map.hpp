#ifndef MAP_HPP
#define MAP_HPP

#include "./implements/equal.hpp"
#include "./implements/lexicographical_compare.hpp"
#include "./implements/pair.hpp"
#include "./implements/reverse_iterator.hpp"
#include "./utils/rbtree.hpp"
#include <exception>
#include <functional>
#include <memory>

namespace ft {
template <typename U, typename V, typename Compare = std::less<U>,
          typename Allocator = std::allocator<std::pair<const U, V>>>
class map {
public:
  typedef U key_type;
  typedef V mapped_type; // type of value of pair
  typedef ft::pair<U, V> value_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef Compare key_compare;
  typedef Allocator allocator_type;

  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;

  // FIXME: implement rbtree
  typedef typename rbtree<value_type, key_type, value_compare,
                          allocator_type>::iterator iterator;
  typedef typename rbtree<value_type, key_type, value_compare,
                          allocator_type>::const_iterator const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

  class value_compare
      : public std::binary_function<value_type, value_type, bool> {
  protected:
    key_compare comp;

  public:
    value_compare(key_compare c) : comp(c) {}
    ~value_compare() {}

    bool operator()(const value_type &x, const value_type &y) const {
      return comp(x.first, y.first);
    }
    bool operator()(const value_type &x, const value_type &y) const {
      return comp(x.first, y);
    }
    bool operator()(const value_type &x, const value_type &y) const {
      return comp(x, y.first);
    };
  };

private:
  rbtree<value_type, key_type, key_compare, allocator_type> _tree;
  key_compare _key_comp;
  value_compare _value_comp;
  allocator_type _alloc;

public:
  // Constructor
  explicit map(const key_compare &key_comp = key_compare(),
               const allocator_type &alloc = allocator_type())
      : _key_comp(key_comp), _value_comp(key_comp), _alloc(alloc), _tree() {}

  // FIXME: need enable_if
  template <typename InputIterator>
  map(InputIterator first, InputIterator last,
      const key_compare &key_comp = key_compare(),
      const allocator_type &alloc = allocator_type())
      : _key_comp(key_comp), _value_comp(key_comp), _alloc(alloc), _tree() {}

  // Copy Constructor
  map(const map &m) {
    if (this != &m) {
      *this = m;
    }
  }

  // Destructor
  ~map() {}

  // Copy Assignment Operator
  // FIXME: 아래 코드는 잘못된 코드임. 수정 필요
  map &operator=(const map &m) {
    if (this != &m) {
      _key_comp = m._key_comp;
      _value_comp = m._value_comp;
      _alloc = m._alloc;
      _tree = _alloc.allocate(m._tree.size());
    }
    return *this;
  }

  // Element access
  mapped_type &at(const key_type &key) {
    iterator it = find(key);
    if (it == end()) {
      throw std::out_of_range("map::at");
    }
    return it->second;
  }

  const mapped_type &at(const key_type &key) const {
    iterator it = find(key);
    if (it == end()) {
      throw std::out_of_range("map::at");
    }
    return it->second;
  }

  // TODO: 개선 필요
  mapped_type &operator[](const key_type &key) {
    iterator it = find(key);
    if (it != end()) {
      return it->second;
    }
    it = insert(ft::make_pair(key, mapped_type())).first;
    return it->second;
  }

  // Iterators
  iterator begin() { return _tree.begin(); }
  const_iterator begin() const { return _tree.begin(); }

  iterator end() { return _tree.end(); }
  const_iterator end() const { return _tree.end(); }

  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }

  // Capacity

  // container is empty
  bool empty() const;

  // get number of elements
  size_type size() const;

  // get max number of elements
  size_type max_size() const;

  // Modifiers

  // erase all elements
  void clear();

  // 삽입에 성공하면 삽입된 요소의 iterator와 true를 pair로 반환
  // 삽입에 실패하면 이미 존재하는 요소의 iterator와 false를 pair로 반환
  ft::pair<iterator, bool> insert(const value_type &value);

  // 삽입에 성공하면 삽입된 요소의 iterator
  // 혹은 이미 존재하는 요소의 iterator를 반환
  iterator insert(iterator pos, const value_type &value);

  // FIXME: need enable_if
  template <typename InputIterator>
  void insert(InputIterator first, InputIterator last);

  void erase(iterator pos);

  void erase(iterator first, iterator last);

  void swap(map &x);

  // Lookup

  // find element with key equivalent to key
  iterator find(const key_type &key);

  const_iterator find(const key_type &key) const;

  // count elements with key equivalent to key
  // NOTE: map은 key가 unique하기 때문에 0 또는 1을 반환
  size_type count(const key_type &key) const {
    return find(key) != end() ? 1 : 0;
  }

  // 해당 키보다 크거나 같은 첫번째 요소의 iterator를 반환
  iterator lower_bound(const key_type &key);

  // 해당 키보다 크거나 같은 첫번째 요소의 const_iterator를 반환
  const_iterator lower_bound(const key_type &key) const;

  // 해당 키보다 작거나 같은 첫번째 요소의 iterator를 반환
  iterator upper_bound(const key_type &key);

  // 해당 키보다 작거나 같은 첫번째 요소의 const_iterator를 반환
  const_iterator upper_bound(const key_type &key) const;

  // first로 lower_bound, second로 upper_bound를 반환
  ft::pair<iterator, iterator> equal_range(const key_type &key);

  // first로 const lower_bound, second로 const upper_bound를 반환
  ft::pair<const_iterator, const_iterator>
  equal_range(const key_type &key) const;

  // Observers

  // return key comparison object
  key_compare key_comp() const { return _key_comp; }

  // return value comparison object
  value_compare value_comp() const { return _value_comp; }
};

// Non-member function overloads
template <typename U, typename V, typename Compare, typename Allocator>
bool operator==(const ft::map<U, V, Compare, Allocator> &x,
                const ft::map<U, V, Compare, Allocator> &y) {
  return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin());
}

template <typename U, typename V, typename Compare, typename Allocator>
bool operator!=(const ft::map<U, V, Compare, Allocator> &x,
                const ft::map<U, V, Compare, Allocator> &y) {
  return !(x == y);
}

template <typename U, typename V, typename Compare, typename Allocator>
bool operator<(const ft::map<U, V, Compare, Allocator> &x,
               const ft::map<U, V, Compare, Allocator> &y) {
  return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template <typename U, typename V, typename Compare, typename Allocator>
bool operator<=(const ft::map<U, V, Compare, Allocator> &x,
                const ft::map<U, V, Compare, Allocator> &y) {
  return !(y < x);
}

template <typename U, typename V, typename Compare, typename Allocator>
bool operator>(const ft::map<U, V, Compare, Allocator> &x,
               const ft::map<U, V, Compare, Allocator> &y) {
  return y < x;
}

template <typename U, typename V, typename Compare, typename Allocator>
bool operator>=(const ft::map<U, V, Compare, Allocator> &x,
                const ft::map<U, V, Compare, Allocator> &y) {
  return !(x < y);
}

template <typename U, typename V, typename Compare, typename Allocator>
void swap(ft::map<U, V, Compare, Allocator> &x,
          ft::map<U, V, Compare, Allocator> &y) {
  x.swap(y);
}

} // namespace ft

#endif
