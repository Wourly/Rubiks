#include <stdio.h>
#include <stdlib.h>
#include "colours.h"

#ifndef STRING_GUARD_H
#define STRING_GUARD_H

#define STRING_GUARD_MEMORY_EXPANSION_COEFFICIENT 1.2
#define STRING_GUARD_MEMORY_EXPANSION_FLAT_AMOUNT 10

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
    unsigned int * length;
    unsigned int * separators; //array
    unsigned int * separators_index;
    unsigned int * separators_capacity;
};

int string_guard_allocate_separators(String_guard * string_guard)
{
    //new separators needed
    if (* string_guard->length >= * string_guard->separators_capacity)
    {
        unsigned int new_separator_capacity = * string_guard->separators_capacity + 5;

        unsigned int * new_separators = NULL;
        
        if
        (
            (new_separators = malloc(new_separator_capacity))
        )
        {
            * string_guard->separators_capacity = new_separator_capacity;
            
            for (register unsigned int i = 0; i < * string_guard->length; i++)
            {
                new_separators[i] = string_guard->separators[i];
            }

            string_guard->separators = new_separators;

        }
        else
        {
            printf(YELLOW "Warning:" WHITE " Not enought memory to use " CYAN "%s" WHITE "! No string pushed!\n" RESET_COLOUR, __func__);
        }
    }

    return 1;
}

//METHODS
int string_guard_push (String_guard * string_guard, char input_string[])
{
    //input string measurement
    unsigned int input_string_length = 0;
    while (input_string[input_string_length++]);

    unsigned int check_separators_allocation = 1;

    //new chars needed
    if (* string_guard->index + input_string_length > * string_guard->capacity)
    {
        long long unsigned int new_capacity =
        * string_guard->capacity * STRING_GUARD_MEMORY_EXPANSION_COEFFICIENT
        +
        input_string_length
        +
        STRING_GUARD_MEMORY_EXPANSION_FLAT_AMOUNT;

        char * new_value = NULL;
        if
        (
            (new_value = malloc(new_capacity * sizeof * new_value))
        )
        {
            if (check_separators_allocation)
            {
                string_guard_allocate_separators(string_guard);
                check_separators_allocation = 0;
            }

            * string_guard->capacity = new_capacity;

            for (register unsigned long long i = 0; string_guard->value[i]; i++)
            {
                new_value[i] = string_guard->value[i];
            }

            new_value[* string_guard->index] = '\0';

            free(string_guard->value);

            string_guard->value = new_value;
        }
        else
        {
            printf(YELLOW "Warning:" WHITE " Not enought memory to use " CYAN "%s" WHITE "! No string pushed!\n" RESET_COLOUR, __func__);
            goto STRING_GUARD_PUSH_END;
        }
    }

    if (check_separators_allocation)
    {
        string_guard_allocate_separators(string_guard);
        check_separators_allocation = 0;
    }

    //pushing
    register unsigned int index_of_input_string = 0;

    for (; index_of_input_string < input_string_length; index_of_input_string++)
    {
        string_guard->value[* string_guard->index + index_of_input_string] = input_string[index_of_input_string];
    }

    string_guard->separators[* string_guard->length] = *string_guard->index;
    
    *string_guard->length += 1;

    *string_guard->index += index_of_input_string - 1;

    STRING_GUARD_PUSH_END:

    return 1;
};

int string_guard_info (String_guard * string_guard)
{
    printf(CYAN "length:" YELLOW "\t%u" RESET_COLOUR, *string_guard->length);
    printf("\tcap:"     "\t%llu", *string_guard->capacity);
    printf("\tcni:"      "\t%llu", *string_guard->index);
    printf("\tclen:"    "\t%llu", *string_guard->index + 1);
    printf("\n");

    return 1;
}

int string_guard_detail (String_guard * string_guard)
{
    string_guard_info (string_guard);

    for (unsigned int i = 0; i < * string_guard->length; i++)
    {
        printf("%u: %u\t", i, string_guard->separators[i]);
    }

    printf("\n");

    return 1;
}

//string_guard_slice ...

//DESTRUCTOR
String_guard * destroy_string_guard(String_guard * string_guard)
{
    FREE_STRING_GUARD_MEMBER(value)
    FREE_STRING_GUARD_MEMBER(index)
    FREE_STRING_GUARD_MEMBER(capacity)
    FREE_STRING_GUARD_MEMBER(length)
    FREE_STRING_GUARD_MEMBER(separators)
    FREE_STRING_GUARD_MEMBER(separators_index)
    FREE_STRING_GUARD_MEMBER(separators_capacity)

    free(string_guard);
    string_guard = NULL;

    return NULL;
}

//CONSTRUCTOR
String_guard * new_string_guard()
{
    String_guard * string_guard = NULL;

    if ((string_guard = malloc(1 * sizeof * string_guard)))
    {
        if
        (
            MALLOC_STRING_GUARD_MEMBER(capacity)
            &&
            MALLOC_STRING_GUARD_MEMBER(index)
            &&
            MALLOC_STRING_GUARD_MEMBER(value)
            &&
            MALLOC_STRING_GUARD_MEMBER(length)
            &&
            MALLOC_STRING_GUARD_MEMBER(separators)
            &&
            MALLOC_STRING_GUARD_MEMBER(separators_index)
            &&
            MALLOC_STRING_GUARD_MEMBER(separators_capacity)
        )
        {
            *string_guard->capacity = 0;
            *string_guard->index = 0;
            string_guard->value[0] = '\0';

            *string_guard->length = 0;

            string_guard->separators[0] = 0;
            *string_guard->separators_capacity = 0;

            return string_guard;
        }
    }

    return destroy_string_guard(string_guard);
};

#endif

