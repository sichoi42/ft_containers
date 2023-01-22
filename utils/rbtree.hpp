#ifndef RBTREE_HPP
#define RBTREE_HPP
#include "./node.hpp"
#include "./tree_iterator.hpp"

namespace ft {
template <typename T, typename Key, typename Compare, typename Allocator>
class rbtree {
public:
  typedef T value_type; // ft::pair<U, V> of map
  typedef Key key_type; // U of map
  typedef Compare key_compare;
  typedef Allocator allocator_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  typedef Node<value_type> node_type;
  typedef node_type *node_pointer;

  typedef tree_iterator<value_type, node_type> iterator;
  typedef tree_iterator<const value_type, node_type> const_iterator;

private:
  node_pointer _begin;
  node_pointer _end;
  node_pointer _nil;
  size_type _size;
  key_compare _comp;
  allocator_type _alloc;

  node_pointer _new_node(const value_type &value) {
    node_pointer node = _alloc.allocate(1);
    _alloc.construct(node, value);
    node->color = RED;
    node->parent = _nil;
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

  node_pointer _set_root(node_pointer x) {
    _end->left = x;
    x->parent = _end;
  }

  node_pointer _get_root() { return _end->left; }

  node_pointer _search_tree(const key_type &key) const {
    node_pointer node = _get_root();
    while (node != _nil) {
      if (_comp(key, node->value)) {
        node = node->left;
      } else if (_comp(node->value, key)) {
        node = node->right;
      } else {
        break;
      }
    }
    return node;
  }

  node_pointer _find_post_parent(const value_type &value,
                                 node_pointer candidate = NULL) {
    if (candidate && candidate != _end) {
      // 후보군의 left로 새 값을 넣을 수 있는 경우
      if (_comp(value, candidate->value) && candidate->left == _nil) {
        // 후보군이 begin이거나, value가 후보군의 predecessor보다는 값이 큰 경우
        iterator it = iterator(candidate, _nil);
        if (it == begin() || _comp(*(--it), value)) {
          return candidate;
        }
        // 후보군의 right로 새 값을 넣을 수 있는 경우
      } else if (_comp(candidate->value, value) && candidate->right == _nil) {
        // value가 후보군의 successor보다는 값이 작은 경우
        iterator it = iterator(candidate, _nil);
        if (_comp(value, *(++it))) {
          return candidate;
        }
      }
    }
    node_pointer node = _get_root();
    node_pointer parent = _end;
    while (node != _nil) {
      parent = node;
      if (_comp(value, node->value)) {
        node = node->left;
      } else if (_comp(node->value, value)) {
        node = node->right;
      } else { // 노드가 이미 트리에 존재하는 경우 parent가 해당 노드가 된다.
        break;
      }
    }
    return parent;
  }

  void left_rotate(node_pointer x) {
    node_pointer y = x->right;
    // y의 왼쪽 서브트리를 x의 오른쪽 서브트리로 설정한다.
    x->right = y->left;
    // y가 왼쪽 서브트리를 가진다면, y의 왼쪽 서브트리의 부모를 x로 설정한다.
    if (y->left != _nil) {
      y->left->parent = x;
    }
    // y의 부모를 x의 부모로 설정한다.
    y->parent = x->parent;
    if (x->parent == _end) {
      _set_root(y);
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else { // x가 부모의 왼쪽 자식이라면
      x->parent->right = y;
    }
    // x의 부모를 y로 설정한다.
    // y의 왼쪽 서브트리를 x로 설정한다.
    x->parent = y;
    y->left = x;
  }

  void right_rotate(node_pointer x) {
    node_pointer y = x->left;
    // y의 오른쪽 서브트리를 x의 왼쪽 서브트리로 설정한다.
    x->left = y->right;
    // y가 오른쪽 서브트리를 가진다면, y의 오른쪽 서브트리의 부모를 x로
    // 설정한다.
    if (y->right != _nil) {
      y->right->parent = x;
    }
    // y의 부모를 x의 부모로 설정한다.
    y->parent = x->parent;
    if (x->parent == _end) {
      _set_root(y);
    } else if (x == x->parent->right) {
      x->parent->right = y;
    } else { // x가 부모의 왼쪽 자식이라면
      x->parent->left = y;
    }
    // x의 부모를 y로 설정한다.
    // y의 오른쪽 서브트리를 x로 설정한다.
    x->parent = y;
    y->right = x;
  }

  void _insert_fixup(node_pointer node) {
    // new node의 부모의 색깔이 레드인 동안 반복한다.
    while (node->parent->color == RED) {
      node_pointer gp = node->parent->parent;
      // 부모가 조부모의 오른쪽 자식인 경우
      if (node->parent == gp->left) {
        // Case 1: 부모의 형제 노드가 레드인 경우
        if (gp->right->color == RED) {
          gp->right->color = BLACK;
          gp->left->color = BLACK;
          gp->color = RED;
          node = gp;
        }
        // Case 2: new node가 부모의 오른쪽 자식인 경우
        else if (node == node->parent->right) {
          node = node->parent;
          left_rotate(node);
        } else {
          // Case 3: new node가 부모의 왼쪽 자식인 경우
          node->parent->color = BLACK;
          gp->color = RED;
          right_rotate(gp);
        }
      } else { // 부모가 조부모의 오른쪽 자식인 경우
        if (gp->left->color == RED) {
          gp->left->color = BLACK;
          gp->right->color = BLACK;
          gp->color = RED;
          node = gp;
        } else if (node == node->parent->left) {
          node = node->parent;
          right_rotate(node);
        } else {
          node->parent->color = BLACK;
          gp->color = RED;
          left_rotate(gp);
        }
      }
      if (node == _get_root()) {
        break;
      }
    }
    _get_root()->color = BLACK;
  }

  // TODO: left 먼저 확인하도록 수정
  node_pointer _insert_node(const value_type &value, node_pointer &parent) {
    node_pointer new_node = new_node(value);
    if (parent == _end) {
      _set_root(new_node);
    } else if (_comp(value, parent->value)) {
      parent->left = new_node;
    } else {
      parent->right = new_node;
    }
    new_node->parent = parent;
    // 최솟값이 들어온 경우 begin을 갱신한다.
    if (_begin == _end || _comp(new_node->value, _begin->value)) {
      _begin = new_node;
    }
    ++_size;
    return new_node;
  }

  _delete_node() {}

public:
  // Constructor
  rbtree(const key_compare &comp, const allocator_type &alloc)
      : _size(size_type()), _comp(comp), _alloc(alloc) {
    _nil = _new_node(value_type());
    _nil->color = BLACK;
    _end = _new_node(value_type());
    _end->color = BLACK;
    _begin = _end;
  }

  // Destructor
  ~rbtree() {
    _destroy_node_tree(_end);
    _destroy_node(_nil);
  }

  // Iterators
  iterator begin() { return iterator(_begin, _nil); }
  const_iterator begin() const { return const_iterator(_begin, _nil); }

  iterator end() { return iterator(_end, _nil); }
  const_iterator end() const { return const_iterator(_end, _nil); }

  // Capacity
  bool empty() const { return _size == 0; }

  size_type size() const { return _size; }

  size_type max_size() const { return _alloc.max_size(); }

  // Modifiers
  void clear();

  // 삽입에 성공하면 삽입된 요소의 iterator와 true를 pair로 반환
  // 삽입에 실패하면 이미 존재하는 요소의 iterator와 false를 pair로 반환
  ft::pair<iterator, bool> insert(const value_type &value) {
    node_pointer parent = _find_post_parent(value);
    if (parent != _end) {
      if (!_comp(parent->value, value) && !_comp(value, parent->value))
        return ft::make_pair(iterator(parent, _nil), false);
    }
    return ft::make_pair(iterator(_insert_node(value, parent))), true);
  }

  // 삽입에 성공하면 삽입된 요소의 iterator
  // 혹은 이미 존재하는 요소의 iterator를 반환
  iterator insert(iterator pos, const value_type &value) {
    node_pointer parent = _find_post_parent(value, pos.base());
    if (parent != _end) {
      if (!_comp(parent->value, value) && !_comp(value, parent->value))
        return iteartor(parent, _nil);
    }
    return iterator(_insert_node(value, parent), _nil);
  }

  template <typename InputIterator>
  void insert(InputIterator first, InputIterator last) {
    while (first != last) {
      insert(*first);
      ++first;
    }
  }

  iterator erase(iterator pos) {
    iterator tmp(pos);
    ++tmp;
    if (pos.base() == _begin) {
      _begin = tmp.base();
    }
    --_size;
    _delete_node(pos->base());
    return tmp;
  }

  size_type erase(const key_type &key) {
    node_pointer target = _search_tree(key);
    if (target == _nil) {
      return 0;
    }
    erase(target);
    return 1;
  }

  void erase(iterator first, iterator last) {
    while (first != last) {
      first = erase(*first);
    }
  }

  iterator find(const key_type &key) {
    node_pointer node = _search_tree(key);
    if (node == _nil) {
      return iterator(_nil, _nil);
    }
  }

  const_iterator find(const key_type &key) const {}
};

} // namespace ft

#endif
