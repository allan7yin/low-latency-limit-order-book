#ifndef RedBlackTreeNode_hpp
#define RedBlackTreeNode_hpp

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
    T *value;
    Colour colour;

  public:
    RedBlackTreeNode(T value, RedBlackTreeNode<T> *left = nullptr,
                     RedBlackTreeNode<T> *right = nullptr,
                     RedBlackTreeNode<T> *parent = nullptr,
                     Colour colour = Colour::RED) : value(value), left(left), right(right), parent(parent), colour(colour) {}
    ~RedBlackTreeNode() {
        if (left) delete left;
        if (right) delete right;
    }
};

#endif