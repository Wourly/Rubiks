#ifndef CUBE_H
#define CUBE_H

#include <stdio.h>
#include <stdlib.h>
#include "elementary.h"
#include "cube_side_arrays.h"
#include "string_guard.h"
#include "colours.h"

#define FREE_CUBE_MEMBER(member) free(cube->member); cube->member = NULL;

typedef struct Cube Cube;

struct Cube
{
    unsigned int * side;
    unsigned int * area;
    Cube_side_arrays * s;   // sides described as chars representing colors
    String_guard * c;       // commands
    unsigned int * is_drawing;
};


//===========================================================================//
//                                  METHODS                                  //
//===========================================================================//
//---------------------------------------------------------------------------//
//                                  drawing                                  //
//---------------------------------------------------------------------------//
#define SIGN    "  " // square character "\u25A0"

#define BREAK_ROW               printf("\n");
#define CUBE_SIDE_LINE          for (int wri = 0; wri < * cube->side; wri++)
#define CUBE_SPACE              ps(* cube->side * 2);
#define CUBE_TOUCH(side_input)  dr(cube->s->side_input, wri, * cube->side);

// print spaces
int ps (int side)
{
    for (int psi = 0; psi < side; psi++)
    {
        printf(" ");
    }
    return 0;
}

// draw row
int dr (char character[], int row, int side)
{
    for (int dri = row * side; dri < (row + 1) * side; dri++)
    {
        switch (character[dri])
        {
            case 'r': printf(RED_BG      SIGN    RESET_COLOUR); break;
            case 'w': printf(WHITE_BG    SIGN    RESET_COLOUR); break;
            case 'y': printf(YELLOW_BG   SIGN    RESET_COLOUR); break;
            case 'b': printf(BLUE_BG     SIGN    RESET_COLOUR); break;
            case 'm': printf(MAGENTA_BG  SIGN    RESET_COLOUR); break;
            case 'c': printf(CYAN_BG     SIGN    RESET_COLOUR); break;
            case 'g': printf(GREEN_BG    SIGN    RESET_COLOUR); break;
        }
    }

    return 0;
}
//draw
int draw_cube (Cube * cube)
{
    BREAK_ROW
    //upper block
    CUBE_SIDE_LINE
    {
        CUBE_SPACE
        CUBE_SPACE
        CUBE_TOUCH(u)
        BREAK_ROW
    }

    //middle block
    CUBE_SIDE_LINE
    {
        CUBE_SPACE
        CUBE_TOUCH(l)
        CUBE_TOUCH(f)
        CUBE_TOUCH(r)
        CUBE_TOUCH(b)
        BREAK_ROW
    }

    //lower block
    CUBE_SIDE_LINE
    {
        CUBE_SPACE
        CUBE_SPACE
        CUBE_TOUCH(d)
        BREAK_ROW
    }

    return 0;
}

int toggle_drawing (Cube * cube)
{
    if (* cube->is_drawing == 0)
    {
        * cube->is_drawing = 1;
    }
    else
    {
        * cube->is_drawing = 0;
    }

    return 0;
}

//---------------------------------------------------------------------------//
//                                  movement                                 //
//---------------------------------------------------------------------------//

//helpers
int turn_own_side (char * side)
{
    char t;

    t = side[0];
    side[0] = side[6];
    side[6] = side[8];
    side[8] = side[2];
    side[2] = t;

    t = side[1];
    side[1] = side[3];
    side[3] = side[7];
    side[7] = side[5];
    side[5] = t;

    return 0;
}

int extend_rotatory_functions (Cube * cube, char * side)
{
    turn_own_side(side);

    if (*cube->is_drawing)
    {
        draw_cube(cube);
    }

    return 0;

};

//manipulation
int turn_front_side (Cube * cube, int rotations)
{
    char t;
    while (rotations--)
    {       
        if (*cube->is_drawing)
        {
            printf("\n\t" GREEN "%s" RESET_COLOUR "\n", __func__);
        }
        
        t = cube->s->l[2];
        cube->s->l[2] = cube->s->d[0];
        cube->s->d[0] = cube->s->r[6];
        cube->s->r[6] = cube->s->u[8];
        cube->s->u[8] = t;

        t = cube->s->l[5];
        cube->s->l[5] = cube->s->d[1];
        cube->s->d[1] = cube->s->r[3];
        cube->s->r[3] = cube->s->u[7];
        cube->s->u[7] = t;

        t = cube->s->l[8];
        cube->s->l[8] = cube->s->d[2];
        cube->s->d[2] = cube->s->r[0];
        cube->s->r[0] = cube->s->u[6];
        cube->s->u[6] = t;

        extend_rotatory_functions(cube, cube->s->f);
    }

    return 0;
};

