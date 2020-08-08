CC=gcc
CFLAGS=-c -Wall -O0 -g
LDFLAGS=-lm -lpthread
SOURCES=main.c colony.c vm.c frame.c object.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=colony

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS)
	rm $(EXECUTABLE)
