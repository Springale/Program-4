/*
 * -----------------------------------------------------------------------------
 * File: TransactionFactory.cpp
 * Author: Lidia Workneh, Sam Pasarakonda
 * Course: CSS 343
 * Assignment: Program 4 - Movie Rental Store
 * Date: May 2026
 *
 * Description:
 * Implements the TransactionFactory class. Parses each command line token
 * by token, validates the customer ID, media type, genre code, and movie
 * existence, then constructs and returns the appropriate Transaction object.
 * Returns nullptr and prints an error for any invalid input.
 * -----------------------------------------------------------------------------
 */
 
#include "TransactionFactory.h"
#include "Transaction.h"
#include "Store.h"
#include "Customer.h"
#include "Movie.h"
#include "Inventory.h"

#include <sstream>
#include <iostream>

// helper: trim leading spaces
std::string TransactionFactory::trimLeft(std::string s) {
    size_t start = s.find_first_not_of(" ");
    if (start == std::string::npos) return "";
    return s.substr(start);
}

// create transaction from command line
Transaction* TransactionFactory::createTransaction(const std::string &line, Store &store) {

    // ignore empty line
    if (line.empty()) return nullptr;

    std::stringstream ss(line);

    char actionCode;
    ss >> actionCode;

    // process inventory display command
    if (actionCode == 'I') {
        return new DisplayInventory();
    }

    // process history command
    if (actionCode == 'H') {

        int customerID;

        if (!(ss >> customerID)) {
            std::cerr << "error: malformed customer id in history command\n";
            return nullptr;
        }

        Customer* customer = store.getCustomer(customerID);

        if (!customer) {
            std::cerr << "error: customer not found\n";
            return nullptr;
        }

        return new History(customer);
    }

    // process borrow and return commands
    if (actionCode == 'B' || actionCode == 'R') {

        int customerID;
        char mediaType;
        char genreCode;

        if (!(ss >> customerID >> mediaType >> genreCode)) {
            std::cerr << "error: malformed transaction command\n";
            return nullptr;
        }

        Customer* customer = store.getCustomer(customerID);

        if (!customer) {
            std::cerr << "error: invalid customer\n";
            return nullptr;
        }

        if (mediaType != 'D') {
            std::cerr << "error: invalid media type\n";
            return nullptr;
        }

        Inventory* inv = store.getInventory();

        if (!inv) {
            std::cerr << "error: missing inventory\n";
            return nullptr;
        }

        Movie* movie = nullptr;

        // process comedy
        if (genreCode == 'F') {

            std::string title, yearStr;

            std::getline(ss >> std::ws, title, ',');
            std::getline(ss >> std::ws, yearStr);

            title = trimLeft(title);

            int year = 0;
            try {
                year = std::stoi(trimLeft(yearStr));
            } catch (...) {
                std::cerr << "error: invalid comedy year\n";
                return nullptr;
            }

            std::string key = "F|" + title + "|" + std::to_string(year);
            movie = inv->getMovieByKey(key);
        }

        // process drama
        else if (genreCode == 'D') {
            std::string director, title;

            std::getline(ss >> std::ws, director, ',');
            std::getline(ss >> std::ws, title, ',');

            director = trimLeft(director);
            title = trimLeft(title);

            std::string key = "D" + director + title; 

            movie = inv->getMovieByKey(key);
        }

        // process classic
        else if (genreCode == 'C') {

            std::string monthStr, yearStr;
            std::string firstName, lastName;

            ss >> monthStr >> yearStr >> firstName >> lastName;

            int month = 0;
            int year = 0;

            try {
                month = std::stoi(monthStr);
                year = std::stoi(yearStr);
            } catch (...) {
                std::cerr << "error: invalid classic date\n";
                return nullptr;
            }

            std::string actor = firstName + " " + lastName;

            std::string key = "C|" + std::to_string(month) + "|" +
                              std::to_string(year) + "|" + actor;

            movie = inv->getMovieByKey(key);
        }

        else {
            std::cerr << "error: invalid genre code\n";
            return nullptr;
        }

        if (!movie) {
            std::cerr << "error: movie not found\n";
            return nullptr;
        }

        // create transaction object
        if (actionCode == 'B') {
            return new Borrow(customer, movie);
        }

        return new Return(customer, movie);
    }

    // unknown command
    std::cerr << "error: unknown command\n";
    return nullptr;
}