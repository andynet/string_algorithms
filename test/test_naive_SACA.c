#include <check.h>
#include "../src/naive_SACA.c"

START_TEST(first_test)
{
    ck_assert_str_eq("", "");
}
END_TEST

Suite * test_suite(void){
    Suite *suite;
    TCase *core;

    suite = suite_create("somename");
    core = tcase_create("core");
    tcase_add_test(core, first_test);
    suite_add_tcase(suite, core);
    return (suite);
}

int main(void){
    int failed;
    Suite *suite;
    SRunner *runner;

    suite = test_suite();
    runner = srunner_create(suite);

    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}

