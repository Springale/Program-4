// ------------------------------------------------ Store.cpp ----------------------------------------------
//
// Programmer: Lidia Workneh, Sam Pasarakonda
// Course: CSS 343
// Date: June 2026
//
// ---------------------------------------------------------------------------------------------------------
// Purpose:
// Implements the Store class. Responsible for loading customer and movie
// data, processing transaction commands, and coordinating interactions
// between customers, inventory, and transactions.
//
// ---------------------------------------------------------------------------------------------------------
// Notes:
// - Uses MovieFactory to construct movie objects dynamically.
// - Uses TransactionFactory to construct transaction objects dynamically.
// - Inventory and customer records are allocated dynamically and released
//   by the Store destructor.
// - Error messages are displayed for invalid files and invalid commands.
// ---------------------------------------------------------------------------------------------------------

#include "Store.h"

#include "Comedy.h"
#include "Drama.h"
#include "Classic.h"

#include "Movie.h"
#include "Transaction.h"
#include "MovieFactory.h"
#include "TransactionFactory.h"
#include "Customer.h"
#include "Inventory.h"
#include "HashTable.h"

#include <fstream>
#include <iostream>

// constructor
Store::Store()
    : inventory(new Inventory()),
      customerTable(new HashTable<Customer*>()) {}

// destructor
Store::~Store() {
    delete inventory;
    delete customerTable;
}

// reads customer information from a file and stores customers in the hash table
void Store::loadCustomers(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file)
    {
        std::cerr << "error opening customer file: " << filename << std::endl;
        return;
    }

    int id;
    std::string lastName, firstName;

    while (file >> id >> lastName >> firstName)
    {
        Customer* newCustomer = new Customer(id, firstName, lastName);

        std::string key = std::to_string(id);
        customerTable->insert(key, newCustomer);
    }
}

// load movies into inventory
void Store::loadMovies(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file)
    {
        std::cerr << "error opening movie file: " << filename << std::endl;
        return;
    }

    char genre;

    while (file >> genre)
    {
        file.ignore(); // skip comma or space

        if (genre == 'F')
        {
            int stock, year;
            std::string director, title;

            file >> stock;
            file.ignore();

            getline(file >> std::ws, director, ',');
            getline(file >> std::ws, title, ',');

            file >> year;

            Movie* movie = new Comedy(stock, director, title, year);
            inventory->addMovie(movie);
        }
        else if (genre == 'D')
        {
            int stock, year;
            std::string director, title;

            file >> stock;
            file.ignore();

            getline(file >> std::ws, director, ',');
            getline(file >> std::ws, title, ',');

            file >> year;

            Movie* movie = new Drama(stock, director, title, year);
            inventory->addMovie(movie);
        }
        else if (genre == 'C')
        {
            int stock, month, year;
            std::string director, title;
            std::string first, last;

            file >> stock;
            file.ignore();

            getline(file >> std::ws, director, ',');
            getline(file >> std::ws, title, ',');

            file >> first >> last;
            std::string actor = first + " " + last;

            file >> month >> year;

            Movie* movie = new Classic(stock, director, title, year, actor, month);
            inventory->addMovie(movie);
        }
        else
        {
            std::string badLine;
            getline(file, badLine);

            std::cerr << "invalid movie type: " << genre << std::endl;
        }
    }
}

// process commands from data4commands.txt
void Store::processCommands(const std::string &filename)
{
    std::ifstream infile(filename);

    if (!infile)
    {
        std::cerr << "error: could not open commands file: " << filename << std::endl;
        return;
    }

    std::string line;

    while (std::getline(infile, line))
    {
        if (line.empty()) continue;

        // create transaction using factory
        Transaction* trans = TransactionFactory::createTransaction(line, *this);

        if (trans != nullptr)
        {
            bool ownedByCustomer = trans->execute(*this);
            if (!ownedByCustomer)
            {
                delete trans;
            }
        }
    }
}

// retrieve a customer from the hash table
Customer* Store::getCustomer(int id) const
{
    return customerTable->find(std::to_string(id));
}

// access inventory
Inventory* Store::getInventory() const
{
    return inventory;
}