#include "channel.h"
#include <pthread.h>
#include <semaphore.h>

struct synch {
    int buffer;
    pthread_mutex_t lock;
};

struct asynch {
    int* buffer;
    int capacity;
    int messages;
    sem_t* sem;
};
void* asynch_inspect(asynch_t* h, int type){
    if(type == 0) return h->buffer;
    if(type == 1) return h->capacity;
    if(type == 2) return h->messages;
    if(type == 3) return h->sem;
}
asynch_t* create_new_a(asynch_t* h, int capacity){
    h = malloc(sizeof(asynch_t));
    h->buffer = malloc(sizeof(int)*capacity);
    h->capacity = capacity ;
    h->messages = -1 ;
    h->sem = malloc(sizeof(sem_t));
    sem_init( h->sem ,0,capacity);
    return h; 
}

int asend(asynch_t* h, int* mess){
    if(h->messages <= h->capacity){
        h->buffer[h->messages] = *mess;
        h->messages++;
        printf("asend=> %d\n",h->buffer[h->messages]);
        sem_post(h->sem);
    }
}

int arecv(asynch_t* h, int* mess){
    printf("r\n");
    sem_wait(h->sem);	
    printf("r2\n");
    printf("arecv %d\n",h->messages);
    printf("arecv=> %p\n",h->buffer);
    printf("arecv=> %d\n",h->buffer[0]);
    printf("arecv=> %d\n",h->buffer[h->messages]);
    printf("=> %d\n",h->buffer[h->messages]);
    *mess = h->buffer[h->messages];
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
    sem_destroy(h->sem);
    free(h->buffer);
    free(h);
}
