#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "roman_calc.h"

static char RomanSymbols[] = "IVXLCDM";

int
get_rank (char symbol)
{
  int i;
  for (i = 0; i < 7; i++)
    if (symbol == RomanSymbols[i])
      return (i + 1);
  return 0;
}

int
roman_number_check (char *r_num)
{
  char *c;
  int rank = 0;
  int current_rank = 0;
  int postfix = 0;
  int prefix = 0;
  if (!r_num)
    return ERROR;

  c = r_num + (strlen (r_num) - 1);

  do
    {
      /* Check for I,V,X,L,C,D & M character */
      rank = get_rank (*c);

      if (!rank)
	return ERROR;
      if (rank == current_rank)
	{
	  /* V,L,D can not be 2 in a row */
	  if (rank % 2 == 0)
	    return ERROR;
	  postfix++;
	  if (postfix == 3)
	    return ERROR;
	}
      else if (rank < current_rank)
	{
	  /* No prefix and postfix at the same time and no more than 1 prefix */
	  if (postfix || prefix)
	    return ERROR;
	  /* V,L,D can not be before higher number */
	  if (rank % 2 == 0)
	    return ERROR;
	  /* The prefix can only odd rank 1 step lower */
	  if ((rank / 2 + 1) != (current_rank / 2))
	    return ERROR;
	  prefix = 1;

	}
      else
	{
	  /* Clear postfix and prefix and update the rank */
	  postfix = 0;
	  prefix = 0;
	  current_rank = rank;
	}

    }
  while (c-- != r_num);
  return SUCCESS;
}

char *
roman_number_add (char *r_num_1, char *r_num_2, char *result)
{
  return result;
}

char *
roman_number_sub (char *r_num_1, char *r_num_2, char *result)
{
  return result;
}
