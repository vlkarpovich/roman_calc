#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "roman_calc.h"

static char RomanSymbols[] = "IVXLCDM";
#define SYMBOL_ONE(level)  RomanSymbols[(level)*2]
#define SYMBOL_FIVE(level)  RomanSymbols[(level)*2+1]

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
get_char (char rank)
{
  return (RomanSymbols[rank - 1]);
}

void
resize_string (char *str, int size)
{
  if (size > 0)
    memmove (str + size, str, strlen (str) + 1);
  else
    memmove (str, str - size, strlen (str) + 1);
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
	  /* The prefix can only have odd rank by 1 step lower */
	  if ((rank / 2 + 1) != (current_rank / 2))
	    return ERROR;
	  /* V,L,D can not be after number with a prefix */
	  if (strchr (c + 2, get_char (rank + 1)))
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
find_token_end (char *in, int level)
{
  char pattern[4];
  char *end;
  if (level)
    {
      pattern[0] = RomanSymbols[level * 2];
      pattern[1] = RomanSymbols[level * 2 + 1];
      pattern[2] = RomanSymbols[(level + 1) * 2];
      pattern[3] = 0;
      end = in + strspn (in, pattern);
    }
  else
    end = in + strlen (in);
  return end;
}

void
get_token (char *in, char *out, int level)
{
  char pattern[3];
  char *start = NULL;
  char *end = NULL;
  int size = 0;
  pattern[0] = SYMBOL_ONE (level);
  pattern[1] = SYMBOL_FIVE (level);
  pattern[2] = 0;
/* Find the start */
  start = strpbrk (in, pattern);
  if (start)
    {
      if ((in != start) && (*(start - 1) == SYMBOL_ONE (level - 1)))
	{
/* lower level with prefix */
	  *out = 0;
	}
      else
	{
/* Find the end */
	  end = find_token_end (start, level);
	  size = end - start;

	  strncpy (out, start, size);

	  out[size] = 0;
	}
    }
  else
    *out = 0;
}

int
count_token_value (char *in, int size, int level)
{
  char *c;
  char prev = 0;
  int counter = 0;
  int prefix = 0;

  for (c = in; c < in + size; c++)
    {
      if (*c == SYMBOL_ONE (level))
	counter++;
      if (*c == SYMBOL_FIVE (level))
	{
	  counter += 5;
	  if (prev == SYMBOL_ONE (level))
	    {
	      prefix++;
	      counter--;
	    }
	}

      if (*c == SYMBOL_ONE (level + 1))
	{
	  counter += 10;
	  if (prev == SYMBOL_ONE (level))
	    {
	      prefix++;
	      counter--;
	    }
	}
      prev = *c;
    }
  return (counter - prefix);
}

int
add_token (char *result, char *in, int level)
{
  int tmp = 0;
  int counter = 0;
  char *end;
  int i;

  end = find_token_end (result, level);
  counter = count_token_value (result, end - result, level);
  counter += count_token_value (in, strlen (in), level);

  if ((SYMBOL_ONE (level) == 'M') && (counter > 3))
    {
      strcpy (result, INFINITY);
      return ERROR;
    }
/* clear this level in result */

  resize_string (result, result - end);
/* get number of 10s */
  tmp = counter / 10;
  for (i = 0; i < tmp; i++)
    {
      resize_string (result, 1);
      *result = SYMBOL_ONE (level + 1);
    }
  result += tmp;

  counter = counter % 10;
  if (counter == 9)
    {
      resize_string (result, 2);
      *result = SYMBOL_ONE (level);
      *(result + 1) = SYMBOL_ONE (level + 1);
    }
  else
    {
      if (counter / 5)
	{
	  resize_string (result, 1);
	  *result = SYMBOL_FIVE (level);
	  result++;
	}
      counter = counter % 5;
      if (counter == 4)
	{
	  resize_string (result, 2);
	  *result = SYMBOL_ONE (level);
	  *(result + 1) = SYMBOL_FIVE (level);
	}
      else
	{
	  for (i = 0; i < counter; i++)
	    {
	      resize_string (result, 1);
	      *result = SYMBOL_ONE (level);
	    }
	}
    }
  return SUCCESS;
}

int
sub_token (char *result, char *in, char *next, int level)
{
  int tmp = 0;
  int counter = 0;
  char *end;
  int i;
  end = find_token_end (result, level);
  counter = count_token_value (result, end - result, level);
  counter -= count_token_value (in, strlen (in), level);

  if (counter < 0)
    {
      if (SYMBOL_ONE (level) == 'M')
	{
	  strcpy (result, NEGATIVE);
	  return ERROR;
	}
      *next = SYMBOL_ONE (level + 1);
      counter = 10 + counter;
    }
  else if (*next != SYMBOL_ONE (level + 1))
    *next = 0;

/* clear this level in result */
  resize_string (result, result - end);
/* get number of 10s */
  tmp = counter / 10;
  for (i = 0; i < tmp; i++)
    {
      resize_string (result, 1);
      *result = SYMBOL_ONE (level + 1);
    }
  result += tmp;

  counter = counter % 10;
  if (counter == 9)
    {
      resize_string (result, 2);
      *result = SYMBOL_ONE (level);
      *(result + 1) = SYMBOL_ONE (level + 1);
    }
  else
    {
      if (counter / 5)
	{
	  resize_string (result, 1);
	  *result = SYMBOL_FIVE (level);
	  result++;
	}
      counter = counter % 5;
      if (counter == 4)
	{
	  resize_string (result, 2);
	  *result = SYMBOL_ONE (level);
	  *(result + 1) = SYMBOL_FIVE (level);
	}
      else
	{
	  for (i = 0; i < counter; i++)
	    {
	      resize_string (result, 1);
	      *result = SYMBOL_ONE (level);
	    }
	}
    }

  return SUCCESS;
}

char *
roman_number_add (char *r_num_1, char *r_num_2, char *result)
{
  int i;
  char token[16];

  if (!r_num_1 || !r_num_2 || !result)
    return NULL;
  *token = 0;
  *result = 0;
  for (i = 0; i <= strlen (RomanSymbols) / 2; i++)
    {
      get_token (r_num_1, token, i);
      if (add_token (result, token, i) == ERROR)
	break;
      *token = 0;
      get_token (r_num_2, token, i);
      if (add_token (result, token, i) == ERROR)
	break;

    }

  return result;
}

char *
roman_number_sub (char *r_num_1, char *r_num_2, char *result)
{
  int i;
  char token[16];
  char next;

  if (!r_num_1 || !r_num_2 || !result)
    return NULL;
  *token = 0;
  *result = 0;

  for (i = 0; i <= strlen (RomanSymbols) / 2; i++)
    {
      get_token (r_num_1, token, i);
      if (add_token (result, token, i) == ERROR)
	break;
      *token = next;
      *(token + 1) = 0;
      if (sub_token (result, token, &next, i) == ERROR)
	break;
      get_token (r_num_2, token, i);
      if (sub_token (result, token, &next, i) == ERROR)
	break;

    }
  if (*result == 0)
    strcpy (result, ZERO);
  return result;
}
