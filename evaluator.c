/****************************************************************
  File: evaluator.c
 -------------
  This file implements the interface given in evaluator.h
****************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "evaluator.h"
#include "parser.h"


List glenv; // the global environment stored as a list
int numGE;


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
	if (car(a)->data != NULL && !strcmp(car(a)->data,"#f")) { 
		// if both are false, return an empty List
		if (car(b)->data != NULL && !strcmp(car(b)->data,"#f")) {
			return init(NULL);
		}
		// just a is false, return b
		return b->first;
	}
	// check to see if the second argument is false, if so return a
	if (car(b)->data != NULL && !strcmp(car(b)->data,"#f") ) { 
		return a;
	}
	// cons the two valid entries
	a->rest = car(b);
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
    if ((car(listA) != NULL && car(listB) == NULL) ||
        (car(listA) == NULL && car(listB) != NULL) ||
        (cdr(listA) != NULL && cdr(listB) == NULL) ||
        (cdr(listA) == NULL && cdr(listB) != NULL) ||
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
    if (car(listA) != NULL && car(listB) != NULL) {
        result = equals(car(listA), car(listB)); // recursive call
        // check what the result was, if it was false say it, otherwise
        //  continue to check rest
        if ( !strcmp(result->data, "#f") ) {
            return init("#f");
        }
    }
    // if they both have rests, ensure they are the same
    if (cdr(listA) != NULL && cdr(listB) != NULL) {
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
 Function: List assocString(char* symbol, List list)
 --------------------
 Private function that returns the pair associated with the symbol, and #f if the 
 symbol is not the first element of any pair
 ***********************************************************************************/
List assocString(char* symbol, List list) {
    // go through the list checking each pair
    while (list != NULL) {
        // get pair
        if ( car(list) != NULL ) {
            List pair = car(list);            
            // check the first element of pair
             if (car(pair) != NULL) {              
                List element = car(pair);
                // check whether the element is the same as given symbol
                if (element->data != NULL) {
                    if (!strcmp(symbol,element->data)) {
                        return pair;
                    }
                }               
            }
        }
        // get the next tuple
        list = cdr(list);
    }
    
    return init("#f");
 }
 
/***********************************************************************************
 Function: List assoc(List symbol, List list)
 --------------------
 Private function that returns the pair associated with the symbol, and #f if the 
 symbol is not the first element of any pair
 ***********************************************************************************/
List assoc(List symbol, List list) {
    return assocString(symbol->data, list);
 }
 
/***********************************************************************************
 Function: List cond(List list)
 --------------------
 The multiple-alternative conditional
 ***********************************************************************************/
List cond(List list) {
    if (list != NULL && car(list) != NULL) {  
        // sturcture is a pair, first part is the boolean, 
        //  second is the part to be executed     
        List structure = car(list); 
        if (car(structure) != NULL) {
            List boolean = eval(car(structure));    // get boolean portion
            // check to see if boolean portion is true
            if ( boolean->data != NULL && (!strcmp(boolean->data, "#t") || !strcmp(boolean->data, "else")) && cdr(structure) != NULL) {
                List rest = cdr(structure); // the executable portion
                List evalStatement = car(rest);
                return eval(evalStatement);
            }
        }  
        // recursive portion to be called if there is more to the cond statement
        if (cdr(list) != NULL) {
            return cond(cdr(list)); 
        }
    }
    return init("#f");
 }



/************************************************************************************
 Function: void printEnvironment()
 --------------------
 Private function that prints out the current global environement
 ***********************************************************************************/
void printEnvironment() {
    printf("Number elements in global environment: %d\n", numGE);
    if (numGE == 0) {
        printList(glenv);
    } else {
        int i = 1;
        printf("%d. ", i);
        printList(car(glenv));  // print the first one
        // if there are more, print them out
        List temp = cdr(glenv);
        while (temp != NULL) {
            i++;
            printf("\n%d. ", i);
            printList(car(temp));
            temp = cdr(temp);
        }
    }
}

/************************************************************************************
 Function: void addToEnvironment()
 --------------------
 Private function that prints out the current global environement
 ***********************************************************************************/
void addToEnvironment(List term, List definition) {      
    // need to repackage the definition
    List temp = init(NULL);
    temp->first = definition;
    // put the term and definition into a pair
    List def = init(NULL);
    def->first = term;
    def->rest = temp;
    
    // tell if this is the first element in the global environment
    if (numGE == 0) {
        glenv->first = def;
    } else {
        List head = glenv;
        List lastHead;
        while (head != NULL) {
            if (cdr(head) == NULL) {
                lastHead = head;
            }
            head = cdr(head);
        }
        lastHead->rest = init(NULL);  
        lastHead->rest->first = def;
    }  
    numGE++;
}


/***********************************************************************************
 Function: See header file for documentation.
 ***********************************************************************************/
List eval(List list) {
	if (car(list) != NULL) {
		if (car(list)->data != NULL) {
			char* data = car(list)->data;
			if (!strcmp(data,"exit")) {
				printf("Have a nice day!\n");
				exit(0);
			} else if (!strcmp(data,"environment")) {
			    printEnvironment();
			    return NULL;
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
                return cons(temp, eval(car(cdr(cdr(list)))) );
            } else if (!strcmp(data,"append")) {
                return append(temp, eval(car(cdr(cdr(list)))) );
            } else if (!strcmp(data,"equal?")) {
                return equals(temp, eval(car(cdr(cdr(list)))) );
            } else if (!strcmp(data,"assoc")) {
                return assoc(temp, eval(car(cdr(cdr(list)))) );         
			} else if (!strcmp(data,"cond")) {
			    List pass = eval(cdr(list));
			    return cond(pass);
			} else if (!strcmp(data,"define")) {
			    List definition = eval(car(cdr(cdr(list))));
			    addToEnvironment(temp, definition);
			    return glenv;
			}
		} else {
			// printf("%s", list->data);
			eval(car(list));
			if (list->rest == NULL) { return list; }
		}
	} else {
	    List re = assoc(list, glenv);
	    if (re->data == NULL) {
	        return car(cdr(re));
        }
    }
	return list;
}


List evals(List list, List globalEnvironment) {
    glenv = globalEnvironment;
    return eval(list);
}
