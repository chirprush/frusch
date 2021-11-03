#ifndef FVM_BYTECODE_H
#define FVM_BYTECODE_H

#include <stdint.h>

typedef enum fvm_bytecode {
	FVMI_NOP,
	FVMI_PUSH8,
	FVMI_HALT
} fvm_bytecode;

uint32_t fvm_bytecode_arity(fvm_bytecode op);

#endif // FVM_BYTECODE_H
