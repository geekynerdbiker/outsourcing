#include <semaphore.h>

typedef struct _rwrlock_t {
    int readers;
    int writers;
    sem_t lock;
    sem_t writelock;
} rwrlock_t;

void rwrlock_init(rwrlock_t *rwr);
void rwrlock_acquire_writelock(rwrlock_t *rwr);
void rwrlock_release_writelock(rwrlock_t *rwr);
void rwrlock_acquire_readlock(rwrlock_t *rwr);
void rwrlock_release_readlock(rwrlock_t *rwr);

void rwrlock_init(rwrlock_t *rwr){
    rwr->readers = 0;
    rwr->writers = 0;
    sem_init(&(rwr->lock),0,1);
    sem_init(&(rwr->writelock),0,1);
}
void rwrlock_acquire_writelock(rwrlock_t *rwr){
    sem_wait(&(rwr->lock));
    rwr->writers++;
    sem_post(&(rwr->lock));
    sem_wait(&(rwr->writelock));
}
void rwrlock_release_writelock(rwrlock_t *rwr){
    sem_wait(&(rwr->lock));
    rwr->writers--;
    sem_post(&(rwr->lock));
    sem_post(&(rwr->writelock));
}
void rwrlock_acquire_readlock(rwrlock_t *rwr){
    sem_wait(&(rwr->lock));
    while (rwr->writers > 0) {
        sem_post(&(rwr->lock));
        sem_wait(&(rwr->lock));
    }
    rwr->readers++;
    if (rwr->readers == 1) {
        sem_wait(&(rwr->writelock));
    }
    sem_post(&(rwr->lock));
}
void rwrlock_release_readlock(rwrlock_t *rwr){
    sem_wait(&(rwr->lock));
    rwr->readers--;
    if (rwr->readers == 0) {
        sem_post(&(rwr->writelock));
    }
    sem_post(&(rwr->lock));
}