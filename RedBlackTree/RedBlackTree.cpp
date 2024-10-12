#include "RedBlackTree.hpp"

template <typename T>
bool RedBlackTree<T>::Insert(T value) {
    auto current = this->root;
    auto parent = nullptr;
    while (current != nullptr) {
        parent = current;
        if (value == current->value) {
            return false;
        } else if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    auto newNode = new RedBlackTreeNode(value, nullptr, nullptr, parent, Colour::RED);
    if (parent == nullptr) {
        root = newNode;
    } else if (parent->value < newNode->value) {
        parent->right = newNode;
    } else {
        parent->left = newNode;
    }

    if (newNode->parent == nullptr) {
        newNode->colour = Colour::BLACK;
        return true;
    }

    if (newNode->parent->colour == Colour::RED) {
        rebalance(newNode);
    }
    return true;
}

template <typename T>
void RedBlackTree<T>::rebalance(RedBlackTreeNode<T> *node) {
    while (node != root && node->parent->colour == Colour::RED) {
        if (node->parent->parent != nullptr && node->parent == node->parent->parent->left) {
            // parent is left child
            auto uncle = node->parent->parent->right;
            if (uncle != nullptr && uncle.colour == Colour::RED) {
                node->parent->colour = Colour::BLACK;
                uncle->colour = Colour::BLACK;
                node->parent->parent->colour = Colour::RED;
                node = node->parent->parent;
            } else {
                // triangle
                if (node == node->parent->right) {
                    node = node.parent;
                    leftRotate(node);
                }
                node->parent->colour = Colour::BLACK;
                node->parent->parent->colour = Colour::RED;
                rightRotate(node->parent->parent);
            }
        } else {
            // parent is right child
            auto uncle = node->parent->parent->left;
            if (uncle != nullptr && uncle.colour == Colour::RED) {
                node->parent->colour = Colour::BLACK;
                uncle->colour = Colour::BLACK;
                node->parent->parent->colour = Colour::RED;
                node = node->parent->parent;
            } else {
                // triangle
                if (node == node->parent->left) {
                    node = node.parent;
                    rightRotate(node);
                }
                node->parent->colour = Colour::BLACK;
                node->parent->parent->colour = Colour::RED;
                leftRotate(node->parent->parent);
            }
        }
    }
    root->colour = Colour::BLACK;
}

template <typename T>
void RedBlackTree<T>::leftRotate(RedBlackTreeNode<T> *node) {
    auto parent = node->parent;
    auto right = node->right;
    node->right = right->left;
    if (right->left != nullptr) {
        right->left->parent = node;
    }

    right->parent = node->parent;
    if (node->parent == nullptr) {
        root = right;
    } else if (node == node->parent->left) {
        node->parent->left = right;
    } else {
        node->parent->right = right;
    }
    right->left = node;
    node->parent = right;
}

template <typename T>
void RedBlackTree<T>::rightRotate(RedBlackTreeNode<T> *node) {
    auto parent = node->parent;
    auto left = node->left;
    node->left = left->right;
    if (left->right != nullptr) {
        left->right->parent = node;
    }

    left->parent = node->parent;
    if (node->parent == nullptr) {
        root = left;
    } else if (node == node->parent->right) {
        node->parent->right = left;
    } else {
        node->parent->left = left;
    }
    right->right = node;
    node->parent = left;
}