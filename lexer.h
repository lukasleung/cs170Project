/****************************************************************
 File: lexer.h
 ----------------
 This is the interface for a lexical analyzer for part of Scheme.
 It has an operation for initializing the stream of tokens and
 for getting the next token.
 ****************************************************************/
#ifndef LEXER
#define LEXER
#include <stdlib.h>

/****************************************************************
 Function: startTokens(int maxLength)
 ------------------------------------
 Initialize a token stream of tokens each of length <= maxLength.

 Call this function before scanning for tokens. Simply call,

    startTokens(20);

 The argument signifies the fact that tokens will have the
 given maximum length. Thus in the above statement tokens in
 the stream can be at most 20 characters long.
 */
void startTokens (int maxLength);

/****************************************************************
 Function: getToken()
 --------------------
 This function returns the next token in the token stream. It
 ignores all white space, including newlines. It returns the
 tokens "(", ")", "#t", "#f", "'" (the single quote), and "()"
 (the empty list, which is returned as the string "()"). All
 other strings of symbols with no white space are regarded as
 symbols or literals, and are returned as strings. (For ease
 in scanning, there is one exception: the "#" sign is excluded
 except at the beginning of #t or #f.)
 
 To invoke this, one may, for example, declare a string variable
 named token:

     char *token;
     
 Then getToken() can be invoked as,
 
     token = getToken();

 This technique is fine as long as you are quite sure you
 will only want to store the value in token until the
 next call to getToken(), and no longer.

 IT IS SAFER to allocate token statically, as in,

     char token[20];

 (assuming, for example, that tokens are <= 20 characters)
 and do a string copy of the return value from getToken():

     strcpy(token, getToken());

 rather than the above assignment. In this syntax the string
 copy acts much more like a true assignment, and using
 getToken() you can store the next token in another variable
 in the same way without losing the information in token.
     
 WARNING: Tokens may be at most maxLength characters long (see
 startTokens()). This function is not guaranteed to work for longer
 tokens, although it may work in most cases.
 */
char * getToken ();

#endif
