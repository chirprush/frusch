#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <frusch/frusch_ast.h>

#include "test_util.h"

test_result test_init_error() {
	char *message = strdup("error message");
	frusch_node *error = frusch_node_error(message);
	test_result result = tassert_ne(error, NULL);
	frusch_node_free(error);
	return result;
}

test_result test_init_int() {
	frusch_node *value = frusch_node_int(3);
	test_result result = tassert_ne(value, NULL);
	frusch_node_free(value);
	return result;
}

test_result test_init_var() {
	char *ident = strdup("identifier");
	frusch_node *var = frusch_node_var(ident);
	test_result result = tassert_ne(var, NULL);
	frusch_node_free(var);
	return result;
}

test_result test_init_binexpr() {
	frusch_node *left = frusch_node_int(3);
	frusch_node *right = frusch_node_var(strdup("test"));
	frusch_node_bin_expr *bin_expr = frusch_node_bin_expr_new(
		left,
		right,
		OP_ADD
	);
	frusch_node *expr_node = frusch_node_binexpr(bin_expr);
	test_result result = tassert_ne(expr_node, NULL);
	frusch_node_free(expr_node);
	return result;
}

test_result test_init_call() {
	frusch_node *func = frusch_node_var(strdup("abcdefghijkl012345"));
	frusch_node_list *args = frusch_node_list_new();
	frusch_node_call_expr *call_expr = frusch_node_call_expr_new(func, args);
	frusch_node *call_node = frusch_node_call(call_expr);
	test_result result = tassert_ne(call_node, NULL);
	frusch_node_free(call_node);
	return result;
}

int main(int argc, char *argv[]) {
	struct test_entry entries[] = {
		test_entry(test_init_error),
		test_entry(test_init_int),
		test_entry(test_init_var),
		test_entry(test_init_binexpr),
		test_entry(test_init_call)
	};
	size_t length = sizeof(entries) / sizeof(entries[0]);
	test_context context = {0};
	context.entries = entries;
	context.length = length;
	test_context_start(&context);
	for (size_t i = 0; i < length; ++i) {
		test_context_run(&context, i);
	}
	test_context_end(&context);
	if (context.failed) {
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
