/*
 * main.c
 * By: Ali Emad Ali
 * Date created: 2021-06-21
 */

#define TRY_PARSER		0

#if TRY_PARSER

#include "../Inc/Std_Types.h"
#include <math.h>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Inc/MathAdv.h"
#include "../Inc/StringAdv.h"
#include "../Inc/LinkedList.h"
#include "../Inc/MathParser_config.h"
#include "../Inc/MathParser.h"
#include "../Inc/ParserApplication.h"


double speed;

int main()
{
    printf("No spaces allowed!\n");
    printf(
    	"Make sure the function is continuous on the range of integration,\n");
    printf("no error handling for this so far.\n\n");

    printf("Speed :\n");
    printf("1.normal    2.fast\n");

    int speedMode;
    scanf("%d", &speedMode);

    if (speedMode == 1)
        speed = 1;
    else if (speedMode == 2)
        speed = 10;

    printf("0. parser tryout\n");
    printf("1. Single integral\n");
    printf("2. double integral\n");
    printf("3. triple integral\n");
    printf("4. equation solver\n");
    printf("5. derivative\n");

    int mode;
    scanf("%d", &mode);

    if (mode == 0)
    {
        char* str = malloc(500 * sizeof(char));

        printf("f(x) = ");
        scanf("%s", str);

        double x;
        printf("x = ");
        scanf("%lf", &x);

        MathParser_t p;
        MathParser_b8SetExpressionString(&p, str, 0, strlen(str) - 1);
        double result = MathParser_d64Evaluate(&p, x, 0.0, 0.0);
        printf("f(%lf) = %lf\n", x, result);

        free(str);
    }
    else if (mode == 1)
    {
        double xL;
        double xH;

        char* str = malloc(500 * sizeof(char));

        printf("f(x) = ");
        scanf("%s", str);

        printf("lower x = ");
        scanf("%lf", &xL);

        printf("higher x = ");
        scanf("%lf", &xH);

        printf("\nCalculating...");

        double RESULT = single_integral(str, xL, xH);

        printf("\n");

        printf("%c%.3lf\n", (char)244, xH);
        printf("%c", (char)179);
        printf("         ( ");
        printf("%s", str);
        printf(" ) dx ");
        printf("%c ", (char)247);

        free(str);

        printf("%.10lf\n", RESULT);

        printf("%c%.3lf\n", (char)245, xL);
    }

    else if (mode == 2)
    {
        double xL;
        double xH;
        double yL;
        double yH;

        char* str = malloc(500 * sizeof(char));

        printf("f(x, y) = ");
		scanf("%s", str);

        printf("lower x = ");
        scanf("%lf", &xL);

        printf("higher x = ");
        scanf("%lf", &xH);

        printf("lower y = ");
        scanf("%lf", &yL);

        printf("higher y = ");
        scanf("%lf", &yH);

        printf("\nCalculating...");

        double RESULT = double_integral(str, xL, xH, yL, yH);

        printf("\nresult = %.10lf", RESULT);

//        cout.precision(3);
//        cout << char(244) << setiosflags(ios::left) << setw(9) << yH << char(244) << xH << endl;
//        cout.precision(10);
//        cout << char(179) << "         " << char(179) << "         ( " << str << " ) dxdy " << char(247) << ' ' << RESULT << endl;
//        delete[] str;
//        cout.precision(3);
//        cout << char(245) << setiosflags(ios::left) << setw(9) << yL << char(245) << xL << endl;
    }

    else if (mode == 3)
    {
        double xL;
        double xH;
        double yL;
        double yH;
        double zL;
        double zH;

        char* str = malloc(500 * sizeof(char));

        printf("f(x, y, z) = ");
		scanf("%s", str);

        printf("lower x = ");
        scanf("%lf", &xL);

        printf("higher x = ");
        scanf("%lf", &xH);

        printf("lower y = ");
        scanf("%lf", &yL);

        printf("higher y = ");
        scanf("%lf", &yH);

        printf("lower z = ");
        scanf("%lf", &zL);

        printf("higher z = ");
        scanf("%lf", &zH);

        printf("\nCalculating...");

        double RESULT = triple_integral(str, xL, xH, yL, yH, zL, zH);

        printf("\nresult = %.10lf", RESULT);

//        cout.precision(3);
//        cout << char(244) << setiosflags(ios::left) << setw(9) << zH << char(244) << setiosflags(ios::left) << setw(9) << yH << char(244) << xH << endl;
//        cout.precision(10);
//        cout << char(179) << "         " << char(179) << "         " << char(179) << "         ( " << str << " ) dxdydz " << char(247) << ' ' << RESULT << endl;
//        delete[] str;
//        cout.precision(3);
//        cout << char(245) << setiosflags(ios::left) << setw(9) << zL << char(245) << setiosflags(ios::left) << setw(9) << yL << char(245) << xL << endl;

    }
    else if (mode == 4)
    {
        double X0;

        char* str = malloc(500 * sizeof(char));

        printf("let : f(x) = 0\n");

        printf("f(x) = ");
		scanf("%s", str);

        printf("X0 = ");
        scanf("%lf", &X0);

        printf("\nCalculating...\n");

        double result = solve(str, X0);

        printf("\nx = %.10lf", result);
    }
    else if (mode == 5)
    {
        int n;
        double x;

        char* str = malloc(500 * sizeof(char));

        printf("f(x) = ");
		scanf("%s", str);

		printf("find nth derivative... n = ");
		scanf("%d", &n);

        printf("x = ");
        scanf("%lf", &x);

        printf("\nCalculating...\n");

        double result = derivative(str, n, x);

        printf(" %d", n);

        for (int i = 0; i < LEN(str) + 3; i++)
            printf(" ");

        printf("|\nd  %c", (char)218);

        for (int i = 0; i < LEN(str); i++)
            printf(" ");

        printf("%c|\n---|", (char)191);

        printf("%s|| %c %.10lf\n  %d%c", str, (char)247, result, n, (char)192);

        for (int i = 0; i < LEN(str); i++)
        	printf(" ");

        printf("%c|\ndx", (char)217);

        for (int i = 0; i < LEN(str) + 3; i++)
        	printf(" ");

        printf("|x=%lf\n", x);
    }
    printf("\nPress any key to exit\n");

    _getch();
    return 0;
}

#endif	/*	TRY_PARSER	*/
