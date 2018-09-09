#include <stdio.h>
#include <stdlib.h>

/*
#define r   "\x1b[31m"
#define g   "\x1b[32m"
#define y   "\x1b[33m"
#define b   "\x1b[34m"
#define m   "\x1b[35m"
#define w   "\x1b[37m"

//reset colour 
#define rc   "\x1b[0m"

//drawing sign
#define sign "\u25A0" // square character used while printing cube
*/

char * rcs(); 

int main () {

    const int side = 3;

    const int area = side * side;

    char fs[area];
    char bs[area];
    char ls[area];
    char rs[area];
    char us[area];
    char ds[area];

    char ts[area]; /* temporary side - copying purposes */

    /* create cube */
    int cc (void)
    {
        /* fill area */
        int fa (char character[], char colour)
        {
            for (int fai = 0; fai < area; fai++)
            {
                character[fai] = colour;
            }
        }

        fa(fs, 'r');
        fa(bs, 'm');
        fa(ls, 'b');
        fa(rs, 'g');
        fa(us, 'y');
        fa(ds, 'w');
        fa(ts, '_');

        return 0;
    }

    /* draw cube - for any size of cube */
    int d (void)
    {
        /* print spaces */
        int ps (void)
        {
            for (int psi = 0; psi < side; psi++)
            {
                printf(" ");
            }
            return 0;
        }

        /* draw row */
        int dr (char character[], int row)
        {
 
            for (int dri = row * side; dri < (row + 1) * side; dri++)
            {
                switch (character[dri])
                {
                    case 'r': printf("\x1b[31m\u25A0\x1b[0m"); break;
                    case 'w': printf("\x1b[37m\u25A0\x1b[0m"); break;
                    case 'y': printf("\x1b[33m\u25A0\x1b[0m"); break;
                    case 'b': printf("\x1b[34m\u25A0\x1b[0m"); break;
                    case 'm': printf("\x1b[35m\u25A0\x1b[0m"); break;
                    case 'g': printf("\x1b[32m\u25A0\x1b[0m"); break;
                }
            }

            return 0;
        }


        printf("\n");

        for (int wri = 0; wri < side; wri++)
        {
            ps();
            ps();
            dr(us, wri);
            printf("\n");
        }

        for (int wri = 0; wri < side; wri++)
        {
            ps();
            dr(ls, wri);
            dr(fs, wri);
            dr(rs, wri);
            dr(bs, wri);
            printf("\n");
        }


        for (int wri = 0; wri < side; wri++)
        {
            ps();
            ps();
            dr(ds, wri);
            printf("\n");
        }
    }

    char t;

    /* boolean draw cube - draws cube after each movement if set to 1 */
    int bdc = 0;

    /* turn own side */
    int tos (char s[])
    {
        t = s[0];
        s[0] = s[6];
        s[6] = s[8];
        s[8] = s[2];
        s[2] = t;

        t = s[1];
        s[1] = s[3];
        s[3] = s[7];
        s[7] = s[5];
        s[5] = t;
        
        return 0;
    }

    /* turns own side another direction */
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

    /* additional functions - extends movement functions */
    int af (char s[], int (*f)())
    {

        /* boolean draw cube function */
        int bdcf (void)
        {
            if (bdc == 1) d();

            return 0;
        }

        tos(s);

        bdcf();
    }


    /* movement functions */
    int F (int rot)
    {
        for (; rot; rot--)
        {       
            if (bdc == 1) {printf("\n      %s\n", __func__);}
            t = ls[2];
            ls[2] = ds[0];
            ds[0] = rs[6];
            rs[6] = us[8];
            us[8] = t;

            t = ls[5];
            ls[5] = ds[1];
            ds[1] = rs[3];
            rs[3] = us[7];
            us[7] = t;

            t = ls[8];
            ls[8] = ds[2];
            ds[2] = rs[0];
            rs[0] = us[6];
            us[6] = t;

            af(fs, F);
        }
        return 0;
    }

    int B (int rot)
    {
        for (; rot; rot--)
        {       
            if (bdc == 1) {printf("\n      %s\n", __func__);}
            /*
            t = us[0];
            us[0] = ls[6];
            ls[6] = ds[8];
            ds[8] = rs[2];
            rs[2] = t;

            t = us[1];
            us[1] = ls[3];
            ls[3] = ds[7];
            ds[7] = rs[5];
            rs[5] = t;

            t = us[2];
            us[2] = ls[0];
            ls[0] = ds[6];
            ds[6] = rs[8];
            rs[8] = t;
            */

            t = rs[2];
            rs[2] = ds[8];
            ds[8] = ls[6];
            ls[6] = us[0];
            us[0] = t;

            t = rs[5];
            rs[5] = ds[7];
            ds[7] = ls[3];
            ls[3] = us[1];
            us[1] = t;

            t = rs[8];
            rs[8] = ds[6];
            ds[6] = ls[0];
            ls[0] = us[2];
            us[2] = t;

            af(bs, B);
        }
        return 0;
    }

    int R (int rot)
    {
        for (; rot; rot--)
        {       
            if (bdc == 1) {printf("\n      %s\n", __func__);}
            t = fs[2];
            fs[2] = ds[2];
            ds[2] = bs[6];
            bs[6] = us[2];
            us[2] = t;

            t = fs[5];
            fs[5] = ds[5];
            ds[5] = bs[3];
            bs[3] = us[5];
            us[5] = t;

            t = fs[8];
            fs[8] = ds[8];
            ds[8] = bs[0];
            bs[0] = us[8];
            us[8] = t;

            af(rs, R);
        }
        return 0;
    }

    int L (int rot)
    {
        for (; rot; rot--)
        {   
            if (bdc == 1) {printf("\n      %s\n", __func__);}
            t = fs[0];
            fs[0] = us[0];
            us[0] = bs[8];
            bs[8] = ds[0];
            ds[0] = t;

            t = fs[3];
            fs[3] = us[3];
            us[3] = bs[5];
            bs[5] = ds[3];
            ds[3] = t;

            t = fs[6];
            fs[6] = us[6];
            us[6] = bs[2];
            bs[2] = ds[6];
            ds[6] = t;

            af(ls, L);
        }

        return 0;
    }

    int U (int rot)
    {
        for (; rot; rot--)
        {   
            if (bdc == 1) {printf("\n      %s\n", __func__);}
            t = fs[0];
            fs[0] = rs[0];
            rs[0] = bs[0];
            bs[0] = ls[0];
            ls[0] = t;

            t = fs[1];
            fs[1] = rs[1];
            rs[1] = bs[1];
            bs[1] = ls[1];
            ls[1] = t;

            t = fs[2];
            fs[2] = rs[2];
            rs[2] = bs[2];
            bs[2] = ls[2];
            ls[2] = t;

            af(us, U);
        }

        return 0;
    }

    int D (int rot)
    {
        for (; rot; rot--)
        {   
            if (bdc == 1) {printf("\n      %s\n", __func__);}
            t = fs[6];
            fs[6] = ls[6];
            ls[6] = bs[6];
            bs[6] = rs[6];
            rs[6] = t;

            t = fs[7];
            fs[7] = ls[7];
            ls[7] = bs[7];
            bs[7] = rs[7];
            rs[7] = t;

            t = fs[8];
            fs[8] = ls[8];
            ls[8] = bs[8];
            bs[8] = rs[8];
            rs[8] = t;

            af(ds, D);
        }

        return 0;
    }

    /* copy array */
    int ca(char caa[], char cab[])
    {
        for (int cai = 0; caa[cai]; cai++)
        {
            caa[cai] = cab[cai];
        }

        return 0;
    }

    /* rotate horizontal (to right) */
    int rH (void)
    {
        tos(us);
        atos(ds);

        ca(ts, fs);
        ca(fs, rs);
        ca(rs, bs);
        ca(bs, ls);
        ca(ls, ts);

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

    // command reader
    int cr (char a[])
    {

        // number of commands
        int l = 0, i = 0;
        while (a[i])
        {
            if (a[i] == ' ') l++;
            i++;
        }
        l += 2; // length of command sequence

        /* command sequence */
        char cs[l][2];

        cs[l-1][0] = '\0';

        /* initialize command sequence with '_' - also required for movements without number "F D" opposite to "F1 D1" */
        for (int csif = 0; cs[csif][0]; csif++)
        {
            cs[csif][0] = '_';
            cs[csif][1] = '_';
        }

        /* filling command sequence from string input */
        for (int cri = 0, csi = 0, csj = 0; a[cri]; cri++)
        {
            if (a[cri] != ' ')
            {
                cs[csi][csj] = a[cri];
                /* backtick means 3 times (reversed movement)*/
                if (a[cri] == '\'')
                {
                    cs[csi][csj] = '3';
                }
                csj++;
            }
            else
            {
                csi++;
                csj = 0;
            }
        }

        /* command executioner */
        int ce (void)
        {
            for (int cei = 0; cs[cei][0]; cei++)
            {
                if (cs[cei][1] > 47 && cs[cei][1] < 58)
                {
                    cs[cei][1] = cs[cei][1] - 48;
                }
                else
                {
                    cs[cei][1] = 1;
                }

                switch (cs[cei][0])
                {
                    case 'F': F(cs[cei][1]); break;
                    case 'B': B(cs[cei][1]); break;
                    case 'R': R(cs[cei][1]); break;
                    case 'L': L(cs[cei][1]); break;
                    case 'U': U(cs[cei][1]); break;
                    case 'D': D(cs[cei][1]); break;
                }
            }
            return 0;
        }

        ce();

        return 0;
    }

    /* toggle drawing */
    int td (void)
    {
        if (bdc == 0)
        {
            bdc = 1;
        }
        else
        {
            bdc = 0;
        }

        return 0;
    }

    /* random command sequence - format for command reader */
    char * rcs (int n)
    {
        char * s;
        int size = n * 3;
        s = (char *) malloc(size * sizeof(char));
        char * p = s;

        for (int rcsi = 0; (rcsi + 3) < size; rcsi = rcsi + 3)
        {
            
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
                default: *p = 'F'; break;
            }

            p++;

            // moves
            char c = (rand() % 3) + 49;
            *p = c;
            p++;
            // separator
            *p = ' ';
            p++;

            //printf("%d-", rcsi + 2);

        }

        return s;
    }


/*
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
/* used commands array, used commands position */
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
*/
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
    if (chs(fs, us, bs[1], us[1]))
    {
        cr("U");
    }
    if (chs(fs, us, bs[3], rs[5]))
    {
        cr("R");
    }
    if (chs(fs, us, bs[5], ls[3]))
    {
        cr("L");
    }
    if (chs(fs, us, bs[7], ds[7]))
    {
        cr("D");
    }
    // right
    if (chs(fs, us, rs[1], us[5]))
    {
        cr("R'");
    }
    if (chs(fs, us, rs[7], ds[5]))
    {
        cr("R");
    }

    // left
    if (chs(fs, us, ls[1], us[3]))
    {
        cr("L");
    }
    if (chs(fs, us, ls[7], ds[3]))
    {
        cr("L'");
    }

    // front
    if (chs(fs, us, fs[5], rs[3]))
    {
        cr("F");
    }
    if (chs(fs, us, fs[7], ds[1]))
    {
        cr("F");
    }
    if (chs(fs, us, fs[3], ls[5]))
    {
        cr("F");
    }

// front / right side piece
    // front 
    if (chs(fs, rs, fs[7], ds[1]))
    {
        cr("D");
    }
    if (chs(fs, rs, fs[3], ls[5]))
    {
        cr("L");
    }
    // right
    if (chs(fs, rs, rs[1], us[5]))
    {
        cr("R'");
    }
    if (chs(fs, rs, rs[7], ds[5]))
    {
        cr("R");
    }
    // left
    if (chs(fs, rs, ls[1], us[3]))
    {
        cr("L'");
    }
    if (chs(fs, rs, ls[7], ds[3]))
    {
        cr("L");
    }
    // back
    if (chs(fs, rs, bs[1], us[1]))
    {
        cr("B");
    }
    if (chs(fs, rs, bs[5], ls[3]))
    {
        cr("B");
    }
    if (chs(fs, rs, bs[7], ds[7]))
    {
        cr("B");
    }
    if (chs(fs, rs, bs[3], rs[5]))
    {
        cr("R2");
    }
// front / down side piece
    // front
    if (chs(fs, ds, fs[3], ls[5]))
    {
        cr("L");
    }
    // right
    if (chs(fs, ds, rs[1], us[5]))
    {
        cr("R B R'");
    }
    if (chs(fs, ds, rs[7], ds[5]))
    {
        cr("R' B R");
    }
    // left
    if (chs(fs, ds, ls[1], us[3]))
    {
        cr("L'");
    }
    if (chs(fs, ds, ls[7], ds[3]))
    {
        cr("D");
    }
    // back
    if (chs(fs, ds, bs[3], rs[5]))
    {
        cr("B");
    }
    if (chs(fs, ds, bs[1], us[1]))
    {
        cr("B");
    }
    if (chs(fs, ds, bs[5], ls[3]))
    {
        cr("B");
    }
    if (chs(fs, ds, bs[7], ds[7]))
    {
        cr("D2");
    }
    // front / left side piece - not done
    // right
    if (chs(fs, ls, rs[1], us[5]))
    {
        cr("R B R'");
    }
    if (chs(fs, ls, rs[7], ds[5]))
    {
        cr("R' B R");
    }
    // back 
    if (chs(fs, ls, bs[7], ds[7]))
    {
        cr("B");
    }
    if (chs(fs, ls, bs[3], rs[5]))
    {
        cr("B");
    }
    if (chs(fs, ls, bs[1], us[1]))
    {
        cr("B");
    }
    if (chs(fs, ls, bs[5], ls[3]))
    {
        cr("L");
    }
    // left
    if (chs(fs, ls, ls[1], us[3]))
    {
        cr("L");
    }
    if (chs(fs, ls, ls[7], ds[3]))
    {
        cr("L'");
    }

    //checking orientation of side pieces

    for (int raFi = 0; raFi < 4; raFi++)
    {
        if (fs[4] != fs[7])
        {
            cr("D2 B R D' R'");
        }
        raF();
    }
    return 0;
}


