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

};

#endif