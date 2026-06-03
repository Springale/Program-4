#include "Transaction.h"
#include "Store.h"
#include "Customer.h"
#include "Movie.h"
#include "Inventory.h"
#include <iostream>

// constructor
Transaction::Transaction(Customer* c, Movie* m) : customer(c), movie(m) {}

// virtual destructor
Transaction::~Transaction() {}

// ==========================================
// --- Borrow transaction subclass --- 

Borrow::Borrow(Customer* c, Movie* m) : Transaction(c, m) {}

void Borrow::execute(Store &store) {
    if (customer == nullptr || movie == nullptr) {
        std::cerr << "Borrow Error: Missing customer or movie reference." << std::endl;
        return;
    }

    // check if the movie is available
    if (movie->getStock() <= 0) {
        std::cerr << "Borrow Error: \"" << movie->getTitle() << "\" is out of stock." << std::endl;
        return;
    }

    movie->decreaseStock(1);                        // reduce inventory count
    customer->trackBorrow(movie->getKey());         // add to customer's active borrows map
    customer->addHistory(this);                     // save this transaction pointer in customer history
}

// ==========================================
// --- Return transaction subclass --- 

Return::Return(Customer* c, Movie* m) : Transaction(c, m) {}

void Return::execute(Store &store) {
    if (customer == nullptr || movie == nullptr) {
        std::cerr << "Return Error: Missing customer or movie reference." << std::endl;
        return;
    }

    // Professor's Feedback Fix: Check if customer actually has it checked out
    if (!customer->hasBorrowed(movie->getKey())) {
        std::cerr << "Return Error: Customer " << customer->getID() 
                  << " did not borrow \"" << movie->getTitle() << "\"." << std::endl;
        return;
    }

    movie->increaseStock(1);                        // return item to inventory stock
    customer->trackReturn(movie->getKey());         // decrement active borrow map count
    customer->addHistory(this);                     // save this transaction pointer in customer history
}

// ==========================================
// --- History transaction subclass --- 

History::History(Customer* c) : Transaction(c, nullptr) {}

void History::execute(Store &store) {
    // check if customer exists
    if (customer == nullptr) {
        std::cerr << "History Error: Customer account does not exist." << std::endl;
        return;
    }
    
    customer->displayHistory(); 
}

// ==========================================
// --- Display inventory transaction subclass --- 

DisplayInventory::DisplayInventory() : Transaction(nullptr, nullptr) {}

void DisplayInventory::execute(Store &store) {
    store.getInventory()->displayInventory();
}