#include <iostream>
#include <utility>

using namespace std;

template<typename T1, typename T2>
class BinarySearchTree {
private:
    struct Node {
        pair<T1, T2> data;
        int leftSize;
        Node* left;
        Node* right;

        Node(const pair<T1, T2>& data) : data(data), leftSize(0), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insert(Node*& node, const pair<T1, T2>& data) {
        if (node == nullptr) {
            node = new Node(data);
            cout << "Node " << data.first << " (" << data.second << ") inserted." << endl;
        }
        else if (data.first < node->data.first) {
            insert(node->left, data);
            node->leftSize++;
        }
        else {
            insert(node->right, data);
        }
    }

    Node* findMin(Node* node) const {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    void remove(Node*& node, const T1& key) {
        if (node == nullptr) {
            return;
        }

        if (key < node->data.first) {
            remove(node->left, key);
            node->leftSize--;
        }
        else if (key > node->data.first) {
            remove(node->right, key);
        }
        else {
            if (node->left != nullptr && node->right != nullptr) {
                Node* minRight = findMin(node->right);
                node->data = minRight->data;
                remove(node->right, minRight->data.first);
            }
            else {
                Node* oldNode = node;
                node = (node->left != nullptr) ? node->left : node->right;
                cout << "Node " << oldNode->data.first << " (" << oldNode->data.second << ") removed." << endl;
                delete oldNode;
            }
        }
    }

    Node* get(Node* node, const T1& key) const {
        if (node == nullptr) {
            return nullptr;
        }
        if (key < node->data.first) {
            return get(node->left, key);
        }
        else if (key > node->data.first) {
            return get(node->right, key);
        }
        else {
            return node;
        }
    }

    pair<T1, T2> rank(Node* node, int n) const {
        if (node == nullptr) {
            throw out_of_range("Rank out of range");
        }
        int leftTreeSize = (node->left != nullptr) ? node->leftSize : 0;

        if (n < leftTreeSize) {
            return rank(node->left, n);
        }
        else if (n > leftTreeSize) {
            return rank(node->right, n - leftTreeSize - 1);
        }
        else {
            return node->data;
        }
    }


    void inorder(Node* node) const {
        if (node != nullptr) {
            inorder(node->left);
            cout << node->data.first << " (" << node->data.second  << ") ";
            inorder(node->right);
        }
    }

    void clear(Node* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}

    ~BinarySearchTree() {
        clear(root);
    }

    void insert(const pair<T1, T2>& data) {
        insert(root, data);
    }

    void remove(const T1& key) {
        remove(root, key);
    }

    pair<T1, T2> get(const T1& key) const {
        Node* node = get(root, key);
        if (node == nullptr) {
            throw out_of_range("Key not found");
        }
        return node->data;
    }

    pair<T1, T2> rank(int n) const {
        return rank(root, n);
    }

    void inorder() const {
        inorder(root);
        cout << endl;
    }
};

int main() {
    BinarySearchTree<int, int> tree;

    // Test 1
    cout << "[ Test 1 ]" << endl;
    tree.insert({ 33, 90 });
    tree.insert({ 50, 73 });
    tree.insert({ 43, 99 });
    tree.insert({ 11, 82 });
    tree.insert({ 24, 78 });
    tree.insert({ 46, 96 });
    tree.insert({ 1, 72 });
    tree.insert({ 8, 88 });
    tree.insert({ 36, 77 });
    tree.insert({ 56, 93 });
    tree.insert({ 53, 82 });
    tree.insert({ 59, 100 });
    cout << endl;

    // Test 2
    cout << "[ Test 2 ]" << endl;
    tree.inorder();
    cout << endl;

    // Test 3
    cout << "[ Test 3 ]" << endl;
    tree.remove(50);
    cout << endl;
    
    // Test 4
    cout << "[ Test 4 ]" << endl;
    tree.inorder();
    cout << endl;
    
    // Test 5
    cout << "[ Test 5 ]" << endl;
    tree.remove(8);
    cout << endl;
    
    // Test 6
    cout << "[ Test 6 ]" << endl;
    tree.inorder();
    cout << endl;
    
    // Test 7
    cout << "[ Test 7 ]" << endl;
    tree.remove(56);
    cout << endl;

    // Test 8
    cout << "[ Test 8 ]" << endl;
    tree.inorder();
    cout << endl;
    
    // Test 9
    cout << "[ Test 9 ]" << endl;
    pair<int, int> result;
    result = tree.get(43);
    cout << result.first << " (" << result.second << ")" << endl;
    cout << endl;

    // Test 10
    cout << "[ Test 10 ]" << endl;
    result = tree.rank(5);
    cout << result.first << " (" << result.second << ")" << endl;
    cout << endl;

    return 0;
}
