#include <check.h>
#include <stdlib.h>
#include "../src/bmh.c"

START_TEST(empty_test){} END_TEST

START_TEST(no_match){
    ck_assert_int_eq(bmh("A", "BBB"), -1);
} END_TEST

START_TEST(match_at_the_beginning){
    ck_assert_int_eq(bmh("AB", "ABBBB"), 0);
} END_TEST

START_TEST(match_at_the_end){
    ck_assert_int_eq(bmh("AB", "BBBBAB"), 4);
} END_TEST

START_TEST(match_in_the_middle){
    ck_assert_int_eq(bmh("AB", "BBBABBBB"), 3);
} END_TEST

START_TEST(multiple_matches){
    ck_assert_int_eq(bmh("AB", "ABBAB"), 0);
    ck_assert_int_eq(bmh("AB", "ABBAB"), 3);
} END_TEST

START_TEST(multiple_overlapping_matches){
    ck_assert_int_eq(bmh("AAA", "AAAA"), 0);
    ck_assert_int_eq(bmh("AAA", "AAAA"), 1);
} END_TEST

Suite * test_suite(void){
    Suite *suite;
    TCase *core;

    suite = suite_create("test");
    core = tcase_create("core");
    tcase_add_test(core, empty_test);
    tcase_add_test(core, no_match);
    tcase_add_test(core, match_at_the_beginning);
    tcase_add_test(core, match_at_the_end);
    tcase_add_test(core, match_in_the_middle);
    tcase_add_test(core, multiple_matches);
    tcase_add_test(core, multiple_overlapping_matches);
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
