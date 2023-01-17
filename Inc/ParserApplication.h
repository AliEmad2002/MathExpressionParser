/*
 * ParserApplication.h
 * By: Ali Emad Ali
 * Date created: 2021-06-21
 */
 
#ifndef INC_PARSERAPPLICATION_H_
#define INC_PARSERAPPLICATION_H_

/*******************************************************************************
 * Derivative evaluation:
 ******************************************************************************/
double derivative(char* str, int n, double a);

/*******************************************************************************
 * Integrals:
 ******************************************************************************/
double single_integral(char* str, double xL, double xH);

double double_integral(char* str, double xL, double xH, double yL, double yH);

double triple_integral(
	char* str,
	double xL, double xH, double yL, double yH, double zL, double zH);

/*******************************************************************************
 * Function solving:
 ******************************************************************************/
/*	using newton-raphson	*/
double solve(char* str, double X0);

/*******************************************************************************
 * Continuity checking: (Not done yet)
 ******************************************************************************/
b8 check_continuity(
	char* str,
	double xL, double xH, double yL, double yH, double zL, double zH);

#endif	/*	INC_PARSERAPPLICATION_H_	*/
