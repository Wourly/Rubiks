#include <stdio.h>
#include <stdlib.h>
#include "colours.h"

#ifndef STRING_GUARD_H
#define STRING_GUARD_H

#define FREE_STRING_GUARD_MEMBER(member) free(string_guard->member); string_guard->member = NULL;

typedef struct String_guard String_guard;

struct String_guard
{
    //number_of_strings - to add later
    //separator_index_of_strings - to add later
    long long unsigned int * capacity;
    long long unsigned int * index;
    char * value;

};

//METHODS
int string_guard_push (String_guard * string_guard, char input_string[])
{
    //input string measurement
    unsigned int input_string_length = 0;
    while (input_string[input_string_length++]);

    //memory management
    if (* string_guard->index + input_string_length > * string_guard->capacity)
    {
        long long unsigned int new_capacity = * string_guard->capacity * 1.2 + input_string_length + 10;

        char * new_value = NULL;
        if ((new_value = malloc(new_capacity * sizeof * new_value)))
        {
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
            goto STRING_GUARD_PUSH_NO_ACTION;
        }
    }

    //pushing
    register unsigned int index_of_input_string = 0;

    for (; index_of_input_string < input_string_length; index_of_input_string++)
    {
        string_guard->value[* string_guard->index + index_of_input_string] = input_string[index_of_input_string];
    }

    *string_guard->index += index_of_input_string - 1;

    STRING_GUARD_PUSH_NO_ACTION:

    return 0;
};

int string_guard_info (String_guard * string_guard)
{
    printf(CYAN "len:" YELLOW "\t%llu " CYAN "\tcap:" YELLOW "\t%llu" CYAN "\ti:" YELLOW "\t%llu\n" RESET_COLOUR, *string_guard->index + 1, *string_guard->capacity, *string_guard->index);

    return 0;
}

//string_guard_slice ...

//DESTRUCTOR
String_guard * destroy_string_guard(String_guard * string_guard)
{
    FREE_STRING_GUARD_MEMBER(value)
    FREE_STRING_GUARD_MEMBER(index)
    FREE_STRING_GUARD_MEMBER(capacity)

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
            (string_guard->capacity = malloc(1 * sizeof * string_guard->capacity))
            &&
            (string_guard->index = malloc(1 * sizeof * string_guard->index))
            &&
            (string_guard->value = malloc(*string_guard->capacity * sizeof * string_guard->value))
        )
        {
            *string_guard->capacity = 15;
            *string_guard->index = 0;
            string_guard->value[0] = '\0';

            return string_guard;
        }
    }

    return destroy_string_guard(string_guard);
};

#endif

