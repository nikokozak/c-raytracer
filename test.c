#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "my_function.h"

static void test_adds_correctly(void **state)
{
    int result = add(1, 2);
    assert_int_equal(result, 3);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_adds_correctly)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
