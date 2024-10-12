#ifndef RedBlackTree_hpp
#define RedBlackTree_hpp

#include "RedBlackTreeNode.hpp"

template <class T>
class RedBlackTree {
  private:
    RedBlackTreeNode<T> *root;
    void rebalance(RedBlackTreeNode<T> *node);
    void leftRotate(RedBlackTreeNode<T> *node);
    void rightRotate(RedBlackTreeNode<T> *node);

  public:
    RedBlackTree(RedBlackTreeNode<T> *root);
    ~RedBlackTree();
    bool Insert(T value);
    bool Delete(T value);
};

#endif