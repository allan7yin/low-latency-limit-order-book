#ifndef RedBlackTree_hpp
#define RedBlackTree_hpp

#include "RedBlackTreeNode.hpp"
#include <unordered_map>

template <class T>
class RedBlackTree {
  private:
    RedBlackTreeNode<T> *root;
    RedBlackTreeNode<T> *minNode;
    RedBlackTreeNode<T> *maxNode;
    int size;
    std::unordered_map<int, RedBlackTreeNode<T> *> nodeMap;

    bool isEmpty() const;
    void rebalanceInsert(RedBlackTreeNode<T> *node);
    void rebalanceDelete(RedBlackTreeNode<T> *node);
    void leftRotate(RedBlackTreeNode<T> *node);
    void rightRotate(RedBlackTreeNode<T> *node);
    void transplant(RedBlackTreeNode<T> *u, RedBlackTreeNode<T> *v);
    RedBlackTreeNode<T> *minimum(RedBlackTreeNode<T> *node);
    RedBlackTreeNode<T> *maximum(RedBlackTreeNode<T> *node); // should just return min and maxNode field

  public:
    RedBlackTree();
    ~RedBlackTree();
    RedBlackTreeNode<T> *Search(const int key);
    bool Insert(const int key, const T value);
    bool Delete(const int key);
    RedBlackTreeNode<T> *GetSmallestNode();
    RedBlackTreeNode<T> *GetLargestNode();
    RedBlackTreeNode<T> *find(int key) const;
};

template <class T>
RedBlackTree<T>::RedBlackTree() : root(nullptr), minNode(nullptr), maxNode(nullptr), size(0) {}

template <class T>
RedBlackTree<T>::~RedBlackTree() {
    if (root) delete root;
}

template <class T>
bool RedBlackTree<T>::isEmpty() const {
    return size == 0;
}

template <class T>
RedBlackTreeNode<T> *RedBlackTree<T>::Search(const int key) {
    if (nodeMap.find(key) == nodeMap.end()) {
        return nullptr;
    }
    return nodeMap[key];
}

