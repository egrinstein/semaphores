#include "channel.h"
#include <pthread.h>
#include <stdio.h>

#ifndef BUFF_SIZE
#define BUFF_SIZE   50		
#endif
#ifndef PRODS
#define PRODS       3		
#endif
#ifndef CONS
#define CONS        3		
#endif
#ifndef N 
#define N           4	/* Quanto cada produtor produz (e cada consumidor consome)*/	
#endif
typedef struct {
    int item;
    asynch_t * shared ; 
} args;
	
void *Producer(void* arg)
{
    int i, item , index;
    
    args* a = arg;
   
    index = a->item; 

    for (i=0; i < N; i++) {

        /* Produz item */
        item = i;	
	 
        asend( a->shared , &item );  
	printf("[P%d] Produziu %d ...\n", index, item); 

        /* Intercala execução do produtor e consumidor */
        if (i % 2 == 1) sleep(1);
    }
    return NULL;
}

void *Consumer(void *arg)
{
    int i,item, index ;

 
    args* a = arg;
    
    index = a->item;

    for (i=0; i < N; i++) {
	/* consome buffer */
        arecv( a->shared , &item );  
	    printf("=====>[C%d] Consumiu %d ...\n", index, item); 
    }
    return NULL;
}

int main()
{
    pthread_t* threads = (pthread_t*)malloc((PRODS+CONS)*sizeof(pthread_t));
    args* thread_args[PRODS+CONS];
       
    int index;
    asynch_t * shared ; 
    shared = create_new_a(shared,BUFF_SIZE);

    for (index = 0; index < PRODS; index++)
    {  
       thread_args[index] = malloc(sizeof(args)); 
       thread_args[index]->item = index;
       thread_args[index]->shared = shared;
       pthread_create(&threads[index], NULL, Producer, thread_args[index]);
    }
    for (index = 0; index < CONS; index++)
    {  
       thread_args[index+PRODS] = malloc(sizeof(args)); 
       thread_args[index+PRODS]->item = index;
       thread_args[index+PRODS]->shared = shared;
       pthread_create(&threads[index+PRODS], NULL, Consumer, thread_args[index]);
    }
    for (index = 0; index < PRODS+CONS; index++)
    {
       pthread_join(threads[index],NULL); 
       free(thread_args[index]);
    }
    adestroy( shared );
    pthread_exit(NULL);
    free(threads);
}
