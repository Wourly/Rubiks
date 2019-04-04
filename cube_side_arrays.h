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
void fill_cube_side_array (char * string_pointer, char character);

//DESTRUCTOR
Cube_side_arrays * destroy_cube_side_arrays (Cube_side_arrays * cube_side_arrays);

//CONTRUCTOR
Cube_side_arrays * new_cube_side_arrays ();

#endif