/*
 * MathAdv.c
 * By: Ali Emad Ali
 * Date created: 2021-06-21
 */

#include "math.h"
#include "../Inc/MathAdv.h"

double pos_powr(double i, unsigned int n)
{
    if (n == 0)
        return 1;
    double result = i;
    for (int j = 1; j < n; j++)
        result *= i;
    return result;
}

int Number_Of_Digits(double x)
{
    int n = (int)x;
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
    double result = (double)(numerator) / factorial(k);
    return result;
}

double sech(double x)
{
	return 1.0 / cosh(x);
}

double csch(double x)
{
	return 1.0 / sinh(x);
}

double coth(double x)
{
	return 1.0 / tanh(x);
}

double asech(double x)
{
	return acosh(1.0 / x);
}

double acsch(double x)
{
	return asinh(1.0 / x);
}

double acoth(double x)
{
	return atanh(1.0 / x);
}

double sec(double x)
{
	return 1.0 / cos(x);
}

double csc(double x)
{
	return 1.0 / sin(x);
}

double cot(double x)
{
	return 1.0 / tan(x);
}

double asec(double x)
{
	return acos(1.0 / x);
}

double acsc(double x)
{
	return asin(1.0 / x);
}

double acot(double x)
{
	return atan(1.0 / x);
}










