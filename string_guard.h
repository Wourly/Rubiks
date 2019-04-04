#include <stdio.h>
#include <stdlib.h>
#include "colours.h"

#ifndef STRING_GUARD_H
#define STRING_GUARD_H

#define STRING_GUARD_MEMORY_EXPANSION_COEFFICIENT 1.2
#define STRING_GUARD_MEMORY_EXPANSION_FLAT_AMOUNT 30

#define FREE_STRING_GUARD_MEMBER(member) free(string_guard->member); string_guard->member = NULL;
#define MALLOC_STRING_GUARD_MEMBER(member) (string_guard->member = malloc(1 * sizeof * string_guard->member))

typedef struct String_guard String_guard;

struct String_guard
{
    //char operations
    long long unsigned int * capacity;
    long long unsigned int * index;
    char * value; //array
    //string operations
    unsigned int * number_of_strings;
    unsigned int * separators; //array
    unsigned int * separators_capacity;
};

//CONSTRUCTOR
String_guard * new_string_guard();
//DESTRUCTOR
String_guard * destroy_string_guard(String_guard * string_guard);

//PUSH
int string_guard_push (String_guard * string_guard, char * input_string);

//LIST OF STRINGS
int string_guard_print_list (String_guard * string_guard);
//GET STRING
char * string_guard_get_string (String_guard * string_guard, int index);

//NUMBER OF STRINGS
int string_guard_info (String_guard * string_guard);

//STRUCT MEMBERS
int string_guard_detail (String_guard * string_guard);

//LIST OF ALL VALUES BY SEPARATORS
int string_guard_list_strings(String_guard * string_guard);

#endif