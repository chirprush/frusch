#include "frusch_bytecodes.h"
#include "frusch_vm.h"
#include "frusch_int.h"

Vm vm_new(u32 *program, u32 program_size) {
	Vm vm = {0};
	vm.program = program;
	vm.program_size = program_size;
	return vm;
}

s32 vm_execute(Vm *vm) {
	if (vm->ip >= vm->program_size) {
		return ERR_BOUNDS;
	}
	switch (vm->program[vm->ip++]) {
	case OP_NOP:
		break;
	case OP_HALT:
		vm->halt = 1;
		break;
	}
	return STATUS_OK;
}

s32 vm_run(Vm *vm) {
	while (!vm->halt) {
		s32 result = vm_execute(vm);
		if (result != STATUS_OK) {
			return result;
		}
	}
	return STATUS_OK;
}
