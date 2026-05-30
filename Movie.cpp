#include "Movie.h"

Movie::Movie(int stock, string director, string title, int year)
    : stock(stock), director(director), title(title), year(year) {}

Movie::~Movie() {}

int Movie::getStock() const {
    return stock;
}

string Movie::getDirector() const {
    return director;
}

string Movie::getTitle() const {
    return title;
}

int Movie::getYear() const {
    return year;
}