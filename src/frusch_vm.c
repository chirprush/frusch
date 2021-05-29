#include "frusch_bytecodes.h"
#include "frusch_vm.h"
#include "frusch_int.h"

#define CHECK_PROG_BOUNDS() if (vm->ip >= vm->program_size) { return ERR_BOUNDS; }
#define CHECK_STACK_BOUNDS() if (vm->sp >= STACK_SIZE) { return ERR_OVERFLOW; }
#define READ_BYTE() (vm->program[vm->ip++])

Vm vm_new(u32 *program, u32 program_size) {
	Vm vm = {0};
	vm.program = program;
	vm.program_size = program_size;
	return vm;
}

s32 vm_execute(Vm *vm) {
	CHECK_PROG_BOUNDS();
	switch (vm->program[vm->ip++]) {
	case OP_NOP:
		break;
	case OP_HALT:
		vm->halt = 1;
		break;
	case OP_PUSH:
		CHECK_PROG_BOUNDS();
		u32 n = READ_BYTE();
		CHECK_STACK_BOUNDS();
		vm->stack[vm->sp++] = n;
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
