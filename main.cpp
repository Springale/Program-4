/*
 * -----------------------------------------------------------------------------
 * File: main.cpp
 * Author: Lidia Workneh, Sam Pasarakonda
 * Course: CSS 343
 * Assignment: Program 4 - Movie Rental Store
 * Date: June 2026
 *
 * Description:
 * Test suite for the movie rental store system. Verifies movie key formats,
 * inventory add/lookup, Classic stock accumulation, customer tracking,
 * borrow/return transactions (including out-of-stock alternative suggestions),
 * history display order, TransactionFactory parsing, file loading, sorting
 * order, and full command processing integration.
 * -----------------------------------------------------------------------------
 */

#include "Store.h"
#include "Inventory.h"
#include "Customer.h"
#include "Movie.h"
#include "Comedy.h"
#include "Drama.h"
#include "Classic.h"
#include "Transaction.h"
#include "TransactionFactory.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// keep track of how many tests pass/fail
static int passed = 0, failed = 0;

// prints pass or fail and updates the counters
void check(bool ok, const string& name) {
    cout << (ok ? "  [PASS] " : "  [FAIL] ") << name << "\n";
    ok ? ++passed : ++failed;
}

// just prints a section header so the output is easier to read
void section(const string& name) {
    cout << "\n=== " << name << " ===\n";
}

// redirects cerr into a string buffer so we can check if an error was printed
struct CerrCapture {
    streambuf* orig;
    ostringstream buf;

    CerrCapture() {
        orig = cerr.rdbuf(buf.rdbuf());
    }

    ~CerrCapture() {
        cerr.rdbuf(orig);
    }

    bool hasOutput() const {
        return !buf.str().empty();
    }
};

// same idea but for cout - lets us inspect what got printed
struct CoutCapture {
    streambuf* orig;
    ostringstream buf;

    CoutCapture() {
        orig = cout.rdbuf(buf.rdbuf());
    }

    ~CoutCapture() {
        cout.rdbuf(orig);
    }

    string get() const {
        return buf.str();
    }
};

// -------------------------------------------------------
// TEST 1: Make sure each movie type generates the right key
// The key is how we look up movies in the inventory map,
// so if this is wrong everything else breaks
// -------------------------------------------------------
void testMovieKeys() {
    section("1. Movie Key Formats");

    // comedy key should be: F|title|year
    Comedy comedy(10, "Nora Ephron", "You've Got Mail", 1998);
    check(comedy.getKey() == "F|You've Got Mail|1998", "Comedy: F|title|year");

    // drama key should be: D + director + title (no separators)
    Drama drama(10, "Steven Spielberg", "Schindler's List", 1993);
    check(drama.getKey() == "DSteven SpielbergSchindler's List", "Drama: D+director+title");

    // classic key should be: C|month|year|actor
    Classic classic(10, "George Cukor", "Holiday", 1938, "Katherine Hepburn", 9);
    check(classic.getKey() == "C|9|1938|Katherine Hepburn", "Classic: C|month|year|actor");
}

// -------------------------------------------------------
// TEST 2: Add movies to inventory and look them up
// Also tests Classic stock merging - if you add the same
// movie/actor combo twice the stock should combine
// -------------------------------------------------------
void testInventory() {
    section("2. Inventory Add, Lookup & Classic Accumulation");

    Inventory inv;
    inv.addMovie(new Comedy(5, "D", "Test Comedy", 2000));
    inv.addMovie(new Drama(7, "Dir", "Test Drama", 1990));

    // add Holiday with two different actors - they should be stored separately
    inv.addMovie(new Classic(10, "G", "Holiday", 1938, "Katherine Hepburn", 9));
    inv.addMovie(new Classic(10, "G", "Holiday", 1938, "Cary Grant", 9));

    check(inv.getMovieByKey("F|Test Comedy|2000") != nullptr,         "Comedy found by key");
    check(inv.getMovieByKey("DDirTest Drama") != nullptr,             "Drama found by key");
    check(inv.getMovieByKey("C|9|1938|Katherine Hepburn") != nullptr, "Classic (Hepburn) found");
    check(inv.getMovieByKey("C|9|1938|Cary Grant") != nullptr,        "Classic (Grant) stored separately");
    check(inv.getMovieByKey("F|Bogus|9999") == nullptr,               "Fake key returns nullptr");

    // adding Hepburn again should merge the stock (10 + 5 = 15)
    inv.addMovie(new Classic(5, "G", "Holiday", 1938, "Katherine Hepburn", 9));
    Movie* hep = inv.getMovieByKey("C|9|1938|Katherine Hepburn");
    check(hep && hep->getStock() == 15, "Duplicate actor entry merges stock (10+5=15)");

    // Grant's stock should be untouched
    Movie* grant = inv.getMovieByKey("C|9|1938|Cary Grant");
    check(grant && grant->getStock() == 10, "Grant's stock unchanged after adding more Hepburn");
}

