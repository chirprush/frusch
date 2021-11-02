#ifndef FVM_MACHINE_H
#define FVM_MACHINE_H

#include "fvm_bytecode.h"
#include "fvm_status.h"
#include "fvm_int.h"

// TODO: Make stack dynamically sized
#define STACK_SIZE 256

typedef struct fvm_machine {
	u8 stack[STACK_SIZE];
	u8 *sp;
	const u8 *instructions;
	u32 inst_length;
	const u8 *ip;
	u8 halt;
} fvm_machine;

fvm_machine *fvm_machine_new(const u8 *instructions, u32 inst_length);

fvm_status fvm_machine_push(fvm_machine *vm, u8 byte);

fvm_status fvm_machine_do_op(fvm_machine *vm);
fvm_status fvm_machine_execute(fvm_machine *vm);

#endif // FVM_MACHINE_H
