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