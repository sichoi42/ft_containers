#ifndef RBTREE_HPP
#define RBTREE_HPP
#include "./node.hpp"
#include "./tree_iterator.hpp"

namespace ft {
template <typename T, typename Key, typename Compare, typename Allocator>
class rbtree {
public:
  typedef T value_type;
  typedef Key key_type;
  typedef Compare key_compare;
  typedef Allocator allocator_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  typedef Node<value_type> node_type;
  typedef node_type *node_pointer;

  typedef tree_iterator<value_type, node_type> iterator;
  typedef tree_iterator<const value_type, node_type> const_iterator;

private:
  node_pointer _root;
  node_pointer _nil;
  size_type _size;
  key_compare _comp;
  allocator_type _alloc;

  node_pointer _new_node(const value_type &value) {
    node_pointer node = _alloc.allocate(1);
    _alloc.construct(node, value);
    node->color = RED;
    node->parent = NULL;
    node->left = _nil;
    node->right = _nil;
    return node;
  }

  void _destroy_node(node_pointer node) {
    _alloc.destroy(node);
    _alloc.deallocate(node, 1);
  }

  void _destroy_node_tree(node_pointer node) {
    if (node == _nil)
      return;
    _destroy_node_tree(node->left);
    _destroy_node_tree(node->right);
    _destroy_node(node);
  }

  node_pointer _search_tree(const value_type &value) {
    node_pointer x = _root;
    while (x != _nil) {
      if (_comp(value, x->value)) {
        x = x->left;
      } else if (_comp(x->value, value)) {
        x = x->right;
      } else {
        break;
      }
    }
    return x;
  }

  // FIXME: search와 insert를 분리해야 함.
  node_pointer _insert_node(const value_type &value) {
    node_pointer new_node = _new_node(value);

    node_pointer y = NULL;
    node_pointer x = _root;
    if (x == _nil) {
      new_node->color = BLACK;
      this->root = new_node;
      return new_node;
    }
    // x는 leaf가 되고, y는 leaf의 부모 노드가 된다.
    while (x != _nil) {
      y = x;
      if (new_node->value > x->value) {
        x = x->right;
      } else {
        x = x->left;
      }
    }
    new_node->parent = y;
    if (new_node->value > y->value) {
      y->right = new_node;
    } else {
      y->left = new_node;
    }
    if (new_node->parent->parent == NULL) {
      return;
    }
    insert_fixup(new_node);
    return new_node;
  }

public:
  // Constructor
  rbtree(const key_compare &comp, const allocator_type &alloc)
      : _size(size_type()), _comp(comp), _alloc(alloc) {
    _nil = _alloc.allocate(1);
    _alloc.construct(_nil, value_type());
    _nil->color = BLACK;
    _nil->parent = _nil;
    _nil->left = NULL;
    _nil->right = NULL;
    _root = _new_node(value_type());
    _root->color = BLACK;
  }

  // Destructor
  ~rbtree() {
    _destroy_node_tree(_root);
    _destroy_node(_nil);
  }

  // Iterators
  iterator begin() { return iterator(_root, _nil); }
  const_iterator begin() const { return const_iterator(_root, _nil); }

  iterator end() { return iterator(_nil, _nil); }
  const_iterator end() const { return const_iterator(_nil, _nil); }

  // Capacity
  bool empty() const { return _size == 0; }

  size_type size() const { return _size; }

  size_type max_size() const { return _alloc.max_size(); }

  // Modifiers
  void clear();

  // 삽입에 성공하면 삽입된 요소의 iterator와 true를 pair로 반환
  // 삽입에 실패하면 이미 존재하는 요소의 iterator와 false를 pair로 반환
  // TODO: _search_tree 구현
  ft::pair<iterator, bool> insert(const value_type &value) {
    node_pointer node = _search_tree(value);
    if (node != _nil) {
      return ft::make_pair(iterator(node, _nil), false);
    }
    return ft::make_pair(iterator(_insert_node(value))), true);
  }

  // 삽입에 성공하면 삽입된 요소의 iterator
  // 혹은 이미 존재하는 요소의 iterator를 반환
  iterator insert(iterator pos, const value_type &value);

  template <typename InputIterator>
  void insert(InputIterator first, InputIterator last);
};

} // namespace ft

#endif
