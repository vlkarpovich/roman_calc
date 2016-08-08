#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "roman_calc.h"

/*
* Roman Numeral Calculator
*/

int
main (int argc, char *argv[])
{
  char result[128];
  if (argc != 4)
    {
      fprintf (stderr, "Usage: roman_calc [numeral] +|- [numeral]\n");
      exit (EXIT_FAILURE);
    }
  if (roman_number_check (argv[1]) == ERROR)
    {
      fprintf (stderr, "Incorrect Roman numeral '%s'\n", argv[1]);
      exit (EXIT_FAILURE);
    }

  if (roman_number_check (argv[3]) == ERROR)
    {
      fprintf (stderr, "Incorrect Roman numeral '%s'\n", argv[3]);
      exit (EXIT_FAILURE);
    }
  if (*argv[2] == '+')
    roman_number_add (argv[1], argv[3], result);
  else if (*argv[2] == '-')
    roman_number_sub (argv[1], argv[3], result);
  else
    {
      fprintf (stderr, "Wrong operand '%s'.Only supported + or - .\n",
	       argv[2]);
      exit (EXIT_FAILURE);
    }
  printf ("%s\n", result);

  return 0;
}
