#include <stdio.h>
#include "fvm_int.h"
#include "fvm_machine.h"
#include "fvm_bytecode.h"
#include "fvm_status.h"

int main(int argc, char *argv[]) {
	const u8 instructions[] = {
		FVMI_PUSH8, 2,
		FVMI_PUSH8, 3,
		FVMI_HALT
	};
	fvm_machine *vm = fvm_machine_new(instructions, sizeof(instructions) / sizeof(u8));
	fvm_status status = fvm_machine_execute(vm);
	printf("%d\n", status);
	printf("%d\n", *vm->stack);
	return 0;
}
