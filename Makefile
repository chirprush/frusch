CC := gcc

CFLAGS := -Werror -Wall -Wswitch-enum

cfiles  := $(wildcard src/*.c)
cfiles  := $(filter-out src/frusch.c, $(cfiles))
cfiles  := $(filter-out src/fvm.c, $(cfiles))
objects := $(cfiles:src/%.c=bin/%.o)

bin/frusch: $(objects)
	$(CC) -c src/frusch.c -o bin/frusch.o $(CFLAGS)
	$(CC) -o bin/frusch bin/frusch.o $(objects) $(CFLAGS)

bin/fvm: $(objects)
	$(CC) -c src/fvm.c -o bin/fvm.o $(CFLAGS)
	$(CC) -o bin/fvm bin/fvm.o $(objects) $(CFLAGS)

$(objects): bin
	$(CC) -c $(@:bin/%.o=src/%.c) -o $@ $(CFLAGS)

bin:
	mkdir bin

clean:
	rm bin/*

.PHONY: clean
