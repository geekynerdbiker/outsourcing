#include "btree.hpp"
#include <iostream> 
#include <cstring>

btree::btree(){
    root = new page(LEAF);
    height = 1;
};

void btree::insert(char *key, uint64_t val){
    // Please implement this function in project 2.
    
    page* p = this->root;
    page* new_page = nullptr;
    page* new_root = nullptr;
    page* stack[100] = { 0 };
    
    uint16_t new_record_size = sizeof(uint16_t) + strlen(key) + sizeof(val) + 1;
    
    int top = -1;
    stack[++top] = p;
    
    while (p->get_type() != LEAF) {
        p = (page*)p->find(key);
        stack[++top] = p;
    }
    
    page* backup = nullptr;
    while (top != -1) {
        p = stack[top--];
        
        if (p->is_full(new_record_size)) {
            if (p == this->root) {
                char* parent_key = (char*)malloc(sizeof(key) + 1);
                new_page = p->split(key, val, &parent_key);
                
                if (backup != nullptr)
                    new_page->set_leftmost_ptr(backup);
                
                new_root = new page(INTERNAL);
                new_root->insert(parent_key, (uint64_t)(new_page));
                
                this->height++;
                this->root = new_root;
                
                new_root->set_leftmost_ptr(p);
                top = -1;
                
                return;
            } if (p->get_type() == INTERNAL) {
                char* parent_key = (char*)malloc(sizeof(key) + 1);
                new_page = p->split(key, val, &parent_key);
                
                if (backup != nullptr)
                    new_page->set_leftmost_ptr(backup);
                
                key = parent_key;
                val = (uint64_t)new_page;
                
                continue;
            }
            backup = p;
            
            char* parent_key = (char*)malloc(sizeof(key) + 1);
            new_page = p->split(key, val, &parent_key);
            
            key = parent_key;
            val = (uint64_t)new_page;
            
            continue;
        } else {
            p->insert(key, val);
            top = -1;
            return;
        }
    }
    
    if (top != -1)
        top = -1;
}

uint64_t btree::lookup(char *key){
    // Please implement this function in project 2.
    uint64_t val = 0;
    page* p = this->root;
    
    while (p->get_type() != LEAF)
        p = (page*)p->find(key);
    
    val = p->find(key);
    
    return val != 0 ? val : 0;
}
