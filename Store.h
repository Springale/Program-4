#ifndef STORE_H
#define STORE_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Inventory;
template <typename V> class HashTable;
class Customer;
class Transaction;

class Store {
private:
    Inventory* inventory;
    HashTable<Customer*>* customerTable;

public:
    // constructor & destructor
    Store();
    ~Store();

    // reads customer files and populates the customer hash table
    void loadCustomers(const std::string &filename);

    // reads movie files and builds the sorted genre inventories
    void loadMovies(const std::string &filename);

    // reads and executes rental transactions and store operations
    void processCommands(const std::string &filename);

    // helper functions
    Customer* getCustomer(int id) const; // Retrieves a specific customer using their ID
    Inventory* getInventory() const;     // Returns a pointer to the inventory for stock adjustments
};

#endif