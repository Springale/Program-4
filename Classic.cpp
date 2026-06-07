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

void Classic::display() const {
    std::cout
        << stock << " "
        << month << " "
        << year << " "
        << actor << " "
        << title
        << std::endl;
}

std::string Classic::getKey() const {
    return "C|" + std::to_string(month) + "|" + std::to_string(year) + "|" + actor;
}

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

char Classic::getType() const {
    return 'C';
}

std::string Classic::getActor() const {
    return actor;
}

int Classic::getMonth() const {
    return month;
}
