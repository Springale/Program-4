#include "MovieFactory.h"

#include "Movie.h"
#include "Comedy.h"
#include "Drama.h"
#include "Classic.h"

#include <sstream>
#include <iostream>

// helper: trim leading spaces
static std::string trimLeft(std::string s) {
    size_t start = s.find_first_not_of(" ");
    if (start == std::string::npos) return "";
    return s.substr(start);
}

// reads a single movie line and builds correct object
Movie* MovieFactory::createMovie(const std::string& line)
{
    if (line.empty()) return nullptr;

    std::stringstream ss(line);

    char genre;
    ss >> genre;

    ss.ignore(); // skip comma

    // comedy: F, stock, director, title, year
    if (genre == 'F')
    {
        int stock, year;
        std::string director, title;

        ss >> stock;
        ss.ignore();

        std::getline(ss >> std::ws, director, ',');
        std::getline(ss >> std::ws, title, ',');

        ss >> year;

        director = trimLeft(director);
        title = trimLeft(title);

        return new Comedy(stock, director, title, year);
    }

    // drama: D, stock, director, title, year
    else if (genre == 'D')
    {
        int stock, year;
        std::string director, title;

        ss >> stock;
        ss.ignore();

        std::getline(ss >> std::ws, director, ',');
        std::getline(ss >> std::ws, title, ',');

        ss >> year;

        director = trimLeft(director);
        title = trimLeft(title);

        return new Drama(stock, director, title, year);
    }

    // classic: C, stock, director, title, actor month year
    else if (genre == 'C')
    {
        int stock, month, year;
        std::string director, title;
        std::string first, last;

        ss >> stock;
        ss.ignore();

        std::getline(ss >> std::ws, director, ',');
        std::getline(ss >> std::ws, title, ',');

        ss >> first >> last >> month >> year;

        std::string actor = first + " " + last;

        return new Classic(stock, director, title, year, actor, month);
    }

    // invalid movie type
    else
    {
        std::cerr << "error: invalid movie genre '" << genre << "'\n";

        std::string skip;
        std::getline(ss, skip);

        return nullptr;
    }
}