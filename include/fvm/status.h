#pragma once

typedef enum fvm_status {
	FVMS_OK = 0,
	FVMS_IOB, /* Instructions Out of Bounds */
	FVMS_UNREACHABLE, /* Unreachable code */
	FVMS_SO, /* Stack overflow */
	FVMS_SU, /* Stack underflow */
} fvm_status;
