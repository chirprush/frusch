#ifndef FVM_BYTECODE_H
#define FVM_BYTECODE_H

#include "fvm_int.h"

typedef enum fvm_bytecode {
	FVMI_NOP,
	FVMI_PUSH8,
	FVMI_HALT
} fvm_bytecode;

u32 fvm_bytecode_arity(fvm_bytecode op);

#endif // FVM_BYTECODE_H
