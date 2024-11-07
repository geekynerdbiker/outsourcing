/**
* bs_tree.h
* Written by : SENG1120 Staff (c1234567)
* Modified : 24/05/2024
*/

#ifndef SENG1120_BST_H
#define SENG1120_BST_H

#include <iostream>

/**
 * This class represents a templated binary search tree.
 * The implementation assumes that T has a method with signature std::string get_key() and has comparison operators defined.
 * The implementation uses an internal binary_node class.
 */
template<typename T>
class binary_search_tree
{
    /**
     * A private, internal struct for the node in a binary search tree.
     */ 
    struct binary_node
    {
        T data;
        binary_node* left;
        binary_node* right;

        binary_node(const T& item = T())
        {
            data = item;
            left = nullptr;
            right = nullptr;
        }

        ~binary_node()
        {
            left = nullptr;
            right = nullptr;
        }
    };

public:
    /**
    * Precondition: None.
    * Postcondition: A new tree is created, with variables initialised as appropriate.
    */
    binary_search_tree();

    /**
    * Precondition: None.
    * Postcondition: The tree is destroyed and all associated memory is freed.
    */
    ~binary_search_tree();

    /**
    * The supplied item is inserted into the binary search tree. If the item already exists, its data its updated.
    *
    * Precondition: None.
    * Postcondition: The data is inserted into the tree, or updated if it already existed.
    * If an item was added, the count is increased by 1.
    */
    void insert(const T& item);

    /**
    * Remove the item with the specified key from the tree, if it exists.
    *
    * Precondition: None
    * Postcondition: The item with the specified key has been removed, if it exists. Otherwise, nothing happens.
    * The count is reduced by 1 if an item is removed.
    */
    void remove(const std::string& key);

    /**
    * Returns true if an item with the specified key exists within the tree. Otherwise, returns false.
    *
    * Precondition: None.
    * Postcondition: The tree has not been modified.
    */
    bool contains(const std::string& key) const;

    /**
    * Return a pointer to the item with the specified key, if it exists. If no such item exists, nullptr is returned.
    *
    * Precondition: None.
    * Postcondition: The tree has not been modified.
    */
    T* find(const std::string& key) const;

    /**
    * Return a reference to the item with the minimum value. If the tree is empty, an exception is thrown.
    *
    * Precondition: None.
    * Postcondition: The tree has not been modified.
    */
    T& find_min() const;

    /**
    * Return a reference to the item with the maximum value. If the tree is empty, an is thrown.
    *
    * Precondition: None
    * Postcondition: The tree has not been modified.
    */
    T& find_max() const;

    /**
    * Clears all items from the tree.
    *
    * Precondition: None.
    * Postcondition: All nodes from the tree are removed and any associated memory is reclaimed.
    */
    void clear();

    /**
    * Return the number of items in the tree.
    *
    * Precondition: None.
    * Postcondition: The tree has not been modified.
    */
    int size() const;

    /**
    * Return true if the tree is emtpy, false otherwise.
    *
    * Precondition: None.
    * Postcondition: The tree has not been modified.
    */
    bool empty() const;

    /**
    * Append the value of each node in the tree to the supplied stream using an inorder traversal. Each element should be separated by a space.
    *
    * Precondition: None.
    * Postcondition: The tree has not been modified.
    */
    void print_inorder(std::ostream& out) const;

    /**
    * Append the value of each node in the tree to the supplied stream using a preorder traversal. Each element should be separated by a space.
    *
    * Precondition: None.
    * Postcondition: The tree has not been modified.
    */
    void print_preorder(std::ostream& out) const;

    /**
    * Append the value of each node in the tree to the supplied stream using a postorder traversal. Each element should be separated by a space.
    *
    * Precondition: None.
    * Postcondition: The tree has not been modified.
    */
    void print_postorder(std::ostream& out) const;

private:
    binary_node* root;
    int count;

    /**
    * The supplied item is inserted into the sub-tree rooted at the supplied node. A pointer to the node is returned.
    *
    * Precondition: None
    * Postcondition: The data is inserted into the correct location in the tree. The count is increased by 1.
    */
    void insert(const T& item, binary_node*& node);

    /**
    * Remove the item with the specified key from the sub-tree rooted at the supplied node, if it exists. A pointer to the node is returned.
    * 
    * Precondition: None
    * Postcondition: The item with the specified key has been removed, if it exists. The count is reduced by 1 if an item is removed.
    */
    void remove(const std::string& key, binary_node*& node);

    /**
    * Determine if an item with the specified key exists in the sub-tree rooted at the supplied node.
    *
    * Precondition: None.
    * Postcondition: The tree has not been modified.
    */
    bool contains(const std::string& key, binary_node* node) const;

    /**
    * Return a pointer to the node containing the item with the specified key, if it exists, in the sub-tree rooted at the supplied node.
    * If no such item exists, nullptr is returned.
    *
    * Precondition: None.
    * Postcondition: The tree has not been modified.
    */
    binary_node* find(const std::string& key, binary_node* node) const;

    /**
    * Return a pointer to the node containing the item with the minimum data value in the sub-tree rooted at the supplied node.
    *
    * Precondition: None.
    * Postcondition: The tree has not been modified.
    */
    binary_node* find_min(binary_node* node) const;

    /**
    * Return a pointer to the node containing the item with the maximum data value in the sub-tree rooted at the supplied node.
    *
    * Precondition: None.
    * Postcondition: The tree has not been modified.
    */
    binary_node* find_max(binary_node* node) const;

    /**
    * Clears all nodes from the sub-tree rooted at the supplied node.
    *
    * Precondition: None
    * Postcondition: All nodes from the sub-tree are removed and any associated memory is reclaimed.
    */
    void clear(binary_node*& node);

    /**
    * Append the value of each node in the sub-tree rooted at the supplied node, to the supplied stream, using an inorder traversal.
    * Each element should be separated by a space.
    *
    * Precondition: None.
    * Postcondition: The tree has not been modified.
    */
    void print_inorder(std::ostream& out, binary_node* node) const;

    /**
    * Append the value of each node in the sub-tree rooted at the supplied node, to the supplied stream, using a preorder traversal.
    * Each element should be separated by a space.
    *
    * Precondition: None.
    * Postcondition: The tree has not been modified.
    */
    void print_preorder(std::ostream& out, binary_node* node) const;

    /**
    * Append the value of each node in the sub-tree rooted at the supplied node, to the supplied stream, using a postorder traversal.
    * Each element should be separated by a space.
    *
    * Precondition: None.
    * Postcondition: The tree has not been modified.
    */
    void print_postorder(std::ostream& out, binary_node* node) const;

};

template<typename T>
std::ostream& operator <<(std::ostream& out, const typename binary_search_tree<T>::binary_node& node)
{
    out << node.data;
    return out;
}

/**
* Append the value of each node in the tree to the supplied stream.
* The tree should be printed according to an inorder traversal.
*
* Precondition: None
* Postcondition: The stream is updated with the data values from the tree appended.
*/
template <typename T>
std::ostream& operator <<(std::ostream& out, const binary_search_tree<T>& tree);

#include "binary_search_tree.hpp"

#endif
