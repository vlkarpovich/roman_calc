#include <stdlib.h>
#include <string.h>
#include "roman_calc.h"

/* Find sequence number of a char in string of allowed Roman symbols */

int
get_rank (const char chr)
{
  char *c;
  c = strchr (RomanSymbols, chr);
  return (c ? (c - RomanSymbols + 1) : 0);
}

int
roman_number_check (const char *roman_number)
{
  const char *c;
  int rank = 0;
  int prev_rank = 0;
  int postfix = 0;

  if (!roman_number)
    {
      return ERROR;
    }

  /* start checking from right to left */
  c = roman_number + (strlen (roman_number) - 1);

  do
    {
      rank = get_rank (*c);
      if (!rank)
	{
	  return ERROR;
	}
      /* Previous and current symbols are the same */
      if (rank == prev_rank)
	{
	  /* no more than 3 symbols in a row */
	  if (postfix == 3)
	    return ERROR;
	  postfix++;
	}
      else
	{
	  postfix = 1;
	}
      prev_rank = rank;
    }
  while (c-- != roman_number);
  return SUCCESS;
}
