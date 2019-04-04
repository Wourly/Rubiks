#include "cube_side_arrays.h"

void fill_cube_side_array (char * string_pointer, char character)
{
    for (register unsigned int i = 0; i < 9; i++)
    {
        string_pointer[i] = character;
    }

    string_pointer[9] = '\0';
}

Cube_side_arrays * destroy_cube_side_arrays (Cube_side_arrays * cube_side_arrays)
{
    FREE_CUBE_SIDE_ARRAY(f)
    FREE_CUBE_SIDE_ARRAY(b)
    FREE_CUBE_SIDE_ARRAY(l)
    FREE_CUBE_SIDE_ARRAY(r)
    FREE_CUBE_SIDE_ARRAY(u)
    FREE_CUBE_SIDE_ARRAY(d)

    free(cube_side_arrays);
    cube_side_arrays = NULL;

    return NULL;
}

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
            fill_cube_side_array(cube_side_arrays->f, 'r');
            fill_cube_side_array(cube_side_arrays->b, 'm');
            fill_cube_side_array(cube_side_arrays->l, 'y');
            fill_cube_side_array(cube_side_arrays->r, 'w');
            fill_cube_side_array(cube_side_arrays->u, 'g');
            fill_cube_side_array(cube_side_arrays->d, 'b');

            return cube_side_arrays;
        }
    }

    return destroy_cube_side_arrays(cube_side_arrays);
}