/*
 * -----------------------------------------------------------------------------
 * File: Classic.cpp
 * Author: Lidia Workneh, Sam Pasarakonda
 * Course: CSS 343
 * Assignment: Program 4 - Movie Rental Store
 * Date: June 2026
 *
 * Description:
 * Implements the Classic class. Classics sorted by year -> month -> actor.
 * Each actor/date combo has separate stock. Key: C|month|year|actor.
 * -----------------------------------------------------------------------------
 */

#include "Classic.h"
#include <iostream>

// Constructor - calls Movie base class, sets actor and month
Classic::Classic(
    int stock, 
    std::string director,
    std::string title,
    int year,
    std::string actor,
    int month
)
: Movie(stock, director, title, year)
{
    this->actor = actor;
    this->month = month;
}

// Display format: stock month year actor title
void Classic::display() const {
    std::cout
        << stock << " "
        << month << " "
        << year << " "
        << actor << " "
        << title
        << std::endl;
}

// Unique key for hash map lookup: C|month|year|actor
std::string Classic::getKey() const {
    return "C|" + std::to_string(month) + "|" + std::to_string(year) + "|" + actor;
}

// Sort by: year, then month, then actor (alphabetical)
bool Classic::operator<(
    const Movie& other
) const {
    const Classic* c = dynamic_cast<const Classic*>(&other);
    if (!c) return false;

    if (year != c->year) {
        return year < c->year;
    }

    if (month != c->month) {
        return month < c->month;
    }

    return actor < c->actor;
}

// Equality requires year, month, actor, AND title all match
bool Classic::operator==(
    const Movie& other
) const {
    const Classic* c = dynamic_cast<const Classic*>(&other);
    if (!c) return false;

    return year == c->year
        && month == c->month
        && actor == c->actor
        && title == c->title;
}

// Genre code 'C'
char Classic::getType() const {
    return 'C';
}

// Getter for actor name
std::string Classic::getActor() const {
    return actor;
}

// Getter for release month
int Classic::getMonth() const {
    return month;
}
