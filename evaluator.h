/****************************************************************
 File: parser.h
 ----------------
 This is the parser for a lexical analyzer for part of Scheme.
 It has an operation for parsing a stream of tokens and printing
 them out with proper indentation.
 ****************************************************************/
#ifndef EVALUATOR
#define EVALUATOR
#include <stdlib.h>
#include "parser.h"


/****************************************************************
 Function: evals(List list)
 --------------------
 This function evaluates a given list as Scheme would have it
 */
List eval(List list);

List evals(List list, List globalEnvironment);

#endif
