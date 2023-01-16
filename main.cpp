/*
 * main.cpp
 * By: Ali Emad Ali
 * Date created: 2021-06-21
 */
 
#include <iostream>
#include <math.h>
#include <conio.h>
#include <iomanip>
#include <ctime>
#include "MathAdv.h"
#include "StringAdv.h"
#include "MathParser.h"
#include "ParserApplication.h"

using namespace std;

double speed;

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
