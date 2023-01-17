/*
 * StringAdv.c
 * By: Ali Emad Ali
 * Date created: 2021-06-21
 */

#include "../Inc/StringAdv.h"

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

int LEN(char* str)
{
    int len;
    for (len = 0; str[len] != '\0'; len++)
    {
    }
    return len;
}
