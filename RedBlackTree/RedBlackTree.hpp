#ifndef RedBlackTree_hpp
#define RedBlackTree_hpp

#include "RedBlackTreeNode.hpp"

template <class T>
class RedBlackTree {
  private:
    RedBlackTreeNode<T> *root;
    void rebalanceInsert(RedBlackTreeNode<T> *node) {
        while (node != root && node->parent->colour == Colour::RED) {
            if (node->parent->parent != nullptr && node->parent == node->parent->parent->left) {
                // parent is left child
                RedBlackTreeNode<T> *uncle = node->parent->parent->right;
                if (uncle != nullptr && uncle->colour == Colour::RED) {
                    node->parent->colour = Colour::BLACK;
                    uncle->colour = Colour::BLACK;
                    node->parent->parent->colour = Colour::RED;
                    node = node->parent->parent;
                } else {
                    // triangle
                    if (node == node->parent->right) {
                        node = node->parent;
                        leftRotate(node);
                    }
                    node->parent->colour = Colour::BLACK;
                    node->parent->parent->colour = Colour::RED;
                    rightRotate(node->parent->parent);
                }
            } else {
                // parent is right child
                RedBlackTreeNode<T> *uncle = node->parent->parent->left;
                if (uncle != nullptr && uncle->colour == Colour::RED) {
                    node->parent->colour = Colour::BLACK;
                    uncle->colour = Colour::BLACK;
                    node->parent->parent->colour = Colour::RED;
                    node = node->parent->parent;
                } else {
                    // triangle
                    if (node == node->parent->left) {
                        node = node->parent;
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
    void rebalanceDelete(RedBlackTreeNode<T> *node) {
        while (node != root && node->colour == Colour::BLACK) {
            if (node == node->parent->left) {
                RedBlackTreeNode<T> *sibling = node->parent->right;

                // Case 1: Sibling is Red
                if (sibling->colour == Colour::RED) {
                    sibling->colour = Colour::BLACK;
                    node->parent->colour = Colour::RED;
                    leftRotate(node->parent); // Use your leftRotate function here
                    sibling = node->parent->right;
                }

                // Case 2: Sibling is Black
                // Sub-case 2.1: Both sibling's children are black
                if ((sibling->left == nullptr || sibling->left->colour == Colour::BLACK) &&
                    (sibling->right == nullptr || sibling->right->colour == Colour::BLACK)) {
                    sibling->colour = Colour::RED;
                    node = node->parent; // Move the double-black issue up to the parent
                }
                // Sub-case 2.2: At least one of sibling's children is red
                else {
                    // Sub-case 2.2.2: Sibling's far child is black and near child is red
                    if (sibling->right == nullptr || sibling->right->colour == Colour::BLACK) {
                        sibling->left->colour = Colour::BLACK;
                        sibling->colour = Colour::RED;
                        rightRotate(sibling); // Use your rightRotate function here
                        sibling = node->parent->right;
                    }

                    // Sub-case 2.2.1: Sibling's far child is red
                    sibling->colour = node->parent->colour;
                    node->parent->colour = Colour::BLACK;
                    if (sibling->right != nullptr) sibling->right->colour = Colour::BLACK;
                    leftRotate(node->parent); // Use your leftRotate function here
                    node = root;              // Exit loop after this fix
                }
            } else {
                // Symmetric case for the right child
                RedBlackTreeNode<T> *sibling = node->parent->left;

                // Case 1: Sibling is Red
                if (sibling->colour == Colour::RED) {
                    sibling->colour = Colour::BLACK;
                    node->parent->colour = Colour::RED;
                    rightRotate(node->parent); // Use your rightRotate function here
                    sibling = node->parent->left;
                }

                // Case 2: Sibling is Black
                // Sub-case 2.1: Both sibling's children are black
                if ((sibling->left == nullptr || sibling->left->colour == Colour::BLACK) &&
                    (sibling->right == nullptr || sibling->right->colour == Colour::BLACK)) {
                    sibling->colour = Colour::RED;
                    node = node->parent; // Move the double-black issue up to the parent
                }
                // Sub-case 2.2: At least one of sibling's children is red
                else {
                    // Sub-case 2.2.2: Sibling's far child is black and near child is red
                    if (sibling->left == nullptr || sibling->left->colour == Colour::BLACK) {
                        sibling->right->colour = Colour::BLACK;
                        sibling->colour = Colour::RED;
                        leftRotate(sibling); // Use your leftRotate function here
                        sibling = node->parent->left;
                    }

                    // Sub-case 2.2.1: Sibling's far child is red
                    sibling->colour = node->parent->colour;
                    node->parent->colour = Colour::BLACK;
                    if (sibling->left != nullptr) sibling->left->colour = Colour::BLACK;
                    rightRotate(node->parent); // Use your rightRotate function here
                    node = root;               // Exit loop after this fix
                }
            }
        }

        // Make sure the root is always black
        node->colour = Colour::BLACK;
    }
    void leftRotate(RedBlackTreeNode<T> *node) {
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
    void rightRotate(RedBlackTreeNode<T> *node) {
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
        left->right = node;
        node->parent = left;
    }
    void transplant(RedBlackTreeNode<T> *u, RedBlackTreeNode<T> *v) {
        if (u->parent == nullptr) {
            this->root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if (v != nullptr) {
            v->parent = u->parent;
        }
    }
    RedBlackTreeNode<T> *minimum(RedBlackTreeNode<T> *node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

  public:
    RedBlackTree(RedBlackTreeNode<T> *root) : root(root) {}
    ~RedBlackTree() {
        if (root) delete root;
    }
    RedBlackTreeNode<T> *Search(T value) {
        auto current = this->root;
        while (current != nullptr) {
            if (value == current->value) {
                break;
            } else if (value < current->value) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        return current;
    }
    bool Insert(T value) {
        auto current = this->root;
        RedBlackTreeNode<T> *parent = nullptr; // cant use auto, otherwise would be of type `std::nullptr_t` not tree node nullptr
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

        auto newNode = new RedBlackTreeNode<T>(value, nullptr, nullptr, parent, Colour::RED);
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
            rebalanceInsert(newNode);
        }
        return true;
    }
    bool Delete(T value) {
        auto nodeToDelete = Search(value);
        if (!nodeToDelete) {
            return false;
        }

        auto deletedColour = nodeToDelete->colour;
        RedBlackTreeNode<T> *replacementNode;
        RedBlackTreeNode<T> *x;

        if (nodeToDelete->left && nodeToDelete->right) {
            // has both children, swap with smallest on right side
            RedBlackTreeNode<T> *minRightSubtree = minimum(nodeToDelete->right);
            deletedColour = minRightSubtree->colour;
            replacementNode = minRightSubtree->right;

            if (minRightSubtree->parent == nodeToDelete) {
                x = minRightSubtree;
            } else {
                transplant(minRightSubtree, minRightSubtree->right);
                minRightSubtree->right = nodeToDelete->right;
                minRightSubtree->right->parent = minRightSubtree;
                x = replacementNode;
            }
            transplant(nodeToDelete, minRightSubtree);
            minRightSubtree->left = nodeToDelete->left;
            minRightSubtree->left->parent = minRightSubtree;
            minRightSubtree->colour = nodeToDelete->colour;
        } else if (nodeToDelete->left) {
            replacementNode = nodeToDelete->left;
            transplant(nodeToDelete, nodeToDelete->left);
            x = nodeToDelete->left;
        } else {
            replacementNode = nodeToDelete->right;
            transplant(nodeToDelete, nodeToDelete->right);
            x = nodeToDelete->right;
        }

        // if colour of deleted node is black, need to re-balance
        if (deletedColour == Colour::BLACK) {
            rebalanceDelete(x); // Fix the red-black tree starting from x
        }

        delete nodeToDelete;
        return true;
    }
};

#endif