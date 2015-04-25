#include "channel.h"
#include <pthread.h>
#include <semaphore.h>

struct synch {
    int buffer;
    pthread_mutex_t lock;
};

struct asynch {
    int *buffer;
    int capacity;
    pthread_mutex_t buffer_lock;
    sem_t write_lock;
		/* Bloqueia se o buffer está cheio */
    sem_t read_lock;
		/* Bloqueia se o buffer está vazio */

};

asynch_t* create_new_a(asynch_t* h, int capacity){
    h = malloc(sizeof(asynch_t));
    h->buffer = malloc(sizeof(int)*capacity);
    h->capacity = capacity ;
    sem_init( &(h->write_lock) ,0,capacity);
    sem_init( &(h->read_lock) ,0,0);
    pthread_mutex_init( &(h->buffer_lock), 0 );
    return h; 
}

int asend(asynch_t* h, int* mess){
    int val ;
	sem_wait( &(h->write_lock) );
	pthread_mutex_lock( &(h->buffer_lock) );
    
        sem_getvalue( &(h->write_lock), &val);
        h->buffer[val] = *mess;

	pthread_mutex_unlock( &(h->buffer_lock) );
	sem_post(&(h->read_lock));
}

int arecv(asynch_t* h, int* mess){
    int val;
    sem_wait(&(h->read_lock));
    pthread_mutex_lock( &(h->buffer_lock) );
 	
    sem_getvalue( &(h->read_lock), &val);
    *mess = h->buffer[val];

    pthread_mutex_unlock( &(h->buffer_lock) );
    sem_post( &(h->write_lock) );
}

synch_t* create_new_s(synch_t* h){
    h = malloc(sizeof(synch_t));
    h->buffer = 0;
    pthread_mutex_init(&(h->lock),NULL);
    return h; 
}

int send(synch_t* h, int* mess){
    pthread_mutex_lock(&(h->lock));
    h->buffer = *mess;
    pthread_mutex_unlock(&(h->lock));
}

int recv(synch_t* h, int* mess){
    pthread_mutex_lock(&(h->lock));
    *mess = h->buffer;
    pthread_mutex_unlock(&(h->lock));
}

void destroy(synch_t* h){
    pthread_mutex_destroy(&(h->lock));
    free(h);
}
void adestroy(asynch_t* h){
    sem_destroy(&(h->write_lock));
    sem_destroy(&(h->read_lock));
    pthread_mutex_destroy(&(h->buffer_lock));
    free(h->buffer);
    free(h);
}
