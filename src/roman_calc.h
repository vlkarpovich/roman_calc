#ifndef ROMAN_CALC_H
#define ROMAN_CALC_H

#define SUCCESS  0
#define ERROR    1

#define ROMAN_NUM_MAX_LEN 20
#define ROMAN_SYMBOLS_NUM  7

static const char RomanSymbols[] = "IVXLCDM";

int roman_number_check (const char *roman_number);
#endif /* ROMAN_CALC_H */
