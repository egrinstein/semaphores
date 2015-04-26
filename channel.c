#include "channel.h"
#include <pthread.h>
#include <semaphore.h>

struct synch {
    int buffer;
    pthread_mutex_t * lock;
};

struct asynch {
    int* buffer;
    int capacity;
    int messages;
    pthread_mutex_t * buffer_lock;
    sem_t* write_sem;
	/* Regula a escrita no buffer */
    sem_t* read_sem;
	/* Regula a leitura no buffer */
};
void* asynch_inspect(asynch_t* h, int type){
    if(type == 0) return h->buffer;
    if(type == 1) return h->capacity;
    if(type == 2) return h->messages;
    if(type == 3) return h->write_sem;
}
asynch_t* create_new_a(asynch_t* h, int capacity){
    h = malloc(sizeof(asynch_t));
    h->buffer = malloc(sizeof(int)*capacity);
    h->capacity = capacity ;
    h->messages = -1 ;
    
    h->read_sem = malloc(sizeof(sem_t));
    h->write_sem = malloc(sizeof(sem_t));
    h->buffer_lock = malloc(sizeof(pthread_mutex_t));
    sem_init( h->read_sem,0,0);
    sem_init( h->write_sem,0,capacity);
    pthread_mutex_init( h->buffer_lock, 0 );
    return h; 
}

int asend(asynch_t* h, int* mess){
    sem_wait( h->write_sem );
    pthread_mutex_lock( h->buffer_lock );
    h->buffer[h->messages] = *mess;
    h->messages++;
    pthread_mutex_unlock( h->buffer_lock );
    sem_post(h->read_sem);
    
}

int arecv(asynch_t* h, int* mess){
    sem_wait(h->read_sem);
    pthread_mutex_lock( h->buffer_lock );	
    *mess = h->buffer[h->messages];
    h->messages--;
    pthread_mutex_unlock( h->buffer_lock );
    sem_post(h->write_sem);
}

synch_t* create_new_s(synch_t* h){
    h = malloc(sizeof(synch_t));
    h->buffer = malloc(sizeof(pthread_mutex_t));
    h->buffer = 0;
    pthread_mutex_init(h->lock,NULL);
    return h; 
}

int send(synch_t* h, int* mess){
    pthread_mutex_lock(h->lock);
    h->buffer = *mess;
    pthread_mutex_unlock(h->lock);
}

int recv(synch_t* h, int* mess){
    pthread_mutex_lock(h->lock);
    *mess = h->buffer;
    pthread_mutex_unlock(h->lock);
}

void destroy(synch_t* h){
    pthread_mutex_destroy(h->lock);
    free(h->lock);
    free(h);
}
void adestroy(asynch_t* h){
    sem_destroy(h->read_sem);
    sem_destroy(h->write_sem);
    pthread_mutex_destroy(h->buffer_lock);
    free(h->buffer);
    free(h);
}
