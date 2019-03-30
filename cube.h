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


//===========================================================================
//METHODS
//===========================================================================

//---------------------------------------------------------------------------
//drawing
//---------------------------------------------------------------------------
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

//---------------------------------------------------------------------------
// movement functions
//---------------------------------------------------------------------------

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

//===========================================================================
//METHODS
//===========================================================================

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