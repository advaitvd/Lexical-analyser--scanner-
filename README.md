# Lexical-analyser--scanner-

A compiler is a program that can read a program in one language (soure code) and 
translate it into an equivalent program in another language(typically machine code).

Source Program ====> COMPILER ====> Machine level program

The following are the phases of compilation:

        Source Program
              |
              V
           Scanner (Lexical Analysis)
              |
              V
            Parser (Syntax Analyzer)
              | (Abstract Syntax Tree - AST)
              V
           Checker (Semantic Analyzer)
              | (Intermediate representation/verified AST)
              V
        Code Generator
              |
              V
      Target Machine Code

- The main focus of this project is on the first phase in which the scanner scans the
source program, performs a lexical analysis and generates tokens to be used in further
stages.
- The Scanner begins the analysis of the source program by reading the input text 
character by character and grouping individual characters into tokens such as
  - identifiers
  - literal values
  - reserved keywords
  - operators, etc.
- It puts the program into a compact and uniform format (a stream of tokens)
- It eliminates redundant information such as comments.
- The output token is of the form
  <token-name, attribute-value>

- In this project, we use the source code from the file sample.n which is our custom programming
language. It has the following features:
  - IDENTIFIER: token shall begin with a letter and be followed by upto 30 letters and numbers and
  are case sensitive.
  - INTLITERAL: integer numbers. eg. 0, 2, 109
  - FLOATLITERAL: floating point number available in two different format: xxx.xxx or .xxx
  - STRINGLITERAL (Max 80 characters including '\0')
  - COMMENTS: starts with '--' and lasts till the end of line.
  - keywords:
    - PROGRAM, BEGIN, END, FUNCTION, READ, WRITE, IF, ELSIF, ENDIF, DO, WHILE, CONTINUE, BREAK,
    RETURN, INT, VOID, STRING, FLOAT, TRUE, FALSE
  - Operators:
    - :=, +, -, *, /, =, !=, <, >, (, ), ;, ,, <=, >=

The program generates the tokens for the sample.n source code and outputs it in the terminal as
well as writes it to the output.txt file.




