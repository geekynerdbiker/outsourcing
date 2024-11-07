#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include "inventory.h"
#include "book.h"

/**
 * Tokenise a string,separating by commas ",".
 */ 
std::vector<std::string> tokenise(const std::string& line)
{
	std::vector<std::string> tokens;

    std::istringstream iss(line);
    std::string token;

    while (std::getline(iss, token, ',')) 
    {
        tokens.push_back(token);
    }

    return tokens;
}

/**
 * Populates the creature tracker with the entries from the text file named "creatures.txt"
 */ 
void populate_inventory(inventory& inv)
{
	std::ifstream infile("books.csv");
	std::string line;

	while(std::getline(infile, line))
    {
        //remove the newline character(s) from the line
        line.erase(std::remove(line.begin(), line.end(), '\n'), line.cend());
		line.erase(std::remove(line.begin(), line.end(), '\r'), line.cend());
        
        std::vector<std::string> tokens = tokenise(line);
		if (tokens.size() != 4)
		{
			throw std::runtime_error("Error when reading the book file.");
		} 

		//line format is isbn, title, genre, rating
		std::string isbn = tokens[0];
		std::string title = tokens[1];
        std::string genre = tokens[2];
		double rating = std::stod(tokens[3]); //convert 4th token to double

        book new_book(isbn, title, genre, rating);
		inv.add_book(new_book);
    }
}

int main()
{
    inventory inv;
    populate_inventory(inv);

    //manipulate std::cout to print booleans as true/false, instead of 1/0.
	std::cout << std::boolalpha; 

    //check book that exists
	std::cout << "Calling book_exists on book that exists: " << inv.book_exists("9780142001745") << std::endl << std::endl;

	//check book that does not exist
	std::cout << "Calling book_exists on book that doesn't exist: " << inv.book_exists("1234567891011") << std::endl << std::endl;

    book* b = inv.get_book("9780142001745");
	std::cout << "Retrieving and printing a book: " << *b << std::endl << std::endl;

    std::vector<std::string> genres = {"Young Adult", "Fantasy", "Historical Fiction", "Classics", "Childrens", "Fiction", 
                                       "Science Fiction", "Horror", "Nonfiction", "Mystery", "Picture Books", "Graphic Novels", 
                                       "Plays", "Poetry", "Romance", "History", "Comics", "Travel", "Philosophy"};

	//loop through each genre and print statistics
	std::cout << "Printing statistics for each type:" << std::endl;
	for(std::string& genre : genres)
	{
		std::cout << "\t" << *inv.get_stats(genre) << std::endl;
	}
	std::cout << std::endl;

    //remove book that exists
	inv.remove_book("9780142001745");
	std::cout << "Checking removed book no longer exists: " << inv.book_exists("9780142001745") << std::endl << std::endl;

	//printing inventory - this will display a lot of output!
	std::cout << "Printing inventory" << std::endl;
	std::cout << inv << std::endl;

    //clear all data
	inv.clear();
}