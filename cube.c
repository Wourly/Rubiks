#include "cube.h"

void draw_cube (Cube * cube)
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
}

void ps (int side)
{
    for (int psi = 0; psi < side; psi++)
    {
        printf(" ");
    }
}

void dr (char character[], int row, int side)
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
}

void toggle_drawing (Cube * cube)
{
    if (* cube->is_drawing == 0)
    {
        * cube->is_drawing = 1;
    }
    else
    {
        * cube->is_drawing = 0;
    }
}

void toggled_draw (Cube * cube)
{
    if (*cube->is_drawing)
    {
        draw_cube(cube);
    }
}

void toggled_name (Cube * cube, char name, int rotations)
{
    if (*cube->is_drawing)
    {
        printf("\n              " YELLOW "%c" CYAN "%d" RESET_COLOUR "\n", name, rotations);
    }
}

void turn_own_side (char * side)
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
}

void turn_own_side_backward (char * side)
{
    char t;

    t = side[0];
    side[0] = side[2];
    side[2] = side[8];
    side[8] = side[6];
    side[6] = t;

    t = side[1];
    side[1] = side[5];
    side[5] = side[7];
    side[7] = side[3];
    side[3] = t;
}

void turn_front_side (Cube * cube, int rotations)
{
    toggled_name(cube, 'F', rotations);
    
    char t;
    while (rotations--)
    {  
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

        turn_own_side(cube->s->f);
    }

    toggled_draw(cube);
};

void turn_back_side (Cube * cube, int rotations)
{
    toggled_name(cube, 'B', rotations);

    char t;
    while (rotations--)
    {       
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

        turn_own_side(cube->s->b);
    }

    toggled_draw(cube);
}

void turn_left_side (Cube * cube, int rotations)
{
    toggled_name(cube, 'L', rotations);

    char t;
    while (rotations--)
    {   
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

        turn_own_side(cube->s->l);
    }

    toggled_draw(cube);
}

void turn_right_side (Cube * cube, int rotations)
{
    toggled_name(cube, 'R', rotations);

    char t;
    while (rotations--)
    {
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

        turn_own_side(cube->s->r);
    }

    toggled_draw(cube);
}

void turn_up_side (Cube * cube, int rotations)
{
    toggled_name(cube, 'U', rotations);

    char t;
    while (rotations--)
    {   
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

        turn_own_side(cube->s->u);
    }

    toggled_draw(cube);
}

void turn_down_side (Cube * cube, int rotations)
{
    toggled_name(cube, 'D', rotations);

    char t;
    while (rotations--)
    {   
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

        turn_own_side(cube->s->d);
    }

    toggled_draw(cube);
}

void rotate_horizontally (Cube * cube, int rotations)
{
    toggled_name(cube, 'H', rotations);
    
    char * ts = NULL;

    if
    (
        (ts = malloc(10 * sizeof * ts))
    )
    {
        while (rotations--)
        {
            ts = cube->s->f;
            cube->s->f = cube->s->r;
            cube->s->r = cube->s->b;
            cube->s->b = cube->s->l;
            cube->s->l = ts;

            turn_own_side(cube->s->u);
            turn_own_side_backward(cube->s->d);
        }
    }
    else
    {
        printf("Error: could not rotate horizontally! No memory\n");
    }

    toggled_draw(cube);
}

void rotate_vertically (Cube * cube, int rotations)
{
    toggled_name(cube, 'V', rotations);

    char t;
    char is_drawing = * cube->is_drawing;
    
    * cube->is_drawing = 0;

    while (rotations--)
    {
        turn_left_side(cube, 1);
        turn_right_side(cube, 3);

        //mid layer
        t = cube->s->f[1];
        cube->s->f[1] = cube->s->u[1];
        cube->s->u[1] = cube->s->b[7];
        cube->s->b[7] = cube->s->d[1];
        cube->s->d[1] = t;

        t = cube->s->f[4];
        cube->s->f[4] = cube->s->u[4];
        cube->s->u[4] = cube->s->b[4];
        cube->s->b[4] = cube->s->d[4];
        cube->s->d[4] = t;

        t = cube->s->f[7];
        cube->s->f[7] = cube->s->u[7];
        cube->s->u[7] = cube->s->b[1];
        cube->s->b[1] = cube->s->d[7];
        cube->s->d[7] = t;
    }

    * cube->is_drawing = is_drawing;

    toggled_draw(cube);
}

