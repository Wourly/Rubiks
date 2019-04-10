#include <stdio.h>
#include <stdlib.h>
#include "colours.h"

#ifndef STRING_GUARD_H
#define STRING_GUARD_H

#define STRING_GUARD_MEMORY_EXPANSION_COEFFICIENT 1.2
#define STRING_GUARD_MEMORY_EXPANSION_FLAT_AMOUNT 30

typedef struct String_guard String_guard;

struct String_guard
{
    //char operations
    long long unsigned int * capacity;  //maximum capacity for "value"
    long long unsigned int * index;     //index used to insert newly pushed characters (overwriting '\0')
    char * value;                       //array of characters passed by string_guard_push
    //string operations
    unsigned int * number_of_strings;   //index maximum
    unsigned int * separators;          //array of indexes
    unsigned int * separators_capacity; //capacity of "separators" array
};

//CONSTRUCTOR
String_guard * new_string_guard();
//DESTRUCTOR
String_guard * destroy_string_guard(String_guard * string_guard);

//addition of chars at the end of value array
//also stores it's index in separators array
//also relocates memory if needed
int string_guard_push (String_guard * string_guard, char * input_string);

//prints "individual strings" with their indexes
int string_guard_print_list (String_guard * string_guard);

//get "string" from between of two separators, based on index
char * string_guard_get_string (String_guard * string_guard, int index);

//prints basic informations about string_guard struct
int string_guard_info (String_guard * string_guard);

//prints all informations about string_guard struct
int string_guard_detail (String_guard * string_guard);

//used in constructor and destructor
#define FREE_STRING_GUARD_MEMBER(member) free(string_guard->member); string_guard->member = NULL;
#define MALLOC_STRING_GUARD_MEMBER(member) (string_guard->member = malloc(1 * sizeof * string_guard->member))

#endif