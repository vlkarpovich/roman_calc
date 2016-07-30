#include <stdlib.h>
#include <check.h>
#include "../src/roman_calc.h"
char *result;

void
setup (void)
{
  result = calloc (ROMAN_NUM_MAX_LEN, sizeof (char));
}

void
teardown (void)
{
  if (result) {
    free (result);
  }
  result = NULL;
}

START_TEST (test_roman_number_check)
{
  ck_assert_int_eq (roman_number_check ("MDCCLXXVII"), SUCCESS);
  ck_assert_int_eq (roman_number_check ("MCLXXVII1"), ERROR);
}
END_TEST

Suite * roman_calc_suite (void)
{
  Suite *s = suite_create ("RomanCalc");

  /* Check Roman Numerical format */
  TCase *tc_roman_format = tcase_create ("Format");
  tcase_add_checked_fixture (tc_roman_format, setup, teardown);
  tcase_add_test (tc_roman_format, test_roman_number_check);
  suite_add_tcase (s, tc_roman_format);

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