void rotate_around (Cube * cube, int rotations)
{
    toggled_name(cube, 'A', rotations);

    char t;
    char is_drawing = * cube->is_drawing;
    
    * cube->is_drawing = 0;

    while (rotations--)
    {
        turn_front_side(cube, 1);
        turn_back_side(cube, 3);

        //mid layer
        t = cube->s->l[1];
        cube->s->l[1] = cube->s->d[3];
        cube->s->d[3] = cube->s->r[7];
        cube->s->r[7] = cube->s->u[5];
        cube->s->u[5] = t;

        t = cube->s->l[4];
        cube->s->l[4] = cube->s->d[4];
        cube->s->d[4] = cube->s->r[4];
        cube->s->r[4] = cube->s->u[4];
        cube->s->u[4] = t;

        t = cube->s->l[7];
        cube->s->l[7] = cube->s->d[5];
        cube->s->d[5] = cube->s->r[1];
        cube->s->r[1] = cube->s->u[3];
        cube->s->u[3] = t;
    }

    * cube->is_drawing = is_drawing;

    toggled_draw(cube);  
}


void randomize_cube(Cube * cube)
{
    String_guard * string_guard = get_random_commands_sequence(100);
    execute_commands(string_guard, cube);
    destroy_string_guard(string_guard);
}

void get_commands(String_guard * string_guard, char * string, Cube * cube)
{

    //if cube is not provided, then it is 

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
            case 'q': printf("End.\n"); goto END_OF_INPUT;
            case '\0': goto END_OF_INPUT;

            case 'a': apply_commands(cube, string_guard->value); destroy_string_guard(string_guard); string_guard = new_string_guard(); break;
            case 't': toggle_drawing(cube); break;
            case 'l': string_guard_print_list(cube->c); break;
            case 's': solve_all(cube); break;
            case 'd': destroy_string_guard(cube->c); cube->c = new_string_guard(); printf("Command history deleted!\n"); break;
            case 'r': randomize_cube(cube); printf("100 random commands were applied\n"); break;
            case 'h': cube_console_game_help();

            case 'F': buff[0] = c; is_movement = 1; break;
            case 'B': buff[0] = c; is_movement = 1; break;
            case 'L': buff[0] = c; is_movement = 1; break;
            case 'R': buff[0] = c; is_movement = 1; break;
            case 'U': buff[0] = c; is_movement = 1; break;
            case 'D': buff[0] = c; is_movement = 1; break;

            case 'H': buff[0] = c; is_movement = 1; break;
            case 'V': buff[0] = c; is_movement = 1; break;
            case 'A': buff[0] = c; is_movement = 1; break;
        }

        //looking for number
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
                buff[1] = c == '\'' ? '3' : '1';
                buff[2] = '\0';
                string_guard_push(string_guard, buff);
                
                is_movement = 0;

                if (i >= limit)
                {
                    goto END_OF_INPUT;
                }
                else
                {
                    goto WAS_NOT_A_MOVEMENT_NUMBER;
                }
            }   
        }
        //looking for number end
    }

    END_OF_INPUT:
    return;
}

void execute_commands(String_guard * string_guard, Cube * cube)
{
    char * buffer = NULL;

    if ((buffer = malloc (3 * sizeof * buffer)))
    {
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

                case 'H': rotate_horizontally(cube, buffer[1] - '0'); string_guard_push(cube->c, buffer); break;
                case 'V': rotate_vertically(cube, buffer[1] - '0'); string_guard_push(cube->c, buffer); break;
                case 'A': rotate_around(cube, buffer[1] - '0'); string_guard_push(cube->c, buffer); break;
            }
        }
    }
    free(buffer);
}

void apply_commands (Cube * cube, char * string)
{
    String_guard * string_guard = new_string_guard();

    get_commands(string_guard, string, NULL);

    execute_commands(string_guard, cube);

    destroy_string_guard(string_guard);
}

String_guard * get_random_commands_sequence (int operations)
{

    String_guard * string_guard = new_string_guard();

    char buff[3];

    time_t seed;
    time(&seed);
    srand(seed);

    while (operations--)
    {
        switch (rand() % 6)
        {
            case 0: buff[0] = 'F'; break;
            case 1: buff[0] = 'B'; break;
            case 2: buff[0] = 'L'; break;
            case 3: buff[0] = 'R'; break;
            case 4: buff[0] = 'U'; break;
            case 5: buff[0] = 'D'; break;
        }

        buff[1] = (rand() % 3) + '1';
        buff[2] = '\0';

        string_guard_push(string_guard, buff);
    }

    return string_guard;
}

bool chs (char * s1, char * s2, char c1, char c2)
{
    //printf("->(%c == %c && %c == %c) || (%c == %c && %c == %c) -->> %d\n\n", s1[4], c1, s2[4], c2, s1[4], c2, s2[4], c1, (s1[4] == c1 && s2[4] == c2) || (s1[4] == c2 && s2[4] == c1));
    return (s1[4] == c1 && s2[4] == c2) || (s1[4] == c2 && s2[4] == c1);
}
bool ispot (char * s1, char * s2, char c1, char c2)
{
    return (s1[4] == c1 || s1[4] == c2) && (c1 != s2[4] && c2 != s2[4]);
}
bool chc (char * s1, char * s2, char * s3, char c1, char c2, char c3)
{
    return (s1[4] == c1 || s1[4] == c2 || s1[4] == c3) && (s2[4] == c1 || s2[4] == c2 || s2[4] == c3) && (s3[4] == c1 || s3[4] == c2 || s3[4] == c3);
}

