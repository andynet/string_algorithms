#include <check.h>
#include <stdlib.h>
#include "../src/suffix_array.h"

START_TEST(test_concat){
    ck_assert_str_eq(concat("A", "B"), "AB");
} END_TEST

START_TEST(test_concat_empty_strings){
    ck_assert_str_eq(concat("", ""), "");
} END_TEST

Suite * test_suite(void){
    Suite *suite;
    TCase *core;

    suite = suite_create("somename");
    core = tcase_create("core");
    tcase_add_test(core, test_concat);
    tcase_add_test(core, test_concat_empty_strings);
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

