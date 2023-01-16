/*
 * MathParser_config.h
 *
 *  Created on: Jan 16, 2023
 *      Author: Ali Emad Ali
 */

#pragma once

using namespace std;

/*	include the headers containing the functions you would use	*/
#include <math.h>
#include "../Inc/mathAdv.h"

double foo(double);
double foo(int);

/*******************************************************************************
 * Array of words (strings) and cpp functions they represent.
 * All functions MUST be of type: double(*)(double)
 * (User configurable):
 ******************************************************************************/
const MathParser_Function_t MathParser_FunctionArr[] = {

	/*	square root	*/
	(MathParser_Function_t){"sqrt", static_cast<double(*)(double)>(sqrt)},

	/*	hyperbolic functions	*/
	(MathParser_Function_t){"sinh", static_cast<double(*)(double)>(sinh)},
	(MathParser_Function_t){"cosh", static_cast<double(*)(double)>(cosh)},
	(MathParser_Function_t){"tanh", static_cast<double(*)(double)>(tanh)},
	(MathParser_Function_t){"sech", static_cast<double(*)(double)>(sech)},
	(MathParser_Function_t){"csch", static_cast<double(*)(double)>(csch)},
	(MathParser_Function_t){"coth", static_cast<double(*)(double)>(coth)},

	/*	inverse hyperbolic functions	*/
	(MathParser_Function_t){"asinh", static_cast<double(*)(double)>(asinh)},
	(MathParser_Function_t){"acosh", static_cast<double(*)(double)>(acosh)},
	(MathParser_Function_t){"atanh", static_cast<double(*)(double)>(atanh)},
	(MathParser_Function_t){"asech", static_cast<double(*)(double)>(asech)},
	(MathParser_Function_t){"acsch", static_cast<double(*)(double)>(acsch)},
	(MathParser_Function_t){"acoth", static_cast<double(*)(double)>(acoth)},

	/*	trigonometric functions	*/
	(MathParser_Function_t){"sin", static_cast<double(*)(double)>(sin)},
	(MathParser_Function_t){"cos", static_cast<double(*)(double)>(cos)},
	(MathParser_Function_t){"tan", static_cast<double(*)(double)>(tan)},
	(MathParser_Function_t){"sec", static_cast<double(*)(double)>(sec)},
	(MathParser_Function_t){"csc", static_cast<double(*)(double)>(csc)},
	(MathParser_Function_t){"cot", static_cast<double(*)(double)>(cot)},

	/*	inverse trigonometric functions	*/
	(MathParser_Function_t){"asin", static_cast<double(*)(double)>(asin)},
	(MathParser_Function_t){"acos", static_cast<double(*)(double)>(acos)},
	(MathParser_Function_t){"atan", static_cast<double(*)(double)>(atan)},
	(MathParser_Function_t){"asec", static_cast<double(*)(double)>(asec)},
	(MathParser_Function_t){"acsc", static_cast<double(*)(double)>(acsc)},
	(MathParser_Function_t){"acot", static_cast<double(*)(double)>(acot)},

	/*	Logarithms	*/
	(MathParser_Function_t){"ln", static_cast<double(*)(double)>(log)},
	(MathParser_Function_t){"log10", static_cast<double(*)(double)>(log10)},

	/*	Abslute value	*/
	(MathParser_Function_t){"abs", static_cast<double(*)(double)>(abs)},
};

