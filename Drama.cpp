/*
 * -----------------------------------------------------------------------------
 * File: Drama.cpp
 * Author: Lidia Workneh, Sam Pasarakonda
 * Course: CSS 343
 * Assignment: Program 4 - Movie Rental Store
 * Date: June 2026
 *
 * Description:
 * Implements the Drama class. Dramas are sorted by director then title,
 * and their lookup key is formatted as D + director + title.
 * -----------------------------------------------------------------------------
 */

#include "Drama.h"

#include <iostream>

Drama::Drama(
    int stock,
    std::string director,
    std::string title,
    int year
)

: Movie(
    stock,
    director,
    title,
    year
)

{}

void Drama::display() const {

    std::cout
        << stock
        << " "
        << director
        << " "
        << title
        << " "
        << year
        << std::endl;

}

std::string Drama::getKey() const {

    return "D" + director + title;

}

bool Drama::operator<(
    const Movie& other
) const {

    const Drama* d = dynamic_cast<const Drama*>(&other);

    if (!d) {
        return false;
    }

    if(director != d->director){

        return director < d->director;

    }

    return title < d->title;

}

bool Drama::operator==(
    const Movie& other
) const {

    const Drama* d = dynamic_cast<const Drama*>(&other);
        
    if (!d) {
        return false;
    }

    return director == d->director
        && title == d->title;

}

char Drama::getType() const {
    return 'D';
}