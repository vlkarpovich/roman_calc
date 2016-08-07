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

/* Check if a symbol is V,L or D */
int
is_symbol_level_five (int rank)
{
  return (!(rank % 2));
}

int
roman_number_check (const char *roman_number)
{
  const char *c;
  int rank = 0;
  int prev_rank = 0;
  int postfix = 0;
  int prefix = 0;
  int count = 0;

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
	  /* no more than 1 level 5 symbols (V,L,D) in a row */
	  if (is_symbol_level_five (rank))
	    {
	      return ERROR;
	    }
	  /* no more than 3 symbols in a row */
	  if (postfix == 3)
	    {
	      return ERROR;
	    }
	  postfix++;
	  count++;
	}
      /* Rank of the current symbol is smaller than the previos one.
         It must be a prefix */
      else if (rank < prev_rank)
	{
	  /* Check for prefix and postfix at the same time */
	  if ((count > 1) || prefix)
	    {
	      return ERROR;
	    }
	  prefix = 1;
	  count = 0;
	}
      else
	{
	  prefix = 0;
	  postfix = 1;
	  count++;
	}
      prev_rank = rank;
    }
  while (c-- != roman_number);
  return SUCCESS;
}
