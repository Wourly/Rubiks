#include "string_guard.h"

//called from string_guard_push
int string_guard_allocate_separators(String_guard * string_guard)
{        
    if (*string_guard->separators_capacity <= *string_guard->number_of_strings)
    {
        unsigned int * new_separators = NULL;

        unsigned int new_separator_capacity = (int)(*string_guard->number_of_strings * STRING_GUARD_MEMORY_EXPANSION_COEFFICIENT) + STRING_GUARD_MEMORY_EXPANSION_FLAT_AMOUNT; 

        if
        (
            (new_separators = malloc(new_separator_capacity * sizeof * new_separators))
        )
        {
            for (int i = 0; i < *string_guard->number_of_strings; i++)
            {
                new_separators[i] = string_guard->separators[i];
            }
            
            free(string_guard->separators);
            string_guard->separators = new_separators;
 
            * string_guard->separators_capacity = new_separator_capacity;     

            return 1;
        }
        else
        {
            return 0;
        }
    }

    return 1;
}

//METHODS
int string_guard_push (String_guard * string_guard, char * input_string)
{
    //input string measurement
    unsigned int input_string_length = 0;
    while (input_string[input_string_length++]);

    unsigned int are_separators_allocated = 0;

    //new memory needed, because input string is too long to be inserted
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
            &&
            (string_guard_allocate_separators(string_guard)) && (are_separators_allocated = 1)
        )
        {
            *string_guard->capacity = new_capacity;

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
            goto STRING_GUARD_PUSH_CANNOT_ALLOCATE_MEMORY;
        }
    }

    if (!are_separators_allocated)
    {
        if (string_guard_allocate_separators(string_guard))
        {
            are_separators_allocated = 1;
        }
        else
        {
            goto STRING_GUARD_PUSH_CANNOT_ALLOCATE_MEMORY;
        }
    }

    //pushing
    register unsigned int index_of_input_string = 0;

    for (; index_of_input_string < input_string_length; index_of_input_string++)
    {
        string_guard->value[* string_guard->index + index_of_input_string] = input_string[index_of_input_string];
    }

    string_guard->separators[* string_guard->number_of_strings] = *string_guard->index;
    
    *string_guard->number_of_strings += 1;

    *string_guard->index += index_of_input_string - 1;

    if (0)
    {
        STRING_GUARD_PUSH_CANNOT_ALLOCATE_MEMORY:
        printf(YELLOW "Warning:" WHITE " Not enought memory to use " CYAN "%s" WHITE "! No string pushed!\n" RESET_COLOUR, __func__);
        return 1;
    }

    return 0;
};

int string_guard_info (String_guard * string_guard)
{
    printf(CYAN "strings:" YELLOW "   %u" RESET_COLOUR, *string_guard->number_of_strings);
    printf("\n");

    return 1;
}

char * string_guard_get_string (String_guard * string_guard, int index)
{
    unsigned int minimum_index = 0;
    unsigned int string_length = 0;

    if (0 <= index && index < * string_guard->number_of_strings - 1)
    {
        minimum_index = string_guard->separators[index];
        string_length = string_guard->separators[index + 1] - string_guard->separators[index];
    }
    else if (index < * string_guard->number_of_strings)
    {
        minimum_index = string_guard->separators[index];
        string_length = * string_guard->index - string_guard->separators[index];
    }
    else
    {
        printf(CYAN "Index out of range." RESET_COLOUR);
        return NULL;
    }

    char * new_string = NULL;

    if
    (
        (new_string = malloc(string_length * sizeof * new_string))
    )
    {
        for (register unsigned int i = 0; i < string_length; i++)
        {            
            new_string[i] = string_guard->value[minimum_index + i];
        }

        new_string[string_length] = '\0';
        return new_string;
    }
    else
    {
        printf(YELLOW "Warning: " RESET_COLOUR "Not enought memory for new string!");
    }

    free(new_string);

    return NULL;
}

int string_guard_print_list (String_guard * string_guard)
{
    for (unsigned int i = 0; i < * string_guard->number_of_strings; i++)
    {
        printf(BLUE "%u:" YELLOW " %u " WHITE "%s   ", i, string_guard->separators[i], string_guard_get_string(string_guard, i));
        
        if (i != 0 && i % 5 == 0)
        {
            printf("\n");
        }
    }

    printf(RESET_COLOUR"\n");

    return 0;
}

int string_guard_detail (String_guard * string_guard)
{
    string_guard_info (string_guard);
    printf(CYAN "capacity:"         YELLOW  "   %llu", *string_guard->capacity);
    printf(CYAN "   index:"          YELLOW  "   %llu", *string_guard->index);
    printf(CYAN "   characters:"     YELLOW  "   %llu", *string_guard->index + 1);

    printf(CYAN "   separator_cap:"  YELLOW  "   %u\n", *string_guard->separators_capacity);

    printf(CYAN "\nlist:   " RESET_COLOUR "(" BLUE "string number:" YELLOW " index of character" RESET_COLOUR " value)\n\n");

    string_guard_print_list(string_guard);

    return 1;
}

//string_guard_slice ...

//DESTRUCTOR
String_guard * destroy_string_guard(String_guard * string_guard)
{
    FREE_STRING_GUARD_MEMBER(value)
    FREE_STRING_GUARD_MEMBER(index)
    FREE_STRING_GUARD_MEMBER(capacity)
    FREE_STRING_GUARD_MEMBER(number_of_strings)
    FREE_STRING_GUARD_MEMBER(separators)
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
            MALLOC_STRING_GUARD_MEMBER(number_of_strings)
            &&
            MALLOC_STRING_GUARD_MEMBER(separators)
            &&
            MALLOC_STRING_GUARD_MEMBER(separators_capacity)
        )
        {
            *string_guard->capacity = 0;
            *string_guard->index = 0;
            string_guard->value[0] = '\0';

            *string_guard->number_of_strings = 0;

            string_guard->separators[0] = 0;
            *string_guard->separators_capacity = 0;

            return string_guard;
        }
    }

    return destroy_string_guard(string_guard);
};