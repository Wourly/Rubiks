#ifndef CUBE_H
#define CUBE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <time.h>
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
void ps (int side);

// draw row
void dr (char character[], int row, int side);
//draw
void draw_cube (Cube * cube);

void toggle_drawing (Cube * cube);

void toggled_name (Cube * cube, char name, int rotations);

void toggled_draw (Cube * cube);

//---------------------------------------------------------------------------//
//                                  movement                                 //
//---------------------------------------------------------------------------//
//helpers
void turn_own_side (char * side);

void turn_own_side_backward (char * side);

//manipulation
void turn_front_side (Cube * cube, int rotations);

void turn_back_side (Cube * cube, int rotations);

void turn_left_side (Cube * cube, int rotations);

void turn_right_side (Cube * cube, int rotations);

void turn_up_side (Cube * cube, int rotations);

void turn_down_side (Cube * cube, int rotations);

void rotate_horizontally (Cube * cube, int rotations);

void rotate_vertically (Cube * cube, int rotations);

void rotate_around (Cube * cube, int rotations);
//---------------------------------------------------------------------------//
//                                   commands                                //
//---------------------------------------------------------------------------//
void get_commands(String_guard * string_guard, char * string, Cube * cube);

void execute_commands(String_guard * string_guard, Cube * cube);

void apply_commands (Cube * cube, char * string);

String_guard * get_random_commands_sequence (int operations);

void randomize_cube (Cube * cube);
//===========================================================================//
//                                 ALGORITHMS                                //
//===========================================================================//

//helpers
// check side (piece)
bool chs (char * s1, char * s2, char c1, char c2);
//is side piece on top - side piece with side 1 color, but without side 2 color
bool ispot (char * s1, char * s2, char c1, char c2);
//check corner (piece)
bool chc (char * s1, char * s2, char * s3, char c1, char c2, char c3);

//ALGORITHMS
void solve_front_cross (Cube * c);

void solve_front_side (Cube * c);

void solve_second_layer (Cube * c);

void solve_back_cross (Cube * c);

void solve_last_side (Cube * c);

void solve_final_layer (Cube * c);

void solve_all (Cube * cube);

//DESTRUCTOR
Cube * destroy_cube(Cube * cube);

//CONSTRUCTOR
Cube * new_cube();

void cube_test (int test_number);

void cube_console_game_help ();

void cube_console_game ();

#endif