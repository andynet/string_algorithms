#include <check.h>
#include <stdlib.h>
#include "../src/bmh.c"

START_TEST(empty_test){} END_TEST

Suite * test_suite(void){
    Suite *suite;
    TCase *core;

    suite = suite_create("test");
    core = tcase_create("core");
    tcase_add_test(core, empty_test);
    suite_add_tcase(suite, core);
    return (suite);
}

int main(void){
    int failed;
    Suite *suite;
    SRunner *runner;

    suite = test_suite();
    runner = srunner_create(suite);

    srunner_run_all(runner, CK_VERBOSE);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}
