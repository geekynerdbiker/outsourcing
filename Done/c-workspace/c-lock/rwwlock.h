#include <semaphore.h>

typedef struct _rwwlock_t {
    int readers;
    int writers;
    sem_t lock;
    sem_t writelock;
} rwwlock_t;

void rwwlock_init(rwwlock_t *rww);
void rwwlock_acquire_writelock(rwwlock_t *rww);
void rwwlock_release_writelock(rwwlock_t *rww);
void rwwlock_acquire_readlock(rwwlock_t *rww);
void rwwlock_release_readlock(rwwlock_t *rww);

void rwwlock_init(rwwlock_t *rww){
    rww->readers = 0;
    rww->writers = 0;
    sem_init(&(rww->lock), 0, 1);
    sem_init(&(rww->writelock), 0, 1);
}
void rwwlock_acquire_writelock(rwwlock_t *rww){
    sem_wait(&(rww->lock));
    rww->writers++;
    sem_post(&(rww->lock));
    sem_wait(&(rww->writelock));
}
void rwwlock_release_writelock(rwwlock_t *rww){
    sem_wait(&(rww->lock));
    rww->writers--;
    if (rww->writers == 0) {
        sem_post(&(rww->lock));
    }
    sem_post(&(rww->writelock));
}
void rwwlock_acquire_readlock(rwwlock_t *rww){
    sem_wait(&(rww->lock));
    while (rww->writers > 0) {
        sem_post(&(rww->lock));
        sem_wait(&(rww->lock));
    }
    rww->readers++;
    sem_post(&(rww->lock));
}
void rwwlock_release_readlock(rwwlock_t *rww){
    sem_wait(&(rww->lock));
    rww->readers--;
    if (rww->readers == 0 && rww->writers > 0) {
        sem_post(&(rww->writelock));
    }
    sem_post(&(rww->lock));
}
