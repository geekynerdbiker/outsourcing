#include <iostream>
#include <vector>

using namespace std;

struct Node {
    string title;
    string author;
    int copies;
    int pub_year;

    Node* left;
    Node* right;

    Node(string _title, string _author, int _copies, int _pub_year)
    : title(_title), author(_author), copies(_copies), pub_year(_pub_year), left(NULL), right(NULL) {
        if (copies < 0 || pub_year < 0) {
            cout << "Data Validation Error!" << endl;
            throw ;
        }
    }
};

class Dictionary {
private:
    Node* _root;
    Node* search(Node* tree, string target);
    void insert(Node* tree, Node* node);
    Node* searchMin(Node* tree);
    Node* remove(Node* tree, Node* parent, string target);
    void preorder(Node* tree);
    void inorder(Node* tree);
    void postorder(Node* tree);

public:
    Dictionary() { _root = NULL; }
    ~Dictionary() {}

    Node* search(string target) { return search(_root, target); }
    void insert(Node* data) { insert(_root, data); }
    Node* remove(string target) { return remove(_root, NULL, target); }
    void preorder() { return inorder(_root); }
    void inorder() { return inorder(_root); }
    void postorder() { return inorder(_root); }
};

Node* Dictionary::search(Node* tree, string target) {
    if (tree == NULL)
        return NULL;

    if (tree->title == target)
        return tree;
    else if (tree->title > target)
        return search(tree->left, target);
    else
        return search(tree->right, target);
}

void Dictionary::insert(Node* tree, Node* node) {
    if (tree == NULL) {
        _root = node;
        return;
    }

    if (search(node->title) == NULL)
        return;

    if (node->title < tree->title) {
        if (tree->left == NULL) {
            tree->left = node;
            return;
        }
        else
            insert(tree->left, node);
    }
    else if (node->title > tree->title) {
        if (tree->right == NULL) {
            tree->right = node;
            return;
        }
        else
            insert(tree->right, node);
    }
}

Node* Dictionary::searchMin(Node* tree) {
    if (tree == NULL)
        return NULL;

    if (tree->left == NULL)
        return tree;
    else
        return searchMin(tree->left);
}

Node* Dictionary::remove(Node* tree, Node* parent, string target) {
     if (tree == NULL)
        return NULL;

    Node* removed = NULL;

    if (tree->title > target)
        removed = remove(tree->left, tree, target);
    else if (tree->title < target)
        removed = remove(tree->right, tree, target);
    else if (tree->title == target) {
        removed = tree;

        if (tree->left == NULL && tree->right == NULL) {
            if (parent != NULL && parent->left == tree)
                parent->left = NULL;
            if (parent != NULL && parent->right == tree)
                parent->right = NULL;
        } else if (tree->left == NULL || tree->right == NULL) {
            Node* temp = NULL;
            if (tree->left != NULL)
                temp = tree->left;
            else
                temp = tree->right;

            if (parent != NULL && parent->left == tree)
                parent->left = temp;
            else if (parent != NULL && parent->right == tree)
                parent->right = temp;
        } else if (tree->left != NULL && tree->right != NULL) {
            Node* min = searchMin(tree->right);
            min = remove(tree, NULL, min->title);
            tree->title = min->title;
        }
    }

    return removed;
}

void Dictionary::preorder(Node* tree) {
    if (tree == NULL)
        return;

    cout << tree->title << ": " << tree->author << endl;
    inorder(tree->left);
    inorder(tree->right);
}

void Dictionary::inorder(Node* tree) {
    if (tree == NULL)
        return;

    inorder(tree->left);
    cout << tree->title << ": " << tree->author << endl;
    inorder(tree->right);
}
void Dictionary::postorder(Node* tree) {
    if (tree == NULL)
        return;

    inorder(tree->left);
    inorder(tree->right);
    cout << tree->title << ": " << tree->author << endl;
}

int main(int argc, const char * argv[]) {
    Dictionary dic;

    while (true) {
        cout << "1. Insert\n2. Search\n3. Delete\n4. Print\n5. Exit Program\n\nInput command: " ;
        int command, option;
        cin >> command;

        Node* n;

        string title;
        string author;
        int copies;
        int pub_year;

        switch (command) {
            case 1:
                cout << "Input title: ";
                cin >> title;
                cout << "Input author name: ";
                cin >> author;
                cout << "Input number of copies: ";
                cin >> copies;
                cout << "Input publication year: ";
                cin >> pub_year;

                n = new Node(title, author, copies, pub_year);
                dic.insert(n);
                break;

            case 2:
                cout << "Input title: ";
                cin >> title;

                n = NULL;
                n = dic.search(title);

                if (n != NULL)
                    cout << n->title << " by " << n->author << "\ncopies: " << n->copies << "\npublished at " << n->pub_year << "\n\n" << endl;
                else
                    cout << "No book exist." << endl;
                break;
            case 3:
                cout << "Input title: ";
                cin >> title;

                n = NULL;
                n = dic.remove(title);

                if (n != NULL)
                    cout << n->title << " is deleted." << endl;
                else
                    cout << "No book exist." << endl;
                break;
            case 4:
                cout << "\n1. Pre-Order\n2. In-Order\n3. Post-Order\nInput Option: ";
                cin >> option;

                switch (option) {
                    case 1:
                        dic.preorder();
                        break;

                    case 2:
                        dic.inorder();
                        break;

                    case 3:
                        dic.postorder();
                        break;

                    default:
                        break;
                }

                break;

            case 5:
                return 0;

            default:
                break;
        }
    }

    return 0;
}
