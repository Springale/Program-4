#ifndef TRANSACTION_FACTORY_H
#define TRANSACTION_FACTORY_H

#include <string>

class Transaction;
class Store;

class TransactionFactory {
public:
    // reads a command line string, validates elements against the Store, and instantiates the correct Transaction subclass
    static Transaction* createTransaction(const std::string &line, Store &store);

private:
    // helper function
    static std::string trimLeft(std::string s);
};

#endif 