/*
 * -----------------------------------------------------------------------------
 * File: Comedy.h
 * Author: Lidia Workneh, Sam Pasarakonda
 * Course: CSS 343
 * Assignment: Program 4 - Movie Rental Store
 * Date: June 2026
 *
 * Description:
 * Defines the Comedy class, a subclass of Movie.
 * Comedies are identified by the genre code 'F' (for "funny") and are
 * sorted by title, then release year.
 * 
 * Key format: F|title|year
 * Example: F|Annie Hall|1977
 * -----------------------------------------------------------------------------
 */
#ifndef COMEDY_H
#define COMEDY_H

#include "Movie.h"

class Comedy : public Movie {

public:
    Comedy(
        int stock,
        string director,
        string title,
        int year
    );

    void display() const override;
    string getKey() const override;
    bool operator<(const Movie& other) const override;
    bool operator==(const Movie& other) const override;
    char getType() const override;
};

#endif
