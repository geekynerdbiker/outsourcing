#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern void debug(const char *fmt, ...);
extern void *sbrk(intptr_t increment);

#define OVERLAP(s) ((s + 7) & ~ (7))
#define LENGTH(p) (*(size_t *)(p - 8))

unsigned int max_size;
int *f = 0;

void *division(void *p, size_t size)
{
    void *e = (p + size);
    
    if (LENGTH(p) - size < 9 )
        return p;
    
    else if (LENGTH(p) - size >= 9 ) {
        LENGTH(e) = LENGTH(p) - size;
        LENGTH(p) = LENGTH(p) - LENGTH(e);
        *(uintptr_t *)e = (uintptr_t)f;
        f = e;
    }
    
    return p;
    
}

void *get_empty(size_t size) {
    void *p = f;
    void *l = 0;
    
    if (!f)
        return 0;
    
    while (p && !(LENGTH(p) >= size)) {
        l = p;
        p = (void *)*( uintptr_t *)p;
    }
    
    if (p) {
        if (l)
            *(uintptr_t *)l = *(uintptr_t *)p;
        else
            f = (void *)*(uintptr_t *)f;
        
        void *e = (p + size);
        
        if (LENGTH(p) - size < 11 )
            return p;
        
        else if (LENGTH(p) - size >= 11 ) {
            LENGTH(e) = LENGTH(p) - size;
            LENGTH(p) = LENGTH(p) - LENGTH(e);
            *(uintptr_t *)e = (uintptr_t)f;
            f = e;
        }
        return p;
    }
    
    else
        return 0;
}

void *myalloc(size_t size)
{
    void *p = 0;
    
    if (size <= 0)
        return 0;
    
    size = OVERLAP(size) + 8;
    if (!f) {
        if (size < (1024 - 32)) {
            p = sbrk(1024 - 32) + 8;
            LENGTH(p) = (1024 - 32);
            return division(p, size);
        } else {
            p = sbrk(size) + 8;
            LENGTH(p) = size;
        }
    } else {
        p = get_empty(size);
        
        if (!p) {
            if (size < (1024 - 32)) {
                p = sbrk(1024 - 32) + 8;
                LENGTH(p) = (1024 - 32);
                return division(p, size);
                
            } else {
                p = sbrk(size) + 8;
                LENGTH(p) = size;
            }
        }
    }
    return p;
}

void myfree(void *ptr)
{
    if (ptr == 0) {
        ptr = 0;
        return;
    } else if (!ptr)
        return;
    
    *(uintptr_t *)ptr = (uintptr_t)f;
    f = ptr;
    
    while (ptr) {
        void *l = 0;
        void *v = f;
        
        while (v && !((ptr + LENGTH(ptr)) == v)) {
            l = v;
            v = (void *)*(uintptr_t *)v;
        }
        
        if (v) {
            LENGTH(ptr) = LENGTH(ptr) + LENGTH(v);
            if (l)
                *(uintptr_t *)l = *(uintptr_t *)v;
            else
                f = (void *)*(uintptr_t *)v;
        }
        ptr = (void *)*(uintptr_t *)ptr;
    }
    
    void *l = 0;
    void *b = sbrk(0);
    
    while (ptr && (ptr + LENGTH(ptr)) == b) {
        ptr = (void *)*( uintptr_t *)ptr;
        l = ptr;
    }
    
    if (!ptr)
        return;
    
    if (!l)
        f = (void *)*(uintptr_t *)f;
    else
        *(uintptr_t *)l = *(uintptr_t *)ptr;
}


void *myrealloc(void *ptr, size_t size)
{
    if (!ptr)
        return myalloc(size);
    
    size = OVERLAP(size) + 8;
    
    if (size < LENGTH(ptr))
        return division(ptr, size);
    
    if (size <= LENGTH(ptr))
        return ptr;
    
    void *v;
    
    v = myalloc(size);
    
    if (v) {
        memcpy(v, ptr, LENGTH(ptr));
        myfree(ptr);
        return v;
    }
    return 0;
}

