/*
 * parserApplication.cpp
 * By: Ali Emad Ali
 * Date created: 2021-06-21
 */

#include <iostream>
#include "../Inc/MathAdv.h"
#include "../Inc/StringAdv.h"
#include "../Inc/MathParser.h"
#include "../Inc/ParserApplication.h"

using namespace std;

/*******************************************************************************
 * Derivative evaluation:
 ******************************************************************************/
double derivative(char* str, int n, double x)
{
    parser* p = new parser[1];
    p->str = str;
    double result;
    if (n == 0)
        result = p->eval(x);
    else
    {
        double N = Number_Of_Digits(x);
        double h;
        if (x != 0)
            h = x * pow(10.0, -9.0 / (n * N));
        else
            h = pow(10.0, -9.0 / (n * N));
        double sum = 0.0;
        for (int k = 0; k <= n; k++)
            sum += combination(n, k) * pow(-1.0, k) * p->eval(x + k * h);
        result = pow(-1.0, n) * sum / pow(h, n);
    }
    delete p;
    return result;
}

/*******************************************************************************
 * Integrals:
 ******************************************************************************/
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
    double n; // number of x sections
    double m; // number of y sections
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

double triple_integral(
	char* str,
	double xL, double xH, double yL, double yH, double zL, double zH)
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

/*******************************************************************************
 * Function solving:
 ******************************************************************************/
 /*	using newton-raphson	*/
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

/*******************************************************************************
 * Continuity checking: (Not done yet)
 ******************************************************************************/
 
