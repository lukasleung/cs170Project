/****************************************************************
 File: parser.h
 ----------------
 This is the parser for a lexical analyzer for part of Scheme.
 It has an operation for parsing a stream of tokens and printing
 them out with proper indentation.
 ****************************************************************/
#ifndef PARSER
#define PARSER
#include <stdlib.h>
#include "lexer.h"


/****************************************************************
 Data members
 ------------
 token:    	array of characters stored for token
 List :		A pointer called List for the conscell data structure 
			which stores either a string or character called data, 
			or two nested conscell structures called first and rest
 */ 
 
typedef struct conscell {
	char* data;
	struct conscell *first;
	struct conscell *rest;
}*List;


//List true, false;

char token[20];

/****************************************************************
 Function: parse()
 --------------------
 This function gets the current token and calls begins evaluating
 the S_Expression. There is no return however, it will correctly
 output the S_Expression with proper indentation.
 */
List parse();
//List eval(List list);

/****************************************************************
 Function: printList(List list)
 --------------------
 This function gets the current token and calls begins evaluating
 the S_Expression. There is no return however, it will correctly
 output the S_Expression onto a single line
 */
void printList(List list);

#endif