// -------------------------------------------------------
// TEST 3: Customer borrow/return tracking
// hasBorrowed, trackBorrow, trackReturn all need to work
// correctly or the return validation breaks
// -------------------------------------------------------
void testCustomerTracking() {
    section("3. Customer Tracking");

    Customer c(1234, "Jane", "Doe");
    check(c.getID() == 1234,         "Customer ID is correct");
    check(c.getName() == "Jane Doe", "Customer name is correct");

    const string key = "F|Fargo|1996";

    // shouldn't have anything borrowed yet
    check(!c.hasBorrowed(key), "hasBorrowed before any borrow = false");

    c.trackBorrow(key);
    check(c.hasBorrowed(key), "hasBorrowed after trackBorrow = true");

    // returning it should work and clear the active rental
    check(c.trackReturn(key),   "trackReturn after valid borrow returns true");
    check(!c.hasBorrowed(key), "hasBorrowed clears after return");

    // can't return something that was never borrowed
    check(!c.trackReturn("F|NeverRented|2000"), "trackReturn without borrow returns false");
}

// -------------------------------------------------------
// TEST 4: Borrow and Return transactions
// Tests the happy path, out-of-stock error, classic
// alternative suggestion, and returning without borrowing
// -------------------------------------------------------
void testTransactions() {
    section("4. Borrow & Return Transactions");

    // --- normal borrow should decrease stock and record the rental ---
    Customer* c1 = new Customer(1111, "A", "B");
    Movie* m1 = new Comedy(3, "D", "Title", 2000);
    Store s1;

    // heap allocated so c1 owns it after execute
    Borrow* b = new Borrow(c1, m1);
    b->execute(s1);

    check(m1->getStock() == 2,              "Borrow: stock goes from 3 to 2");
    check(c1->hasBorrowed("F|Title|2000"),  "Borrow: rental recorded for customer");

    delete c1;  // c1 destructor cleans up b through history
    delete m1;

    // --- borrowing when stock is 0 should print an error ---
    Customer c2(2222, "A", "B");
    Movie* m2 = new Comedy(0, "D", "Empty", 2000);
    Store s2;

    // stack-allocated borrow is fine here since execute returns early and never calls addHistory
    Borrow b2(&c2, m2);

    {
        CerrCapture cap;
        b2.execute(s2);
        check(cap.hasOutput(), "Borrow: error printed when out of stock");
    }

    check(m2->getStock() == 0, "Borrow: stock stays 0 after failed borrow");
    delete m2;

    // --- out-of-stock classic should suggest the other actor's version ---
    Store s_alt;
    s_alt.loadCustomers("data4customers.txt");
    s_alt.loadMovies("data4movies.txt");

    Movie* hepburn = s_alt.getInventory()->getMovieByKey("C|9|1938|Katherine Hepburn");

    // drain all 10 copies
    for (int i = 0; i < 10; i++) {
        hepburn->decreaseStock(1);
    }

    Customer* c_alt = s_alt.getCustomer(1000);

    // stack is fine since it'll return early
    Borrow b_alt(c_alt, hepburn);
    string altErr;

    {
        CerrCapture cap;
        b_alt.execute(s_alt);
        altErr = cap.buf.str();
    }

    check(!altErr.empty(),                           "Classic out of stock: error is printed");
    check(altErr.find("Cary Grant") != string::npos, "Classic out of stock: suggests Cary Grant version");

    // --- returning a movie should restore stock and clear the rental ---
    Customer* c3 = new Customer(3333, "A", "B");
    Movie* m3 = new Comedy(5, "D", "Film", 2000);
    Store s3;

    // borrow it first (stock = 4), c3 owns this Borrow
    (new Borrow(c3, m3))->execute(s3);

    // now return it (stock = 5), c3 owns this Return
    Return* ret = new Return(c3, m3);
    ret->execute(s3);

    check(m3->getStock() == 5,              "Return: stock goes back to 5");
    check(!c3->hasBorrowed("F|Film|2000"), "Return: active rental is cleared");

    delete c3;
    delete m3;

    // --- returning something you never borrowed should print an error ---
    Customer c4(4444, "A", "B");
    Movie* m4 = new Comedy(10, "D", "Unrented", 2000);
    Store s4;

    // stack is fine here since execute returns early
    Return ret2(&c4, m4);

    {
        CerrCapture cap;
        ret2.execute(s4);
        check(cap.hasOutput(), "Return: error when not borrowed");
    }

    check(m4->getStock() == 10, "Return: stock unchanged after invalid return");
    delete m4;
}

