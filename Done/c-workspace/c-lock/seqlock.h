#include <pthread.h>

typedef struct _seqlock_t {
    unsigned seq;
    pthread_mutex_t lock;
} seqlock_t;

void seqlock_init(seqlock_t *seq);
void seqlock_write_lock(seqlock_t *seq);
void seqlock_write_unlock(seqlock_t *seq);
unsigned seqlock_read_begin(seqlock_t *seq);
unsigned seqlock_read_retry(seqlock_t *seq, unsigned cnt);

void seqlock_init(seqlock_t *seq){
    seq->seq = 0;
    pthread_mutex_init(&(seq->lock), NULL);
}
void seqlock_write_lock(seqlock_t *seq){
    pthread_mutex_lock(&(seq->lock));
    seq->seq++;
}
void seqlock_write_unlock(seqlock_t *seq){
    seq->seq++;
    pthread_mutex_unlock(&(seq->lock));
}
unsigned seqlock_read_begin(seqlock_t *seq){
    unsigned seqno;

    do {
        seqno = seq->seq;
    } while (seqno & 1);
    __sync_synchronize();

    return seqno;
}
unsigned seqlock_read_retry(seqlock_t *seq, unsigned cnt){
    __sync_synchronize();
    return seq->seq != cnt;
}