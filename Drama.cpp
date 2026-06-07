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
 * 
 * Key implementation details:
 * - Director is the primary sort key (alphabetical by last name)
 * - Title is secondary (alphabetical within same director)
 * - Year is NOT used for sorting (only for display)
 * - No separators in key because director+title combination is unique
 * -----------------------------------------------------------------------------
 */

#include "Drama.h"
#include <iostream>

// ==========================================
// Constructor - passes all parameters to Movie base class
// ==========================================
Drama::Drama(
    int stock,
    std::string director,
    std::string title,
    int year
)
: Movie(stock, director, title, year)  // Base class handles stock/director/title/year
{}

// ==========================================
// display - prints Drama movie information
// Format: stock director title year
// ==========================================
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

// ==========================================
// getKey - generates unique identifier for hash map lookup
// Format: D + director + title (no separators)
// 
// ==========================================
std::string Drama::getKey() const {
    return "D" + director + title;
}

// ==========================================
// operator< - defines sorting order for Dramas
// 
// Sorting priority:
// 1. Director name (alphabetical - A comes before B)
// 2. Title (alphabetical within same director)
// 
// ==========================================
bool Drama::operator<(
    const Movie& other
) const {
    // Try to cast to Drama - if fails, we can't compare
    const Drama* d = dynamic_cast<const Drama*>(&other);
    if (!d) {
        return false;  // Can't compare Drama with non-Drama
    }

    // PRIMARY SORT: Compare by director first
    if (director != d->director) {
        return director < d->director;
    }

    // SECONDARY SORT: If directors are equal, compare by title
    return title < d->title;
}

// ==========================================
// operator== - checks if two Drama movies are identical
// 
// Both director and title must match because:
// - Same director, different title = different movie
// - Different director, same title = different movie (remake)
// - Year is NOT required for equality (a film could have multiple releases)
// ==========================================
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

// ==========================================
// getType - returns genre code for Drama
// ==========================================
char Drama::getType() const {
    return 'D';
}
```
