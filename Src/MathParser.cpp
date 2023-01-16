/*
 * MathParser.cpp
 * By: Ali Emad Ali
 * Date created: 2021-06-21
 */
 
#include <iostream>
#include <math.h>
#include <conio.h>
#include <iomanip>
#include <ctime>
#include <stdlib.h>
#include "../Inc/MathAdv.h"
#include "../Inc/StringAdv.h"
#include "../Inc/MathParser.h"

using namespace std;

double speed;

/*******************************************************************************
 * Type of a character (byte):
 ******************************************************************************/
MathParser_CharType_t type(char ch)
{
    if ('0' <= ch && ch <= '9')
        return MathParser_CharType_Digit;
    else if (ch == '.')
        return MathParser_CharType_Point;
    else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '^')
        return MathParser_CharType_Operator;
    else if (ch == '(' || ch == ')')
        return MathParser_CharType_Bracket;
    else if ('a' <= ch && ch <= 'z')
        return MathParser_CharType_Letter;
    else if (ch == ' ')
        return MathParser_CharType_space;
    else
        return MathParser_CharType_Error;
} 

/*******************************************************************************
 * Converting a string to a number:
 ******************************************************************************/
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

/*******************************************************************************
 * Evaluating arrays of numbers with their corrresponding operators:
 ******************************************************************************/
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
	///here the value of x,y,z would not matter, as I am parsing some numbers.
    double RESULT = pp->eval(0.0, 0.0, 0.0, numCount, opCount); 
    delete pp->str;
    delete pp;
    return RESULT;
}

/*******************************************************************************
 * struct MathParser:
 ******************************************************************************/
double MathParser::MathParser_doubleEval(
	double x = 0.0, double y = 0.0, double z = 0.0, int nC = 0, int oC = 0)
{
	for (int k = 0; str[k] != '\0' && never_ran; k++)
	{
		/*	any '-' without a number before it, put zero before it	*/
		if (str[k] == '-')
		{
			if (k == 0)
				stuck(str, '0', k);
			else if (str[k - 1] == '[' || str[k - 1] == '(')
				stuck(str, '0', k);
		}

		/*
		 * any number not followed by another number, a pint, a right bracket,
		 * or an operator, and is not the last in the str: I put '*' after it:
		 */
		else if (
			(
				type(str[k]) == MathParser_CharType_Digit 		||
				str[k] == 'x' 									||
				str[k] == 'y' 									||
				str[k] == 'z' 									||
				str[k] == 'e'
			) 													&&
			type(str[k + 1]) != 0 								&&
			str[k + 1] != '.' 									&&
			str[k + 1] != ']' 									&&
			str[k + 1] != ')' 									&&
			type(str[k + 1]) != 2 								&&
			str[k + 1] != '\0')
		{
			stuck(str, '*', k + 1);
		}

		else if (
			str[k] == 'p' 										&&
			str[k + 1] == 'i' 									&&
			type(str[k + 2]) != MathParser_CharType_Digit 		&&
			str[k + 2] != '.' 									&&
			str[k + 2] != ']' 									&&
			str[k + 2] != ')' 									&&
			type(str[k + 2]) != 2 								&&
			str[k + 2] != '\0')
		{
			stuck(str, '*', k + 2);
		}
	}

	/*	clear never ran flag	*/
	never_ran = false;

	n = LEN(str);

	/*
	 * zero by default, unless I am using the function: numerical_EVAL(), I
	 * send special nC and oC.
	 */
	numCount = nC;
	opCount = oC;

	/*	for every character in str	*/
	for (int i = 0; i < n; i++)
	{
		if (type(str[i]) == MathParser_CharType_Digit)
		{
			// find out where the number that starts with 'str[i]' ends:
			int j;
			for (j = i; type(str[j]) == 0; j++);

			/*
			 * The digits between i and j-1 form an integer, thus: We store
			 * them at our num arr:
			 */
			num[numCount] = To_int(str, i, j - 1);

			/*	check decimal point	*/
			bool is_there_a_point = false;
			if (type(str[j]) == MathParser_CharType_Point)
			{
				// find out where the number after the point ends:
				int k;
				for (k = j + 1; type(str[k]) == 0; k++);

				/*
				 * The digits between j+1 and k-1 form an integer, thus: We add
				 * them at our num arr, but after a point:
				 */
				num[numCount] += To_after_point(str, j + 1, k - 1);

				i = k - 1;
				is_there_a_point = true;
			}

			if (!is_there_a_point)
				i = j - 1;

			numCount++;
		}
		///*********************************************************************
		else if (type(str[i]) == MathParser_CharType_Operator)
		{
			switch(str[i])
			{
			case '+':
				op[opCount++] = '+';
				break;
			case '-':
				op[opCount++] = '-';
				break;
			case '*':
				op[opCount++] = '*';
				break;
			case '/':
				op[opCount++] = '/';
				break;
			case '^':
				op[opCount++] = '^';
				break;
			}
		}
		///*********************************************************************
		else if (type(str[i]) == MathParser_CharType_Letter)
		{
			/*	find where this word ends	*/
			int j;
			for (j = i + 1; type(str[j]) == MathParser_CharType_Letter; j++);

			/*	parse inputs of this word (i.e.: arguments), if any	*/
			double arguments;
			if (str[j] == '(')
			{
				/*	Find the closer of 'j':	*/
				int closer = find_closing_bracket(str, j);
				/*	Parse every thing between opener and closer	*/
				arguments = EVAL(str, j + 1, closer - 1, x, y, z);
			}

			/*	get pointer to the cpp function that this word implements	*/

			/*
			 * apply the function that this word implements, as input, give it:
			 * 'x', 'y', 'z', 'arguments'
			 */

			/*	add function's numerical value to num array	*/

			/*	update 'i'	*/


			if (str[i] == 'x')
			{
				// Just put its value in its place:
				num[numCount++] = x;
			}
			else if (str[i] == 'y')
			{
				// Just put its value in its place:
				num[numCount++] = y;
			}
			else if (str[i] == 'z')
			{
				// Just put its value in its place:
				num[numCount++] = z;
			}
			else if (str[i] == 'e')
			{
				// Just put its value in its place:
				num[numCount++] = 2.71828182846;
			}
			else if (str[i] == 'p' && str[i + 1] == 'i') // pi
			{
				// Just put its value in its place:
				num[numCount++] = 3.14159265359;
				i++;
			}
			///=================================================================
			else if (
				str[i] == 's' && str[i + 1] == 'q' &&
				str[i + 2] == 'r' && str[i + 3] == 't') // sqrt:
			{
				int opener = i + 4;
				// Find the closer of 'opener':
				int closer = find_closing_bracket(str, opener);
				/*	Parse every thing between opener and closer	*/
				double inside = EVAL(str, opener + 1, closer - 1, x, y, z);

				num[numCount++] = pow(inside, 0.5);
				i = closer;
			}
			///=================================================================
			else if (
				str[i] == 's' && str[i + 1] == 'i' &&
				str[i + 2] == 'n' && str[i + 3] == 'h') // sinh:
			{
				int opener = i + 4;

				// Find the closer of 'opener':
				int closer = find_closing_bracket(str, opener);

				/*	Parse every thing between opener and closer	*/
				double inside = EVAL(str, opener + 1, closer - 1, x, y, z);
				num[numCount++] = sinh(inside);
				i = closer;
			}
			///=================================================================
			else if (
				str[i] == 'c' && str[i + 1] == 'o' &&
				str[i + 2] == 's' && str[i + 3] == 'h') // cosh:
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









