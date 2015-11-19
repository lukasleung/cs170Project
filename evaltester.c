#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "evaluator.h"

main()
{
	/*
	true = malloc(sizeof(struct conscell));
	false = malloc(sizeof(struct conscell));
	true->first = NULL;
	true->rest = NULL;
	false->first = NULL;
	false->rest = NULL;
	true->data = "#t";
	false->data = "#f";
	*/
	char token[20];

	startTokens(20);

	printf("A prototype evaluator for Scheme.\n");
	printf("Type Scheme expressions using quote,\n");
	printf("car, cdr, cons and symbol?.\n");
	printf("The function call (exit) quits.\n\n");

	while(1) {
		printf("scheme> ");
		printList(eval(parse()));
		printf("\n\n");
	}
	
}

