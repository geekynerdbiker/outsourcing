#pragma once

#define SKIPLIST_MAX_LEVEL    16

// Comparison function
// int (*skiplist_cmp_func)(void *, void *)
typedef int skiplist_cmp_func(void* key_a, void* key_b);

// Print function
typedef void skiplist_print_kv_func(void* key, void* value);

struct skiplist {
    int count;                      // the number of nodes in skiplist
    struct sl_node_t* head;         // head node of skiplist
    skiplist_cmp_func* cmp;         // key comparison function
    skiplist_print_kv_func* print;  // key/value print function
};

struct sl_node_t {
    int level;                      // node's level
    void* key;                      // key
    void* value;                    // value

    // struct sl_node_t *next[0];   // next does not include size of sl_node_t
    // struct sl_node_t *next[1];   // all node has one pointer basically 
    // struct sl_node_t **next;     // same as follow declaration but not clearly
    struct sl_node_t* next[];       // forward pointers
};

struct skiplist* skiplist_create(skiplist_cmp_func* cmp,
	skiplist_print_kv_func* print, unsigned int seed);
int skiplist_destroy(struct skiplist* sl);

int skiplist_add(struct skiplist* sl, void* key, void* value);
int skiplist_set(struct skiplist* sl, void* key, void* value, void** old);
int skiplist_get(struct skiplist* sl, void* key, void** value);
int skiplist_exist(struct skiplist* sl, void* key);
int skiplist_delete(struct skiplist* sl, void* key, void** value);
int skiplist_count(struct skiplist* sl);
int skiplist_empty(struct skiplist* sl);

void skiplist_debug(struct skiplist* sl);
