#include "Comedy.h"

#include <iostream>

using namespace std;

Comedy::Comedy(
    int stock,
    string director,
    string title,
    int year
)

: Movie(stock,director,title,year)
{}

void Comedy::display() const {

    cout
        << title
        << " "
        << year
        << " Stock:"
        << stock
        << endl;
}

string Comedy::getKey() const {

    return title
        + ","
        + to_string(year);
}

bool Comedy::operator<(const Movie& other) const {

    const Comedy& c =
        dynamic_cast<const Comedy&>(other);

    if(title != c.title)
        return title < c.title;

    return year < c.year;
}

bool Comedy::operator==(const Movie& other) const {

    const Comedy& c =
        dynamic_cast<const Comedy&>(other);

    return title == c.title &&
           year == c.year;
}