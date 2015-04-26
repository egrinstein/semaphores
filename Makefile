all: 
	gcc -o prodcon channel.c testeasync.c -lpthread -lrt
