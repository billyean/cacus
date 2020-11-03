CC = gcc
CFLAGS = -g -Wall
CPPFLAGS =
LDFLAGS =  -lpthread

all: high_cpu_no_tracing

high_cpu_no_tracing: high_cpu_no_tracing.c
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) -f *.o high_cpu_no_tracing