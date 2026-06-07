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
 * 
 * Hash function details:
 * - Polynomial rolling hash with base 31 (common prime for strings)
 * - 31 is used in Java's String.hashCode() for good distribution
 * - TABLE_SIZE is 101 (prime number reduces collisions)
 * 
 * Collision handling:
 * - Separate chaining with std::list
 * - Each bucket contains a linked list of key-value pairs
 * - Simple and effective for small to medium-sized tables
 * -----------------------------------------------------------------------------
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <string>
#include <functional>

template <typename V>
class HashTable {
private:
    static const int TABLE_SIZE = 101;  // Prime number for better distribution

    // Each bucket is a list of (key, value) pairs
    std::vector<std::list<std::pair<std::string, V>>> table;

    /*
     * Hash function using polynomial rolling hash with base 31.
     * 
     * Why 31? 
     * - 31 is an odd prime (reduces collisions)
     * - Multiplication by 31 can be optimized by compilers (31 = 32 - 1)
     * - Used in Java's String.hashCode() for proven performance
     * 
     * Algorithm:
     * hash = 0
     * for each character c in key:
     *     hash = hash * 31 + c
     * return hash % TABLE_SIZE
     */
    int hash(const std::string& key) const {
        unsigned long hash = 0;
        for (char c : key) {
            hash = hash * 31 + c;
        }
        return hash % TABLE_SIZE;
    }

public:
    // Constructor - creates empty table with TABLE_SIZE buckets
    HashTable() : table(TABLE_SIZE) {}

    /*
     * insert - adds or updates a key-value pair in the hash table
     * 
     * If key exists: updates existing value
     * If key doesn't exist: adds new pair to the bucket's list
     * 
     * Time complexity: O(1) average, O(n) worst case (all keys in same bucket)
     */
    void insert(const std::string& key, V value) {
        int idx = hash(key);

        // Check if key already exists in this bucket
        for (auto& pair : table[idx]) {
            if (pair.first == key) {
                pair.second = value;  // Update existing value
                return;
            }
        }

        // Key not found - add new pair to the bucket
        table[idx].push_back({key, value});
    }

    /*
     * find - retrieves value associated with key
     * 
     * Returns value if found, nullptr (for pointer types) if not found
     * 
     * Note: This design assumes V is a pointer type (Customer*, Movie*)
     * For non-pointer types, would need a different not-found indicator
     * 
     * Time complexity: O(1) average, O(n) worst case
     */
    V find(const std::string& key) const {
        int idx = hash(key);

        // Search for key in the bucket's list
        for (const auto& pair : table[idx]) {
            if (pair.first == key) {
                return pair.second;  // Found - return value
            }
        }

        return nullptr;  // Not found - return null pointer
    }

    /*
     * remove - deletes key-value pair from hash table
     * 
     * Uses remove_if to delete any pair matching the key
     * If key doesn't exist, does nothing (no error)
     * 
     * Time complexity: O(1) average, O(n) worst case
     */
    void remove(const std::string& key) {
        int idx = hash(key);

        // Remove all pairs with matching key (should be at most one)
        table[idx].remove_if([&](auto& p) {
            return p.first == key;
        });
    }

    /*
     * deleteAllValues - deletes all stored pointer values and clears the table
     * 
     * IMPORTANT: This should ONLY be called when V is a pointer type.
     * Used by Store destructor to clean up Customer objects.
     * 
     * Time complexity: O(n) where n is total number of entries
     */
    void deleteAllValues() {
        for (auto& bucket : table) {
            for (auto& pair : bucket) {
                delete pair.second;  // Delete the stored pointer
            }
            bucket.clear();  // Clear the bucket
        }
    }
};

#endif
