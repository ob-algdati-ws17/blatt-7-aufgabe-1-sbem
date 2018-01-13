/**
 * @authors Ehsan Moslehi, Sebastian Bauman
 */

#include <functional>
#include "AVLTree.h"

using namespace ::std;

AVLTree::Node::Node(const int k) : key(k) {}

AVLTree::Node::Node(const int k,Node *p)
        : key(k), prev(p) {}

AVLTree::Node::Node(const int k,Node *p, Node *l, Node *r)
        : key(k), prev(p), left(l), right(r) {}

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
                node->left = new Node(value, node);
                node->bal -= 1;
                if (node->bal =! 0) {
                    upin(node);
                }
            }
            else {
                insert(value, node);
            }
        } else {
            if (node->left == nullptr) {
                node->left = new Node(value, node);
                node->bal += 1;
                if (node->bal =! 0) {
                    upin(node);
                }
            } else {
                insert(value, node);
            }
        }
    }
}

void AVLTree::upin(Node *node) {
    if (node->prev != nullptr) {
        // Left child of his parent.
        if (node->key < node->prev->key) {
            if (node->prev->bal == 1) {
                node->prev->bal = 0;
            }
            else if (node->prev->bal == 0) {
                node->prev->bal = -1;
                upin(node->prev);
            }
            else {
                if (node->bal == -1) {
                    if (node->prev->prev == nullptr) {
                        root = rotateRight(node->prev);
                    }
                    else if (node->prev->key < node->prev->prev->key) {
                        node->prev->prev->left = rotateRight(node->prev);
//                        node->bal = 0;
//                        node->right->bal = 0;
                    }
                    else {
                        node->prev->prev->right = rotateRight(node->prev);
//                        node->bal = 0;
//                        node->right->bal = 0;
                    }
                }
                else if (node->bal == 1) {
                    if (node->prev->prev == nullptr) {
                        root = rotateLeftRight(node->prev);
                    }
                    else if (node->prev->key < node->prev->prev->key) {
                        node->prev->prev->left = rotateLeftRight(node->prev);
                    }
                    else {
                        node->prev->prev->right = rotateLeftRight(node->prev);
                    }
                }
            }
        }
        // Right child of his parent.
        else {
            if (node->prev->bal == -1) {
                node->prev->bal = 0;
            }
            else if (node->prev->bal == 0) {
                node->prev->bal = 1;
                upin(node->prev);
            }
            else {
                if (node->bal == 1) {
                    if (node->prev->prev == nullptr) {
                        root = rotateLeft(node->prev);
                    }
                    else if (node->prev->key < node->prev->prev->key) {
                        node->prev->prev->left = rotateLeft(node->prev);
//                        node->bal = 0;
//                        node->right->bal = 0;
                    }
                    else {
                        node->prev->prev->right = rotateLeft(node->prev);
//                        node->bal = 0;
//                        node->right->bal = 0;
                    }
                }
                else if (node->bal == -1) {
                    if (node->prev->prev == nullptr) {
                        root = rotateRightLeft(node->prev);
                    }
                    else if (node->prev->key < node->prev->prev->key) {
                        node->prev->prev->left = rotateRightLeft(node->prev);
                    }
                    else {
                        node->prev->prev->right = rotateRightLeft(node->prev);
                    }
                }
            }
        }
    }
}

/********************************************************************
 * Rotations
 *******************************************************************/

AVLTree::Node *AVLTree::rotateLeft(Node *n) {
    Node *oldRoot = n;
    Node *newRoot = oldRoot->right;
    oldRoot->right = newRoot->left;
    newRoot->left = oldRoot;
    return newRoot;
}

AVLTree::Node *AVLTree::rotateRight(Node *n) {
    Node *oldRoot = n;
    Node *newRoot = oldRoot->left;
    oldRoot->left = newRoot->right;
    newRoot->right = oldRoot;
    return newRoot;
}

AVLTree::Node *AVLTree::rotateLeftRight(Node *n) {
    n->left = rotateLeft(n->left);
    return rotateRight(n);
}

AVLTree::Node *AVLTree::rotateRightLeft(Node *n) {
    n->right = rotateRight(n->right);
    return rotateLeft(n);
}

/********************************************************************
 * Traversal
 *******************************************************************/
// © Prof. Dr. Oliver Braun
// The following code is extracted from the solution to the assignment Blatt 6
vector<int> *AVLTree::preorder() const {
    if (root == nullptr)
        return nullptr;
    return root->preorder();
}

// © Prof. Dr. Oliver Braun
// The following code is extracted from the solution to the assignment Blatt 6
vector<int> *AVLTree::Node::preorder() const {
    auto vec = new vector<int>();
    // Wurzel in vec
    vec->push_back(key);
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->preorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->preorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    return vec;
}

// © Prof. Dr. Oliver Braun
// The following code is extracted from the solution to the assignment Blatt 6
vector<int> *AVLTree::inorder() const {
    if (root == nullptr)
        return nullptr;
    return root->inorder();
}

// © Prof. Dr. Oliver Braun
// The following code is extracted from the solution to the assignment Blatt 6
vector<int> *AVLTree::Node::inorder() const {
    auto vec = new vector<int>();
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->inorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // Wurzel in vec
    vec->push_back(key);
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->inorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    return vec;
}

// © Prof. Dr. Oliver Braun
// The following code is extracted from the solution to the assignment Blatt 6
vector<int> *AVLTree::postorder() const {
    if (root == nullptr)
        return nullptr;
    return root->postorder();
}

// © Prof. Dr. Oliver Braun
// The following code is extracted from the solution to the assignment Blatt 6
vector<int> *AVLTree::Node::postorder() const {
    auto vec = new vector<int>();
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->postorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->postorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    // Wurzel in vec
    vec->push_back(key);
    return vec;
}

/********************************************************************
 * operator<<
 *******************************************************************/
// © Prof. Dr. Oliver Braun
// The following code is extracted from the solution to the assignment Blatt 6
std::ostream &operator<<(std::ostream &os, const AVLTree &tree) {
    function<void(std::ostream &, const int, const AVLTree::Node *, const string)> printToOs
            = [&](std::ostream &os, const int value, const AVLTree::Node *node, const string l) {

                static int nullcount = 0;

                if (node == nullptr) {
                    os << "    null" << nullcount << "[shape=point];" << endl;
                    os << "    " << value << " -> null" << nullcount
                       << " [label=\"" << l << "\"];" << endl;
                    nullcount++;
                } else {
                    os << "    " << value << " -> " << node->key
                       << " [label=\"" << l << "\"];" << endl;

                    printToOs(os, node->key, node->left, "l");
                    printToOs(os, node->key, node->right, "r");
                }
            };
    os << "digraph tree {" << endl;
    if (tree.root == nullptr) {
        os << "    null " << "[shape=point];" << endl;
    } else {
        printToOs(os, tree.root->key, tree.root->left, "l");
        printToOs(os, tree.root->key, tree.root->right, "r");
    }
    os << "}" << endl;
    return os;
}
