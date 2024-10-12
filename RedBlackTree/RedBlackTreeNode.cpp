#include "RedBlackTreeNode.hpp"

template <typename T>
RedBlackTreeNode<T>::RedBlackTreeNode(T value, RedBlackTreeNode<T> *left = nullptr, RedBlackTreeNode<T> *right = nullptr, RedBlackTreeNode<T> *parent = nullptr, Colour colour = Colour::RED)
    : left(left), right(right), parent(parent), value(value), colour(colour) {
}