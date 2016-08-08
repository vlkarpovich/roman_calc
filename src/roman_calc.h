#ifndef ROMAN_CALC_H
#define ROMAN_CALC_H

#define SUCCESS  0
#define ERROR    1

#define ZERO     "Nulla"
#define INFINITY "Infinitas"
#define NEGATIVE "Negativa"

#define ROMAN_NUM_MAX_LEN 20
#define ROMAN_SYMBOLS_NUM  7
#define ROMAN_TOKEN_MAX 4

static const char RomanSymbols[] = "IVXLCDM";

int roman_number_check (const char *roman_number);
char *roman_number_add (const char *number1, const char *number2, char *result);
char *roman_number_sub (const char *number1, const char *number2, char *result);
#endif /* ROMAN_CALC_H */
