// intbst.cpp
// Implements class IntBST
// Alex Wray, 1/22/2026

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() { 
    root = nullptr;
}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
    root = nullptr;
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if (n == nullptr) {return;}
    if (n->left) {
        clear(n->left);
        n->left = nullptr;
    }
    if (n->right) {
        clear(n->right);
        n->right = nullptr;
    }
    n->parent = nullptr;
    delete n;
    n = nullptr;
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if (root == nullptr) {
        root = new Node();
        root->info = value;
        return true;
    }
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if (value == n->info) {
        return false;
    }
    if (value < n->info) {
        if (n->left) {
            return insert(value, n->left);
        }
        else {
            n->left = new Node();
            n->left->info = value;
            n->left->parent = n;
            return true;
        }
    }
    else {
        if (n->right) {
            return insert(value, n->right);
        }
        else {
            n->right = new Node();
            n->right->info = value;
            n->right->parent = n;
            return true;
        }
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
    //cout << endl;
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if (n == nullptr) {return;}
    cout << n->info << " ";
    printPreOrder(n->left);
    printPreOrder(n->right);
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
    //cout << endl;
}
void IntBST::printInOrder(Node *n) const {
    if (n == nullptr) {return;}
    printInOrder(n->left);
    cout << n->info << " ";
    printInOrder(n->right);
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
    //cout << endl;
}

void IntBST::printPostOrder(Node *n) const {
    if (n == nullptr) {return;}
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
}

// return sum of values in tree
int IntBST::sum() const {
    if (root == nullptr) {return 0;}
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    int c = n->info;
    if (n->left) {
        c += sum(n->left);
    }
    if (n->right) {
        c += sum(n->right);
    }
    return c;
}

// return count of values
int IntBST::count() const {
    if (root == nullptr) {return 0;}
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    int c = 1;
    if (n->left) {
        c += count(n->left);
    }
    if (n->right) {
        c += count(n->right);
    }
    return c;
}

// returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if (n == nullptr) {return nullptr;}
    if (value == n->info) {return n;}
    else if (value < n->info) {
        return getNodeFor(value, n->left);
    }
    else {
        return getNodeFor(value, n->right);
    }
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    return getNodeFor(value, root) != nullptr;
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node* n = root;
    Node* maxLess = nullptr;
    while (n != nullptr) {
        if (n->info < value) {
            //if (maxLess == nullptr || maxLess->info < n->info) {}
            maxLess = n;
            n = n->right;
        }
        else {
            n = n->left;
        }
    }
    return maxLess;
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    Node* curr = getPredecessorNode(value);
    if (curr) {
        return curr->info;
    }
    return 0;
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    Node* n = root;
    Node* minGreater = nullptr;
    while (n != nullptr) {
        if (n->info > value) {
            //if (minGreater == nullptr || minGreater->info > n->info) {}
            minGreater = n;
            n = n->left;
        }
        else {
            n = n->right;
        }
    }
    return minGreater;
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    Node* curr = getSuccessorNode(value);
    if (curr) {
        return curr->info;
    }
    return 0;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){

    Node* n = getNodeFor(value, root);
    if (!n) {
        return false;
    }
    //joins left and right into one tree, next
    Node* next = n->right;
    if (next == nullptr) {
        next = n->left;
    } else {
        Node* curr = next;
        while (curr->left) {
            curr = curr->left;
        }
        curr->left = n->left;
        curr->left->parent = curr;
    }

    //links parents to next
    if (n->parent) {
        if (n->parent->left == n) {
            n->parent->left = next;
        }
        else{
            n->parent->right = next;
        }   
    } else {
        root = next;
    }

    if (next) {next->parent = n->parent;}
    delete n;
    n = nullptr;
    return true;
}
