/*
* book_genre_stats.h
* Written by : SENG1120 Staff (c1234567)
* Modified : 04/10/2024
*
* This class represents a stats object for a book genre.
* This file should be used in conjunction with Assignment 3 for SENG1120.
*/

#ifndef SENG1120_BOOK_GENRE_STATS_H
#define SENG1120_BOOK_GENRE_STATS_H

#include <string>
#include <iostream>

class book_genre_stats
{
public:

	/*
    * Precondition:    None
    * Postcondition:   A stats object is created with an empty string for the genre, and 0 for the count and total power.
    */
    book_genre_stats();

	/*
    * Precondition:    None
    * Postcondition:   A stats is created with the supplied genre, and 0 for the count and total power.
    */
    book_genre_stats(const std::string& genre);

    /*
    * Return a const reference to the genre as the key.
    *
    * Precondition:    None
    * Postcondition:   A reference to the genre is returned.
    */
    const std::string& get_key() const;

    /*
    * Return a count of the number of books with this genre.
    *
    * Precondition:    None
    * Postcondition:   The number of books with this genre is returned.
    */
    int get_count() const;

    /*
    * Increment the count by 1.
    *
    * Precondition:    None
    * Postcondition:   The count is increased by 1.
    */
    void increment_count();
    
    /*
    * Decrement the count by 1.
    *
    * Precondition:    None
    * Postcondition:   The count is decreased by 1.
    */
    void decrement_count();

    /*
    * Add the supplied rating to the total cumulative rating.
    *
    * Precondition:    None
    * Postcondition:   The total cumultative rating is increased by the supplied amount.
    */
    void add_rating(double rating);
    
    /*
    * Subtract the supplied rating amount from the total cumulative rating.
    *
    * Precondition:    None
    * Postcondition:   The total cumultative rating is decreased by the supplied amount.
    */
    void subtract_rating(double rating);

    /*
    * Return the average rating of books with this type. 
    *
    * Precondition:    None
    * Postcondition:   The average rating of books with this type is returned.
    */
    double average_rating() const;

private:
    std::string genre;     // The genre
    int count;             // The number of books
    double total_rating;   // The cumulative total of ratings in this genre
};


/*
* The stats object is appended to the stream.
*
* The expected format is (<genre>, <count>, <average rating>), including the brackets.
*
* For example: (Young Adult, 26, 4.05)
*
* Precondition:    None
* Postcondition:   The stream is updated with the stats appended.
*/
std::ostream& operator << (std::ostream& os, const book_genre_stats& s);

/*
* Determine if two objects are equal. Two objects are considered equal if they have the same genre (key).
*
* Precondition:    None
* Postcondition:   Returns true if the objects have the same genre (key).
*/
bool operator == (const book_genre_stats& s1, const book_genre_stats& s2);

/*
* Determine if the first object is ordered before the second object, alphabetically by genre (key). 
*
* Precondition:    None
* Postcondition:   Returns true if the first object's key is less than the second object's.
*/
bool operator < (const book_genre_stats& s1, const book_genre_stats& s2);

/*
* Determine if the first object is after before the second object, alphabetically by genre (key). 
*
* Precondition:    None
* Postcondition:   Returns true if the first object's key is greater than the second object's.
*/
bool operator > (const book_genre_stats& s1, const book_genre_stats& s2);

#endif