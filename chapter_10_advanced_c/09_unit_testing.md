# 10.9 Unit Testing in C

C has no built-in test runner. No `pytest`, no `jest`, no `cargo test`. You build your own safety net.

## Quick and Dirty: `assert.h`

For small projects and rapid prototyping, the standard `assert()` macro is sufficient. If the condition is false, the program immediately aborts and prints the failing expression, file, and line number.

```c
#include <stdio.h>
#include <assert.h>

int add(int a, int b) { return a + b; }

int main(void) {
    assert(add(2, 2) == 4);     // PASS — continues silently.
    assert(add(-1, 1) == 0);    // PASS.
    assert(add(0, 0) == 0);     // PASS.
    
    printf("All tests passed!\n");
    return 0;
}
```

If any assertion fails:
```
program: main.c:8: main: Assertion `add(2, 2) == 5' failed.
Aborted (core dumped)
```

## Professional Framework: Unity

For real projects, use a proper testing framework like **Unity** (ThrowTheSwitch/Unity). It provides structured test suites, setup/teardown hooks, and rich failure messages.

```c
#include "unity.h"
#include "my_math.h"

void setUp(void) {}     // Runs before each test.
void tearDown(void) {}  // Runs after each test.

void test_add_positive_numbers(void) {
    TEST_ASSERT_EQUAL_INT(7, add(3, 4));
}

void test_add_negative_numbers(void) {
    TEST_ASSERT_EQUAL_INT(0, add(-1, 1));
}

void test_array_equality(void) {
    int expected[] = {1, 2, 3};
    int actual[]   = {1, 2, 3};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, 3);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_add_positive_numbers);
    RUN_TEST(test_add_negative_numbers);
    RUN_TEST(test_array_equality);
    return UNITY_END();
}
```

## Project Structure Best Practice

```
my_project/
├── src/
│   ├── main.c
│   ├── math_utils.c
│   └── math_utils.h
├── tests/
│   └── test_math_utils.c
├── Makefile
└── README.md
```

Your Makefile should have a `make test` target that compiles and runs your test suite automatically.

> **Veteran Rule:** Write tests *before* you consider a function "done." In C, a function that compiles is not a function that works. Tests prove correctness. Valgrind proves safety.
