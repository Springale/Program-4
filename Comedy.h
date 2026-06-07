/*
 * -----------------------------------------------------------------------------
 * File: Comedy.h
 * Author: Lidia Workneh, Sam Pasarakonda
 * Course: CSS 343
 * Assignment: Program 4 - Movie Rental Store
 * Date: May 2026
 *
 * Description:
 * Defines the Comedy class, a subclass of Movie.
 * Comedies are identified by the genre code 'F' (funny) and are
 * sorted by title, then release year.
 * -----------------------------------------------------------------------------
 */
#ifndef COMEDY_H
#define COMEDY_H

#include "Movie.h"

class Comedy : public Movie {

public:
    /*
     * Constructor for Comedy movies
     * @param stock - number of copies available
     * @param director - film director
     * @param title - movie title (used as primary sort key)
     * @param year - release year (used as secondary sort key)
     */
    Comedy(
        int stock,
        string director,
        string title,
        int year
    );

    // Displays Comedy movie info: title, year, stock
    void display() const override;

    // Returns unique key: "F|title|year"
    string getKey() const override;

    /*
     * Comparison operator for sorting Comedies
     * Sorts by: title (alphabetical) -> year (chronological)
     */
    bool operator<(const Movie& other) const override;

    // Equality check: compares title AND year (director not needed)
    bool operator==(const Movie& other) const override;

    // Returns genre code 'F'
    char getType() const override;
};

#endif
