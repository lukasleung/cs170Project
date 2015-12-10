#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "evaluator.h"

main()
{
	char token[20];
    List globalEnvironment = init(NULL);
	startTokens(20);

	printf("\nA prototype evaluator for Scheme.\n");
	printf("Type Scheme expressions using quote,\n");
	printf("car, cdr, cons and symbol?.\n");
	printf("The function call (exit) quits.\n\n");
    printf("scheme> ");
	while(1) {
		printList(evals(parse(), globalEnvironment));
		printf("\n\nscheme> ");
	}
	
}

