#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "skiplist.h"
// 변수, 파라미터 바꾸지 말 것
/*
 * Define SENTINEL node.
 */
static struct sl_node_t SENTINEL = { 0, NULL, NULL };
#define IS_SENTINEL(n) (n == &SENTINEL)

/*
 * Allocate memory for a node of skiplist.
 * Forward pointers are initialized to SENTINAL node.
 */
static struct sl_node_t* alloc_node(struct skiplist* sl, int level, void* key, void* value) {
    int size;
    struct sl_node_t* new_node;
    
    size = sizeof(struct sl_node_t) + level * sizeof(struct sl_node_t*); // 노드 구조체 + 포인터 배열[레벨]
    new_node = malloc(size);
    if (new_node == NULL) // 할당 안됐으면 NULL을 반환
        return NULL;
    
    new_node->level = level;
    new_node->key = key;
    new_node->value = value;
    
    for (int i = 0; i < level; i++)
        new_node->next[i] = &SENTINEL; // 포인터 배열값 &SENTINEL로 초기화
    
    return new_node;
}

/*
 * Free memory for a node
 */
static void free_node(struct sl_node_t* n) {
    free(n);
}

int skiplist_count(struct skiplist* sl) {
    return sl->count;
}

int skiplist_empty(struct skiplist* sl) {
    return sl->count == 0;
}

/*
 * Create a new skiplist.
 * cmp parameter is a function to compare nodes' key
 */
struct skiplist* skiplist_create(skiplist_cmp_func* cmp,
                                 skiplist_print_kv_func* print, unsigned int seed) { // skip list = sl 생성
    struct skiplist* sl;
    struct sl_node_t* head;
    
    sl = malloc(sizeof(struct skiplist)); // sl에 구조체만큼의 메모리 할당
    if (sl) {
        sl->count = 0; // sl의 노드수 초기화
        sl->cmp = cmp; //
        sl->print = print;
        
        head = alloc_node(sl, SKIPLIST_MAX_LEVEL, &SENTINEL, &SENTINEL); // level에 MAX값 할당 -> 헤드 레벨을 증가시킬 때 구현이 용이해짐
        if (head == NULL) {
            free(sl);
            return NULL;
        }
        sl->head = head; // 할당한 head를 sl의 head로 전달
        srand(seed);        // to generate random level using rand()
    }
    
    return sl;
}

/*
 * Destroy skiplist
 * Free all node, head and sl
 * return the number of nodes
 */
int skiplist_destroy(struct skiplist* sl) {
    int num_nodes = 0;
    struct sl_node_t* cur, * to_free;
    
    /////////////////////////////////////////
    // input code: free all node
    assert(sl);
    cur = sl->head->next[0];
    
    while (!IS_SENTINEL(cur)) {
        to_free = cur;
        cur = to_free->next[0];
        free_node(to_free);
        num_nodes++;
    }
    for (int i = 0; i < sl->head->level; i++)
        sl->head->next[i] = &SENTINEL;
    /////////////////////////////////////////
    
    free_node(sl->head);
    free(sl);
    
    return num_nodes;
}

/*
 * Generate level with probability 1/2 using coin flip.
 */
static int generate_rand() {
    /////////////////////////////////////////
    // input code: generate probability 1/2 using rand()
    return rand() % 2;
    /////////////////////////////////////////
}

static int generate_rand_level() {
    int level = 1; // 기본 레벨 1
    
    while (generate_rand() == 0 && level < SKIPLIST_MAX_LEVEL) // 랜덤함수로 레벨값 증가시킴
        level++;
    
    return level;
}

/*
 * Set prevs[] pointers to the level nodes that precede the position for key.
 * add, set and delete functions use this one.
 */
static void set_prev_ptrs(struct skiplist* sl, void* key,
                          struct sl_node_t* head, int level, struct sl_node_t** prevs) {
    
    int lvl, res;
    struct sl_node_t* cur, * next;
    
    /////////////////////////////////////////
    // input code: set prevs[] pointers to the nodes before key
    cur = head;
    lvl = level-1;
    
    do {
        assert(lvl < cur->level);
        assert(cur->level <= SKIPLIST_MAX_LEVEL);
        next = cur->next[level];
        if (!next)
            break;
        res = IS_SENTINEL(next) ? 1 : sl->cmp(next->key, key);
        
        if (res < 0)
            cur = next;
        else {
            prevs[lvl] = cur;
            lvl--;
        }
    } while (lvl >= 0);
    /////////////////////////////////////////
}

/*
 * Insert key and value in ascending order.
 */
