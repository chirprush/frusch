#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fvm/status.h>
#include <fvm/machine.h>

#include "test_util.h"

test_result test_instruction_out_of_bounds() {
	const uint8_t instructions[] = {
		FVMI_PUSH8,
	};
	fvm_machine *vm = fvm_machine_new(instructions, sizeof(instructions) / sizeof(instructions[0]));
	fvm_status status = fvm_machine_execute(vm);
	test_result result = tassert_eq(status, FVMS_IOB);
	fvm_machine_free(vm);
	return result;
}

test_result test_stack_underflow() {
	const uint8_t instructions[] = {
		FVMI_PUSH8, 3,
		FVMI_ADD8,
		FVMI_HALT,
	};
	fvm_machine *vm = fvm_machine_new(instructions, sizeof(instructions) / sizeof(instructions[0]));
	fvm_status status = fvm_machine_execute(vm);
	test_result result = tassert_eq(status, FVMS_SU);
	fvm_machine_free(vm);
	return result;
}

test_result test_all_ops() {
	const uint8_t instructions[] = {
		FVMI_PUSH8, 3,
		FVMI_PUSH8, 5,
		FVMI_ADD8,
		FVMI_PUSH8, 2,
		FVMI_PUSH8, 5,
		FVMI_POP8,
		FVMI_DIV8,
		FVMI_PUSH8, 27,
		FVMI_MUL8,
		FVMI_PUSH8, 2,
		FVMI_SUB8,
		FVMI_PUSH8, 5,
		FVMI_MOD8,
		FVMI_HALT,
	};
	fvm_machine *vm = fvm_machine_new(instructions, sizeof(instructions) / sizeof(instructions[0]));
	fvm_status status = fvm_machine_execute(vm);
	test_result result = tassert(status == FVMS_OK && *vm->sp);
	fvm_machine_free(vm);
	return result;
}

int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;
	struct test_entry entries[] = {
		test_entry(test_instruction_out_of_bounds),
		test_entry(test_stack_underflow),
		test_entry(test_all_ops)
	};
	size_t length = sizeof(entries) / sizeof(entries[0]);
	test_context context = {0};
	context.entries = entries;
	context.length = length;
	test_context_start(&context);
	for (size_t i = 0; i < length; ++i) {
		test_context_run(&context, i);
	}
	test_context_end(&context);
	if (context.failed) {
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
