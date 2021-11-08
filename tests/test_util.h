#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include <stdio.h>
#include <stdlib.h>

typedef enum test_result_type {
	TEST_TRUE,
	TEST_FALSE,
	TEST_EQ,
	TEST_NE,
	TEST_FAIL,
	TEST_PASS
} test_result_type;

typedef struct test_result {
	test_result_type type;
	int left;
	int right;
	const char *expr_left;
	const char *expr_right;
	size_t line;
	const char *file;
} test_result;

#define tassert(expr) return (test_result) { .type = TEST_TRUE, .left = (expr), .right = 0, .expr_left = #expr, .expr_right = NULL, .line =  __LINE__, .file = __FILE__ };
#define tnassert(expr) return (test_result) { .type = TEST_FALSE, .left = (expr), .right = 0, .expr_left = #expr, .expr_right = NULL, .line =  __LINE__, .file = __FILE__ };
#define tassert_eq(_left, _right) return (test_result) { .type = TEST_EQ, .left = (_left), .right = (_right), .expr_left = #_left, .expr_right = #_right, .line = __LINE__, .file = __FILE__ };
#define tassert_ne(_left, _right) return (test_result) { .type = TEST_NE, .left = (_left), .right = (_right), .expr_left = #_left, .expr_right = #_right, .line = __LINE__, .file = __FILE__ };
#define tfail() return (test_result) { .type = TEST_FAIL, .left = 0, .right = 0, .expr_left = NULL, .expr_right = NULL, .line = __LINE__, .file = __FILE__ };
#define tpass() return (test_result) { .type = TEST_PASS, .left = 0, .right = 0, .expr_left = NULL, .expr_right = NULL, .line = __LINE__, .file = __FILE__ };

unsigned char test_result_passed(const test_result *result) {
	switch (result->type) {
	case TEST_TRUE:
		return result->left;
	case TEST_FALSE:
		return !result->left;
	case TEST_EQ:
		return result->left == result->right;
	case TEST_NE:
		return result->left != result->right;
	case TEST_FAIL:
		return 0;
	case TEST_PASS:
		return 1;
	default:
		return 0;
	}
}

#define RED "\e[31m"
#define GREEN "\e[32m"
#define YELLOW "\e[33m"
#define BLUE "\e[34m"
#define PURPLE "\e[35m"

void test_result_print(const test_result *result, unsigned char passed, const char *name) {
	const char *pass_message = passed ? "passed" : "failed";
	const char *pass_color = passed ? GREEN : RED;
	printf("\n %sIn\e[0m %s%s\e[0m:%s%ld\e[0m %s%s\e[0m(): %stest %s\e[0m\n", PURPLE, GREEN, result->file, YELLOW, result->line, BLUE, name, pass_color, pass_message);
	if (result->type == TEST_TRUE || result->type == TEST_FALSE) {
		printf("   %sGot\e[0m %s%s\e[0m (%s%d\e[0m)\n", PURPLE, pass_color, result->expr_left, YELLOW, result->left);
	} else if (result->type == TEST_EQ || result->type == TEST_NE) {
		printf("   %sGot\e[0m %s%s\e[0m (%s%d\e[0m)\n", PURPLE, pass_color, result->expr_left, YELLOW, result->left);
		printf("   %sExpected\e[0m %s%s\e[0m (%s%d\e[0m)\n", PURPLE, GREEN, result->expr_right, YELLOW, result->right);
	}
}

typedef test_result (*test_func)();

struct test_entry {
	test_func func;
	const char *name;
};

#define test_entry(name) { (name), #name }

typedef struct test_context {
	struct test_entry *entries;
	size_t length;
	int passed;
	int failed;
} test_context;

void test_context_start(test_context *context) {
	printf("%sRunning\e[0m %s%ld\e[0m %stests\e[0m:\n", PURPLE, YELLOW, context->length, PURPLE);
}

void test_context_run(test_context *context, size_t i) {
	struct test_entry *entry = &context->entries[i];
	test_result result = entry->func();
	unsigned char passed = test_result_passed(&result);
	test_result_print(&result, passed, entry->name);
	if (passed) {
		context->passed++;
	} else {
		context->failed++;
	}
}

void test_context_end(test_context *context) {
	printf("\n%sResults\e[0m: %s%d passed\e[0m, %s%d failed\e[0m\n", PURPLE, GREEN, context->passed, RED, context->failed);
}

#endif // TEST_UTIL_H
