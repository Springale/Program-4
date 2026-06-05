#include "Drama.h"

#include <iostream>

Drama::Drama(
    int stock,
    std::string director,
    std::string title,
    int year
)

: Movie(
    stock,
    director,
    title,
    year
)

{}

void Drama::display() const {

    std::cout
        << stock
        << " "
        << director
        << " "
        << title
        << " "
        << year
        << std::endl;

}

std::string Drama::getKey() const {

    return "D" + director + title;

}

bool Drama::operator<(
    const Movie& other
) const {

    const Drama& d =
        static_cast<const Drama&>(other);

    if(director != d.director){

        return director < d.director;

    }

    return title < d.title;

}

bool Drama::operator==(
    const Movie& other
) const {

    const Drama& d =
        static_cast<const Drama&>(other);

    return director == d.director
        && title == d.title;

}