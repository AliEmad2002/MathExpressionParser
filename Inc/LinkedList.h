/*
 * LinkedList.h
 *
 *  Created on: Jan 17, 2023
 *      Author: Ali Emad Ali
 */

#ifndef INC_LINKEDLIST_H_
#define INC_LINKEDLIST_H_



typedef struct{
	double val;			// value
	void* nextPtr;		// pointer to next 'DoubleLinkedList_t' object
}Double_LinkedList_t;

typedef struct{
	char val;			// value
	void* nextPtr;		// pointer to next 'CharLinkedList_t' object
}Char_LinkedList_t;





#endif /* INC_LINKEDLIST_H_ */
