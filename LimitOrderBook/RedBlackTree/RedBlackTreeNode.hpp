#ifndef RedBlackTreeNode_hpp
#define RedBlackTreeNode_hpp

#include <type_traits>

enum class Colour {
    RED,
    BLACK
};

template <class T>
struct RedBlackTreeNode {
  public:
    int key; // limit price in this case
    T value;
    RedBlackTreeNode *left;
    RedBlackTreeNode *right;
    RedBlackTreeNode *parent;

    Colour colour;
    RedBlackTreeNode(int key, T value, RedBlackTreeNode<T> *left = nullptr,
                     RedBlackTreeNode<T> *right = nullptr,
                     RedBlackTreeNode<T> *parent = nullptr,
                     Colour colour = Colour::RED);
    ~RedBlackTreeNode();
};

template <class T>
RedBlackTreeNode<T>::RedBlackTreeNode(int key, T value, RedBlackTreeNode<T> *left, RedBlackTreeNode<T> *right, RedBlackTreeNode<T> *parent, Colour colour)
    : key(key), value(value), left(left), right(right), parent(parent), colour(colour) {}

template <class T>
RedBlackTreeNode<T>::~RedBlackTreeNode() {
    if (left) delete left;
    if (right) delete right;
    if constexpr (std::is_pointer<T>::value) {
        delete value;
    }
}

#endif