/*
 * -----------------------------------------------------------------------------
 * File: Transaction.cpp
 * Author: Lidia Workneh, Sam Pasarakonda
 * Course: CSS 343
 * Assignment: Program 4 - Movie Rental Store
 * Date: June 2026
 *
 * Description:
 * Implements the Transaction subclasses. Borrow decreases stock and records
 * the rental. Return validates the customer borrowed the movie, restores
 * stock, and suggests in-stock Classic alternatives when out of stock.
 * History and DisplayInventory print records without modifying state.
 * -----------------------------------------------------------------------------
 */

#include "Transaction.h"
#include "Store.h"
#include "Customer.h"
#include "Movie.h"
#include "Classic.h"
#include "Inventory.h"
#include <iostream>

// constructor
Transaction::Transaction(Customer* c, Movie* m) : customer(c), movie(m), success(false) {}

// virtual destructor
Transaction::~Transaction() {}

// ==========================================
// Borrow subclass 

Borrow::Borrow(Customer* c, Movie* m) : Transaction(c, m) {}

void Borrow::execute(Store &store) {
    if (customer == nullptr || movie == nullptr) {
        std::cerr << "Borrow Error: Missing customer or movie reference." << std::endl;
        return;
    }

    // check if the movie is available
    if (movie->getStock() <= 0) {
        std::cerr << "Borrow Error: \"" << movie->getTitle() << "\" ("
                  << movie->getKey() << ") is out of stock.\n";

        if (movie->getType() == 'C') {
            auto alts = store.getInventory()->getClassicAlternatives(
                movie->getTitle(), movie->getKey());
            if (!alts.empty()) {
                std::cerr << "  Available versions of \"" << movie->getTitle() << "\":\n";
                for (Movie* alt : alts) {
                    Classic* c = dynamic_cast<Classic*>(alt);
                    std::cerr << "    - " << c->getActor()
                              << " (" << c->getMonth() << "/" << c->getYear() << ")"
                              << " — " << c->getStock() << " in stock\n";
                }
            }
        }
        return;
    }

    movie->decreaseStock(1);
    customer->trackBorrow(movie->getKey());
    customer->addHistory(this);
    success = true;
}

void Borrow::display() const {
    std::cout << "borrow transaction" << std::endl;
}

// ==========================================
// Return subclass 

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

    movie->increaseStock(1);
    customer->addHistory(this);
    success = true;
}

void Return::display() const {
    std::cout << "return transaction" << std::endl;
}

// ==========================================
// History subclass 

History::History(Customer* c) : Transaction(c, nullptr) {}

void History::execute(Store &store) {
    if (customer == nullptr) {
        std::cerr << "History Error: Customer account does not exist." << std::endl;
        return;
    }
    
    customer->displayHistory();
    success = true;
}

void History::display() const {
    std::cout << "history transaction" << std::endl;
}

// ==========================================
// Display inventory subclass
DisplayInventory::DisplayInventory()
    : Transaction(nullptr, nullptr) {}

void DisplayInventory::execute(Store &store) {
    if (store.getInventory()) {
        store.getInventory()->displayInventory();
        success = true;
    }
}

void DisplayInventory::display() const {
    std::cout << "display inventory transaction" << std::endl;
}