void solve_front_cross (Cube * c)
{
    if
    (
        c->s->f[4] == c->s->f[1] && c->s->f[4] == c->s->f[3] && c->s->f[4] == c->s->f[5] && c->s->f[4] == c->s->f[7]
        &&
        c->s->u[4] == c->s->u[7]
        &&
        c->s->r[4] == c->s->r[3]
        &&
        c->s->d[4] == c->s->d[1]
        &&
        c->s->l[4] == c->s->l[5]
    )
    {
        goto SOLVE_FRONT_CROSS_SKIP;
    }

    if (*c->is_drawing)
    {
        printf("\nSolving front cross\n");
    }

// front / up side piece
    // back
    if (chs(c->s->f, c->s->u, c->s->b[1], c->s->u[1]))
    {
        apply_commands(c, "U");
    }
    if (chs(c->s->f, c->s->u, c->s->b[3], c->s->r[5]))
    {
        apply_commands(c, "R");
    }
    if (chs(c->s->f, c->s->u, c->s->b[5], c->s->l[3]))
    {
        apply_commands(c, "L");
    }
    if (chs(c->s->f, c->s->u, c->s->b[7], c->s->d[7]))
    {
        apply_commands(c, "D");
    }
    // right
    if (chs(c->s->f, c->s->u, c->s->r[1], c->s->u[5]))
    {
        apply_commands(c, "R'");
    }
    if (chs(c->s->f, c->s->u, c->s->r[7], c->s->d[5]))
    {
        apply_commands(c, "R");
    }

    // left
    if (chs(c->s->f, c->s->u, c->s->l[1], c->s->u[3]))
    {
        apply_commands(c, "L");
    }
    if (chs(c->s->f, c->s->u, c->s->l[7], c->s->d[3]))
    {
        apply_commands(c, "L'");
    }

    // front
    if (chs(c->s->f, c->s->u, c->s->f[5], c->s->r[3]))
    {
        apply_commands(c, "F");
    }
    if (chs(c->s->f, c->s->u, c->s->f[7], c->s->d[1]))
    {
        apply_commands(c, "F");
    }
    if (chs(c->s->f, c->s->u, c->s->f[3], c->s->l[5]))
    {
        apply_commands(c, "F");
    }

// front / right side piece
    // front 
    if (chs(c->s->f, c->s->r, c->s->f[7], c->s->d[1]))
    {
        apply_commands(c, "D");
    }
    if (chs(c->s->f, c->s->r, c->s->f[3], c->s->l[5]))
    {
        apply_commands(c, "L");
    }
    // right
    if (chs(c->s->f, c->s->r, c->s->r[1], c->s->u[5]))
    {
        apply_commands(c, "R'");
    }
    if (chs(c->s->f, c->s->r, c->s->r[7], c->s->d[5]))
    {
        apply_commands(c, "R");
    }
    // left
    if (chs(c->s->f, c->s->r, c->s->l[1], c->s->u[3]))
    {
        apply_commands(c, "L'");
    }
    if (chs(c->s->f, c->s->r, c->s->l[7], c->s->d[3]))
    {
        apply_commands(c, "L");
    }
    // back
    if (chs(c->s->f, c->s->r, c->s->b[1], c->s->u[1]))
    {
        apply_commands(c, "B");
    }
    if (chs(c->s->f, c->s->r, c->s->b[5], c->s->l[3]))
    {
        apply_commands(c, "B");
    }
    if (chs(c->s->f, c->s->r, c->s->b[7], c->s->d[7]))
    {
        apply_commands(c, "B");
    }
    if (chs(c->s->f, c->s->r, c->s->b[3], c->s->r[5]))
    {
        apply_commands(c, "R2");
    }
// front / down side piece
    // front
    if (chs(c->s->f, c->s->d, c->s->f[3], c->s->l[5]))
    {
        apply_commands(c, "L");
    }
    // right
    if (chs(c->s->f, c->s->d, c->s->r[1], c->s->u[5]))
    {
        apply_commands(c, "R B R'");
    }
    if (chs(c->s->f, c->s->d, c->s->r[7], c->s->d[5]))
    {
        apply_commands(c, "R' B R");
    }
    // left
    if (chs(c->s->f, c->s->d, c->s->l[1], c->s->u[3]))
    {
        apply_commands(c, "L'");
    }
    if (chs(c->s->f, c->s->d, c->s->l[7], c->s->d[3]))
    {
        apply_commands(c, "D");
    }
    // back
    if (chs(c->s->f, c->s->d, c->s->b[3], c->s->r[5]))
    {
        apply_commands(c, "B");
    }
    if (chs(c->s->f, c->s->d, c->s->b[1], c->s->u[1]))
    {
        apply_commands(c, "B");
    }
    if (chs(c->s->f, c->s->d, c->s->b[5], c->s->l[3]))
    {
        apply_commands(c, "B");
    }
    if (chs(c->s->f, c->s->d, c->s->b[7], c->s->d[7]))
    {
        apply_commands(c, "D2");
    }
    // front / left side piece - not done
    // right
    if (chs(c->s->f, c->s->l, c->s->r[1], c->s->u[5]))
    {
        apply_commands(c, "R B R'");
    }
    if (chs(c->s->f, c->s->l, c->s->r[7], c->s->d[5]))
    {
        apply_commands(c, "R' B R");
    }
    // back 
    if (chs(c->s->f, c->s->l, c->s->b[7], c->s->d[7]))
    {
        apply_commands(c, "B");
    }
    if (chs(c->s->f, c->s->l, c->s->b[3], c->s->r[5]))
    {
        apply_commands(c, "B");
    }
    if (chs(c->s->f, c->s->l, c->s->b[1], c->s->u[1]))
    {
        apply_commands(c, "B");
    }
    if (chs(c->s->f, c->s->l, c->s->b[5], c->s->l[3]))
    {
        apply_commands(c, "L");
    }
    // left
    if (chs(c->s->f, c->s->l, c->s->l[1], c->s->u[3]))
    {
        apply_commands(c, "L");
    }
    if (chs(c->s->f, c->s->l, c->s->l[7], c->s->d[3]))
    {
        apply_commands(c, "L'");
    }

    //checking orientation of side pieces
    if (c->s->f[4] != c->s->f[1] || c->s->f[4] != c->s->f[3] || c->s->f[4] != c->s->f[5] || c->s->f[4] != c->s->f[7])
    {
        for (unsigned int sfci = 0; sfci < 4; sfci++)
        {
            if (c->s->f[4] != c->s->f[7])
            {
                apply_commands(c, "D2 B R D' R'");
            }
            apply_commands(c, "A");
        }
    }
    SOLVE_FRONT_CROSS_SKIP:

    return;
}

