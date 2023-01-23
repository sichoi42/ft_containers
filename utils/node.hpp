#ifndef NODE_HPP
#define NODE_HPP

// iostream이 정의되지 않은 경우에만 정의
#ifndef IOSTREAM_HPP
#include <iostream>
#endif

namespace ft {
enum Color { RED, BLACK };

template <typename T> class Node {
  typedef T value_type;

  public:
  value_type value;
  Node *left;
  Node *right;
  Node *parent;
  Color color;

  Node() : parent(NULL), left(NULL), right(NULL), value(value_type()), color(BLACK) {}

  Node(const value_type& value) : parent(NULL), left(NULL), right(NULL), value(value), color(BLACK) {}

  Node(const Node& n) {
    if (this != &n) {
      value = n.value;
      left = n.left;
      right = n.right;
      parent = n.parent;
      color = n.color;
    }
  }

  Node &operator=(const Node& n) {
    if (this != &n) {
      *this = n;
    }
    return *this;
  }
};

// Non-member function for node

/* Tree debug tools */
template <typename NodePtr> void preorder_helper(NodePtr node, NodePtr nil) {
  if (node != nil) {
    std::cout << node->value << " ";
    preorder_helper(node->left);
    preorder_helper(node->right);
  }
}

template <typename NodePtr> void inorder_helper(NodePtr node, NodePtr nil) {
  if (node != nil) {
    inorder_helper(node->left);
    std::cout << node->value << " ";
    inorder_helper(node->right);
  }
}

template <typename NodePtr> void postorder_helper(NodePtr node, NodePtr nil) {
  if (node != nil) {
    postorder_helper(node->left);
    postorder_helper(node->right);
    std::cout << node->value << " ";
  }
}

#define BG_RED "\033[41m"
#define BG_BLACK "\033[40m"
#define BG_RESET "\033[0m"
template <typename NodePtr>
void print_helper(NodePtr root, std::string indent, bool last, NodePtr nil) {
  if (root != nil) {
    std::cout << indent;
    if (last) {
      std::cout << "R----";
      indent += "   ";
    } else {
      std::cout << "L----";
      indent += "|  ";
    }

    Color c = root->color ? RED : BLACK;
    // c가 RED인 경우 빨간색 배경으로 출력
    if (c == RED) {
      std::cout << BG_RED << root->value << "(" << c << ")" << BG_RESET
                << std::endl;
    } else {
      std::cout << BG_BLACK << root->value << "(" << c << ")" << BG_RESET
                << std::endl;
    }
    print_helper(root->left, indent, false);
    print_helper(root->right, indent, true);
  }
}
/* End of Tree debug tools */

template <typename NodePtr> NodePtr get_min_node(NodePtr node, NodePtr nil) {
  while (node->left != nil) {
    node = node->left;
  }
  return node;
}

template <typename NodePtr> NodePtr get_max_node(NodePtr node, NodePtr nil) {
  while (node->right != nil) {
    node = node->right;
  }
  return node;
}

// 선택한 노드의 오른쪽 서브트리 중 가장 작은 값을 가지는 노드를 반환한다.
template <typename NodePtr> NodePtr get_successor(NodePtr x, NodePtr nil) {
  if (x->right != nil) {
    return get_min_node(x->right, nil);
  }
  // 선택한 노드의 오른쪽 자식이 없는 경우
  // 해당 노드가 서브 트리 내의 최댓값임을 의미하므로 서브 트리의 루트 노드를
  // 선택한다.
  NodePtr y = x->parent;
  while (y != nil && x == y->right) {
    x = y;
    y = y->parent;
  }
  return y;
}

// 선택한 노드의 왼쪽 서브트리 중 가장 큰 값을 가지는 노드를 반환한다.
template <typename NodePtr> NodePtr get_predecessor(NodePtr x, NodePtr nil) {
  if (x->left != nil) {
    return get_max_node(x->left, nil);
  }
  // 선택한 노드의 왼쪽 자식이 없는 경우
  // 해당 노드가 서브 트리 내의 최솟값임을 의미하므로 서브 트리의 루트 노드를
  // 선택한다.
  NodePtr y = x->parent;
  while (y != nil && x == y->left) {
    x = y;
    y = y->parent;
  }
  return y;
}

} // namespace ft

#endif
