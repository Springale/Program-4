/*
 * -----------------------------------------------------------------------------
 * File: Customer.h
 * Author: Lidia Workneh, Sam Pasarakonda
 * Course: CSS 343
 * Assignment: Program 4 - Movie Rental Store
 * Date: May 2026
 *
 * Description:
 * Defines the Customer class, which represents a store member identified
 * by a unique 4-digit ID. Tracks borrow/return transaction history and
 * maintains a count of active rentals per movie key to validate returns.
 * History is displayed in reverse chronological order (newest first).
 * -----------------------------------------------------------------------------
 */
 
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
#include <unordered_map>

class Transaction; 

class Customer {
private:
    int id;                                          // unique 4-digit customer ID
    std::string firstName;                           // customer's first name
    std::string lastName;                            // customer's last name
    std::vector<Transaction*> history;               // stores transaction history from oldest to newest
    std::unordered_map<std::string, int> activeRentals; // tracks active borrows

public:
    // constructor & destructor
    Customer(int id, const std::string &fName, const std::string &lName);
    ~Customer();

    // saves a processed Borrow or Return transaction pointer
    void addHistory(Transaction* transaction);
    // prints customer transactions from most recent to oldest       
    void displayHistory() const;                     
    
    // return Validation helpers 
    void trackBorrow(const std::string &movieKey);   // increments the count for a borrowed movie key
    bool trackReturn(const std::string &movieKey);   // decrements the count for a returned movie key
    bool hasBorrowed(const std::string &movieKey) const; // verifies if active rental count for a key is > 0

    // accessors
    int getID() const;                               // returns the customer's ID
    std::string getName() const;                     // returns the full name formatted
};

#endif