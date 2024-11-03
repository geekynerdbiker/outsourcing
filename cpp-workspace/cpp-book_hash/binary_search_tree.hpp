template<typename T>
binary_search_tree<T>::binary_search_tree() : root(nullptr), count(0) {}

template<typename T>
binary_search_tree<T>::~binary_search_tree() {
    clear();
}

template<typename T>
void binary_search_tree<T>::insert(const T& item) {
    insert(item, root);
}

template<typename T>
void binary_search_tree<T>::insert(const T& item, binary_node*& node) {
    if (node == nullptr) {
        node = new binary_node(item);
        count++;
    } else if (item.get_key() < node->data.get_key()) {
        insert(item, node->left);
    } else if (item.get_key() > node->data.get_key()) {
        insert(item, node->right);
    } else {
        node->data = item;
    }
}

template<typename T>
void binary_search_tree<T>::remove(const std::string& key) {
    remove(key, root);
}

template<typename T>
void binary_search_tree<T>::remove(const std::string& key, binary_node*& node) {
    if (node == nullptr) return;

    if (key < node->data.get_key()) {
        remove(key, node->left);
    } else if (key > node->data.get_key()) {
        remove(key, node->right);
    } else {
        if (node->left == nullptr) {
            binary_node* temp = node;
            node = node->right;
            delete temp;
        } else if (node->right == nullptr) {
            binary_node* temp = node;
            node = node->left;
            delete temp;
        } else {
            binary_node* minNode = find_min(node->right);
            node->data = minNode->data;
            remove(minNode->data.get_key(), node->right);
        }
        count--;
    }
}

template<typename T>
bool binary_search_tree<T>::contains(const std::string& key) const {
    return contains(key, root);
}

template<typename T>
bool binary_search_tree<T>::contains(const std::string& key, binary_node* node) const {
    if (node == nullptr) return false;
    if (key < node->data.get_key()) return contains(key, node->left);
    if (key > node->data.get_key()) return contains(key, node->right);
    return true;
}

template<typename T>
T* binary_search_tree<T>::find(const std::string& key) const {
    binary_node* result = find(key, root);
    return result ? &result->data : nullptr;
}

template<typename T>
typename binary_search_tree<T>::binary_node* binary_search_tree<T>::find(const std::string& key, binary_node* node) const {
    if (node == nullptr) return nullptr;
    if (key < node->data.get_key()) return find(key, node->left);
    if (key > node->data.get_key()) return find(key, node->right);
    return node;
}

template<typename T>
T& binary_search_tree<T>::find_min() const {
    if (empty()) throw std::runtime_error("Tree is empty");
    return find_min(root)->data;
}

template<typename T>
typename binary_search_tree<T>::binary_node* binary_search_tree<T>::find_min(binary_node* node) const {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

template<typename T>
T& binary_search_tree<T>::find_max() const {
    if (empty()) throw std::runtime_error("Tree is empty");
    return find_max(root)->data;
}

template<typename T>
typename binary_search_tree<T>::binary_node* binary_search_tree<T>::find_max(binary_node* node) const {
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}

template<typename T>
void binary_search_tree<T>::clear() {
    clear(root);
    count = 0;
}

template<typename T>
void binary_search_tree<T>::clear(binary_node*& node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
        node = nullptr;
    }
}

template<typename T>
int binary_search_tree<T>::size() const {
    return count;
}

template<typename T>
bool binary_search_tree<T>::empty() const {
    return count == 0;
}

template<typename T>
void binary_search_tree<T>::print_inorder(std::ostream& out) const {
    print_inorder(out, root);
}

template<typename T>
void binary_search_tree<T>::print_inorder(std::ostream& out, binary_node* node) const {
    if (node != nullptr) {
        print_inorder(out, node->left);
        out << node->data << " ";
        print_inorder(out, node->right);
    }
}

template<typename T>
void binary_search_tree<T>::print_preorder(std::ostream& out) const {
    print_preorder(out, root);
}

template<typename T>
void binary_search_tree<T>::print_preorder(std::ostream& out, binary_node* node) const {
    if (node != nullptr) {
        out << node->data << " ";
        print_preorder(out, node->left);
        print_preorder(out, node->right);
    }
}

template<typename T>
void binary_search_tree<T>::print_postorder(std::ostream& out) const {
    print_postorder(out, root);
}

template<typename T>
void binary_search_tree<T>::print_postorder(std::ostream& out, binary_node* node) const {
    if (node != nullptr) {
        print_postorder(out, node->left);
        print_postorder(out, node->right);
        out << node->data << " ";
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const binary_search_tree<T>& tree) {
    tree.print_inorder(out);
    return out;
}
