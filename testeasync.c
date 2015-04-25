#include "channel.h"
#include <pthread.h>
#include <stdio.h>

#define BUFF_SIZE   5		
#define PRODS       3		
#define CONS        3		
#define N           4	/* Quanto cada produtor produz 
			(e cada consumidor consome)*/	


asynch_t * shared ; 
	/* Canal compartilhado */

void *Producer(void *arg)
{
    int i, item , index;

    index = (int)arg; 

    for (i=0; i < N; i++) {

        /* Produz item */
        item = i;	
	
	printf("[P%d] Produzindo %d ...\n", index, item); 
        asend( shared , &item );  

        /* Interleave  producer and consumer execution */
        if (i % 2 == 1) sleep(1);
    }
    return NULL;
}

void *Consumer(void *arg)
{
    int i,item, index ;

    index = (int)arg;

    for (i=0; i < N; i++) {

        arecv( shared , &item );  
	printf("=====>[C%d] Consumiu %d ...\n", index, item); 
    }
    return NULL;
}

int main()
{
    pthread_t idProd, idCons;
    int index;

    create_new_a(shared,BUFF_SIZE);
    for (index = 0; index < PRODS; index++)
    {  
       pthread_create(&idProd, NULL, Producer, (void*)index);
    }
    
    for (index = 0; index < CONS; index++)
    {  
       pthread_create(&idCons, NULL, Consumer, (void*)index);
    }

    adestroy( shared );
    pthread_exit(NULL);
}