template <class T>
bool RedBlackTree<T>::Insert(const int key, const T value) {
    if (nodeMap.find(key) == nodeMap.end()) {
        auto current = this->root;
        RedBlackTreeNode<T> *parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if (key == current->key) {
                return false;
            } else if (key < current->key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        auto newNode = new RedBlackTreeNode<T>(key, value, nullptr, nullptr, parent, Colour::RED);
        if (parent == nullptr) {
            root = newNode;
        } else if (parent->key < newNode->key) {
            parent->right = newNode;
        } else {
            parent->left = newNode;
        }

        if (minNode == nullptr || newNode->key < minNode->key) {
            minNode = newNode;
        }

        if (maxNode == nullptr || newNode->key > maxNode->key) {
            maxNode = newNode;
        }

        if (newNode->parent == nullptr) {
            newNode->colour = Colour::BLACK;
            nodeMap[key] = newNode;
            return true;
        }

        if (newNode->parent->colour == Colour::RED) {
            rebalanceInsert(newNode);
        }
        nodeMap[key] = newNode;
        size++;
        return true;
    }
    return false;
}

template <class T>
bool RedBlackTree<T>::Delete(const int key) {
    auto nodeToDelete = Search(key);
    if (!nodeToDelete) {
        return false;
    }
    if (nodeToDelete == minNode) {
        if (nodeToDelete->right) {
            minNode = minimum(nodeToDelete->right);
        } else {
            minNode = nodeToDelete->parent;
            while (minNode && minNode->left == nullptr) {
                minNode = minNode->parent;
            }
        }
    }

    if (nodeToDelete == maxNode) {
        if (nodeToDelete->left) {
            maxNode = maximum(nodeToDelete->left);
        } else {
            maxNode = nodeToDelete->parent;
            while (maxNode && maxNode->right == nullptr) {
                maxNode = maxNode->parent;
            }
        }
    }

    auto deletedColour = nodeToDelete->colour;
    RedBlackTreeNode<T> *replacementNode;
    RedBlackTreeNode<T> *x;

    if (nodeToDelete->left && nodeToDelete->right) {
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

    if (deletedColour == Colour::BLACK) {
        rebalanceDelete(x);
    }

    nodeToDelete->left = nullptr;
    nodeToDelete->right = nullptr;
    delete nodeToDelete;
    nodeMap.erase(key);
    size--;
    return true;
}

template <class T>
RedBlackTreeNode<T> *RedBlackTree<T>::GetSmallestNode() {
    return minNode;
}

template <class T>
RedBlackTreeNode<T> *RedBlackTree<T>::GetLargestNode() {
    return maxNode;
}

template <class T>
RedBlackTreeNode<T> *RedBlackTree<T>::find(int key) const {
    if (nodeMap.find(key) == nodeMap.end()) {
        return nullptr;
    }
    return nodeMap.at(key);
}

template <class T>
void RedBlackTree<T>::leftRotate(RedBlackTreeNode<T> *node) {
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

template <class T>
void RedBlackTree<T>::rightRotate(RedBlackTreeNode<T> *node) {
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

template <class T>
void RedBlackTree<T>::transplant(RedBlackTreeNode<T> *u, RedBlackTreeNode<T> *v) {
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

template <class T>
RedBlackTreeNode<T> *RedBlackTree<T>::minimum(RedBlackTreeNode<T> *node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

template <class T>
RedBlackTreeNode<T> *RedBlackTree<T>::maximum(RedBlackTreeNode<T> *node) {
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}

template <class T>
void RedBlackTree<T>::rebalanceInsert(RedBlackTreeNode<T> *node) {
    while (node != root && node->parent->colour == Colour::RED) {
        if (node->parent == node->parent->parent->left) {
            RedBlackTreeNode<T> *uncle = node->parent->parent->right;
            if (uncle && uncle->colour == Colour::RED) {
                node->parent->colour = Colour::BLACK;
                uncle->colour = Colour::BLACK;
                node->parent->parent->colour = Colour::RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    leftRotate(node);
                }
                node->parent->colour = Colour::BLACK;
                node->parent->parent->colour = Colour::RED;
                rightRotate(node->parent->parent);
            }
        } else {
            RedBlackTreeNode<T> *uncle = node->parent->parent->left;
            if (uncle && uncle->colour == Colour::RED) {
                node->parent->colour = Colour::BLACK;
                uncle->colour = Colour::BLACK;
                node->parent->parent->colour = Colour::RED;
                node = node->parent->parent;
            } else {
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

template <class T>
void RedBlackTree<T>::rebalanceDelete(RedBlackTreeNode<T> *node) {
    while (node != root && node->colour == Colour::BLACK) {
        if (node == node->parent->left) {
            RedBlackTreeNode<T> *sibling = node->parent->right;
            if (sibling->colour == Colour::RED) {
                sibling->colour = Colour::BLACK;
                node->parent->colour = Colour::RED;
                leftRotate(node->parent);
                sibling = node->parent->right;
            }
            if ((!sibling->left || sibling->left->colour == Colour::BLACK) &&
                (!sibling->right || sibling->right->colour == Colour::BLACK)) {
                sibling->colour = Colour::RED;
                node = node->parent;
            } else {
                if (!sibling->right || sibling->right->colour == Colour::BLACK) {
                    sibling->left->colour = Colour::BLACK;
                    sibling->colour = Colour::RED;
                    rightRotate(sibling);
                    sibling = node->parent->right;
                }
                sibling->colour = node->parent->colour;
                node->parent->colour = Colour::BLACK;
                if (sibling->right) sibling->right->colour = Colour::BLACK;
                leftRotate(node->parent);
                node = root;
            }
        } else {
            RedBlackTreeNode<T> *sibling = node->parent->left;
            if (sibling->colour == Colour::RED) {
                sibling->colour = Colour::BLACK;
                node->parent->colour = Colour::RED;
                rightRotate(node->parent);
                sibling = node->parent->left;
            }
            if ((!sibling->left || sibling->left->colour == Colour::BLACK) &&
                (!sibling->right || sibling->right->colour == Colour::BLACK)) {
                sibling->colour = Colour::RED;
                node = node->parent;
            } else {
                if (!sibling->left || sibling->left->colour == Colour::BLACK) {
                    sibling->right->colour = Colour::BLACK;
                    sibling->colour = Colour::RED;
                    leftRotate(sibling);
                    sibling = node->parent->left;
                }
                sibling->colour = node->parent->colour;
                node->parent->colour = Colour::BLACK;
                if (sibling->left) sibling->left->colour = Colour::BLACK;
                rightRotate(node->parent);
                node = root;
            }
        }
    }
    node->colour = Colour::BLACK;
}

#endif