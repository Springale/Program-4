#include "Store.h"

int main() {
    std::cout << "starting program..." << std::endl;
    Store store;

    store.loadCustomers("data4customers.txt");
    store.loadMovies("data4movies.txt");
    store.processCommands("data4commands.txt");

    std::cout << "program finished successfully." << std::endl;

    return 0;
}