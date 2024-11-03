template <typename T>
hash_table<T>::hash_table(int num_cells)
    : capacity(num_cells), count(0) {
    table.resize(capacity);
}

template <typename T>
hash_table<T>::~hash_table() {
    clear();
}

template <typename T>
void hash_table<T>::insert(const T& item) {
    size_t index = hash_function(item.get_key());
    table[index].push_back(item);
    count++;
}

template <typename T>
void hash_table<T>::remove(const std::string& key) {
    size_t index = hash_function(key);
    if (list_remove(table[index], key)) {
        count--;
    }
}

template <typename T>
T* hash_table<T>::get(const std::string& key) {
    size_t index = hash_function(key);
    return list_find(table[index], key);
}

template <typename T>
bool hash_table<T>::contains(const std::string& key) {
    size_t index = hash_function(key);
    return list_contains(table[index], key);
}

template <typename T>
void hash_table<T>::clear() {
    for (auto& list : table) {
        list.clear();
    }
    count = 0;
}

template <typename T>
bool hash_table<T>::empty() const {
    return count == 0;
}

template <typename T>
int hash_table<T>::size() const {
    return count;
}

template <typename T>
void hash_table<T>::print(std::ostream& os) const {
    for (size_t i = 0; i < table.size(); ++i) {
        os << i << ": ";
        list_print(os, table[i]);
        os << std::endl;
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const hash_table<T>& ht) {
    ht.print(out);
    return out;
}