// -------------------------------------------------------
// TEST 5: Customer history shows newest transaction first
// We borrow then return, so the return should appear
// before the borrow when we display history
// -------------------------------------------------------
void testHistoryOrder() {
    section("5. History Display Order (newest first)");

    Customer* c = new Customer(9876, "H", "T");
    Movie* m = new Comedy(10, "D", "Film", 2001);
    Store store;

    // first transaction (oldest)
    (new Borrow(c, m))->execute(store);

    // second transaction (newest)
    (new Return(c, m))->execute(store);

    // capture the display output so we can check the order
    string out;

    {
        CoutCapture cap;
        c->displayHistory();
        out = cap.get();
    }

    size_t posRet = out.find("return transaction");
    size_t posBor = out.find("borrow transaction");

    check(posRet != string::npos && posBor != string::npos, "Both transactions show up in history");
    check(posRet < posBor, "Return (newest) appears before Borrow in output");

    delete c;
    delete m;
}

// -------------------------------------------------------
// TEST 6: TransactionFactory parses commands correctly
// Valid commands should create the right transaction type.
// Invalid commands should return nullptr and print an error.
// -------------------------------------------------------
void testFactory() {
    section("6. TransactionFactory");

    Store store;
    store.loadCustomers("data4customers.txt");
    store.loadMovies("data4movies.txt");

    // check that each valid command creates the right type
    Transaction* t1 = TransactionFactory::createTransaction("I", store);
    check(dynamic_cast<DisplayInventory*>(t1) != nullptr, "I creates DisplayInventory");
    delete t1;

    Transaction* t2 = TransactionFactory::createTransaction("H 1000", store);
    check(dynamic_cast<History*>(t2) != nullptr, "H 1000 creates History");
    delete t2;

    Transaction* t3 = TransactionFactory::createTransaction("B 1000 D F Annie Hall, 1977", store);
    check(dynamic_cast<Borrow*>(t3) != nullptr, "B comedy creates Borrow");
    delete t3;

    Transaction* t4 = TransactionFactory::createTransaction("B 1000 D D Barry Levinson, Good Morning Vietnam,", store);
    check(dynamic_cast<Borrow*>(t4) != nullptr, "B drama creates Borrow");
    delete t4;

    Transaction* t5 = TransactionFactory::createTransaction("B 1000 D C 9 1938 Katherine Hepburn", store);
    check(dynamic_cast<Borrow*>(t5) != nullptr, "B classic creates Borrow");
    delete t5;

    // helper lambda so we don't repeat this block for every invalid case
    auto checkInvalid = [&](const string& cmd, const string& label) {
        CerrCapture cap;
        Transaction* t = TransactionFactory::createTransaction(cmd, store);
        check(t == nullptr && cap.hasOutput(), label);
    };

    // all of these should fail with an error message
    checkInvalid("X",                              "Unknown action 'X' returns nullptr");
    checkInvalid("H 1234",                         "H with invalid customer returns nullptr");
    checkInvalid("B 1234 D F Annie Hall, 1977",    "B with invalid customer returns nullptr");
    checkInvalid("B 1000 Z F Annie Hall, 1977",    "B with bad media type returns nullptr");
    checkInvalid("B 1000 D Y Annie Hall, 1977",    "B with bad genre returns nullptr");
    checkInvalid("B 1000 D F Bogus Film, 2001",    "B with nonexistent movie returns nullptr");
}

