#ifndef FVM_MACHINE_H
#define FVM_MACHINE_H

#include <stdint.h>

#include "fvm_bytecode.h"
#include "fvm_status.h"

// TODO: Make stack dynamically sized
#define STACK_SIZE 256

typedef struct fvm_machine {
	uint8_t stack[STACK_SIZE];
	uint8_t *sp;
	const uint8_t *instructions;
	uint32_t inst_length;
	const uint8_t *ip;
	uint8_t halt;
} fvm_machine;

fvm_machine *fvm_machine_new(const uint8_t *instructions, uint32_t inst_length);
void fvm_machine_free(fvm_machine *vm);

fvm_status fvm_machine_push(fvm_machine *vm, uint8_t byte);
uint8_t fvm_machine_pop(fvm_machine *vm);

fvm_status fvm_machine_do_op(fvm_machine *vm);
fvm_status fvm_machine_execute(fvm_machine *vm);

#endif // FVM_MACHINE_H
