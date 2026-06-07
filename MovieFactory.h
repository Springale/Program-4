/*
 * -----------------------------------------------------------------------------
 * File: MovieFactory.h
 * Author: Lidia Workneh, Sam Pasarakonda
 * Course: CSS 343
 * Assignment: Program 4 - Movie Rental Store
 * Date: May 2026
 *
 * Description:
 * Declares the MovieFactory class, which constructs the correct Movie
 * subclass (Comedy, Drama, or Classic) from a raw input line string.
 * Invalid genre codes are rejected with an error message.
 * -----------------------------------------------------------------------------
 */
 
#ifndef MOVIE_FACTORY_H
#define MOVIE_FACTORY_H

#include <string>

class Movie;

class MovieFactory {
public:
    // reads a movie line and returns correct movie object
    static Movie* createMovie(const std::string& line);
};

#endif