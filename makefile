CC = gcc
OBJECTS = field_works.o observer.o main.o
LIBS = -L/usr/lib/x86_64-linux-gnu -lSDL
CFLAGS = -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -Wall -g
BINDIR = $(DESTDIR)/usr/bin
NAME = field


field: $(OBJECTS)
	$(CC) -o $(NAME) $(OBJECTS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o
	rm field