void solve_front_side (Cube * c)
{
//does not check for other sides!!! ERROR!, the same is in back side
    if
    (
        c->s->f[4] == c->s->f[0] && c->s->f[4] == c->s->f[2] && c->s->f[4] == c->s->f[6] && c->s->f[4] == c->s->f[8]
        &&
        c->s->u[4] == c->s->u[6] && c->s->u[4] == c->s->u[8]
        &&
        c->s->r[4] == c->s->r[0] && c->s->r[4] == c->s->r[6]
        &&
        c->s->d[4] == c->s->d[0] && c->s->d[4] == c->s->d[2]
        &&
        c->s->l[4] == c->s->l[2] && c->s->l[4] == c->s->l[8]
    
    )
    {
        goto SOLVE_FRONT_SIDE_SKIP;
    }

    if (*c->is_drawing)
    {
        printf("\nSolving front side\n");
    }

    for (int sfsi = 0; sfsi < 4; sfsi++)
    {
        if (chc(c->s->f, c->s->d, c->s->r, c->s->f[2], c->s->u[8], c->s->r[0]))
        {
            apply_commands(c, "R B R'");
        }

        if (chc(c->s->f, c->s->d, c->s->r, c->s->f[0], c->s->u[6], c->s->l[2]))
        {
            apply_commands(c, "L' B' L");
        }

        if (chc(c->s->f, c->s->d, c->s->r, c->s->f[6], c->s->d[0], c->s->l[8]))
        {
            apply_commands(c, "L B L'");
        }
    //back
        if (chc(c->s->f, c->s->d, c->s->r, c->s->d[8], c->s->r[8], c->s->b[6]))
        {
            apply_commands(c, "B");
        }

        if (chc(c->s->f, c->s->d, c->s->r, c->s->r[2], c->s->u[2], c->s->b[0]))
        {
            apply_commands(c, "B");
        }

        if (chc(c->s->f, c->s->d, c->s->r, c->s->u[0], c->s->l[0], c->s->b[2]))
        {
            apply_commands(c, "B");
        }
    //fix into correct corner
        if (chc(c->s->f, c->s->d, c->s->r, c->s->d[6], c->s->l[6], c->s->b[8]))
        {
            apply_commands(c, "R' B R");
        }
            apply_commands(c, "A");
    }

    for (unsigned int sfsi = 0; sfsi < 4; sfsi++)
    {
        // if middle piece is not equal to corner piece, turn the corner piece until it is equal ... (corner pieces are already in position)
        while (c->s->f[4] != c->s->f[8])
        {
            apply_commands(c, "R' B R B' R' B R");
        }
        apply_commands(c, "A");
    }

    SOLVE_FRONT_SIDE_SKIP:

    return;
}

