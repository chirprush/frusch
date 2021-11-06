#include <stdio.h>
#include <stdint.h>
#include <fvm/fvm_machine.h>
#include <fvm/fvm_bytecode.h>
#include <fvm/fvm_status.h>

int main(int argc, char *argv[]) {
	const uint8_t instructions[] = {
		FVMI_PUSH8, 2,
		FVMI_PUSH8, 3,
		FVMI_HALT
	};
	fvm_machine *vm = fvm_machine_new(instructions, sizeof(instructions) / sizeof(uint8_t));
	fvm_status status = fvm_machine_execute(vm);
	printf("%d\n", status);
	printf("%d\n", *vm->stack);
	return 0;
}
