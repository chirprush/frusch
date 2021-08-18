#include <stdio.h>
#include "fvm_bytecodes.h"
#include "fvm_vm.h"
#include "fvm_int.h"

int main(int argc, char *argv[]) {
	u32 program[] = {
		OP_PUSH, 3,
		OP_HALT,
	};
	u32 program_size = sizeof(program) / sizeof(u32);
	Vm vm = vm_new(program, program_size);
	s32 result = vm_execute(&vm);
	printf("%d\n", result);
	return 0;
}
