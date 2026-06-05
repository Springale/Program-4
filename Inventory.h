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

private:
    void insertSorted(std::vector<Movie*>& list, Movie* movie);
};

#endif