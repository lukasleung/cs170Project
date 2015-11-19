/****************************************************************
  File: parser.c
 -------------
  This file implements the interface given in parser.h.
****************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "parser.h"

/****************************************************************
 Data members
 ------------
 token:    	array of characters stored for token
 ****************************************************************/
char token[20];

/****************************************************************
 Function: printLevel(int level, char* printString)
 --------------------
 Private function that prints the correct amount of spaces 
 (2 spaces for each level) depending on the level within the
 string they are. Will then print out the specified string if one
 was inputted
 ****************************************************************/
void printLevel(int level, char* printString){
	int i;
	for ( i = 0; i < level ; i = i+1 ) { printf("  "); }	
	// check to see if there was string inputted; if yes, print
	if (printString[0] != '\0') { printf("%s\n",printString); }
}


/****************************************************************
 Function: *init(char data, ConsCell *first, ConsCell *rest)
 --------------------
 Private function that initializes a conscell based off of the 
 information provided by user.
 ****************************************************************/
List init(char* data) {
    List cell = (List) malloc(sizeof(struct conscell));
    if (data == NULL) {
    	// initializing with no data from user
    	cell->data = NULL;
    } else {
    	// allocate memory for data portion of List, copy data there
    	cell->data = malloc(sizeof(char)*strlen(data) + 1); 
    	strcpy(cell->data, data);
	}
	// pointers will be set outside method
    cell->first = NULL;
    cell->rest = NULL;
    return cell;
}

/****************************************************************
 Function: See header file for documentation.
 ****************************************************************/
void printList2(List list, int start) {
	if (list != NULL) {
		if (list->data != NULL) {
			printf("%s", list->data);
		} else {
			if (start) { printf("("); }
			
			printList2(list->first, 1);
			
			if (list->rest == NULL) { printf(")"); } 
			else { 
				printf(" ");
				printList2(list->rest, 0); 
			}
		}
	}
}

void printList(List list) {
	printList2(list, 1);
}

/****************************************************************
 Function: S_Expression(int level)
 --------------------
 Private function that Creates a conscell List while adhering to 
 the specifications discussed in class. 
 ****************************************************************/
List S_Expression(int level) {
	List local, temp;
	if ( !strcmp(token,"(") ) {	// check if open
		printf("yolo (\n");
		local = init(NULL);
		strcpy(token, getToken()); // token = getToken();
		local->first = S_Expression(level+1);
		temp = local;
		while ( strcmp(token,")") ) {
			// not close => check if nested or if an element 
			printf("should not be here!\n");
			temp->rest = init(NULL);	// have the rest point ot a new List
			temp = temp->rest;			// let's alter the next list
			temp->first = S_Expression(level+1);
		}
		temp->rest = NULL;
	} else if (!strcmp(token,"#t")) {
		local = init("#t");// true;
	} else if (!strcmp(token,"()") || !strcmp(token,"#f")) {
		local = init("#f");// false;
	} else if( !strcmp(token,"\'") ) { // check if token is a '
		printf("yolo \'\n");
		local = init(NULL);
		local->first = init("quote");
		temp = local;
		printList(temp);
		strcpy(token, getToken());		
		temp->rest = init(NULL);
		temp = temp->rest;
        temp->first = S_Expression(level+1);
//		while (strcmp(token,")")) {
//		    printf("\' portion: %s\n", token);
//		    temp->rest = init(NULL);
//		    temp = temp->rest;
//		    temp->first = S_Expression(level+1);
//	    }
		printList(temp);
		temp->rest = NULL;
	}else {
		// not an open parens => print out content
		printf("else portion: %s\n", token);
		local = init(token); 
	}
	// always get the next token unless this is the end of the inputted string
	if (level != 0 ) { strcpy(token, getToken()); }
	return local;
}

/****************************************************************
 Function: See header file for documentation.
 ****************************************************************/
List parse() {
	startTokens(20);
	strcpy(token, getToken()); //token = getToken();
	return S_Expression(0);
}
