#include <stdlib.h>
#include <check.h>
#include "../src/roman_calc.h"
char *result;

void
setup (void)
{
  result = calloc (20, sizeof (char));
}

void
teardown (void)
{
  if (result)
    free (result);
  result = NULL;
}

START_TEST (test_roman_number_check)
{
  /* Test for all correct symbals */
  ck_assert_int_eq (roman_number_check ("MDCLXVI"), SUCCESS);
  /* Test for a long number */
  ck_assert_int_eq (roman_number_check ("MMMDCCCLXXXVIII"), SUCCESS);
  ck_assert_int_eq (roman_number_check ("MMMCDLXXXIV"), SUCCESS);
  /* Test for more than 3 symbols in a row */
  ck_assert_int_eq (roman_number_check ("XIIII"), ERROR);
  /* Test for more than 1 V,L,D in a row */
  ck_assert_int_eq (roman_number_check ("VV"), ERROR);
  /* Test to a wrong symbol */
  ck_assert_int_eq (roman_number_check ("12MIXI"), ERROR);
  /* Test to a wrong prefix */
  ck_assert_int_eq (roman_number_check ("CCID"), ERROR);
  ck_assert_int_eq (roman_number_check ("CCDXXL"), ERROR);
  /* Test to prefix and postfix at the same time */
  ck_assert_int_eq (roman_number_check ("CCDXLX"), ERROR);
}
END_TEST

START_TEST (test_roman_number_add)
{
  ck_assert_str_eq (roman_number_add ("I", "I", result), "II");
}
END_TEST

START_TEST (test_roman_number_sub)
{
  ck_assert_str_eq (roman_number_sub ("II", "I", result), "I");
}
END_TEST

START_TEST (test_roman_number_sub_nulla)
{
  ck_assert_str_eq (roman_number_sub ("III", "III", result), ZERO);
}
END_TEST

Suite * roman_calc_suite (void)
{
  Suite *s = suite_create ("RomanCalc");

  /* Check number format test case */
  TCase *tc_roman_format = tcase_create ("Format");
  tcase_add_checked_fixture (tc_roman_format, setup, teardown);
  tcase_add_test (tc_roman_format, test_roman_number_check);
  suite_add_tcase (s, tc_roman_format);

  /* Addition test cases */
  TCase *tc_roman_add = tcase_create ("Add");
  tcase_add_checked_fixture (tc_roman_add, setup, teardown);
  tcase_add_test (tc_roman_add, test_roman_number_add);
  suite_add_tcase (s, tc_roman_add);

  /* Subtraction test cases */
  TCase *tc_roman_sub = tcase_create ("Sub");
  tcase_add_checked_fixture (tc_roman_sub, setup, teardown);
  tcase_add_test (tc_roman_sub, test_roman_number_sub);
  tcase_add_test (tc_roman_sub, test_roman_number_sub_nulla);
  suite_add_tcase (s, tc_roman_sub);

  return s;
}

int
main (void)
{
  int number_failed;
  Suite *s = roman_calc_suite ();
  SRunner *sr = srunner_create (s);
  srunner_run_all (sr, CK_NORMAL);
  number_failed = srunner_ntests_failed (sr);
  srunner_free (sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
