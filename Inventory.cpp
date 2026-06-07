/*
 * -----------------------------------------------------------------------------
 * File: Inventory.cpp
 * Author: Lidia Workneh, Sam Pasarakonda
 * Course: CSS 343
 * Assignment: Program 4 - Movie Rental Store
 * Date: May 2026
 *
 * Description:
 * Implements the Inventory class. Movies are inserted in sorted order into
 * genre-specific vectors and indexed by key in a hash map for O(1) lookup.
 * Duplicate Classic entries with the same key merge their stock counts.
 * -----------------------------------------------------------------------------
 */

#include "Inventory.h"
#include "Classic.h"
#include <iostream>

// constructor
Inventory::Inventory() {}

// destructor
Inventory::~Inventory() {

    for (Movie* m : comedies) delete m;
    for (Movie* m : dramas) delete m;
    for (Movie* m : classics) delete m;
}

void Inventory::insertSorted(std::vector<Movie*>& list, Movie* movie) {

    auto it = list.begin();

    while (it != list.end() && **it < *movie) {
        ++it;
    }

    list.insert(it, movie);
}

void Inventory::addMovie(Movie* movie) {

    if (!movie) return;

    std::string key = movie->getKey();

    // check duplicate
    auto it = movieMap.find(key);

    if (it != movieMap.end()) {

        // if movie already exists, increase stock only
        it->second->increaseStock(movie->getStock());

        delete movie;
        return;
    }

    // insert into hash map
    movieMap[key] = movie;
    char type = movie->getType();

    if (type == 'F') {
        insertSorted(comedies, movie);
    }
    else if (type == 'D') {
        insertSorted(dramas, movie);
    }
    else if (type == 'C') {
        insertSorted(classics, movie);
    }
}

Movie* Inventory::getMovieByKey(const std::string& key) const {

    auto it = movieMap.find(key);

    if (it == movieMap.end()) {
        return nullptr;
    }

    return it->second;
}

std::vector<Movie*> Inventory::getClassicAlternatives(const std::string& title,
                                                       const std::string& excludeKey) const {
    std::vector<Movie*> results;
    for (Movie* m : classics) {
        if (m->getTitle() == title && m->getKey() != excludeKey && m->getStock() > 0) {
            results.push_back(m);
        }
    }
    return results;
}

void Inventory::displayInventory() const {

    std::cout << "\n=== COMEDIES ===\n";
    for (Movie* m : comedies) {
        if (m) {
            m->display();
        }
    }

    std::cout << "\n=== DRAMAS ===\n";
    for (Movie* m : dramas) {
        if (m) {
            m->display();
        }
    }

    std::cout << "\n=== CLASSICS ===\n";
    for (Movie* m : classics) {
        if (m) {
            m->display();
        }
    }
}