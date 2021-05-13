#ifndef FRUSCH_BYTECODES_H
#define FRUSCH_BYTECODES_H

typedef enum Statuscode {
	STATUS_OK = 0,
	ERR_BOUNDS = -1,
} Statuscode;

typedef enum Bytecode {
	OP_NOP = 0,
	OP_HALT,
} Bytecode;

#endif /* FRUSCH_BYTECODES_H */
