#include <stdio.h>
#include "string_guard.h"
#include "cube.h"


int main () {

String_guard * s = get_random_commands_sequence(10);

Cube * cube = new_cube();

execute_commands(s, cube);

string_guard_list_strings(cube->c);

/*
string_guard_push(commands, "_pes");

string_guard_info(commands);

string_guard_push(commands, "9kladivo");

string_guard_info(commands);

printf("%s", commands->value);

    //random command sequence - format for command reader
    char * rcs (int n)
    {
        char * s;
        int size = n * 3;
        s = (char *) malloc(size * sizeof(char));
        if (!s)
        {
            printf("No memory");
            exit(0);
        }
        char * p = s;

        for (int rcsi = 0; (rcsi + 3) < size; rcsi = rcsi + 3)
        {
            printf("a");
            // face
            int f = rand() % 6;

            switch (f)
            {
                case 0: *p = 'F'; break;
                case 1: *p = 'U'; break;
                case 2: *p = 'R'; break;
                case 3: *p = 'L'; break;
                case 4: *p = 'B'; break;
                case 5: *p = 'D'; break;
                default: printf("Error!");
            }

            p++;

            // moves
            char c = (rand() % 3) + '1';
            *p = c;
            p++;
            // separator
            *p = ' ';
            p++;

            printf("%d-", rcsi + 2);

        }

        return s;
    }



    // random command sequence - format for command reader
    char * rcs (int n)
    {
        char * s;
        int size = n * 3;
        s = (char *) malloc(size * sizeof(char));

        //printf("%d", size / 3);
        for (int rcsi = 0; (rcsi + 3) < size; rcsi = rcsi + 3, p++)
        {
            
            //face
            int f = rand() % 6;

            switch (f)
            {
                case 0: s[rcsi] = 'F'; break;
                case 1: s[rcsi] = 'U'; break;
                case 2: s[rcsi] = 'R'; break;
                case 3: s[rcsi] = 'L'; break;
                case 4: s[rcsi] = 'B'; break;
                case 5: s[rcsi] = 'D'; break;
            }

            //moves
            char c = (rand() % 3) + 49;
            s[rcsi + 1] = c;
            //separator
            s[rcsi + 2] = ' ';

            //printf("%d-", rcsi + 2);

        }

        return s;
    }
*/
/* c.s.ued commanc.s.d array, c.s.ued commanc.s.d position */
/*
char * uca = (char *) malloc (1000*sizeof(char));
char * ucp = uca;
char *ucae = (char *)(&uca + 1) - 1;

for (int ucai = 0; ucai < 999; ucai++)
{
    uca[ucai] = ' ';
}
* ucae = '\0';

// apply command
int ac (char s[])
{
    cr(s);

    for (int aci = 0; s[aci]; aci++, ucp++)
    {
        * ucp = s[aci];
    }

    ucp++;
    * ucp = ' ';

    return 0;
}

// save command message
int scm (char s[])
{
    for (int aci = 0; s[aci]; aci++, ucp++)
    {
       * ucp = s[aci];
    }

    ucp++;
    * ucp = ' ';

    return 0;
}

// check side (piece)
int chs (char s1[], char s2[], char c1, char c2)
{
    return (s1[4] == c1 && s2[4] == c2) || (s1[4] == c2 && s2[4] == c1);
}

// is side piece on top - side piece with side 1 color, but without side 2 color
int ispot (char s1[], char s2[], char c1, char c2)
{
    return (s1[4] == c1 || s1[4] == c2) && (c1 != s2[4] && c2 != s2[4]);
}

//check corner (piece)
int chc (char s1[], char s2[], char s3[], char c1, char c2, char c3)
{
    return (s1[4] == c1 || s1[4] == c2 || s1[4] == c3) && (s2[4] == c1 || s2[4] == c2 || s2[4] == c3) && (s3[4] == c1 || s3[4] == c2 || s3[4] == c3);
}

// solve front cross
int sfc (void)
{
// front / up side piece
    // back
    if (chs(c.s.f, c.s.u, c.s.b[1], c.s.u[1]))
    {
        cr("U");
    }
    if (chs(c.s.f, c.s.u, c.s.b[3], c.s.r[5]))
    {
        cr("R");
    }
    if (chs(c.s.f, c.s.u, c.s.b[5], c.s.l[3]))
    {
        cr("L");
    }
    if (chs(c.s.f, c.s.u, c.s.b[7], c.s.d[7]))
    {
        cr("D");
    }
    // right
    if (chs(c.s.f, c.s.u, c.s.r[1], c.s.u[5]))
    {
        cr("R'");
    }
    if (chs(c.s.f, c.s.u, c.s.r[7], c.s.d[5]))
    {
        cr("R");
    }

    // left
    if (chs(c.s.f, c.s.u, c.s.l[1], c.s.u[3]))
    {
        cr("L");
    }
    if (chs(c.s.f, c.s.u, c.s.l[7], c.s.d[3]))
    {
        cr("L'");
    }

    // front
    if (chs(c.s.f, c.s.u, c.s.f[5], c.s.r[3]))
    {
        cr("F");
    }
    if (chs(c.s.f, c.s.u, c.s.f[7], c.s.d[1]))
    {
        cr("F");
    }
    if (chs(c.s.f, c.s.u, c.s.f[3], c.s.l[5]))
    {
        cr("F");
    }

// front / right side piece
    // front 
    if (chs(c.s.f, c.s.r, c.s.f[7], c.s.d[1]))
    {
        cr("D");
    }
    if (chs(c.s.f, c.s.r, c.s.f[3], c.s.l[5]))
    {
        cr("L");
    }
    // right
    if (chs(c.s.f, c.s.r, c.s.r[1], c.s.u[5]))
    {
        cr("R'");
    }
    if (chs(c.s.f, c.s.r, c.s.r[7], c.s.d[5]))
    {
        cr("R");
    }
    // left
    if (chs(c.s.f, c.s.r, c.s.l[1], c.s.u[3]))
    {
        cr("L'");
    }
    if (chs(c.s.f, c.s.r, c.s.l[7], c.s.d[3]))
    {
        cr("L");
    }
    // back
    if (chs(c.s.f, c.s.r, c.s.b[1], c.s.u[1]))
    {
        cr("B");
    }
    if (chs(c.s.f, c.s.r, c.s.b[5], c.s.l[3]))
    {
        cr("B");
    }
    if (chs(c.s.f, c.s.r, c.s.b[7], c.s.d[7]))
    {
        cr("B");
    }
    if (chs(c.s.f, c.s.r, c.s.b[3], c.s.r[5]))
    {
        cr("R2");
    }
// front / down side piece
    // front
    if (chs(c.s.f, c.s.d, c.s.f[3], c.s.l[5]))
    {
        cr("L");
    }
    // right
    if (chs(c.s.f, c.s.d, c.s.r[1], c.s.u[5]))
    {
        cr("R B R'");
    }
    if (chs(c.s.f, c.s.d, c.s.r[7], c.s.d[5]))
    {
        cr("R' B R");
    }
    // left
    if (chs(c.s.f, c.s.d, c.s.l[1], c.s.u[3]))
    {
        cr("L'");
    }
    if (chs(c.s.f, c.s.d, c.s.l[7], c.s.d[3]))
    {
        cr("D");
    }
    // back
    if (chs(c.s.f, c.s.d, c.s.b[3], c.s.r[5]))
    {
        cr("B");
    }
    if (chs(c.s.f, c.s.d, c.s.b[1], c.s.u[1]))
    {
        cr("B");
    }
    if (chs(c.s.f, c.s.d, c.s.b[5], c.s.l[3]))
    {
        cr("B");
    }
    if (chs(c.s.f, c.s.d, c.s.b[7], c.s.d[7]))
    {
        cr("D2");
    }
    // front / left side piece - not done
    // right
    if (chs(c.s.f, c.s.l, c.s.r[1], c.s.u[5]))
    {
        cr("R B R'");
    }
    if (chs(c.s.f, c.s.l, c.s.r[7], c.s.d[5]))
    {
        cr("R' B R");
    }
    // back 
    if (chs(c.s.f, c.s.l, c.s.b[7], c.s.d[7]))
    {
        cr("B");
    }
    if (chs(c.s.f, c.s.l, c.s.b[3], c.s.r[5]))
    {
        cr("B");
    }
    if (chs(c.s.f, c.s.l, c.s.b[1], c.s.u[1]))
    {
        cr("B");
    }
    if (chs(c.s.f, c.s.l, c.s.b[5], c.s.l[3]))
    {
        cr("L");
    }
    // left
    if (chs(c.s.f, c.s.l, c.s.l[1], c.s.u[3]))
    {
        cr("L");
    }
    if (chs(c.s.f, c.s.l, c.s.l[7], c.s.d[3]))
    {
        cr("L'");
    }

    //checking orientation of side pieces

    for (int raFi = 0; raFi < 4; raFi++)
    {
        if (c.s.f[4] != c.s.f[7])
        {
            cr("D2 B R D' R'");
        }
        raF();
    }
    return 0;
}


//solve front side
int sc.s.f (void)
{
    for (int raFi = 0; raFi < 4; raFi++)
    {
//front

       // printf("BEFORE ALGO:\n");
        //d();

        if (chc(c.s.f, c.s.d, c.s.r, c.s.f[2], c.s.u[8], c.s.r[0]))
        {
            cr("R B R'");
        }

        if (chc(c.s.f, c.s.d, c.s.r, c.s.f[0], c.s.u[6], c.s.l[2]))
        {
            cr("L' B' L");
        }

        if (chc(c.s.f, c.s.d, c.s.r, c.s.f[6], c.s.d[0], c.s.l[8]))
        {
            cr("L B L'");
        }
    //back
        if (chc(c.s.f, c.s.d, c.s.r, c.s.d[8], c.s.r[8], c.s.b[6]))
        {
            cr("B");
        }

        if (chc(c.s.f, c.s.d, c.s.r, c.s.r[2], c.s.u[2], c.s.b[0]))
        {
            cr("B");
        }

        if (chc(c.s.f, c.s.d, c.s.r, c.s.u[0], c.s.l[0], c.s.b[2]))
        {
            cr("B");
        }
    //fix into correct corner
        if (chc(c.s.f, c.s.d, c.s.r, c.s.d[6], c.s.l[6], c.s.b[8]))
        {
            cr("R' B R");
        }


        //scm("*");


            //printf("AFTER ALGO: %s\n", uca);
            //d();
            //printf("\nAFTER ROTATION");

            raF();
            

        //printf("");

            //d();
            //printf("\n------------------------------------------------------------------------------------------\n####################################################################################\n");
   
    }

    for (int raFi = 0; raFi < 4; raFi++)
    {
        // if middle piece is not equal to corner piece, turn the corner piece until it is equal ... (corner pieces are already in position)
        while (c.s.f[4] != c.s.f[8])
        {
            cr("R' B R B' R' B R");
        }
        raF();
    }

    return 0;
}

//solve second layer
int ssl (void)
{
    rFD();

    for (int ssli1 = 0; ssli1 < 2; ssli1++)
    {
        //printf("\n#################################################\nSolving side number %d", ssli1 + 1);
        for (int ssli2 = 0; ssli2 < 2; ssli2++)
        {
            //d();
            //dont move with cube, when side pieces are oriented correctly
            if ((c.s.f[3] == c.s.f[4] && c.s.l[5] == c.s.l[4]) && (c.s.f[5] == c.s.f[4] && c.s.r[3] == c.s.r[4]))
            {
                continue;
            }
            //grac.s.b only one piece and moves it to top
            while (1)
            {
            //from front - mc.s.ut not take correct pieces
                if ((c.s.l[5] == c.s.f[4] && c.s.f[3] == c.s.l[4]) || (c.s.l[5] == c.s.r[4] && c.s.f[3] == c.s.f[4]) || (c.s.l[5] == c.s.f[4] && c.s.f[3] == c.s.r[4]))
                {
                    cr("L' U L U F U' F'");
                    break;
                }

                if ((c.s.r[3] == c.s.f[4] && c.s.f[5] == c.s.r[4]) || (c.s.r[3] == c.s.l[4] && c.s.f[5] == c.s.f[4]) || (c.s.r[3] == c.s.f[4] && c.s.f[5] == c.s.l[4]))
                {
                    cr("R U' R' U' F' U F");
                    break;
                }
            //from back
                if (ispot(c.s.f, c.s.u, c.s.b[3], c.s.r[5]))
                {
                    cr("R' U R U B U' B'");
                    break;
                }
                if (ispot(c.s.f, c.s.u, c.s.b[5], c.s.l[3]))
                {
                    cr("L U' L' U' B' U B");
                    break;
                }
                break;
            }
            //from top
            if (ispot(c.s.f, c.s.u, c.s.u[3], c.s.l[1]))
            {
                cr("U");
            }
            if (ispot(c.s.f, c.s.u, c.s.u[1], c.s.b[1]))
            {
                cr("U");
            }
            if (ispot(c.s.f, c.s.u, c.s.u[5], c.s.r[1]))
            {
                cr("U");
            }

            //d();

            while (1)
            {
                if (c.s.f[1] == c.s.f[4])
                {
                    if (c.s.r[4] == c.s.u[7])
                    {
                        cr("U R U' R' U' F' U F");
                        break; 
                    }

                    if (c.s.l[4] == c.s.u[7])
                    {
                        cr("U' L' U L U F U' F'");
                        break;
                    }
                }

                if (c.s.f[1] == c.s.r[4])
                {
                    cr("U2 F' U F U R U' R'");
                    break;
                }

                if (c.s.f[1] == c.s.l[4])
                {
                    cr("U2 F U' F' U' L' U L");
                    break;
                }
                break;
            }
            //d();
        }

        rH();
        rH();
        
    }

    rFD();
    rFD();
    rFD();
    return 0;
}
//solve back cross
int sbc (void)
{
    rFD();
    rFD();

    //correct side pieces
    int csp;
    int sbc_c;

SBC_CHCK_SIDE:

    csp = 0;
    char sq[14] = "D R F R' F' D'";

    for (int cspi = 1; cspi <= 7; cspi += 2)
    {
        if (c.s.f[cspi] == c.s.f[4])
        {
            csp++;
        } 
    }

    if (csp == 4)
    {
        goto SBC_END;
    }

    if (csp < 4)
    {
        cr(sq);
    }

    if (csp == 2)
    {
        //position needed for algorithm
        while (c.s.f[4] != c.s.f[3])
        {
            cr("F");
        }

        if (c.s.f[4] == c.s.f[7])
        {
            cr("F");
        }

        if (c.s.f[4] == c.s.f[1])
        {

            cr(sq);
        }

        if (c.s.f[4] == c.s.f[5])
        {
            cr(sq);
        }
    }

    if (sbc_c == 5)
    {
        printf("Program failed while solving back corner!");
        exit(0);
    }

    sbc_c++;

    goto SBC_CHCK_SIDE;

    SBC_END:

    rFD();
    rFD();

    return 0;
}

//solve last side
int sc.s.l (void)
{
    rFD();
    rFD();

    // uncorrect corner pieces //// ("incorrect" is correct)
    int uccp;
    int sc.s.l_c = 0;

Sc.s.l_CHCK_ORI:

    uccp = 0;

    for (int uccpi = 0; uccpi <= 8; uccpi += 2)
    {
        if (c.s.f[uccpi] != c.s.f[4])
        {
            uccp++;
        } 
    }

    if (uccp == 0)
    {
        goto Sc.s.l_END;
    }

    if (uccp == 4)
    {
        while (!(c.s.l[2] == c.s.f[4] && c.s.l[8] == c.s.f[4]))
        {
            F(1);
        }
    }

    if (uccp == 3)
    {
        while (!(c.s.f[6] == c.s.f[4]))
        {
            F(1);
        }
    }

    if (uccp == 2)
    {
        while (!(c.s.r[0] == c.s.f[4]))
        {
            F(1);
        }
    }

    //d();

    cr("R F R' F R F F R'");

    //d();
    if (sc.s.l_c == 5)
    {
        printf("Program failed while solving back face!");
        exit(0);
    }

    sc.s.l_c++;

    goto Sc.s.l_CHCK_ORI;

Sc.s.l_END:

    rFD();
    rFD();

    return 0;
}

int sfl (void)
{

    rFD();
    rFD();

    //d();

    //sides with correct cornec.s.r
    int scc = 0;

    if (c.s.u[6] == c.s.u[8])
    {
        scc++;
    }

    if (c.s.r[0] == c.s.r[6])
    {
        scc++;
    }

    if (c.s.d[0] == c.s.d[2])
    {
        scc++;
    }

    if (c.s.l[2] == c.s.l[8])
    {
        scc++;
    }

//----------------------------

    if (scc > 0)
    {

        FROM_RARE:

        //d();

        while (1)
        {
            if ((c.s.u[6] == c.s.u[4] && c.s.u[8] == c.s.u[4]) || (c.s.r[0] == c.s.r[4] && c.s.r[6] == c.s.r[4]) || (c.s.d[0] == c.s.d[4] && c.s.d[2] == c.s.d[4]) || (c.s.l[2] == c.s.l[4] && c.s.l[8] == c.s.l[4]))
            {
                break;
            }

            F(1);
        }
        //d();
        //printf("%d", scc);

        while (1)
        {
            if (c.s.u[6] == c.s.u[4] && c.s.u[8] == c.s.u[4])
            {
                break;
            }

            raF();
        }

        //d();
        //main top layer alorithm
        if (scc < 2)
        {
            cr("R' D R' U2 R D' R' U2 R2 F'");
        }
        //d();

        while (1)
        {
            if (c.s.u[6] == c.s.u[4] && c.s.u[8] == c.s.u[4])
            {
                break;
            }

            raF();
        }

        //d();

        for (int i = 0; i < 2; i++)
        {
            if (c.s.d[1] == c.s.l[4])
            {
                cr("D2 F L R' D2 L' R F D2");
            }

            if (c.s.d[1] == c.s.r[4])
            {
                cr("D2 F' L R' D2 L' R F' D2");
            }

            if (c.s.u[7] != c.s.u[4] && c.s.r[3] != c.s.r[4] && c.s.d[1] != c.s.d[4] && c.s.l[5] != c.s.l[4])
            {
                cr("D2 F' L R' D2 L' R F' D2");
            }

            while (1)
            {
                if ((c.s.u[6] == c.s.u[4] && c.s.u[8] == c.s.u[4] && c.s.u[7] == c.s.u[4]) || (c.s.u[7] != c.s.u[4] && c.s.r[3] != c.s.r[4] && c.s.d[1] != c.s.d[4] && c.s.l[5] != c.s.l[4]))
                {
                    break;
                }
                raF();
            }
        }

        //d();
    }
    ec.s.le // there is no side with correct cornec.s.r yet
    {
        while (1)
        {
            if (((c.s.d[0] == c.s.d[4] && c.s.l[8] == c.s.l[4]) && (c.s.u[8] == c.s.u[4] && c.s.r[0] == c.s.r[4])) || ((c.s.l[2] == c.s.l[4] && c.s.u[6] == c.s.u[4]) && (c.s.r[6] == c.s.r[4] && c.s.d[2] == c.s.d[4])))
            {
                break;
            }

            F(1);
        }

        while (1)
        {
            if (c.s.d[0] == c.s.d[4] && c.s.l[8] == c.s.l[4])
            {
                break;
            }
            raF();
        }

        cr("R' D R' U2 R D' R' U2 R2 F'");

        goto FROM_RARE;
    }
        //d();
    return 0;
}

//solve whole cube
int swc (void)
{
    sfc();
    sc.s.f();
    ssl();
    sbc();
    sc.s.l();
    sfl();
    return 0;
}


cc();
cr(rcs(235));
swc();
d();
*/
/*
rand() % 6 creates infinite loop sometimes, if suc.s.btitued by number, does not make trouble
232 rcs hidden error
235
..examples


for (int test = 200; test <= 210; test++)
{
    cc();
    cr(rcs(test));
    swc();
    d();
}
*/
/*
cr(rcs(352));
sfc();
sc.s.f();
ssl();
sbc();
sc.s.l();
sfl();
*/


  return 0;
}