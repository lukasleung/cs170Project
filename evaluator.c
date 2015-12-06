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


/***********************************************************************************
 Function: List car(List list)
 --------------------
 Private function that returns a list containing only the first element of the given
 list.
 ***********************************************************************************/
List car(List list) {	
	return list->first;
}

/***********************************************************************************
 Function: List cdr(List list)
 --------------------
 Private function that returns a list containing everything from the current list 
 without the first element of that list.
 ***********************************************************************************/
List cdr(List list) {
	return list->rest;
}

/***********************************************************************************
 Function: List quote(List list)
 --------------------
 Private function that returns the list given
 ***********************************************************************************/
List quote(List list) {
	return list;
}

/***********************************************************************************
 Function: List symbol(List list)
 --------------------
 Private function that returns either #t or () depending on wheather list is a symbol
 aka has data stored in it.
 ***********************************************************************************/
List symbol(List list) {
	if ( list->data != NULL ) { return init("#t"); }
	else { return init("()"); }
}

/***********************************************************************************
 Function: List cons(List listA, List listB)
 --------------------
 Private function that returns a conscell List by inserting the first argument at the
 fron of the second so that listA appears as a singular element within List b.
 ***********************************************************************************/
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

/***********************************************************************************
 Function: List listCopy(List list)
 --------------------
 Private function that returns a conscell List that is the identical copy of the 
 given list
 ***********************************************************************************/
List listCopy(List list) {
    if (list == NULL) { return NULL; }
    if (list->data != NULL) {   // if there is data stored in this conscell
        return init(list->data);
    }
    // no data, fill in first and rest 
    List copy = init(NULL);
    if (car(list) != NULL) {    // if there is a first, copy the first
        copy->first = listCopy(car(list));
    } 
    if (cdr(list) != NULL) {    // if there is a rest, copy the rest
        copy->rest = listCopy(cdr(list));
    }
    return copy;
}

/***********************************************************************************
 Function: List append(List listA, List listB)
 --------------------
 Private function that returns a conscell List by appending listB to the end of listA
 ***********************************************************************************/
 List append(List listA, List listB) {
    List a = init(NULL);
    a = listCopy(listA);
    if (cdr(a) != NULL) { // if the list has a rest, get to the last rest
        List temp = cdr(a);
        while (cdr(temp) != NULL) {
            temp = cdr(temp);
        }
        temp->rest = listCopy(listB);  // set the last rest to point to the copy of b
    } else {
        a->rest = listCopy(listB);  // 
    }
    return a;
 }

/***********************************************************************************
 Function: List nullFnc(List list)
 --------------------
 Private function that returns either true or false depending on if the given list
 is null
 ***********************************************************************************/
 List nullFnc(List list) {
    if ( list->data != NULL ) {
        if (!strcmp(list->data,"#f")) {
            return init("#t");
        }
    }
    return init("#f");
 }
 
/***********************************************************************************
 Function: int cellEqual(List listA, List listB)
 --------------------
 Private function that returns a 1 if the two cells have the same data and a 
 ***********************************************************************************/
 int cellEquals(List cellA, List cellB) {
    return strcmp(cellA->data, cellB->data);
 }

/***********************************************************************************
 Function: List checkStatus(List listA, List listB)
 --------------------
 Private function that returns true if the two initaial conscells are structurally 
 equivalent and false otherwise
 ***********************************************************************************/
 List checkStatus(List listA, List listB) {
    if ((listA->first != NULL && listB->first == NULL) ||
        (listA->first == NULL && listB->first != NULL) ||
        (listA->rest != NULL && listB->rest == NULL) ||
        (listA->rest == NULL && listB->rest != NULL) ||
        (listA->data != NULL && listB->data == NULL) ||
        (listA->data == NULL && listB->data != NULL)) {
        return init("#f");
    }
    return init("#t");
 }


/***********************************************************************************
 Function: List equals(List listA, List listB)
 --------------------
 Private function that returns a conscell List by appending listB to the end of listA
 ***********************************************************************************/
 List equals(List listA, List listB) {
    // check to see if the list have same initial structure
    List result = checkStatus(listA, listB);
    if ( !strcmp(result->data, "#f") ) {
        return init("#f");
    }
    // if they both hold data, make sure it is the same
    if (listA->data != NULL && listB->data != NULL) {
        if (cellEquals(listA, listB)) {
            return init("#f");
        }
    }
    // if they both have firsts, ensure they are the same
    if (listA->first != NULL && listB->first != NULL) {
        result = equals(car(listA), car(listB)); // recursive call
        // check what the result was, if it was false say it, otherwise
        //  continue to check rest
        if ( !strcmp(result->data, "#f") ) {
            return init("#f");
        }
    }
    // if they both have rests, ensure they are the same
    if (listA->rest != NULL && listB->rest != NULL) {
        result = equals(cdr(listA), cdr(listB)); // recursive call
        // check what result was
        if ( !strcmp(result->data, "#f") ) {
            return init("#f");
        }
    }   
    // have not returned false yet => these two lists are the same.
    return init("#t");
 }

/***********************************************************************************
 Function: See header file for documentation.
 ***********************************************************************************/
List eval(List list){
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
			} else if (!strcmp(data,"null?")) {
			    return nullFnc(temp);
			} else if (!strcmp(data,"cons")) {
				return cons(temp, eval(car(cdr(cdr(list)))));
			} else if (!strcmp(data,"append")) {
			    return append(temp, eval(car(cdr(cdr(list)))));
			} else if (!strcmp(data,"equal?")) {
			    return equals(temp, eval(car(cdr(cdr(list)))));
			}
		} else {
			printf("%s", list->data);
			eval(car(list));
			if (list->rest == NULL) { return list; }
		}
	}
	return list;
}


