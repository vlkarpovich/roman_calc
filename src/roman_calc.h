#ifndef ROMAN_CALC_H
#define ROMAN_CALC_H

#define SUCCESS  0
#define ERROR    1
#define ZERO     "Nulla"
#define INFINITY "Infinitas"
#define NEGATIVE "Negativa"

int roman_number_check (char *r_num);
char *roman_number_add (char *r_num_1, char *r_num_2, char *result);
char *roman_number_sub (char *r_num_1, char *r_num_2, char *result);
#endif /* ROMAN_CALC_H */
