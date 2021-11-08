#include <stdio.h>
#include <stdlib.h>

#include "test_util.h"

test_result test_addition() {
	tassert_eq(1 + 1, 2);
}

test_result test_not() {
	tnassert(1);
}

test_result test_not_equal() {
	tassert_ne(3 / 3, 1);
}

test_result test_fail() {
	tassert(0);
}

int main(int argc, char *argv[]) {
	struct test_entry entries[] = {
		test_entry(test_addition),
		test_entry(test_not),
		test_entry(test_not_equal),
		test_entry(test_fail)
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
