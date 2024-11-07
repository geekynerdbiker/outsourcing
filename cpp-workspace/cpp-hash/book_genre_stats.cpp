#include "book_genre_stats.h"

// Default constructor
book_genre_stats::book_genre_stats()
    : genre(""), count(0), total_rating(0.0) {}

// Constructor with genre parameter
book_genre_stats::book_genre_stats(const std::string& genre)
    : genre(genre), count(0), total_rating(0.0) {}

// Get key (genre)
const std::string& book_genre_stats::get_key() const {
    return genre;
}

// Get count of books
int book_genre_stats::get_count() const {
    return count;
}

// Increment count
void book_genre_stats::increment_count() {
    count++;
}

// Decrement count
void book_genre_stats::decrement_count() {
    if (count > 0) {
        count--;
    }
}

// Add rating
void book_genre_stats::add_rating(double rating) {
    total_rating += rating;
}

// Subtract rating
void book_genre_stats::subtract_rating(double rating) {
    total_rating -= rating;
}

// Calculate average rating
double book_genre_stats::average_rating() const {
    if (count == 0) {
        return 0.0; // Prevent division by zero
    }
    return total_rating / count;
}

// Overloaded output operator
std::ostream& operator<<(std::ostream& os, const book_genre_stats& s) {
    os << "(" << s.get_key() << ", " << s.get_count() << ", " << s.average_rating() << ")";
    return os;
}

// Equality operator
bool operator==(const book_genre_stats& s1, const book_genre_stats& s2) {
    return s1.get_key() == s2.get_key();
}

// Less than operator
bool operator<(const book_genre_stats& s1, const book_genre_stats& s2) {
    return s1.get_key() < s2.get_key();
}

// Greater than operator
bool operator>(const book_genre_stats& s1, const book_genre_stats& s2) {
    return s1.get_key() > s2.get_key();
}
