#ifndef FRUSCH_VM_H
#define FRUSCH_VM_H

#include "frusch_int.h"

// TODO: Adapt stack to be dynamically allocated
#define STACK_SIZE 64

typedef struct Vm {
	u32 stack[STACK_SIZE];
	u32 *program;
	u32 program_size;
	u32 sp;
	u32 ip;
	u8 halt;
} Vm;

Vm vm_new(u32 *program, u32 program_size);
s32 vm_execute(Vm *vm);
s32 vm_run(Vm *vm);

#endif /* FRUSCH_VM_H */