//solve front side
int sfs (void)
{
    for (int raFi = 0; raFi < 4; raFi++)
    {
//front
/*
        printf("BEFORE ALGO:\n");
        d();
*/
        if (chc(fs, ds, rs, fs[2], us[8], rs[0]))
        {
            cr("R B R'");
        }

        if (chc(fs, ds, rs, fs[0], us[6], ls[2]))
        {
            cr("L' B' L");
        }

        if (chc(fs, ds, rs, fs[6], ds[0], ls[8]))
        {
            cr("L B L'");
        }
    //back
        if (chc(fs, ds, rs, ds[8], rs[8], bs[6]))
        {
            cr("B");
        }

        if (chc(fs, ds, rs, rs[2], us[2], bs[0]))
        {
            cr("B");
        }

        if (chc(fs, ds, rs, us[0], ls[0], bs[2]))
        {
            cr("B");
        }
    //fix into correct corner
        if (chc(fs, ds, rs, ds[6], ls[6], bs[8]))
        {
            cr("R' B R");
        }

/*
        scm("*");


            printf("AFTER ALGO: %s\n", uca);
            d();
            printf("\nAFTER ROTATION");
*/
            raF();
            
/*
        printf("");

            d();
            printf("\n------------------------------------------------------------------------------------------\n####################################################################################\n");
*/    
    }

    for (int raFi = 0; raFi < 4; raFi++)
    {
        // if middle piece is not equal to corner piece, turn the corner piece until it is equal ... (corner pieces are already in position)
        while (fs[4] != fs[8])
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
            if ((fs[3] == fs[4] && ls[5] == ls[4]) && (fs[5] == fs[4] && rs[3] == rs[4]))
            {
                continue;
            }
            //grabs only one piece and moves it to top
            while (1)
            {
            //from front - must not take correct pieces
                if ((ls[5] == fs[4] && fs[3] == ls[4]) || (ls[5] == rs[4] && fs[3] == fs[4]) || (ls[5] == fs[4] && fs[3] == rs[4]))
                {
                    cr("L' U L U F U' F'");
                    break;
                }

                if ((rs[3] == fs[4] && fs[5] == rs[4]) || (rs[3] == ls[4] && fs[5] == fs[4]) || (rs[3] == fs[4] && fs[5] == ls[4]))
                {
                    cr("R U' R' U' F' U F");
                    break;
                }
            //from back
                if (ispot(fs, us, bs[3], rs[5]))
                {
                    cr("R' U R U B U' B'");
                    break;
                }
                if (ispot(fs, us, bs[5], ls[3]))
                {
                    cr("L U' L' U' B' U B");
                    break;
                }
                break;
            }
            //from top
            if (ispot(fs, us, us[3], ls[1]))
            {
                cr("U");
            }
            if (ispot(fs, us, us[1], bs[1]))
            {
                cr("U");
            }
            if (ispot(fs, us, us[5], rs[1]))
            {
                cr("U");
            }

            //d();

            while (1)
            {
                if (fs[1] == fs[4])
                {
                    if (rs[4] == us[7])
                    {
                        cr("U R U' R' U' F' U F");
                        break; 
                    }

                    if (ls[4] == us[7])
                    {
                        cr("U' L' U L U F U' F'");
                        break;
                    }
                }

                if (fs[1] == rs[4])
                {
                    cr("U2 F' U F U R U' R'");
                    break;
                }

                if (fs[1] == ls[4])
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
        if (fs[cspi] == fs[4])
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
        while (fs[4] != fs[3])
        {
            cr("F");
        }

        if (fs[4] == fs[7])
        {
            cr("F");
        }

        if (fs[4] == fs[1])
        {

            cr(sq);
        }

        if (fs[4] == fs[5])
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
int sls (void)
{
    rFD();
    rFD();

    // uncorrect corner pieces //// ("incorrect" is correct)
    int uccp;
    int sls_c = 0;

SLS_CHCK_ORI:

    uccp = 0;

    for (int uccpi = 0; uccpi <= 8; uccpi += 2)
    {
        if (fs[uccpi] != fs[4])
        {
            uccp++;
        } 
    }

    if (uccp == 0)
    {
        goto SLS_END;
    }

    if (uccp == 4)
    {
        while (!(ls[2] == fs[4] && ls[8] == fs[4]))
        {
            F(1);
        }
    }

    if (uccp == 3)
    {
        while (!(fs[6] == fs[4]))
        {
            F(1);
        }
    }

    if (uccp == 2)
    {
        while (!(rs[0] == fs[4]))
        {
            F(1);
        }
    }

    //d();

    cr("R F R' F R F F R'");

    //d();
    if (sls_c == 5)
    {
        printf("Program failed while solving back face!");
        exit(0);
    }

    sls_c++;

    goto SLS_CHCK_ORI;

SLS_END:

    rFD();
    rFD();

    return 0;
}

int sfl (void)
{

    rFD();
    rFD();

    //d();

    //sides with correct corners
    int scc = 0;

    if (us[6] == us[8])
    {
        scc++;
    }

    if (rs[0] == rs[6])
    {
        scc++;
    }

    if (ds[0] == ds[2])
    {
        scc++;
    }

    if (ls[2] == ls[8])
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
            if ((us[6] == us[4] && us[8] == us[4]) || (rs[0] == rs[4] && rs[6] == rs[4]) || (ds[0] == ds[4] && ds[2] == ds[4]) || (ls[2] == ls[4] && ls[8] == ls[4]))
            {
                break;
            }

            F(1);
        }
        //d();
        //printf("%d", scc);

        while (1)
        {
            if (us[6] == us[4] && us[8] == us[4])
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
            if (us[6] == us[4] && us[8] == us[4])
            {
                break;
            }

            raF();
        }

        //d();

        for (int i = 0; i < 2; i++)
        {
            if (ds[1] == ls[4])
            {
                cr("D2 F L R' D2 L' R F D2");
            }

            if (ds[1] == rs[4])
            {
                cr("D2 F' L R' D2 L' R F' D2");
            }

            if (us[7] != us[4] && rs[3] != rs[4] && ds[1] != ds[4] && ls[5] != ls[4])
            {
                cr("D2 F' L R' D2 L' R F' D2");
            }

            while (1)
            {
                if ((us[6] == us[4] && us[8] == us[4] && us[7] == us[4]) || (us[7] != us[4] && rs[3] != rs[4] && ds[1] != ds[4] && ls[5] != ls[4]))
                {
                    break;
                }
                raF();
            }

        }

        //d();
    }
    else // there is no side with correct corners yet
    {

        while (1)
        {
            if (((ds[0] == ds[4] && ls[8] == ls[4]) && (us[8] == us[4] && rs[0] == rs[4])) || ((ls[2] == ls[4] && us[6] == us[4]) && (rs[6] == rs[4] && ds[2] == ds[4])))
            {
                break;
            }

            F(1);
        }

        while (1)
        {
            if (ds[0] == ds[4] && ls[8] == ls[4])
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
    sfs();
    ssl();
    sbc();
    sls();
    sfl();
    return 0;
}


cc();
cr(rcs(235));
swc();
d();

/*
232 rcs hidden error
235

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
sfs();
ssl();
sbc();
sls();
sfl();
*/

  return 0;
}