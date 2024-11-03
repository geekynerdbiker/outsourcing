#include "book.h"

book::book()
    : isbn(""), title(""), genre(""), rating(0.0) {}

book::book(const std::string& isbn, const std::string& title, const std::string& genre, double rating)
    : isbn(isbn), title(title), genre(genre), rating(rating) {}

const std::string& book::get_key() const {
    return isbn;
}

const std::string& book::get_title() const {
    return title;
}

const std::string& book::get_genre() const {
    return genre;
}

double book::get_rating() const {
    return rating;
}

bool operator==(const book& b1, const book& b2) {
    return b1.get_key() == b2.get_key();
}

bool operator<(const book& b1, const book& b2) {
    return b1.get_key() < b2.get_key();
}

bool operator>(const book& b1, const book& b2) {
    return b1.get_key() > b2.get_key();
}

std::ostream& operator<<(std::ostream& os, const book& b) {
    os << "(" << b.get_key() << ", " << b.get_title() << ", " << b.get_genre() << ", " << b.get_rating() << ")";
    return os;
}
