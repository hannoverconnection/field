CC = gcc
OBJECTS = field_works.o observer.o main.o
LIBS = -L/usr/lib/x86_64-linux-gnu -lSDL
CFLAGS = -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -Wall -g
BINDIR = $(DESTDIR)/usr/bin
NAME = field

field: observer.o field_works.o main.o
	$(CC) -o $(NAME) $(OBJECTS) $(LIBS)

field_works.o: field_works.c
	$(CC) $(CFLAGS) -c field_works.c -o field_works.o

observer.o: observer.c
	$(CC) $(CFLAGS) -c observer.c -o observer.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

clean:
	rm *.o