// -------------------------------------------------------
// TEST 7: Load files and run the full command file
// Makes sure all customers/movies load correctly, the
// inventory is sorted right, and stock changes after commands
// -------------------------------------------------------
void testIntegration() {
    section("7. File Loading & Command Integration");

    Store store;
    store.loadCustomers("data4customers.txt");

    // the movie file has 'Z' entries that should be rejected
    {
        CerrCapture cap;
        store.loadMovies("data4movies.txt");
        check(cap.hasOutput(), "Invalid Z-genre entries print an error on load");
    }

    // spot-check that customers loaded correctly
    check(store.getCustomer(1000) != nullptr, "Customer 1000 (Minnie Mouse) loaded");
    check(store.getCustomer(5000) != nullptr, "Customer 5000 (Freddie Frog) loaded");
    check(store.getCustomer(1234) == nullptr, "Customer 1234 not in file returns nullptr");

    // spot-check that movies loaded correctly
    Inventory* inv = store.getInventory();
    check(inv->getMovieByKey("F|Annie Hall|1977")                  != nullptr, "Annie Hall loaded");
    check(inv->getMovieByKey("DSteven SpielbergSchindler's List")   != nullptr, "Schindler's List loaded");
    check(inv->getMovieByKey("C|9|1938|Katherine Hepburn")         != nullptr, "Holiday (Hepburn) loaded");
    check(inv->getMovieByKey("C|9|1938|Cary Grant")                != nullptr, "Holiday (Grant) loaded");

    // check sorting - comedies by title so Annie Hall (A) comes before Fargo (F)
    // and comedies section comes before dramas which comes before classics
    string out;

    {
        CoutCapture cap;
        inv->displayInventory();
        out = cap.get();
    }

    check(out.find("Annie Hall") < out.find("Fargo"),     "Comedies sorted: Annie Hall before Fargo");
    check(out.find("Annie Hall") < out.find("Schindler"), "Comedy section appears before Drama section");
    check(out.find("Schindler")  < out.find("Hepburn"),   "Drama section appears before Classics section");

    // run the command file and check that borrows actually changed stock
    Movie* annieHall = inv->getMovieByKey("F|Annie Hall|1977");
    int stockBefore = annieHall->getStock();

    {
        CoutCapture c;
        CerrCapture e;
        store.processCommands("data4commands.txt");
    }

    check(annieHall->getStock() < stockBefore, "Annie Hall stock decreased after borrow commands");

    // customer 1234 was never loaded so any command for them should have been rejected
    check(store.getCustomer(1234) == nullptr, "Invalid customer 1234 was never added");
}

// -------------------------------------------------------
int main() {
    cout << "=== CSS 343 Program 4 - Test Suite ===\n";

    testMovieKeys();
    testInventory();
    testCustomerTracking();
    testTransactions();
    testHistoryOrder();
    testFactory();
    testIntegration();

    cout << "\n=== RESULTS: " << passed << " passed, " << failed << " failed ===\n";
    return failed > 0 ? 1 : 0;
}
