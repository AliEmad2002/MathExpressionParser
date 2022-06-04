/// 2021-06-21
/// Code: Ali Emad
#include <iostream>
#include <math.h>
#include<conio.h>
#include<iomanip>
#include<ctime>
using namespace std;
///parser needed functions:
int type(char ch);
double To_int(char* str, int i, int j);
double pos_powr(double i, int n);
double To_after_point(char* str, int j, int k);
void stuck(char* str, char ch, int k);
int find_closing_bracket(char* str, int opening_B);
double EVAL(char* str, int start, int End, double x, double y, double z);
double numerical_EVAL(double num[50], char op[30], int start, int end_num);
int LEN(char* str);
///math functions:
double single_integral(char* str, double xL, double xH);
double double_integral(char* str, double xL, double xH, double yL, double yH);
double triple_integral(char* str, double xL, double xH, double yL, double yH, double zL, double zH);
int Number_Of_Digits(double x);
double solve(char* str, double X0);
double factorial(int n);
double combination(int n, int k);
double derivative(char* str, int n, double a);
bool check_continuity(char* str, double xL, double xH, double yL, double yH, double zL, double zH); ///not done yet

double speed;
///=============================================================================
struct parser
{
    char* str;
    int n; ///Length of str array.
    double num[50]; ///Here I store numbers
    char op[30]; ///Here I store operators
    int numCount;
    int opCount;
    bool never_ran = true;
    double eval(double x = 0.0, double y = 0.0, double z = 0.0, int nC = 0, int oC = 0)
    {
        for (int k = 0; str[k] != '\0' && never_ran; k++)
        {
            ///any '-' without a number before it, I put zero before it:
            if (str[k] == '-')
            {
                if (k == 0)
                    stuck(str, '0', k);
                else if (str[k - 1] == '[' || str[k - 1] == '(')
                    stuck(str, '0', k);
            }
            ///any number not followed by another number, a pint, a right bracket, or an operator, and is not the last in the str: I put '*' after it:
            else if ((type(str[k]) == 0 || str[k] == 'x' || str[k] == 'y' || str[k] == 'z' || str[k] == 'e')
                && type(str[k + 1]) != 0 && str[k + 1] != '.' && str[k + 1] != ']' && str[k + 1] != ')' && type(str[k + 1]) != 2 && str[k + 1] != '\0')
            {
                stuck(str, '*', k + 1);
            }

            else if (str[k] == 'p' && str[k + 1] == 'i' && type(str[k + 2]) != 0 && str[k + 2] != '.' && str[k + 2] != ']' && str[k + 2] != ')' && type(str[k + 2]) != 2 && str[k + 2] != '\0')
            {
                stuck(str, '*', k + 2);
            }
        }
        never_ran = false;
        n = LEN(str);
        numCount = nC;///zero by default, unless I am using the function: numerical_EVAL(), I send special nC and oC
        opCount = oC;
        for (int i = 0; i < n; i++)
        {
            if (type(str[i]) == 0)   ///if we have a number:
            {   ///We find out where it ends:
                int j;
                for (j = i; type(str[j]) == 0; j++)
                {
                }
                ///The digits between i and j-1 form an integer, thus: We store them at our num arr:
                num[numCount] = To_int(str, i, j - 1);
                bool is_there_a_point = false;
                if (type(str[j]) == 1) ///if the number was followed by a point
                {   ///We find out where it ends:
                    int k;
                    for (k = j + 1; type(str[k]) == 0; k++)
                    {
                    }
                    ///The digits between j+1 and k-1 form an integer, thus: We add them at our num arr, but after a point:
                    num[numCount] += To_after_point(str, j + 1, k - 1);
                    i = k - 1;
                    is_there_a_point = true;
                }
                if (!is_there_a_point)
                    i = j - 1;
                numCount++;
            }
            ///***********************************************************************
            else if (type(str[i]) == 2) ///if we have an operator:
            {
                if (str[i] == '+')
                    op[opCount++] = '+';
                else if (str[i] == '-')
                    op[opCount++] = '-';
                else if (str[i] == '*')
                    op[opCount++] = '*';
                else if (str[i] == '/')
                    op[opCount++] = '/';
                else if (str[i] == '^')
                    op[opCount++] = '^';
            }
            ///***********************************************************************
            else if (type(str[i]) == 4) ///if we have a char, but not a number, a point or an operator:
            {
                if (str[i] == 'x')
                {
                    ///Just put its value in its place:
                    num[numCount++] = x;
                }
                else if (str[i] == 'y')
                {
                    ///Just put its value in its place:
                    num[numCount++] = y;
                }
                else if (str[i] == 'z')
                {
                    ///Just put its value in its place:
                    num[numCount++] = z;
                }
                else if (str[i] == 'e')
                {
                    ///Just put its value in its place:
                    num[numCount++] = 2.71828182846;
                }
                else if (str[i] == 'p' && str[i + 1] == 'i') ///pi
                {
                    ///Just put its value in its place:
                    num[numCount++] = 3.14159265359;
                    i++;
                }
                ///================================================================================
                else if (str[i] == 's' && str[i + 1] == 'q' && str[i + 2] == 'r' && str[i + 3] == 't') ///sqrt:
                {
                    int opener = i + 4;
                    ///Find the closer of 'opener':
                    int closer = find_closing_bracket(str, opener);
                    ///Parse every thing between opener and closer in a variable called inside:
                    double inside = EVAL(str, opener + 1, closer - 1, x, y, z);
                    num[numCount++] = pow(inside, 0.5);
                    i = closer;
                }
                ///================================================================================
                else if (str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n' && str[i + 3] == 'h') ///sinh:
                {
                    int opener = i + 4;
                    ///Find the closer of 'opener':
                    int closer = find_closing_bracket(str, opener);
                    ///Parse every thing between opener and closer in a variable called inside:
                    double inside = EVAL(str, opener + 1, closer - 1, x, y, z);
                    num[numCount++] = sinh(inside);
                    i = closer;
                }
                ///================================================================================
                else if (str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's' && str[i + 3] == 'h') ///cosh:
                {
                    int opener = i + 4;
                    ///Find the closer of 'opener':
                    int closer = find_closing_bracket(str, opener);
                    ///Parse every thing between opener and closer in a variable called inside:
                    double inside = EVAL(str, opener + 1, closer - 1, x, y, z);
                    num[numCount++] = cosh(inside);
                    i = closer;
                }
                ///================================================================================
                else if (str[i] == 't' && str[i + 1] == 'a' && str[i + 2] == 'n' && str[i + 3] == 'h') ///tanh:
                {
                    int opener = i + 4;
                    ///Find the closer of 'opener':
                    int closer = find_closing_bracket(str, opener);
                    ///Parse every thing between opener and closer in a variable called inside:
                    double inside = EVAL(str, opener + 1, closer - 1, x, y, z);
                    num[numCount++] = tanh(inside);
                    i = closer;
                }
                ///================================================================================
                else if (str[i] == 's' && str[i + 1] == 'e' && str[i + 2] == 'c' && str[i + 3] == 'h') ///sech:
                {
                    int opener = i + 4;
                    ///Find the closer of 'opener':
                    int closer = find_closing_bracket(str, opener);
                    ///Parse every thing between opener and closer in a variable called inside:
                    double inside = EVAL(str, opener + 1, closer - 1, x, y, z);
                    num[numCount++] = 1.0 / cosh(inside);
                    i = closer;
                }
                ///================================================================================
                else if (str[i] == 'c' && str[i + 1] == 's' && str[i + 2] == 'c' && str[i + 3] == 'h') ///csch:
                {
                    int opener = i + 4;
                    ///Find the closer of 'opener':
                    int closer = find_closing_bracket(str, opener);
                    ///Parse every thing between opener and closer in a variable called inside:
                    double inside = EVAL(str, opener + 1, closer - 1, x, y, z);
                    num[numCount++] = 1.0 / sinh(inside);
                    i = closer;
                }
                ///================================================================================
                else if (str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 't' && str[i + 3] == 'h') ///coth
                {
                    int opener = i + 4;
                    ///Find the closer of 'opener':
                    int closer = find_closing_bracket(str, opener);
                    ///Parse every thing between opener and closer in a variable called inside:
                    double inside = EVAL(str, opener + 1, closer - 1, x, y, z);
                    num[numCount++] = 1.0 / tanh(inside);
                    i = closer;
                }
                ///================================================================================
                else if (str[i] == 'a' && str[i + 1] == 's' && str[i + 2] == 'i' && str[i + 3] == 'n' && str[i + 4] == 'h') ///asinh:
                {
                    int opener = i + 5;
                    ///Find the closer of 'opener':
                    int closer = find_closing_bracket(str, opener);
                    ///Parse every thing between opener and closer in a variable called inside:
                    double inside = EVAL(str, opener + 1, closer - 1, x, y, z);
                    num[numCount++] = asinh(inside);
                    i = closer;
                }
                ///================================================================================
                else if (str[i] == 'a' && str[i + 1] == 'c' && str[i + 2] == 'o' && str[i + 3] == 's' && str[i + 4] == 'h') ///acosh:
                {
                    int opener = i + 5;
                    ///Find the closer of 'opener':
                    int closer = find_closing_bracket(str, opener);
                    ///Parse every thing between opener and closer in a variable called inside:
                    double inside = EVAL(str, opener + 1, closer - 1, x, y, z);
                    num[numCount++] = acosh(inside);
                    i = closer;
                }
                ///================================================================================
                else if (str[i] == 'a' && str[i + 1] == 't' && str[i + 2] == 'a' && str[i + 3] == 'n' && str[i + 4] == 'h') ///atanh:
                {
                    int opener = i + 5;
                    ///Find the closer of 'opener':
                    int closer = find_closing_bracket(str, opener);
                    ///Parse every thing between opener and closer in a variable called inside:
                    double inside = EVAL(str, opener + 1, closer - 1, x, y, z);
                    num[numCount++] = atanh(inside);
                    i = closer;
                }
                ///================================================================================
                else if (str[i] == 'a' && str[i + 1] == 's' && str[i + 2] == 'e' && str[i + 3] == 'c' && str[i + 4] == 'h') ///asech:
                {
                    int opener = i + 5;
                    ///Find the closer of 'opener':
                    int closer = find_closing_bracket(str, opener);
                    ///Parse every thing between opener and closer in a variable called inside:
                    double inside = EVAL(str, opener + 1, closer - 1, x, y, z);
                    num[numCount++] = acosh(1.0 / inside);
                    i = closer;
                }
                ///================================================================================
                else if (str[i] == 'a' && str[i + 1] == 'c' && str[i + 2] == 's' && str[i + 3] == 'c' && str[i + 4] == 'h') ///acsch:
                {
                    int opener = i + 5;
                    ///Find the closer of 'opener':
                    int closer = find_closing_bracket(str, opener);
                    ///Parse every thing between opener and closer in a variable called inside:
                    double inside = EVAL(str, opener + 1, closer - 1, x, y, z);
                    num[numCount++] = asinh(1.0 / inside);
                    i = closer;
                }
                ///================================================================================
                else if (str[i] == 'a' && str[i + 1] == 'c' && str[i + 2] == 'o' && str[i + 3] == 't' && str[i + 4] == 'h') ///acoth:
                {
                    int opener = i + 5;
                    ///Find the closer of 'opener':
                    int closer = find_closing_bracket(str, opener);
                    ///Parse every thing between opener and closer in a variable called inside:
                    double inside = EVAL(str, opener + 1, closer - 1, x, y, z);
                    num[numCount++] = atanh(1.0 / inside);
                    i = closer;
                }
                ///================================================================================
                else if (str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n') ///sin:
                {
                    int opener = i + 3;
                    ///Find the closer of 'opener':
                    int closer = find_closing_bracket(str, opener);
                    ///Parse every thing between opener and closer in a variable called inside:
                    double inside = EVAL(str, opener + 1, closer - 1, x, y, z);
                    num[numCount++] = sin(inside);
                    i = closer;
                }
                ///================================================================================
                else if (str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's') ///cos:
                {
                    int opener = i + 3;
                    ///Find the closer of 'opener':
                    int closer = find_closing_bracket(str, opener);
                    ///Parse every thing between opener and closer in a variable called inside:
                    double inside = EVAL(str, opener + 1, closer - 1, x, y, z);
                    num[numCount++] = cos(inside);
                    i = closer;
                }
                ///================================================================================
                else if (str[i] == 't' && str[i + 1] == 'a' && str[i + 2] == 'n') ///tan:
                {
                    int opener = i + 3;
                    ///Find the closer of 'opener':
                    int closer = find_closing_bracket(str, opener);
                    ///Parse every thing between opener and closer in a variable called inside:
                    double inside = EVAL(str, opener + 1, closer - 1, x, y, z);
                    num[numCount++] = tan(inside);
                    i = closer;
                }
                ///================================================================================
                else if (str[i] == 's' && str[i + 1] == 'e' && str[i + 2] == 'c') ///sec:
                {
                    int opener = i + 3;
                    ///Find the closer of 'opener':
                    int closer = find_closing_bracket(str, opener);
                    ///Parse every thing between opener and closer in a variable called inside:
                    double inside = EVAL(str, opener + 1, closer - 1, x, y, z);
                    num[numCount++] = 1.0 / cos(inside);
                    i = closer;
                }
                ///================================================================================
                else if (str[i] == 'c' && str[i + 1] == 's' && str[i + 2] == 'c') ///csc:
                {
                    int opener = i + 3;
                    ///Find the closer of 'opener':
                    int closer = find_closing_bracket(str, opener);
                    ///Parse every thing between opener and closer in a variable called inside:
                    double inside = EVAL(str, opener + 1, closer - 1, x, y, z);
                    num[numCount++] = 1.0 / sin(inside);
                    i = closer;
                }
                ///================================================================================
                else if (str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 't') ///cot:
                {
                    int opener = i + 3;
                    ///Find the closer of 'opener':
                    int closer = find_closing_bracket(str, opener);
                    ///Parse every thing between opener and closer in a variable called inside:
                    double inside = EVAL(str, opener + 1, closer - 1, x, y, z);
                    num[numCount++] = 1.0 / tan(inside);
                    i = closer;
                }
                ///================================================================================
                else if (str[i] == 'a' && str[i + 1] == 's' && str[i + 2] == 'i' && str[i + 3] == 'n') ///asin:
                {
                    int opener = i + 4;
                    ///Find the closer of 'opener':
                    int closer = find_closing_bracket(str, opener);
                    ///Parse every thing between opener and closer in a variable called inside:
                    double inside = EVAL(str, opener + 1, closer - 1, x, y, z);
                    num[numCount++] = asin(inside);
                    i = closer;
                }
                ///================================================================================
                else if (str[i] == 'a' && str[i + 1] == 'c' && str[i + 2] == 'o' && str[i + 3] == 's') ///acos:
                {
                    int opener = i + 4;
                    ///Find the closer of 'opener':
                    int closer = find_closing_bracket(str, opener);
                    ///Parse every thing between opener and closer in a variable called inside:
                    double inside = EVAL(str, opener + 1, closer - 1, x, y, z);
                    num[numCount++] = acos(inside);
                    i = closer;
                }
                ///================================================================================
                else if (str[i] == 'a' && str[i + 1] == 't' && str[i + 2] == 'a' && str[i + 3] == 'n') ///atan:
                {
                    int opener = i + 4;
                    ///Find the closer of 'opener':
                    int closer = find_closing_bracket(str, opener);
                    ///Parse every thing between opener and closer in a variable called inside:
                    double inside = EVAL(str, opener + 1, closer - 1, x, y, z);
                    num[numCount++] = atan(inside);
                    i = closer;
                }
                ///================================================================================
                else if (str[i] == 'a' && str[i + 1] == 's' && str[i + 2] == 'e' && str[i + 3] == 'c') ///asec:
                {
                    int opener = i + 4;
                    ///Find the closer of 'opener':
                    int closer = find_closing_bracket(str, opener);
                    ///Parse every thing between opener and closer in a variable called inside:
                    double inside = EVAL(str, opener + 1, closer - 1, x, y, z);
                    num[numCount++] = acos(1.0 / inside);
                    i = closer;
                }
                ///================================================================================
                else if (str[i] == 'a' && str[i + 1] == 'c' && str[i + 2] == 's' && str[i + 3] == 'c') ///acsc:
                {
                    int opener = i + 4;
                    ///Find the closer of 'opener':
                    int closer = find_closing_bracket(str, opener);
                    ///Parse every thing between opener and closer in a variable called inside:
                    double inside = EVAL(str, opener + 1, closer - 1, x, y, z);
                    num[numCount++] = asin(1.0 / inside);
                    i = closer;
                }
                ///================================================================================
                else if (str[i] == 'a' && str[i + 1] == 'c' && str[i + 2] == 'o' && str[i + 3] == 't') ///acot:
                {
                    int opener = i + 4;
                    ///Find the closer of 'opener':
                    int closer = find_closing_bracket(str, opener);
                    ///Parse every thing between opener and closer in a variable called inside:
                    double inside = EVAL(str, opener + 1, closer - 1, x, y, z);
                    num[numCount++] = atan(1.0 / inside);
                    i = closer;
                }
                ///================================================================================
                else if (str[i] == 'l' && str[i + 1] == 'n') ///ln:
                {
                    int opener = i + 2;
                    ///Find the closer of 'opener':
                    int closer = find_closing_bracket(str, opener);
                    ///Parse every thing between opener and closer in a variable called inside:
                    double inside = EVAL(str, opener + 1, closer - 1, x, y, z);
                    num[numCount++] = log(inside);
                    i = closer;
                }
                ///================================================================================
                else if (str[i] == 'l' && str[i + 1] == 'o' && str[i + 2] == 'g' && str[i + 3] == '(') ///log: (base 10)
                {
                    int opener = i + 3;
                    ///Find the closer of 'opener':
                    int closer = find_closing_bracket(str, opener);
                    ///Parse every thing between opener and closer in a variable called inside:
                    double inside = EVAL(str, opener + 1, closer - 1, x, y, z);
                    num[numCount++] = log10(inside);
                    i = closer;
                }
                ///================================================================================
                else if (str[i] == 'a' && str[i + 1] == 'b' && str[i + 2] == 's') ///abs
                {
                    int opener = i + 3;
                    ///Find the closer of 'opener':
                    int closer = find_closing_bracket(str, opener);
                    ///Parse every thing between opener and closer in a variable called inside:
                    double inside = EVAL(str, opener + 1, closer - 1, x, y, z);
                    num[numCount++] = abs(inside);
                    i = closer;
                }
            }

            ///*************************************************************************
            else if (str[i] == '(') ///opener
            {
                ///Find the closer:
                int closer = find_closing_bracket(str, i);
                ///Parse every thing between i and closer into 'inside':
                double inside = EVAL(str, i + 1, closer - 1, x, y, z);
                num[numCount++] = inside;
                i = closer;
            }


        }
        for (int j = 0; j < opCount; j++)
        {
            if (op[j] == '^')
                num[j + 1] = pow(num[j], num[j + 1]);
            ///=================================================
            else if (op[j] == '*')
            {
                if (op[j + 1] == '^')
                {
                    int i;
                    ///search for the last '^' operator:
                    ///it will be op[j+i-1]
                    for (i = 1; op[j + i] == '^'; i++)
                    {
                    }
                    double temp = num[j + i];
                    for (int k = i - 1; k > 0; k--)
                        temp = pow(num[j + k], temp);
                    num[j + i] = num[j] * temp;
                    j = j + i - 1;
                }
                else
                    num[j + 1] = num[j] * num[j + 1];
            }
            ///=================================================
            else if (op[j] == '/')
            {
                if (op[j + 1] == '^')
                {
                    int i;
                    ///search for the last '^' operator:
                    ///it will be op[j+i-1]
                    for (i = 1; op[j + i] == '^'; i++)
                    {
                    }
                    double temp = num[j + i];
                    for (int k = i - 1; k > 0; k--)
                        temp = pow(num[j + k], temp);
                    num[j + i] = num[j] / temp;
                    j = j + i - 1;
                }
                else
                    num[j + 1] = num[j] / num[j + 1];
            }
            ///=================================================
            else if (op[j] == '+')
            {
                ///search for the next '+' or '-' operator:
                ///it will be op[j+i]
                int i;
                for (i = 1; op[j + i] != '+' && op[j + i] != '-' && j + i < opCount; i++)
                {
                }
                ///now: what ever operators are between j & i, they must be a combination of '*', '/' and '^'
                ///so we parse them seperatly:
                if (i > 1)
                {
                    double temp = numerical_EVAL(num, op, j + 1, j + i);
                    num[j + i] = num[j] + temp;
                    j = j + i - 1;
                }
                else
                    num[j + 1] = num[j] + num[j + 1];
            }
            ///=================================================
            else if (op[j] == '-')
            {
                ///search for the next '+' or '-' operator:
                ///it will be op[j+i]
                int i;
                for (i = 1; op[j + i] != '+' && op[j + i] != '-' && j + i < opCount; i++)
                {
                }
                ///now: what ever operators are between j & i, they must be a combination of '*', '/' and '^'
                ///so we parse them seperatly:
                if (i > 1)
                {
                    double temp = numerical_EVAL(num, op, j + 1, j + i);
                    num[j + i] = num[j] - temp;
                    j = j + i - 1;
                }
                else
                    num[j + 1] = num[j] - num[j + 1];
            }
        }
        return num[numCount - 1];
    }
};
///=============================================================================
int main()
{
    float t;
    cout << "No spaces allowed!\n";
    cout << "Make sure the function is continuous on the range of integration, no error handling for this so far.\n";
    cout << endl;
    cout << "Speed :\n";
    cout << "1.normal    2.fast\n";
    int speedMode;
    cin >> speedMode;
    if (speedMode == 1)
        speed = 1;
    else if (speedMode == 2)
        speed = 10;
    cout << "0. parser tryout\n";
    cout << "1. Single integral\n";
    cout << "2. double integral\n";
    cout << "3. triple integral\n";
    cout << "4. equation solver\n";
    cout << "5. derivative\n";
    int mode;
    cin >> mode;
    if (mode == 0)
    {
        char* str = new char[500]; ///you can write an expression up to 500 chars
        cout << "f(x) = ";
        cin >> str;
        double x;
        cout << "x = ";
        cin >> x;
        parser* p = new parser[1];
        p->str = str;
        double result = p->eval(x);
        cout << "f(" << x << ") = " << result << endl;
        delete p;
    }
    else if (mode == 1)
    {
        double xL;
        double xH;
        char* str = new char[500]; ///you can write an expression up to 500 chars
        cout << "f(x) = ";
        cin >> str;
        cout << "lower x : ";
        cin >> xL;
        cout << "higher x : ";
        cin >> xH;
        cout << "\nCalculating...";
        const clock_t begin_time = clock();
        double RESULT = single_integral(str, xL, xH);
        t = float(clock() - begin_time) / CLOCKS_PER_SEC;
        cout << endl;
        cout.precision(3);
        cout << char(244) << xH << endl;
        cout << char(179) << "         ( " << str << " ) dx " << char(247) << ' ';
        delete str;
        cout.precision(10);
        cout << RESULT << endl;
        cout.precision(3);
        cout << char(245) << xL << endl;
    }

    else if (mode == 2)
    {
        double xL;
        double xH;
        double yL;
        double yH;
        char* str = new char[500]; ///you can write an expression up to 500 chars
        cout << "f(x, y) = ";
        cin >> str;
        cout << "lower x : ";
        cin >> xL;
        cout << "higher x : ";
        cin >> xH;
        cout << "lower y : ";
        cin >> yL;
        cout << "higher y : ";
        cin >> yH;
        cout << "\nCalculating...";
        const clock_t begin_time = clock();
        double RESULT = double_integral(str, xL, xH, yL, yH);
        t = float(clock() - begin_time) / CLOCKS_PER_SEC;
        cout << endl;
        cout.precision(3);
        cout << char(244) << setiosflags(ios::left) << setw(9) << yH << char(244) << xH << endl;
        cout.precision(10);
        cout << char(179) << "         " << char(179) << "         ( " << str << " ) dxdy " << char(247) << ' ' << RESULT << endl;
        delete str;
        cout.precision(3);
        cout << char(245) << setiosflags(ios::left) << setw(9) << yL << char(245) << xL << endl;
    }

    else if (mode == 3)
    {
        double xL;
        double xH;
        double yL;
        double yH;
        double zL;
        double zH;
        char* str = new char[500]; ///you can write an expression up to 500 chars
        cout << "f(x, y, z) = ";
        cin >> str;
        cout << "lower x : ";
        cin >> xL;
        cout << "higher x : ";
        cin >> xH;
        cout << "lower y : ";
        cin >> yL;
        cout << "higher y : ";
        cin >> yH;
        cout << "lower z : ";
        cin >> zL;
        cout << "higher z : ";
        cin >> zH;
        cout << "\nCalculating...";
        const clock_t begin_time = clock();
        double RESULT = triple_integral(str, xL, xH, yL, yH, zL, zH);
        t = float(clock() - begin_time) / CLOCKS_PER_SEC;
        cout << endl;
        cout.precision(3);
        cout << char(244) << setiosflags(ios::left) << setw(9) << zH << char(244) << setiosflags(ios::left) << setw(9) << yH << char(244) << xH << endl;
        cout.precision(10);
        cout << char(179) << "         " << char(179) << "         " << char(179) << "         ( " << str << " ) dxdydz " << char(247) << ' ' << RESULT << endl;
        delete str;
        cout.precision(3);
        cout << char(245) << setiosflags(ios::left) << setw(9) << zL << char(245) << setiosflags(ios::left) << setw(9) << yL << char(245) << xL << endl;

    }
    else if (mode == 4)
    {
        double X0;
        char* str = new char[500]; ///you can write an expression up to 500 chars
        cout << "let : f(x) = 0\n";
        cout << "f(x) = ";
        cin >> str;
        cout << "x0 = ";
        cin >> X0;
        cout << "\nCalculating...\n";
        const clock_t begin_time = clock();
        double result = solve(str, X0);
        t = float(clock() - begin_time) / CLOCKS_PER_SEC;
        cout << "x = " << result << endl;
    }
    else if (mode == 5)
    {
        int n;
        double x;
        char* str = new char[500]; ///you can write an expression up to 500 chars
        cout << "f(x) = ";
        cin >> str;
        cout << "find nth derivative... n = ";
        cin >> n;
        cout << "x = ";
        cin >> x;
        cout << "\nCalculating...\n";
        const clock_t begin_time = clock();
        double result = derivative(str, n, x);
        t = float(clock() - begin_time) / CLOCKS_PER_SEC;
        cout << ' ' << n;
        for (int i = 0; i < LEN(str) + 3; i++)
            cout << ' ';
        cout << '|' << endl;
        cout << "d  " << char(218);
        for (int i = 0; i < LEN(str); i++)
            cout << ' ';
        cout << char(191) << '|' << endl;
        cout << "---|";
        cout << str;
        cout << "|| " << char(247) << ' ' << result << endl;
        cout << "  " << n << char(192);
        for (int i = 0; i < LEN(str); i++)
            cout << ' ';
        cout << char(217) << '|' << endl;
        cout << "dx";
        for (int i = 0; i < LEN(str) + 3; i++)
            cout << ' ';
        cout << "|x=" << x << endl;
    }
    cout << "Calculation time: " << t << " seconds\n";
    cout << "press any key to exit";
    _getch();
    return 0;
}
///=============================================================================
int type(char ch)
{
    if ('0' <= ch && ch <= '9')
        return 0; ///Digit.
    else if (ch == '.')
        return 1; ///Point.
    else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '^')
        return 2; ///Operator.
    else if (ch == '(' || ch == ')')
        return 3; ///Bracket.
    else if ('a' <= ch && ch <= 'z')
        return 4; ///Letter.
    else if (ch == ' ')
        return 5; ///space
    else
        return -1;
}

double To_int(char* str, int i, int j)
{
    double result = 0;
    for (int n = i; n <= j; n++)
        result += (str[n] - '0') * pos_powr(10.0, j - n);
    return result;
}
double To_after_point(char* str, int j, int k)
{
    double temp = To_int(str, j, k);
    double result = temp / pos_powr(10.0, k - j + 1);
    return result;
}

double pos_powr(double i, int n)
{
    if (n == 0)
        return 1;
    double result = i;
    for (int j = 1; j < n; j++)
        result *= i;
    return result;
}



double EVAL(char* str, int start, int End, double x, double y, double z)
{
    parser* p = new parser;
    int n = End - start + 2;
    p->str = new char[n];
    for (int j = 0; j < n - 1; j++)
        p->str[j] = str[j + start];
    p->str[n - 1] = '\0';
    double E = p->eval(x, y, z);
    delete p->str;
    delete p;
    return E;
}

int LEN(char* str)
{
    int len;
    for (len = 0; str[len] != '\0'; len++)
    {
    }
    return len;
}

void stuck(char* str, char ch, int k)
{
    int last = LEN(str);
    for (int i = last; i >= k; i--)
        str[i + 1] = str[i];
    str[k] = ch;
}

int find_closing_bracket(char* str, int opener)        ///taken from https://stackoverflow.com/questions/12752225/how-do-i-find-the-position-of-matching-parentheses-or-braces-in-a-given-piece-of
{
    int closer = opener;
    int counter = 1;
    while (counter > 0)
    {
        char c = str[++closer];
        if (c == '(')
            counter++;
        else if (c == ')')
            counter--;
    }
    return closer;
}


double numerical_EVAL(double num[50], char op[30], int start, int end_num)
{
    ///int start is the start of both num and op
    ///but note that end_op is always one decimal less than end_num
    int end_op = end_num - 1;
    parser* pp = new parser;
    pp->str = new char[1];
    *(pp->str) = '\n';
    int numCount = end_num - start + 1;
    int opCount = end_op - start + 1;
    for (int j = 0; j < numCount; j++)
        pp->num[j] = num[j + start];
    for (int j = 0; j < opCount; j++)
        pp->op[j] = op[j + start];
    double RESULT = pp->eval(0.0, 0.0, 0.0, numCount, opCount); ///here the value of x,y,z would not matter, as I am parsing some numbers.
    delete pp->str;
    delete pp;
    return RESULT;
}

double single_integral(char* str, double xL, double xH)
{
    parser pp;
    pp.str = str;

    ///===========================
    double h = (1e-6) * speed;
    double dx = (xH - xL) * h;
    ///===========================
    double n = 1 / h;
    ///===========================
    double result = 0.0;
    double Xi = xL + 0.5 * dx;
    int count = 0;
    int l = 1;
    unsigned int N = static_cast<unsigned int>(n);
    cout << endl;
    for (int j = 0; j < 100; j++)
        cout << char(176);
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        result += pp.eval(Xi);
        Xi += dx;
        count++;
        if (count == static_cast<int>(l * 0.01 * N)) ///every 1% of N
        {
            cout << char(178);
            l++;
        }
    }
    ///===========================
    result *= dx;
    return result;
}

