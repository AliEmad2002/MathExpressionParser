/*
 * MathParser.h
 * By: Ali Emad Ali
 * Date created: 2021-06-21
 */
 
#ifndef INC_MATHPARSER_H_
#define INC_MATHPARSER_H_


/*******************************************************************************
 * Type of a character (byte):
 ******************************************************************************/
typedef enum{
	MathParser_CharType_Error = -1,
	MathParser_CharType_Digit,
	MathParser_CharType_Point,
	MathParser_CharType_Operator,
	MathParser_CharType_Bracket,
	MathParser_CharType_Letter,
	MathParser_CharType_space
}MathParser_CharType_t;

MathParser_CharType_t type(char ch);

/*******************************************************************************
 * Converting a string to a number:
 ******************************************************************************/
/*
 * Converts string section from i to j, to an integer.
 * (Return value is double as it is more commonly used in this program, which
 * saves casting time).
 */
double To_int(char* str, int i, int j);

/*
 * Converts string section from i to j, to a floating point number, such that
 * all numbers are after decimal point.
 * Example: To_after_point("123456", 0, 5) = 0.123456
 */
double To_after_point(char* str, int j, int k);

/*
 * Evaluates a mathematical expression to a numerical value.
 * Internally creates object of struct parser.
 */
double EVAL(const char* str, int start, int end, double x, double y, double z);

/*******************************************************************************
 * Evaluating arrays of numbers with their corrresponding operators:
 ******************************************************************************/
double numerical_EVAL(double num[50], char op[30], int start, int end_num);

/*******************************************************************************
 * struct MathParser:
 ******************************************************************************/
typedef struct
{
    char str[MAX_EXPRESSION_STR_LEN];			// string of math expression.
    int n; 										// Used length of str array.

    /*
     * while parsing, number and operator may be re-arranged (due to algorithem)
     * so linked list would be a good boost of arranging process.
     */
    Double_LinkedList_t numLinkedList[MAX_EXPRESSION_STR_LEN / 2];
    Char_LinkedList_t opLinkedList[MAX_EXPRESSION_STR_LEN / 2];

	int numCount;								// used length of 'num' array
    int opCount;								// used length of 'op' array
}MathParser_t;

/*
 * copies char array to p->str.
 * checks for syntax errors first. If any, it returns false. otherwise it
 * returns true.
 */
b8 MathParser_b8SetExpressionString(
	MathParser_t* p, const char* expressionStr, int start, int end);

/*
 * inits linked list elemnts of a parser object.
 * Note: parser object must be init first before evaluating. No checking before
 * evaluation to reduce overhead.
 */
void MathParser_voidInitParserLinkedLists(MathParser_t* p);

/*
 * Function that evaluates object of struct "MathParser" into a numerical
 * value.
 */
double MathParser_d64Evaluate(MathParser_t* p, double x, double y, double z);

/*******************************************************************************
 * struct MathParser_Function_t:
 ******************************************************************************/
double(*MathParse_ptrGetFunction(char* str, int start, int end))(double);

#endif	/*	INC_MATHPARSER_H_	*/
