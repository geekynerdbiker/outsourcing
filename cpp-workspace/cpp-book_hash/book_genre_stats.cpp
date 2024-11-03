#include "book_genre_stats.h"

book_genre_stats::book_genre_stats()
    : genre(""), count(0), total_rating(0.0) {}

book_genre_stats::book_genre_stats(const std::string& genre)
    : genre(genre), count(0), total_rating(0.0) {}

const std::string& book_genre_stats::get_key() const {
    return genre;
}

int book_genre_stats::get_count() const {
    return count;
}

void book_genre_stats::increment_count() {
    count++;
}

void book_genre_stats::decrement_count() {
    if (count > 0) {
        count--;
    }
}

void book_genre_stats::add_rating(double rating) {
    total_rating += rating;
}

void book_genre_stats::subtract_rating(double rating) {
    total_rating -= rating;
}

double book_genre_stats::average_rating() const {
    if (count == 0) {
        return 0.0;
    }
    return total_rating / count;
}

std::ostream& operator<<(std::ostream& os, const book_genre_stats& s) {
    os << "(" << s.get_key() << ", " << s.get_count() << ", " << s.average_rating() << ")";
    return os;
}

bool operator==(const book_genre_stats& s1, const book_genre_stats& s2) {
    return s1.get_key() == s2.get_key();
}

bool operator<(const book_genre_stats& s1, const book_genre_stats& s2) {
    return s1.get_key() < s2.get_key();
}

bool operator>(const book_genre_stats& s1, const book_genre_stats& s2) {
    return s1.get_key() > s2.get_key();
}
