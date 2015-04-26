#include "channel.h"
#include <pthread.h>
#include <stdio.h>

#define BUFF_SIZE   5		
#define PRODS       1		
#define CONS        1		
#define N           1	/* Quanto cada produtor produz 
			(e cada consumidor consome)*/	

typedef struct {
    int item;
    asynch_t * shared ; 
} args;
	/* Canal compartilhado */

void *Producer(void* arg)
{
    int i, item , index;
    printf("ct = %p\n\n",(void*)arg);
    args* a = arg;
    printf("ct == %p\n\n",(void*)a);
    index = a->item; 
    printf("criada thread produtora %d\n",index);
    for (i=0; i < N; i++) {

        /* Produz item */
        item = i;	
	
	    printf("[P%d] Produzindo %d ...\n", index, item); 
        printf("%p\t%d\n",a->shared,asynch_inspect(a->shared,2));  
        asend( a->shared , &item );  
	    printf("[P%d] Produziu %d ...\n", index, item); 

        /* Interleave  producer and consumer execution */
        if (i % 2 == 1) sleep(1);
    }
    return NULL;
}

void *Consumer(void *arg)
{
    int i,item, index ;

    args* a = arg;
    index = a->item;
    printf("criada thread consumidora %d\n",index);
    for (i=0; i < N; i++) {
        arecv( a->shared , &item );  
	    printf("=====>[C%d] Consumiu %d ...\n", index, item); 
    }
    return NULL;
}

int main()
{
    pthread_t idProd, idCons;
    int index;
    asynch_t * shared ; 
    shared = create_new_a(shared,BUFF_SIZE);
    printf("criado canal:\n%d\n",asynch_inspect(shared,2));
    for (index = 0; index < PRODS; index++)
    {  
       args* arg = malloc(sizeof(args)); 
       arg->item = index;
       arg->shared = shared;
       printf("ct %p\n",arg);
       pthread_create(&idProd, NULL, Producer, arg);
    }
    
    for (index = 0; index < CONS; index++)
    {  
       args* arg = malloc(sizeof(args)); 
       arg->item = index;
       pthread_create(&idCons, NULL, Consumer, &arg);
    }

    adestroy( shared );
    pthread_exit(NULL);
}
