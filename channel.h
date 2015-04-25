
#include <stdlib.h>

typedef struct synch synch_t;
typedef struct asynch asynch_t;

asynch_t* create_new_a(asynch_t* h, int capacity);

int asend(asynch_t* h, int* mess);

int arecv(asynch_t* h, int* mess);

synch_t* create_new_s(synch_t* h);

int send(synch_t* h, int* mess);

int recv(synch_t* h, int* mess);


