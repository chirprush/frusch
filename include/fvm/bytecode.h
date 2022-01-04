#ifndef FVM_BYTECODE_H
#define FVM_BYTECODE_H

#include <stdlib.h>
#include <stdint.h>

typedef enum fvm_bytecode {
	FVMI_NOP,
	FVMI_PUSH8,
	FVMI_POP8,
	FVMI_ADD8,
	FVMI_SUB8,
	FVMI_MUL8,
	FVMI_DIV8,
	FVMI_MOD8,
	FVMI_HALT
} fvm_bytecode;

size_t fvm_bytecode_arity(fvm_bytecode op);
size_t fvm_bytecode_sarity(fvm_bytecode op);

#endif // FVM_BYTECODE_H
