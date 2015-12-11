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
    List functionEnvironment = init(NULL);
	startTokens(20);

	printf("\n\t\t\e[4mA prototype evaluator for Scheme.\e[0m\n\n");
	printf("Type Scheme expressions using \e[3mquote, car, cdr, cons\e[0m and many more.\n");
	printf("   Or define symbols and functions on your own like in Scheme.\n");
	printf("   Type \e[1m(environment)\e[0m to display the current defined symbols.\n");
	printf("     Type \e[1m(functions)\e[0m to display all the current functions.\n");
	printf("\t\tThe function call \e[1m(exit)\e[0m quits.\n\n");
    printf("scheme> ");
	while(1) {
		printList(evals(parse(), globalEnvironment, functionEnvironment));
		printf("\n\nscheme> ");
	}
	
}

