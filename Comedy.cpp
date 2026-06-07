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

// ==========================================
// Constructor -  passes all parameters to Movie base class
// ==========================================
Comedy::Comedy(
    int stock,
    string director,
    string title,
    int year
)
: Movie(stock, director, title, year)  // Base class handles stock/director/title/year
{}

// ==========================================
// display - prints Comedy movie information
// Format: title year Stock:stock
// ==========================================
void Comedy::display() const {
    cout
        << title
        << " "
        << year
        << " Stock:"
        << stock
        << endl;
}

// ==========================================
// getKey - generates unique identifier for hash map lookup
// Format: F|title|year
// 
// ==========================================
string Comedy::getKey() const {
    return "F|" + title + "|" + to_string(year);
}

// ==========================================
// operator< - defines sorting order for Comedies
// 
// Sorting priority:
// 1. Title (alphabetical order - A comes before B)
// 2. Year (chronological - older comes before newer within same title)
// 
// ==========================================
bool Comedy::operator<(const Movie& other) const {
    const Comedy* c = dynamic_cast<const Comedy*>(&other);
    if (!c) {
        return false;  // Can't compare Comedy with non-Comedy
    }

    // PRIMARY SORT: Compare by title first
    if (title != c->title) {
        return title < c->title;
    }

    // SECONDARY SORT: If titles are equal, compare by year
    return year < c->year;
}

// ==========================================
// operator== - checks if two Comedy movies are identical
// 
// ==========================================
bool Comedy::operator==(const Movie& other) const {
    const Comedy* c = dynamic_cast<const Comedy*>(&other);
    if (!c) { 
        return false; 
    }

    return title == c->title &&
           year == c->year;
}

// ==========================================
// getType - returns genre code for Comedy ('F' for "funny")
// ==========================================
char Comedy::getType() const {
    return 'F';
}

char Comedy::getType() const {
    return 'F';
}
