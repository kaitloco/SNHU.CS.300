//============================================================================
// Name        : HashTable.cpp
// Author      : Kaitlyn OConnell 
// Version     : 1.0
// Copyright   : Copyright © 2023 SNHU COCE
// Description : Lab 4-2 Hash Table
//============================================================================

#include <algorithm>
#include <climits>
#include <iostream>
#include <string> // atoi
#include <time.h>
#include <vector>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

const unsigned int DEFAULT_SIZE = 179;

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

//============================================================================
// Hash Table class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a hash table with chaining.
 */
class HashTable {

private:
    // Define structures to hold bids
    struct Node {
        Bid bid;
        unsigned int key;
        Node *next;

        // default constructor
        Node() {
            key = UINT_MAX; // use key indicator that the cell has not ye been occupied. 
            next = nullptr;
        }

        // initialize with a bid
        Node(Bid aBid) : Node() {
            bid = aBid;
        }

        // initialize with a bid and a key
        Node(Bid aBid, unsigned int aKey) : Node(aBid) {
            key = aKey;
        }
    };

    vector<Node> nodes;

    unsigned int tableSize = DEFAULT_SIZE;

    unsigned int hash(int key);

public:
    HashTable();
    HashTable(unsigned int size);
    virtual ~HashTable();
    void Insert(Bid bid);
    void PrintAll();
    void Remove(string bidId);
    Bid Search(string bidId);
    size_t Size();
};

/**
 * Default constructor
 */
HashTable::HashTable() {
    // FIXME (1): Initialize the structures used to hold bids
    nodes.resize(tableSize); 

    // Initalize node structure by resizing tableSize
}

/**
 * Constructor for specifying size of the table
 * Use to improve efficiency of hashing algorithm
 * by reducing collisions without wasting memory.
 */
HashTable::HashTable(unsigned int size) {
    // invoke local tableSize to size with this->
    // resize nodes size
	this->tableSize = size;
	nodes.resize(size);
}


/**
 * Destructor
 */
HashTable::~HashTable() {
    // FIXME (2): Implement logic to free storage when class is destroyed
    nodes.erase(nodes.begin(), nodes.end()); 
    // erase nodes beginning
    //No deletion this is clearing vector.
}

/**
 * Calculate the hash value of a given key.
 * Note that key is specifically defined as
 * unsigned int to prevent undefined results
 * of a negative list index.
 *
 * @param key The key to hash
 * @return The calculated hash
 */
unsigned int HashTable::hash(int key) {
    // FIXME (3): Implement logic to calculate a hash value
	return key % tableSize;
    // return key tableSize
}

/**
 * Insert a bid
 *
 * @param bid The bid to insert
 */
void HashTable::Insert(Bid bid) {
    // FIXME (4): Implement logic to insert a bid
    // create the key for the given bid
    unsigned int key = hash(atoi(bid.bidId.c_str()));
	Node* oldNode = &nodes.at(key);

    //Vector always has a node. 
    if (oldNode ->key == UINT_MAX) {
        oldNode->bid = bid;
		oldNode->key = key;
		oldNode->next = nullptr;
    }
    else {
                if (oldNode->key == UINT_MAX) {
            oldNode->bid = bid;
            oldNode->key = key;
			oldNode->next = nullptr;
                }
                else {
                    //you have key collision
					//find the next open node
                    while (oldNode->next != nullptr) {
                        oldNode = oldNode->next;
                    }
                    Node* newNode = new Node(bid, key);
					oldNode->next = newNode;
                }
    }
    // retrieve node using key
    // if no entry found for the key
        // assign this node to the key position
    // else if node is not used
         // assing old node key to UNIT_MAX, set to key, set old node to bid and old node next to null pointer
    // else find the next open node
            // add new newNode to end
}

/**
 * Print all bids
 */
void HashTable::PrintAll() {
    // FIXME (5): Implement logic to print all bids
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        if (it->key != UINT_MAX) {
			cout << "Key " << it->key << " : " 
                << it->bid.bidId << ", " 
                << it->bid.title << ", " 
                << it->bid.amount << ", " 
                << it->bid.fund << endl;
            Node* node = it->next;
            while (node != nullptr) {
                cout << "Key " << node->key << " : " 
                    << node->bid.bidId << ", " 
                    << node->bid.title << ", " 
                    << node->bid.amount << ", " 
                    << node->bid.fund << endl;
                node = node->next;
			}
	}
    // for node begin to end iterate
    //   if key not equal to UINT_MAx
            // output key, bidID, title, amount and fund
            // node is equal to next iter
            // while node not equal to nullptr
               // output key, bidID, title, amount and fund
               // node is equal to next node

}

