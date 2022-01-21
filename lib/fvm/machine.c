#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fvm/machine.h>
#include <fvm/bytecode.h>
#include <fvm/status.h>

#define FVM_CHUNK_SIZE 4096

fvm_machine *fvm_machine_new(const uint8_t *instructions, uint32_t inst_length) {
	fvm_machine *vm = malloc(sizeof(fvm_machine));
	vm->stack = malloc(FVM_CHUNK_SIZE);
	vm->stack_capacity = FVM_CHUNK_SIZE;
	vm->sp = vm->stack - 1;
	vm->instructions = instructions;
	vm->inst_length = inst_length;
	vm->ip = vm->instructions;
	vm->halt = false;
	return vm;
}

void fvm_machine_free(fvm_machine *vm) {
	free(vm->stack);
	free(vm);
}

fvm_status fvm_machine_push(fvm_machine *vm, uint8_t byte) {
	uint64_t size = vm->sp + 1 - vm->stack;
	if (size >= vm->stack_capacity) {
		uint32_t new_capacity = vm->stack_capacity + FVM_CHUNK_SIZE;
		vm->stack = realloc(vm->stack, new_capacity);
		vm->stack_capacity = new_capacity;
		vm->sp = vm->stack + size - 1;
	}
	*(++vm->sp) = byte;
	return FVMS_OK;
}

uint8_t fvm_machine_pop(fvm_machine *vm) {
	return *(vm->sp--);
}

fvm_status fvm_machine_do_op(fvm_machine *vm) {
	if (vm->halt) {
		return FVMS_OK;
	} else if (vm->ip - vm->instructions >= vm->inst_length) {
		return FVMS_IOB;
	}
	fvm_bytecode op = (fvm_bytecode)(*vm->ip);
	uint32_t arity = fvm_bytecode_arity(op);
	if (vm->ip - vm->instructions + arity >= vm->inst_length) {
		return FVMS_IOB;
	}
	uint32_t stack_arity = fvm_bytecode_stack_arity(op);
	if (stack_arity > vm->sp + 1 - vm->stack) {
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
		vm->halt = true;
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
