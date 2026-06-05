#include "Store.h"

#include "Comedy.h"
#include "Drama.h"
#include "Classic.h"

#include "Movie.h"
#include "Inventory.h"

void Store::loadMovies(const std::string& filename) {

    std::ifstream file(filename);

    if (!file) {

        std::cerr
            << "Error opening movie file: "
            << filename
            << std::endl;

        return;
    }

    char genre;

    while (file >> genre) {

        file.ignore(); // skip comma after genre

        if (genre == 'F') {

            int stock;
            int year;

            std::string director;
            std::string title;

            file >> stock;

            file.ignore();

            file >> std::ws;
            getline(file, director, ',');

            file >> std::ws;
            getline(file, title, ',');

            file >> year;

            Movie* movie =
                new Comedy(
                    stock,
                    director,
                    title,
                    year
                );

            inventory->addMovie(movie);
        }

        else if (genre == 'D') {

            int stock;
            int year;

            std::string director;
            std::string title;

            file >> stock;

            file.ignore();

            file >> std::ws;
            getline(file, director, ',');

            file >> std::ws;
            getline(file, title, ',');

            file >> year;

            Movie* movie =
                new Drama(
                    stock,
                    director,
                    title,
                    year
                );

            inventory->addMovie(movie);
        }

        else if (genre == 'C') {

            int stock;
            int month;
            int year;

            std::string director;
            std::string title;

            std::string first;
            std::string last;

            file >> stock;

            file.ignore();

            file >> std::ws;
            getline(file, director, ',');

            file >> std::ws;
            getline(file, title, ',');

            file >> first >> last;

            std::string actor =
                first + " " + last;

            file >> month >> year;

            Movie* movie =
                new Classic(
                    stock,
                    director,
                    title,
                    year,
                    actor,
                    month
                );

            inventory->addMovie(movie);
        }

        else {

            std::string badLine;

            getline(file, badLine);

            std::cerr
                << "Invalid movie type: "
                << genre
                << std::endl;
        }
    }
}