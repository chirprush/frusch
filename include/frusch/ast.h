#pragma once

#include <stdint.h>

// TODO: Add NODE_PTR, NODE_CHAR, NODE_STR, NODE_UN_EXPR, and NODE_REF
typedef enum frusch_node_type {
	NODE_ERR,
	NODE_INT,
	NODE_VAR,
	NODE_BIN_EXPR,
	NODE_CALL
} frusch_node_type;

typedef enum frusch_node_op {
	OP_ADD,
	OP_SUB,
	OP_MUL,
	OP_DIV,
	OP_MOD
} frusch_node_op;

typedef struct frusch_node_bin_expr {
	struct frusch_node *left;
	struct frusch_node *right;
	frusch_node_op op;
} frusch_node_bin_expr;

frusch_node_bin_expr *frusch_node_bin_expr_new(struct frusch_node *left, struct frusch_node *right, frusch_node_op op);
void frusch_node_bin_expr_free(frusch_node_bin_expr *expr);

typedef struct frusch_node_list {
	struct frusch_node *nodes;
	uint32_t length;
	uint32_t capacity;
} frusch_node_list;

frusch_node_list *frusch_node_list_new();
void frusch_node_list_free(frusch_node_list *list);

typedef struct frusch_node_call_expr {
	struct frusch_node *func;
	frusch_node_list *args;
} frusch_node_call_expr;

frusch_node_call_expr *frusch_node_call_expr_new(struct frusch_node *func, frusch_node_list *args);
void frusch_node_call_expr_free(frusch_node_call_expr *call);

typedef struct frusch_node {
	frusch_node_type type;
	union {
		// NOTE: All pointers stored in frusch_node should be owned, allocated strings
		char *as_err;
		uint32_t as_int;
		char *as_var;
		frusch_node_bin_expr *as_bin_expr;
		frusch_node_call_expr *as_call;
	};
} frusch_node;

frusch_node *frusch_node_error(char *value);
frusch_node *frusch_node_int(uint32_t value);
frusch_node *frusch_node_var(char *value);
frusch_node *frusch_node_binexpr(frusch_node_bin_expr *value);
frusch_node *frusch_node_call(frusch_node_call_expr *value);
void frusch_node_free(frusch_node *node);
