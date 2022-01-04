#include <stdlib.h>
#include <stdint.h>

#include <fvm/bytecode.h>

size_t fvm_bytecode_arity(fvm_bytecode op) {
	switch (op) {
	case FVMI_NOP: return 0;
	case FVMI_PUSH8: return 1;
	case FVMI_POP8: return 0;
	case FVMI_ADD8: return 0;
	case FVMI_SUB8: return 0;
	case FVMI_MUL8: return 0;
	case FVMI_DIV8: return 0;
	case FVMI_MOD8: return 0;
	case FVMI_HALT: return 0;
	default:
		// This shouldn't happen
		return 0;
	}
}

size_t fvm_bytecode_sarity(fvm_bytecode op) {
	switch (op) {
	case FVMI_NOP: return 0;
	case FVMI_PUSH8: return 0;
	case FVMI_POP8: return 1;
	case FVMI_ADD8: return 2;
	case FVMI_SUB8: return 2;
	case FVMI_MUL8: return 2;
	case FVMI_DIV8: return 2;
	case FVMI_MOD8: return 2;
	case FVMI_HALT: return 0;
	default:
		// This shouldn't happen
		return 0;
	}
}
