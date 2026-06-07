/*
 * -----------------------------------------------------------------------------
 * File: Inventory.h
 * Author: Lidia Workneh, Sam Pasarakonda
 * Course: CSS 343
 * Assignment: Program 4 - Movie Rental Store
 * Date: June 2026
 *
 * Description:
 * Defines the Inventory class, which stores and manages all movies in the
 * rental system. Movies are kept in sorted genre vectors (comedies, dramas,
 * classics) and in a hash map for O(1) key-based lookup. Supports adding
 * movies, retrieving by key, finding Classic alternatives, and displaying
 * the full inventory in sorted order.
 * -----------------------------------------------------------------------------
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <string>
#include <unordered_map>
#include "Movie.h"

class Inventory {
private:
    std::vector<Movie*> comedies;
    std::vector<Movie*> dramas;
    std::vector<Movie*> classics;

    // FAST LOOKUP (replaces HashTable)
    std::unordered_map<std::string, Movie*> movieMap;

public:
    Inventory();
    ~Inventory();

    void addMovie(Movie* movie);

    Movie* getMovieByKey(const std::string& key) const;

    void displayInventory() const;

    // Returns in-stock classics with the same title but a different key
    std::vector<Movie*> getClassicAlternatives(const std::string& title,
                                               const std::string& excludeKey) const;

private:
    void insertSorted(std::vector<Movie*>& list, Movie* movie);
};

#endif