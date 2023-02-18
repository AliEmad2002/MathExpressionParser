/*
 * MathParser.c
 * By: Ali Emad Ali
 * Date created: 2021-06-21
 */

#include "../Inc/Std_Types.h"
#include <math.h>
//#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "../Inc/MathAdv.h"
#include "../Inc/StringAdv.h"
#include "../Inc/LinkedList.h"
#include "../Inc/MathParser_config.h"
#include "../Inc/MathParser.h"


/*******************************************************************************
 * Macros:
 ******************************************************************************/
#define LINKED_LIST_MAX_LEN  (MAX_EXPRESSION_STR_LEN / 2)

/*******************************************************************************
 * Type of a character (byte):
 ******************************************************************************/
inline MathParser_CharType_t type(char ch)
{
    if ('0' <= ch && ch <= '9')
        return MathParser_CharType_Digit;
    else if ('a' <= ch && ch <= 'z')
        return MathParser_CharType_Letter;
    else if (ch == '.')
        return MathParser_CharType_Point;
    else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
        return MathParser_CharType_Operator;
    else if (ch == '(' || ch == ')')
        return MathParser_CharType_Bracket;
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

double EVAL(const char* str, int start, int end, double x, double y, double z)
{
	MathParser_t p;
	MathParser_b8SetExpressionString(&p, str, start, end);

	return MathParser_d64Evaluate(&p, x, y, z);
}

/*******************************************************************************
 * struct MathParser:
 ******************************************************************************/
/*
 * copies char array to p->str.
 * checks for syntax errors first. If any, it returns false. otherwise it
 * returns true.
 */
b8 MathParser_b8SetExpressionString(
	MathParser_t* p, const char* expressionStr, int start, int end)
{
	/**
	 * copy 'expressionStr' to 'p->str', and set 'p->n' to length of the
	 * expression string.
	 */
	for (p->n = 0; p->n < end - start + 1; p->n++)
	{
		p->str[p->n] = expressionStr[p->n + start];
	}
	p->str[p->n] = '\0';

	/**
	 * process 'expressionStr' for any syntax errors,
	 * and put zero before the negative sign that ccomes in the very first of
	 * the expression (if any).
	 */
	/*
	 * if first char of the expression is a negative sign, put zero before it
	 */
	if (p->str[0] == '-')
	{
		stuck(p->str, '0', 0);
		p->n++;
	}

	b8 isThereSyntaxError = false;

	//TODO: Add the syntax checking function.

	if (isThereSyntaxError)
		return false;

	/*	no syntax errors were found	*/
	return true;
}

///*
// * inits linked list elemnts of a parser object.
// * Note: parser object must be init first before evaluating. No checking before
// * evaluation to reduce overhead.
// */
//void MathParser_voidInitParserLinkedLists(MathParser_t* p)
//{
//	for (int i = 0; i < LINKED_LIST_MAX_LEN - 1; i++)
//	{
//		p->numLinkedList[i].nextPtr = (void*)&(p->numLinkedList[i + 1]);
//
//		p->opLinkedList[i].nextPtr = (void*)&(p->opLinkedList[i + 1]);
//	}
//
//	p->numLinkedList[LINKED_LIST_MAX_LEN - 1].nextPtr = NULL;
//	p->opLinkedList[LINKED_LIST_MAX_LEN - 1].nextPtr = NULL;
//}

double MathParser_d64Evaluate(MathParser_t* p, double x, double y, double z)
{
	/*	reset counts	*/
	p->numCount = 0;
	p->opCount = 0;

	/*	extract refrences to elements of 'p' for good readability	*/
	char* str = p->str;
	Double_LinkedList_t* numLinkedList = p->numLinkedList;
	Char_LinkedList_t* opLinkedList = p->opLinkedList;

	/*	parse the expression string to find numbers and operators	*/
	for (int i = 0; i < p->n; i++)
	{
		if (type(str[i]) == MathParser_CharType_Digit)
		{
			/*	find out where the number that starts with 'str[i]' ends:	*/
			int j;
			for (j = i; type(str[j]) == MathParser_CharType_Digit; j++);

			/*
			 * The digits between i and j-1 form an integer, thus: they are
			 * stored in numLinkedList[]:
			 */
			numLinkedList[p->numCount].val = To_int(str, i, j - 1);

			/*	check decimal point	*/
			if (type(str[j]) == MathParser_CharType_Point)
			{
				// find out where the number after the point ends:
				int k;
				for (k = j + 1; type(str[k]) == MathParser_CharType_Digit; k++);

				/*
				 * The digits between j+1 and k-1 form an integer, thus: We add
				 * them at our num arr, but after a point:
				 */
				numLinkedList[p->numCount].val +=
					To_after_point(str, j + 1, k - 1);

				i = k - 1;
			}
			else
				i = j - 1;

			numLinkedList[p->numCount].nextPtr =
				(void*)&(numLinkedList[p->numCount + 1]);
			p->numCount++;
		}

		else if (type(str[i]) == MathParser_CharType_Operator)
		{
			opLinkedList[p->opCount].nextPtr =
				(void*)&(opLinkedList[p->opCount + 1]);

			opLinkedList[p->opCount++].val = str[i];
		}

		else if (type(str[i]) == MathParser_CharType_Letter)
		{
			numLinkedList[p->numCount].nextPtr =
				(void*)&(numLinkedList[p->numCount + 1]);
			// TODO: what if the word start with 'x', 'y', 'z', 'e' or "pi" ?

			if (str[i] == 'x')
			{
				// Just put its value in its place:
				numLinkedList[p->numCount++].val = x;
			}
			else if (str[i] == 'y')
			{
				// Just put its value in its place:
				numLinkedList[p->numCount++].val = y;
			}
			else if (str[i] == 'z')
			{
				// Just put its value in its place:
				numLinkedList[p->numCount++].val = z;
			}
			else if (str[i] == 'e')
			{
				// Just put its value in its place:
				numLinkedList[p->numCount++].val = 2.71828182846;
			}
			else if (str[i] == 'p' && str[i + 1] == 'i') // pi
			{
				// Just put its value in its place:
				numLinkedList[p->numCount++].val = 3.14159265359;
				i++;
			}
			else
			{
				/*	find where this word ends	*/
				int j;
				for (
					j = i + 1; type(str[j]) == MathParser_CharType_Letter; j++);

				/*
				 * get pointer to the cpp function that this word implements
				 */
				double(*funcPtr)(double) =
					MathParse_ptrGetFunction(str, i, j-1);

				/*	parse inputs of this word (i.e.: arguments), if any	*/
				double arguments = 0.0;
				if (str[j] == '(')
				{
					/*	Find the closer of 'j':	*/
					int closer = find_closing_bracket(str, j);
					/*	Parse every thing between opener and closer	*/
					arguments = EVAL(str, j + 1, closer - 1, x, y, z);
					i = closer;
				}
				else
					i = j - 1;

				/*
				 * apply the function that this word implements, as input, give
				 * it: 'arguments'
				 *
				 * and add function's numerical value to num array
				 */
				numLinkedList[p->numCount++].val = funcPtr(arguments);
			}
		}

		else if (str[i] == '(') // opener
		{
			/*	Find the closer:	*/
			int closer = find_closing_bracket(str, i);

			/*	Parse every thing between i and closer into 'inside':	*/
			double inside = EVAL(str, i + 1, closer - 1, x, y, z);

			numLinkedList[p->numCount].nextPtr =
				(void*)&(numLinkedList[p->numCount + 1]);

			numLinkedList[p->numCount++].val = inside;

			i = closer;
		}
	}

	/**	parse numbers and operators to find the final evaluation value	*/
	if (p->opCount == 0)
	{
		opLinkedList[0].val = '\0';
		opLinkedList[0].nextPtr = NULL;
	}
	else
		opLinkedList[p->opCount - 1].nextPtr = NULL;

	numLinkedList[p->numCount - 1].nextPtr = NULL;

	Char_LinkedList_t* currentOpPtr = &opLinkedList[0];
	Double_LinkedList_t* currentNumPtr = &numLinkedList[0];

	/*	Do all '^'s first	*/
	while(currentOpPtr != NULL)
	{
		if (currentOpPtr->val == '^')
		{
			Double_LinkedList_t* nextNumPtr =
				(Double_LinkedList_t*)currentNumPtr->nextPtr;

			currentNumPtr->val = pow(currentNumPtr->val, nextNumPtr->val);

			currentNumPtr->nextPtr = nextNumPtr->nextPtr;
		}

		else
			currentNumPtr = (Double_LinkedList_t*)currentNumPtr->nextPtr;

		Char_LinkedList_t* nextOpPtr =
			(Char_LinkedList_t*)currentOpPtr->nextPtr;

		if (nextOpPtr == NULL)
			break;

		else if (nextOpPtr->val == '^')
			currentOpPtr->nextPtr = nextOpPtr->nextPtr;

		currentOpPtr = nextOpPtr;
	}

	/*	Do all '*'s and '/'s second	*/
	if (opLinkedList[0].val == '^')
		currentOpPtr = (Char_LinkedList_t*)opLinkedList[0].nextPtr;
	else
		currentOpPtr = &opLinkedList[0];

	currentNumPtr = &numLinkedList[0];
	while(currentOpPtr != NULL)
	{
		if (currentOpPtr->val == '*')
		{
			Double_LinkedList_t* nextNumPtr =
				(Double_LinkedList_t*)currentNumPtr->nextPtr;

			currentNumPtr->val = currentNumPtr->val * nextNumPtr->val;

			currentNumPtr->nextPtr = nextNumPtr->nextPtr;
		}

		else if (currentOpPtr->val == '/')
		{
			Double_LinkedList_t* nextNumPtr =
				(Double_LinkedList_t*)currentNumPtr->nextPtr;

			currentNumPtr->val = currentNumPtr->val / nextNumPtr->val;

			currentNumPtr->nextPtr = nextNumPtr->nextPtr;
		}

		else
			currentNumPtr = (Double_LinkedList_t*)currentNumPtr->nextPtr;

		Char_LinkedList_t* nextOpPtr =
			(Char_LinkedList_t*)currentOpPtr->nextPtr;

		if (nextOpPtr == NULL)
			break;

		else if (nextOpPtr->val == '*' || nextOpPtr->val == '/')
			currentOpPtr->nextPtr = nextOpPtr->nextPtr;

		currentOpPtr = nextOpPtr;
	}

	/*	Do all '+'s and '-'s third	*/
	if (
		opLinkedList[0].val == '*' || opLinkedList[0].val == '^' ||
		opLinkedList[0].val == '/')
		currentOpPtr = (Char_LinkedList_t*)opLinkedList[0].nextPtr;
	else
		currentOpPtr = &opLinkedList[0];

	currentNumPtr = &numLinkedList[0];
	while(currentOpPtr != NULL)
	{
		if (currentOpPtr->val == '+')
		{
			Double_LinkedList_t* nextNumPtr =
				(Double_LinkedList_t*)currentNumPtr->nextPtr;

			currentNumPtr->val = currentNumPtr->val + nextNumPtr->val;

			currentNumPtr->nextPtr = nextNumPtr->nextPtr;
		}

		else if (currentOpPtr->val == '-')
		{
			Double_LinkedList_t* nextNumPtr =
				(Double_LinkedList_t*)currentNumPtr->nextPtr;

			currentNumPtr->val = currentNumPtr->val - nextNumPtr->val;

			currentNumPtr->nextPtr = nextNumPtr->nextPtr;
		}

		else
			currentNumPtr = (Double_LinkedList_t*)currentNumPtr->nextPtr;

		Char_LinkedList_t* nextOpPtr =
			(Char_LinkedList_t*)currentOpPtr->nextPtr;

		if (nextOpPtr == NULL)
			break;

		else if (nextOpPtr->val == '+' || nextOpPtr->val == '-')
			currentOpPtr->nextPtr = nextOpPtr->nextPtr;

		currentOpPtr = nextOpPtr;
	}

	return numLinkedList[0].val;
}

/*******************************************************************************
 * struct MathParser_Function_t:
 ******************************************************************************/
double(*MathParse_ptrGetFunction(char* str, int start, int end))(double)
{
	/*	copy str[start] : str[end] to a new temp string	*/
	char tempStr[MAX_EXPRESSION_STR_LEN];
	int tempStrLen = end - start + 2;
	for(int i = start; i <= end; i++)
		tempStr[i - start] = str[i];
	tempStr[tempStrLen - 1] = '\0';

	/*	loop on function array and find a match	*/
	for (int i = 0; MathParser_FunctionArr[i].wordStr != NULL; i++)
	{
		if (strcmp(tempStr, MathParser_FunctionArr[i].wordStr) == 0)
		{
			return MathParser_FunctionArr[i].funcPtr;
		}
	}

	/*	if it was not found in arr, return NULL	*/
	return NULL;
}







