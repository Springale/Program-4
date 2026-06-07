/*
 * -----------------------------------------------------------------------------
 * File: Transaction.h
 * Author: Lidia Workneh, Sam Pasarakonda
 * Course: CSS 343
 * Assignment: Program 4 - Movie Rental Store
 * Date: May 2026
 *
 * Description:
 * Defines the Transaction abstract base class and its four concrete subclasses:
 * Borrow, Return, History, and DisplayInventory. Each subclass implements
 * execute() to carry out the corresponding store operation. Borrow and Return
 * are owned by the Customer's history after execution.
 * -----------------------------------------------------------------------------
 */

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

// forward declarations
class Store;
class Customer;
class Movie;

class Transaction {
protected:
    Customer* customer; 
    Movie* movie;       

public:
    // constructor & destructor
    Transaction(Customer* c = nullptr, Movie* m = nullptr);
    virtual ~Transaction();

    // pure virtual function executed by subclasses
    virtual void execute(Store &store) = 0; 
    virtual void display() const = 0;
};

// --- subclasses ---

class Borrow : public Transaction {
public:
    Borrow(Customer* c, Movie* m);
    void execute(Store &store) override;
    void display() const override;
};

class Return : public Transaction {
public:
    Return(Customer* c, Movie* m);
    void execute(Store &store) override;
    void display() const override;
};

class History : public Transaction {
public:
    History(Customer* c);
    void execute(Store &store) override;
    void display() const override;
};

class DisplayInventory : public Transaction {
public:
    DisplayInventory();
    void execute(Store &store) override;
    void display() const override;
};

#endif