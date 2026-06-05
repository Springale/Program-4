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

};

#endif