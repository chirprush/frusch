CC := gcc

CFLAGS := -Werror -Wall -Wswitch-enum -fshort-enums -g

frusch_source  := $(wildcard lib/frusch/*.c)
fvm_source     := $(wildcard lib/fvm/*.c)
frusch_objects := $(frusch_source:lib/frusch/%.c=bin/%.o)
fvm_objects    := $(fvm_source:lib/fvm/%.c=bin/%.o)

bin/frusch: bin/libfrusch.a
	$(CC) -o bin/frusch src/frusch_main.c -Lbin -lfrusch -Iinclude $(CFLAGS)

bin/fvm: bin/libfvm.a
	$(CC) -o bin/fvm src/fvm_main.c -Lbin -lfvm -Iinclude $(CFLAGS)

bin/libfrusch.a: $(frusch_objects) $(fvm_objects)
	ar rcs bin/libfrusch.a $(frusch_objects) $(fvm_objects)

bin/libfvm.a: $(fvm_objects)
	ar rcs bin/libfvm.a $(fvm_objects)

$(frusch_objects): bin
	$(CC) -c $(@:bin/%.o=lib/frusch/%.c) -o $@ $(CFLAGS) -Iinclude/frusch

$(fvm_objects): bin
	$(CC) -c $(@:bin/%.o=lib/fvm/%.c) -o $@ $(CFLAGS) -Iinclude/fvm

bin:
	mkdir -p bin

clean:
	rm bin/*

.PHONY: clean
