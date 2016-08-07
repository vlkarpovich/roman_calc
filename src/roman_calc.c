#include <stdlib.h>
#include <string.h>
#include "roman_calc.h"

#define BASE10(var) ((var-1)/2)
#define SYMBOL_ONE(level)  RomanSymbols[(level)*2]
#define SYMBOL_FIVE(level)  RomanSymbols[(level)*2+1]

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
	  /* Check for prefix is not a level five symbol */
	  if (is_symbol_level_five (rank))
	    {
	      return ERROR;
	    }
	  /* Check if prefix is already set */
	  if (prefix)
	    {
	      return ERROR;
	    }
	  /* if postfix is in the same decimal base */
	  if ((count > 1) && (BASE10 (rank) == BASE10 (get_rank (*(c + 2)))))
	    {
	      return ERROR;
	    }
	  /* The prefix can only have 1 base 10 step lower
	     CM  is OK , XM is not valid */
	  if ((BASE10 (rank) + 1) != (BASE10 (prev_rank)))
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

/* Walk a string to find the end of the symbols sequnce in a range ( level )
  for example find the first symbol after  C,D & M in MDCXIV  = XIV
*/

char *
find_token_end (char *in, int level)
{
  char pattern[4];
  char *end;
  if (level)
    {
      pattern[0] = SYMBOL_ONE (level);
      pattern[1] = SYMBOL_FIVE (level);
      pattern[2] = SYMBOL_ONE (level + 1);
      pattern[3] = 0;
      end = in + strspn (in, pattern);
    }
  else
    end = in + strlen (in);
  return end;
}

/* Search the input for first appearance of 1 & 5 symbols */
char *
find_token_start (const char *in, int level)
{
  char pattern[3];

  pattern[0] = SYMBOL_ONE (level);
  pattern[1] = SYMBOL_FIVE (level);
  pattern[2] = 0;

  return strpbrk (in, pattern);
}

/* Find a substring (token) with symbols with the same decimal base level.
   Place the token in the out string.
*/
void
get_token (const char *in, char *out, int level)
{
  char *start = NULL;
  char *end = NULL;
  int size = 0;

  *out = 0;
  start = find_token_start (in, level);
  if (start)
    {
      end = find_token_end (start, level);
      size = end - start;
      strncpy (out, start, size);
      out[size] = 0;
    }
}

/* Remove symbols or insert empty space in a string
*/
void
resize_string (char *str, int size)
{
  if (size > 0)
    memmove (str + size, str, strlen (str) + 1);
  else
    memmove (str, str - size, strlen (str) + 1);
}

/* Add a token to a string with Roman numerical
*/
int
add_token (char *result, char *in, int level)
{
  /* Insert input in result string */
  resize_string (result, strlen (in));
  memcpy (result, in, strlen (in));
  return (SUCCESS);
}

/* Addition of 2 string with roman numerical.
 The function splits the number in tokens containing symbols responsible
 for the same value range, aka 1,10,100 and 1000.
 Then it adds token one by one.
*/
char *
roman_number_add (const char *number_1, const char *number_2, char *result)
{
  int i;
  char token[ROMAN_NUM_MAX_LEN];
  if (!number_1 || !number_2 || !result)
    {
      return NULL;
    }

  *token = 0;
  *result = 0;
  for (i = 0; i <= ROMAN_SYMBOLS_NUM / 2; i++)
    {
      get_token (number_1, token, i);
      if (add_token (result, token, i) == ERROR)
	{
	  break;
	}
      *token = 0;
      get_token (number_2, token, i);
      if (add_token (result, token, i) == ERROR)
	{
	  break;
	}
    }
  return result;
}