int turn_back_side (Cube * cube, int rotation)
{
    char t;
    while (rotation--)
    {       
        if (*cube->is_drawing)
		{
			printf("\n\t" GREEN "%s" RESET_COLOUR "\n", __func__);
		}

        t = cube->s->r[2];
        cube->s->r[2] = cube->s->d[8];
        cube->s->d[8] = cube->s->l[6];
        cube->s->l[6] = cube->s->u[0];
        cube->s->u[0] = t;

        t = cube->s->r[5];
        cube->s->r[5] = cube->s->d[7];
        cube->s->d[7] = cube->s->l[3];
        cube->s->l[3] = cube->s->u[1];
        cube->s->u[1] = t;

        t = cube->s->r[8];
        cube->s->r[8] = cube->s->d[6];
        cube->s->d[6] = cube->s->l[0];
        cube->s->l[0] = cube->s->u[2];
        cube->s->u[2] = t;

        extend_rotatory_functions(cube, cube->s->f);
    }
    return 0;
}


int turn_left_side (Cube * cube, int rotation)
{
    char t;
    while (rotation--)
    {   
        if (*cube->is_drawing)
		{
			printf("\n\t" GREEN "%s" RESET_COLOUR "\n", __func__);
		}
        t = cube->s->f[0];
        cube->s->f[0] = cube->s->u[0];
        cube->s->u[0] = cube->s->b[8];
        cube->s->b[8] = cube->s->d[0];
        cube->s->d[0] = t;

        t = cube->s->f[3];
        cube->s->f[3] = cube->s->u[3];
        cube->s->u[3] = cube->s->b[5];
        cube->s->b[5] = cube->s->d[3];
        cube->s->d[3] = t;

        t = cube->s->f[6];
        cube->s->f[6] = cube->s->u[6];
        cube->s->u[6] = cube->s->b[2];
        cube->s->b[2] = cube->s->d[6];
        cube->s->d[6] = t;

        extend_rotatory_functions(cube, cube->s->l);
    }

    return 0;
}

int turn_right_side (Cube * cube, int rotation)
{
    char t;
    while (rotation--)
    {       
        if (*cube->is_drawing)
		{
			printf("\n\t" GREEN "%s" RESET_COLOUR "\n", __func__);
		}
        t = cube->s->f[2];
        cube->s->f[2] = cube->s->d[2];
        cube->s->d[2] = cube->s->b[6];
        cube->s->b[6] = cube->s->u[2];
        cube->s->u[2] = t;

        t = cube->s->f[5];
        cube->s->f[5] = cube->s->d[5];
        cube->s->d[5] = cube->s->b[3];
        cube->s->b[3] = cube->s->u[5];
        cube->s->u[5] = t;

        t = cube->s->f[8];
        cube->s->f[8] = cube->s->d[8];
        cube->s->d[8] = cube->s->b[0];
        cube->s->b[0] = cube->s->u[8];
        cube->s->u[8] = t;

        extend_rotatory_functions(cube, cube->s->b);
    }
    return 0;
}

int turn_up_side (Cube * cube, int rotation)
{
    char t;
    while (rotation--)
    {   
        if (*cube->is_drawing)
		{
			printf("\n\t" GREEN "%s" RESET_COLOUR "\n", __func__);
		}
        t = cube->s->f[0];
        cube->s->f[0] = cube->s->r[0];
        cube->s->r[0] = cube->s->b[0];
        cube->s->b[0] = cube->s->l[0];
        cube->s->l[0] = t;

        t = cube->s->f[1];
        cube->s->f[1] = cube->s->r[1];
        cube->s->r[1] = cube->s->b[1];
        cube->s->b[1] = cube->s->l[1];
        cube->s->l[1] = t;

        t = cube->s->f[2];
        cube->s->f[2] = cube->s->r[2];
        cube->s->r[2] = cube->s->b[2];
        cube->s->b[2] = cube->s->l[2];
        cube->s->l[2] = t;

        extend_rotatory_functions(cube, cube->s->u);
    }

    return 0;
}

