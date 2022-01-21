#pragma once

#include <stdint.h>
#include <stdbool.h>

#include <fvm/bytecode.h>
#include <fvm/status.h>

typedef struct fvm_machine {
	uint8_t *stack;
	uint8_t *sp;
	uint32_t stack_capacity;

	const uint8_t *instructions;
	const uint8_t *ip;
	uint32_t inst_length;

	bool halt;
} fvm_machine;

fvm_machine *fvm_machine_new(const uint8_t *instructions, uint32_t inst_length);
void fvm_machine_free(fvm_machine *vm);

fvm_status fvm_machine_push(fvm_machine *vm, uint8_t byte);
uint8_t fvm_machine_pop(fvm_machine *vm);

fvm_status fvm_machine_do_op(fvm_machine *vm);
fvm_status fvm_machine_execute(fvm_machine *vm);
