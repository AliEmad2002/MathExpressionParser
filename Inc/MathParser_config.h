/*
 * MathParser_config.h
 *
 *  Created on: Jan 16, 2023
 *      Author: Ali Emad Ali
 */

#ifndef INC_MATHPARSER_CONFIG_H_
#define INC_MATHPARSER_CONFIG_H_

/*	include the headers containing the functions you would use	*/
#include <math.h>
#include "../Inc/mathAdv.h"

/*******************************************************************************
 * Memory allocation parameters:
 ******************************************************************************/
#define MAX_EXPRESSION_STR_LEN		100

/*******************************************************************************
 * struct MathParser_Function_t:
 ******************************************************************************/
typedef struct{
	const char* wordStr; 			// pointer to a constant string.d
	double(*funcPtr)(double);		// pointer to function.
}MathParser_Function_t;

typedef double (*ddFunc_t)(double);
/*******************************************************************************
 * Array of words (strings) and c functions they represent.
 * All functions MUST be of type: double(*)(double)
 * (User configurable):
 ******************************************************************************/
static const MathParser_Function_t MathParser_FunctionArr[] = {

	/*	square root	*/
	(MathParser_Function_t){"sqrt", (ddFunc_t)sqrt},

	/*	hyperbolic functions	*/
	(MathParser_Function_t){"sinh", (ddFunc_t)sinh},
	(MathParser_Function_t){"cosh", (ddFunc_t)cosh},
	(MathParser_Function_t){"tanh", (ddFunc_t)tanh},
	(MathParser_Function_t){"sech", (ddFunc_t)sech},
	(MathParser_Function_t){"csch", (ddFunc_t)csch},
	(MathParser_Function_t){"coth", (ddFunc_t)coth},

	/*	inverse hyperbolic functions	*/
	(MathParser_Function_t){"asinh", (ddFunc_t)asinh},
	(MathParser_Function_t){"acosh", (ddFunc_t)acosh},
	(MathParser_Function_t){"atanh", (ddFunc_t)atanh},
	(MathParser_Function_t){"asech", (ddFunc_t)asech},
	(MathParser_Function_t){"acsch", (ddFunc_t)acsch},
	(MathParser_Function_t){"acoth", (ddFunc_t)acoth},

	/*	trigonometric functions	*/
	(MathParser_Function_t){"sin", (ddFunc_t)sin},
	(MathParser_Function_t){"cos", (ddFunc_t)cos},
	(MathParser_Function_t){"tan", (ddFunc_t)tan},
	(MathParser_Function_t){"sec", (ddFunc_t)sec},
	(MathParser_Function_t){"csc", (ddFunc_t)csc},
	(MathParser_Function_t){"cot", (ddFunc_t)cot},

	/*	inverse trigonometric functions	*/
	(MathParser_Function_t){"asin", (ddFunc_t)asin},
	(MathParser_Function_t){"acos", (ddFunc_t)acos},
	(MathParser_Function_t){"atan", (ddFunc_t)atan},
	(MathParser_Function_t){"asec", (ddFunc_t)asec},
	(MathParser_Function_t){"acsc", (ddFunc_t)acsc},
	(MathParser_Function_t){"acot", (ddFunc_t)acot},

	/*	Logarithms	*/
	(MathParser_Function_t){"ln", (ddFunc_t)log},
	(MathParser_Function_t){"log10", (ddFunc_t)log10},

	/*	Abslute value	*/
	(MathParser_Function_t){"abs", (ddFunc_t)abs},

	/*	Array terminator	*/
	(MathParser_Function_t){NULL, NULL}
};

#endif	/*	INC_MATHPARSER_CONFIG_H_	*/
