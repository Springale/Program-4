#include "Inventory.h"
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

    // 🔥 CHECK DUPLICATE
    auto it = movieMap.find(key);

    if (it != movieMap.end()) {

        // movie already exists → increase stock only
        it->second->increaseStock(movie->getStock());

        delete movie;
        return;
    }

    // insert into hash map
    movieMap[key] = movie;

    // insert into correct genre list
    if (key[0] == 'F') {
        insertSorted(comedies, movie);
    }
    else if (key[0] == 'D') {
        insertSorted(dramas, movie);
    }
    else if (key[0] == 'C') {
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

void Inventory::displayInventory() const {

    std::cout << "\n=== COMEDIES ===\n";
    for (Movie* m : comedies) {
        m->display();
    }

    std::cout << "\n=== DRAMAS ===\n";
    for (Movie* m : dramas) {
        m->display();
    }

    std::cout << "\n=== CLASSICS ===\n";
    for (Movie* m : classics) {
        m->display();
    }
}