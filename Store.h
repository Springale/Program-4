// ------------------------------------------------ Store.h ------------------------------------------------
//
// Programmer: Lidia Workneh, Sam Pasarakonda
// Course: CSS 343
// Date: June 2026
//
// ---------------------------------------------------------------------------------------------------------
// Purpose:
// Defines the Store class, which serves as the central coordinator for the
// movie rental system. The Store class manages customer records, inventory
// initialization, and transaction processing.
//
// ---------------------------------------------------------------------------------------------------------
// Notes:
// - Maintains a hash table of customers for efficient lookup by customer ID.
// - Owns and manages the Inventory object.
// - Loads customer, movie, and command data from input files.
// - Uses factory classes to create Movie and Transaction objects.
// ---------------------------------------------------------------------------------------------------------

#ifndef STORE_H
#define STORE_H

#include <string>

class Inventory;
class Customer;
template <typename V> class HashTable;

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