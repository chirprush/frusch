CC := gcc

CFLAGS := -Werror -Wall -Wswitch-enum -fshort-enums -g

frusch_cfiles  := $(wildcard src/frusch_*.c)
fvm_cfiles  := $(wildcard src/fvm_*.c)
frusch_objects := $(frusch_cfiles:src/%.c=bin/%.o)
fvm_objects := $(fvm_cfiles:src/%.c=bin/%.o)
all_objects := $(filter-out bin/fvm_main.o,$(frusch_objects) $(fvm_objects))

bin/frusch: $(frusch_objects) $(fvm_objects)
	$(CC) -o bin/frusch $(all_objects) $(CFLAGS)

bin/fvm: $(fvm_objects)
	$(CC) -o bin/fvm $(fvm_objects) $(CFLAGS)

$(frusch_objects): bin
	$(CC) -c $(@:bin/%.o=src/%.c) -o $@ $(CFLAGS)

$(fvm_objects): bin
	$(CC) -c $(@:bin/%.o=src/%.c) -o $@ $(CFLAGS)

bin:
	mkdir -p bin

clean:
	rm bin/*

.PHONY: frusch fvm clean
