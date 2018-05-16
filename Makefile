CFLAGS = -o
CC = g++

default: cc

cc:	LoopFusion.c LoopInterchange.c LoopTiling.c LoopUnrolling.c
	$(CC) $(CFLAGS) LoopFusion.o LoopFusion.c
	$(CC) $(CFLAGS) LoopInterchange.o LoopInterchange.c
	$(CC) $(CFLAGS) LoopTiling.o LoopTiling.c
	$(CC) $(CFLAGS) LoopUnrolling.o LoopUnrolling.c

clean:
	$(RM) Loop*.o *~