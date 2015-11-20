
/****************************************************************
  File: evaluator.c
 -------------
  This file implements the interface given in parser.h.
****************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "evaluator.h"
#include "parser.h"


/****************************************************************
 Function: List car(List list)
 --------------------
 Private function that returns a list containing only the first
 element of the given list.
 ****************************************************************/
List car(List list) {	
	return list->first;
}

/****************************************************************
 Function: List cdr(List list)
 --------------------
 Private function that returns a list containing everything from
 the current list without the first element of that list.
 ****************************************************************/
List cdr(List list) {
	return list->rest;
}

/****************************************************************
 Function: List symbol(List list)
 --------------------
 Private function that returns either #t or () depending on 
 wheather list is a symbol aka has data stored in it.
 ****************************************************************/
List quote(List list) {
	return list;
}


/****************************************************************
 Function: List symbol(List list)
 --------------------
 Private function that returns either #t or () depending on 
 wheather list is a symbol aka has data stored in it.
 ****************************************************************/
List symbol(List list) {
	if ( list->data != NULL ) { return init("#t"); }
	else { return init("()"); }
}

/****************************************************************
 Function: List cons(List listA, List listB)
 --------------------
 Private function that returns a conscell List by inserting the 
 first argument at the fron of the second so that listA appears as
 a singular element within List b.
 ****************************************************************/
List cons(List listA, List listB) {
	// need to create new pointers.
	List a = init(NULL);
	List b = init(NULL);
	a->first = listA;
	b->first = listB;
	// check to see if the first argument is false
	if ( a->first->data != NULL && !strcmp(a->first->data,"#f") ) { 
		// if both are false, return an empty List
		if ( b->first->data != NULL && !strcmp(b->first->data,"#f") ) {
			return init(NULL);
		}
		// just a is false, return b
		return b->first;
	}
	// check to see if the second argument is false, if so return a
	if ( b->first->data != NULL && !strcmp(b->first->data,"#f") ) { 
		return a;
	}
	// cons the two valid entries
	a->rest = b->first;
	return a;
}


/****************************************************************
 Function: See header file for documentation.
 ****************************************************************/


List eval(List list){	
    /*
    printf("\nyolo-eval");
	printf("\n          list: ");
	printList(list);
	printf("\n     car(list): ");
	printList(car(list));
	printf("\n     cdr(list): ");
	printList(cdr(list));
	printf("\ncar(cdr(list)): ");
	printList(car(cdr(list)));
	printf("\n");
	exit(0);
    */
	if (car(list) != NULL) {
		if (car(list)->data != NULL) {
			char* data = car(list)->data;
			if (!strcmp(data,"exit")) {
				printf("Have a nice day!\n");
				exit(0);
			} else if (!strcmp(data,"environment")) {
			    printf("print out my current environment\n");
			}
			List temp = eval(car(cdr(list)));
			if (!strcmp(data,"car")) {
				return car(temp);
			} else if (!strcmp(data,"cdr")) {
				return cdr(temp);
			} else if (!strcmp(data,"quote")) {
				return quote(car(cdr(list)));
			} else if (!strcmp(data,"symbol?")) {
				return symbol(temp);
			} else if (!strcmp(data,"cons")) {
				return cons(temp, eval(car(cdr(cdr(list)))));
			}
		} else {
			printf("%s", list->data);
			eval(car(list));
			if (list->rest == NULL) { return list; } 
			//else { return eval(list->rest); }
		}
	}
	return list;
}


