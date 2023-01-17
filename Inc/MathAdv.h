/*
 * MathAdv.h
 * By: Ali Emad Ali
 * Date created: 2021-06-21
 */
 
#ifndef INC_MATHADV_H_
#define INC_MATHADV_H_

/*
 * returns i ^ n
 * n range: 0 and all possible positive numbers.
 */
double pos_powr(double i, unsigned int n);

/*	gets number of digits a anumber	*/
int Number_Of_Digits(double x);

/*	factorial (see math defintion)	*/
double factorial(int n);

/*	combination (see math defintion)	*/
double combination(int n, int k);

/*	functions fot implemented in math.h	*/
double sech(double);
double csch(double);
double coth(double);

double asech(double);
double acsch(double);
double acoth(double);

double sec(double);
double csc(double);
double cot(double);

double asec(double);
double acsc(double);
double acot(double);

#endif /*	INC_MATHADV_H_	*/
