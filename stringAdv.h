/*
 * StringAdv.cpp
 * By: Ali Emad Ali
 * Date created: 2021-06-21
 */

/*
 * stucks 'ch' at str[k], shifts all characters after it one byte forward
 * Note: 'str' must have enough size.
 */
void stuck(char* str, char ch, int k);

/*
 * Finds closing bracket of an opening one in a string.
 * Note: no error handling yet! bracketing in string must be correct. Otherwise
 * Unexpected result is returned.
 */
int find_closing_bracket(char* str, int opening_B);

/*	returns length of a string	*/
int LEN(char* str);
