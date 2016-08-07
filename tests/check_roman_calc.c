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
  /* Test for correct symbols */
  ck_assert_int_eq (roman_number_check ("MDCCLXXVII"), SUCCESS);
  ck_assert_int_eq (roman_number_check ("MCLXXVII1"), ERROR);
  /* Test for more than 3 symbols in a row */
  ck_assert_int_eq (roman_number_check ("IIII"), ERROR);
  /* Test for more than 1 of V,L,D in a row */
  ck_assert_int_eq (roman_number_check ("XVV"), ERROR);
  /* Test for a prefix and postfix at the same time */
  ck_assert_int_eq (roman_number_check ("IXV"), ERROR);
  /* Test if the prefix is V,L or D */
  ck_assert_int_eq (roman_number_check ("DMVX"), ERROR);
  /* Test for prefix for a symbol if in the same range */
  ck_assert_int_eq (roman_number_check ("CCID"), ERROR);
  /* Test if prefix of a symbol is not the same range as postfix */
  ck_assert_int_eq (roman_number_check ("CMV"), SUCCESS);
}
END_TEST

START_TEST (test_roman_number_add)
{
  /* Simple test */
  ck_assert_str_eq (roman_number_add ("MLX", "VI", result), "MLXVI");
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

  /* Addition test cases */
  TCase *tc_roman_add = tcase_create ("Add");
  tcase_add_checked_fixture (tc_roman_add, setup, teardown);
  tcase_add_test (tc_roman_add, test_roman_number_add);
  suite_add_tcase (s, tc_roman_add);

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
