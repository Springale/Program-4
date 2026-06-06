#include "Store.h"
#include "Inventory.h"
#include "Customer.h"
#include "Movie.h"
#include "Transaction.h"
#include "TransactionFactory.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;

// helper: section divider
void section(const std::string& name) {
    std::cout << "\n====================================\n";
    std::cout << name << "\n";
    std::cout << "====================================\n";
}

int main() {
    Store store;

    // loading data
    store.loadCustomers("data4customers.txt");
    store.loadMovies("data4movies.txt");

    // ---------------------------
    section("1. Inventory + sorting check");
    Inventory* inv = store.getInventory();
    inv->displayInventory(); // visual check

    // ---------------------------
    section("2. Command processing");
    store.processCommands("data4commands.txt");

    // ---------------------------
    // section("3. Stock verification");
    // auto checkStock = [&](string key, int expected) {
    //     Movie* m = inv->getMovieByKey(key);
    //     assert(m != nullptr);

    //     cout << key << " -> Stock: " << m->getStock() << endl;
    //     assert(m->getStock() >= 0);
    // };

    // // stock checks
    // checkStock("F|Annie Hall|1977", 9);
    // checkStock("F|Fargo|1996", 9);
    // checkStock("F|You've Got Mail|1998", 9);

    // checkStock("D|Barry Levinson|Good Morning Vietnam", 9);
    // checkStock("D|Gus Van Sant|Good Will Hunting", 9);

    // checkStock("C|3|1971|Ruth Gordon", 0);
    // checkStock("C|2|1971|Malcolm McDowell", 9);


    // // ---------------------------
    // section("4. Customer history check");

    // Customer* c5000 = store.getCustomer(5000);
    // assert(c5000 != nullptr);

    // const vector<Transaction*>& history = c5000->getHistory();

    // // expected pattern
    // vector<string> expected = {
    //     "Borrow",
    //     "Return",
    //     "Borrow",
    //     "Return",
    //     "Borrow",
    //     "Return",
    //     "Borrow"
    // };

    // assert(history.size() == expected.size());

    // for (size_t i = 0; i < history.size(); i++) {

    //     if (expected[i] == "Borrow") {
    //         assert(dynamic_cast<Borrow*>(history[i]) != nullptr);
    //     }
    //     else if (expected[i] == "Return") {
    //         assert(dynamic_cast<Return*>(history[i]) != nullptr);
    //     }
    // }

    // cout << "Customer 5000 history VERIFIED\n";

    // section("4. FINAL INVENTORY STATE (CHECK STOCK CHANGES)");

    // store.getInventory()->displayInventory();

    // section("5. CUSTOMER HISTORY CHECKS");

    // int testCustomers[] = {1000, 1111, 5000, 8000, 8888};

    // for (int id : testCustomers) {
    //     std::cout << "\n--- history for customer " << id << " ---\n";
    //     Customer* c = store.getCustomer(id);
    //     if (c) {
    //         c->displayHistory();
    //     } else {
    //         std::cout << "invalid customer\n";
    //     }
    // }

    // section("6. MANUAL EDGE CASE TESTS");

    // // invalid customer
    // std::cout << "\n[invalid customer lookup]\n";
    // Customer* bad = store.getCustomer(1234);
    // if (!bad) std::cout << "pass: invalid customer handled\n";

    // // invalid movie lookup
    // std::cout << "\n[invalid movie lookup]\n";
    // Movie* m = store.getInventory()->getMovieByKey("F|Fake Movie|9999");
    // if (!m) std::cout << "pass: invalid movie handled\n";

    // section("7. COMPLEX SCENARIO TESTS (BORROW/RETURN STRESS)");

    // // simulate repeated borrow/return stress
    // Transaction* t1 = TransactionFactory::createTransaction(
    //     "B 1000 D F Annie Hall, 1977", store);

    // if (t1) {
    //     t1->execute(store);
    //     delete t1;
    // }

    // Transaction* t2 = TransactionFactory::createTransaction(
    //     "R 1000 D F Annie Hall, 1977", store);

    // if (t2) {
    //     t2->execute(store);
    //     delete t2;
    // }

    // section("8. INVENTORY FINAL VALIDATION");

    // store.getInventory()->displayInventory();

    // section("9. MEMORY / CRASH SAFETY CHECK");

    // for (int i = 1000; i < 1010; i++) {
    //     Customer* c = store.getCustomer(i);
    //     if (c) {
    //         std::cout << "customer " << i << " exists\n";
    //     }
    // }

    // section("TEST COMPLETE");

    return 0;
}