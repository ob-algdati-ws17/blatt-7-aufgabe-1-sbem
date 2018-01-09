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

void AVLTree::insert(int value) {
    if (root == nullptr) {
        root = new Node(value);
    }
    else {
        insert(value, root);
    }
}

void AVLTree::insert(int value, Node *node) {
    if (value != node->key) {
        if (value < node->key) {
            if (node->left == nullptr) {
                node->left = new Node(value);
            }
            else {
                insert(value, node->left);
            }
        }
        else {
            if (node->right == nullptr) {
                node->right = new Node(value);
            }
            else {
                insert(value, node->right);
            }
        }
        upin(node);
    }
}
