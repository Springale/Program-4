/*
 * -----------------------------------------------------------------------------
 * File: Movie.h
 * Author: Lidia Workneh, Sam Pasarakonda
 * Course: CSS 343
 * Assignment: Program 4 - Movie Rental Store
 * Date: May 2026
 *
 * Description:
 * Defines the abstract Movie base class used in the movie rental system.
 * Movie stores data and behavior common to all movie types, including
 * stock, director, title, and release year. Specific movie genres
 * (Comedy, Drama, and Classic) inherit from this class and implement
 * genre-specific functionality.
 * -----------------------------------------------------------------------------
 */

#ifndef MOVIE_H
#define MOVIE_H

#include <string>
using namespace std;

class Movie {
protected:
    int stock;          // Number of copies currently available
    string director;    // Director of the movie
    string title;       // Movie title
    int year;           // Release year

public:
    Movie(int stock, string director, string title, int year);
    virtual ~Movie();

    // Accessor methods
    int getStock() const;
    string getDirector() const;
    string getTitle() const;
    int getYear() const;
    
    virtual char getType() const = 0;

    // Displays movie information
    virtual void display() const = 0;
    // Returns unique key used for movie lookup
    virtual string getKey() const = 0;

    // Stock management
bool borrow();

void returnMovie();

void increaseStock(int amount);

void decreaseStock(int amount);

// Comparison operators for sorting
virtual bool operator<(const Movie& other) const = 0;

virtual bool operator==(const Movie& other) const = 0;
};

#endif