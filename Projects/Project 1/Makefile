CC=gcc
CFLAGS=-Wall

all: proctopk threadtopk

proctopk: proctopk.c
	$(CC) $(CFLAGS) -o $@ $<

threadtopk: threadtopk.c
	$(CC) $(CFLAGS) -o $@ $< -lpthread

clean:
	rm -f proctopk threadtopk