void solve_second_layer (Cube * c)
{
    if
    (
        (c->s->d[4] == c->s->d[3] && c->s->d[4] == c->s->d[5])
        &&
        (c->s->l[4] == c->s->l[1] && c->s->l[4] == c->s->l[7])
        &&
        (c->s->r[4] == c->s->r[1] && c->s->r[4] == c->s->r[7])
        &&
        (c->s->u[4] == c->s->u[3] && c->s->u[4] == c->s->u[5])
    )
    {
        goto SOLVE_SECOND_LAYER_SKIP;
    }

    if (*c->is_drawing)
    {
        printf("\nSolving second layer\n");
    }

    apply_commands(c, "V");

    for (int ssli1 = 0; ssli1 < 2; ssli1++)
    {
        for (int ssli2 = 0; ssli2 < 2; ssli2++)
        {

            //dont move with cube, when side pieces are oriented correctly
            if ((c->s->f[3] == c->s->f[4] && c->s->l[5] == c->s->l[4]) && (c->s->f[5] == c->s->f[4] && c->s->r[3] == c->s->r[4]))
            {
                continue;
            }
            //grabs only one piece and moves it to top
            while (1)
            {
            //from front - must not take correct pieces
                if ((c->s->l[5] == c->s->f[4] && c->s->f[3] == c->s->l[4]) || (c->s->l[5] == c->s->r[4] && c->s->f[3] == c->s->f[4]) || (c->s->l[5] == c->s->f[4] && c->s->f[3] == c->s->r[4]))
                {
                    apply_commands(c, "L' U L U F U' F'");
                    break;
                }

                if ((c->s->r[3] == c->s->f[4] && c->s->f[5] == c->s->r[4]) || (c->s->r[3] == c->s->l[4] && c->s->f[5] == c->s->f[4]) || (c->s->r[3] == c->s->f[4] && c->s->f[5] == c->s->l[4]))
                {
                    apply_commands(c, "R U' R' U' F' U F");
                    break;
                }
            //from back
                if (ispot(c->s->f, c->s->u, c->s->b[3], c->s->r[5]))
                {
                    apply_commands(c, "R' U R U B U' B'");
                    break;
                }
                if (ispot(c->s->f, c->s->u, c->s->b[5], c->s->l[3]))
                {
                    apply_commands(c, "L U' L' U' B' U B");
                    break;
                }
                break;
            }
            //from top
            if (ispot(c->s->f, c->s->u, c->s->u[3], c->s->l[1]))
            {
                apply_commands(c, "U");
            }
            if (ispot(c->s->f, c->s->u, c->s->u[1], c->s->b[1]))
            {
                apply_commands(c, "U");
            }
            if (ispot(c->s->f, c->s->u, c->s->u[5], c->s->r[1]))
            {
                apply_commands(c, "U");
            }

            //d();

            while (1)
            {
                if (c->s->f[1] == c->s->f[4])
                {
                    if (c->s->r[4] == c->s->u[7])
                    {
                        apply_commands(c, "U R U' R' U' F' U F");
                        break; 
                    }

                    if (c->s->l[4] == c->s->u[7])
                    {
                        apply_commands(c, "U' L' U L U F U' F'");
                        break;
                    }
                }

                if (c->s->f[1] == c->s->r[4])
                {
                    apply_commands(c, "U2 F' U F U R U' R'");
                    break;
                }

                if (c->s->f[1] == c->s->l[4])
                {
                    apply_commands(c, "U2 F U' F' U' L' U L");
                    break;
                }
                break;
            }
        }

        apply_commands(c, "H2");
    }

    apply_commands(c, "V3");

    SOLVE_SECOND_LAYER_SKIP:

    return;
}

void solve_back_cross (Cube * c)
{

    if (c->s->b[4] == c->s->b[1] && c->s->b[4] == c->s->b[3] && c->s->b[4] == c->s->b[5] && c->s->b[4] == c->s->b[7])
    {
        goto SOLVE_BACK_CROSS_SKIP;
    }

    if (*c->is_drawing)
    {
        printf("\nSolving back cross\n");
    }

    apply_commands(c, "V2");
    
    //correct side pieces
    int csp;
    int sbc_c;

SOLVE_BACK_CROSS_CHECK_SIDE:

    csp = 0;
    char sq[14] = "D R F R' F' D'";

    for (unsigned int cspi = 1; cspi <= 7; cspi += 2)
    {
        if (c->s->f[cspi] == c->s->f[4])
        {
            csp++;
        } 
    }

    if (csp == 4)
    {
        goto SOLVE_BACK_CROSS_END;
    }

    if (csp < 4 && csp != 2)
    {
        apply_commands(c, sq);
    }

    if (csp == 2)
    {
        //position needed for algorithm
        while (c->s->f[4] != c->s->f[3])
        {
            apply_commands(c, "F");
        }

        if (c->s->f[4] == c->s->f[7])
        {
            apply_commands(c, "F");
        }

        if (c->s->f[4] == c->s->f[1])
        {
            apply_commands(c, sq);
        }

        if (c->s->f[4] == c->s->f[5])
        {
            apply_commands(c, sq);
        }
    }

    if (sbc_c == 5)
    {
        printf("Program failed while solving back corner!");
        exit(0);
    }

    sbc_c++;

    goto SOLVE_BACK_CROSS_CHECK_SIDE;

    SOLVE_BACK_CROSS_END:

    apply_commands(c, "V2");
            
    SOLVE_BACK_CROSS_SKIP:

    return;
}

