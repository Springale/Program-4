#include "TransactionFactory.h"
#include "Transaction.h"
#include "Store.h"
#include "Customer.h"
#include "Movie.h"
#include "Inventory.h"
#include <sstream>
#include <iostream>

Transaction* TransactionFactory::createTransaction(const std::string &line, Store &store) {
    if (line.empty()) return nullptr;

    std::stringstream ss(line);
    char actionCode;
    ss >> actionCode;

    // process inventory display command ('i')
    if (actionCode == 'I') {
        return new DisplayInventory();
    }

    // process history command ('h')
    if (actionCode == 'H') {
        int customerID;

        if (!(ss >> customerID)) {
            std::cerr << "command error: malformed customer id in history command." << std::endl;
            return nullptr;
        }

        Customer* customer = store.getCustomer(customerID);
        if (customer == nullptr) {
            std::cerr << "command error: customer id " << customerID << " not found for history command." << std::endl;
            return nullptr;
        }

        return new History(customer);
    }

    // process borrow ('b') and return ('r') commands
    if (actionCode == 'B' || actionCode == 'R') {
        int customerID;
        char mediaType;
        char genreCode;

        if (!(ss >> customerID >> mediaType >> genreCode)) {
            std::cerr << "command error: malformed transaction parameters: " << line << std::endl;
            return nullptr;
        }

        // validate customer exists
        Customer* customer = store.getCustomer(customerID);
        if (customer == nullptr) {
            std::cerr << "command error: customer id " << customerID << " not found." << std::endl;
            return nullptr;
        }

        // validate media type
        if (mediaType != 'D') {
            std::cerr << "command error: invalid media type '" << mediaType << "'." << std::endl;
            return nullptr;
        }

        std::string movieKey = "";

        // generate lookup key based on genre
        if (genreCode == 'C') {         // comedy: title, year
            std::string remaining;

            // TODO: verify movie key formatting matches MovieFactory exactly
// getline() may include leading spaces, which can cause key mismatches
// with Inventory::getMovieByKey(), leading to failed lookups.
            std::getline(ss, remaining);
            movieKey = "C" + remaining;
        }
        else if (genreCode == 'D') {    // drama: director, title
            std::string remaining;
            std::getline(ss, remaining);
            movieKey = "D" + remaining;
        }
        else if (genreCode == 'F') {    // classic: month, year, actor
            std::string remaining;
            std::getline(ss, remaining);
            movieKey = "F" + remaining;
        }
        else {
            std::cerr << "command error: invalid genre code '" << genreCode << "'." << std::endl;
            return nullptr;
        }

        // find movie in inventory
        Movie* movie = store.getInventory()->getMovieByKey(movieKey);
        if (movie == nullptr) {
            std::cerr << "command error: movie not found in inventory: " << movieKey << std::endl;
            return nullptr;
        }

        // create transaction object
        if (actionCode == 'B') {
            return new Borrow(customer, movie);
        } else {
            return new Return(customer, movie);
        }
    }

    // unknown command
    std::cerr << "command error: unrecognized action code '" << actionCode << "'." << std::endl;
    return nullptr;
}