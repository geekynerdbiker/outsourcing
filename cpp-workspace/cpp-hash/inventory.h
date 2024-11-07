/*
* inventory.h
* Written by : SENG1120 Staff (c1234567)
* Modified : 04/10/2024
*
* This class represents a simple inventory manager for books.
* This file should be used in conjunction with Assignment 3 for SENG1120.
*/

#ifndef SENG1120_INVENTORY_H
#define SENG1120_INVENTORY_H

#include <iostream>
#include <string>

#include "book.h"
#include "binary_search_tree.h"
#include "hash_table.h"
#include "book_genre_stats.h"

class inventory 
{
public:
    /*
    * Add a new book to the inventory.
    *
    * Precondition:    None
    * Postcondition:   Both the tree and hash table have been updated accordingly.
    */
    void add_book(const book& new_book);

    /*
    * Remove the information for the book with the supplied ISBN from the inventory.
    *
    * Precondition:    None
    * Postcondition:   Both the tree and hash table have been updated accordingly.
    */
    bool remove_book(const std::string& isbn);

    /*
    * Check if a book with the supplied ISBN exists.
    *
    * Precondition:    None
    * Postcondition:   Return true if the book is in the tree. Otherwise, return false.
    */
    bool book_exists(const std::string& isbn);

    /*
    * Get a pointer to the book with the supplied ISBN, or nullptr if it does not exist.
    *
    * Precondition:    None
    * Postcondition:   A pointer to the book with the supplied ISBN, if it exists. Otherwise, returns nullptr.
    */
    book* get_book(const std::string& isbn);

    /*
    * Display the books contained in the inventory. 
    * This should simply print the tree using its stream insertion operator.
    * 
    * Precondition:    None
    * Postcondition:   The books have been appended to the stream.
    */ 
    void display_books() const;

    /*
    * Clears both the tree and hash table.
    *
    * Precondition:    None
    * Postcondition:   All nodes from the tree, and entries from the hash table, are removed and any associated memory is reclaimed. Pointers are set to nullptr.
    */
    void clear();

    /*
    * Return a count of the number of books with the supplied genre.
    *
    * Precondition:    None
    * Postcondition:   The number of books with the supplied genre is returned.
    */
    int genre_count(const std::string& genre);

    /*
    * Return the average rating of books with the supplied genre.
    *
    * Precondition:    None
    * Postcondition:   The average rating of books with the supplied genre is returned.
    */
    double genre_average_rating(const std::string& genre);

    /*
    * Get a pointer to the stats object with the supplied genre, or nullptr if it does not exist.
    *
    * Precondition:    None
    * Postcondition:   A pointer to the stats object with the supplied genre, if it exists. Otherwise, returns nullptr.
    */
    book_genre_stats* get_stats(const std::string& genre);

    /*
    * Append both the tree and the hash table to the stream.
    * 
    * The expected format is given below.
    * 
    * Books: <tree>
    * 
    * Stats:
    * <hash table>
    * 
    * Precondition:    None
    * Postcondition:   The inventory has been appended to the stream.
    */ 
    void print(std::ostream& os) const;

private:
    binary_search_tree<book> bst;     // BST for books, ordered by ISBN
    hash_table<book_genre_stats> ht;  // Hash table for genre stats
};

/*
* Append both the tree and the table to the stream. 
* You are expected to use the print function. 
* See print for further details on the expected format.
*
* Precondition:    None
* Postcondition:   The inventory has been appended to the stream.
*/ 
std::ostream& operator<<(std::ostream& out, const inventory& inv);

#endif