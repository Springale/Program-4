// ------------------------------------------------ Store.cpp ----------------------------------------------
//
// Programmer: Lidia Workneh, Partner Name
// Course: CSS 343
// Date: June 2026
//
// ---------------------------------------------------------------------------------------------------------
// Purpose:
// Implements the Store class. Responsible for loading customer and movie
// data, processing transaction commands, and coordinating interactions
// between customers, inventory, and transactions.
//
// ---------------------------------------------------------------------------------------------------------
// Notes:
// - Uses MovieFactory to construct movie objects dynamically.
// - Uses TransactionFactory to construct transaction objects dynamically.
// - Inventory and customer records are allocated dynamically and released
//   by the Store destructor.
// - Error messages are displayed for invalid files and invalid commands.
// ---------------------------------------------------------------------------------------------------------

#include "Store.h"
#include "Inventory.h"
#include "HashTable.h" 
#include "Movie.h"
#include "Transaction.h"
#include "MovieFactory.h"
#include "TransactionFactory.h"
#include "Customer.h"

Store::Store() : inventory(new Inventory()),
      customerTable(new HashTable<Customer*>()) {
}

Store::~Store() {
    delete inventory; // Inventory destructor clears all Movie objects
    
    // TODO: Verify HashTable implementation.
    // If HashTable does not delete stored Customer* objects,
    // iterate through the table and delete each Customer* before
    // deleting the hash table itself.
    
    delete customerTable; 
}

// load Customers from data4customers.txt
void Store::loadCustomers(const std::string &filename) {
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Error: Could not open customer file: " << filename << std::endl;
        return;
    }

    int id;
    std::string lastName, firstName;
    
    // read formatted data
    while (infile >> id >> lastName >> firstName) {
        Customer* newCustomer = new Customer(id, firstName, lastName);
        
        // use string version of ID as key for hash table
        std::string key = std::to_string(id);
        customerTable->insert(key, newCustomer);
    }
}

// load Movies from data4movies.txt
void Store::loadMovies(const std::string &filename) {
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Error: Could not open movie file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(infile, line)) {
        if (line.empty()) continue;

        // factory dynamically builds the right subclass (Comedy, Drama, Classic)
        Movie* newMovie = MovieFactory::createMovie(line);
        
        if (newMovie != nullptr) {
            // handles duplicate logic by incrementing stock internally
            inventory->addMovie(newMovie);
            // (TODO: verify stock-increment behavior in addMovie())
        } else {
            std::cerr << "Parse Error: Skipping invalid movie entry line: " << line << std::endl;
        }
    }
}

// process Commands from data4commands.txt
void Store::processCommands(const std::string &filename) {
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Error: Could not open commands file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(infile, line)) {
        if (line.empty()) continue;

        // factory parses line and returns correct Transaction type
        Transaction* trans = TransactionFactory::createTransaction(line, *this);

        if (trans != nullptr) {
            trans->execute(*this); // Polymorphic execution

            // Check if the transaction is just a "Display" or "History" command
            // We use dynamic_cast to check if it's one of the temporary print actions
            if (dynamic_cast<History*>(trans) != nullptr || 
                dynamic_cast<DisplayInventory*>(trans) != nullptr) {
                
                // Safe to delete immediately because Customer didn't save a pointer to it
                delete trans; 
            }
            // TODO: Verify transaction ownership.
            // Borrow and Return transactions may be stored by Customer
            // for history tracking. If not, they should be deleted here
            // to avoid memory leaks.
        }
    }
}

// retrieve a customer from the HashTable
Customer* Store::getCustomer(int id) const {
    std::string key = std::to_string(id);
    return customerTable->find(key); // TODO: This is assuming find returns nullptr if key doesn't exist
}

// access inventory (used by transactions)
Inventory* Store::getInventory() const {
    return inventory;
}