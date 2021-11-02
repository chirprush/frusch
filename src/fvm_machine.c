#include <stdlib.h>
#include "fvm_machine.h"
#include "fvm_bytecode.h"
#include "fvm_status.h"
#include "fvm_int.h"

fvm_machine *fvm_machine_new(const u8 *instructions, u32 inst_length) {
	fvm_machine *vm = malloc(sizeof(fvm_machine));
	vm->sp = vm->stack;
	vm->instructions = instructions;
	vm->inst_length = inst_length;
	vm->ip = vm->instructions;
	vm->halt = 0;
	return vm;
}

fvm_status fvm_machine_push(fvm_machine *vm, u8 byte) {
	if (vm->sp - vm->stack >= STACK_SIZE) {
		return FVMS_SO;
	}
	*(vm->sp++) = byte;
	return FVMS_OK;
}

fvm_status fvm_machine_do_op(fvm_machine *vm) {
	if (vm->halt) {
		return FVMS_OK;
	} else if (vm->ip - vm->instructions >= vm->inst_length) {
		return FVMS_IOB;
	}
	fvm_bytecode op = (fvm_bytecode)(*vm->ip);
	u32 arity = fvm_bytecode_arity(op);
	if (vm->ip - vm->instructions + arity >= vm->inst_length) {
		return FVMS_IOB;
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
		case FVMI_HALT:
			vm->halt = 1;
			break;
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
