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
 * 
 * Key format: C|month|year|actor
 * Example: C|9|1938|Katherine Hepburn
 * -----------------------------------------------------------------------------
 */
 
#ifndef CLASSIC_H
#define CLASSIC_H

#include "Movie.h"

class Classic : public Movie {

private:
    std::string actor;  // Major actor for this specific Classic version
    int month;          // Release month (1-12) - used for sorting

public:
    /*
     * Constructor for Classic movies
     * @param stock - number of copies available
     * @param director - film director
     * @param title - movie title
     * @param year - release year
     * @param actor - major actor in this version
     * @param month - release month (1-12)
     */
    Classic(
        int stock,
        std::string director,
        std::string title,
        int year,
        std::string actor,
        int month
    );

    // Displays Classic movie info: stock, month, year, actor, title
    void display() const override;

    // Returns unique key: "C|month|year|actor"
    std::string getKey() const override;

    /*
     * Comparison operator for sorting Classics
     * Sorts by: year -> month -> actor (lexicographically)
     * This matches the assignment specification exactly
     */
    bool operator<(
        const Movie& other
    ) const override;

    // Equality check: compares year, month, actor, AND title
    bool operator==(
        const Movie& other
    ) const override;

    // Returns genre code 'C'
    char getType() const override;

    // Getters for Classic-specific fields
    std::string getActor() const;
    int getMonth() const;
};

#endif
