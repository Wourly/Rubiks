#include "cube.h"

int main () {

  //cube_console_game();

  //cube_test(50000);

Cube * c = new_cube();

toggle_drawing(c);


for (int i = 0; i < 100000; i++)
{
    String_guard * string_guard = get_random_commands_sequence(100);
    execute_commands(string_guard, c);
    solve_front_cross(c);
    destroy_string_guard(string_guard);
    destroy_string_guard(c->c);
    c->c = new_string_guard();
}

destroy_cube(c);

  getc(stdin);

  return 0;
}