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
  typedef Compare value_compare;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  typedef Node<value_type> node_type;
  typedef node_type *node_pointer;

  typedef Allocator allocator_type;
  typedef typename allocator_type::template rebind<node_type>::other node_allocator;
  typedef std::allocator_traits<node_allocator> node_traits;

  typedef tree_iterator<value_type, node_type> iterator;
  typedef tree_iterator<const value_type, node_type> const_iterator;

private:
  node_pointer _begin;
  node_pointer _end;
  node_pointer _nil;
  size_type _size;
  value_compare _comp;
  node_allocator _alloc;

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

  void _set_root(node_pointer x) {
    _end->left = x;
    x->parent = _end;
  }

  node_pointer _get_root() const { return _end->left; }

  // u: 기증자, v: 수취자
  // u의 부모와 v의 부모를 연결한다.
  void _transplant(node_pointer u, node_pointer v) {
    // u가 root인 경우, v를 root로 만든다.
    if (u->parent == _end) {
      _set_root(v);
    } else if (u == u->parent->left) {
      // u가 부모의 왼쪽 자식인 경우, v를 u의 부모의 왼쪽 자식으로 만든다.
      u->parent->left = v;
    } else {
      // u가 부모의 오른쪽 자식인 경우, v를 u의 부모의 오른쪽 자식으로 만든다.
      u->parent->right = v;
    }
    // v의 부모를 u의 부모로 만든다.
    v->parent = u->parent;
  }

  void _swap_color(node_pointer u, node_pointer v) {
    Color tmp = u->color;
    u->color = v->color;
    v->color = tmp;
  }

  node_pointer _search_tree(const key_type &key) const {
    node_pointer node = _get_root();
    while (node != _nil) {
      if (_comp(key, node->value)) {
        node = node->left;
      } else if (_comp(node->value, key)) {
        node = node->right;
      } else {
        return node;
      }
    }
    return _end;
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

  void _left_rotate(node_pointer x) {
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

  void _right_rotate(node_pointer x) {
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
          _left_rotate(node);
        } else {
          // Case 3: new node가 부모의 왼쪽 자식인 경우
          node->parent->color = BLACK;
          gp->color = RED;
          _right_rotate(gp);
        }
      } else { // 부모가 조부모의 오른쪽 자식인 경우
        if (gp->left->color == RED) {
          gp->left->color = BLACK;
          gp->right->color = BLACK;
          gp->color = RED;
          node = gp;
        } else if (node == node->parent->left) {
          node = node->parent;
          _right_rotate(node);
        } else {
          node->parent->color = BLACK;
          gp->color = RED;
          _left_rotate(gp);
        }
      }
      if (node == _get_root()) {
        break;
      }
    }
    _get_root()->color = BLACK;
  }

  node_pointer _insert_node(const value_type &value, node_pointer &parent) {
    node_pointer new_node = _new_node(value);
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

  void _delete_fixup_left(node_pointer &x) {
    node_pointer s = x->parent->right;
    // Case-1: x의 형제 노드 s가 레드인 경우
    if (s->color == RED) {
      _swap_color(s, x->parent);
      _left_rotate(x->parent);
      s = x->parent->right;
    }
    // Case-2: s의 자식 노드가 모두 블랙인 경우
    // x는 doubly black이므로 x의 블랙과 s의 블랙을 부모에게 전가한다.
    if (s->left->color == BLACK && s->right->color == BLACK) {
      s->color = RED;
      // x의 부모가 red and black이거나 doubly black이면서 root노드인 경우
      // 블랙으로 바꾸면 상황 종료
      if (x->parent->color == RED || x->parent == _get_root()) {
        x->parent->color = BLACK;
        x = _get_root();
      } else {
        // 그렇지 않으면 기준을 부모로 올려서 다시 검사
        x = x->parent;
      }
    } else {
      // Case-3: s의 오른쪽 자식만 블랙인 경우
      if (s->right->color == BLACK) {
        _swap_color(s, s->left);
        _right_rotate(s);
        s = x->parent->right;
      }
      // Case-4: s의 왼쪽 자식만 블랙인 경우
      s->color = x->parent->color;
      x->parent->color = BLACK;
      s->right->color = BLACK;
      _left_rotate(x->parent);
      x = _get_root();
    }
  }

  void _delete_fixup_right(node_pointer &x) {
    node_pointer s = x->parent->left;
    // Case-1: x의 형제 노드 s가 레드인 경우
    if (s->color == RED) {
      _swap_color(s, x->parent);
      _right_rotate(x->parent);
      s = x->parent->left;
    }
    // Case-2: s의 자식 노드가 모두 블랙인 경우
    // x는 doubly black이므로 x의 블랙과 s의 블랙을 부모에게 전가한다.
    if (s->left->color == BLACK && s->right->color == BLACK) {
      s->color = RED;
      // x의 부모가 red and black이거나 doubly black이면서 root노드인 경우
      // 블랙으로 바꾸면 상황 종료
      if (x->parent->color == RED || x->parent == _get_root()) {
        x->parent->color = BLACK;
        x = _get_root();
      } else {
        // 그렇지 않으면 기준을 부모로 올려서 다시 검사
        x = x->parent;
      }
    } else {
      // Case-3: s의 왼쪽 자식만 블랙인 경우
      if (s->left->color == BLACK) {
        _swap_color(s, s->right);
        _left_rotate(s);
        s = x->parent->left;
      }
      // Case-4: s의 오른쪽 자식만 블랙인 경우
      s->color = x->parent->color;
      x->parent->color = BLACK;
      s->left->color = BLACK;
      _right_rotate(x->parent);
      x = _get_root();
    }
  }

  // Balancing RBTree after deletion
  void _delete_fixup(node_pointer x) {
    node_pointer root = _get_root();
    while (x != root && x->color == BLACK) {
      if (x == x->parent->left) {
        _delete_fixup_left(x);
      } else {
        _delete_fixup_right(x);
      }
    }
    x->color = BLACK;
  }

  void _delete_node(node_pointer target) {
    Color origin_color = target->color;
    node_pointer x;
    // target의 왼쪽 자식이 nil이라면, target을 target의 오른쪽 자식으로
    // 이식한다.
    if (target->left == _nil) {
      x = target->right;
      _transplant(target, x);
    } else if (target->right == _nil) {
      // target의 오른쪽 자식이 nil이라면, target을 target의 왼쪽 자식으로
      // 이식한다.
      x = target->left;
      _transplant(target, x);
    } else { // 자식 둘 다 nil이 아니라면
      node_pointer y = ft::get_successor(target, _nil);
      origin_color = y->color;
      x = y->right;
      if (y->parent == target) {
        x->parent = y;
      } else {
        _transplant(y, x);
        y->right = target->right;
        y->right->parent = y;
      }
      _transplant(target, y);
      y->left = target->left;
      y->left->parent = y;
      y->color = target->color;
    }
    _destroy_node(target);
    if (origin_color == BLACK) {
      _delete_fixup(x);
    }
  }

  // 해당 키보다 크거나 같은 첫번째 요소를 반환
  node_pointer _get_lower_bound(const key_type &key) const {
    node_pointer node = _get_root();
    node_pointer target = _end;
    while (node != _nil) {
      if (!_comp(node->value, key)) {
        target = node;
        node = node->left;
      } else {
        node = node->right;
      }
    }
    return target;
  }

  // 해당 키보다 큰 첫번째 요소를 반환
  node_pointer _get_upper_bound(const key_type &key) const {
    node_pointer node = _get_root();
    node_pointer target = _end;
    while (node != _nil) {
      if (_comp(key, node->value)) {
        target = node;
        node = node->left;
      } else {
        node = node->right;
      }
    }
    return target;
  }

public:
  // Constructor
  rbtree(const value_compare &comp, const allocator_type &alloc)
      : _size(size_type()), _comp(comp), _alloc(alloc) {
    _nil = _new_node(value_type());
    _nil->color = BLACK;
    _end = _new_node(value_type());
    _end->color = BLACK;
    _begin = _end;
  }

  // Copy Constructor
  rbtree(const rbtree &rb) : _size(size_type()), _comp(rb._comp), _alloc(rb._alloc) {
      _nil = _new_node(value_type());
      _nil->color = BLACK;
      _end = _new_node(value_type());
      _end->color = BLACK;
      _begin = _end;
      insert(rb.begin(), rb.end());
  }

  rbtree &operator=(const rbtree &rb){
    if (this != &rb) {
      rbtree tmp(rb);
      swap(tmp);
    }
    return *this;
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
  void clear() { erase(begin(), end()); }

  // 삽입에 성공하면 삽입된 요소의 iterator와 true를 pair로 반환
  // 삽입에 실패하면 이미 존재하는 요소의 iterator와 false를 pair로 반환
  ft::pair<iterator, bool> insert(const value_type &value) {
    node_pointer parent = _find_post_parent(value);
    if (parent != _end) {
      if (!_comp(parent->value, value) && !_comp(value, parent->value))
        return ft::make_pair(iterator(parent, _nil), false);
    }
    return ft::make_pair(iterator(_insert_node(value, parent), _nil), true);
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
    if (pos == begin()) {
      _begin = tmp.base();
    }
    --_size;
    _delete_node(pos.base());
    return tmp;
  }

  size_type erase(const key_type &key) {
    node_pointer target = _search_tree(key);
    if (target == _end) {
      return 0;
    }
    erase(iterator(target, _nil));
    return 1;
  }

  void erase(iterator first, iterator last) {
    while (first != last) {
      first = erase(first);
    }
  }

  void swap(rbtree &rb) {
    std::swap(_begin, rb._begin);
    std::swap(_end, rb._end);
    std::swap(_nil, rb._nil);
    std::swap(_size, rb._size);
    std::swap(_comp, rb._comp);
    std::swap(_alloc, rb._alloc);
  }

  iterator find(const key_type &key) {
    node_pointer node = _search_tree(key);
    return iterator(node, _nil);
  }

  const_iterator find(const key_type &key) const {
    node_pointer node = _search_tree(key);
    return const_iterator(node, _nil);
  }

  // 해당 키보다 크거나 같은 첫번째 요소의 iterator를 반환
  iterator lower_bound(const key_type &key) {
    return iterator(_get_lower_bound(key), _nil);
  }

  // 해당 키보다 크거나 같은 첫번째 요소의 const_iterator를 반환
  const_iterator lower_bound(const key_type &key) const {
    return const_iterator(_get_lower_bound(key), _nil);
  }

  // 해당 키보다 큰 첫번째 요소의 iterator 반환
  iterator upper_bound(const key_type &key) {
    return iterator(_get_upper_bound(key), _nil);
  }

  // 해당 키보다 큰 첫번째 요소의 const_iterator 반환
  const_iterator upper_bound(const key_type &key) const {
    return const_iterator(_get_upper_bound(key), _nil);
  }

  // first로 lower_bound, second로 upper_bound를 반환
  ft::pair<iterator, iterator> equal_range(const key_type &key) {
    return ft::make_pair(lower_bound(key), upper_bound(key));
  }

  // first로 const lower_bound, second로 const upper_bound를 반환
  ft::pair<const_iterator, const_iterator>
  equal_range(const key_type &key) const {
    const_iterator lower = lower_bound(key);
    const_iterator upper = upper_bound(key);
    return ft::make_pair(lower_bound(key), upper_bound(key));
  }
};

} // namespace ft

#endif
