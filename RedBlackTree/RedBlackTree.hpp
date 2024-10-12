#include "RedBlackTreeNode.hpp"

template <class T>
class RedBlackTree {
  private:
    RedBlackTreeNode<T> *root;
    void rebalance(RedBlackTreeNode<T> *node);
    void leftRotate(RedBlackTreeNode<T> *node);
    void rightRotate(RedBlackTreeNode<T> *node);

  public:
    bool Insert(T value);
};