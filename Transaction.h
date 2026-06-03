#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

// Forward declarations
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