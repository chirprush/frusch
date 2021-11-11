#include <stdlib.h>
#include <stdint.h>
#include "fvm_machine.h"
#include "fvm_bytecode.h"
#include "fvm_status.h"

#define STACK_START_SIZE 0

fvm_machine *fvm_machine_new(const uint8_t *instructions, uint32_t inst_length) {
	fvm_machine *vm = malloc(sizeof(fvm_machine));
	vm->stack = malloc(sizeof(uint8_t) * STACK_START_SIZE);
	vm->stack_length = 0;
	vm->stack_capacity = STACK_START_SIZE;
	vm->sp = vm->stack;
	vm->instructions = instructions;
	vm->inst_length = inst_length;
	vm->ip = vm->instructions;
	vm->halt = 0;
	return vm;
}

void fvm_machine_free(fvm_machine *vm) {
	free(vm->stack);
	free(vm);
}

fvm_status fvm_machine_push(fvm_machine *vm, uint8_t byte) {
	uint32_t size = vm->sp - vm->stack;
	if (size >= vm->stack_capacity) {
		uint32_t new_capacity =
			vm->stack_capacity == 0 ||
			vm->stack_capacity < STACK_START_SIZE ?
			1 || STACK_START_SIZE : vm->stack_capacity * 2;
		vm->stack = realloc(vm->stack, new_capacity);
		vm->stack_capacity = new_capacity;
		vm->sp = vm->stack + size;
	}
	*(vm->sp++) = byte;
	++vm->stack_length;
	return FVMS_OK;
}

uint8_t fvm_machine_pop(fvm_machine *vm) {
	return *(--vm->sp);
}

fvm_status fvm_machine_do_op(fvm_machine *vm) {
	if (vm->halt) {
		return FVMS_OK;
	} else if (vm->ip - vm->instructions >= vm->inst_length) {
		return FVMS_IOB;
	}
	fvm_bytecode op = (fvm_bytecode)(*vm->ip);
	size_t arity = fvm_bytecode_arity(op);
	if (vm->ip - vm->instructions + arity >= vm->inst_length) {
		return FVMS_IOB;
	}
	size_t sarity = fvm_bytecode_sarity(op);
	if (sarity > vm->sp - vm->stack) {
		return FVMS_SU;
	}
	vm->ip++;
	switch (op) {
	case FVMI_NOP:
		break;
	case FVMI_PUSH8: {
		fvm_status push_status = fvm_machine_push(vm, *vm->ip);
		if (push_status != FVMS_OK) {
			return push_status;
		}
		break;
	}
	case FVMI_POP8: {
		fvm_machine_pop(vm);
		break;
	}
	case FVMI_ADD8: {
		uint8_t right = fvm_machine_pop(vm);
		uint8_t left = fvm_machine_pop(vm);
		fvm_machine_push(vm, left + right);
		break;
	}
	case FVMI_SUB8: {
		uint8_t right = fvm_machine_pop(vm);
		uint8_t left = fvm_machine_pop(vm);
		fvm_machine_push(vm, left - right);
		break;
	}
	case FVMI_MUL8: {
		uint8_t right = fvm_machine_pop(vm);
		uint8_t left = fvm_machine_pop(vm);
		fvm_machine_push(vm, left * right);
		break;
	}
	case FVMI_DIV8: {
		uint8_t right = fvm_machine_pop(vm);
		uint8_t left = fvm_machine_pop(vm);
		fvm_machine_push(vm, left / right);
		break;
	}
	case FVMI_MOD8: {
		uint8_t right = fvm_machine_pop(vm);
		uint8_t left = fvm_machine_pop(vm);
		fvm_machine_push(vm, left % right);
		break;
	}
	case FVMI_HALT: {
		vm->halt = 1;
		break;
	}
	default:
		// This shouldn't happen
		return FVMS_UNREACHABLE;
	}
	vm->ip += arity;
	return FVMS_OK;
}

fvm_status fvm_machine_execute(fvm_machine *vm) {
	while (!vm->halt) {
		fvm_status status = fvm_machine_do_op(vm);
		if (status != FVMS_OK) {
			return status;
		}
	}
	return FVMS_OK;
}
