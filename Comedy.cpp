/*
 * -----------------------------------------------------------------------------
 * File: Comedy.cpp
 * Author: Lidia Workneh, Sam Pasarakonda
 * Course: CSS 343
 * Assignment: Program 4 - Movie Rental Store
 * Date: June 2026
 *
 * Description:
 * Implements the Comedy class. Comedies are sorted by title then year,
 * and their lookup key is formatted as F|title|year.
 * -----------------------------------------------------------------------------
 */
 
#include "Comedy.h"

#include <iostream>

using namespace std;

Comedy::Comedy(
    int stock,
    string director,
    string title,
    int year
)

: Movie(stock,director,title,year)
{}

void Comedy::display() const {

    cout
        << title
        << " "
        << year
        << " Stock:"
        << stock
        << endl;
}

string Comedy::getKey() const {
    return "F|" + title + "|" + to_string(year);
}

bool Comedy::operator<(const Movie& other) const {

    const Comedy* c =
        dynamic_cast<const Comedy*>(&other);
        
    if (!c) {
        return false;
    }

    if(title != c->title)
        return title < c->title;

    return year < c->year;
}

bool Comedy::operator==(const Movie& other) const {

    const Comedy* c =
        dynamic_cast<const Comedy*>(&other);

    if (!c) { 
        return false; 
    }

    return title == c->title &&
           year == c->year;
}

char Comedy::getType() const {
    return 'F';
}