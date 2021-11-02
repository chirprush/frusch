#ifndef FRUSCH_AST_H
#define FRUSCH_AST_H

#include "fvm_int.h"

// TODO: Add NODE_PTR, NODE_CHAR, NODE_STR, NODE_UN_EXPR, and NODE_REF
typedef enum frusch_node_type {
	NODE_ERROR,
	NODE_INT,
	NODE_VAR,
	NODE_BIN_EXPR,
	NODE_CALL
} frusch_node_type;

typedef struct frusch_node_bin_expr {
	struct frusch_node *left;
	struct frusch_node *right;
	char *op;
} frusch_node_bin_expr;

typedef struct frusch_node_call_expr {
	struct frusch_node *func;
	struct frusch_node *args;
	u8 args_length;
} frusch_node_call_expr;

typedef struct frusch_node {
	frusch_node_type type;
	union {
		// NOTE: All strings stored in frusch_node should be owned, allocated strings
		char *as_error;
		u32 as_int;
		char *as_var;
		frusch_node_bin_expr *as_bin_expr;
		frusch_node_call_expr *as_call;
	} unwrap;
} frusch_node;

frusch_node *frusch_node_error(char *value);
frusch_node *frusch_node_int(u32 value);
frusch_node *frusch_node_var(char *value);
frusch_node *frusch_node_call(frusch_node_call_expr *value);
frusch_node *frusch_node_free(frusch_node *node);

#endif // FRUSCH_AST_H
