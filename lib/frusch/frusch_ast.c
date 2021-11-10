#include <stdlib.h>

#include "frusch_ast.h"

frusch_node_bin_expr *frusch_node_bin_expr_new(frusch_node *left, frusch_node *right, frusch_node_op op) {
	frusch_node_bin_expr *expr = malloc(sizeof(frusch_node_bin_expr));
	expr->left = left;
	expr->right = right;
	expr->op = op;
	return expr;
}

void frusch_node_bin_expr_free(frusch_node_bin_expr *expr) {
	frusch_node_free(expr->left);
	frusch_node_free(expr->right);
	free(expr);
}

frusch_node_list *frusch_node_list_new() {
	frusch_node_list *list = malloc(sizeof(frusch_node_list));
	list->nodes = NULL;
	list->length = 0;
	list->capacity = 0;
	return list;
}

void frusch_node_list_free(frusch_node_list *list) {
	if (list->nodes != NULL) {
		free(list->nodes);
	}
	free(list);
}

frusch_node_call_expr *frusch_node_call_expr_new(frusch_node *func, frusch_node_list *args) {
	frusch_node_call_expr *call = malloc(sizeof(frusch_node_call_expr));
	call->func = func;
	call->args = args;
	return call;
}

void frusch_node_call_expr_free(frusch_node_call_expr *call) {
	frusch_node_free(call->func);
	if (call->args != NULL || call->args->length == 0) {
		frusch_node_list_free(call->args);
	}
	free(call);
}

frusch_node *frusch_node_error(char *value) {
	frusch_node *node = malloc(sizeof(frusch_node));
	node->type = NODE_ERR;
	node->as_err = value;
	return node;
}

frusch_node *frusch_node_int(uint32_t value) {
	frusch_node *node = malloc(sizeof(frusch_node));
	node->type = NODE_INT;
	node->as_int = value;
	return node;
}

frusch_node *frusch_node_var(char *value) {
	frusch_node *node = malloc(sizeof(frusch_node));
	node->type = NODE_VAR;
	node->as_var = value;
	return node;
}

frusch_node *frusch_node_binexpr(frusch_node_bin_expr *value) {
	frusch_node *node = malloc(sizeof(frusch_node));
	node->type = NODE_BIN_EXPR;
	node->as_bin_expr = value;
	return node;
}

frusch_node *frusch_node_call(frusch_node_call_expr *value) {
	frusch_node *node = malloc(sizeof(frusch_node));
	node->type = NODE_CALL;
	node->as_call = value;
	return node;
}

void frusch_node_free(frusch_node *node) {
	switch (node->type) {
	case NODE_ERR:
		free(node->as_err);
		break;
	case NODE_INT:
		break;
	case NODE_VAR:
		free(node->as_var);
		break;
	case NODE_BIN_EXPR:
		frusch_node_bin_expr_free(node->as_bin_expr);
		break;
	case NODE_CALL:
		frusch_node_call_expr_free(node->as_call);
		break;
	}
	free(node);
}
