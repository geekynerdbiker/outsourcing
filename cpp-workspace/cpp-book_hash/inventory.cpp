#include "inventory.h"

inventory::inventory() : bst(), ht(101) {}
inventory::~inventory() {
    clear();
}

void inventory::add_book(const book& new_book) {
    bst.insert(new_book);

    const std::string& genre = new_book.get_genre();
    if (!ht.contains(genre)) {
        ht.insert(book_genre_stats(genre));
    }
    book_genre_stats* stats = ht.get(genre);
    if (stats) {
        stats->increment_count();
        stats->add_rating(new_book.get_rating());
    }
}

bool inventory::remove_book(const std::string& isbn) {
    book* book_to_remove = bst.find(isbn);

    if (book_to_remove) {
        const std::string& genre = book_to_remove->get_genre();
        book_genre_stats* stats = ht.get(genre);
        if (stats) {
            stats->decrement_count();
            stats->subtract_rating(book_to_remove->get_rating());
        }
        bst.remove(isbn);
        return true;
    }
    return false;
}

bool inventory::book_exists(const std::string& isbn) {
    return bst.contains(isbn);
}

book* inventory::get_book(const std::string& isbn) {
    return bst.find(isbn);
}

void inventory::display_books() const {
    std::cout << bst;
}

void inventory::clear() {
    bst.clear();
    ht.clear();
}

int inventory::genre_count(const std::string& genre) {
    book_genre_stats* stats = ht.get(genre);
    return stats ? stats->get_count() : 0;
}

double inventory::genre_average_rating(const std::string& genre) {
    book_genre_stats* stats = ht.get(genre);
    return stats ? stats->average_rating() : 0.0;
}

book_genre_stats* inventory::get_stats(const std::string& genre) {
    return ht.get(genre);
}

void inventory::print(std::ostream& os) const {
    os << "Books:\n" << bst << "\n\nStats:\n" << ht;
}

std::ostream& operator<<(std::ostream& out, const inventory& inv) {
    inv.print(out);
    return out;
}
