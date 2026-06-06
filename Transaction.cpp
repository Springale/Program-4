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

// display
void Borrow::display() const {
    std::cout << "borrow transaction" << std::endl;
}

// ==========================================
// --- Return transaction subclass --- 

Return::Return(Customer* c, Movie* m) : Transaction(c, m) {}

void Return::execute(Store &store) {
    if (customer == nullptr || movie == nullptr) {
        std::cerr << "Return Error: Missing customer or movie reference." << std::endl;
        return;
    }

    if (!customer->trackReturn(movie->getKey())) {
        std::cerr << "Return Error: Customer " << customer->getID()
                << " did not borrow \"" << movie->getTitle() << "\"." << std::endl;
        return;
    }

    customer->trackReturn(movie->getKey());
    movie->increaseStock(1);                        // return item to inventory stock
    customer->addHistory(this);                     // save this transaction pointer in customer history
}

// display
void Return::display() const {
    std::cout << "return transaction" << std::endl;
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

void History::display() const {
    std::cout << "history transaction" << std::endl;
}

// ==========================================
// --- Display inventory transaction subclass --- 
DisplayInventory::DisplayInventory()
    : Transaction(nullptr, nullptr) {}

void DisplayInventory::execute(Store &store) {
    if (store.getInventory()) {
        store.getInventory()->displayInventory();
    }
}

void DisplayInventory::display() const {
    std::cout << "display inventory transaction" << std::endl;
}
