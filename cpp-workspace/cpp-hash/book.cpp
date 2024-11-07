#include "book.h"

// Default constructor
book::book()
    : isbn(""), title(""), genre(""), rating(0.0) {}

// Constructor with parameters
book::book(const std::string& isbn, const std::string& title, const std::string& genre, double rating)
    : isbn(isbn), title(title), genre(genre), rating(rating) {}

// Get key (ISBN)
const std::string& book::get_key() const {
    return isbn;
}

// Get title
const std::string& book::get_title() const {
    return title;
}

// Get genre
const std::string& book::get_genre() const {
    return genre;
}

// Get rating
double book::get_rating() const {
    return rating;
}

// Overloaded equality operator
bool operator==(const book& b1, const book& b2) {
    return b1.get_key() == b2.get_key();
}

// Less than operator
bool operator<(const book& b1, const book& b2) {
    return b1.get_key() < b2.get_key();
}

// Greater than operator
bool operator>(const book& b1, const book& b2) {
    return b1.get_key() > b2.get_key();
}

// Overloaded output operator
std::ostream& operator<<(std::ostream& os, const book& b) {
    os << "(" << b.get_key() << ", " << b.get_title() << ", " << b.get_genre() << ", " << b.get_rating() << ")";
    return os;
}
