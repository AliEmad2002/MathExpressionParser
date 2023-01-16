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