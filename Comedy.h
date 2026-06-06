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