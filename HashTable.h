/*
 * -----------------------------------------------------------------------------
 * File: HashTable.h
 * Author: Lidia Workneh, Sam Pasarakonda
 * Course: CSS 343
 * Assignment: Program 4 - Movie Rental Store
 * Date: June 2026
 *
 * Description:
 * Defines a generic hash table template class that maps string keys to
 * values of type V. Uses chaining (linked lists) to handle collisions.
 * Provides O(1) average-case insert, find, and remove operations.
 * Used by Store to look up customers by ID in constant time.
 * -----------------------------------------------------------------------------
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <string>

template <typename V>
class HashTable {
private:
    static const int TABLE_SIZE = 101; // prime number is common

    std::vector<std::list<std::pair<std::string, V>>> table;

    int hash(const std::string& key) const {
        unsigned long hash = 0;
        for (char c : key) {
            hash = hash * 31 + c;
        }
        return hash % TABLE_SIZE;
    }

public:
    HashTable() : table(TABLE_SIZE) {}

    // V must be a pointer type — deletes every stored value.
    ~HashTable() {
        for (auto& bucket : table) {
            for (auto& pair : bucket) {
                delete pair.second;
            }
        }
    }

    void insert(const std::string& key, V value) {
        int idx = hash(key);

        for (auto& pair : table[idx]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }

        table[idx].push_back({key, value});
    }

    V find(const std::string& key) const {
        int idx = hash(key);

        for (auto& pair : table[idx]) {
            if (pair.first == key) {
                return pair.second;
            }
        }

        return nullptr; // works for pointer types
    }

    void remove(const std::string& key) {
        int idx = hash(key);

        table[idx].remove_if([&](auto& p) {
            return p.first == key;
        });
    }
};

#endif