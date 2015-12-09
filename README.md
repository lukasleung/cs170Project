# Analysis of Programming Languages Project Fall 2015
**Goal:** *Create a Scheme Interpreter in C*

Click [here](http://cs.clarku.edu/~fgreen/courses/cs170/CS170HW/index.html)
for the assignment description **OR** click on one of the parts below to see detailed explanations

## [Part 1:](http://cs.clarku.edu/~fgreen/courses/cs170/CS170HW/CS170Proj1.html) 
  Write a recursive descent parser for the subset of Scheme defined by the following EBNF grammar

      <s_expression> ⟶ ( { <s_expression> } ) | #t | #f | <symbol> 

## [Part 2:](http://cs.clarku.edu/~fgreen/courses/cs170/CS170HW/CS170Proj2.html)
  1. Modify your S_Expression() function so that it returns the underlying "cons-cell" structure of the list that it parses.

  2. Add an eval() function that can evaluate a list, given its internal representation. For now, just implement the the following basic functions: 
    - **quote**
    - **car**
    - **cdr**
    - **cons**
    - **symbol?**

## [Part 3:](http://cs.clarku.edu/~fgreen/courses/cs170/CS170HW/CS170Proj3.html)
This assignment sets up the necessary preliminaries for function definition. Done in two steps.
  1. Add the following built-in Scheme functions to your interpreter:
    - **append**: takes two arguments and returns a list that appends the second list to the end of the first.
    - **null?**
    - **equal?**: returns #t if its arguments evaluate to the same value and #f otherwise
    - **assoc**: returns the pair associated with the symbol
    - **cond**: the multiple-alternative conditional
  
  2. Binding of Values to Symbols done simply by defining symbols to have values, which is much the same as defining constant functions. This is analogous to assigning values to variables in imperative languages.
    - When a definition is made using define, we will ADD to the referencing environment.
    - When eval comes across a symbol, it should try to "evaluate" it.

## [Part 4:](http://cs.clarku.edu/~fgreen/courses/cs170/CS170HW/CS170Proj4.html)
  Enhance your interpreter so that it is capable of reading user function definitions and evaluating them correctly.

## [Part 5:](http://cs.clarku.edu/~fgreen/courses/cs170/CS170HW/CS170Proj5.html)
  Make your interpreter even nicer than it is now. Add the following capabilites:
  1. Arithmetic functions: +, -, *. Note that addition and multiplication take any number of arguments. This will require you to recognize when an atom is a number, to convert back and forth between strings and numbers, and probably will entail the most work in this assignment.
  
  2. Logical functions: AND, OR and NOT. Note again that AND and OR take any number of arguments. AND returns the last value computed in its arguments, if they are all non-#f, and #f otherwise; OR returns the first non-#f argument if there is one, and #f otherwise. It's a short-circuit evaluation in both cases. NOT is just a synonym for NULL?.
  
  3. Relational operators: <, >. Naturally, these apply only to numbers.
  
  4. Other miscellaneous functions which you may not have added yet:
    - list
    - cadr, caddr, cadddr and caddddr
    - list?
    - number?
    - last
    - length

## Extra Credit:
+ Local binding via the LET special form. 
+ Pretty-printing lists (this would be very useful). Instead of having a list come out like this,

        ((this is a really long list to illustrate) (the problems with having 
        lists spill over) (from one line to another))

  print it out like this, indenting the right amount to expose the structure:

      ((this is a really long list to illustrate)
       (the problems with having lists spill over)
       (from one line to another))

