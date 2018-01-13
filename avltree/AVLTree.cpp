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


/********************************************************************
 * Destructors
 *******************************************************************/

AVLTree::Node::~Node(){
    delete left;
    delete right;
}

AVLTree::~AVLTree(){
    delete root;
}


/********************************************************************
 * Supporting methods
 *******************************************************************/

AVLTree::Node *AVLTree::findSymPred(AVLTree::Node *n) {
    auto smallest_node = n->left;
    if(smallest_node != nullptr) {
        while(smallest_node->right != nullptr) {
            smallest_node = smallest_node->right;
        }
    }

    return smallest_node;
}


/********************************************************************
 * search, insert and remove
 *******************************************************************/

AVLTree::Node *AVLTree::search(const int value) {
    if (root == nullptr) {
        return nullptr;
    }
    return root->search(value);
}

AVLTree::Node *AVLTree::Node::search(const int value) {
    if (value == key) {
        return this;
    }
    if (value < key && left != nullptr) {
        return left->search(value);
    }
    if (value > key && right != nullptr) {
        return right->search(value);
    }
    return nullptr;
}

void AVLTree::insert(int value) {
    if (root == nullptr) {
        root = new Node(value);
    } else {
        insert(value, root);
    }
}

void AVLTree::insert(int value, Node *node) {
    if (value != node->key) {
        if (value < node->key) {
            if (node->left == nullptr) {
                node->left = new Node(value);
            } else {
                insert(value, node->left);
            }
        } else {
            if (node->right == nullptr) {
                node->right = new Node(value);
            } else {
                insert(value, node->right);
            }
        }
        upin(node);
    }
}

void AVLTree::remove(const int key) {
    auto p = search(key);

    if(p != nullptr) {
        if(p != root) {
            // case 1
            if(p->left == nullptr && p->right == nullptr) {
                // q is right successor of pp
                if(p->key < p->prev->key) {
                    // case 1.1
                    if(p->prev->right->bal == '0') {
                        p->prev->bal = 0;
                        upout(p->prev);
                    }
                        // case 1.2
                    else if(p->prev->right->bal == '1') {
                        p->prev->bal = 1;
                    }
                        // case 1.3
                    else {

                    }
                    // replace p with a leaf (nullptr) and
                    // delete p
                    p->prev->left = nullptr;
                    delete p;
                }
                    // q is left successor of pp
                else {
                    // replace p with a leaf (nullptr) and
                    // delete p
                    p->prev->right = nullptr;
                    delete p;
                }
            }
                // case 2
            else if ((p->left == nullptr && p->right != nullptr) || (p->left != nullptr && p->right == nullptr)) {

            }
                // case 3
            else {

            }
        }
        else {
            if(p->left == nullptr && p->right == nullptr) {
                root = nullptr;
            }
            else {
                if(p->left != nullptr && p->right == nullptr) {
                    root = p->left;
                }
                else {
                    root = p->right;
                }
                root->prev = nullptr;
            }
            delete p;
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
    if(oldRoot->right != nullptr) {
        oldRoot->right->prev = oldRoot;
    }
    newRoot->left = oldRoot;
    newRoot->prev = oldRoot->prev;
    oldRoot->prev = newRoot;
    return newRoot;
}

AVLTree::Node *AVLTree::rotateRight(Node *n) {
    Node *oldRoot = n;
    Node *newRoot = oldRoot->left;
    oldRoot->left = newRoot->right;
    if(oldRoot->left != nullptr) {
        oldRoot->left->prev = oldRoot;
    }
    newRoot->right = oldRoot;
    newRoot->prev = oldRoot->prev;
    oldRoot->prev = newRoot;
    return newRoot;
}

AVLTree::Node *AVLTree::rotateLeftRight(Node *n) {
    n->left = rotateLeft(n->left);
    n->left->prev = n;
    return rotateRight(n);
}

AVLTree::Node *AVLTree::rotateRightLeft(Node *n) {
    n->right = rotateRight(n->right);
    n->right->prev = n;
    return rotateLeft(n);
}


/********************************************************************
 * upin(p) and upout(p)
 *******************************************************************/

void AVLTree::upin(Node *node) {

}

void AVLTree::upout(Node *node) {
    if(node->bal == '0') {
        // p is left child of father pp
        if(node->key < node->prev->key) {
            if(node->prev->bal == '-1') {
                node->prev->bal = 0;
            }
            else if(node->prev->bal == '0') {
                node->prev->bal = 1;
            }
            else {
                // case 1.3.1
                if(node->prev->right->bal == '0') {
                    if(node->prev->key < node->prev->prev->key) {
                        // we have to link the left pointer of the father
                        // of the father to the return of rotate method
                        node->prev->prev->left = rotateLeft(node->prev);
                    }
                    else {
                        // we have to link the right pointer of the father
                        // of the father to the return of rotate method
                        node->prev->prev->right = rotateLeft(node->prev);
                    }
                }
                // case 1.3.2
                else if(node->prev->right->bal == '1') {
                    if(node->prev->key < node->prev->prev->key) {
                        node->prev->prev->left = rotateLeft(node->prev);
                        upout(node->prev->prev->left);
                    }
                    else {
                        node->prev->prev->right = rotateLeft(node->prev);
                        upout(node->prev->prev->right);
                    }
                }
                // case 1.3.3
                else {
                    if(node->prev->key < node->prev->prev->key) {
                        node->prev->prev->left = rotateRightLeft(node->prev);
                        upout(node->prev->prev->left);
                    }
                    else {
                        node->prev->prev->right = rotateRightLeft(node->prev);
                        upout(node->prev->prev->right);
                    }
                }
            }
        }
        // p is right child of father pp
        else {
            if(node->prev->bal == '-1') {
                node->prev->bal = 0;
            }
            else if(node->prev->bal == '0') {
                node->prev->bal = 1;
            }
            else {
                // case 2.3.1
                if(node->prev->left->bal == '0') {
                    if(node->prev->key < node->prev->prev->key) {
                        // we have to link the left pointer of the father
                        // of the father to the return of rotate method
                        node->prev->prev->left = rotateRight(node->prev);
                    }
                    else {
                        // we have to link the right pointer of the father
                        // of the father to the return of rotate method
                        node->prev->prev->right = rotateRight(node->prev);
                    }
                }
                    // case 2.3.2
                else if(node->prev->left->bal == '1') {
                    if(node->prev->key < node->prev->prev->key) {
                        node->prev->prev->left = rotateRight(node->prev);
                        upout(node->prev->prev->left);
                    }
                    else {
                        node->prev->prev->right = rotateRight(node->prev);
                        upout(node->prev->prev->right);
                    }
                }
                    // case 2.3.3
                else {
                    if(node->prev->key < node->prev->prev->key) {
                        node->prev->prev->left = rotateLeftRight(node->prev);
                        upout(node->prev->prev->left);
                    }
                    else {
                        node->prev->prev->right = rotateLeftRight(node->prev);
                        upout(node->prev->prev->right);
                    }
                }
            }
        }
    }
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
