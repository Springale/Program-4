/*
 * -----------------------------------------------------------------------------
 * File: Classic.h
 * Author: Lidia Workneh, Sam Pasarakonda
 * Course: CSS 343
 * Assignment: Program 4 - Movie Rental Store
 * Date: June 2026
 *
 * Description:
 * Defines the Classic class, a subclass of Movie.
 * Classics are identified by the genre code 'C' and are sorted by
 * release date (year then month), then major actor. Each actor/date
 * combination is stored as a separate entry with its own stock count.
 * -----------------------------------------------------------------------------
 */
 
#ifndef CLASSIC_H
#define CLASSIC_H

#include "Movie.h"

class Classic : public Movie {

private:
    std::string actor;
    int month;

public:

    Classic(
        int stock,
        std::string director,
        std::string title,
        int year,
        std::string actor,
        int month
    );

    void display() const override;

    std::string getKey() const override;

    bool operator<(
        const Movie& other
    ) const override;

    bool operator==(
        const Movie& other
    ) const override;

    char getType() const override;

    std::string getActor() const;
    int getMonth() const;
};

#endif