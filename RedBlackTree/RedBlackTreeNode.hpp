#ifndef RedBlackTree_hpp
#define RedBlackTree_hpp

enum class Colour {
    RED,
    BLACK
};

template <class T>
class RedBlackTreeNode {
  private:
    RedBlackTreeNode *left;
    RedBlackTreeNode *right;
    RedBlackTreeNode *parent;
    T value;
    Colour colour;

  public:
    RedBlackTreeNode(T value, RedBlackTreeNode *left, RedBlackTreeNode *right, RedBlackTreeNode *parent, Colour colour);
};

#endif