/*
 * -----------------------------------------------------------------------------
 * File: TransactionFactory.h
 * Author: Lidia Workneh, Sam Pasarakonda
 * Course: CSS 343
 * Assignment: Program 4 - Movie Rental Store
 * Date: May 2026
 *
 * Description:
 * Declares the TransactionFactory class, which parses a command line
 * string and constructs the correct Transaction subclass (Borrow, Return,
 * History, or DisplayInventory). Validates customer ID, media type, genre
 * code, and movie existence against the Store before creating a transaction.
 * -----------------------------------------------------------------------------
 */
 
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