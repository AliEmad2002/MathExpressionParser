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
double EVAL(char* str, int start, int End, double x, double y, double z);

/*******************************************************************************
 * Evaluating arrays of numbers with their corrresponding operators:
 ******************************************************************************/
double numerical_EVAL(double num[50], char op[30], int start, int end_num);

/*******************************************************************************
 * struct MathParser:
 ******************************************************************************/
typedef struct
{
    char* str;				// string of math expression.
    int n; 					// Length of str array.
    
	double num[50]; 		// numbers are stored Here.
    char op[30]; 			// operators are stored Here.
    
	int numCount;			// used length of 'num' array
    int opCount;			// used length of 'op' array
	
    bool never_ran = true;	// if the object was never ran before, the string
							// 'str' needs to be checked for syntax errors and
							// remove spaces from. This variable is used to
							// store that state.
}MathParser;

/*
 * Function that evaluates object of struct "MathParser" into a numerical
 * value.
*/
double MathParser_doubleEval(
	MathParser* parser,
	double x = 0.0, double y = 0.0, double z = 0.0, int nC = 0, int oC = 0);
