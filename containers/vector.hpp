#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP
#include "../implements/enable_if.hpp"
#include "../implements/equal.hpp"
#include "../implements/is_integral.hpp"
#include "../implements/lexicographical_compare.hpp"
#include "../implements/random_access_iterator.hpp"
#include "../implements/reverse_iterator.hpp"
#include <memory>
#include <stdexcept>

namespace ft {
template <typename T, typename Allocator = std::allocator<T>> class vector {
public:
  typedef T value_type;
  typedef Allocator allocator_type;

  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;

  typedef typename allocator_type::size_type size_type;
  typedef typename allocator_type::difference_type difference_type;

  typedef ft::random_access_iterator<pointer> iterator;
  typedef ft::random_access_iterator<const_pointer> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

private:
  size_type _size;
  size_type _capacity;
  pointer _data;
  allocator_type _alloc;

  size_type _new_capacity(size_type new_capacity) const {
    const size_type _max_size = max_size();
    const size_type _double_capacity = 2 * _capacity;
    if (_double_capacity >= _max_size) {
      return _max_size;
    }
    return _double_capacity > new_capacity ? _double_capacity : new_capacity;
  }

public:
  // Constrcutor
  explicit vector(const allocator_type &alloc = allocator_type())
      : _size(0), _capacity(0), _data(NULL), _alloc(alloc) {}

  explicit vector(size_type n, const value_type &value = value_type(),
                  const allocator_type &alloc = allocator_type())
      : _size(n), _capacity(n), _alloc(alloc) {
    if (n > 0) {
      _data = _alloc.allocate(n);
      for (size_type i = 0; i < n; i++) {
        _data[i] = value;
      }
    } else {
      _data = NULL;
    }
  }

  template <typename InputIterator>
  // NOTE: push_back에 의해 capacity와 size가 일치하지 않을 수 있다.
  vector(InputIterator first, InputIterator last,
         typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type
             * = 0)
      : _size(0), _capacity(0), _data(NULL) {
    while (first != last) {
      push_back(*first);
      first++;
    }
    pointer _new_data = _alloc.allocate(_size);
    for (size_type i = 0; i < _size; i++) {
      _new_data[i] = _data[i];
    }
    _alloc.deallocate(_data, _capacity);
    _data = _new_data;
    _capacity = _size;
  }

  // Copy constructor
  vector(const vector &vec) {
    if (this != &vec) {
      *this = vec;
    }
  }

  // Destructor
  ~vector(){};

  // Copy assignment operator
  vector &operator=(const vector &vec) {
    if (this != &vec) {
      _size = vec._size;
      _capacity = vec._capacity;
      _alloc = vec._alloc;
      _data = _alloc.allocate(_capacity);
      for (size_type i = 0; i < _size; i++) {
        _data[i] = vec._data[i];
      }
    }
    return *this;
  }

  // Member function
  void assign(size_type n, const_reference value) {
    clear();
    resize(n, value);
  }

  template <typename InputIterator>
  // NOTE: push_back에 의해 capacity와 size가 일치하지 않을 수 있다.
  void assign(
      InputIterator first, InputIterator last,
      typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * =
          0) {
    clear();
    while (first != last) {
      push_back(*first);
      first++;
    }
  }

  allocator_type get_allocator() const { return _alloc; }

  // Element access
  reference at(size_type pos) {
    if (pos >= _size) {
      throw std::out_of_range("vector");
    }
    return _data[pos];
  }
  const_reference at(size_type pos) const {
    if (pos >= _size) {
      throw std::out_of_range("vector");
    }
    return _data[pos];
  }

  reference operator[](size_type pos) { return _data[pos]; }
  const_reference operator[](size_type pos) const { return _data[pos]; }

  reference front() { return _data[0]; }
  const_reference front() const { return _data[0]; }

  reference back() { return _data[_size - 1]; }
  const_reference back() const { return _data[_size - 1]; }

  pointer data() { return _data; }
  const_pointer data() const { return _data; }

  // Iterators
  iterator begin() { return iterator(_data); }
  const_iterator begin() const { return const_iterator(_data); }

  iterator end() { return iterator(_data + _size); }
  const_iterator end() const { return const_iterator(_data + _size); }

  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }

  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  // Capacity
  bool empty() const { return _size == 0; }

  size_type size() const { return _size; }

  size_type max_size() const { return _alloc.max_size(); }

  void reserve(size_type new_capacity) {
    if (new_capacity > _capacity) {
      pointer new_data = _alloc.allocate(new_capacity);
      for (size_type i = 0; i < _size; i++) {
        new_data[i] = _data[i];
      }
      _alloc.deallocate(_data, _capacity);
      _data = new_data;
      _capacity = new_capacity;
    }
  }

