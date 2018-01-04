/**
 * @authors Ehsan Moslehi, Sebastian Bauman
 */

#include "AVLTree.h"

using namespace ::std;

AVLTree::Node::Node(const int k) : key(k), bal(0) {}

AVLTree::Node::Node(const int k, Node *l, Node *r)
        : key(k), left(l), right(r), bal(0) {}

bool AVLTree::search(const int value) const {
    if (root == nullptr) {
        return false;
    }
    return root->search(value);
}

bool AVLTree::Node::search(const int value) const {
    if (value == key) {
        return true;
    }
    if (value < key && left != nullptr) {
        return left->search(value);
    }
    if (value > key && right != nullptr) {
        return right->search(value);
    }
    return false;
}
