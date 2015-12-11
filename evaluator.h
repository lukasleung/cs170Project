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

/****************************************************************
 Function: evals(List list)
 --------------------
 This function evaluates a given list as Scheme would have it
    - list:  is the List to be evaluated (conscell structure)
    - globalEnvironment: is the List structure to hold all of the
                user defined definitions (can be pre-populated)
    - functionEnvironment: is the List structure to hold all of the
                user defined functions (can be pre-populated)
 */
List evals(List list, List globalEnvironment, List functionEnvironment);

/****************************************************************
 Function: evalf(List list)
 --------------------
 This function evaluates a given list which acts as a nested function call
    - list:  is the List to be evaluated (conscell structure)
    - originalEnvironment: is the original List structure to hold all of the
                user defined definitions
    - augmentedEnvironment: is the augmented List structure to hold all of the
                function defined definitions
    - functionEnvironment: is the List structure to hold all of the
                user defined functions
    - numOl: number of elements in the originalEnvironment
    - numAl: number of elements in the augmentedEnvironment
    - numF : number of elements in the functionEnvironment
 */
List evalf(List list, List originalEnvironment, List augmentedEnvironment, List functionEnvironment, int numOl, int numAl, int numF);

#endif