int skiplist_add(struct skiplist* sl, void* key, void* value) {
    int min_level, cur_level, new_level;
    struct sl_node_t* head, * new_node;
    struct sl_node_t* prevs[SKIPLIST_MAX_LEVEL];
    
    head = sl->head;
    cur_level = head->level;
    set_prev_ptrs(sl, key, head, cur_level, prevs); // prevs 찾는 위 함수 사용
    
    /////////////////////////////////////////
    // input code: add new_node to skiplist
    assert(sl);
    assert(head);
    
    new_level = generate_rand_level();
    new_node = alloc_node(sl, new_level, key, value);
    
    if (!new_node)
        return 0;
    
    if (new_level > cur_level) {
        struct sl_node_t* old_head = sl->head;
        struct sl_node_t* new_head = alloc_node(sl, new_node->level,
                                                &SENTINEL, &SENTINEL);
        if (new_head == NULL)
            return 0;
        
        for (int i = 0; i < old_head->level; i++)
            new_head->next[i] = old_head->next[i];
        
        for (int i = old_head->level; i < new_head->level; i++)
            new_head->next[i] = new_node;
        
        sl->head = new_head;
        free_node(old_head);
        
        for (int i = 0; i < cur_level; i++)
            if (prevs[i] == head)
                prevs[i] = sl->head;
        head = sl->head;
    }
    
    min_level = new_node->level < cur_level ? new_node->level : cur_level;
    for (int i = 0; i < min_level; i++) {
        assert(i < prevs[i]->level);
        new_node->next[i] = prevs[i]->next[i];
        assert(prevs[i]->level <= SKIPLIST_MAX_LEVEL);
        prevs[i]->next[i] = new_node;
    }
    /////////////////////////////////////////
    
    sl->count++;
    
    return 1;
}

/*
 * Search key in skiplist.
 * if key exists
 *      replace value of the node and return 1.
 *      old is set to value of the node.
 * else
 *      add the key and the value to skiplist.
 */
int skiplist_set(struct skiplist* sl, void* key, void* value, void** old) { 
    int res, cur_level;
    struct sl_node_t* head, * candiate;
    struct sl_node_t* prevs[SKIPLIST_MAX_LEVEL];
    
    head = sl->head;
    cur_level = head->level;
    set_prev_ptrs(sl, key, head, cur_level, prevs);
    
    /////////////////////////////////////////
    // input code: replace value of old node into value and old is set to previous value
    assert(sl);
    assert(head);
    
    candiate = prevs[0]->next[0];
    
    if (!IS_SENTINEL(candiate)) {
        int res = sl->cmp(candiate->key, key);
        if (res == 0) {
            if (old)
                *old = candiate->value;
            candiate->value = value;
            return 1;
        } else {
            if (old)
                *old = NULL;
        }
    }
    /////////////////////////////////////////
    
    return skiplist_add(sl, key, value);
}

/*
 * Search key in skiplist.
 * if key exists
 *      delete the node and return 1 in the node.
 *      old is set to value of the node.
 * else return 0.
 */
int skiplist_delete(struct skiplist* sl, void* key, void** old) {
    int cur_level;
    struct sl_node_t* head, * to_delete;
    struct sl_node_t* prevs[SKIPLIST_MAX_LEVEL];
    
    head = sl->head;
    cur_level = head->level;
    set_prev_ptrs(sl, key, head, cur_level, prevs);
    
    /////////////////////////////////////////
    // input code: delete the node of key and old value is set to value of the node
    // if not exist, return 0
    to_delete = prevs[0]->next[0];
    if (IS_SENTINEL(to_delete) || 0 != sl->cmp(to_delete->key, key))
        return 0;
    
    for (int i = 0; i < to_delete->level; i++)
        prevs[i]->next[i] = to_delete->next[i];
    if (old)
        *old = to_delete->value;
    /////////////////////////////////////////
    
    free_node(to_delete);
    sl->count--;
    
    return 1;
}

/*
 * Search key in skiplist.
 * if key exists, return *value in the node.
 * else return NULL.
 */
int skiplist_get(struct skiplist* sl, void* key, void** value) {
    int lvl, res, found = 0; // res???
    struct sl_node_t* head, * cur, * next = NULL;
    
    cur = head = sl->head;
    lvl = head->level - 1;
    do {
        next = cur->next[lvl];
        
        ///////////////////////////////////////// int*, char*로 변환 나중에
        // input code: search the node of key 서치 알고리즘
        assert(next->level <= SKIPLIST_MAX_LEVEL);
        res = IS_SENTINEL(next) ? 1 : sl->cmp(next->key, key);
        
        if (res < 0)
            cur = next;
        else if (res >= 0) {
            if (lvl == 0) {
                if (res == 0)
                    return next->value;
                return NULL;
            }
            lvl--;
        }
        /////////////////////////////////////////
    } while (lvl >= 0);
    
    ///
    cur = cur->next[0];
    if (next->key == key) {
        found = 1;
    }
    ///
    
    if (found) {
        if (value) *value = next->value;
        return 1;
    }
    else {
        return 0;
    }
}

int skiplist_exist(struct skiplist* sl, void* key) {
    return skiplist_get(sl, key, NULL);
}

void skiplist_debug(struct skiplist* sl) {
    int max_level, num_nodes = 0;
    int counts[SKIPLIST_MAX_LEVEL] = { 0, };
    struct sl_node_t* head, * node, * prev_node;
    
    max_level = sl->head->level;
    head = sl->head;
    for (int i = max_level - 1; i >= 0; i--) {
        printf("Level %d:", i);
        prev_node = NULL;
        for (node = head->next[i]; node != &SENTINEL; node = node->next[i]) {
            sl->print(node->key, node->value);
            
            if (prev_node && (sl->cmp(prev_node->key, node->key) > 0)) {
                printf("Error: node->key < prev_node->key\n");
                exit(-1);
            }
            prev_node = node;
            
            if (node->level > max_level) {
                printf("Error: node->level > head->level\n");
                exit(-1);
            }
            num_nodes++;
        }
        
        counts[i] = num_nodes;
        num_nodes = 0;
    }
    
    for (int i = 0; i < max_level; i++)
        printf("The number of nodes in level %d = %d\n", i, counts[i]);
}
