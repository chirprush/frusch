#include <stdint.h>
#include "fvm_bytecode.h"

uint32_t fvm_bytecode_arity(fvm_bytecode op) {
	switch (op) {
		case FVMI_NOP: return 0;
		case FVMI_PUSH8: return 1;
		case FVMI_HALT: return 0;
		default:
			// This shouldn't happen
			return 0;
	}
}