double double_integral(char* str, double xL, double xH, double yL, double yH)
{
    parser pp;
    pp.str = str;
    double n; ///number of x sections
    double m; ///number of y sections
    ///===========================
    double hx = (1e-4) * speed;
    double hy = (1e-3) * speed;
    ///===========================
    double dx = (xH - xL) * hx;
    double dy = (yH - yL) * hy;
    double dA = dx * dy;
    ///===========================
    n = 1 / hx;
    m = 1 / hy;
    ///===========================
    double result = 0.0;
    double Yj = yL + 0.5 * dy;
    double Xi;
    int count = 0;
    int l = 1;
    unsigned int M = static_cast<unsigned int>(m);
    cout << endl;
    for (int j = 0; j < 100; j++)
        cout << char(176);
    cout << endl;
    for (int j = 0; j < m; j++)
    {
        Xi = xL + 0.5 * dx;
        for (int i = 0; i < n; i++)
        {
            result += pp.eval(Xi, Yj);
            Xi += dx;
        }
        Yj += dy;
        count++;
        if (count == static_cast<int>(l * 0.01 * M)) ///every 1% of M
        {
            cout << char(178);
            l++;
        }
    }
    ///===========================
    result *= dA;
    return result;
}

double triple_integral(char* str, double xL, double xH, double yL, double yH, double zL, double zH)
{
    parser pp;
    pp.str = str;
    double n; ///number of x sections
    double m; ///number of y sections
    double p; ///number of z sections

    ///===========================
    double hx = (1e-3) * speed;
    double hy = (1e-2) * speed;
    double hz = (1e-2) * speed;
    ///===========================
    double dx = (xH - xL) * hx;
    double dy = (yH - yL) * hy;
    double dz = (zH - zL) * hz;
    double dV = dx * dy * dz;
    ///===========================
    n = 1 / hx;
    m = 1 / hy;
    p = 1 / hz;
    ///===========================
    double result = 0.0;
    double Zk = zL + 0.5 * dz;
    double Yj;
    double Xi;
    int count = 0;
    int l = 1;
    unsigned int P = static_cast<unsigned int>(p);
    cout << endl;
    for (int j = 0; j < 100; j++)
        cout << char(176);
    cout << endl;
    for (int k = 0; k < p; k++)
    {
        Yj = yL + 0.5 * dy;
        for (int j = 0; j < m; j++)
        {
            Xi = xL + 0.5 * dx;
            for (int i = 0; i < n; i++)
            {
                result += pp.eval(Xi, Yj, Zk);
                Xi += dx;
            }
            Yj += dy;
        }
        Zk += dz;
        count++;
        if (count == static_cast<int>(l * 0.01 * P)) ///every 1% of P
        {
            cout << char(178);
            l++;
        }
    }
    ///===========================
    result *= dV;
    return result;
}


