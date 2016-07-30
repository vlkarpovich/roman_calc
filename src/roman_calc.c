#include <stdlib.h>
#include <string.h>
#include "roman_calc.h"

int
roman_number_check (const char *roman_number)
{
  if (!roman_number)
    {
    return ERROR;
    }
  if (strspn (roman_number, RomanSymbols) == strlen (roman_number))
    {
      return SUCCESS;
    }
  return ERROR;
}
