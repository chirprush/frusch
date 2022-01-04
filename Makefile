CC := gcc

CFLAGS  := -Werror -Wall -Wswitch-enum -fshort-enums -g
LDFLAGS := -Iinclude

frusch_source  := $(wildcard lib/frusch/*.c)
frusch_objects := $(frusch_source:lib/frusch/%.c=bin/%.o)

fvm_source     := $(wildcard lib/fvm/*.c)
fvm_objects    := $(fvm_source:lib/fvm/%.c=bin/%.o)

# Frusch
bin/frusch: bin/libfrusch.a
	$(CC) -o bin/frusch src/frusch_main.c -Lbin -lfrusch $(CFLAGS) $(LDFLAGS)

bin/test_frusch: bin/libfrusch.a
	$(CC) -o bin/test_frusch tests/test_frusch.c -Lbin -lfrusch $(CFLAGS) $(LDFLAGS)

bin/libfrusch.a: $(frusch_objects) $(fvm_objects)
	ar rcs bin/libfrusch.a $(frusch_objects) $(fvm_objects)

bin/%.o: lib/frusch/%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

# FVM
bin/fvm: bin/libfvm.a
	$(CC) -o bin/fvm src/fvm_main.c -Lbin -lfvm $(CFLAGS) $(LDFLAGS)

bin/test_fvm: bin/libfvm.a
	$(CC) -o bin/test_fvm tests/test_fvm.c -Lbin  -lfvm $(CFLAGS) $(LDFLAGS)

bin/libfvm.a: $(fvm_objects)
	ar rcs bin/libfvm.a $(fvm_objects)

bin/%.o: lib/fvm/%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

bin:
	mkdir -p bin

clean:
	rm bin/*

.PHONY: tests clean