int Number_Of_Digits(double x)
{
    int n = static_cast<int>(x);
    int i = 0;
    int j = 1;
    while (n / j >= 1)
    {
        i++;
        j *= 10;
    }
    if (i == 0)
        i = 1;
    return i;
}

double factorial(int n)
{
    double result = 1;
    for (int i = n; i > 0; i--)
        result *= i;
    return result;
}

double combination(int n, int k)
{
    int numerator = 1;
    int i_max = n - k;
    for (int i = n; i > i_max; i--)
        numerator *= i;
    double result = static_cast<double>(numerator) / factorial(k);
    return result;
}

double derivative(char* str, int n, double x)
{
    parser* p = new parser[1];
    p->str = str;
    double result;
    if (n == 0)
        result = p->eval(x);
    else
    {
        double N = Number_Of_Digits(x);        /// cout<<"N= "<<N<<endl;
        double h;         ///cout<<"h= "<<h<<endl;
        if (x != 0)
            h = x * pow(10.0, -9.0 / (n * N));
        else
            h = pow(10.0, -9.0 / (n * N));
        double sum = 0.0;
        for (int k = 0; k <= n; k++)
            sum += combination(n, k) * pow(-1.0, k) * p->eval(x + k * h);
        result = pow(-1.0, n) * sum / pow(h, n);     ///    cout<<"result= "<<result<<endl;
    }
    delete p;
    return result;
}

double solve(char* str, double X0)
{
    parser* p = new parser[1];
    p->str = str;
    double X_n = X0;
    double X_n1;
    double h = 1e-9 * speed;
    while (abs(p->eval(X_n)) >= h)
    {
        X_n1 = X_n - p->eval(X_n) / derivative(str, 1, X_n);
        if (isnan(X_n1) || isinf(X_n1))
            X_n1 = X_n + 1.0;
        X_n = X_n1;
    }
    delete p;
    return X_n;
}