  size_type capacity() const { return _capacity; }

  // Modifiers
  void clear() { _size = 0; }

  iterator insert(iterator pos, const_reference value) {
    size_type start = static_cast<size_type>(pos - begin());
    if (_size == _capacity) {
      reserve(_new_capacity(_capacity + 1));
    }
    for (size_type i = _size; i > start; i--) {
      _data[i] = _data[i - 1];
    }
    _data[start] = value;
    ++_size;
    return iterator(&_data[start]);
  }

  iterator insert(iterator pos, size_type n, const_reference value) {
    size_type start = static_cast<size_type>(pos - begin());
    if (_size + n > _capacity) {
      reserve(_new_capacity(_size + n));
    }
    for (size_type i = _size; i > start; i--) {
      _data[i + n - 1] = _data[i - 1];
    }
    for (size_type i = 0; i < n; i++) {
      _data[start + i] = value;
    }
    _size += n;
    return iterator(&_data[start]);
  }

  template <typename InputIterator>
  iterator insert(
      iterator pos, InputIterator first, InputIterator last,
      typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * =
          0) {
    vector new_data(first, last);
    size_type n = new_data.size();
    size_type start = static_cast<size_type>(pos - begin());
    if (_size + n > _capacity) {
      reserve(_new_capacity(_size + n));
    }
    for (size_type i = _size; i > start; i--) {
      _data[i + n - 1] = _data[i - 1];
    }
    for (size_type i = 0; i < n; i++) {
      _data[start + i] = new_data[i];
    }
    _size += n;
    return iterator(&_data[start]);
  }

  iterator erase(const_iterator pos) {
    size_type start = static_cast<size_type>(pos - begin());
    for (size_type i = start; i < _size - 1; i++) {
      _data[i] = _data[i + 1];
    }
    --_size;
    return iterator(&_data[start]);
  }

  iterator erase(const_iterator first, const_iterator last) {
    difference_type l = first - begin();
    difference_type r = last - begin();
    size_type n = static_cast<size_type>(r - l);
    for (size_type i = r; i < _size; i++) {
      _data[i - n] = _data[i];
    }
    _size -= n;
    return iterator(&_data[l]);
  }

  void push_back(const_reference value) {
    if (_size == _capacity) {
      reserve(_new_capacity(_capacity + 1));
    }
    ++_size;
    back() = value;
  }

  void pop_back() { --_size; }

  // void	resize(size_type n) {
  // 	resize(n, 0);
  // }

  void resize(size_type n, value_type value = value_type()) {
    if (n > _size) {
      if (n > _capacity) {
        reserve(_new_capacity(n));
      }
      for (size_type i = _size; i < n; i++) {
        _data[i] = value;
      }
    }
    _size = n;
  }

  void swap(vector &vec) {
    std::swap(_size, vec._size);
    std::swap(_capacity, vec._capacity);
    std::swap(_data, vec._data);
    std::swap(_alloc, vec._alloc);
  }
};
// Non-member function overloads
template <typename T, typename Allocator>
bool operator==(const ft::vector<T, Allocator> &x,
                const ft::vector<T, Allocator> &y) {
  return (x.size() == y.size()) && ft::equal(x.begin(), x.end(), y.begin());
}

template <typename T, typename Allocator>
bool operator!=(const ft::vector<T, Allocator> &x,
                const ft::vector<T, Allocator> &y) {
  return !(x == y);
}

template <typename T, typename Allocator>
bool operator<(const ft::vector<T, Allocator> &x,
               const ft::vector<T, Allocator> &y) {
  return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template <typename T, typename Allocator>
bool operator<=(const ft::vector<T, Allocator> &x,
                const ft::vector<T, Allocator> &y) {
  return !(y < x);
}

template <typename T, typename Allocator>
bool operator>(const ft::vector<T, Allocator> &x,
               const ft::vector<T, Allocator> &y) {
  return y < x;
}

template <typename T, typename Allocator>
bool operator>=(const ft::vector<T, Allocator> &x,
                const ft::vector<T, Allocator> &y) {
  return !(x < y);
}

// Non-member function
template <typename T, typename Allocator>
void swap(ft::vector<T, Allocator> &x, ft::vector<T, Allocator> &y) {
  x.swap(y);
}
} // namespace ft

#endif

/*
        STL Reference
        https://en.cppreference.com/w/cpp/container/stack

        STL Base Header
        https://en.cppreference.com/w/cpp/header/stack
*/
