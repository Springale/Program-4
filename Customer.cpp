#include "Customer.h"
#include "Transaction.h"
#include <iostream>

// constructor
Customer::Customer(int id, const std::string &fName, const std::string &lName)
    : id(id), firstName(fName), lastName(lName) {}

// destructor cleans up transaction objects stored in history
Customer::~Customer() {
    for (Transaction* trans : history) {
        delete trans;
    }
    history.clear();
}

// adds a valid transaction to the customer's history
void Customer::addHistory(Transaction* transaction) {
    if (transaction != nullptr) {
        history.push_back(transaction);
    }
}

// displays history from most recent to oldest
void Customer::displayHistory() const {
    std::cout << "\n** Transaction History for Customer "
              << id << ": " << lastName << ", " << firstName
              << " **" << std::endl;

    if (history.empty()) {
        std::cout << "   no transaction history found." << std::endl;
        return;
    }

    // loop backwards so newest transactions appear first
    for (int i = static_cast<int>(history.size()) - 1; i >= 0; --i) {
        std::cout << "   ";
        history[i]->display();
    }
}

// increments active rental count for a movie
void Customer::trackBorrow(const std::string &movieKey) {
    activeRentals[movieKey]++;
}

// decrements active rental count for a movie
void Customer::trackReturn(const std::string &movieKey) {
    auto it = activeRentals.find(movieKey);

    if (it != activeRentals.end()) {
        it->second--;

        // remove entry when no active copies remain
        if (it->second <= 0) {
            activeRentals.erase(it);
        }
    }
}

// returns true if the customer currently has this movie checked out
bool Customer::hasBorrowed(const std::string &movieKey) const {
    auto it = activeRentals.find(movieKey);

    return (it != activeRentals.end() && it->second > 0);
}

// getters
int Customer::getID() const {
    return id;
}

std::string Customer::getName() const {
    return firstName + " " + lastName;
}