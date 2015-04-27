all: 
	gcc -o async channel.c testeasync.c -lpthread -lrt -DPRODS=10 -DCONS=10 -DN=10 -DBUFF_SIZE=10 
	gcc -o  sync channel.c testesync.c  -lpthread -lrt -DPRODS=10 -DCONS=10 -DN=10
#	gcc -o async1 channel.c testeasync.c -lpthread -lrt -DBUFF_SIZE=10 -DPRODS=10 -DCONS=5 -DN=10
#	gcc -o async2 channel.c testeasync.c -lpthread -lrt -DBUFF_SIZE=10 -DPRODS=5 -DCONS=10 -DN=10
#	gcc -o async3 channel.c testeasync.c -lpthread -lrt -DBUFF_SIZE=5  -DPRODS=10 -DCONS=5 -DN=10
#	gcc -o async4 channel.c testeasync.c -lpthread -lrt -DBUFF_SIZE=5  -DPRODS=5 -DCONS=10 -DN=10
#	gcc -o sync1 channel.c testesync.c -lpthread -lrt -DPRODS=10 -DCONS=5 -DN=10
#	gcc -o sync2 channel.c testesync.c -lpthread -lrt -DPRODS=5 -DCONS=10 -DN=10
#	gcc -o sync3 channel.c testesync.c -lpthread -lrt -DPRODS=10 -DCONS=5 -DN=10
#	gcc -o sync4 channel.c testesync.c -lpthread -lrt -DPRODS=5 -DCONS=10 -DN=10
