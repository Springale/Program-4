/*
 * -----------------------------------------------------------------------------
 * File: Drama.h
 * Author: Lidia Workneh, Sam Pasarakonda
 * Course: CSS 343
 * Assignment: Program 4 - Movie Rental Store
 * Date: June 2026
 *
 * Description:
 * Defines the Drama class, a concrete subclass of Movie.
 * Dramas are identified by the genre code 'D' and are sorted
 * by director, then title.
 * -----------------------------------------------------------------------------
 */

#ifndef DRAMA_H
#define DRAMA_H

#include "Movie.h"

class Drama : public Movie {

public:

    Drama(
        int stock,
        string director,
        string title,
        int year
    );

    void display() const override;

    string getKey() const override;

    bool operator<(
        const Movie& other
    ) const override;

    bool operator==(
        const Movie& other
    ) const override;

    char getType() const override;

};

#endif