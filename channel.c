#include "channel.h"
struct synch {
    int buffer;
    pthread_mutex_t* lock;
};

struct asynch {
    int *buffer;
    int capacity;
    sem_t sem;
};

asynch_t* create_new_a(asynch_t* h, int capacity){
    h = malloc(sizeof(asynch_t));
    h->buffer = malloc(sizeof(int)*capacity);
    sem_init(h->sem,0,capacity);
    return h; 
}

int asend(asynch_t* h, int* mess){
    //checa capacidade
    int val;
    sem_getvalue(h->sem, &val);
    h->buffer[val] = *mess;
    sem_post(h->sem);
}

int arecv(asynch_t* h, int* mess){
    sem_wait(h->sem);           
    int val;
    sem_getvalue(h->sem, &val);
    *mess = h->buffer[val];
}

synch_t* create_new_s(synch_t* h){
    h = malloc(sizeof(synch_t));
    h->buffer = 0;
    pthread_mutex_init(h->lock,NULL);
    return h; 
}

int send(synch_t* h, int* mess){
    mutex_lock(h->lock);
    h->buffer = *mess;
    mutex_unlock(h->lock);
}

int recv(synch_t* h, int* mess){
    mutex_lock(h->lock);
    *mess = h->buffer;
    mutex_unlock(h->lock);
}

void destroy(synch_t* h){
    //destruir mutex
    free(h);
}
void adestroy(asynch_t* h){
    //destruir semaforo
    free(h->buffer);
    free(h);
}
