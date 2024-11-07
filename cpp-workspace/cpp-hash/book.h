/*
* book.h
* Written by : SENG1120 Staff (c1234567)
* Modified : 04/10/2024
*
* This class represents a book.
* This file should be used in conjunction with Assignment 3 for SENG1120.
*/
#ifndef SENG1120_BOOK_H
#define SENG1120_BOOK_H

#include <string>
#include <iostream>

class book 
{
public:
	/*
    * Precondition:    None
    * Postcondition:   A book object is created with an empty strings and 0 for the rating.
    */
    book();

	/*
    * Precondition:    None
    * Postcondition:   A book object is created with the supplied values.
    */
    book(const std::string& isbn, const std::string& title, const std::string& genre, double rating);

    /*
    * Return a const reference to the ISBN, as the key of the object.
    *
    * Precondition:    None
    * Postcondition:   A const reference to the ISBN is returned.
    */
    const std::string& get_key() const;

    /*
    * Return a const reference to the title
    *
    * Precondition:    None
    * Postcondition:   A const reference to the title is returned.
    */
    const std::string& get_title() const;

    /*
    * Return a const reference to the genre
    *
    * Precondition:    None
    * Postcondition:   A const reference to the genre is returned.
    */
    const std::string& get_genre() const;

    /*
    * Return the rating of the book.
    *
    * Precondition:    None
    * Postcondition:   The rating is returned.
    */
    double get_rating() const;

private:
    std::string isbn;   // the 13-digit ISBN, which is a unique identifier.
    std::string title;  // the title of the book
    std::string genre;  // the primary genre of the book
    double rating;      // the book's rating
};

/*
* Determine if two books are equal. Two objects are considered equal if they have the same ISBN (key).
*
* Precondition:    None
* Postcondition:   Returns true if the objects have the same ISBN (key).
*/
bool operator ==(const book& b1, const book& b2);

/*
* Determine if the first book is ordered before the second book, alphabetically by ISBN (key). 
*
* Precondition:    None
* Postcondition:   Returns true if the first book's key is less than the second book's.
*/
bool operator <(const book& b1, const book& b2);

/*
* Determine if the first book is ordered after the second book, alphabetically by ISBN (key). 
*
* Precondition:    None
* Postcondition:   Returns true if the first book's key is greater than the second book's.
*/
bool operator >(const book& b1, const book& b2);


/*
* The book object is appended to the stream.
*
* The expected format is (<ISBN>, <title>, <genre>, <rating>), including the brackets.
*
* For example: (9780001000391, The Prophet, Poetry, 4.22)
*
* Precondition:    None
* Postcondition:   The stream is updated with the stats appended.
*/
std::ostream& operator <<(std::ostream& os, const book& b);

#endif