void solve_last_side (Cube * c)
{
    if (c->s->b[4] == c->s->b[0] && c->s->b[4] == c->s->b[2] && c->s->b[4] == c->s->b[6] && c->s->b[4] == c->s->b[8])
    {
        goto SOLVE_LAST_SIDE_SKIP;
    }

    if (*c->is_drawing)
    {
        printf("\nSolving last side\n");
    }

    apply_commands(c, "H2");

    int incorrect_corner_pieces;
    int solve_last_side_attempt = 0;

SOLVE_LAST_SIDE_CHECK_ORIENTATION:

    incorrect_corner_pieces = 0;

    for (int incorrect_corner_piecesi = 0; incorrect_corner_piecesi <= 8; incorrect_corner_piecesi += 2)
    {
        if (c->s->f[incorrect_corner_piecesi] != c->s->f[4])
        {
            incorrect_corner_pieces++;
        } 
    }

    if (incorrect_corner_pieces == 0)
    {
        goto SOLVE_LAST_SIDE_END;
    }

    if (incorrect_corner_pieces == 4)
    {
        while (!(c->s->l[2] == c->s->f[4] && c->s->l[8] == c->s->f[4]))
        {
            apply_commands(c, "F");
        }
    }

    if (incorrect_corner_pieces == 3)
    {
        while (!(c->s->f[6] == c->s->f[4]))
        {
            apply_commands(c, "F");
        }
    }

    if (incorrect_corner_pieces == 2)
    {
        while (!(c->s->r[0] == c->s->f[4]))
        {
            apply_commands(c, "F");
        }
    }

    apply_commands(c, "R F R' F R F F R'");

    if (solve_last_side_attempt == 5)
    {
        printf("Program failed while solving back face!");
        exit(0);
    }

    solve_last_side_attempt++;

    goto SOLVE_LAST_SIDE_CHECK_ORIENTATION;

    SOLVE_LAST_SIDE_END:

    apply_commands(c, "H2");

    SOLVE_LAST_SIDE_SKIP:

    return;
}

void solve_final_layer (Cube * c)
{
    if
    (
        (c->s->d[4] == c->s->d[6] && c->s->l[4] == c->s->l[0] && c->s->r[4] == c->s->r[2] && c->s->u[4] == c->s->u[0])
        &&
        (c->s->d[4] == c->s->d[7] && c->s->l[4] == c->s->l[3] && c->s->r[4] == c->s->r[5] && c->s->u[4] == c->s->u[1])
        &&
        (c->s->d[4] == c->s->d[8] && c->s->l[4] == c->s->l[6] && c->s->r[4] == c->s->r[8] && c->s->u[4] == c->s->u[2])
    )
    {
        goto SOLVE_FINAL_LAYER_SIDE_SKIP;
    }

    if (*c->is_drawing)
    {
        printf("\nSolving final layer\n");
    }

    apply_commands(c, "H2");

    int sides_with_correct_corner = 0;

    if (c->s->u[6] == c->s->u[8])
    {
        sides_with_correct_corner++;
    }

    if (c->s->r[0] == c->s->r[6])
    {
        sides_with_correct_corner++;
    }

    if (c->s->d[0] == c->s->d[2])
    {
        sides_with_correct_corner++;
    }

    if (c->s->l[2] == c->s->l[8])
    {
        sides_with_correct_corner++;
    }

    if (sides_with_correct_corner > 0)
    {

        SOLVE_FINAL_LAYER_FROM_RARE:

        while (1)
        {
            if ((c->s->u[6] == c->s->u[4] && c->s->u[8] == c->s->u[4]) || (c->s->r[0] == c->s->r[4] && c->s->r[6] == c->s->r[4]) || (c->s->d[0] == c->s->d[4] && c->s->d[2] == c->s->d[4]) || (c->s->l[2] == c->s->l[4] && c->s->l[8] == c->s->l[4]))
            {
                break;
            }

            apply_commands(c, "F");
        }

        while (1)
        {
            if (c->s->u[6] == c->s->u[4] && c->s->u[8] == c->s->u[4])
            {
                break;
            }
            
            apply_commands(c, "A");
        }

        //main top layer algorithm
        if (sides_with_correct_corner < 2)
        {
            apply_commands(c, "R' D R' U2 R D' R' U2 R2 F'");
        }

        while (1)
        {
            if (c->s->u[6] == c->s->u[4] && c->s->u[8] == c->s->u[4])
            {
                break;
            }

            apply_commands(c, "A");
        }

        for (int sfli = 0; sfli < 2; sfli++)
        {
            if (c->s->d[1] == c->s->l[4])
            {
                apply_commands(c, "D2 F L R' D2 L' R F D2");
            }

            if (c->s->d[1] == c->s->r[4])
            {
                apply_commands(c, "D2 F' L R' D2 L' R F' D2");
            }

            if (c->s->u[7] != c->s->u[4] && c->s->r[3] != c->s->r[4] && c->s->d[1] != c->s->d[4] && c->s->l[5] != c->s->l[4])
            {
                apply_commands(c, "D2 F' L R' D2 L' R F' D2");
            }

            while (1)
            {
                if ((c->s->u[6] == c->s->u[4] && c->s->u[8] == c->s->u[4] && c->s->u[7] == c->s->u[4]) || (c->s->u[7] != c->s->u[4] && c->s->r[3] != c->s->r[4] && c->s->d[1] != c->s->d[4] && c->s->l[5] != c->s->l[4]))
                {
                    break;
                }
                apply_commands(c, "A");
            }
        }
    }
    else // there is no side with correct corners yet
    {
        while (1)
        {
            if (((c->s->d[0] == c->s->d[4] && c->s->l[8] == c->s->l[4]) && (c->s->u[8] == c->s->u[4] && c->s->r[0] == c->s->r[4])) || ((c->s->l[2] == c->s->l[4] && c->s->u[6] == c->s->u[4]) && (c->s->r[6] == c->s->r[4] && c->s->d[2] == c->s->d[4])))
            {
                break;
            }
            apply_commands(c, "F");
        }

        while (1)
        {
            if (c->s->d[0] == c->s->d[4] && c->s->l[8] == c->s->l[4])
            {
                break;
            }
            apply_commands(c, "A");
        }

        apply_commands(c, "R' D R' U2 R D' R' U2 R2 F'");

        goto SOLVE_FINAL_LAYER_FROM_RARE;
    }

    SOLVE_FINAL_LAYER_SIDE_SKIP:

    return;
}

