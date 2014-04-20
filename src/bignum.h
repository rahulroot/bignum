#ifndef __big_num_h_
#define __big_num_h_

#include <string>

typedef extern int BigN[10000];

/* function to print the big number */
void print_big(BigN arg);

/* read a big number into array from input string */
void read_big(const string &str, BigN num);

/* function to add two big number and return a result */
void add_big(BigN a, BigN b, BigN result);

/* function to compare the two big number */
int compare_big(BigN a, BigN b);

/* Function to perfrom the substraction on big number */
void sub_big(BigN a, BigN b, BigN result);

/* Function to perform the divisibility on big number by integer */
void div_big(BigN num, int divisor, BigN quo, int &rem);

#endif 
