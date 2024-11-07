#include "inventory.h"

// Add a new book to the inventory
void inventory::add_book(const book& new_book) {
    // Insert book into the binary search tree
    bst.insert(new_book);

    // Update genre stats in the hash table
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

// Remove the information for the book with the supplied ISBN from the inventory
bool inventory::remove_book(const std::string& isbn) {
    book* book_to_remove = get_book(isbn);
    if (book_to_remove) {
        const std::string& genre = book_to_remove->get_genre();
        book_genre_stats* stats = ht.get(genre);
        if (stats) {
            stats->decrement_count();
            stats->subtract_rating(book_to_remove->get_rating());
        }
        bst.remove(*book_to_remove); // Assuming remove method is implemented in BST
        return true;
    }
    return false;
}

// Check if a book with the supplied ISBN exists
bool inventory::book_exists(const std::string& isbn) {
    return bst.contains(book(isbn, "", "", 0)); // Check for existence by ISBN
}

// Get a pointer to the book with the supplied ISBN
book* inventory::get_book(const std::string& isbn) {
    return bst.get(isbn); // Assuming get method is implemented in BST
}

// Display the books contained in the inventory
void inventory::display_books() const {
    std::cout << bst; // Use the overloaded << operator for the BST
}

// Clears both the tree and hash table
void inventory::clear() {
    bst.clear();
    ht.clear();
}

// Return a count of the number of books with the supplied genre
int inventory::genre_count(const std::string& genre) {
    book_genre_stats* stats = ht.get(genre);
    return stats ? stats->get_count() : 0;
}

// Return the average rating of books with the supplied genre
double inventory::genre_average_rating(const std::string& genre) {
    book_genre_stats* stats = ht.get(genre);
    return stats ? stats->average_rating() : 0.0;
}

// Get a pointer to the stats object with the supplied genre
book_genre_stats* inventory::get_stats(const std::string& genre) {
    return ht.get(genre);
}

// Append both the tree and the hash table to the stream
void inventory::print(std::ostream& os) const {
    os << "Books:\n" << bst << "\n\nStats:\n" << ht;
}

// Overloaded output operator for inventory
std::ostream& operator<<(std::ostream& out, const inventory& inv) {
    inv.print(out);
    return out;
}
