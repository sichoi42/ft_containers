#include <iostream>
#include <map>

enum Color {
  BLACK,
  RED
};

struct Node {
  int key;
  Node *parent;
  Node *left;
  Node *right;
  Color color;
};

typedef Node* NodePtr;

class RBTree {
  private:
    NodePtr root;
    NodePtr nil;

  void init_nil_node(NodePtr node, NodePtr parent) {
    node->parent = parent;
    node->left = NULL;
    node->right = NULL;
    node->color = BLACK;
  }

  void preorder_helper(NodePtr node) {
    if (node != nil) {
      std::cout << node->key << " ";
      preorder_helper(node->left);
      preorder_helper(node->right);
    }
  }

  void inorder_helper(NodePtr node) {
    if (node != nil) {
      inorder_helper(node->left);
      std::cout << node->key << " ";
      inorder_helper(node->right);
    }
  }

  void postorder_helper(NodePtr node) {
    if (node != nil) {
      postorder_helper(node->left);
      postorder_helper(node->right);
      std::cout << node->key << " ";
    }
  }

  NodePtr search_tree_helper(NodePtr node, int key) {
    if (node == nil || key == node->key) {
      return node;
    }

    if (key < node->key) {
      return search_tree_helper(node->left, key);
    } else {
      return search_tree_helper(node->right, key);
    }
  }

  void print_helper(NodePtr root, std::string indent, bool last) {
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
      std::cout << root->key << "(" << c << ")" << std::endl;
      print_helper(root->left, indent, false);
      print_helper(root->right, indent, true);
    }
  }

  // TODO: implement
  // Balancing RBTree after deletion
  // void delete_fixup(NodePtr x)
  // rb_transplant(NodePtr u, NodePtr v)
  // delete_node_helper(NodePtr node, int key)

  // Balancing RBTree after insertion
  void insert_fixup(NodePtr newNode) {
    // new node의 부모의 색깔이 레드인 동안 반복한다.
    while (newNode->parent->color == RED) {
      NodePtr gp = newNode->parent->parent;
       // 부모가 조부모의 오른쪽 자식인 경우
      if (newNode->parent == gp->left) {
        // Case 1: 부모의 형제 노드가 레드인 경우
        if (gp->right->color == RED) {
          gp->right->color = BLACK;
          gp->left->color = BLACK;
          gp->color = RED;
          newNode = gp;
        }
        // Case 2: new node가 부모의 오른쪽 자식인 경우
        else if (newNode == newNode->parent->right) {
          newNode = newNode->parent;
          left_rotate(newNode);
        } else {
          // Case 3: new node가 부모의 왼쪽 자식인 경우
          newNode->parent->color = BLACK;
          gp->color = RED;
          right_rotate(gp);
        }
      } else { // 부모가 조부모의 오른쪽 자식인 경우
        if (gp->left->color == RED) {
          gp->left->color = BLACK;
          gp->right->color = BLACK;
          gp->color = RED;
          newNode = gp;
        } else if (newNode == newNode->parent->left) {
          newNode = newNode->parent;
          right_rotate(newNode);
        } else {
          newNode->parent->color = BLACK;
          gp->color = RED;
          left_rotate(gp);
        }
      }
      if (newNode == root) {
        break;
      }
    }
    root->color = BLACK;
  }

  public:

  RBTree() {
    nil = new Node;
    nil->color = BLACK;
    nil->left = NULL;
    nil->right = NULL;
    root = nil;
  }

  void preorder() {
    preorder_helper(this->root);
  }

  void inorder() {
    inorder_helper(this->root);
  }

  void postorder() {
    postorder_helper(this->root);
  }

  NodePtr search_tree(int k) {
    return search_tree_helper(this->root, k);
  }

  NodePtr get_min_node(NodePtr node) {
    while (node->left != nil) {
      node = node->left;
    }
    return node;
  }

  NodePtr get_max_node(NodePtr node) {
    while (node->right != nil) {
      node = node->right;
    }
    return node;
  }

  // 선택한 노드의 오른쪽 서브트리 중 가장 작은 값을 가지는 노드를 반환한다.
  NodePtr get_successor(NodePtr x) {
    if (x->right != nil) {
      return get_min_node(x->right);
    }
    // 선택한 노드의 오른쪽 자식이 없는 경우
    // 해당 노드가 서브 트리 내의 최댓값임을 의미하므로 서브 트리의 루트 노드를 선택한다.
    NodePtr y = x->parent;
    while (y != nil && x == y->right) {
      x = y;
      y = y->parent;
    }
    return y;
  }

  // 선택한 노드의 왼쪽 서브트리 중 가장 큰 값을 가지는 노드를 반환한다.
  NodePtr get_predecessor(NodePtr x) {
    if (x->left != nil) {
      return get_max_node(x->left);
    }
    // 선택한 노드의 왼쪽 자식이 없는 경우
    // 해당 노드가 서브 트리 내의 최솟값임을 의미하므로 서브 트리의 루트 노드를 선택한다.
    NodePtr y = x->parent;
    while (y != nil && x == y->left) {
      x = y;
      y = y->parent;
    }
    return y;
  }

  void left_rotate(NodePtr x) {
    NodePtr y = x->right;
    // y의 왼쪽 서브트리를 x의 오른쪽 서브트리로 설정한다.
    x->right = y->left;
    // y가 왼쪽 서브트리를 가진다면, y의 왼쪽 서브트리의 부모를 x로 설정한다.
    if (y->left != nil) {
      y->left->parent = x;
    }
    // y의 부모를 x의 부모로 설정한다.
    y->parent = x->parent;
    if (x->parent == nil) {
      this->root = y;
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

  void right_rotate(NodePtr x) {
    NodePtr y = x->left;
    // y의 오른쪽 서브트리를 x의 왼쪽 서브트리로 설정한다.
    x->left = y->right;
    // y가 오른쪽 서브트리를 가진다면, y의 오른쪽 서브트리의 부모를 x로 설정한다.
    if (y->right != nil) {
      y->right->parent = x;
    }
    // y의 부모를 x의 부모로 설정한다.
    y->parent = x->parent;
    if (x->parent == nil) {
      this->root = y;
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

  void insert(int key) {
    NodePtr newNode = new Node;
    newNode->color = RED;
    newNode->key = key;
    newNode->left = nil;
    newNode->right = nil;
    newNode->parent = NULL;

    NodePtr y = NULL;
    NodePtr x = this->root;
    if (x == nil) {
      newNode->color = BLACK;
      this->root = newNode;
      return ;
    }
    // x는 leaf가 되고, y는 leaf의 부모 노드가 된다.
    while (x != nil) {
      y = x;
      if (newNode->key > x->key) {
        x = x->right;
      } else {
        x = x->left;
      }
    }
    newNode->parent = y;
    if (newNode->key > y->key) {
      y->right = newNode;
    } else {
      y->left = newNode;
    }
    if (newNode->parent->parent == NULL) {
      return ;
    }
    insert_fixup(newNode);
  }

  void print_tree() {
    if (root) {
      print_helper(root, "", true);
      std::cout << "========end of tree========" << std::endl;
    }
  }
};


int	main(void)
{
  RBTree	rbtree;
  rbtree.insert(55);
  rbtree.print_tree();
  rbtree.insert(40);
  rbtree.print_tree();
  rbtree.insert(65);
  rbtree.print_tree();
  rbtree.insert(60);
  rbtree.print_tree();
  rbtree.insert(75);
  rbtree.print_tree();
  rbtree.insert(57);
  rbtree.print_tree();
  return (0);
}