/**
 * Remove a bid
 *
 * @param bidId The bid id to search for
 */
    void HashTable::Remove(string bidId) {
    // FIXME (6): Implement logic to remove a bid
    unsigned int key = hash(atoi(bidId.c_str()));
    Node* node = &nodes.at(key);
    /// if the bucket is empty
    if (node->key == UINT_MAX) {
        return;
    }
   //check the node 
        if (node->bid.bidId.compare(bidId) == 0;  {
            //remove this node
            std::cout << "remove top nodes for " << bidId << std::endl;
            if (node->next == nullptr) {
                node->key = UINT_MAX;
            else {
                Node* temp = node->next;
                *node = *temp;
                delete temp;
            }
            return; 
            }
                Node* cur = node->next;
                Node* pre = node;
                while (cur != nullptr) {
                    if (cur->bid.bidId.compare(bidId) == 0; {
                        //remove this node
                        pre->next = cur->next;
                        delete cur;
                        cur = nullptr;
                        return;
                    }
                    pre = cur;
                        cur = cur->next;
                }
            }
    // set key equal to hash atoi bidID cstring
    // erase node begin and key
}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
        Bid HashTable::Search(string bidId) {
    Bid bid;

    // FIXME (7): Implement logic to search for and return a bid
	unsigned int key = hash(atoi(bidId.c_str()));
	Node* node = &nodes.at(key);
	while (node != nullptr && node->key != UINT_MAX) {
        if (node->bid.bidId.compare(bidId) == 0; {
            return node->bid;
        }
    node = node->next;
	}
	return bid;
    // create the key for the given bid
    // if entry found for the key
         //return node bid
	
    // if no entry found for the key
      // return bid
    // while node not equal to nullptr
        // if the current node matches, return it
        //node is equal to next node

    return bid;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, HashTable* hashTable) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            hashTable->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98223";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales.csv";
        bidKey = "98223";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a hash table to hold all the bids
    HashTable* bidTable;

    Bid bid;
    bidTable = new HashTable();
    
    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bidTable);

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bidTable->PrintAll();
            break;

        case 3:
            ticks = clock();

            bid = bidTable->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
                cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 4:
            bidTable->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}

/// Code Reflection
//We needed to implement the hash table with chaining. 
// We used a vector of nodes to hold the bids. Each node has a bid, a key and a pointer to the next node. 
// We implemented: 
//  the hash function to calculate the hash value of a given key. 
//  the insert function to insert a bid into the hash table. 
//  the print all function to print all the bids in the hash table. 
//  the remove function to remove a bid from the hash table. 
//  the search function to search for a bid in the hash table. 
//  Last but not least, main function implementation was necessary to test our hash table functionality.
// I used a modulo-based hash function to map bid IDs to a vector, and used linked list chaining using the Node* next function, that waay multiple bids could store using one index. 
// Challenges I faced were with the bid search and bid remove functions, I struggled to get the linked lists to correctly check each node for the bidID without errors. 
// With the remove function, removing the first node in the chain was a challenge, I had to make sure to update the head of the chain correctly.
// I ended up using a while loop to traverse the chain and check each node for the bidID, and if found, I updated the pointers to remove the node from the chain.
//PseudoCode: 
// Insert(bid): 
//  Key = hash(bidID)
//  Node = table[key]
// if node is empty:
//  the bid stored in the node
// else:
//  if not null 
//  move to next node
// create new node with bid and add to end of chain
// PrintAll():
// for each node in table:
// if node is not empty:
// print node info
// move to next node in chain and print info until end of chain
// Search(bidID):
// Key = hash(bidID)
// Node = table[key]
// while node is not null:
// if node bidID matches search bidID:
// return node bid
// move to next node in chain
// return empty bid if not found
// Remove(bidID):
//   Key = hash(bidID)
//   Node = table[key]
//   if node is empty:
//     return
//   if node bidID matches remove bidID:
//      else copy next node to current node and delete next node
//  traverse chain to find bidID and remove node if found
// The overall importance and function of the HashTable is to efficiently handle large loads of data without collision, and is pertinent for large scale data storage/systems. 