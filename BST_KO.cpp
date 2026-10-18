//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Kaitlyn OConnell
// Version     : 1.0
// Copyright   : Copyright � 2023 SNHU COCE
// Description : Lab 5-2 Binary Search Tree
//============================================================================
#include <iostream>
#include <time.h>
#include <string>
#include <vector>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

// Internal structure for tree node
struct Node {
    Bid bid;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Bid aBid) : Node() {
        bid = aBid;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    Node* removeNode(Node* node, string bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // FixMe (1): initialize housekeeping variables
    root = nullptr; // root starts empty
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    //FixMe (2)
    // recurse from root deleting every node

    // simple post-order delete
    while (root != nullptr) {
        root = removeNode(root, root->bid.bidId);
    }
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // FixMe (3a): In order root
    // call inOrder function and pass root
    inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // FixMe (4a): Post order root
    postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // FixMe (5a): Pre order root
    preOrder(root);
}

/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    // FIXME (6a) Implement inserting a bid into the tree

    // if root equal to null ptr
    if (root == nullptr) {
        root = new Node(bid);
    }
    else {
        // add Node root and bid
        addNode(root, bid);
    }
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    // FIXME (7a) Implement removing a bid from the tree
    root = removeNode(root, bidId);
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {

    // FIXME (8) Implement searching the tree for a bid

    Node* current = root;

    // keep looping downwards until bottom reached or matching bidId found
    while (current != nullptr) {

        // if match found, return current bid
        if (current->bid.bidId == bidId) {
            return current->bid;
        }

        // if bid is smaller than current node then traverse left
        if (bidId < current->bid.bidId) {
            current = current->left;
        }
        else {
            // else larger so traverse right
            current = current->right;
        }
    }

    // return empty bid if not found
    Bid bid;
    return bid;
}

/**
 * Add a bid to some node (recursive)
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {

    // FIXME (6b) Implement inserting a bid into the tree

    // if bid is smaller then go left
    if (bid.bidId < node->bid.bidId) {

        // if no left node
        if (node->left == nullptr) {
            node->left = new Node(bid);
        }
        else {
            // recurse down the left node
            addNode(node->left, bid);
        }
    }
    else {
        // else go right

        if (node->right == nullptr) {
            node->right = new Node(bid);
        }
        else {
            // recurse down the right node
            addNode(node->right, bid);
        }
    }
}

void BinarySearchTree::inOrder(Node* node) {
    // FixMe (3b): In order traversal

    if (node != nullptr) {
        // left(small)
        inOrder(node->left);

        // output
        cout << node->bid.bidId << ": "
            << node->bid.title << " | "
            << node->bid.amount << " | "
            << node->bid.fund << endl;

        // right(large)
        inOrder(node->right);
    }
}

void BinarySearchTree::postOrder(Node* node) {
    // FixMe (4b): Post order

    if (node != nullptr) {
        postOrder(node->left);
        postOrder(node->right);

        cout << node->bid.bidId << ": "
            << node->bid.title << " | "
            << node->bid.amount << " | "
            << node->bid.fund << endl;
    }
}

void BinarySearchTree::preOrder(Node* node) {
    // FixMe (5b): Pre order

    if (node != nullptr) {
        cout << node->bid.bidId << ": "
            << node->bid.title << " | "
            << node->bid.amount << " | "
            << node->bid.fund << endl;

        preOrder(node->left);
        preOrder(node->right);
    }
}

/**
 * Remove a bid from some node (recursive)
 */
Node* BinarySearchTree::removeNode(Node* node, string bidId) {

    // FIXME (7b) Implement removing a bid from the tree

    if (node == nullptr) {
        return node;
    }

    // go left
    if (bidId < node->bid.bidId) {
        node->left = removeNode(node->left, bidId);
    }
    // go right
    else if (bidId > node->bid.bidId) {
        node->right = removeNode(node->right, bidId);
    }
    else {
        // node found

        // no children
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }
        // one child (right/large)
        else if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        // one child (left/small)
        else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        // two children
        else {
            // find min in right subtree
            Node* temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }

            // copy value
            node->bid = temp->bid;

            // delete duplicate
            node->right = removeNode(node->right, temp->bid.bidId);
        }
    }

    return node;
}
/**
*
*
**/