int turn_down_side (Cube * cube, int rotation)
{
    char t;
    while (rotation--)
    {   
        if (*cube->is_drawing)
		{
			printf("\n\t" GREEN "%s" RESET_COLOUR "\n", __func__);
		}
        t = cube->s->f[6];
        cube->s->f[6] = cube->s->l[6];
        cube->s->l[6] = cube->s->b[6];
        cube->s->b[6] = cube->s->r[6];
        cube->s->r[6] = t;

        t = cube->s->f[7];
        cube->s->f[7] = cube->s->l[7];
        cube->s->l[7] = cube->s->b[7];
        cube->s->b[7] = cube->s->r[7];
        cube->s->r[7] = t;

        t = cube->s->f[8];
        cube->s->f[8] = cube->s->l[8];
        cube->s->l[8] = cube->s->b[8];
        cube->s->b[8] = cube->s->r[8];
        cube->s->r[8] = t;

        extend_rotatory_functions(cube, cube->s->d);
    }

    return 0;
}

    // turns own side another direction
    int atos (char s[])
    {
        t = s[0];
        s[0] = s[2];
        s[2] = s[8];
        s[8] = s[6];
        s[6] = t;

        t = s[1];
        s[1] = s[5];
        s[5] = s[7];
        s[7] = s[3];
        s[3] = t;
        
        return 0;
    }


    //rotate around Front
    int raF (void)
    {
        F(1);
        B(3);
        //mid layer
        t = ls[1];
        ls[1] = ds[3];
        ds[3] = rs[7];
        rs[7] = us[5];
        us[5] = t;

        t = ls[4];
        ls[4] = ds[4];
        ds[4] = rs[4];
        rs[4] = us[4];
        us[4] = t;

        t = ls[7];
        ls[7] = ds[5];
        ds[5] = rs[1];
        rs[1] = us[3];
        us[3] = t;
        return 0;   
    }

    //rotate Front down
    int rFD (void)
    {
        L(1);
        R(3);
        //mid layer
        t = fs[1];
        fs[1] = us[1];
        us[1] = bs[7];
        bs[7] = ds[1];
        ds[1] = t;

        t = fs[4];
        fs[4] = us[4];
        us[4] = bs[4];
        bs[4] = ds[4];
        ds[4] = t;

        t = fs[7];
        fs[7] = us[7];
        us[7] = bs[1];
        bs[1] = ds[7];
        ds[7] = t;

        return 0;
    }

//---------------------------------------------------------------------------//
//                                   commands                                //
//---------------------------------------------------------------------------//

int get_commands_from_string(String_guard * string_guard, char * string)
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

int execute_commands(String_guard * string_guard, Cube * cube)
{
    char * buffer = NULL;

    if ((buffer = malloc (3 * sizeof * buffer)))
    {
        printf("%u<--\n", *string_guard->number_of_strings);

        for (register unsigned int i = 0; i < * string_guard->number_of_strings; i++)
        {
            buffer = string_guard_get_string(string_guard, i);

            switch (buffer[0])
            {
                case 'F': turn_front_side(cube, buffer[1] - '0'); string_guard_push(cube->c, buffer); break;
                case 'B': turn_back_side(cube, buffer[1] - '0'); string_guard_push(cube->c, buffer); break;
                case 'L': turn_left_side(cube, buffer[1] - '0'); string_guard_push(cube->c, buffer); break;
                case 'R': turn_right_side(cube, buffer[1] - '0'); string_guard_push(cube->c, buffer); break;
                case 'U': turn_up_side(cube, buffer[1] - '0'); string_guard_push(cube->c, buffer); break;
                case 'D': turn_down_side(cube, buffer[1] - '0'); string_guard_push(cube->c, buffer); break;
            }
        }
    }

    return 0;
}

int apply_commands (Cube * cube, char * string)
{
    String_guard * string_guard = new_string_guard();

    get_commands_from_string(string_guard, string);

    execute_commands(string_guard, cube);

    return 0;
}

//===========================================================================//
//                                 METHODS END                               //
//===========================================================================//

//DESTRUCTOR
Cube * destroy_cube(Cube * cube)
{

    FREE_CUBE_MEMBER(side)
    FREE_CUBE_MEMBER(area)
    FREE_CUBE_MEMBER(s)
    FREE_CUBE_MEMBER(c)
    FREE_CUBE_MEMBER(is_drawing)

    free(cube);

    cube = NULL;

    return NULL;
}

//CONSTRUCTOR
Cube * new_cube()
{

    Cube * cube = NULL;

    if ((cube = malloc(1 * sizeof * cube)))
    {
        if
        (
            (cube->side = malloc(1 * sizeof * cube->side))
            &&
            (cube->area = malloc(1 * sizeof * cube->area))
            &&
            (cube->s = new_cube_side_arrays())
            &&
            (cube->c = new_string_guard())
            &&
            (cube->is_drawing = malloc(1 * sizeof * cube->is_drawing))
        )
        {
            *cube->side = 3;
            *cube->area = *cube->side * * cube->side;
            *cube->is_drawing = 1;

            return cube;
        }
    }

    return destroy_cube(cube);
};
#endif