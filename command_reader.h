#include <stdio.h>
#include "string_guard.h"

#ifndef COMMAND_READER_H
#define COMMAND_READER_H

int read_commands(String_guard * string_guard, char * string)
{
    //if string is NULL, reading from stdin
    unsigned int limit = 0;
    if (string) while (string[limit++]); else limit = 1;

    char c;
    char buff [3];

    int is_movement = 0;

    unsigned int i = 0;

    while (i < limit)
    {
        is_movement = 0;

        c = string ? string[i++] : getc(stdin);
        
        WAS_NOT_A_MOVEMENT_NUMBER:

        switch (c)
        {
            case 'q': goto END_OF_INPUT;
            case 'F': buff[0] = c; is_movement = 1; break;
            case 'B': buff[0] = c; is_movement = 1; break;
            case 'L': buff[0] = c; is_movement = 1; break;
            case 'R': buff[0] = c; is_movement = 1; break;
            case 'U': buff[0] = c; is_movement = 1; break;
            case 'D': buff[0] = c; is_movement = 1; break;
        }

        if (is_movement)
        {
            c = string ? string[i++] : getc(stdin);

            if (c > '0' && c <= '9')
            {
                buff[1] = c;
                buff[2] = '\0';
                string_guard_push(string_guard, buff);
            }
            else
            {
                buff[1] = '1';
                buff[2] = '\0';
                string_guard_push(string_guard, buff);

                is_movement = 0;
                goto WAS_NOT_A_MOVEMENT_NUMBER;
            }
        }
    }

    END_OF_INPUT:

    return 0;
}

#endif