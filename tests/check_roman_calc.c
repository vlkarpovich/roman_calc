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
  if (result)
    {
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
  /* Test if prefix of a symbol is in the same range as the symbol */
  ck_assert_int_eq (roman_number_check ("MDCCXLIII"), SUCCESS);
}
END_TEST

START_TEST (test_roman_number_add)
{
  /* Simple test */
  ck_assert_str_eq (roman_number_add ("MLX", "VI", result), "MLXVI");
  /*  Test addition of bigger number to smaller */
  ck_assert_str_eq (roman_number_add ("VI", "MDCLX", result), "MDCLXVI");
  /* If the numeral is I,X or C you can't have more than three */
  ck_assert_str_eq (roman_number_add ("II", "II", result), "IV");
 /* Add large numbers */
  ck_assert_str_eq (roman_number_add ("MDCCXLIII", "MCIX", result), "MMDCCCLII");
 /* The result is bigger than Romans can count */
  ck_assert_str_eq (roman_number_add ("MMDCCXLIII", "MDCCXLIII", result), INFINITY);
 /* Test insane input values */
  ck_assert_ptr_eq ((void*)roman_number_add ("MMDCIIIIIS","IDDFFSSII", result), NULL );
}
END_TEST

START_TEST (test_roman_number_sub)
{
  /* Simple test */
  ck_assert_str_eq (roman_number_sub ("II", "I", result), "I");
  /* Subtract a small number from a large number */
  ck_assert_str_eq (roman_number_sub ("MMM", "I", result), "MMCMXCIX");
  /* Use large numbers */
  ck_assert_str_eq (roman_number_sub ("MMDCCXLIII", "MCCXLIX", result), "MCDXCIV");
  /* Test for a negative result */
  ck_assert_str_eq (roman_number_sub ("XIX", "CXC", result), NEGATIVE);
  /* Check for the zero value result */
  ck_assert_str_eq (roman_number_sub ("MCMXCIV", "MCMXCIV", result), ZERO);
 /* Test insane input values */
  ck_assert_ptr_eq ((void*)roman_number_sub ("", "BADNUMBER", result), NULL );
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

  /* Subtraction test cases */
  TCase *tc_roman_sub = tcase_create ("Sub");
  tcase_add_checked_fixture (tc_roman_sub, setup, teardown);
  tcase_add_test (tc_roman_sub, test_roman_number_sub);
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