void solve_all (Cube * cube)
{
    solve_front_cross(cube);
    solve_front_side(cube);
    solve_second_layer(cube);
    solve_back_cross(cube);
    solve_last_side(cube);
    solve_final_layer(cube);
}

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
}

void cube_test (int test_number)
{

    time_t start_time = time(NULL);

    Cube * cube = new_cube();
    toggle_drawing(cube);
    long unsigned int total_cube_commands = 0;

    for (unsigned int i = 0; i < test_number; i++)
    {
        String_guard * commands = get_random_commands_sequence(100);
        apply_commands(cube, commands->value);
        solve_all(cube);
        total_cube_commands += * cube->c->number_of_strings;
        destroy_string_guard(cube->c);
        cube->c = new_string_guard();

        //draw_cube(cube);
    }

    time_t end_time = time(NULL);

    //string_guard_detail(cube->c);
    printf("%d cubes were solved in %lu seconds\n", test_number, end_time - start_time);
    printf("Total randomizing commands used: %d\n", test_number * 100);
    printf("Commands to solve all cubes: %lu\n", total_cube_commands - test_number * 100);
    printf("Average commands to solve a cube: %lu\n", (total_cube_commands - test_number * 100) / test_number);
    printf("Average time to solve one cube is %f seconds.", (float)(end_time - start_time) / (float)test_number);

    destroy_cube(cube);
}

