/*
 * -----------------------------------------------------------------------------
 * File: Classic.cpp
 * Author: Lidia Workneh, Sam Pasarakonda
 * Course: CSS 343
 * Assignment: Program 4 - Movie Rental Store
 * Date: June 2026
 *
 * Description:
 * Implements the Classic class. Classics are sorted by year, then month,
 * then major actor. Each actor/date combination is a separate entry with
 * its own stock. Lookup key is formatted as C|month|year|actor.
 * -----------------------------------------------------------------------------
 */

#include "Classic.h"
#include <iostream>

// ==========================================
// Constructor
// ==========================================
Classic::Classic(
    int stock, 
    std::string director,
    std::string title,
    int year,
    std::string actor,
    int month
)
: Movie(stock, director, title, year)  // Call base class constructor
{
    this->actor = actor;
    this->month = month;
}

// ==========================================
// Display - prints Classic movie information
// Format: stock month year actor title
// ==========================================
void Classic::display() const {
    std::cout
        << stock << " "
        << month << " "
        << year << " "
        << actor << " "
        << title
        << std::endl;
}

// ==========================================
// getKey - generates unique identifier for hash map lookup
// Format: C|month|year|actor
// 
// 
// - 'C' prefix prevents collisions with other genres
// - Pipes separate fields for easy parsing
// - Actor is last because it's the most specific discriminator
// ==========================================
std::string Classic::getKey() const {
    return "C|" + std::to_string(month) + "|" + std::to_string(year) + "|" + actor;
}

// ==========================================
// operator< - defines sorting order for Classics
// 
// Sorting priority (from highest to lowest):
// 1. Year (chronological)
// 2. Month (chronological within same year)
// 3. Actor name (alphabetical within same month/year)
// 
// This matches the assignment specification:
// "Classics are sorted by release date, then major actor"
// ==========================================
bool Classic::operator<(
    const Movie& other
) const {
    // Tries to cast to Classic - if it fails, cannot compare
    const Classic* c = dynamic_cast<const Classic*>(&other);
    if (!c) return false;

    // PRIMARY SORT: Compares by year first
    if (year != c->year) {
        return year < c->year;
    }

    // SECONDARY SORT: If same year, compares by month
    if (month != c->month) {
        return month < c->month;
    }

    // TERTIARY SORT: If same month/year, compares by actor name
    return actor < c->actor;
}

// ==========================================
// operator == - checks if two Classic movies are identical
// 
// All four fields must match because:
// - Different year/month = different release date = different movie
// - Different actor = different version (even with same title)
// - Different title = obviously different movie
// ==========================================
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

// ==========================================
// getType - returns genre code for Classic
// ==========================================
char Classic::getType() const {
    return 'C';
}

// ==========================================
// getActor - returns major actor name
// ==========================================
std::string Classic::getActor() const {
    return actor;
}

// ==========================================
// getMonth - returns release month (1-12)
// ==========================================
int Classic::getMonth() const {
    return month;
}
