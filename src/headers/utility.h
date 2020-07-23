#ifndef UTILITY_H
#define UTILITY_H

/** Includes **/
#include <stdio.h>
#include <string.h>
#include <stdint.h>

/** Constants **/

/** Typedefs **/

/*
        String Conversion Error

        Lists all the possible erros for when converting string to int
*/
typedef enum StringConErr {
        GOOD,           // No problems converting 
        NULL_STRING,    // String inputted pointed to NULL
        NOT_NUMBER,     // Tried to convert non numeric char/s to int
        WHITE_SPACE,    // String has extra white-space that it shouldn't have 
        LEADING_ZERO    // String has a leading 0; I consider this invalid 
} StringConErr;

/** Functions **/
int string_to_int(char *string, StringConErr *error);
char *get_file_extension(char *fileName);
uint8_t get_nth_dec_digit(uint16_t number, uint8_t n);

#endif