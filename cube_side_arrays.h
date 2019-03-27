#include <stdio.h>
#include <stdlib.h>

#ifndef CUBE_SIDE_ARRAYS_H
#define CUBE_SIDE_ARRAYS_H

//arrayS, it is plural, do not forget S

#define MALLOC_CUBE_SIDE_ARRAY($array_name$)       (cube_side_arrays->$array_name$ = malloc(10 * sizeof * cube_side_arrays->$array_name$))
//#define fill_cube_side_array(array_name)         fill_cube_side_array(cube_side_arrays->array_name, 'array_name'); !!! Character constant too long
#define FREE_CUBE_SIDE_ARRAY($array_name$)         free(cube_side_arrays->$array_name$); cube_side_arrays->$array_name$ = NULL;

typedef struct Cube_side_arrays Cube_side_arrays;

struct Cube_side_arrays
{
    char * f; //front
    char * b; //bottom
    char * l; //left
    char * r; //right
    char * u; //up
    char * d; //down
};


//METHODS
int fill_cube_side_array (char * string_pointer, char character)
{
    for (int i = 0; i < 9; i++)
    {
        string_pointer[i] = character;
    }

    string_pointer[9] = '\0';

    return 0;
}

//DESTRUCTOR
int destroy_cube_side_arrays (Cube_side_arrays * cube_side_arrays)
{
    FREE_CUBE_SIDE_ARRAY(f)
    FREE_CUBE_SIDE_ARRAY(b)
    FREE_CUBE_SIDE_ARRAY(l)
    FREE_CUBE_SIDE_ARRAY(r)
    FREE_CUBE_SIDE_ARRAY(u)
    FREE_CUBE_SIDE_ARRAY(d)

    free(cube_side_arrays);
    cube_side_arrays = NULL;

    return 0;
}

//CONTRUCTOR
Cube_side_arrays * new_cube_side_arrays ()
{
    Cube_side_arrays * cube_side_arrays = NULL;

    if ((cube_side_arrays = malloc(1 * sizeof * cube_side_arrays)))
    {
        if
        (
            MALLOC_CUBE_SIDE_ARRAY(f)
            &&
            MALLOC_CUBE_SIDE_ARRAY(b)
            &&
            MALLOC_CUBE_SIDE_ARRAY(l)
            &&
            MALLOC_CUBE_SIDE_ARRAY(r)
            &&
            MALLOC_CUBE_SIDE_ARRAY(u)
            &&
            MALLOC_CUBE_SIDE_ARRAY(d)
        )
        {
            fill_cube_side_array(cube_side_arrays->f, 'r'); //red
            fill_cube_side_array(cube_side_arrays->b, 'w'); //white
            fill_cube_side_array(cube_side_arrays->l, 'y'); //yellow
            fill_cube_side_array(cube_side_arrays->r, 'b'); //blue
            fill_cube_side_array(cube_side_arrays->u, 'm'); //magenta
            fill_cube_side_array(cube_side_arrays->d, 'g'); //gree
        }
        else
        {
            destroy_cube_side_arrays(cube_side_arrays);
        };
    };

    return cube_side_arrays;
};

#endif