void cube_console_game_help ()
{
    printf("Use following commands:\n\n");
    printf("...for side moves:\n\n" CYAN);
    
    printf("\t" RED_BG      "           ");
    printf("\t" MAGENTA_BG  "           ");
    printf("\t" YELLOW_BG   "           ");
    printf("\t" WHITE_BG    "           ");
    printf("\t" GREEN_BG    "           ");
    printf("\t" BLUE_BG     "           ");

    printf(RESET_COLOUR "\n");
       
    printf("\t" RED_BG      "           ");
    printf("\t" MAGENTA_BG  "           ");
    printf("\t" YELLOW_BG   "           ");
    printf("\t" WHITE_BG    "           ");
    printf("\t" GREEN_BG    "           ");
    printf("\t" BLUE_BG     "           ");

    printf(RESET_COLOUR "\n");

    printf("\t" RED_BG      "    " BLACK_BG " F " RED_BG        "    ");
    printf("\t" MAGENTA_BG  "    " BLACK_BG " B " MAGENTA_BG    "    ");
    printf("\t" YELLOW_BG   "    " BLACK_BG " L " YELLOW_BG     "    ");
    printf("\t" WHITE_BG    "    " BLACK_BG " R " WHITE_BG      "    ");
    printf("\t" GREEN_BG    "    " BLACK_BG " U " GREEN_BG      "    ");
    printf("\t" BLUE_BG     "    " BLACK_BG " D " BLUE_BG       "    ");

    printf(RESET_COLOUR "\n");

    printf("\t" RED_BG      "           ");
    printf("\t" MAGENTA_BG  "           ");
    printf("\t" YELLOW_BG   "           ");
    printf("\t" WHITE_BG    "           ");
    printf("\t" GREEN_BG    "           ");
    printf("\t" BLUE_BG     "           ");

    printf(RESET_COLOUR "\n");
       
    printf("\t" RED_BG      "           ");
    printf("\t" MAGENTA_BG  "           ");
    printf("\t" YELLOW_BG   "           ");
    printf("\t" WHITE_BG    "           ");
    printf("\t" GREEN_BG    "           ");
    printf("\t" BLUE_BG     "           ");

    printf(RESET_COLOUR "\n\n...you may combine it with number (F1) or apostrophe (R')\n\n");

    printf("...for cube rotation:\n\n\t");

    printf("    "       GREEN_BG    "      " RESET_COLOUR);  
    printf("      "     WHITE_BG    "      " RESET_COLOUR); 

    printf("          "   GREEN_BG    "      " RESET_COLOUR); 
    printf("      "     RED_BG      "      " RESET_COLOUR); 

    printf("          "   RED_BG      "      " RESET_COLOUR); 
    printf("      "     YELLOW_BG   "      " RESET_COLOUR);

    printf("\n\t");

    printf(CYAN "A:  "           GREEN_BG    "      " RESET_COLOUR "  ->  " WHITE_BG     "      " RESET_COLOUR);
    printf(CYAN "    V:    "     GREEN_BG    "      " RESET_COLOUR "  ->  " RED_BG       "      " RESET_COLOUR);
    printf(CYAN "    H:    "     RED_BG      "      " RESET_COLOUR "  ->  " YELLOW_BG    "      " RESET_COLOUR);
    
    printf("\n\t");

    printf("    "       GREEN_BG    "      " RESET_COLOUR);  
    printf("      "     WHITE_BG    "      " RESET_COLOUR); 

    printf("          "   GREEN_BG    "      " RESET_COLOUR); 
    printf("      "     RED_BG      "      " RESET_COLOUR); 

    printf("          "   RED_BG      "      " RESET_COLOUR); 
    printf("      "     YELLOW_BG   "      " RESET_COLOUR); 
    
    printf("\n\n" RESET_COLOUR);

    Cube * show_cube = new_cube();

    draw_cube(show_cube);

    destroy_cube(show_cube);

    printf("\nExecution commands:\n\n");

    printf("\t" CYAN "h" RESET_COLOUR ":\t game help\t");
    printf("\t" CYAN "q" RESET_COLOUR ":\t quit game\t");

    printf("\n");

    printf("\t" CYAN "a" RESET_COLOUR ":\t apply commands\t");
    printf("\t" CYAN "enter" RESET_COLOUR ":\t execute\t");

    printf("\n");

    printf("\t" CYAN "r" RESET_COLOUR ":\t randomize cube\t");
    printf("\t" CYAN "s" RESET_COLOUR ":\t solve cube\t");

    printf("\n");

    printf("\t" CYAN "l" RESET_COLOUR ":\t list history\t");
    printf("\t" CYAN "d" RESET_COLOUR ":\t delete history\t");

    printf("\n");

    printf("\t" CYAN "t" RESET_COLOUR ":\t toggle drawing\t");

    printf("\n" RESET_COLOUR);

    printf("\nTo get started, type: \"F1a\" and press enter\n\n");
}

void cube_console_game ()
{
    Cube * cube = new_cube();

    String_guard * commands = new_string_guard();

    printf("\n\t" RESET_COLOUR);

    printf(RED_BG "      "  RESET_COLOUR "  "       GREEN_BG "  " RESET_COLOUR "  "  GREEN_BG "  "  RESET_COLOUR "  " CYAN_BG "      "  RESET_COLOUR "  " MAGENTA_BG "      " RESET_COLOUR "\n\t");
    printf(RED_BG "  "      RESET_COLOUR "      "   GREEN_BG "  " RESET_COLOUR "  "  GREEN_BG "  "  RESET_COLOUR "  " CYAN_BG "  "      RESET_COLOUR "  " CYAN_BG       "  "      RESET_COLOUR "  " MAGENTA_BG "  " RESET_COLOUR "\n\t");
    printf(RED_BG "  "      RESET_COLOUR "      "   GREEN_BG "  " RESET_COLOUR "  "  GREEN_BG "  "  RESET_COLOUR "  " CYAN_BG "      "  RESET_COLOUR "  " MAGENTA_BG "      " RESET_COLOUR "\n\t");
    printf(RED_BG "  "      RESET_COLOUR "      "   GREEN_BG "  " RESET_COLOUR "  "  GREEN_BG "  "  RESET_COLOUR "  " CYAN_BG "  "      RESET_COLOUR "  " CYAN_BG       "  "      RESET_COLOUR "  " MAGENTA_BG "  " RESET_COLOUR "\n\t");
    printf(RED_BG "      "  RESET_COLOUR "  "       GREEN_BG "      " RESET_COLOUR "  " CYAN_BG "      "  RESET_COLOUR "  " MAGENTA_BG "      " RESET_COLOUR "\n\t");
    
    printf("\n");

    cube_console_game_help();

    get_commands(commands, NULL, cube);
}